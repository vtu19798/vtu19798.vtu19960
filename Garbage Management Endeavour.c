#include<Arduino.h>
#include<WiFi.h>
#include<WiFiClient.h>
#include<ThingSpeak.h>
#ifdef ESP32
#include<WiFi.h>
#elif defined(ESP8266)
#include<ESP8266WiFi.h>
#endif
#include<WiFiClient.h>
#include<ThingSpeak.h>
#defineWIFISSID”TP−Link8E98”
#defineWIFIPASSWORD”86427920”
WiFiClientclient;
unsignedlongmyChannelNumber=2394057;
constchar*myWriteAPIKey=”Y769PAN3DWTKA14C”;
Stringreadstring=””;
Stringwaterlevel;
intind1;
voidsetup(){
Serial.begin(9600);
Serial.println();
Serial.print(”ConnectingtoAP”);
WiFi.begin(WIFISSID,WIFIPASSWORD);
// Wait for WiFi connection
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
delay(200);
}
Serial.println();
Serial.println("WiFi connected.");
Serial.println("IP address:");
Serial.println(WiFi.localIP()); // Print local IP address
}
ThingSpeak.begin(client); // Initialize ThingSpeak client
voidloop(){
readstring=””; // Reset the variable to store incoming data
// Read data from serial port
while(Serial.available()){
delay(10); // Delay added to ensure stability
charc=Serial.read(); // Read a character from serial port
// Exit the loop when '#' is detected after the word
if(c=='#'){
break;
}
readstring+=c; // Build the string
}
// Check if data is received
if(readstring.length()>0){
Serial.println(readstring); // Print received data
waterlevel=readstring; // Store received data in waterlevel variable
Serial.print("Water Level: ");
Serial.println(waterlevel); // Print water level data
ThingSpeak.setField(1,waterlevel); // Set the value of Field 1 in ThingSpeak channel
ThingSpeak.writeFields(myChannelNumber,myWriteAPIKey); // Write data to ThingSpeak channel
delay(1000); // Delay before sending next data
}
}
