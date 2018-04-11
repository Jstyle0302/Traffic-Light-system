int LED_R=13;
int LED_Y=12;
int LED_G=11;
int status = 0;  //0 for green, 1 for yellow, others for red
// define the LED digit patters, from 0 - 9
// 1 = LED on, 0 = LED off, in this order:
// Arduino pin: 2,3,4,5,6,7,8 (Mapping a,b,c,d,e,f,g of Seven-Segment LED)
byte seven_seg_digits[10][7] = { { 1,1,1,1,1,1,0 },  // = 0
                                 { 0,1,1,0,0,0,0 },  // = 1
                                 { 1,1,0,1,1,0,1 },  // = 2
                                 { 1,1,1,1,0,0,1 },  // = 3
                                 { 0,1,1,0,0,1,1 },  // = 4
                                 { 1,0,1,1,0,1,1 },  // = 5
                                 { 1,0,1,1,1,1,1 },  // = 6
                                 { 1,1,1,0,0,0,0 },  // = 7
                                 { 1,1,1,1,1,1,1 },  // = 8
                                 { 1,1,1,0,0,1,1 }   // = 9  
                                 };

void setup() {
  Serial.begin(9600);
  pinMode(LED_R,OUTPUT);
  pinMode(LED_Y,OUTPUT);
  pinMode(LED_G,OUTPUT);
  
  pinMode(2, OUTPUT); 
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(9, 0);  // 關閉小數點
  }
void sevenSegWrite(byte digit) {
  byte pin = 2;
  for (byte seg = 0; seg < 7; ++seg) {
    digitalWrite(pin, seven_seg_digits[digit][seg]);
    ++pin;
  }
}
void loop() {
  if (Serial.available() > 0) { 
    if(status ==0){
        if (Serial.read()=='L') {
            status = 0;
          }  
        else if(Serial.read()=='H') {
          status = 1;
        }
        else{
          status = 0;
          }
      }
    else if(status ==1){
        status = 2;
      }
    else{
        status = 0;
      }  
    if (status == 0){
      digitalWrite(LED_G, HIGH);
      digitalWrite(LED_R, LOW);
      digitalWrite(LED_Y, LOW);
      delay(9000);
      }
    else if(status == 1){
      delay(1500);
      digitalWrite(LED_G, LOW); 
      digitalWrite(LED_Y,HIGH);
      digitalWrite(LED_R, LOW);
      delay(1500);
      }
    else{
      digitalWrite(LED_G, LOW); 
      digitalWrite(LED_Y, LOW);
      digitalWrite(LED_R, HIGH);
      for (byte digit = 10; digit > 0; --digit) {
        delay(1000);
        sevenSegWrite(digit - 1);
        }
      }
    }
  delay(1);     
  }
