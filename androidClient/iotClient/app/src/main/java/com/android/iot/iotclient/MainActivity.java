package com.android.iot.iotclient;

import android.os.SystemClock;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;

import android.os.AsyncTask;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {

    private Socket client = null;
    private boolean loop;
    private PrintWriter printwriter;
    private EditText messageField;
    private EditText ipField;
    private EditText portField;
    private Button sendButton;
    private Button stopButton;
    private String messsage;
    private String serverIP;
    private int port;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ipField= (EditText) findViewById(R.id.serverIP);
        portField= (EditText) findViewById(R.id.port);
        messageField= (EditText) findViewById(R.id.message);

        sendButton = (Button) findViewById(R.id.send);
        stopButton = (Button) findViewById(R.id.stop);

        // Button press event listener
        sendButton.setOnClickListener(new View.OnClickListener() {

            public void onClick(View v) {
                messsage = messageField.getText().toString(); // get the text message on the text field
                serverIP = ipField.getText().toString();
                port =  Integer.parseInt(portField.getText().toString());

                SendMessage sendMessageTask = new SendMessage();
                sendMessageTask.execute();
            }
        });
        stopButton.setOnClickListener(new View.OnClickListener() {

            public void onClick(View v) {
                messsage = "disconnect";
                loop = false;

            }
        });
    }
    private class SendMessage extends AsyncTask<Void, Void, Void> {

        @Override
        protected Void doInBackground(Void... params) {
            try {

                client = new Socket(serverIP, port); // connect to the server
                printwriter = new PrintWriter(client.getOutputStream(), true);
                loop = true;
                while(loop) {
                    printwriter.write(messsage); // write the message to output stream
                    SystemClock.sleep(1000);
                    printwriter.flush();
                }
                printwriter.write(messsage); // write the message to output stream
                printwriter.flush();
                printwriter.close();
                client.close(); // closing the connection

            } catch (UnknownHostException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return null;
        }

    }

}
