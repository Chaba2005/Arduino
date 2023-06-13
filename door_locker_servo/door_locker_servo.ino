/*Door lock system code
 * https://srituhobby.com
 */
 
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
String UID = "A0 B1 53 7E";
byte lock = 0;

Servo servo;
MFRC522 rfid(SS_PIN, RST_PIN);


void setup() {
  Serial.begin(9600);
  servo.write(70);
  servo.attach(3);
  SPI.begin();
  rfid.PCD_Init();
}

void loop() {
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if ( ! rfid.PICC_ReadCardSerial())
    return;


  Serial.print("NUID tag is :");
  String ID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    ID.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    ID.concat(String(rfid.uid.uidByte[i], HEX));
    delay(300);
  }
  ID.toUpperCase();

  if (ID.substring(1) == UID && lock == 0 ) {
    
    servo.write(70);
    delay(1500);
    lock = 1;
  } else if (ID.substring(1) == UID && lock == 1 ) {
    servo.write(160);
    Serial.print("fon");
    delay(1500);
    lock = 0;
  } else {
    delay(1500);
    Serial.print("AFF");
  }
}
