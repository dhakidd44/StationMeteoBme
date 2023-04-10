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
AsyncWebServer server(80); // initialisation de notre serveur au port 8

// Concatenation de texte page notre page HTML
const char index_html[] PROGMEM = R"=====(

 <!DOCTYPE html>
<html>

<head>
    <title>Weather Station</title>
    <!-- Importer Bootstrap CSS --> 
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css">
    <link href='https://fonts.googleapis.com/css?family=Open+Sans:300,400,600' rel='stylesheet'>

</head>

<body>
    </head>
    <style>
        .head1 {

            text-align: center;

        }
        .border3 {
            border-radius: 10px;
            border: 1px solid black;
            width: 350px;
            position: absolute;
            top: 10%;
            left: 35vw;
        }
        .alt {
            font-family: Arial, Helvetica, sans-serif;
            display: block;
            margin: 0px auto;
            /* text-align: center; */
            color: #444444;
            display: table-cell;
           position: relative;
            font-weight: 100;
        }
        .h1 {
            border-radius: 10px;
            border-color: black;
            background-color: rgb(131, 164, 230);

        }

        .body {
            background-color: aliceblue;

        }

        .border3 {
            border-radius: 1px solid black;
        }

        .od {
            color: rgb(231, 146, 19);
            font-size: xx-large;

        }

        .od2 {
            color: rgb(11, 108, 205);
          
           font-size: xx-large;
        }

        .od3 {
            color: rgb(18, 234, 72);
            font-size: xx-large;
        }

        .od4 {
            color: rgb(126, 30, 182);
            font-size: xx-large;
        }
  
    </style>

    <body>

        <div class="row1 border3">
            <div class="container head1">
                <h1 class="h1">ESP8266 WEATHER STATION</h1>

            </div>
            <hr>

            <div class="row  row1">
                <div class="col bordure">
                    <svg class="od" xmlns="http://www.w3.org/2000/svg" width="49" height="40" fill="currentColor"
                        class="bi bi-thermometer-half" viewBox="0 0 16 16">
                        <path d="M9.5 12.5a1.5 1.5 0 1 1-2-1.415V6.5a.5.5 0 0 1 1 0v4.585a1.5 1.5 0 0 1 1 1.415z" />
                        <path
                            d="M5.5 2.5a2.5 2.5 0 0 1 5 0v7.55a3.5 3.5 0 1 1-5 0V2.5zM8 1a1.5 1.5 0 0 0-1.5 1.5v7.987l-.167.15a2.5 2.5 0 1 0 3.333 0l-.166-.15V2.5A1.5 1.5 0 0 0 8 1z" />
                    </svg>
                </div>
                <div class="col bordure alt">Temperature </div>
                <div id="temperature" class="col od ">  </div>
                <div class="col bordure od"><sup>&deg;C </sup> </div>
            </div>

            <hr>
            <hr>
            <div class="row  ">
                <div class="col bordure"><svg class="od2" xmlns="http://www.w3.org/2000/svg" width="40" height="40"
                        fill="currentColor" class="bi bi-droplet-fill" viewBox="0 0 16 16">
                        <path
                            d="M8 16a6 6 0 0 0 6-6c0-1.655-1.122-2.904-2.432-4.362C10.254 4.176 8.75 2.503 8 0c0 0-6 5.686-6 10a6 6 0 0 0 6 6ZM6.646 4.646l.708.708c-.29.29-1.128 1.311-1.907 2.87l-.894-.448c.82-1.641 1.717-2.753 2.093-3.13Z" />
                    </svg></div>
                <div class="col bordure alt">Humidity </div>
                <div id="humidity" class="col od2">   </div>
                <div class="col bordure od2"><sup>% </sup></div>

            </div>
            <hr>
            <hr>
            <div class="row  ">
                <div class="col bordure"><svg class="od3" xmlns="http://www.w3.org/2000/svg" width="40" height="40"
                        fill="currentColor" class="bi bi-speedometer" viewBox="0 0 16 16">
                        <path
                            d="M8 2a.5.5 0 0 1 .5.5V4a.5.5 0 0 1-1 0V2.5A.5.5 0 0 1 8 2zM3.732 3.732a.5.5 0 0 1 .707 0l.915.914a.5.5 0 1 1-.708.708l-.914-.915a.5.5 0 0 1 0-.707zM2 8a.5.5 0 0 1 .5-.5h1.586a.5.5 0 0 1 0 1H2.5A.5.5 0 0 1 2 8zm9.5 0a.5.5 0 0 1 .5-.5h1.5a.5.5 0 0 1 0 1H12a.5.5 0 0 1-.5-.5zm.754-4.246a.389.389 0 0 0-.527-.02L7.547 7.31A.91.91 0 1 0 8.85 8.569l3.434-4.297a.389.389 0 0 0-.029-.518z" />
                        <path fill-rule="evenodd"
                            d="M6.664 15.889A8 8 0 1 1 9.336.11a8 8 0 0 1-2.672 15.78zm-4.665-4.283A11.945 11.945 0 0 1 8 10c2.186 0 4.236.585 6.001 1.606a7 7 0 1 0-12.002 0z" />
                    </svg></div>
                <div class="col bordure alt">Pression </div>
                <div id="pression" class="col bordure id2 od3"></div>
                <div class="col bordure id2 od3"><sup> hPa </sup> </div>
            </div>
            <hr>
            <hr>
            <div class="row  ">
                <div class="col bordure"><svg class="od4" xmlns="http://www.w3.org/2000/svg" width="40" height="40"
                        fill="currentColor" class="bi bi-file-image-fill" viewBox="0 0 16 16">
                        <path
                            d="M4 0h8a2 2 0 0 1 2 2v8.293l-2.73-2.73a1 1 0 0 0-1.52.127l-1.889 2.644-1.769-1.062a1 1 0 0 0-1.222.15L2 12.292V2a2 2 0 0 1 2-2zm4.002 5.5a1.5 1.5 0 1 0-3 0 1.5 1.5 0 0 0 3 0z" />
                        <path
                            d="M10.564 8.27 14 11.708V14a2 2 0 0 1-2 2H4a2 2 0 0 1-2-2v-.293l3.578-3.577 2.56 1.536 2.426-3.395z" />
                    </svg></i></div>
                <div class="col bordure alt">Altitude </div>
                <div id="altitude" class="col bordure id2 od4 "> </div>
                <div class="col bordure id2 od4"><sup> m</sup> </div>
                <hr>
                <hr>
            </div>

        </div>
        <script src="/Js/stock.js"></script>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.3/jquery.min.js"></script>  
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/js/bootstrap.bundle.min.js"
        integrity="sha384-kenU1KFdBIe4zVF0s0G1M5b4hcpxyD9F7jL+jjXkk+Q2h455rYXK/7HAuoJl+0I4"
        crossorigin="anonymous"></script>
    </body>
</html>
    )=====";

 // Concatenation de javascript
const char Js_sam[] PROGMEM = R"=====(
    setInterval(function () {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
                var objBme = JSON.parse(this.responseText);
                document.getElementById("temperature").innerHTML = objBme.Temperature;
                document.getElementById("humidity").innerHTML = objBme.Humidity;
                document.getElementById("pression").innerHTML = objBme.Pression;
                document.getElementById("altitude").innerHTML = objBme.Altitude;
            }
        };
        xhttp.open("GET", "/data", true);
        xhttp.send();
    }, 3000);
)=====";   
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