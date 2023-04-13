from google.cloud import datastore
from flask import Flask, request
from requests_oauthlib import OAuth2Session
from google.oauth2 import id_token
from google.auth import crypt, jwt
from google.auth.transport import requests
import requests as reqq
import json

import os 
os.environ['OAUTHLIB_INSECURE_TRANSPORT'] = '1'

app = Flask(__name__)
client = datastore.Client()

CLIENT_ID = '235567067117-311138uqqb0mkl8hfuqj0c5snja780gf.apps.googleusercontent.com'
CLIENT_SECRET = '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'
#REDIRECT_URI = 'http://localhost:8080/profile'
REDIRECT_URI = 'https://hw7-chanall.uw.r.appspot.com/profile'
SCOPE = ['https://www.googleapis.com/auth/userinfo.profile', 'https://www.googleapis.com/auth/userinfo.email', 'openid']
oauth = OAuth2Session(CLIENT_ID, redirect_uri=REDIRECT_URI, scope=SCOPE)

@app.route('/')
def index():
	auth_url, state = oauth.authorization_url('https://accounts.google.com/o/oauth2/v2/auth?')

	return '<div style="text-align: center"><h1>Welcome</h1>\n <p>Using hw7 url due to being unable to enable billing on another hw</p>\n <a href=%s>Sign in to continue.</a></div>' % auth_url

@app.route('/profile')
def oauthroute():
	token = oauth.fetch_token('https://accounts.google.com/o/oauth2/token', authorization_response=request.url, client_secret=CLIENT_SECRET)
	id_info = id_token.verify_oauth2_token(token['id_token'], requests.Request(), CLIENT_ID)

	# Search for user
	query = client.query(kind="users")
	query.add_filter("sub", "=", id_info['sub'])
	result = list(query.fetch())

	# Create a new user if they're not in the database
	if len(result) == 0:
		new_user = datastore.entity.Entity(key=client.key('users'))
		new_user.update({'email': id_info['email'], 'sub': id_info['sub']})
		client.put(new_user)

		return (("<h1>New Account Created</h1>\n <p>JWT: %s</p>\n <p>Unique User ID: %s</p>\n" % (token['id_token'], id_info['sub'])), 201)

	elif len(result) == 1:
		return (("<h1>Welcome back!</h1>\n <p>JWT: %s</p>\n <p>Unique User ID: %s</p>\n" % (token['id_token'], id_info['sub'])), 200)

@app.route('/users', methods=['GET'])
def get_users():
	if request.method == 'GET':
		query = client.query(kind="users")
		results = list(query.fetch())

		for e in results:
			e["id"] = e.key.id
			e["self"] = request.url + "/" + str(e.key.id)

		return (json.dumps(results), 200)

@app.route('/users/<uid>', methods=['GET'])
def get_user_id(uid):
	if request.method == 'GET':

		jwt_token = verifyJWT()
		if jwt_token == 'fail':
			return(json.dumps({'Error': 'Could not verify JWT!'}), 401)
		elif jwt_token == 'nojwt':
			return (json.dumps({'Error': 'JWT was not given!'}), 401)
		
		# Verify uid
		if jwt_token != uid:
			return(json.dumps({'Error': 'You do not have access to this user!'}), 401)
			
		# Find user with sub
		query = client.query(kind="users")
		query.add_filter("sub", "=", uid)
		results = list(query.fetch())

		if len(results) == 0:
			return(json.dumps({'Error': 'This user does not exist!\n'}), 401)

		for e in results:
			e["id"] = e.key.id
			e["self"] = request.url

		return (json.dumps(results), 200)

