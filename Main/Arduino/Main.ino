// Viral Science
// RFID
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define FOUT_PIN 11
#define JUIST_PIN 12
#define SS_PIN 10
#define RST_PIN 9
#define LED_GREEN A4 // define green LED pin
#define LED_RED A5   // define red LED
#define SERVO_PIN 3
#define BIEPER A3
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
Servo myServo;                    // define servo name

void setup()
{
  Serial.begin(9600);
  SPI.begin();               // Initiate  SPI bus
  mfrc522.PCD_Init();        // Initiate MFRC522
  myServo.attach(SERVO_PIN); // servo pin
  myServo.write(0);          // servo start position
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BIEPER, OUTPUT);
  pinMode(FOUT_PIN, OUTPUT);
  pinMode(JUIST_PIN,OUTPUT);
  analogWrite(LED_RED, 255); // set the red led on
  Serial.println("Put your card to the reader...");
  Serial.println();

  //set everything to low
  analogWrite(LED_GREEN, LOW);
  analogWrite(LED_RED, HIGH);
  digitalWrite(FOUT_PIN, LOW);
  digitalWrite(JUIST_PIN, LOW);
}

void loop()
{
  // Is er een nieuwe kaart?
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Is die kaart leesbaar
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  // Show UID on serial monitor
  Serial.print("UID tag :");
  String content = "";

  
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();

  //check als de token juist is
  if (content.substring(1) == "89 B4 18 B9") // change here the UID of the card/cards that you want to give access
  {
    authorized();
  }
  else
  {
    unauthorized();
  }
}

// turns on the green light and move the servo motor
void authorized()
{
  byte beginPos = 0, endPos = 90;

  Serial.println("Authorized access");
  Serial.println();

  analogWrite(LED_RED, 0);
  analogWrite(LED_GREEN, 255);

  digitalWrite(JUIST_PIN, HIGH);
  analogWrite(BIEPER, 255);
  delay(500);
  analogWrite(BIEPER, 0);
  digitalWrite(JUIST_PIN, LOW);

  myServo.write(endPos);
  delay(3000);
  myServo.write(beginPos);

  analogWrite(LED_GREEN, 0);
  analogWrite(LED_RED, 255);
}

// turns on the red light
void unauthorized()
{
  Serial.println("Access denied");
  for (byte i = 0; i < 3; i++)
  {
    analogWrite(BIEPER, 255);
    analogWrite(LED_RED, 0);
    delay(200);
    analogWrite(BIEPER, 0);
    analogWrite(LED_RED, 255);
    delay(200);
  }
  digitalWrite(FOUT_PIN, HIGH);
  delay(500);
  digitalWrite(FOUT_PIN, LOW)
}
