#include<Servo.h>
Servo servo;

int ena = 9;
int enb = 10;
int in1 = 7;
int in2 = 8;
int in3 = 11;
int in4 = 12;
char val ;
int W,w,V,v,kec;
long duration,cm,meter;
int trig=6;
int echo=5;
int jarak[3];
int avoiding;
int pos=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(A5,OUTPUT);
  pinMode(A3,OUTPUT);
  Serial.begin(9600);
    servo.attach(3);
      pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
}

void loop() { 
  if( Serial.available() > 0 ) {
  val = Serial.read();
  Serial.println(val); 
  }
  rc();  
  if(avoiding == 1 ){
  avoid();
  }
}

void avoid(){
  for(pos=pos;pos<=85;pos++){
  servo.write(pos);
  delay(2);}
  
  ultra();
  jarak[2]=cm;
  
  if(cm>=10){
  lurus();
  }
  
  if(cm<=10){    
  for(pos=pos;pos<=180;pos++){
  servo.write(pos);
  delay(1);}
  ultra();
  jarak[1]=cm;   
  
  for(pos=pos;pos>=15;pos++){
  servo.write(pos);
  delay(1);}
  ultra();
  jarak[3]=cm;
  if(jarak[1]>=jarak[2]||jarak[3]>=jarak[2]){
  if(jarak[1]>jarak[3]){
    kiricepat();
    }
  if(jarak[3]>jarak[1]){
    kanancepat();
    }  
  }else{
    mundur();
  }
}
}
  
void rc(){
  if( val == 'X'){
    avoiding=1;
  }
  if( val == 'x'){
    avoiding=0;
  }
  if( val == 'F' ) {
    lurus();
  }
  if( val == 'B' ) {
    mundur();
  } 
  if( val == 'R' ) {
    kanancepat();
  }
  if( val == 'L' ) {
    
    kiricepat();
  }
  if( val == 'I' ) {
     kananselow();
  }
  if( val == 'G' ) {
     kiriselow();
  }
  if( val == 'H' ) {
     mundurserongkiri();
  }
  if( val == 'J' ) {
     mundurserongkanan();
  }
  if( val == 'S' ) {
     berhenti();
  }
  if( val == 'W' ) {
     analogWrite(A3,255);
  }
  if( val == 'w' ) {
     analogWrite(A3,0);
  }
  if( val == 'V' ) {
     analogWrite(A5,255);
  }
  if( val == 'v' ) {
     analogWrite(A5,0);
  }
  if( val == '1' ) {
     kec=25;
  }
  if( val == '2' ) {
     kec=50;
  }
  if( val == '3' ) {
     kec=75;
  }
  if( val == '4' ) {
     kec=100;
  }
  if( val == '5' ) {
     kec=125;
  }
  if( val == '6' ) {
     kec=150;
  }
  if( val == '7' ) {
     kec=175;
  }
  if( val == '8' ) {
     kec=200;
  }
  if( val == '9' ) {
     kec=225;
  }
  if( val == '10' ) {
     kec=250;
  }
}  
void ultra(){
  digitalWrite(trig,LOW);
  delayMicroseconds(5);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  duration=pulseIn(echo,HIGH);
  cm=(duration/2)/29.1;
  meter=(duration/2)/2910;
  
  Serial.print(meter);
  Serial.print("m, "); 
  Serial.print(cm);
  Serial.println("cm");
}  
void lurus(){
  analogWrite(ena, kec-14);
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);

  analogWrite(enb, kec);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
}

void mundur(){
  analogWrite(ena, kec-50);
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH);

  analogWrite(enb, kec);
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
}

void kanancepat(){
  analogWrite(ena, kec-14);
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);

  analogWrite(enb, kec);
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
}

void kiricepat(){
  analogWrite(ena, kec-14);
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH);

  analogWrite(enb, kec);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
}

void kananselow(){
  analogWrite(ena, kec-14);
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);

  analogWrite(enb, kec/3);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
}

void kiriselow(){
  analogWrite(ena, (kec/3)-14);
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);

  analogWrite(enb, kec);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
}

void mundurserongkanan(){
  analogWrite(ena, kec-14);
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH);

  analogWrite(enb, kec/3);
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
}

void mundurserongkiri(){
  analogWrite(ena, (kec/3)-14);
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH);

  analogWrite(enb, kec);
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
}

void berhenti(){
  analogWrite(ena, 0);
  digitalWrite(in1, LOW); digitalWrite(in2, LOW);

  analogWrite(enb, 0);
  digitalWrite(in3, LOW); digitalWrite(in4, LOW);
}

void brake(){
  analogWrite(ena, kec-14);
  digitalWrite(in1, HIGH); digitalWrite(in2, HIGH);

  analogWrite(enb, kec);
  digitalWrite(in3, HIGH); digitalWrite(in4, HIGH);
}

