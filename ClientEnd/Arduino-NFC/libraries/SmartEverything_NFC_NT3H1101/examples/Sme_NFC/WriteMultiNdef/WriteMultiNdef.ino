/*
    SmeNfc Library - WriteMultiNdef

    Demonstrate how to write multiple NDEF and put on the correct position.
    The library compose the NDEF record accordingly with the required tag.
    And make in the end the RGB led continuously blink green.

    created 27 Apr 2015
    Authors: Mik (smkk@axelelettronica.it), Bill (github@unbiot.com)

    This example is in the public domain
    https://github.com/ameltech

    NXP more information available here:
    http://www.nxp.com/products/identification_and_security/nfc_and_reader_ics/connected_tag_solutions/series/NT3H1101_NT3H1201.html
*/

#include <Wire.h>
#include <SmeNfc.h>
#include <Arduino.h>

#define SME_2_1         "SmartEverything"
#define WEB             "amel-tech.com"
#define FEATURE_READY   "Feature Supported: NFC, SigFox, GPS, Arduino IDE"

bool nfcOk;
byte buffer[UID_SIZE];

// the setup function runs once when you press reset or power the board
void setup() {

  // Initialize the SmartEverything as Master
  Wire.begin();
	
  // initialize digital pin 13 as an output.
  pinMode(PIN_LED_13, OUTPUT);

  // just clear the buffer
  for (int i = 0; i < UID_SIZE; i++) {
    buffer[i] = 0;
  }

  // initialize USB console
  SerialUSB.begin(115200);

  if (smeNfcDriver.readUID(buffer)) {
    smeNfc.storeText(NDEFFirstPos, SME_2_1);
    smeNfc.storeUrihttp(NDEFMiddlePos, WEB);
    smeNfc.storeText(NDEFLastPos, FEATURE_READY);
    nfcOk = true;
  }
}

// the loop function runs over and over again forever
void loop() {

  if (nfcOk == true) {

    // Send the UID of the NT3H1101 to the Console
    SerialUSB.print("Serial number (UID): ");
    for (int i = 0; i < UID_SIZE; i++) {
      SerialUSB.print(buffer[i], HEX);
      SerialUSB.print(':');
    }
    SerialUSB.println();

    digitalWrite(PIN_LED_13, LOW);	// turn the LED On
    delay(1000);

    digitalWrite(PIN_LED_13, HIGH);   // turn the LED off
    delay(2000);					// wait for a second
  }
}
