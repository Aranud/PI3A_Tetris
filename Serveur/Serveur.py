#/usr/bin/env python
# -*- coding:utf-8 -*-

import uuid, sys, os
from Queue import *

from twisted.python import log
from twisted.internet import reactor
from twisted.web.server import Site
from twisted.web.wsgi import WSGIResource

from flask import Flask, session, request, escape, redirect, make_response, render_template, url_for

from autobahn.twisted.websocket import WebSocketServerFactory, \
                                       WebSocketServerProtocol

from autobahn.twisted.resource import WebSocketResource, \
                                      WSGIRootResource, \
                                      HTTPChannelHixie76Aware

#################################################################

app = Flask(__name__)
# set the secret key.  keep this really secret:
app.secret_key = str(uuid.uuid4())
#app.secret_key = 'A0Zr98j/3yX R~XHH!jmN]LWX/,?RT'
#app.secret_key = os.urandom(24)                     # Generation d'une cle secret aleatoire (utilise pour les sessions)

#################################################################
#FIFOClientClassique = Queue()   # FIFO des clients classique (Futur evolution)
ListClientClassique = []         # Contient la liste des utlisateur
increment = [0]                 # Increment des clients classiques

class ClientClassique:          # Definir un client classique et si un client mobile lui est affecte
    def __init__(self, identifiant, client):
        self.identifiant = identifiant
        self.client = client        # contient la reference vers la web socket du client classique
        self.controleur = False     # indique si un controleur lui est affecte

## Protocole du Server pour les WebSocket 
class ServerProtocol(WebSocketServerProtocol):

   def onMessage(self, payload, isBinary):
      self.sendMessage(payload, isBinary)

   def onConnect(self, request):
      print("Client connecting: {}".format(request.peer))

   def onOpen(self):
      print("WebSocket connection open.")
      ListClientClassique.append(ClientClassique(increment[0], self))
      increment[0] += 1
      print(ListClientClassique[0].identifiant)

   def onClose(self, wasClean, code, reason):
      print("WebSocket connection closed: {}".format(reason))
      for clientClassique in ListClientClassique:     # Recherche le client classique
            if clientClassique.client == self:       # Si le client classique correspond
                ListClientClassique.remove(clientClassique) # Suppression de l'utilisateur de la liste

######################################################

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

@app.route('/login_client_mobile', methods=['GET']) # Permet les connection du client mobile
def login_client_mobile():
    if request.method == 'GET':                 # (double protection des method d'envoie)
        if len(ListClientClassique) > 0:   # Si il ny a pas de client classique aucun test nest effecute
            for clientClassique in ListClientClassique:   # Parcour les client classique
                if clientClassique.controleur == False:   # Si le client classique nest pas associe a un client mobile 
                    ListClientClassique[ListClientClassique.index(clientClassique)].controleur = True # On confirme une association
                    return "%d" % clientClassique.identifiant, 200        # Renvoie le nom du client
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
            if str(clientClassique.identifiant) == nom_client:       # Si le nom correspond
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
        print(nom_client)
        for clientClassique in ListClientClassique: # Recherche du client classique correspondant au nom
            if str(clientClassique.identifiant) == nom_client:   # Si le nom correspond
                clientClassique.client.sendMessage(piece.encode(encoding='UTF-8'), False)
                return 'OK Tetromino : ' + piece, 200   # Renvoie message succes
        return 'Client Classique non trouve', 400        # Le client classique na pas ete trouve
    else:
        return 'Erreur : La requete doit etre de type POST', 405    # Mauvaise methode de requete

######################

if __name__ == '__main__':
   if len(sys.argv) > 1 and sys.argv[1] == 'debug':
      log.startLogging(sys.stdout)
      debug = True
   else:
      debug = False
   debug = True

   app.debug = debug
   if debug:
      log.startLogging(sys.stdout)

   ## create a Twisted Web resource for our WebSocket server
   wsFactory = WebSocketServerFactory("ws://localhost:8080",
                                      debug = debug,
                                      debugCodePaths = debug)

   wsFactory.protocol = ServerProtocol
   wsFactory.setProtocolOptions(allowHixie76 = True) # needed if Hixie76 is to be supported

   wsResource = WebSocketResource(wsFactory)

   ## create a Twisted Web WSGI resource for our Flask server
   wsgiResource = WSGIResource(reactor, reactor.getThreadPool(), app)

   ## create a root resource serving everything via WSGI/Flask, but
   ## the path "/ws" served by our WebSocket stuff
   rootResource = WSGIRootResource(wsgiResource, {'ws': wsResource})

   
   ## create a Twisted Web Site and run everything
   site = Site(rootResource)
   site.protocol = HTTPChannelHixie76Aware # needed if Hixie76 is to be supported

   reactor.listenTCP(8080, site)
   reactor.run()                    # Lance l'application avec ecoute sur WebSocket

