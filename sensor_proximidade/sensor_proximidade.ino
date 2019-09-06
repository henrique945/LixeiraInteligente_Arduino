#include <NewPing.h>

#define Trig_pin 5  //positivo
#define Echo_pin 4  //negativo
#define MaxDist 200

NewPing distSens(Trig_pin, Echo_pin, MaxDist);

void setup(){
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode( 9, OUTPUT);
  pinMode( 8, OUTPUT);
  pinMode( 7, OUTPUT);
  
  Serial.begin(115200);
}

void loop(){
  delay(1000);
  int vol = distSens.ping();
  Serial.println(vol);
  
  if(vol > 1000)
    ledsPrinting(1);
  else if(vol >= 800 && vol <= 1000)
    ledsPrinting(2);
  else if(vol >= 600 && vol < 800)
    ledsPrinting(3);
  else if(vol >= 400 && vol < 600)
    ledsPrinting(4);
  else if(vol >= 200 && vol < 400)
    ledsPrinting(5);
  else
    ledsPrinting(0);
}
//SEQUENCIA DE PORTAS: 11 8 9 10 7

void ledsPrinting(int led){
  switch(led){
    case 1:
      digitalWrite( 7,LOW);
      digitalWrite( 8,LOW);
      digitalWrite( 9,LOW);
      digitalWrite(10,LOW);
      digitalWrite(11,HIGH);
      break;
     case 2:
      digitalWrite( 7, LOW);
      digitalWrite( 8, HIGH);
      digitalWrite( 9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
      break;
    case 3:
      digitalWrite( 7, LOW);
      digitalWrite( 8, HIGH);
      digitalWrite( 9, HIGH);
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
      break;
    case 4:
      digitalWrite( 7, LOW);
      digitalWrite( 8, HIGH);
      digitalWrite( 9, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
      break;
    case 5:
      digitalWrite( 7, HIGH);
      digitalWrite( 8, HIGH);
      digitalWrite( 9, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
      break;
    default:
      digitalWrite( 7, LOW);
      digitalWrite( 8, LOW);
      digitalWrite( 9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      break;
  }

/*  if(led >= 7 || led <= 11){
    int i;
    for(i=7; i<=led+6; i++)
      digitalWrite(i, HIGH); 
    for(i=leds+2; i<=11; i++
      digitalWrite(i, LOW);
  }
  else
    for(i=7; i<=11; i++)
      digitalWrite(i, LOW);*/
}



  
  
