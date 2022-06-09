from flask import Blueprint, render_template, send_from_directory, request, url_for
import os
import json
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

@views.route("/datapost", methods=["POST"])
def datapost():
    data = request.json()
