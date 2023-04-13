from flask import Blueprint, request
from google.cloud import datastore
import json

client = datastore.Client()

bp = Blueprint('load', __name__, url_prefix= '/loads')

@bp.route('', methods=['GET', 'POST'])
def loads_get_post():
	if request.method == 'GET':
		query = client.query(kind="loads")
		q_limit = int(request.args.get('limit', '3'))
		q_offset = int(request.args.get('offset', '0'))
		g_iterator = query.fetch(limit= q_limit, offset=q_offset)
		pages = g_iterator.pages
		results = list(next(pages))

		if g_iterator.next_page_token:
			next_offset = q_offset + q_limit
			next_url = request.base_url + "?limit=" + str(q_limit) + "&offset=" + str(next_offset)

		else:
			next_url = None

		for e in results:
			e["id"] = e.key.id
			e["self"] = request.url_root + "loads/" + str(e.key.id)

			if e["item"] != None:
				e['item']['self'] = request.url_root + "boats/" + str(e['item']['id'])

		output = {"loads": results}

		if next_url:
			output["next"] = next_url

		return (json.dumps(output), 200)

	elif request.method == 'POST':
		content = request.get_json()
		if len(content) != 3:
			return (json.dumps({"Error": "The request object is missing at least one of the required attributes"}), 400)

		new_load = datastore.entity.Entity(key=client.key("loads"))
		new_load.update({"volume": content["volume"], 'item': None, 'content': content['item'], 'creation_date': content['creation_date']})
		client.put(new_load)
		new_load['id'] = new_load.key.id
		new_load['self'] = request.url + '/' + str(new_load.key.id)

		return (json.dumps(new_load), 201)

@bp.route('/<id>', methods=['GET', 'DELETE'])
def loads_get_delete(id):
	if request.method == 'GET':
		load_key = client.key("loads", int(id))
		load = client.get(key=load_key)

		if load == None:
			return (json.dumps({"Error": "No load with this load_id exists"}), 404)

		if load["item"]:
			load["item"]["self"] = request.url_root + "boats/" + str(load["item"]["id"])

		load["id"] = id
		load["self"] = request.url

		return (json.dumps(load), 200)

	if request.method == 'DELETE':
		key = client.key("loads", int(id))
		load = client.get(key=key)

		if load == None:
			return (json.dumps({"Error": "No load with this load_id exists"}), 404)

		if load['item'] != None:
			boat = client.get(key=client.key("boats", load['item']['id']))
			boat["loads"].remove({'id': load.key.id})
			client.put(boat)

		client.delete(key)

		return (json.dumps(''),204)

	else:
		return 'Method not recogonized'
