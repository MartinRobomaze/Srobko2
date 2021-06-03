from flask import *
import 

app = Flask(__name__)


@app.route("/add_filename", methods=['GET'])
def handle_add_filename():
    add_filename = request.args.get('add_filename')
    
    if add_filename != None:
        print(add_filename)
    
    return redirect("/")


@app.route("/load_filename", methods=['GET'])
def handle_load_filename():
    load_filename = request.args.get('load_filename')
    
    if load_filename != None:
        print(load_filename)
        pass
    
    return redirect("/")


@app.route("/", methods=['GET'])
def index():
    filename_list = ['mopslik', 'mopslik2', 'fdsafjaksdhjflakshf']
    
    return render_template("index.html",  filename_list=filename_list)
