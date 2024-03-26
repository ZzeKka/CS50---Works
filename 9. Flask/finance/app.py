import os
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/cash_up", methods=["GET", "POST"])
@login_required
def cash_up():
    """Add money to your account"""
    if request.method == "GET":
        return render_template("cash_up.html")
    else:
        added_cash = float(request.form.get("cash"))
        if not added_cash:
            return apology("Invalid amount")
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        user_cash = float(user_cash[0]["cash"])
        balance = user_cash + added_cash
        db.execute("Update users SET cash = ? WHERE id = ?", balance, session["user_id"])
        return redirect("/")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    transactions = db.execute(
        "SELECT symbol, SUM(shares) AS shares, price, SUM(value) AS value FROM transactions WHERE user_id = ? GROUP BY symbol", session["user_id"])
    cash_db = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    if cash_db:
        cash = cash_db[0]["cash"]
    else:
        cash = 0
    grand_total = cash
    for item in transactions:
        grand_total += item["value"]
    return render_template("index.html", database=transactions, cash=cash, grand_total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not symbol:
            return apology("Invalid Symbol")
        if lookup(symbol) == None:
            return apology("symbol not found")
        else:
            stock = lookup(symbol)
        if not shares.isdigit():
            return apology("You cannot purchase partial shares")
        shares = int(shares)
        if shares <= 0:
            return apology("Invalid shares")
        price = stock["price"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = cash[0]["cash"]
        total = shares * price
        if cash < total:
            return apology("Sorry youre broke")
        date = datetime.datetime.now()
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, value, date) VALUES(?, ?, ?, ?, ?, ?)",
                   session["user_id"], stock["symbol"], shares, price, shares * price, date)
        new_balance = cash - total
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, session["user_id"])
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT * FROM transactions WHERE user_id = ?", session["user_id"])
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        s = request.form.get("symbol")
        if lookup(s) == None:
            return apology("symbol not found")
        else:
            dict = lookup(s)
        price, symbol = dict["price"], dict["symbol"]
        return render_template("quoted.html", price=price, symbol=symbol)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username, password, confirmation = request.form.get(
            "username"), request.form.get("password"), request.form.get("confirmation")
        # ensure username is filled
        if not username:
            return apology("must provide username", 400)
        # ensure password is filled
        elif not password or not confirmation:
            return apology("must provide password", 400)
        # check if password and confirmation match
        elif password != confirmation:
            return apology("Passwords don't match", 400)
        # check if username exists
        elif db.execute("SELECT * FROM users WHERE username = ?", username):
            return apology("Username already taken", 400)
        # Insert new user
        hash = generate_password_hash(request.form.get("password"))
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)
        user_id = db.execute("SELECT id FROM users WHERE username = ?", username)
        session["user_id"] = user_id[0]["id"]
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        print(symbol)
        if not symbol:
            return apology("Invalid Symbol")
        if lookup(symbol) == None:
            return apology("symbol not found")
        else:
            stock = lookup(symbol)
        if not shares.isdigit():
            return apology("You cannot purchase partial shares")
        shares = int(shares)
        if shares < 0:
            return apology("Invalid shares")
        price = stock["price"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = cash[0]["cash"]

        user_shares = db.execute(
            "SELECT SUM(shares) as shares FROM transactions WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)
        print(user_shares)
        user_shares = user_shares[0]["shares"]

        transaction_value = shares * price
        if cash < transaction_value:
            return apology("Not enough money")

        print(shares)
        print(type(shares))
        print(user_shares)
        print(type(user_shares))
        if shares > user_shares:
            return apology("You dont have all those shares")

        date = datetime.datetime.now()
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, value, date) VALUES(?, ?, ?, ?, ?, ?)",
                   session["user_id"], symbol, (-1)*shares, price, (-1) * price * shares, date)
        new_balance = cash + transaction_value
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, session["user_id"])
        return redirect("/")
    else:
        symbols = db.execute(
            "SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", session["user_id"])
        return render_template("sell.html", symbols=[row["symbol"] for row in symbols])
