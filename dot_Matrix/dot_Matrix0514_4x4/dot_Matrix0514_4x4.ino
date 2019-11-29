void setup() {
  // put your setup code here, to run once:
  pinMode(2,OUTPUT); //c1
  pinMode(3,OUTPUT); //r3
  pinMode(4,OUTPUT); //c2
  pinMode(5,OUTPUT); //r1
  pinMode(6,OUTPUT); //r4
  pinMode(7,OUTPUT); //c3
  pinMode(8,OUTPUT); //r2
  pinMode(9,OUTPUT); //c4
}

void loop() {
  // put your main code here, to run repeatedly:
  int direction = 0;
  int i;
  int t=0;

  while(direction<6){
  
  if(direction  == 0){ // None
    for(i=0;i<8;i++){
      digitalWrite(i+2,LOW);
    }
  }
  else if(direction == 2 || direction == 4){ // L,R 
    t=0;
    while(t<100){
    digitalWrite(5,HIGH);
    digitalWrite(8,HIGH);
    digitalWrite(3,HIGH);
    digitalWrite(6,HIGH);
    digitalWrite(2,HIGH);
    digitalWrite(9,HIGH);
    delay(5);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(2,LOW);
    digitalWrite(9,LOW);
    if(direction == 2) digitalWrite(8,LOW);
    else if(direction == 4) digitalWrite(3,LOW);
    delay(5);
    t++;
    }
        for(i=0;i<8;i++){
      digitalWrite(i+2,LOW);
    }
  }
  else if(direction == 1 || direction == 3){ //U,D
    t=0;
    while(t<100){
    digitalWrite(8,HIGH);
    digitalWrite(3,HIGH);
    delay(30);
    digitalWrite(5,HIGH);
    digitalWrite(8,LOW);
    digitalWrite(3,LOW);
    digitalWrite(6,HIGH);
    digitalWrite(2,HIGH);
    digitalWrite(9,HIGH);
    if(direction == 1) digitalWrite(7,HIGH);
    else if(direction == 3) digitalWrite(4,HIGH);
    delay(5);
    t++;
    }
        for(i=0;i<8;i++){
      digitalWrite(i+2,LOW);
    }
  }else if(direction == 5){ // X
    t=0;
    while(t<100){
    digitalWrite(8,HIGH);
    digitalWrite(3,HIGH);
    digitalWrite(2,HIGH);
    digitalWrite(9,HIGH);
    delay(100);
    digitalWrite(8,LOW);
    digitalWrite(3,LOW);
    digitalWrite(2,LOW);
    digitalWrite(9,LOW);
    digitalWrite(5,HIGH);
    digitalWrite(6,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(7,HIGH);
    delay(5);
    t++;
    }
        for(i=0;i<8;i++){
      digitalWrite(i+2,LOW);
    }
  }
  direction++;
  }
 
}
