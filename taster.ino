#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
 
const char* SSID = "SSID";
const char* PSK = "PASSWORD";

String server = "http://192.168.2.109/";
String path_getSpot1 = server + "getData.php?id=1";
String path_getSpot2 = server + "getData.php?id=2";
String path_setSpot = server + "setData.php";


int stateSpot1 = 0; // 0=off, 1=on
int stateSpot2 = 0;

int ledSpot1 = 5; //LED zur signalisierung des eingeschalteten Zustandes des Scheinwerfers Id = 1
int ledSpot2 = 4; //LED zur signalisierung des eingeschalteten Zustandes des Scheinwerfers Id = 2
int tasterSpot1 = 16; //Taster für Scheinwerfer Id = 1
int tasterSpot2 = 18; //Taster für Scheinwerfer Id = 2

long debounceDelay = 50; //

// the setup function runs once when you press reset or power the board
void setup() {
  WiFi.begin(SSID, PSK);
  
  // initialize pins
  pinMode(tasterSpot1, INPUT_PULLDOWN); //integrierten pulldown-widerstand schalten
  pinMode(tasterSpot2, INPUT_PULLDOWN); //
  pinMode(ledSpot1, OUTPUT); //
  pinMode(ledSpot2, OUTPUT); //
  digitalWrite(ledSpot1, LOW);
  digitalWrite(ledSpot2, LOW);

  attachInterrupt(tasterSpot1, tasterSpot1_pressed(), RISING)
  attachInterrupt(tasterSpot2, tasterSpot2_pressed(), RISING)
}

// the loop function runs over and over again forever
void loop() {
  if(WiFi.status() != WL_CONNECTED){
    WiFi.begin(SSID, PSK);
  }
  else{
    HTTPClient http;
    
    //Status LED1 abfragen
    http.begin(path_getSpot1.c_str());
    int httpResponseCode = http.GET();
    String payload = "0";

    if (httpResponseCode > 0){
      payload = http.getString();
      stateSpot1 = payload.toInt();
      digitalWrite(ledSpot1, stateSpot1);
    }
    else{
      break;
    }
    http.end()
    
    //Status LED2 abfragen
    http.begin(pathSpot2.c_str());
    int httpResponseCode = http.GET();
    String payload = "0";

    if (httpResponseCode > 0){
      payload = http.getString();
      stateLED2 = payload.toInt();
      digitalWrite(ledSpot2, stateSpot2);
    }
    else{
      break;
    }
    http.end();
}

boolean debounce(int pin){
  delay(debounceDelay);
  boolean state = digitalRead(pin);
  //warte 10ms und gib dann den status des tasters aus
  return state;
}

void setState(int id, int state){
  HTTPClient http;
  http.begin(path_setSpot.c_str());
  
  String httpRequestData = "id=" + id + "&status=" + state //Request vorbereiten
  int httpResponseCode = http.POST(httpRequestData); //Request ausfuehrend

  http.end()
}
void tasterSpot1_pressed() {
  if (debounce(tasterSpot1) == true){
    
    if (stateSpot1 == 0){ //wenn der Scheinwerfer aus ist, dann einschalten
      setState(1, 1)
    }
    else if (stateSpot1 == 1){ //wenn der Scheinwerfer an ist, dann ausschalten
      setState(1, 0)
    }
  }
}

void tasterSpot2_pressed() {
  if (debounce(tasterSpot2) == true){
    
    if (stateSpot2 == 0){ //wenn der Scheinwerfer aus ist, dann einschalten
      setState(2, 1)
    }
    else if (stateSpot2 == 1){ //wenn der Scheinwerfer an ist, dann ausschalten
      setState(2, 0)
    }
  }
  
}
