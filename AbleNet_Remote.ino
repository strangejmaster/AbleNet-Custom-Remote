#include <IRremote.hpp>
/*
-John Galvez

This code sends signals from an IR remote to an AbleNet device through an aux cable.

AbleNet can be controlled by any digital 3.5mm mono switch (Page 8, https://files.ablenetinc.com/BigCommerce/content/html/Downloads/Activity_Supports/powerlink4_manual.pdf)

Uses this remote: https://www.amazon.com/Alinan-Infrared-Wireless-Control-Receiver/dp/B0CBP2DB9S/


Please see the schematic for pins https://anacapa.kycon.com/Pub_Eng_Draw/STX-3120-5B.pdf
Pin 1 (GND) of the 3.5mm adapter should connect to the emitter pin of the transistor
Pin 5 (Power) of the 3.5mm adapter should connect to the collector pin of the transistor
====Full schematic on paper
*/




// Switch connects to the base pin of the transistor
#define switch 3

// irOut connects to the out pin of the HX1838 circuit
#define irOut 6

IRRecv recv(irOut);
decode_results results; // Stores the results of the remote

bool toggled = false;

void setup() {
    pinMode(switch, OUTPUT);
    Serial.begin(9600);

    // Test switching
    Serial.println("Activating in 1 second")
    delay(1000);
    Serial.println("Turning off in 4 seconds");
    digitalWrite(switch, HIGH);
    delay(4000);
    digitalWrite(switch, LOW);

    Serial.println("Starting receiver...");
    recv.enableIRIn();
    Serial.println("Active")
}

void loop() {
    if (recv.decode(&results)) {
      // Print the HEX code recieved
      Serial.println(results.value, HEX);

      // Start listening for signals again
      recv.resume();

      toggle = !toggle;
      digitalWrite(switch, toggle ? HIGH : LOW);      
    }
}
