// Viral Science
// RFID
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9
#define LED_GREEN A4               // define green LED pin
#define LED_RED A5                 // define red LED
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
Servo myServo;                    // define servo name

void setup()
{
  Serial.begin(9600); // Initiate a serial communication
  SPI.begin();        // Initiate  SPI bus
  mfrc522.PCD_Init(); // Initiate MFRC522
  myServo.attach(3);  // servo pin
  myServo.write(0);   // servo start position
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  analogWrite(LED_RED, 255); // set the red led on
  Serial.println("Put your card to the reader...");
  Serial.println();
}

void loop()
{
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  // Show UID on serial monitor
  Serial.print("UID tag :");
  String content = "";
  byte letter;

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

  if (content.substring(1) == "89 B4 18 B9") // change here the UID of the card/cards that you want to give access
  {
    authorized();
  }
  else
  {
    unauthorized();
  }

}

// turns on the green light and moves the servo motor
void authorized()
{
  int beginPos = 0, endPos = 90;

  Serial.println("Authorized access");
  Serial.println();

  analogWrite(LED_RED, 0);
  analogWrite(LED_GREEN, 255);

  myServo.write(endPos);
  delay(3000);
  myServo.write(beginPos);

  analogWrite(LED_GREEN, 0);
  analogWrite(LED_RED, 255);
}

//turns on the red light
void unauthorized()
{
  Serial.println("Access denied");
  analogWrite(LED_RED, 255);
}
