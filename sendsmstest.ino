#include <SoftwareSerial.h>

SoftwareSerial SIM900A(10,11);
int fishSwitchState = HIGH;
int fishSwitchPin = 9;
int previous = LOW;
int state = HIGH;
bool smsSent = false;
long time; 
long debounce = 200;

void setup()
{
  //Initialize the GSM module
  pinMode(fishSwitchPin, INPUT);
  SIM900A.begin(115200);   // Setting the baud rate of GSM Module  
  Serial.begin(115200);    // Setting the baud rate of Serial Monitor (Arduino)
  Serial.println ("SIM900A Ready");
  delay(100);
  Serial.println ("Type s to send message or r to receive message");
}


void loop()
{
  //Check the pin for switch activation, send sms, if so.
  fishSwitchState = digitalRead(fishSwitchPin);
  if (fishSwitchState != previous && previous == LOW && millis() - 200 > debounce  )
  {
    Serial.println(fishSwitchState);
    time = millis();
    if (smsSent == false)
    {
      Serial.println("Sending sms");
      SendMessage();
      smsSent = true;
    }
   
      
  }
  previous = fishSwitchState;

 if (SIM900A.available()>0)
   Serial.write(SIM900A.read());
}


 void SendMessage()
{
  //Phone number and msg content
  SIM900A.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  SIM900A.println("AT+CMGS=\"+371xxxxxxxx\"\r"); //Mobile phone number to send message
  delay(1000);
  SIM900A.println("Fish on!"); // Messsage content
  delay(100);
  SIM900A.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
