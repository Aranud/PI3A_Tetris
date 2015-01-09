#/usr/bin/env python
# -*- coding:utf-8 -*-

from flask import Flask, session, request, escape, redirect, make_response, render_template, url_for
import os
from Queue import *
import socket
app = Flask(__name__)

# set the secret key.  keep this really secret:
#app.secret_key = 'A0Zr98j/3yX R~XHH!jmN]LWX/,?RT'
#app.secret_key = os.urandom(24)                     # Generation d'une cle secret aleatoire (utilise pour les sessions)

#################################################################
#FIFOClientClassique = Queue()   # FIFO des clients classique (Futur evolution)
ListClientClassique = []         # Contient la liste des utlisateur
increment = [0]                 # Increment des clients classiques

class ClientClassique:          # Definir un client classique et si un client mobile lui est affecte
    def __init__(self, nom):
        self.nom = nom              # nom du client classique
        self.controleur = False     # indique si un controleur lui est affecte
        self.fifoPieces = Queue()   # Contient les pieces pour le client classique

##########

#Gere les erreur 400, 401, 403, 404, 405 500
@app.errorhandler(400)
@app.errorhandler(401)
@app.errorhandler(403)
@app.errorhandler(404)
@app.errorhandler(454)
@app.errorhandler(500)
def ma_page_erreur(error):
    if error :
        return "Erreur {}".format(error.code), error.code   # Renvoie l'erreur

########################

@app.route('/login_client_classique', methods=['GET'])  # Permet les connection du client classique
def login_client_classique():
#    if request.method == 'POST':                
#        session['nom'] = request.form['nom']
#        if 'nom' in session:
#            ListClientClassique.append(ClientClassique('nom'))
#            return 'Connecte comme -->%s' % escape(session['nom'])
#        else:
#            return 'Vous n etes pas connecte'
    if request.method == 'GET':                             # (double protection des method d'envoie)
        nom = 'client' + `increment[0]`                     # Creation d'un nom d'utilisateur
        increment[0] += 1                                   # Incremente le compteur des clients classique s
        ListClientClassique.append(ClientClassique(nom))    # Ajout du nouveau client a la liste des client classique
        return nom, 200                                     # Renvoie le nom de l'utilisateur
    else:
        return 'Erreur : La requete doit etre de type GET', 405 # Mauvaise methode de requete (double protection)

@app.route('/logout_client_classique', methods=['POST'])    # Permet les deconnection du client classique

def logout_client_classique():
    if request.method == 'POST':                        # (double protection des method d'envoie)
        nom_client = request.form['nom_client']         # Recupere le nom de l'utilisateur
        for clientClassique in ListClientClassique:     # Recherche le client classique
            if clientClassique.nom == nom_client:       # Si le client classique correspond
                ListClientClassique.remove(clientClassique) # Suppression de l'utilisateur de la liste
                return 'Deconnecte', 200                                  # Renvoie la confirmation de la deconnection
        return 'Client Classique inconnu, Deconnecte', 200       # Le client est deja deconnecte ou est inexistant
    else:
        return 'Erreur : La requete doit etre de type GET', 405 # Mauvaise methode de requete

@app.route('/obtenir_pieces', methods=['POST']) # Permet au client classique de recupere les Tetromino
def obtenir_pieces():
    if request.method == 'POST':                    # (double protection des method d'envoie)
        for clientClassique in ListClientClassique: # Recherche le client classique
            if clientClassique.nom == request.form['nom_client']: # Si le client classique correspond
                if clientClassique.fifoPieces.empty() == False:  # Si la liste n'est pas vide
                    return clientClassique.fifoPieces.get(), 200 # Renvoie la pieces la plus anciennes
                else:
                    return "", 200   # Aucune piece disponible pour le moment
        return 'Client Classique inconnue', 204      # Le nom envoyer nest pas reconnue
    else:
        return 'Erreur : La requete doit etre de type POST', 405 # Mauvaise methode de requete

######################

@app.route('/login_client_mobile', methods=['GET']) # Permet les connection du client mobile
def login_client_mobile():
    if request.method == 'GET':                 # (double protection des method d'envoie)
        if len(ListClientClassique) > 0:   # Si il ny a pas de client classique aucun test nest effecute
            for clientClassique in ListClientClassique:   # Parcour les client classique
                if clientClassique.controleur == False:   # Si le client classique nest pas associe a un client mobile 
                    ListClientClassique[ListClientClassique.index(clientClassique)].controleur = True # On confirme une association
                    return clientClassique.nom, 200        # Renvoie le nom du client
            return 'Tout les clients sont occupes', 204     # Il n'y a pas de client disponible
        else:
            return 'Aucun client present', 204    # Il n'y a pas de client connecte
    else:
        return 'Erreur : La requete doit etre de type GET', 405 # Mauvaise methode de requete
    
@app.route('/logout_client_mobile', methods=['POST'])   # Permet les deconnection du client mobile
def logout_client_mobile():
    if request.method == 'POST':                # (double protection des method d'envoie)
        nom_client = request.form['nom_client']         # Recupere le nom du client classique
        for clientClassique in ListClientClassique:     # Recherche le client classique
            if clientClassique.nom == nom_client:       # Si le nom correspond
                ListClientClassique[ListClientClassique.index(clientClassique)].controleur = False  # Indique que le client classique na plus de client mobile associe
                return 'Deconnecte', 200                  # Renvoie la confirmation de la deconnection
        return 'Client Classique inconnu, Deconnecte', 200  # Le client est deja deconnecte ou est inexistant
    else:
        return 'Erreur : La requete doit etre de type GET', 405 # Mauvaise methode de requete

@app.route('/envoie_piece', methods=['POST'])   # Permet au client mobile d'envoyer les Tetromino
def envoie_piece():
    if request.method == 'POST':                    # Si il s'agit bien d'une requete POST
        piece = request.form['piece']               # Recupere le Tetromino envoye
        nom_client = request.form['nom_client']     # Recupere le nom du client auquel l'on souhaite fournir le Tetromino
        for clientClassique in ListClientClassique: # Recherche du client classique correspondant au nom
            if clientClassique.nom == nom_client:   # Si le nom correspond
                clientClassique.fifoPieces.put(piece)   # Ajoute le tetromino a la liste de pieces du client classique
                return 'OK Tetromino : ' + piece, 200   # Renvoie message succes
        return 'Client Classique non trouve', 400        # Le client classique na pas ete trouve
    else:
        return 'Erreur : La requete doit etre de type POST', 405    # Mauvaise methode de requete

######################

if __name__ == '__main__':
    app.debug = True        # Lance l'application en mode debug
    app.run()               # Permet l'execution de l'application