@app.route('/hws', methods=['GET', 'POST'])
def hws_get_post():
	if request.method == 'GET':
		jwt_token = verifyJWT()

		if jwt_token == 'fail':
			return(json.dumps({'Error': 'Could not verify JWT!'}), 401)

		elif jwt_token == 'nojwt':
			return (json.dumps({'Error': 'JWT was not given!'}), 401)

		query = client.query(kind="hws")
		query.add_filter('owner', '=', jwt_token)
		q_limit = int(request.args.get('limit', '5'))
		q_offset = int(request.args.get('offset', '0'))
		l_iterator = query.fetch(limit= q_limit, offset=q_offset)
		pages = l_iterator.pages
		results = list(next(pages))

		if l_iterator.next_page_token:
			next_offset = q_offset + q_limit
			next_url = request.base_url + "?limit=" + str(q_limit) + "&offset=" + str(next_offset)

		else:
			next_url = None

		for e in results:
			e["id"] = e.key.id
			e["self"] = request.url_root + 'hws/' + str(e.key.id)

			if e['tasks']:
				for single_task in e['tasks']:
					gtask_key = client.key("tasks", single_task['id'])
					gtask = client.get(key=gtask_key)
					single_task['title'] = gtask['title']
					single_task['due_date'] = gtask['due_date']
					single_task['description'] = gtask['description']
					single_task['completed'] = gtask['completed']
					single_task["self"] = request.url_root + "tasks/" + str(single_task['id'])

		output = {"hws": results}

		if next_url:
			output["next"] = next_url

		output['total'] = len(list(query.fetch()))

		return (json.dumps(output), 200)

	elif request.method == 'POST':
		jwt_token = verifyJWT()

		if jwt_token == 'fail':
			return(json.dumps({'Error': 'Could not verify JWT!'}), 401)

		elif jwt_token == 'nojwt':
			return (json.dumps({'Error': 'JWT was not given!'}), 401)

		content = request.get_json()

		if len(content) != 3:
			return (json.dumps({"Error": "The request object is missing at least one of the required attributes"}), 400)
		
		new_hw = datastore.entity.Entity(key=client.key("hws"))
		new_hw.update({"title": content["title"], "due_date": content["due_date"], "notes": content["notes"], "owner": jwt_token, "tasks": [], "completed_tasks": []})
		client.put(new_hw)

		new_hw.update({'id': new_hw.key.id, 'self': request.url + "/" + str(new_hw.key.id)})

		return (json.dumps(new_hw), 201)

@app.route('/tasks', methods=['GET', 'POST'])
def tasks_get_post():
	if request.method == 'GET':
		jwt_token = verifyJWT()

		if jwt_token == 'fail':
			return(json.dumps({'Error': 'Could not verify JWT!'}), 401)

		elif jwt_token == 'nojwt':
			return (json.dumps({'Error': 'JWT was not given!'}), 401)

		query = client.query(kind="tasks")
		query.add_filter('owner', '=', jwt_token)
		q_limit = int(request.args.get('limit', '5'))
		q_offset = int(request.args.get('offset', '0'))
		l_iterator = query.fetch(limit= q_limit, offset=q_offset)
		pages = l_iterator.pages
		results = list(next(pages))

		if l_iterator.next_page_token:
			next_offset = q_offset + q_limit
			next_url = request.base_url + "?limit=" + str(q_limit) + "&offset=" + str(next_offset)

		else:
			next_url = None

		for e in results:
			e["id"] = e.key.id
			e["self"] = request.url_root + 'tasks/' + str(e.key.id)

		output = {"tasks": results}

		if next_url:
			output["next"] = next_url

		output['total'] = len(list(query.fetch()))

		return (json.dumps(output), 200)

	elif request.method == 'POST':
		jwt_token = verifyJWT()

		if jwt_token == 'fail':
			return(json.dumps({'Error': 'Could not verify JWT!'}), 401)

		elif jwt_token == 'nojwt':
			return (json.dumps({'Error': 'JWT was not given!'}), 401)

		# Grab content
		content = request.get_json()

		# Check all properties
		if len(content) != 3:
			return (json.dumps({"Error": "The request object is missing at least one of the required attributes"}), 400)
		
		new_task = datastore.entity.Entity(key=client.key("tasks"))
		new_task.update({'title': content['title'], 'hid': None, 'completed': False, "description": content["description"], "due_date": content["due_date"], "owner": jwt_token})
		client.put(new_task)

		# Return object
		new_task.update({'id': new_task.key.id, 'self': request.url + "/" + str(new_task.key.id)})

		return (json.dumps(new_task), 201)

