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


void setup() {
  
}

void loop() {
  // put your main code here, to run repeatedly:
}