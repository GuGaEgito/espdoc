from flask import Flask, jsonify, render_template
from flask_cors import CORS



app = Flask(__name__)
CORS(app)

estado_led = "OFF"

@app.route('/status', methods=['GET'])
def check_status():
    return jsonify({"led": estado_led})


#Método chamado pelo client
@app.route('/toggle', methods=['POST'])
def toggle_led():
    global estado_led
    estado_led = "ON" if estado_led == "OFF" else "OFF" #operador ternário
    return f"LED agora está {estado_led}"


@app.route("/")
def index():
    return render_template("index.html")


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5050, debug=True, use_reloader=False)

