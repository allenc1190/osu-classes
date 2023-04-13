from google.cloud import datastore
import requests
from flask import render_template, redirect, session
import flask
import uuid
import string
import random

app = flask.Flask(__name__)
client = datastore.Client()
app.secret_key = str(uuid.uuid4().hex)

ENDPOINT = "https://accounts.google.com/o/oauth2/v2/auth?"
SCOPE = "profile"
#ACCESS_TYPE = "access_type=offline&"
RESPONSE_TYPE = "code"
REDIRECT_URI = "https://chanall-hw6.uw.r.appspot.com/oauth"
#REDIRECT_URI = "http://localhost:8080/oauth"
CLIENT_ID = "356450809548-oltjmmmaoqdggfk3cjbhfov4u1db1ai3.apps.googleusercontent.com"
CLIENT_SECRET = "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"
STATE = ''.join(random.choice(string.ascii_uppercase + string.ascii_lowercase + string.digits) for i in range(10))

@app.route('/')
def index():
	return render_template('index.html')

@app.route('/gauth')
def gauth():
	flask.session['state'] = STATE
	url = f'{ENDPOINT}client_id={CLIENT_ID}&scope={SCOPE}&response_type={RESPONSE_TYPE}&redirect_uri={REDIRECT_URI}&state={STATE}'
	return redirect(url, code=307)

@app.route('/oauth')
def oauth():
	stateCheck = flask.session('state')
	if stateCheck != requests.args.get('state'):
		return ('State does not match. Please login again')

	auth_code = flask.request.args.get('code')
	data = {
		'code': auth_code,
		'client_id': CLIENT_ID,
		'client_secret': CLIENT_SECRET,
		'redirect_uri': REDIRECT_URI,
		'grant_type': 'authorization_code'
	}

	r = requests.post('https://oauth2.googleapis.com/token', data=data)
	json_data = r.json()
	#print('response = ', json_data)
	acc_token = json_data['access_token']

	headers = {'Authorization': 'Bearer ' + acc_token}

	profile = requests.get("https://people.googleapis.com/v1/people/me?personFields=names", headers=headers)
	profile_json = profile.json()

	givenName= profile_json['names'][0]['givenName']
	familyName= profile_json['names'][0]['familyName']
	state= STATE

	return render_template('oauth.html', givenName=givenName, familyName=familyName, state=state)

if __name__ == '__main__':
	app.run(host='127.0.0.1', port=8080, debug=True)