@app.route('/hws/<hid>', methods=['GET', 'DELETE', 'PUT', 'PATCH'])
def hws_get_delete_put_patch(hid):
	if request.method == 'GET':
		jwt_token = verifyJWT()

		if jwt_token == 'fail':
			return(json.dumps({'Error': 'Could not verify JWT!'}), 401)

		elif jwt_token == 'nojwt':
			return (json.dumps({'Error': 'JWT was not given!'}), 401)

		hw_key = client.key("hws", int(hid))
		hw = client.get(key=hw_key)

		if hw == None:
			return (json.dumps({"Error": "This hw does not exist!"}), 404)

		if hw['owner'] != jwt_token:
			return (json.dumps({'Error': 'You do not own this hw!'}), 401)

		hw['id'] = hw.key.id
		hw['self'] = request.url
		
		if hw['tasks']:
			for task in hw['tasks']:
				gtask_key = client.key("tasks", task['hid'])
				gtask = client.get(key=gtask_key)
				task['title'] = gtask['title']
				task['due_date'] = gtask['due_date']
				task['description'] = gtask['description']
				task['completed'] = gtask['completed']
				task['self'] = request.url_root + "tasks/" + str(task['hid'])

		if hw['completed_tasks']:
			for ctask in hw['completed_tasks']:
				gtask_key = client.key("tasks", ctask['hid'])
				gtask = client.get(key=gtask_key)
				ctask['title'] = gtask['title']
				ctask['due_date'] = gtask['due_date']
				ctask['description'] = gtask['description']
				ctask['completed'] = gtask['completed']

		return(json.dumps(hw), 200)
		
	elif request.method == 'DELETE':
		jwt_token = verifyJWT()

		if jwt_token == 'fail':
			return(json.dumps({'Error': 'Could not verify JWT!'}), 401)

		elif jwt_token == 'nojwt':
			return (json.dumps({'Error': 'JWT was not given!'}), 401)

		hw_key = client.key("hws", int(hid))
		hw = client.get(key=hw_key)

		if hw == None:
			return (json.dumps({'Error': 'This hw does not exist!'}), 401)
		
		if hw['owner'] != jwt_token:
			return (json.dumps({'Error': 'You do not own this hw!'}), 401)
		
		if hw['tasks']:
			for task in hw['tasks']:
				gtask_key = client.key("tasks", task['id'])
				gtask = client.get(key=gtask_key)
				gtask['hid'] = None
				client.put(gtask)

		if hw['completed_tasks']:
			for task in hw['completed_tasks']:
				gtask_key = client.key("tasks", task['id'])
				gtask = client.get(key=gtask_key)
				gtask['hid'] = None
				client.put(gtask)
		
		client.delete(hw)

		return(json.dumps(''), 204)

	elif request.method == 'PUT' or request.method == 'PATCH':
		jwt_token = verifyJWT()

		if jwt_token == 'fail':
			return(json.dumps({'Error': 'Could not verify JWT!'}), 401)

		elif jwt_token == 'nojwt':
			return (json.dumps({'Error': 'JWT was not given!'}), 401)

		hw_key = client.key("hws", int(hid))
		hw = client.get(key=hw_key)

		if hw == None:
			return (json.dumps({'Error': 'This hw does not exist!'}), 401)
		
		if hw['owner'] != jwt_token:
			return (json.dumps({'Error': 'You do not own this hw!'}), 401)
		
		content = request.get_json()

		if len(content) == 0:
			return (json.dumps({"Error": "The request object is missing!"}), 400)

		for properties in content:
			if properties == 'title' and type(content.get(properties)) == str:
				hw["title"] = content.get(properties)

			elif properties == 'notes' and type(content.get(properties)) == str:
				hw["notes"] = content.get(properties)

			elif properties == 'due_date' and type(content.get(properties)) == str:
				hw["due_date"] = content.get(properties)

			else:
				return (json.dumps({"Error": "Invalid content!"}), 400)

		client.put(hw)
		hw['id'] = hw.key.id
		hw['self'] = request.url
		
		if hw['tasks']:
			for single_task in hw['tasks']:
				gtask_key = client.key("tasks", single_task['id'])
				gtask = client.get(key=gtask_key)
				single_task['title'] = gtask['title']
				single_task['due_date'] = gtask['due_date']
				single_task['description'] = gtask['description']
				single_task['completed'] = gtask['completed']
				single_task["self"] = request.url_root + "tasks/" + str(single_task['id'])

		if hw['completed_tasks']:
			for ctask in hw['completed_tasks']:
				gtask_key = client.key("tasks", ctask['id'])
				gtask = client.get(key=gtask_key)
				ctask['title'] = gtask['title']
				ctask['due_date'] = gtask['due_date']
				ctask['description'] = gtask['description']
				ctask['completed'] = gtask['completed']
				ctask["self"] = request.url_root + "tasks/" + str(ctask['id'])

		return(json.dumps(hw), 201)

