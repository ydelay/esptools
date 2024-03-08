#include <Arduino.h>
#include <string>
#include <Wire.h>
#include <EEPROM.h>
#include <EspConfigManager.h>
#include <EspWiFiManager.h>
#include <EspConfigWebserver.h>

#define debug true


  EspConfigManager *espConfig;
  EspWiFiManager *espWiFi;
  EspConfigWebserver *espWebserver;
// ------- Fonction Setup du programme -------------------------------------------------------------

void setup()
{
  Serial.begin(115200);
  delay(20000);

  Serial.println("Initialisation de EspConfigManager");
  espConfig = new EspConfigManager();

  if(!espConfig->load()) 
  {
    Serial.println("Initialisation de l'EEPROM dans 10 secondes");
    delay(10000);
    Serial.println("Initialisation de la configuration");
    delay(1000);

    espConfig->setMagic();

    espConfig->setDeviceName("ESP32");

    espConfig->setClientWiFiSSID("delayfamilyUPC");
    espConfig->setClientWiFiPassword("Yvesvalerie6870");
    espConfig->setClientWiFiToActivate(true);
    espConfig->setClientWiFiManualIP(false);

    espConfig->setAccesspointWiFiSSID("ESP32 WiFi AP");
    espConfig->setAccesspointWiFiPassword("wifipassword");
    espConfig->setAccesspointWiFiToActivate(false);
    espConfig->setAccesspointWiFiManualIP(false);

    espConfig->setWEBUser("admin");
    espConfig->setWEBPassword("admin");
    espConfig->setWEBPort(8080);

    Serial.println("Sauvegarde de la configuration");
    espConfig->save();

    Serial.println("Fin de l'initialisation de l'EEPROM");
  }
  else
  {
    Serial.println("EEPROM déjà initialisée");
  }

  Serial.println("Configuration du WiFi");
  espWiFi = new EspWiFiManager(espConfig);
  espWiFi->setconfig(espConfig);
  espWiFi->setconsole(NULL);
  espWiFi->setup();
  espWiFi->begin();
  Serial.print("Connexion au WiFi en cours");
  
  while (!espWiFi->isConnected())
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nWiFi connecté");
  delay(5000);

  espWebserver = new EspConfigWebserver();


  Serial.println("Fin de setup");

}

// ------- Fonction Loop du programme --------------------------------------------------------------

void loop()
{
  // put your main code here, to run repeatedly:
  // put your main code here, to run repeatedly:
  
  Serial.println("Chargement de la structure de puis l'EEPROM");
  if (espConfig->load())
  {
    Serial.println("Chargement de la structure de puis l'EEPROM");

    debug ? Serial.println("espconfig.load() appelé") : 0;
    debug ? Serial.println("Contenu de l'EEPROM") : 0;
    debug ? Serial.print("EespConfig->getMagic() : ") : 0;
    debug ? Serial.println(espConfig->getMagic().c_str()) : 0;
    debug ? Serial.print("espConfig->getDeviceName : ") : 0;
    debug ? Serial.println(espConfig->getDeviceName().c_str()) : 0;
    debug ? Serial.print("espConfig->getDeviceDescription : ") : 0;
    debug ? Serial.println(espConfig->getDeviceDescription().c_str()) : 0;
    debug ? Serial.print("espConfig->getDeviceLocation : ") : 0;
    debug ? Serial.println(espConfig->getDeviceLocation().c_str()) : 0;
    debug ? Serial.print("espConfig->getClientWiFiSSID : ") : 0;
    debug ? Serial.println(espConfig->getClientWiFiSSID().c_str()) : 0;
    debug ? Serial.print("espConfig->getClientWiFiPassword : ") : 0;
    debug ? Serial.println(espConfig->getClientWiFiPassword().c_str()) : 0;
    debug ? Serial.print("espConfig->getWEBUser : ") : 0;
    debug ? Serial.println(espConfig->getWEBUser().c_str()) : 0;
    debug ? Serial.print("espConfig->getWEBPassword : ") : 0;
    debug ? Serial.println(espConfig->getWEBPassword().c_str()) : 0;
    debug ? Serial.print("espConfig->getWEBPort : ") : 0;
    debug ? Serial.println(String(espConfig->getWEBPort()).c_str()) : 0;
    debug ? Serial.print("espConfig->getMQTTPort : ") : 0;
    debug ? Serial.println(String(espConfig->getMQTTPort()).c_str()) : 0;
  }
  else
  {
    Serial.println("Erreur de chargement de la structure depuis l'EEPROM");
  }

  delay(5000);
}

// ------- Core des fonctions déclarées  -----------------------------------------------------------




