#define stepper PORTB

#define w_time 5
#define tam 4

int pinopir = 7;
int aci;
int steps[tam] = {0B0011, 0B0110, 0B1100, 0B1001};
int currentStep;
bool vdd = false;

void setup(){
  pinMode(pinopir, INPUT);
  
  Serial.begin(115200);
  for(int z=8; z<12; z++){
    pinMode(z, OUTPUT);
  }   
  currentStep = 0;
  rotate();
}  

void rotate(){
  stepper = steps[currentStep];
}

void increaseStep(){
  currentStep = (currentStep + 1) % tam;
}

void decreaseStep(){
  currentStep = (currentStep - 1 + tam) % tam;
}

void clockwise(int steps, int opt){
  int i;
  for(i=0;i<steps;i++){
    if(opt == 0){
      increaseStep();
    }
    else{
      decreaseStep();
    }
    rotate();
    delay(w_time);
  }
  
}
void loop() {
   aci = digitalRead(pinopir);

 
   Serial.println(aci);
   if(aci == 1 && vdd == false){
      Serial.println("abriu");
      clockwise(1800,0);
      vdd = true;
   }
   else if(aci == 0 && vdd == true){
      Serial.println("fechou");
      clockwise(1800,1);
      vdd = false;
   }
   delay(1000);
   
}