@app.route('/hws/<hid>/tasks', methods=['GET', 'POST'])
def tasks_get_post_hws(hid):
	if request.method == 'GET':
		jwt_token = verifyJWT()

		if jwt_token == 'fail':
			return(json.dumps({'Error': 'Could not verify JWT!'}), 401)

		elif jwt_token == 'nojwt':
			return (json.dumps({'Error': 'JWT was not given!'}), 401)

		hw_key = client.key("hws", int(hid))
		hw = client.get(key=hw_key)

		if hw == None:
			return (json.dumps({'Error': 'This hw does not exist!'}), 401)

		if hw['owner'] != jwt_token:
			return (json.dumps({'Error': 'You do not own this hw!'}), 401)

		query = client.query(kind="tasks")
		query.add_filter("hid", "=", hid)
		query.add_filter("completed", "=", False)
		tasks = list(query.fetch())

		query = client.query(kind="tasks")
		query.add_filter("hid", "=", hid)
		query.add_filter("completed", "=", True)
		ctasks = list(query.fetch())

		for e in tasks:
			e["id"] = e.key.id
			e["self"] = request.url_root + "tasks/" + str(e.key.id)

		for e in ctasks:
			e["id"] = e.key.id
			e["self"] = request.url_root + "tasks/" + str(e.key.id)

		return(json.dumps({'tasks': tasks, 'completed_tasks': ctasks}), 200)
		
	elif request.method == 'POST':
		jwt_token = verifyJWT()

		if jwt_token == 'fail':
			return(json.dumps({'Error': 'Could not verify JWT!'}), 401)

		elif jwt_token == 'nojwt':
			return (json.dumps({'Error': 'JWT was not given!'}), 401)

		hw_key = client.key("hws", int(hid))
		hw = client.get(key=hw_key)

		if hw == None:
			return (json.dumps({'Error': 'This hw does not exist!'}), 401)

		if hw['owner'] != jwt_token:
			return (json.dumps({'Error': 'You do not own this hw!'}), 401)

		content = request.get_json()

		if len(content) != 3:
			return (json.dumps({"Error": "The request object is missing at least one of the required attributes"}), 400)
		
		new_task = datastore.entity.Entity(key=client.key("tasks"))
		new_task.update({'title': content['title'], 'hid': hid, 'completed': False, "description": content["description"], "due_date": content["due_date"], "owner": jwt_token})
		client.put(new_task)

		hw['tasks'].append({'id': new_task.key.id, 'owner': jwt_token, 'hid': hid})
		client.put(hw)

		hw.update({'id': hw.key.id, 'self': request.url_root + "hws/" + str(hw.key.id)})

		for task in hw['tasks']:
			task['self'] = request.url_root + "tasks/" + str(task['id'])

		return (json.dumps(hw), 201)

