#include <WiFi.h>

const char* wifiName = "4DS817";
const char* wifiPass = "aUReaLw7";

IPAddress clientIp(192,168,1,106);
WiFiServer server;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  WiFi.begin(wifiName,wifiPass);
  while(WiFi.status() != WL_CONNECTED){
    WiFi.begin(wifiName,wifiPass);
    Serial.print(WiFi.status());
    Serial.println("  ...");
    delay(5000);
  }
  //WiFi.config(localIp,gateway,subnet,dns1,dns2);
  Serial.print("Wifi connected with IP: ");
  Serial.println(WiFi.localIP());
  server.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();
  if(client){
    if(client.connected()){
      Serial.println("Connected to client");
    }
    client.stop();
  }

}
