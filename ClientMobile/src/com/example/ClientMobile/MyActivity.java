package com.example.ClientMobile;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.TextView;

public class MyActivity extends Activity {

    private TextView zoneDeTexte;
    private Button boutonConnection;
    private ImageButton boutonTetrominoI;
    private ImageButton boutonTetrominoT;
    private ImageButton boutonTetrominoO;
    private ImageButton boutonTetrominoJ;
    private ImageButton boutonTetrominoL;
    private ImageButton boutonTetrominoS;
    private ImageButton boutonTetrominoZ;

    private View.OnClickListener boutonConnectionListener;
    private View.OnClickListener boutonTetrominoIListener;
    private View.OnClickListener boutonTetrominoTListener;
    private View.OnClickListener boutonTetrominoOListener;
    private View.OnClickListener boutonTetrominoJListener;
    private View.OnClickListener boutonTetrominoLListener;
    private View.OnClickListener boutonTetrominoSListener;
    private View.OnClickListener boutonTetrominoZListener;

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
        boutonConnection = (Button) findViewById(R.id.boutonConnection);
        boutonTetrominoI = (ImageButton) findViewById(R.id.boutonTetrominoI);
        boutonTetrominoT = (ImageButton) findViewById(R.id.boutonTetrominoT);
        boutonTetrominoO = (ImageButton) findViewById(R.id.boutonTetrominoO);
        boutonTetrominoJ = (ImageButton) findViewById(R.id.boutonTetrominoJ);
        boutonTetrominoL = (ImageButton) findViewById(R.id.boutonTetrominoL);
        boutonTetrominoS = (ImageButton) findViewById(R.id.boutonTetrominoS);
        boutonTetrominoZ = (ImageButton) findViewById(R.id.boutonTetrominoZ);

        boutonConnectionListener = new View.OnClickListener()  {
            public void onClick(View v) {
                Connection();
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
    }

    private void SendTetrominoT() {
    }

    private void SendTetrominoO() {
    }

    private void SendTetrominoJ() {
    }

    private void SendTetrominoL() {
    }

    private void SendTetrominoS() {
    }

    private void SendTetrominoZ() {
    }

    private void Connection() {
    }
}
