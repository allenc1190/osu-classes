from google.cloud import datastore
from flask import Flask, request, jsonify
from google.auth import jwt
from google.auth.transport import requests
from requests_oauthlib import OAuth2Session
from google.oauth2 import id_token
from google.auth import crypt
import json
import os 

os.environ['OAUTHLIB_INSECURE_TRANSPORT'] = '1'

app = Flask(__name__)
client = datastore.Client()

CLIENT_ID = '235567067117-311138uqqb0mkl8hfuqj0c5snja780gf.apps.googleusercontent.com'
CLIENT_SECRET = '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'
#REDIRECT_URI = 'http://localhost:8080/oauth'
REDIRECT_URI = 'https://hw7-chanall.uw.r.appspot.com/oauth'
SCOPE = ['https://www.googleapis.com/auth/userinfo.profile', 'https://www.googleapis.com/auth/userinfo.email', 'openid']
oauth = OAuth2Session(CLIENT_ID, redirect_uri=REDIRECT_URI, scope=SCOPE)

@app.route('/')
def index():
	auth_url, state = oauth.authorization_url('https://accounts.google.com/o/oauth2/v2/auth?')

	return '<div style="text-align: center"><h1>Welcome</h1>\n <a href=%s>Sign in to get your JWT.</a></div>' % auth_url

@app.route('/oauth')
def oauthroute():
	token = oauth.fetch_token('https://accounts.google.com/o/oauth2/token', client_secret=CLIENT_SECRET, authorization_response=request.url)
	json_token = jsonify({"jwt": token['id_token']})

	return (json_token, 200)

@app.route('/verify')
def verify():
	try:
		idinfo = id_token.verify_oauth2_token(request.args['jwt'], requests.Request(), CLIENT_ID)
	except:
		return('Could not verify JWT!', 401)

	return repr(idinfo) + "<br> the user is: " + idinfo['email']

@app.route('/boats', methods=['GET', 'POST'])
def boats_get_post():

	if request.method == 'GET':
		list_public = False

		jwt_token = request.headers.get('Authorization')

		if jwt_token:
			jwt_token = jwt_token.split(" ")[1]

			try:
				jwt_sub = id_token.verify_oauth2_token(jwt_token, requests.Request(), CLIENT_ID)['sub']
			except:
				list_public = True
		else:
			list_public = True

		query = client.query(kind="boats")
		if list_public:
			query.add_filter("public", "=", True)

		else:
			query.add_filter("owner", "=", jwt_sub)
		results = list(query.fetch())

		for e in results:
			e["id"] = e.key.id

		return (json.dumps(results), 200)

	elif request.method == 'POST':
		jwt_token = request.headers.get('Authorization')

		if jwt_token:
			jwt_token = jwt_token.split(" ")[1]

			try:
				jwt_sub = id_token.verify_oauth2_token(jwt_token, requests.Request(), CLIENT_ID)['sub']
			except:
				return('Unable to verify JWT\n', 401)

		else:
			return (json.dumps('No JWT'), 401)

		content = request.get_json()

		if len(content) != 4:
			return (json.dumps({"Error": "The request object is missing at least one of the required attributes"}), 400)

		new_boat = datastore.entity.Entity(key=client.key("boats"))
		new_boat.update({"name": content["name"], "type": content["type"], "length": content["length"], "public": content["public"]})
		client.put(new_boat)

		return (json.dumps({"name": content["name"], "type": content["type"], "length": content["length"], "public": content["public"]}), 201)

	else:
		return 'Method not recogonized'

@app.route('/owners/<owner_id>/boats', methods=['GET'])
def boats_get_owners(owner_id):
	if request.method == 'GET':
		query = client.query(kind="boats")
		query.add_filter("public", "=", True)
		query.add_filter("owner", "=", owner_id)
		results = list(query.fetch())

		for e in results:
			e["id"] = e.key.id

		return (json.dumps(results), 200)

@app.route('/boats/<boat_id>', methods=['DELETE'])
def delete_boat(boat_id):
	if request.method == 'DELETE':
		jwt_token = request.headers.get('Authorization')

		if jwt_token:
			jwt_token = jwt_token.split(" ")[1]
			try:
				jwt_sub = id_token.verify_oauth2_token(jwt_token, requests.Request(), CLIENT_ID)['sub']
			except:
				return('Unable to verify JWT\n', 401)

		else:
			return (json.dumps('JWT was not given!'), 401)
		
		boat_key = client.key("boats", int(boat_id))
		boat = client.get(key=boat_key)

		if boat == None:
			return (json.dumps({'Error': 'No boat with this boat_id exists'}), 403)

		elif boat['owner'] != jwt_sub:
			return (json.dumps({'Error': 'This boat is owned by someone else!'}), 403)

		client.delete(boat_key)

		return (json.dumps(''), 204)

if __name__ == '__main__':
	app.run(host='127.0.0.1', port=8080, debug=True)