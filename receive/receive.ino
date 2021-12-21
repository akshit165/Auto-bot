String incomingByte ;    

void setup() {

  Serial.begin(9600);
  pinMode(2,OUTPUT);   //left motors forward
  //pinMode(3,OUTPUT);   //left motors reverse
  pinMode(4,OUTPUT);   //right motors forward
  //pinMode(5,OUTPUT);   //right motors reverse

}
void loop() {


  if (Serial.available() > 0) {

  incomingByte = Serial.readStringUntil('\n');
    if (incomingByte == "left") {
      Serial.write("Going Left");
      digitalWrite(4,LOW);
      digitalWrite(2,HIGH);
      delay(2000);
      digitalWrite(2,LOW);
      delay(1000);
    }

    else if (incomingByte == "right") {
      Serial.write("Going Right");
      digitalWrite(2,LOW);
      digitalWrite(4,HIGH);
      delay(2000);
      digitalWrite(4,LOW);   
      delay(1000);  
    }

  }

}
