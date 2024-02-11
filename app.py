from flask import Flask, request, jsonify

app = Flask(__name__)

ID_LIST = ['1234', '5678', '0']

@app.route('/api_door_lock', methods=['POST'])
def post_example():
    data = request.json  # Assuming the incoming data is in JSON format

    badge_id = data.get('badge_id')
    target_token = data.get('target_token')

    print(badge_id, target_token)
    if badge_id is not None and target_token is not None:
        if badge_id in ID_LIST and target_token == 'OK!':
            return jsonify({'message': 'Access granted'}), 200
        else:
            return jsonify({'message': 'Invalid badge_id'}), 400
    else:
        return jsonify({'message': 'Missing badge_id or target_token in the POST request'}), 400

if __name__ == '__main__':
    app.run(debug=False, host="0.0.0.0", port=5000)