@app.route('/tasks/<tid>', methods=['GET', 'DELETE', 'PUT', 'PATCH'])
def tasks_get_delete_put_patch(tid):
	if request.method == 'GET':
		jwt_token = verifyJWT()

		if jwt_token == 'fail':
			return(json.dumps({'Error': 'Could not verify JWT!'}), 401)

		elif jwt_token == 'nojwt':
			return (json.dumps({'Error': 'JWT was not given!'}), 401)

		task_key = client.key("tasks", int(tid))
		task = client.get(key=task_key)

		if task == None:
			return (json.dumps({'Error': 'This task does not exist!'}), 401)

		if task['owner'] != jwt_token:
			return (json.dumps({'Error': 'You do not own this task!'}), 401)

		task['id'] = task.key.id
		task['self'] = request.url

		return(json.dumps(task), 200)

	elif request.method == 'DELETE':
		jwt_token = verifyJWT()

		if jwt_token == 'fail':
			return(json.dumps({'Error': 'Could not verify JWT!'}), 401)

		elif jwt_token == 'nojwt':
			return (json.dumps({'Error': 'JWT was not given!'}), 401)

		task_key = client.key("tasks", int(tid))
		task = client.get(key=task_key)

		if task == None:
			return (json.dumps({"Error": "No task with this task_id exists"}), 404)
			
		elif task['owner'] != jwt_token:
			return (json.dumps({'Error': 'You do not own this task!'}), 401)
		
		if task['hid']:
			hw_key = client.key("hws", int(task['hid']))
			hw = client.get(key=hw_key)

			if task['completed']:
				hw['completed_tasks'].remove({'id': task.key.id, 'owner': jwt_token, 'hid': str(hw.key.id)})

			else:
				hw['tasks'].remove({'id': task.key.id, 'owner': jwt_token, 'hid': str(hw.key.id)})

			client.put(hw)
		
		client.delete(task)			

		return(json.dumps(''), 204)

	elif request.method == 'PUT' or request.method == 'PATCH':
		jwt_token = verifyJWT()

		if jwt_token == 'fail':
			return(json.dumps({'Error': 'Could not verify JWT!'}), 401)

		elif jwt_token == 'nojwt':
			return (json.dumps({'Error': 'JWT was not given!'}), 401)

		task_key = client.key("tasks", int(tid))
		task = client.get(key=task_key)

		if task == None:
			return (json.dumps({'Error': 'This task does not exist!'}), 401)
		
		if task['owner'] != jwt_token:
			return (json.dumps({'Error': 'You do not own this task!'}), 401)
		
		content = request.get_json()

		if len(content) == 0:
			return (json.dumps({"Error": "The request object is missing!"}), 400)

		for properties in content:
			if properties == 'completed' and type(content.get(properties)) == bool:
				if task["hid"]:
					hw_key = client.key("hws", int(task['hid']))
					hw = client.get(key=hw_key)

					if task['completed'] == False and content.get(properties) == True:
						hw['tasks'].remove({'id': task.key.id, 'owner': jwt_token, 'hid': str(hw.key.id)})
						hw['completed_tasks'].append({'id': task.key.id, 'owner': jwt_token, 'hid': str(hw.key.id)})

					elif task['completed'] == True and content.get(properties) == False:
						hw['completed_tasks'].remove({'id': task.key.id, 'owner': jwt_token, 'hid': str(hw.key.id)})
						hw['tasks'].append({'id': task.key.id, 'owner': jwt_token, 'hid': str(hw.key.id)})

					client.put(hw)

				task["completed"] = content.get(properties)

			elif properties == 'title' and type(content.get(properties)) == str:
				task["title"] = content.get(properties)

			elif properties == 'description' and type(content.get(properties)) == str:
				task["description"] = content.get(properties)

			elif properties == 'due_date' and type(content.get(properties)) == str:
				task["due_date"] = content.get(properties)

			else:
				return (json.dumps({"Error": "Invalid content!"}), 400)

		client.put(task)
		task['id'] = task.key.id
		task['self'] = request.url

		return(json.dumps(task), 201)

@app.route('/hws/<hid>/tasks/<tid>', methods=['PUT'])
def put_task_hw(hid, tid):
	if request.method == 'PUT':
		jwt_token = verifyJWT()

		if jwt_token == 'fail':
			return(json.dumps({'Error': 'Could not verify JWT!'}), 401)

		elif jwt_token == 'nojwt':
			return (json.dumps({'Error': 'JWT was not given!'}), 401)

		hw_key = client.key("hws", int(hid))
		hw = client.get(key=hw_key)
		task_key = client.key("tasks", int(tid))
		task = client.get(key=task_key)

		if hw == None:
			return (json.dumps({"Error": "This hw does not exist!"}), 404)

		if task == None:
			return (json.dumps({"Error": "This task does not exist!"}), 404)

		if hw['owner'] != jwt_token:
			return (json.dumps({'Error': 'You do not own this hw!'}), 401)

		elif task['owner'] != jwt_token:
			return (json.dumps({'Error': 'You do not own this task!'}), 401)

		for ptask in hw['tasks']:
			if ptask['id'] == int(tid):
				return (json.dumps({'Error': 'This task is already in the hw!'}), 403)
		
		hw['tasks'].append({'id': task.key.id, 'owner': task['owner'], 'hid': hid})
		client.put(hw)
		task['hid'] = hid
		client.put(task)

		return(json.dumps(''), 204)

def verifyJWT():
	jwt_token = request.headers.get('Authorization')

	if jwt_token:
		jwt_token = jwt_token.split(" ")[1]

		try:
			jwt_token = id_token.verify_oauth2_token(jwt_token, requests.Request(), CLIENT_ID)['sub']

		except:
			return 'fail'

	else:
		return 'nojwt'
		
	return jwt_token

if __name__ == '__main__':
	app.run(host='127.0.0.1', port=8080, debug=True)