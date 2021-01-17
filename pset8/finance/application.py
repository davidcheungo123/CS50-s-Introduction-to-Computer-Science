import os
import json
import pandas as pd
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    names = db.execute("SELECT DISTINCT(name) FROM purchase WHERE purchase_id= :id_backup", id_backup= int(session["user_id"]))
    symbols= db.execute("SELECT DISTINCT(symbol) FROM purchase WHERE purchase_id= :id_backup", id_backup= int(session["user_id"]))
    shares_purchase= db.execute("SELECT name, stocks FROM purchase WHERE purchase_id=:id_backup GROUP BY name", id_backup= int(session["user_id"]))
    shares_sell = db.execute("SELECT name, stocks FROM sell WHERE sell_id=:id_backup GROUP BY name", id_backup= int(session["user_id"]))
    totals_bought=db.execute("SELECT name,SUM(total) FROM purchase WHERE purchase_id=:id_backup GROUP BY name", id_backup= int(session["user_id"]))
    totals_sell=db.execute("SELECT name,SUM(total) FROM sell WHERE sell_id=:id_backup GROUP BY name", id_backup= int(session["user_id"]))


    Lookup =[]
    Price_now =[]
    shares_bought_list=[]
    shares_sold_list=[]
    total_bought_list=[]


    for i in range(len(symbols)):

        Lookup.append(lookup(symbols[i]['symbol']))

        Price_now.append(Lookup[i]['price'])


    print(Lookup)
    print(Price_now)
    print(shares_purchase)
    print(shares_sell)
    print(totals_bought)
    print(totals_sell)

    remaining_shares= []
    remaining_totals= []

    for i in range(len(shares_purchase)):

        shares_left= shares_purchase[i]['stocks']

        totals_left = -totals_bought[i]['SUM(total)']

        for j in range(len(shares_sell)):

            if shares_purchase[i]['name'] == shares_sell[j]['name']:

                shares_left -=  shares_sell[j]['stocks']

            if totals_bought[i]['name'] == totals_sell[j]['name']:

                totals_left += totals_sell[j]['SUM(total)']


        remaining_shares.append(shares_left)

        remaining_totals.append(totals_left)

    stocks_sum =sum(remaining_totals)

    print(f"remaining_shares :{remaining_shares}" )
    print(f"remaining_totals : {remaining_totals}")


    list=[]

    stocks_total= 0

    for i in range(len(names)):

        stock_info ={}

        a= {'symbol' :Lookup[i]['symbol'] , 'name': Lookup[i]['name'], 'shares': int(remaining_shares[i]), 'price': round(Lookup[i]['price'],2), 'total' : round(remaining_shares[i]*Lookup[i]['price'],2)}

        stock_info.update(a)

        list.append(stock_info)

        stocks_total +=remaining_shares[i]*Lookup[i]['price']

    print(list)

    remaining_cash = db.execute("SELECT cash FROM users WHERE id= :id_backup", id_backup= int(session["user_id"]))

    remaining_cash_1 = remaining_cash[0]['cash']

    remaining_cash = round(remaining_cash[0]['cash'],2)

    grand_total= round(stocks_total + remaining_cash_1,2)


    return render_template("index.html", list=list, remaining_cash=remaining_cash, grand_total=grand_total)



