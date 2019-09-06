#include <SoftwareSerial.h>
#include <NewPing.h>

#define Trig_pin 5  //positivo
#define Echo_pin 4  //negativo
#define MaxDist 200

NewPing distSens(Trig_pin, Echo_pin, MaxDist);
SoftwareSerial esp8266(2, 3);
 
#define TIMEOUT 5000
String AP = "Neet"; //wifi
String PASS = "12341234"; //senha do wifi
int countTrueCommand;

int spare = 0;
boolean error;

typedef struct sensorData{
  int vol;
} sensorData;
 
void setup(){
  //Only for tests, LED will be replaced by the valve
  pinMode(12,OUTPUT);
  digitalWrite(12,HIGH);

  //Here code really begins
  Serial.begin(115200);
  esp8266.begin(115200);
  delay(2000);
  Serial.println("** Setting up ESP **\n");
  sendCommand("AT","OK");
  sendCommand("AT+CWMODE=1","OK");
  sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"","OK");

  Serial.println("\n\n\n** Starting Reading Sensors ** \n");
}
 
void loop() {
  error=0;
  sensorData data = readSensors();
  sendData(data);
  delay(20000);
 }

sensorData readSensors(){
  sensorData data;
  data.vol = distSens.ping();
  return data;
}

boolean sendCommand(String cmd, String ack){
  esp8266.println(cmd); // Send "AT+" command to module
  if (!echoFind(ack)) // timed out waiting for ack string
    return true; // ack blank or ack found
}

void sendData(sensorData data){ //struct sensorData
  String messageBody="";
  String API = "JILMZGJVTC54TSW3"; //chave
  String HOST = "api.thingspeak.com";
  String PORT = "80";
  String getData = "GET /update?api_key="+ API +"&field1" + "=" + data.vol;
  String lenData = String(getData.length()+4);

  Serial.println("Volume: " + String(data.vol));

  sendCommand("AT+CIPMUX=1","OK");
  sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,"OK");
  sendCommand("AT+CIPSEND=0," + lenData,">");
  esp8266.println(getData);
  delay(1500);
  countTrueCommand++;
  sendCommand("AT+CIPCLOSE=0","OK");
}

boolean echoFind(String keyword){
 byte current_char = 0;
 byte keyword_length = keyword.length();
 long deadline = millis() + TIMEOUT;
 while(millis() < deadline){
  if (esp8266.available()){
    char ch = esp8266.read();
    Serial.write(ch);
    if (ch == keyword[current_char])
      if (++current_char == keyword_length){
       Serial.println();
       return true;
    }
   }
  }
 return false; // Timed out
}
