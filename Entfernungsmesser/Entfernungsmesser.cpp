#include <LiquidCrystal.h>
#include <NewPing.h>

#include "Entfernungsmesser.h"

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}


// The loop function is called in an endless loop
void loop()
{
	  delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
	  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
	  lcd.print("Ping: ");
	  lcd.print(sonar.convert_cm(uS)); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
	  lcd.println("cm");
}