@app.route("/history")
@login_required
def history():

    bought_data =db.execute("SELECT symbol, bought_stocks, price, timestamp FROM purchase WHERE purchase_id= :id_backup", id_backup= int(session["user_id"]))
    sold_data= db.execute("SELECT symbol, sold_stocks, PRICE, timestamp FROM sell WHERE sell_id= :id_backup", id_backup= int(session["user_id"]))

    list_1=[]
    list_2=[]

    for i in range(len(bought_data)):

        list= [bought_data[i]['symbol'], bought_data[i]['bought_stocks'], bought_data[i]['price'], bought_data[i]['timestamp']]

        list_1.append(list)

    for i in range(len(sold_data)):

        list= [sold_data[i]['symbol'], -1*(sold_data[i]['sold_stocks']), sold_data[i]['PRICE'], sold_data[i]['timestamp']]

        list_2.append(list)

    list_1.extend(list_2)

    sorted_list = sorted(list_1, key= lambda x:x[3])

    print(sorted_list)

    final_list =[]

    for i in range(len(sorted_list)):

        datetime = pd.to_datetime(int(sorted_list[i][3]), unit='s')

        b = {'symbol': sorted_list[i][0], 'shares': sorted_list[i][1], 'price': sorted_list[i][2], 'transacted':datetime}

        final_list.append(b)


    return render_template("history.html", final_list=final_list)


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        id_backup= int(rows[0]["id"])

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

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")

    else:
        symbol = request.form.get("symbol")
        shares = float(request.form.get("shares"))
        Lookup = lookup(symbol)
        dataTimeObj = datetime.now().timestamp()
        initial_stocks_purchase = db.execute("SELECT stocks ,name FROM purchase WHERE purchase_id= :id_backup AND symbol= :symbol", id_backup=session["user_id"], symbol=symbol.upper() )

        print(initial_stocks_purchase)


        if len(initial_stocks_purchase) == 0:

            initial_stocks_purchase=0

        else:

            initial_stocks_purchase= initial_stocks_purchase[-1]['stocks']

        if Lookup is None:
            return apology("The symbol does not exit or The input is blank", 403)
        elif not (shares.is_integer() and shares>= 1):
            return apology("The input is not a positive integer", 403)
        else:
            total= float(shares*Lookup["price"])
            cash= db.execute("SELECT cash FROM users WHERE id = :id_backup", id_backup= session["user_id"])
            print(total)
            print(cash)
            if total> cash[0]['cash']:
                return apology("You have no enough money", 403)
            else:

                db.execute("INSERT INTO purchase ( purchase_id ,name, price, symbol, bought_stocks,total,timestamp) VALUES ( :purchase_id,:name, :price, :symbol, :bought_stocks, :total, :timestamp)",
                purchase_id=session["user_id"],name=Lookup["name"],price=Lookup["price"],symbol=Lookup["symbol"],bought_stocks= shares, total= shares*Lookup["price"], timestamp=dataTimeObj)
                db.execute("UPDATE users SET cash = :update WHERE id = :id_backup", update=cash[0]['cash']-total, id_backup= int(session["user_id"]))
                db.execute("UPDATE purchase SET stocks = :update WHERE purchase_id = :id_backup", update=initial_stocks_purchase+shares, id_backup= int(session["user_id"]))
                return redirect("/")




@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method=="GET":
        return render_template("quote.html")

    else:
        symbol = request.form.get("symbol")
        Lookup = lookup(symbol)
        return render_template("quoted.html", Lookup=Lookup)



@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method=="GET":

        return render_template("register.html")

    else:
        username = request.form.get("username")
        password= str(request.form.get("password"))
        confirmation = request.form.get("confirmation")

        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=username)

        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        elif password != confirmation:

            return apology("The passwords do not match", 403)

        elif len(rows) != 0:
            return apology("Username already exists", 403)


        hash_1= generate_password_hash(password, method='pbkdf2:sha256',salt_length=8)
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash_1)", username= username, hash_1=hash_1)
        return redirect("/")





@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "GET":
        return render_template("sell.html")

    else:
        symbol = request.form.get("symbol")
        shares = float(request.form.get("shares"))
        Lookup = lookup(symbol)
        Lookup_1 = db.execute("SELECT :symbol,name FROM purchase WHERE purchase_id= :id_backup", symbol=symbol.upper(), id_backup=session["user_id"] )
        dataTimeObj = datetime.now().timestamp()
        initial_stocks_sold = db.execute("SELECT stocks ,name FROM sell WHERE sell_id= :id_backup AND symbol= :symbol", id_backup=session["user_id"], symbol=symbol.upper() )
        initial_stocks_purchase = db.execute("SELECT stocks ,name FROM purchase WHERE purchase_id= :id_backup AND symbol= :symbol", id_backup=session["user_id"], symbol=symbol.upper() )

        if len(initial_stocks_purchase) == 0:

            initial_stocks_purchase=0

        else:

            initial_stocks_purchase= initial_stocks_purchase[-1]['stocks']

        if len(initial_stocks_sold) == 0:

            initial_stocks_sold=0

        else:

            initial_stocks_sold= initial_stocks_sold[-1]['stocks']

        stocks_hold = initial_stocks_purchase - initial_stocks_sold
        if len(Lookup_1) ==0:
            return apology("The record does not exit or The input is blank", 403)
        elif not (shares.is_integer() and shares>= 1):
            return apology("The input is not a positive integer", 403)
        else:
            if shares> stocks_hold :
                return apology("You have not enough shares to sell", 403)
            else:
                total=shares*Lookup["price"]
                final_stocks=shares
                cash= db.execute("SELECT cash FROM users WHERE id = :id_backup", id_backup= session["user_id"])
                db.execute("INSERT INTO sell ( sell_id ,name, price, symbol, sold_stocks,total,timestamp) VALUES ( :sell_id,:name, :price, :symbol, :sold_stocks, :total, :timestamp)",
                sell_id=session["user_id"],name=Lookup["name"],price=Lookup["price"],symbol=Lookup["symbol"],sold_stocks= shares, total=total, timestamp=dataTimeObj)
                db.execute("UPDATE users SET cash = :update WHERE id = :id_backup", update=cash[0]['cash']+total, id_backup= int(session["user_id"]))
                db.execute("UPDATE sell SET stocks = :update WHERE sell_id = :id_backup", update=final_stocks+initial_stocks_sold, id_backup= int(session["user_id"]))

                return redirect("/")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
