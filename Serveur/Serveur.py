#/usr/bin/env python
# -*- coding:utf-8 -*-

from flask import Flask, session, request, escape, redirect, make_response, render_template, url_for
import os
app = Flask(__name__)

@app.route('/accueil')
def accueil():
    mots = ["Ceci", "est", "un", "test"]
    return render_template('accueil.html', titre="Bienvenue !", mots=mots)

@app.errorhandler(401)
@app.errorhandler(403)
@app.errorhandler(404)
#@app.errorhandler(500)
def ma_page_erreur(error):
    #return "Page d'erreur {}".format(error.code), error.code
    if error :
        return render_template('erreur.html', erreur=error.code)
    else :
        return "Une erreur est survenue", 500

@app.route('/')
def index():
    if 'username' in session:
        return 'Logged in as %s' % escape(session['username'])
    return 'You are not logged in'

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        session['username'] = request.form['username']
        return redirect(url_for('index'))
    return '''
        <form action="" method="post">
            <p><input type=text name=username>
            <p><input type=submit value=Login>
        </form>
    '''

@app.route('/logout')
def logout():
    # remove the username from the session if it's there
    session.pop('username', None)
    return redirect(url_for('index'))

# set the secret key.  keep this really secret:
#app.secret_key = 'A0Zr98j/3yX R~XHH!jmN]LWX/,?RT'
app.secret_key = os.urandom(24)

if __name__ == '__main__':
    app.debug = True
    app.run()
