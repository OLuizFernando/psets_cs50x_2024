import os

from cs50 import SQL
from datetime import datetime
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


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    if db.execute("SELECT 1 FROM stocks WHERE user_id = ?", session["user_id"]):
        stocks = db.execute(
            "SELECT symbol, shares FROM stocks WHERE user_id = ?", session["user_id"])
        current_cash = db.execute("SELECT cash FROM users WHERE id = ?",
                                  session["user_id"])[0]["cash"]
        total_balance = current_cash

        for stock in stocks:
            stock["current_price"] = lookup(stock["symbol"])["price"]
            stock["total_value"] = stock["current_price"] * stock["shares"]
            total_balance += stock["total_value"]

            stock["current_price"] = usd(stock["current_price"])
            stock["total_value"] = usd(stock["total_value"])

        return render_template("index.html", stocks=stocks, current_cash=usd(current_cash), total_balance=usd(total_balance))

    else:
        current_cash = db.execute("SELECT cash FROM users WHERE id = ?",
                                  session["user_id"])[0]["cash"]
        return render_template("empty.html", current_cash=usd(current_cash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        n_shares = request.form.get("shares")

        stocks = db.execute(
            "SELECT symbol, shares FROM stocks WHERE user_id = ?", session["user_id"])
        stock_symbols_owned = [stock["symbol"] for stock in stocks]

        if not request.form.get("symbol") or not request.form.get("shares"):
            return apology("you must fill in all fields", 403)

        if not lookup(symbol):
            return apology("stock symbol not found")

        try:
            int(n_shares)
        except ValueError:
            return apology("invalid number of shares")

        if not n_shares.isnumeric or int(n_shares) < 1:
            return apology("invalid number of shares")

        current_cash = db.execute("SELECT cash FROM users WHERE id = ?",
                                  session["user_id"])[0]["cash"]
        share_price = lookup(symbol)["price"]
        total_price = share_price * int(n_shares)

        if current_cash < share_price * int(n_shares):
            return apology("insufficient funds")

        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   current_cash - total_price, session["user_id"])

        if symbol not in stock_symbols_owned:
            db.execute("INSERT INTO stocks (user_id, symbol, shares) VALUES (?, ?, ?)",
                       session["user_id"], symbol, n_shares)
        else:
            current_shares = db.execute(
                "SELECT shares FROM stocks WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)[0]["shares"]
            db.execute("UPDATE stocks SET shares = ? WHERE user_id = ? AND symbol = ?",
                       current_shares + int(n_shares), session["user_id"], symbol)

        insert_transaction(user_id=session["user_id"], type="BUY",
                           symbol=symbol, price=total_price, shares=n_shares)
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    if request.method == "POST":
        current_password_hash = db.execute(
            "SELECT hash FROM users WHERE id = ?", session["user_id"])[0]["hash"]
        current_password = request.form.get("current_password")

        new_password = request.form.get("new_password")
        confirm_new_password = request.form.get("confirm_new_password")

        if not current_password or not new_password or not confirm_new_password:
            return apology("you must fill in all fields", 403)

        if not check_password_hash(current_password_hash, current_password):
            return apology("invalid current password")

        if new_password != confirm_new_password:
            return apology("invalid new password confirmation")

        if current_password == new_password:
            return apology("new password must differ from current one")

        new_password_hash = generate_password_hash(new_password)
        db.execute("UPDATE users SET hash = ? WHERE id = ?", new_password_hash, session["user_id"])

        return render_template("password_changed.html")

    else:
        return render_template("change_password.html")


@app.route("/delete_account", methods=["GET", "POST"])
@login_required
def delete_account():
    if request.method == "POST":
        account_info = db.execute(
            "SELECT username, hash FROM users WHERE id = ?", session["user_id"])[0]

        username = request.form.get("username")
        password = request.form.get("password")

        if not username or not password:
            return apology("you must fill in all fields", 403)

        if username != account_info["username"] or not check_password_hash(account_info["hash"], password):
            return apology("invalid username and/or password", 403)

        db.execute("DELETE FROM transactions WHERE user_id = ?", session["user_id"])
        db.execute("DELETE FROM stocks WHERE user_id = ?", session["user_id"])
        db.execute("DELETE FROM users WHERE id = ?", session["user_id"])

        return redirect("/logout")

    else:
        return render_template("delete_account.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute(
        "SELECT type, symbol, price, shares, year, month, day, hour, minute FROM transactions WHERE user_id = ?", session[
            "user_id"]
    )
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


@app.route("/options", methods=["GET", "POST"])
@login_required
def options():
    """Account options"""
    if request.method == "POST":
        if request.form["action"] == "change_password":
            return redirect("/change_password")

        if request.form["action"] == "delete_account":
            return redirect("/delete_account")

        return apology("unkown error")
    else:
        username = db.execute("SELECT username FROM users WHERE id = ?",
                              session["user_id"])[0]["username"]
        return render_template("options.html", username=username)


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote"""
    if request.method == "POST":
        if lookup(request.form.get("symbol")):
            stock = lookup(request.form.get("symbol"))
            stock["price"] = usd(stock["price"])
            return render_template("stock.html", stock=stock)
        else:
            return apology("stock symbol not found")
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username").strip()
        password = request.form.get("password")
        confirm_password = request.form.get("confirmation")

        users = db.execute("SELECT * FROM users")

        if not username or not password or not confirm_password:
            return apology("you must fill in all fields")

        elif password != confirm_password:
            return apology("confirm your password correctly")

        for user in users:
            if username == user["username"]:
                return apology("username already exists")

        hash = generate_password_hash(password)

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)

        user_id = db.execute(
            "SELECT id FROM users WHERE username = ?", username
        )

        session["user_id"] = user_id

        return redirect("/login")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    stocks = db.execute("SELECT symbol, shares FROM stocks WHERE user_id = ?", session["user_id"])

    if request.method == "POST":
        symbol = request.form.get("symbol")
        n_shares = request.form.get("shares")

        if not symbol or not n_shares:
            return apology("you must fill in all fields", 403)

        if int(n_shares) < 1:
            return apology("invalid number of shares")

        avaliable_symbols = [stock["symbol"] for stock in stocks]
        if symbol not in avaliable_symbols:
            return apology("stock not avaliable")

        avaliable_n_shares = db.execute(
            "SELECT shares FROM stocks WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)[0]["shares"]
        if int(n_shares) > avaliable_n_shares:
            return apology("insufficient shares to sell")

        current_cash = db.execute("SELECT cash FROM users WHERE id = ?",
                                  session["user_id"])[0]["cash"]
        share_price = lookup(symbol)["price"]
        total_price = share_price * int(n_shares)

        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   current_cash + total_price, session["user_id"])

        if int(n_shares) == avaliable_n_shares:
            db.execute("DELETE FROM stocks WHERE user_id = ? AND symbol = ?",
                       session["user_id"], symbol)

        else:
            db.execute("UPDATE stocks SET shares = ? WHERE user_id = ? AND symbol = ?",
                       avaliable_n_shares - int(n_shares), session["user_id"], symbol)

        insert_transaction(user_id=session["user_id"], type="SELL",
                           symbol=symbol, price=total_price, shares=n_shares)
        return redirect("/")

    else:
        return render_template("sell.html", stocks=stocks)


def insert_transaction(user_id, type, symbol, price, shares):
    """Insert all of the transaction infos into the transactions table"""
    now = datetime.now()

    year = f"{now.year:02d}"
    month = f"{now.month:02d}"
    day = f"{now.day:02d}"

    hour = f"{now.hour:02d}"
    minute = f"{now.minute:02d}"

    db.execute("INSERT INTO transactions (user_id, type, symbol, price, shares, year, month, day, hour, minute) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",
               user_id, type, symbol, usd(price), shares, year, month, day, hour, minute)
