#/usr/bin/env python
# -*- coding:utf-8 -*-

from flask import Flask, session, request, escape, redirect, make_response, render_template, url_for
import os
from Queue import *
import socket
app = Flask(__name__)

# set the secret key.  keep this really secret:
#app.secret_key = 'A0Zr98j/3yX R~XHH!jmN]LWX/,?RT'
app.secret_key = os.urandom(24)

#################################################################
FIFOClientClassique = Queue()
ListClientClassique = []

class ClientClassique:
    def __init__(self, nom):
        self.nom = nom
        self.controleur = false
        self.fifoPieces = Queue()

##########

@app.errorhandler(401)
@app.errorhandler(403)
@app.errorhandler(404)
#@app.errorhandler(500)
def ma_page_erreur(error):
    if error :
        return "Erreur {}".format(error.code), error.code
    else :
        return "Une erreur est survenue", 500

@app.route('/')
def index():
    if 'username' in session:
        return 'Connecte comme %s' % escape(session['username'])
    return 'Vous n etes pas connecte'

########################

@app.route('/login_client_classique', methods=['POST'])
def login_client_classique():
    if request.method == 'POST':
        session['nom'] = request.form['nom']
        if 'nom' in session:
            #FIFOClientClassique.put(ClientClassique('username'))        #Ajoute le nouveau clientclassique dans la FIFO
            ListClientClassique.append(ClientClassique('nom'))
            return 'Connecte comme -->%s' % escape(session['nom'])
        else:
            return 'Vous n etes pas connecte'
        
    return 'Erreur : La requete doit etre de type POST'

@app.route('/obtenir_pieces')
def obtenir_pieces():
    if request.method == 'POST':
        if 'username' in session:
            for clientClassique in ListClientClassique:
                if clientClassique.nom == nom:
                    return clientClassique.fifoPieces.get()
        return 'Client Classique non trouve'    
    else:
        return 'Error'
        
@app.route('/logout_client_classique')
def logout_client_classique():
    # remove the username from the session if it's there
    session.pop('username', None)
    return redirect(url_for('index'))

######################

@app.route('/login_client_mobile', methods=['GET'])
def login_client_mobile():
    if request.method == 'GET':
        if len(ListClientClassique) > 0:
            for index, clientClassique in ListClientClassique:
                if clientClassique.controleur == false:
                    ListClientClassique[index].controleur = true
                    return clientClassique.name
            return 'Aucun'
        else:
            return 'Vide'
    else:
        return 'Erreur : La requete doit etre de type GET'
    
@app.route('/logout_client_mobile')
def logout_client_mobile():
    # remove the username from the session if it's there
    session.pop('username', None)
    return 'You are logged out'

@app.route('/envoie_piece')
def envoie_piece():
    if request.method == 'POST':
        piece = request.form['piece']
        nom = request.form['nom']
        for clientClassique in ListClientClassique:
            if clientClassique.nom == nom:
                clientClassique.fifoPieces.append(piece)
                return 'OK'
        return 'Client Classique non trouve'        
    else:
        return 'Erreur : La requete doit etre de type POST'

######################

if __name__ == '__main__':
    app.debug = True
    app.run()
