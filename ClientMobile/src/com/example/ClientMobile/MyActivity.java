package com.example.ClientMobile;

import android.app.Activity;
import android.os.Bundle;
import android.os.StrictMode;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;
import org.apache.commons.logging.Log;
import org.apache.http.*;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.util.EntityUtils;

import java.io.*;
import java.net.HttpURLConnection;
import java.net.*;
import java.util.ArrayList;
import java.util.List;

public class MyActivity extends Activity {

    // Definie les formatges des requetes HTTP
    private static final String HTTP = "http://";
    private static final String REQUETE_CONNECTION = "/login_client_mobile";
    private static final String REQUETE_DECONNECTION = "/logout_client_mobile";
    private static final String REQUETE_ENVOYER_TETROMINO = "/envoie_piece";

    // Definition des caracteres envoye en qualite de Tetromino
    private static final String TETROMINOI = "I";
    private static final String TETROMINOT = "T";
    private static final String TETROMINOO = "O";
    private static final String TETROMINOJ = "J";
    private static final String TETROMINOL = "L";
    private static final String TETROMINOS = "S";
    private static final String TETROMINOZ = "Z";

    private Boolean connectionEtablie = false;  // Indique si une connection est etablie vers le serveur et a un client classique
    private String nomClientClassique = "";     // Contient le nom du client classique
    private String adresse = "";                // Contient l'adresse IP+Port vers le serveur

    // Declaration des buttons utiliser dans notre application
    private TextView zoneDeTexte;
    private Button boutonConnection;
    private ImageButton boutonTetrominoI;
    private ImageButton boutonTetrominoT;
    private ImageButton boutonTetrominoO;
    private ImageButton boutonTetrominoJ;
    private ImageButton boutonTetrominoL;
    private ImageButton boutonTetrominoS;
    private ImageButton boutonTetrominoZ;
    private EditText editTextAdresse;

    // Listener de tout les boutton permettant de receptionner les evenement sur ses derniers
    private View.OnClickListener boutonConnectionListener;
    private View.OnClickListener boutonTetrominoIListener;
    private View.OnClickListener boutonTetrominoTListener;
    private View.OnClickListener boutonTetrominoOListener;
    private View.OnClickListener boutonTetrominoJListener;
    private View.OnClickListener boutonTetrominoLListener;
    private View.OnClickListener boutonTetrominoSListener;
    private View.OnClickListener boutonTetrominoZListener;

    private boolean isConnected = false;

