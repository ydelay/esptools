#include <Arduino.h>
#include <string>
#include <Wire.h>
#include <EEPROM.h>
#include <EspConfigManager.h>

#define debug true
#define init_eeprom false

  

  static const int L_EEPROM_SIZE = 2048;
  static constexpr const char *L_L_EEPROM_MAGIC = "EEPROM";
  static const int L_L_EEPROM_MAGIC_SIZE = 7;
  static const int L_WIFI_MAX_SSID_SIZE = 32;
  static const int L_WIFI_MAX_PASSWORD_SIZE = 64;
  static const int L_MQTT_MAX_USER_SIZE = 32;
  static const int L_MQTT_MAX_PASSWORD_SIZE = 64;
  static const int L_WEB_MAX_USER_SIZE = 32;
  static const int L_WEB_MAX_PASSWORD_SIZE = 64;
  static const int L_DEVICE_MAX_NAME_SIZE = 32;
  static const int L_DEVICE_MAX_DESCRIPTION_SIZE = 255;
  static const int L_DEVICE_MAX_LOCATION_SIZE = 128;
  static const int L_OTA_MAX_PASSWORD_SIZE = 64;


  struct
  {
      char Magic[L_L_EEPROM_MAGIC_SIZE];
      char DeviceName[L_DEVICE_MAX_NAME_SIZE + 1];
      char DeviceDescription[L_DEVICE_MAX_DESCRIPTION_SIZE + 1];
      char DeviceLocation[L_DEVICE_MAX_LOCATION_SIZE + 1];
      char ClientWiFiSSID[L_WIFI_MAX_SSID_SIZE + 1];
      char ClientWiFiPassword[L_WIFI_MAX_PASSWORD_SIZE + 1];
      bool ClientWiFiToActivate;
      bool ClientWiFiManualIP;
      uint8_t ClientAdresse[4];
      uint8_t ClientSubnet[4];
      uint8_t ClientGateway[4];
      uint8_t ClientDNS[4];
      char AccesspointWiFiSSID[L_WIFI_MAX_SSID_SIZE + 1];
      char AccesspointWiFiPassword[L_WIFI_MAX_PASSWORD_SIZE + 1];
      bool AccesspointWiFiToActivate;
      bool AccesspointWiFiManualIP;
      uint8_t AccesspointAdresse[4];
      uint8_t AccesspointSubnet[4];
      uint8_t AccesspointGateway[4];
      uint8_t AccesspointDNS[4];
      uint8_t MQTTServer[4];
      char MQTTUser[L_MQTT_MAX_USER_SIZE + 1];
      char MQTTPassword[L_MQTT_MAX_PASSWORD_SIZE + 1];
      int16_t MQTTPort;
      char WEBUser[L_WEB_MAX_USER_SIZE + 1];
      char WEBPassword[L_WEB_MAX_PASSWORD_SIZE + 1];
      int16_t WEBPort;
      bool OTAEnable;
      char OTAPassword[L_OTA_MAX_PASSWORD_SIZE + 1];
      int16_t OTAPort;
  } New_EEPROM_Config;

  EspConfigManager *espConfig;

// ------- Fonction Setup du programme -------------------------------------------------------------

