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

    private static final String HTTP = "http://";
    private static final String REQUETE_CONNECTION = "/login_client_mobile";
    private static final String REQUETE_DECONNECTION = "/logout_client_mobile";
    private static final String REQUETE_ENVOYER_TETROMINO = "/envoie_piece";

    private static final String TETROMINOI = "I";
    private static final String TETROMINOT = "T";
    private static final String TETROMINOO = "O";
    private static final String TETROMINOJ = "J";
    private static final String TETROMINOL = "L";
    private static final String TETROMINOS = "S";
    private static final String TETROMINOZ = "Z";

    private Boolean connectionEtablie = false;
    private String nomClientClassique = "";
    private String adresse = "";

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
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        InitializeApp();
    }

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

        boutonConnectionListener = new View.OnClickListener()  {
            public void onClick(View v) {
                try {
                    if(connectionEtablie == false)
                        Connection();
                    else
                        Deconnection();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        };
        boutonConnection.setOnClickListener(boutonConnectionListener);

        boutonTetrominoIListener = new View.OnClickListener()  {
            public void onClick(View v) {
                SendTetrominoI();
            }
        };
        boutonTetrominoI.setOnClickListener(boutonTetrominoIListener);

        boutonTetrominoTListener = new View.OnClickListener()  {
            public void onClick(View v) {
                SendTetrominoT();
            }
        };
        boutonTetrominoT.setOnClickListener(boutonTetrominoTListener);

        boutonTetrominoOListener = new View.OnClickListener()  {
            public void onClick(View v) {
                SendTetrominoO();
            }
        };
        boutonTetrominoO.setOnClickListener(boutonTetrominoOListener);

        boutonTetrominoJListener = new View.OnClickListener()  {
            public void onClick(View v) {
                SendTetrominoJ();
            }
        };
        boutonTetrominoJ.setOnClickListener(boutonTetrominoJListener);

        boutonTetrominoLListener = new View.OnClickListener()  {
            public void onClick(View v) {
                SendTetrominoL();
            }
        };
        boutonTetrominoL.setOnClickListener(boutonTetrominoLListener);

        boutonTetrominoSListener = new View.OnClickListener()  {
            public void onClick(View v) {
                SendTetrominoS();
            }
        };
        boutonTetrominoS.setOnClickListener(boutonTetrominoSListener);

        boutonTetrominoZListener = new View.OnClickListener()  {
            public void onClick(View v) {
                SendTetrominoZ();
            }
        };
        boutonTetrominoZ.setOnClickListener(boutonTetrominoZListener);
    }

    private void SendTetrominoI() {
        try {
            SendTetromino(TETROMINOI);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void SendTetrominoT() {
        try {
            SendTetromino(TETROMINOT);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void SendTetrominoO() {
        try {
            SendTetromino(TETROMINOO);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void SendTetrominoJ() {
        try {
            SendTetromino(TETROMINOJ);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void SendTetrominoL() {
        try {
            SendTetromino(TETROMINOL);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void SendTetrominoS() {
        try {
            SendTetromino(TETROMINOS);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void SendTetrominoZ() {
        try {
            SendTetromino(TETROMINOZ);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void SendTetromino(String tetromino) throws Exception{

        String url = HTTP + adresse + REQUETE_ENVOYER_TETROMINO;

        HttpClient httpclient = new DefaultHttpClient();
        HttpPost httppost = new HttpPost(url);

        try {
            // Add your data
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

                zoneDeTexte.setText(responseString);
            } else{
                //Closes the connection.
                response.getEntity().getContent().close();
                throw new IOException(statusLine.getReasonPhrase());
            }
        } catch (ClientProtocolException e) {
            // TODO Auto-generated catch block
        } catch (IOException e) {
            // TODO Auto-generated catch block
        }
    }

    private void Connection() throws Exception {

        adresse = editTextAdresse.getText().toString();

        String myurl = HTTP + adresse + REQUETE_CONNECTION;
        URI url = new URI(myurl);

        HttpClient httpclient = new DefaultHttpClient();
        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
        StrictMode.setThreadPolicy(policy);
        HttpResponse response = httpclient.execute(new HttpGet(url));
        StatusLine statusLine = response.getStatusLine();

        if(statusLine.getStatusCode() == HttpStatus.SC_OK) {
            ByteArrayOutputStream out = new ByteArrayOutputStream();
            response.getEntity().writeTo(out);
            out.close();
            String responseString = out.toString();

            zoneDeTexte.setText(responseString);
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
            //Closes the connection.
            response.getEntity().getContent().close();
            throw new IOException(statusLine.getReasonPhrase());
        }
    }

    private void Deconnection() {

        String url = HTTP + adresse + REQUETE_DECONNECTION;

        HttpClient httpclient = new DefaultHttpClient();
        HttpPost httppost = new HttpPost(url);

        try {
            // Add your data
            List<NameValuePair> nameValuePairs = new ArrayList<NameValuePair>(1);
            nameValuePairs.add(new BasicNameValuePair("nom_client", nomClientClassique));
            httppost.setEntity(new UrlEncodedFormEntity(nameValuePairs));

            // Execute HTTP Post Request
            HttpResponse response = httpclient.execute(httppost);
            StatusLine statusLine = response.getStatusLine();

            if(statusLine.getStatusCode() == HttpStatus.SC_OK || statusLine.getStatusCode() == HttpStatus.SC_NO_CONTENT){
                ByteArrayOutputStream out = new ByteArrayOutputStream();
                response.getEntity().writeTo(out);
                out.close();
                String responseString = out.toString();

                zoneDeTexte.setText(responseString);
                nomClientClassique = "";
                connectionEtablie = false;
                boutonConnection.setText("Connection");
                editTextAdresse.setEnabled(true);
                adresse = "";

                ActivationBoutton(false);

            } else{
                //Closes the connection.
                response.getEntity().getContent().close();
                throw new IOException(statusLine.getReasonPhrase());
            }
        } catch (ClientProtocolException e) {
            // TODO Auto-generated catch block
        } catch (IOException e) {
            // TODO Auto-generated catch block
        }
    }

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
