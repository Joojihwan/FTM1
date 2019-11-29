#include "WiFiEsp.h"

#ifndef HAVE_HWSERIAL1

#endif

#include "SoftwareSerial.h"

SoftwareSerial Serial1(2,3); // RX, TX

int sensor = 4;
int motorA1 = 6;
int motorA2 = 7;
int cnt = 0;

char ssid[] = "bbb";            // your network SSID (name)
char pass[] = "32624269";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status
char server[] = "155.230.25.126";

WiFiEspClient client;

int connectServer(String s){ //155.230.25.126:11066/arduino?sqltype1=findvalue&table1=dduk&where1=dduk&value1=1&time=010105
  int fire = 0;
  
  if (client.connect(server, 11066)) {
  
      Serial.println("Connected to server");
      
      // Make a HTTP request
      client.println("GET /" + s + " HTTP/1.1");
      client.println("Host: 155.230.25.126");
      client.println("Connection: close");
      client.println();

      int i = 0;
      int j = 0;
      
      while (client.available()) { // 서버 응답중 y or n 찾는 반복문 ( 바뀐 응답 확인해야함 )
        String line = client.readStringUntil('\r');
        
        if(i == 4){ 

        Serial.println(line[1]);

        if(line[1] == 'y') fire = 1;
        }
        i++;
      }
      
      client.flush();
      client.stop();
      delay(500);
    }
  Serial.println(fire);
  
  return fire;
}


void openDoor(int m1, int m2,int n){
  analogWrite(m1,140);
  digitalWrite(m2,LOW);
}

void closeDoor(int m1,int m2,int n){
  digitalWrite(m1,LOW);
  digitalWrite(m2,1);
}

void holdo(int m1,int m2, int t){
  digitalWrite(m1,LOW);
  digitalWrite(m2,LOW);
  delay(t);
}

void setup() 
{
  pinMode(sensor,INPUT); 
  pinMode(motorA1,OUTPUT);
  pinMode(motorA2,OUTPUT);
  Serial.begin(9600);
  Serial1.begin(9600);
  WiFi.init(&Serial1);

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
}
 
void loop() 
{ 
  int var = digitalRead(sensor);
  char open = 'n';
  int yes;
  
  if(var == HIGH){
    Serial.println("detected"); //arduino?sqltype1=findvalue&table1=dduk&where1=dduk&value1=1&time=010105
    open = 'y';
    if(connectServer("arduino?sqltype1=findvalue_rtc&table1=seoul") == 1){
      open = 'f';
    }
    
    delay(50);
  }else if(var == LOW){
    Serial.println("gone");
    open = 'n';
    yes = connectServer("arduino?sqltype1=findvalue_rtc&table1=seoul");
    if(yes == 1){
      open = 'f';
    }
    
    delay(50);
  }

  if(open == 'y'){
    while(cnt<10){
      openDoor(motorA2,motorA1,cnt);
      cnt++; delay(25);
      Serial.println(cnt);
      }
      open = 'n';
  }else if(open == 'n'){
    while(cnt>0){
        closeDoor(motorA2,motorA1,cnt);
        cnt--; delay(25);
        Serial.println(cnt);
        //var = digitalRead(sensor); //닫으면서 중간에 확인요
        //if(var == HIGH) break;
      }
      open = 'y';
  }else if(open == 'f'){
    while(cnt<10){
      openDoor(motorA2,motorA1,cnt);
      cnt++; delay(28);// 다여는데 1초요
      Serial.println(cnt);
    }
    holdo(motorA2,motorA1,500);
    while(true){
      Serial.println("fire");
      delay(3000);
    }
  }
  
  holdo(motorA1,motorA2,500); // 닫다가 빠져나오면서 잠깐 홀드
  delay(100);

}
