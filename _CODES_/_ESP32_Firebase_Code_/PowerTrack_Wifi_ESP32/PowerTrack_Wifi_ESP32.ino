#include <Arduino.h>
///Only change these if required

#define _SSID "SSID"                                                                                // Your WiFi SSID
#define _PASSWORD "PASSWORD"                                                                        // Your WiFi Password
#define REFERENCE_URL "https://smart-meter-connect-default-rtdb.firebaseio.com/"                    // Your Firebase project reference url
String Sheets_GAS_ID = "AKfycbwqcat3eObFIYfIJOAXMDAEHKJ5vLfBMXQAxTOS1Ic_P8XjbEI9dSSikmM3ucUjMQq-";  // Your Google Appscript anon reference url



///***************************************///


#include "TRIGGER_WIFI.h"
#include "TRIGGER_GOOGLESHEETS.h"
#include <WiFi.h>
#include <ESP32Firebase.h>
#include <WiFiClientSecure.h>

#define Onboard_Led 2
#define Relay 26

Firebase firebase(REFERENCE_URL);

/**********Google Sheets Definations***********/

char column_name_in_sheets[][6] = { "val1", "val2", "val3", "val4", "val5" };
int No_of_Parameters = 5;

/*********************************************/

float PriceDay, PriceEve, PriceNight;
String bRelay;
int8_t indexOfA, indexOfB, indexOfC, indexOfD, indexOfE, indexOfF;
String _Voltage, _Current, _Power, _Units, _Total_Rate, _Today_Unit;

char c;
String dataIn;

/*********************************************/

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);

  // Connect to WiFi
  Serial.print(F("Connecting to: "));
  Serial.println(F(_SSID));
  WiFi.begin(_SSID, _PASSWORD);

  pinMode(Onboard_Led, OUTPUT);
  digitalWrite(Onboard_Led, HIGH);


  //Wifi Connecting Process
  pinMode(Relay, OUTPUT);
  
  digitalWrite(Relay, HIGH);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("-"));
    digitalWrite(Onboard_Led, LOW);
    delay(300);
    digitalWrite(Onboard_Led, HIGH);
    delay(300);
  }

  digitalWrite(Onboard_Led, LOW);

  // Print the IP address
  Serial.print(WiFi.localIP());

  client.setInsecure();


  
  Serial.println(ESP.getFreeHeap());  //Shows Free Heap inside ESP32

  Google_Sheets_Init(column_name_in_sheets, Sheets_GAS_ID, No_of_Parameters);  //Initialize Google Sheet Data TX

  ///*******......Get Information From FireBase.....*******///

  PriceDay = firebase.getFloat("/Price/Day");

  PriceEve = firebase.getFloat("/Price/Eve");

  PriceNight = firebase.getFloat("/Price/Night");
}

void loop() {
  for (int g = 0; g < 5; g++) {

    ///*******....Send Information To ATMEGA328P....*******///

    Serial2.print(PriceDay, 2);
    Serial2.print("A");
    Serial2.print(PriceEve, 2);
    Serial2.print("B");
    Serial2.print(PriceNight, 2);
    Serial2.print("C");

    Serial2.print("\n");

    Serial2.flush();

    while (Serial2.available() > 0) {
      delay(1000);
      c = Serial2.read();

      if (c == '\n') {
        break;
      } else {
        dataIn += c;
      }
    }

    if (c == '\n') {
      Parse_the_Data();

      c = 0;
      dataIn = "";
    }

    digitalWrite(Onboard_Led, HIGH);

    ///********************************************///
    ///*******..........Relay Bus...........*******///
    ///********************************************///

    bRelay = firebase.getString("/Meter/Relay");

    if (bRelay == "true" && (150.00f < _Voltage.toFloat()) && _Current.toFloat() < 20.00f) {
      digitalWrite(Relay, HIGH);
      firebase.setString("/Meter/RelayActive", "ON");
    } else if (bRelay == "true" && (_Voltage.toFloat() < 150.00f)) {
      digitalWrite(Relay, LOW);
      firebase.setString("/Meter/RelayActive", "Voltage_ERROR!!!");
    } else if (bRelay == "true" && (_Current.toFloat() > 20.00f)) {
      digitalWrite(Relay, LOW);
      firebase.setString("/Meter/RelayActive", "Current_ERROR!!!");
    } else if (bRelay == "false") {
      digitalWrite(Relay, LOW);
      firebase.setString("/Meter/RelayActive", "OFF");
    }

    ///*******....Set Information to FireBase....*******///

    firebase.setString("/Meter/Voltage", String(_Voltage.toFloat(), 2));

    firebase.setFloat("/Meter/Current", _Current.toFloat());

    firebase.setFloat("/Meter/Power", _Power.toFloat());

    firebase.setString("/Meter/Units", String(_Units.toFloat(), 2));

    firebase.setFloat("/Meter/Total_Rate", _Total_Rate.toFloat());

    firebase.setFloat("/Meter/Today_Unit", _Today_Unit.toFloat());


    ///*******......Get Information From FireBase.....*******///

    PriceDay = firebase.getFloat("/Price/Day");

    PriceEve = firebase.getFloat("/Price/Eve");

    PriceNight = firebase.getFloat("/Price/Night");


    ///*******....Set Information to Google_Sheets....*******///

    Data_to_Sheets(No_of_Parameters, _Voltage.toFloat(), _Current.toFloat(), _Units.toFloat(), _Total_Rate.toFloat(), _Today_Unit.toFloat());

    digitalWrite(Onboard_Led, LOW);

    delay(5000);
  }
  ESP.restart();
}

void Parse_the_Data() {
  indexOfA = dataIn.indexOf("A");
  indexOfB = dataIn.indexOf("B");
  indexOfC = dataIn.indexOf("C");
  indexOfD = dataIn.indexOf("D");
  indexOfE = dataIn.indexOf("E");
  indexOfF = dataIn.indexOf("F");

  _Voltage = dataIn.substring(0, indexOfA);
  _Current = dataIn.substring(indexOfA + 1, indexOfB);
  _Power = dataIn.substring(indexOfB + 1, indexOfC);
  _Units = dataIn.substring(indexOfC + 1, indexOfD);
  _Total_Rate = dataIn.substring(indexOfD + 1, indexOfE);
  _Today_Unit = dataIn.substring(indexOfE + 1, indexOfF);
}
