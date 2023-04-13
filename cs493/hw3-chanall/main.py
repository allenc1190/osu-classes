from google.cloud import datastore
from flask import Flask, request
import json

app = Flask(__name__)
client = datastore.Client()

@app.route('/')
def index():
	return "Please navigate to /boats to use this"\

@app.route('/boats', methods=['POST','GET'])
def boats_post_get():
	if request.method == 'POST':
		content = request.get_json()

		if len(content) != 3:
			return (json.dumps({"Error": "The request object is missing at least one of the required attributes"}), 400)

		new_boat = datastore.entity.Entity(key=client.key("boats"))
		new_boat.update({"name": content["name"], "type": content["type"], "length": content["length"]})
		client.put(new_boat)

		return (json.dumps({"id": new_boat.key.id, "name": content["name"], "type": content["type"], "length": content["length"], "self": str(request.url) + "/" + str(new_boat.key.id)}), 201)
	
	elif request.method == 'GET':
		query = client.query(kind="boats")
		results = list(query.fetch())

		for e in results:
			e["id"] = e.key.id
			e["self"] = str(request.url) + "/" + str(e.key.id)

		return (json.dumps(results), 200)

	else:
		return 'Method not recogonized'

@app.route('/boats/<id>', methods=['GET','DELETE','PATCH'])
def boats_get_delete_patch(id):
	if request.method == 'GET':
		content = request.get_json()
		boat_key = client.key("boats", int(id))
		boat = client.get(key=boat_key)

		if boat == None:
			return (json.dumps({"Error": "No boat with this boat_id exists"}), 404)

		boat["id"] = id
		boat["self"] = str(request.url)

		return (json.dumps(boat), 200)
	
	elif request.method == 'DELETE':
		boat_key = client.key("boats", int(id))
		query = client.query(kind="slips")
		query.add_filter('current_boat', '=', int(id))
		result = list(query.fetch())

		if len(result) > 0:
			result[0]["current_boat"] = None
			client.put(result[0])

		if client.get(key=boat_key) == None:
			return (json.dumps({"Error": "No boat with this boat_id exists"}), 404)

		client.delete(boat_key)

		return ('',204)

	elif request.method == 'PATCH':
		content = request.get_json()

		if len(content) != 3:
			return (json.dumps({"Error": "The request object is missing at least one of the required attributes"}), 400)
		boat_key = client.key("boats", int(id))
		boat = client.get(key=boat_key)

		if boat == None:
			return (json.dumps({"Error": "No boat with this boat_id exists"}), 404)
		boat.update({"name": content["name"], "type": content["type"], "length": content["length"]})
		client.put(boat)

		return (json.dumps({"id": boat.key.id, "name": content["name"], "type": content["type"], "length": content["length"], "self": str(request.url)}), 200)

	else:
		return 'Method not recogonized'

@app.route('/slips', methods=['POST','GET'])
def slips_get_post():
	if request.method == 'POST':
		content = request.get_json()

		if len(content) != 1:
			return (json.dumps({"Error": "The request object is missing the required number"}), 400)

		new_slip = datastore.entity.Entity(key=client.key("slips"))
		new_slip.update({"number": content["number"], "current_boat": None})
		client.put(new_slip)

		return (json.dumps({"id": new_slip.key.id, "number": content["number"], "current_boat": None, "self": str(request.url) + "/" + str(new_slip.key.id)}), 201)
	
	elif request.method == 'GET':
		query = client.query(kind="slips")
		results = list(query.fetch())

		for e in results:
			e["id"] = e.key.id
			e["self"] = str(request.url) + "/" + str(e.key.id)

		return (json.dumps(results), 200)
		
	else:
		return 'Method not recogonized'

@app.route('/slips/<id>', methods=['GET', 'DELETE'])
def slips_get_delete(id):
	if request.method == 'GET':
		slip_key = client.key("slips", int(id))
		slip = client.get(key=slip_key)

		if slip == None:
			return (json.dumps({"Error": "No slip with this slip_id exists"}), 404)

		slip["id"] = id
		slip["self"] = str(request.url)

		return (json.dumps(slip), 200)

	elif request.method == 'DELETE':
		slip_key = client.key("slips", int(id))

		if client.get(key=slip_key) == None:
			return (json.dumps({"Error": "No slip with this slip_id exists"}), 404)

		client.delete(slip_key)

		return ('',204)

	else:
		return 'Method not recogonized'

@app.route('/slips/<slip_id>/<boat_id>', methods=['PUT', 'DELETE'])
def slips_put_delete(slip_id, boat_id):
	if request.method == 'PUT':
		slip = client.get(key=client.key("slips", int(slip_id)))
		boat = client.get(key=client.key("boats", int(boat_id)))

		if boat == None or slip == None:
			return (json.dumps({"Error": "The specified boat and/or slip does not exist"}), 404)

		elif slip["current_boat"] != None:
			return (json.dumps({"Error": "The slip is not empty"}), 403)

		slip.update({"current_boat": boat.key.id})
		client.put(slip)

		return('', 204)

	elif request.method == 'DELETE':
		slip = client.get(key=client.key("slips", int(slip_id)))
		boat = client.get(key=client.key("boats", int(boat_id)))

		if boat == None or slip == None or int(slip["current_boat"]) != int(boat_id):
			return (json.dumps({"Error": "No boat with this boat_id is at the slip with this slip_id"}), 404)

		slip.update({"current_boat": None})
		client.put(slip)

		return ('', 204)
	
if __name__ == '__main__':
	app.run(host='127.0.0.1', port=8081, debug=True)
