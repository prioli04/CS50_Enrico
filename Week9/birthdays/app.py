import os

import sqlite3
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    db = sqlite3.connect("birthdays.db")
    c = db.cursor()

    if request.method == "POST":

        # TODO: Add the user's entry into the database
        add_entry(request.form, c)

        db.commit()
        db.close()
        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        c.execute("SELECT name, month, day FROM birthdays;")
        q_result = c.fetchall()
        db.close()
        return render_template("index.html", birthdays_q=q_result)


def add_entry(form, c):
    name = form.get("name")
    month = form.get("month")
    day = form.get("day")

    c.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?);",
              (name, month, day))

    return