void setup()
{
Serial.begin(115200);

delay(20000);
Serial.println("Initialisation du programme");
delay(10000);
if (init_eeprom)
{
  Serial.println("Initialisation de l'EEPROM");
  EEPROM.begin(L_EEPROM_SIZE); 
  Serial.println("Initialisation de la configuration");
  strncpy(New_EEPROM_Config.Magic, L_L_EEPROM_MAGIC, sizeof(New_EEPROM_Config.Magic));
  strncpy(New_EEPROM_Config.DeviceName, "ESP8266", sizeof(New_EEPROM_Config.DeviceName));
  strncpy(New_EEPROM_Config.DeviceDescription, "ESP8266", sizeof(New_EEPROM_Config.DeviceDescription));
  strncpy(New_EEPROM_Config.DeviceLocation, "Bureau", sizeof(New_EEPROM_Config.DeviceLocation));
  strncpy(New_EEPROM_Config.ClientWiFiSSID, "delayfamilyUPC", sizeof(New_EEPROM_Config.ClientWiFiSSID));
  strncpy(New_EEPROM_Config.ClientWiFiPassword, "Yvesvalerie6870", sizeof(New_EEPROM_Config.ClientWiFiPassword));
  New_EEPROM_Config.ClientWiFiToActivate = true;
  New_EEPROM_Config.ClientWiFiManualIP = false;
  New_EEPROM_Config.AccesspointWiFiToActivate = false;
  New_EEPROM_Config.AccesspointWiFiManualIP = false;
  strncpy(New_EEPROM_Config.WEBUser, "admin", sizeof(New_EEPROM_Config.WEBUser));
  strncpy(New_EEPROM_Config.WEBPassword, "admin", sizeof(New_EEPROM_Config.WEBPassword));
  New_EEPROM_Config.MQTTPort = 1883;
  New_EEPROM_Config.WEBPort = 8080;
  New_EEPROM_Config.OTAEnable = true;
  strncpy(New_EEPROM_Config.OTAPassword, "Test", sizeof(New_EEPROM_Config.OTAPassword));
  New_EEPROM_Config.OTAPort = 8266;
  Serial.println("Sauvegarde de la configuration");
  EEPROM.put(0, New_EEPROM_Config);
  Serial.println("Sauvegarde de l'EEPROM");
  EEPROM.commit();
  delay(5000);
}
else
{
  Serial.println("Uniquement lecture de l'EEPROM");
}

espConfig = new EspConfigManager();

debug ? Serial.println("Chargement de la structure de puis l'EEPROM") : NULL;
espConfig->load();
debug ? Serial.println("espconfig.load() appelé") : NULL;
debug ? Serial.println("Contenu de l'EEPROM") : NULL;
debug ? Serial.print("EespConfig->getMagic() : ") : NULL;
debug ? Serial.println(espConfig->getMagic().c_str()) : NULL;
debug ? Serial.print("espConfig->getDeviceName : ") : NULL;
debug ? Serial.println(espConfig->getDeviceName().c_str()) : NULL;
debug ? Serial.print("espConfig->getDeviceDescription : ") : NULL;
debug ? Serial.println(espConfig->getDeviceDescription().c_str()) : NULL;
debug ? Serial.print("espConfig->getDeviceLocation : ") : NULL;
debug ? Serial.println(espConfig->getDeviceLocation().c_str()) : NULL;
debug ? Serial.print("espConfig->getClientWiFiSSID : ") : NULL;
debug ? Serial.println(espConfig->getClientWiFiSSID().c_str()) : NULL;
debug ? Serial.print("espConfig->getClientWiFiPassword : ") : NULL;
debug ? Serial.println(espConfig->getClientWiFiPassword().c_str()) : NULL;
debug ? Serial.print("espConfig->getWEBUser : ") : NULL;
debug ? Serial.println(espConfig->getWEBUser().c_str()) : NULL;
debug ? Serial.print("espConfig->getWEBPassword : ") : NULL;
debug ? Serial.println(espConfig->getWEBPassword().c_str()) : NULL;
debug ? Serial.print("espConfig->getWEBPort : ") : NULL;
debug ? Serial.println(String(espConfig->getWEBPort()).c_str()) : NULL;
debug ? Serial.print("espConfig->getMQTTPort : ") : NULL;
debug ? Serial.println(String(espConfig->getMQTTPort()).c_str()) : NULL;


Serial.println("Fin de setup");

}

// ------- Fonction Loop du programme --------------------------------------------------------------

void loop()
{
   // put your main code here, to run repeatedly:
   delay(2000);
   // put your main code here, to run repeatedly:
Serial.print(".");
}

// ------- Core des fonctions déclarées  -----------------------------------------------------------




