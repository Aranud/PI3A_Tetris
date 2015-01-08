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
increment = [0]

class ClientClassique:
    def __init__(self, nom):
        self.nom = nom
        self.controleur = False
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

@app.route('/login_client_classique', methods=['GET', 'POST'])
def login_client_classique():
    if request.method == 'POST':                
        session['nom'] = request.form['nom']
        if 'nom' in session:
            ListClientClassique.append(ClientClassique('nom'))
            return 'Connecte comme -->%s' % escape(session['nom'])
        else:
            return 'Vous n etes pas connecte'
    else:
        nom = 'client' + `increment[0]`
        increment[0] += 1
        #session['nom'] = nom
        #if nom in session:
        ListClientClassique.append(ClientClassique(nom))
        return nom
        #else:
        #    return 'Vous n etes pas connecte'

@app.route('/obtenir_pieces')
def obtenir_pieces():
    if request.method == 'POST':
        for clientClassique in ListClientClassique:
            if clientClassique.nom == nom:
                return clientClassique.fifoPieces.get(), 200
        return 'Client Classique inconnue', 204    
    else:
        return 'Erreur : La requete doit etre de type POST', 405
        
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
            for clientClassique in ListClientClassique:
                if clientClassique.controleur == False:
                    ListClientClassique[ListClientClassique.index(clientClassique)].controleur = True
                    return clientClassique.nom, 200
            return 'Tout les clients sont occupes', 204
        else:
            return 'Aucun client present', 204
    else:
        return 'Erreur : La requete doit etre de type GET', 405
    
@app.route('/logout_client_mobile', methods=['POST'])
def logout_client_mobile():
    if request.method == 'POST':
        nom_client = request.form['nom_client']
        for clientClassique in ListClientClassique:
            if clientClassique.nom == nom_client:
                ListClientClassique[ListClientClassique.index(clientClassique)].controleur = False
                return 'Deconnecte', 200
        return 'Client Classique inconnu, Deconnecte', 204
    else:
        return 'Erreur : La requete doit etre de type GET', 405

@app.route('/envoie_piece', methods=['POST'])
def envoie_piece():
    if request.method == 'POST':
        piece = request.form['piece']
        nom_client = request.form['nom_client']
        for clientClassique in ListClientClassique:
            if clientClassique.nom == nom_client:
                clientClassique.fifoPieces.put(piece)
                return 'OK Tetromino : ' + piece, 200
        return 'Client Classique non trouve', 400        
    else:
        return 'Erreur : La requete doit etre de type POST', 405

######################

if __name__ == '__main__':
    app.debug = True
    app.run()