    /**
     * Called when the activity is first created.
     */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);     // Creation d'une instance de note application
        setContentView(R.layout.main);          // Et de sa vu

        InitializeApp();    // Initialisation de l'application
    }

    // Inialisation de l'application avec affectation des evenement au bouton
    private void InitializeApp() {

        zoneDeTexte = (TextView) findViewById(R.id.zoneDeTexte);
        editTextAdresse = (EditText) findViewById(R.id.editTextAdresse);
        boutonConnection = (Button) findViewById(R.id.boutonConnection);
        boutonTetrominoI = (ImageButton) findViewById(R.id.boutonTetrominoI);
        boutonTetrominoT = (ImageButton) findViewById(R.id.boutonTetrominoT);
        boutonTetrominoO = (ImageButton) findViewById(R.id.boutonTetrominoO);
        boutonTetrominoJ = (ImageButton) findViewById(R.id.boutonTetrominoJ);
        boutonTetrominoL = (ImageButton) findViewById(R.id.boutonTetrominoL);
        boutonTetrominoS = (ImageButton) findViewById(R.id.boutonTetrominoS);
        boutonTetrominoZ = (ImageButton) findViewById(R.id.boutonTetrominoZ);

        ActivationBoutton(false);


        // Permet la connection avec un client classique
        boutonConnectionListener = new View.OnClickListener()  {
            public void onClick(View v) {
                try {
                    if(connectionEtablie == false)  // Si une connection nest pas etablie
                        Connection();               // Une connection est effectue
                    else                            // Sinon
                        Deconnection();             // Une deconnection est effectue
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        };
        boutonConnection.setOnClickListener(boutonConnectionListener);

        // Permet l'envoie d'un tetromino en fonction du boutton selectionne

        boutonTetrominoIListener = new View.OnClickListener()  {
            public void onClick(View v) {
                try {
                    SendTetromino(TETROMINOI);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        };
        boutonTetrominoI.setOnClickListener(boutonTetrominoIListener);

        boutonTetrominoTListener = new View.OnClickListener()  {
            public void onClick(View v) {
                try {
                    SendTetromino(TETROMINOT);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        };
        boutonTetrominoT.setOnClickListener(boutonTetrominoTListener);

        boutonTetrominoOListener = new View.OnClickListener()  {
            public void onClick(View v) {
                try {
                    SendTetromino(TETROMINOO);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        };
        boutonTetrominoO.setOnClickListener(boutonTetrominoOListener);

        boutonTetrominoJListener = new View.OnClickListener()  {
            public void onClick(View v) {
                try {
                    SendTetromino(TETROMINOJ);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        };
        boutonTetrominoJ.setOnClickListener(boutonTetrominoJListener);

        boutonTetrominoLListener = new View.OnClickListener()  {
            public void onClick(View v) {
                try {
                    SendTetromino(TETROMINOL);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        };
        boutonTetrominoL.setOnClickListener(boutonTetrominoLListener);

        boutonTetrominoSListener = new View.OnClickListener()  {
            public void onClick(View v) {
                try {
                    SendTetromino(TETROMINOS);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        };
        boutonTetrominoS.setOnClickListener(boutonTetrominoSListener);

        boutonTetrominoZListener = new View.OnClickListener()  {
            public void onClick(View v) {
                try {
                    SendTetromino(TETROMINOZ);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        };
        boutonTetrominoZ.setOnClickListener(boutonTetrominoZListener);
    }

    // Permet l'envoie d'un tetromino part requete POST
    private void SendTetromino(String tetromino) throws Exception{

        String url = HTTP + adresse + REQUETE_ENVOYER_TETROMINO;    // Formatage de l'url

        // Iinitialisation du client http
        HttpClient httpclient = new DefaultHttpClient();
        HttpPost httppost = new HttpPost(url);

        try {
            // Formatage de la requete POST avec les donnees a envoyer
            List<NameValuePair> nameValuePairs = new ArrayList<NameValuePair>(2);
            nameValuePairs.add(new BasicNameValuePair("piece", tetromino));
            nameValuePairs.add(new BasicNameValuePair("nom_client", nomClientClassique));
            httppost.setEntity(new UrlEncodedFormEntity(nameValuePairs));

            // Execute HTTP Post Request
            HttpResponse response = httpclient.execute(httppost);
            StatusLine statusLine = response.getStatusLine();

            if(statusLine.getStatusCode() == HttpStatus.SC_OK){
                ByteArrayOutputStream out = new ByteArrayOutputStream();
                response.getEntity().writeTo(out);
                out.close();
                String responseString = out.toString();

                zoneDeTexte.setText(responseString);    // Affiche le tetromino envoyer
            } else{
                //Ferme la connection
                response.getEntity().getContent().close();
                throw new IOException(statusLine.getReasonPhrase());
            }
        } catch (ClientProtocolException e) {
            // TODO Auto-generated catch block
        } catch (IOException e) {
            // TODO Auto-generated catch block
        }
    }

    // Permet la connection du client mobile a un client classique par requete GET
    private void Connection() throws Exception {

        adresse = editTextAdresse.getText().toString();     // Recupere l'adresse du serveur demande

        String myurl = HTTP + adresse + REQUETE_CONNECTION;     // Formatage de l'url
        URI url = new URI(myurl);

        // Iinitialisation du client http
        HttpClient httpclient = new DefaultHttpClient();
        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
        StrictMode.setThreadPolicy(policy);
        HttpResponse response = httpclient.execute(new HttpGet(url));   // envoie de la requete
        StatusLine statusLine = response.getStatusLine();               // recupere la reponse

        if(statusLine.getStatusCode() == HttpStatus.SC_OK) {            // Si la requete est bine comprise
            ByteArrayOutputStream out = new ByteArrayOutputStream();
            response.getEntity().writeTo(out);
            out.close();
            String responseString = out.toString();


            zoneDeTexte.setText("ClientClassique : " + responseString);    // Affichage le resultat de la connection
            nomClientClassique = responseString;
            connectionEtablie = true;
            boutonConnection.setText("Deconnection");
            editTextAdresse.setEnabled(false);

            ActivationBoutton(true);

        } else if(statusLine.getStatusCode() == HttpStatus.SC_NO_CONTENT) {
            ByteArrayOutputStream out = new ByteArrayOutputStream();
            response.getEntity().writeTo(out);
            out.close();
            String responseString = out.toString();
            zoneDeTexte.setText(responseString);

        } else{
            //Ferme la connection
            response.getEntity().getContent().close();
            throw new IOException(statusLine.getReasonPhrase());
        }
    }

    // Permet la deconnection du client mobile a son client classique part requete POST
    private void Deconnection() {

        String url = HTTP + adresse + REQUETE_DECONNECTION;     //Formatage de l'url

        // Iinitialisation du client http
        HttpClient httpclient = new DefaultHttpClient();
        HttpPost httppost = new HttpPost(url);

        try {
            // Formatage de la requete POST avec les donnees a envoyer
            List<NameValuePair> nameValuePairs = new ArrayList<NameValuePair>(1);
            nameValuePairs.add(new BasicNameValuePair("nom_client", nomClientClassique));
            httppost.setEntity(new UrlEncodedFormEntity(nameValuePairs));

            // Execute HTTP Post Request
            HttpResponse response = httpclient.execute(httppost);
            StatusLine statusLine = response.getStatusLine();

            // Si la requete a bien etait recu est comprise
            if(statusLine.getStatusCode() == HttpStatus.SC_OK || statusLine.getStatusCode() == HttpStatus.SC_NO_CONTENT){
                ByteArrayOutputStream out = new ByteArrayOutputStream();
                response.getEntity().writeTo(out);
                out.close();
                String responseString = out.toString();

                zoneDeTexte.setText(responseString);        // Affiche la reponse

                // Netoyage et demande du formulaire de connection
                nomClientClassique = "";
                connectionEtablie = false;
                boutonConnection.setText("Connection");
                editTextAdresse.setEnabled(true);
                adresse = "";

                ActivationBoutton(false);

            } else{
                //Ferme la connection.
                response.getEntity().getContent().close();
                throw new IOException(statusLine.getReasonPhrase());
            }
        } catch (ClientProtocolException e) {
            // TODO Auto-generated catch block
        } catch (IOException e) {
            // TODO Auto-generated catch block
        }
    }

    // Permet l'activation ou non des boutons d'envoie des Tetrominos
    private void ActivationBoutton(boolean enable){

        boutonTetrominoI.setEnabled(enable);
        boutonTetrominoT.setEnabled(enable);
        boutonTetrominoO.setEnabled(enable);
        boutonTetrominoJ.setEnabled(enable);
        boutonTetrominoL.setEnabled(enable);
        boutonTetrominoS.setEnabled(enable);
        boutonTetrominoZ.setEnabled(enable);
    }


}
