#include <Adafruit_Fingerprint.h>

SoftwareSerial mySerial(2, 3);// Serial pins 2 and 3

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial); // Function to read and wirte Rx & Tx pins
#define RELAY_PIN       4
#define ACCESS_DELAY    3000 

void setup()
{
  pinMode(RELAY_PIN, OUTPUT);
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) 
  {

  } 
  else 
  {
    while (1) { delay(1); }
  }
  digitalWrite(RELAY_PIN, HIGH);  

}



void loop()

{

  if ( getFingerPrint() != -1)
  {
    digitalWrite(RELAY_PIN, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY_PIN, HIGH);   
  }  
  delay(90);            //delay before next scan.
}
// returns -1 if failed, otherwise returns ID #
int getFingerPrint() 
{
  int p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;
  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;
  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;// found a match!
  return finger.fingerID;
}
