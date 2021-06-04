from flask import *
from RadioController import RadioController
from os import path, makedirs, mknod
from threading import Thread

app = Flask(__name__)

filename_list = []

radio = RadioController()


# makes sure list of movements exists
if not path.exists("movements"):
    if not path.isdir("movements"):
        makedirs("movements")
if not path.exists("movements/_files.list"):
    if not path.isfile("movements/_files.list"):
        mknod("movements/_files.list")


@app.route("/add_filename", methods=['GET'])
def handle_add_filename():
    print("Add_filename")
    add_filename = str(request.args.get('add_filename'))

    if add_filename != None:
        if not add_filename in filename_list:
            with open("movements/_files.list", "a") as file:
                file.write(add_filename + " ")
                #mknod("movements/" + add_filename + ".rbm")

        radio.receiveData(add_filename)

    return render_template("add_movement.html")


@app.route("/stop_recording", methods=['GET'])
def handle_stop_recording():
    radio.stopReceiving()
    return redirect("/")


@app.route("/load_filename", methods=['GET'])
def handle_load_filename():
    load_filename = str(request.args.get('load_filename')) + ".rbm"

    if load_filename != None:
        print(load_filename)
        pass

    return redirect("/")


@app.route("/", methods=['GET'])
def index():
    print("AAAAAA")
    with open("movements/_files.list", "r") as file:
        filename_list = file.readline().strip().split()

        print(filename_list)

    return render_template("index.html",  filename_list=filename_list)
