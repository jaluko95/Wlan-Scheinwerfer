#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
 
const char* SSID = "SSID";
const char* PSK = "PASSWORD";

String server = "http://Steuerung_1/sendData.php";

void setup() {
  pinMode(D0, OUTPUT);
  digitalWrite(D0, HIGH);
  pinMode(2, OUTPUT);
  WiFi.begin(SSID, PSK);
}
 
void loop() {
  if(WiFi.status() != WL_CONNECTED){
    WiFi.begin(SSID, PSK);
    
    digitalWrite(2, HIGH);   // Onboard LED blinkt falls nicht verbunden
    delay(1000);                       
    digitalWrite(2, LOW);    
    delay(1000);
    digitalWrite(2, HIGH);   
    delay(1000);                       
    digitalWrite(2, LOW);    
    delay(1000);
  }
  else{
    HTTPClient http;
    String path = server + "?id=2";  
    http.begin(path.c_str());

    int httpResponseCode = http.GET();
    String payload = "0";
    
    if (httpResponseCode > 0){
      payload = http.getString();

      //GPIOS schalten
      if(payload.toInt()==0){ //aus
        digitalWrite(D0, HIGH);
      }
      else if(payload.toInt()==1){ //an
        digitalWrite(D0, LOW);
      }
       
      else
      {
        
      }
    }
  }

  delay(2000); // Alle 2 Sekunden abfragen
}
