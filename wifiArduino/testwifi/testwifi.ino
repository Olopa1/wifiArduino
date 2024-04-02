#include <WiFi.h>

#define LED 2
const char* wifiName = "TP-Link_CF67";
const char* wifiPass = "75051808";

IPAddress clientIp(192,168,1,106);
WiFiServer server(7070);

void setCharTab(char *tab,char setTo){
  unsigned int len = strLen(tab);
  for(unsigned int i = 0; i < len;i++){
    *(tab + i) = setTo;
  }
}

unsigned int strLen(const char* text){
  unsigned int sum = 0;
  for(int i = 0; *(text + i);i++){
    sum++;
  }
  return sum;
}

int strCmp(const char* text1,const char* text2){
  if(strLen(text1) != strLen(text2)) return -1;
  unsigned int len = strLen(text1);
  for(unsigned int i = 0; i < len;i++){
    if(*(text1 + i) != *(text2 + i)) return -1;
  }
  return 0;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED,OUTPUT);
  WiFi.begin(wifiName,wifiPass);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(WiFi.status());
    Serial.println("  ...");
    delay(10000);
  }
  Serial.print("Wifi connected with IP: ");
  Serial.println(WiFi.localIP());
  server.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  char text[256];
  strCmp(text,"on");
  WiFiClient client = server.available();
  while(client){
    if(client.connected()){
      Serial.println("Connected to client");
      delay(10000);
      if(client.available()!=0){
        Serial.print("Available ");
        Serial.print(client.available());
        Serial.println(" bytes to read");
        unsigned int index = 0;
        while(client.available()){
          text[index] = client.read();
          index++;
          Serial.print(text);
        }
        if(strCmp(text,"on") == 0){
          digitalWrite(LED,HIGH);
        }
        else if(strCmp(text,"off") == 0){
          digitalWrite(LED,LOW);  
        }
        else if(strCmp(text,"stop") == 0){
          client.stop();
        }
        setCharTab(text,0);
      }
    }
  }
}
