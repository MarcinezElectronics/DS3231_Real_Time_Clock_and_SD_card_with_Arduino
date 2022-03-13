
/*
 * Viyázat!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * A fájl név maximum 8 karakter lehet!
 */
 
#include <Wire.h>
#include <DS3231.h>
#include <SPI.h>
#include <SD.h>

DS3231 ora;
RTClib myRTC;
File   tempData;

void writeToFile(String dataFile, String tempDatas);
void createFile(String fileName);

const int chipSelect = 53;
String csvData = "teszt";

void setup () {
  
    Serial.begin(9600);
    while (!Serial) {
    ;
    }
    Wire.begin();

    if (!SD.begin(chipSelect)) {
      Serial.println("SD card error!");
    while (1);
  }

  Serial.println("SD card OK!");
  
  createFile("unixtemp.csv");//"Ev, Honap, Nap, Ora, Perc, Masodperc, Homerseklet");
}

void loop () {
    
    delay(1000);
    
    DateTime now = myRTC.now();

    csvData = String(now.unixtime()) + ',' + String(ora.getTemperature());

    //csvData = String(now.year()) + ',' + String(now.month()) + ',' + String(now.day()) + ',' + String(now.hour()) + ',' + String(now.minute()) + ',' + String(now.second()) + ',' + String(ora.getTemperature());

    Serial.println(csvData);

    //Serial.println(String(now.secondstime()));
    writeToFile("viztemp.csv", csvData);
    
    Serial.print(now.year());
    Serial.print('/');
    
    if(now.month() < 10) {
      Serial.print("0");
      Serial.print(now.month());
    }
    else {Serial.print(now.month());}
    
    Serial.print('/');
    
    if(now.day() < 10) {
      Serial.print("0");
      Serial.print(now.day());
    }
    else {Serial.print(now.day());}
    
    Serial.print(' ');
    
    if(now.hour() < 10) {
      Serial.print("0");
      Serial.print(now.hour());
    }
    else {Serial.print(now.hour());}
    
    Serial.print(':');
    
    if(now.minute() < 10) {
      Serial.print("0");
      Serial.print(now.minute());
    }
    else {Serial.print(now.minute());}
    
    Serial.print(':');
    
    if(now.second() < 10) {
      Serial.print("0");
      Serial.print(now.second());
    }
    else {Serial.print(now.second());}
    
    Serial.print(' ');
    
    Serial.print(ora.getTemperature(), 2);
    Serial.println("°C");

    switch(ora.getDoW()){
      case 1: Serial.println("Vasarnap");
      break;
      case 2: Serial.println("Hetfo");
      break;
      case 3: Serial.println("Kedd");
      break;
      case 4: Serial.println("Szerda");
      break;
      case 5: Serial.println("Csutortok");
      break;
      case 6: Serial.println("Pentek");
      break;
      case 7: Serial.println("Szombat");
      break;
      default:
      break;
    }
}

//SD kártya írás, olvasás, felülírás függvényei--------------------------------------
void createFile(String fileName){

  tempData = SD.open(fileName, FILE_WRITE);

  if (tempData) {
    tempData.close();
    Serial.println(csvData);
    Serial.println("Write OK!");
  }
  else {
    Serial.println("Error opening viztemp.csv");
  } 
}

void writeToFile(String dataFile, String tempDatas){

  tempData = SD.open(dataFile, FILE_WRITE);

  if (tempData) {
    tempData.println(tempDatas);
    tempData.close();
    Serial.println("Write OK!");
    Serial.println(csvData);
  } else {
    Serial.println("SD card error!");
  }  
}
