// ####################################################################################################
// Programm : Read_SML_and_EBus
// ============================
//  Author : Frank Hinkel Version 1.0 / 16.03.2013
// ----------------------------------------------------------------------------------------------------
// Liest von den Seriellen Schnittstellen Serial1 und Serial3 die Infrarotsignale von Elektrozaehlern.
// An Serial3 wird auf Daten an einer EBus-Schnittstelle gelauscht. In der 2. Ausbaustufe sollen auch
// Daten auf den eBus geschrieben werden. Die Lesemodule werden als unabhaengige Automaten implemen-
// tiert.
//
// RX1 = IR-Serial-In 1 : Liest den Zählerstand des Elektrozählers 1
// RX2 = IR-Serial-In 2 : Liest den Zählerstand des Elektrozählers 2
// RX3 = eBus-Serial-In : Liest die Daten an der EBus Schnittstelle
//
// ====================================================================================================
// Changelog:
// 16.03.2013 Frank Hinkel : Ersterstellung
// 01.04.2013 Frank Hinkel : Fertigstellung Prototyp
// ####################################################################################################

// Standard-Libraries
#include <SPI.h>
#include <Ethernet.h>

#include <eBus.h> // class implementing eBus-Protokoll (read/write) for Weishaupt heating
#include <SML.h>  // class implementing SML-Protokoll (read) for EHZ power meters

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 240);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

eBus myEBus;
SML mySML1;
SML mySML2;

//String testData1;int posTestData1;
//String testData2;int posTestData2;

void init_serial() {
	Serial.begin(9600);
	Serial1.begin(9600);  // IR-Signal sendet mit 9600 Baud
	Serial2.begin(9600);  // IR-Signal sendet mit 9600 Baud
	Serial3.begin(2400);  // Ebus sendet mit 2400 Baud

	Serial.println("### Programmstart ###");
}

void serialEvent1() // Serial Data received an RX1 : SML
{
	int i = 0;
	if (mySML2.busy)
		return;
	while ((i++ < 1000) && Serial1.available())
		mySML1.doData(Serial1.read());
}

void serialEvent2() // Serial Data received an RX2 : SML
{
	int i = 0;
	if (mySML1.busy)
		return;
	while ((i++ < 1000) && Serial2.available())
		mySML2.doData(Serial2.read());
}

void serialEvent3() // Serial Data received an RX3 : eBus
{
	int i = 0;
	while ((i++ < 1000) && Serial3.available())
		myEBus.doData(Serial3.read());
}

void SendSerial3(unsigned char data[]) {
	Serial3.write(0xAA);
	for (int i = 0; data[i] != 0xAA; i++)
		Serial3.write(data[i]);
	Serial3.write(0xAA);
}

void setup() {
	init_serial();

	// start the Ethernet connection and the server:
	Ethernet.begin(mac, ip);
	server.begin();

}

void printSML(EthernetClient &client, SML &mySML) {
	client.print("Serial=");
	client.println(mySML.OB2_0_0_0);
	client.print("OB 1.7.0=");
	client.println(mySML.OB2_1_7_0);
	client.print("OB 2.7.0=");
	client.println(mySML.OB2_2_7_0);
	client.print("OB 1.8.1=");
	client.println(mySML.OB2_1_8_1);
	client.print("OB 2.8.1=");
	client.println(mySML.OB2_2_8_1);
	client.println();
}

void printEBus(EthernetClient &client, eBus &myEBus) {
	client.print("Datum=");
	client.print(myEBus.dataDatum);
	client.print(" ");
	client.println(myEBus.dataZeit);
	client.print("K=");
	client.println(myEBus.dataKesselTemp);
	client.print("W=");
	client.println(myEBus.dataBrauchwasserTemp);
	client.print("V=");
	client.println(myEBus.dataVorlaufTemp);
	client.print("A=");
	client.println(myEBus.dataAussenTemp);
	client.println();
}

void loop() {
	EthernetClient client = server.available();

	if (client) {
		// an http request ends with a blank line
		boolean currentLineIsBlank = true;
		while (client.connected()) {
			if (client.available()) {
				char c = client.read();
				// if you've gotten to the end of the line (received a newline
				// character) and the line is blank, the http request has ended,
				// so you can send a reply
				if (c == '\n' && currentLineIsBlank) {
					// send a standard http response header
					client.println("HTTP/1.1 200 OK");
					client.println("Content-Type: text/html");
					client.println("Connection: close");
					client.println();
					client.println("<!DOCTYPE HTML>");
					client.println("<html>");

					// add a meta refresh tag, so the browser pulls again every 60 seconds:
					client.println(
							"<meta http-equiv=\"refresh\" content=\"60\">");

					client.println("<pre>");

					printEBus(client, myEBus);
					printSML(client, mySML1);
					printSML(client, mySML2);

					client.println("</pre>");
					client.println("</html>");

					break;
				}
				if (c == '\n') {
					// you're starting a new line
					currentLineIsBlank = true;
				} else if (c != '\r') {
					// you've gotten a character on the current line
					currentLineIsBlank = false;
				}
			}
		}
		// give the web browser time to receive the data
		delay(1);
		// close the connection:
		client.stop();
	}

	/*
	 if((posTestData1<testData1.length()) && !mySML1.busy) {
	 byte data = mySML1.hex2dec(testData1.substring(posTestData1,posTestData1+2));
	 mySML1.doData(data);
	 posTestData1 += 2;
	 delay(10);
	 }
	 */
}

