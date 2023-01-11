#include "Variables.h"
#include <Scheduler.h>
#include <Task.h>
#include <LittleFS.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>
#include <WiFiClient.h>
#include <WiFiManager.h>
#include <WiFiUdp.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
#include <OpenTherm.h>
#include <ArduinoJson.h>

//Входные и выходные контакты OpenTherm, подключены к 4 и 5 контактам платы
const int inPin = 4;  //D2
const int outPin = 5; //D1

#define BUILTIN_LED 2     // D4 Встроенный LED
#define BOILER_RATING 24.0 // Boiler max power in kW
#define HOUSE_ENERGY 2700.0 // Energy of 1°C of a house
#define MINUTE_ENERGY_LOSS -0.06 // Loss of energy per minute

bool debug = false;
//flag for saving data
bool shouldSaveConfig = false;

#define DEBUG  \
    if (debug) \
    Serial
#define INFO Serial
#define WARN Serial

// Temporary
float 
    c_e = 0; // Accumulated energy

char host[80] = "boiler-01";
char mqtt_server[80];
char mqtt_port[6] = "1883";
char mqtt_user[34];
char mqtt_password[34];

OpenTherm ot(inPin, outPin);
WiFiClient espClient;
PubSubClient client(espClient);

/* Новый код добавляется из скетчей  */