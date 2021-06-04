from flask import *
from RadioController import RadioController
from os import path, makedirs, mknod


app = Flask(__name__)

filename_list = []

rf = RadioController()


# makes sure list of movements exists
if not path.exists("movements"):
    if not path.isdir("movements"):
        makedirs("movements")
if not path.exists("movements/_files.list"):
    if not path.isfile("movements/_files.list"):
        mknod("movements/_files.list")


@app.route("/add_movement", methods=['GET'])
def handle_add_movement():
    add_movement = str(request.args.get('add_movement'))

    if add_movement != None:
        if not add_movement in filename_list:
            with open("movements/_files.list", "a") as file:
                file.write(add_movement + " ")

        rf.receiveData(add_movement)

    return render_template("add_movement.html")


@app.route("/stop_recording", methods=['GET'])
def handle_stop_recording():
    rf.stopReceiving()
    return redirect("/")


@app.route("/stop_playing", methods=['GET'])
def handle_stop_playing():
    rf.stopSending()
    return redirect("/")


@app.route("/load_movement", methods=['GET'])
def handle_load_movement():
    load_movement = str(request.args.get('load_movement'))

    if load_movement != None:
        if load_movement in filename_list:
            return redirect("/")
        else:
            rf.sendData(load_movement)

    return render_template("load_movement.html")


@app.route("/", methods=['GET'])
def index():
    with open("movements/_files.list", "r") as file:
        movements_list = file.readline().strip().split()

        print(movements_list)

    return render_template("index.html", movements_list=movements_list)
