/*
  Titre      : Staion Meteo
  Auteur     : Ernest Samuel Andre
  Date       : 10/04/2023
  Description: Ce programme a pour but de faire une Staion meteo avec
                un capteur BME280 et d'afficher les donnees
               sur une page web. Ces donnes seront mis dans un fichier 
               Json puis avec la communcation de notre page web et le fichier Json sera realiser avec Ajax
  Version    : 0.0.1
*/

//Librairies necessaires pour notre programme
#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <WebServer.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#define SEALEVELPRESSURE_HPA (1013.25) // Niveau de la mer en hPa

// Connection a notre reseau Local
const char *ssid = "Cottage";
const char *password = "Cottage2018";


Adafruit_BME280 bme;                   // initialisation du capteur BME280
void setup() {

   Serial.begin(115200); // Initialisation de notre moniteur serie
    delay(100);
    bme.begin(0x76); // Initalisation de notre capteur
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
     Serial.println(ssid); // Affichage du nom de reseau
   WiFi.begin(ssid, password); // connection a notre wifi local
    // attente de connection a notre reseau
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }

     // initialisation du capteur BME280
    if (!bme.begin(0x76))
    {
        Serial.println("Erreur lors de l'initialisation du capteur BME280");
        while (1)
            ;
    }
  
}

void loop() {
  // put your main code here, to run repeatedly:
}