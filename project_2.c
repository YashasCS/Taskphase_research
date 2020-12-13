const int buttonPin=7;
int pushCount =0;
int state=0;
void setup()
{
  pinMode(buttonPin,INPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(11,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  state=digitalRead(buttonPin);
  if(state==HIGH)
  {
    pushCount++;
    delay(100);
    Serial.print(pushCount);
  }
 if(pushCount ==1)
    {digitalWrite(6,LOW);
     digitalWrite(5,LOW);
     digitalWrite(4,LOW);
          delay(1000);
     
     digitalWrite(6,LOW);
     digitalWrite(5,LOW);
     digitalWrite(4,HIGH);
          delay(1000);

     
     digitalWrite(6,LOW);
     digitalWrite(5,HIGH);
     digitalWrite(4,LOW);
          delay(1000);

     
     digitalWrite(6,LOW);
     digitalWrite(5,HIGH);
     digitalWrite(4,HIGH);
          delay(1000);

     
     digitalWrite(6,HIGH);
     digitalWrite(5,LOW);
     digitalWrite(4,LOW);
          delay(1000);

     
     digitalWrite(6,HIGH);
     digitalWrite(5,LOW);
     digitalWrite(4,HIGH);
          delay(1000);

     
     digitalWrite(6,HIGH);
     digitalWrite(5,HIGH);
     digitalWrite(4,LOW);
          delay(1000);

     
     digitalWrite(6,HIGH);
     digitalWrite(5,HIGH);
     digitalWrite(4,HIGH);
          delay(1000);
    }     
      
 if(pushCount ==2)
 {
   for(int i =0;i<255; i=i+10)
   {
     analogWrite(11,i);
     delay(100);
   }
   for(int j=255; j>0; j=j-10)
   {
     analogWrite(11,j);
     delay(100);
   }
 }
    
    if(pushCount ==3)
  {
   
      analogWrite(11, 255);
      delay(1000);
      analogWrite(11,0);
      delay(1000);
    
  }
    
}

