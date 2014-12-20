#/usr/bin/env python
# -*- coding:utf-8 -*-

from flask import Flask, request, make_response, render_template
app = Flask(__name__)

@app.route('/')
@app.route('/accueil')
def accueil():
    mots = ["Ceci", "est", "un", "test"]
    return render_template('accueil.html', titre="Bienvenue !", mots=mots)

@app.errorhandler(401)
@app.errorhandler(404)
@app.errorhandler(500)
def ma_page_erreur(error):
    #return "Page d'erreur {}".format(error.code), error.code
    return render_template('erreur.html', erreur=error.code)

if __name__ == '__main__':
    app.run()
