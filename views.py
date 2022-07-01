from flask import Blueprint, render_template, send_from_directory, request, jsonify
import os
import json
from datarec import DataRec
views = Blueprint("views", __name__, template_folder="templateFiles", static_folder="staticFiles")

@views.route("/")
def home():
    return render_template('home.html')

@views.route("/stats")
def stats():
    return render_template('stats.html')

@views.route("/favicon.ico")
def favicon():
    return send_from_directory(os.path.join(views.root_path, 'staticFiles'),'favicon.ico',mimetype='image/vnd.microsoft.icon')

@views.route("/404")
def FourOFour():
    return render_template("404.html")

@views.route("/datapost", methods=["GET", "POST"])
def datapost():
    if (request.method == "POST"):
        data = request.get_json()

        resp = jsonify(success=True)
        return resp
    if (request.method == "GET"):
        return render_template("404.html")