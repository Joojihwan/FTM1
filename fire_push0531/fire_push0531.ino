#include "WiFiEsp.h"



// Emulate Serial1 on pins 6/7 if not present

#ifndef HAVE_HWSERIAL1

#endif

#include "SoftwareSerial.h"

SoftwareSerial Serial1(2, 3); // RX, TX

int tmp = 0; // Aanlog 0번


char ssid[] = "SSID Name";            // your network SSID (name)

char pass[] = "Password";        // your network password

int status = WL_IDLE_STATUS;     // the Wifi radio's status



char server[] = "Server IP";



// Initialize the Ethernet client object

WiFiEspClient client;



void setup()

{

  // initialize serial for debugging

  Serial.begin(9600);

  // initialize serial for ESP module

  Serial1.begin(9600);

  // initialize ESP module

  WiFi.init(&Serial1);



  // check for the presence of the shield

  if (WiFi.status() == WL_NO_SHIELD) {

    Serial.println("WiFi shield not present");

    // don't continue

    while (true);

  }



  // attempt to connect to WiFi network

  while ( status != WL_CONNECTED) {

    Serial.print("Attempting to connect to WPA SSID: ");

    Serial.println(ssid);

    // Connect to WPA/WPA2 network

    status = WiFi.begin(ssid, pass);

  }



  // you're connected now, so print out the data

  Serial.println("You're connected to the network");


  Serial.println();

  Serial.println("Starting connection to server...");

  // if you get a connection, report back via serial


}



void loop()

{
  int reading = analogRead(tmp);

  float voltage = reading *5.0 / 1024.0; // mv로 들어오는 입력을
  float temperature = voltage *100; // 온도로 변환하는 과정

  
  Serial.println(temperature);
  if(temperature >=25){ // '25' 이상 감지 시 서버에 연결, GET 함수 보냄
    
    if (client.connect(server, 11066)) {
  
      Serial.println("Connected to server");
  
      // Make a HTTP request
  
      client.println("GET /fire/1 HTTP/1.1");
  
      client.println("Host:" + server);
  
      client.println("Connection: close");
  
      client.println();

      client.flush(); // ** 꼭필요
      client.stop(); // client와 연결을 끊지 않으면 여러가지 문제 
      delay(10000);
      while(true);
    }
  }
  delay(1000);
}
