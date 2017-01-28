
#include <Bridge.h>
#include <YunClient.h>

#define PORT 6666

// Define our client object
YunClient client;
bool Connected;

// Make the client connect to the desired server and port
IPAddress addr(192,168,201,207);
  
// Or define it using a single unsigned 32 bit value
// IPAddress addr(0xc0a8sab9); // same as 192.168.42.185
  
// Or define it using a byte array
// const uint8 addrBytes = {192, 168, 42, 185};
// IPAddress addr(addrBytes);

// Or connect by a server name and port.
// Note that the Yun doesn't support mDNS by default, so "Yun.local" won't work
// client.connect("ServerName.com", PORT);


void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  // Bridge startup
  Bridge.begin();
  
  Serial.begin(115200);
  while (!Serial)
  {
    digitalWrite(13, HIGH);
    delay(125);
    digitalWrite(13, LOW);
    delay(125);
  }  
  Serial.println("Client connecting on port 6666");
  Connected = false;
}

void loop()
{
  // Is a connection currently active?
  if (!Connected)
  {
    // Not currently connected, try to establish a connection
    client.connect(addr, PORT);
    if (client.connected())
    {
      Serial.println("Connected to the server.");

      // Send something to the client
      client.println("Hello Server!");
       
      // Remember that there is a connection
      Connected = true;
    }
    else
    {
      // The connection attempt has failed.
      Serial.println("Could not connect to the server.");  
    
      // Give some time before trying again.
      // A real program needs to be more inteligent here.
      delay(5000);
    }
  }
  
  // Is a connection currently active?
  // Not an ELSE clause from the above IF, because a
  // new connection might have just been established.
  if (Connected)
  {
    // We think we are connected. Is that true?
    if (client.connected())
    {
      // Yes, we really are connected.
      // Send something to the client
      client.println("Rahul");
      
      // Delay just to prevent too much data streaming
      // to the server, a real application will need to
      // be more intelligent here.
      delay(1000);
      
      // Read all incoming bytes available from the server and print them
      while (client.available())
      {
        char c = client.read();
        Serial.print(c);
      }
      Serial.flush();
    }
    else
    {
       // We think we are connected, but we aren't.
       // The connection must've just closed on us.
       Serial.println("Server connection closed!");
       
       // Clean up the client connection
       client.stop();
       
       // Track that we are no longer connected.
       // This will try to establish a connection the next time around.
       Connected = false;
    }
  }
}
