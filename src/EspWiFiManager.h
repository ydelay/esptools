#ifndef ESPWIFIMANAGER_H
#define ESPWIFIMANAGER_H
#ifdef ESP8266
  #include <ESP8266WifI.h>
#elif defined(ESP32)
  #include <WiFi.h>
#else
  #error "Ni ESP32 ni ESP8266 n'est défini"
#endif
#include <EspConsole.h>
#include <EspConfigManager.h>

class EspWiFiManager
{
private:
  EspConfigManager *config;
  EspConsole *console;

  bool STAconnected = false;
  bool APconnected = false;
  WiFiMode_t mode = WIFI_OFF;
  
  int choisirCanal();
  
public:
  /**
   * @brief This class represents a WiFi manager for ESP8266.
   *
   * The EspWiFiManager class provides functionality to manage WiFi connections on an ESP8266 device.
   */

  //--------------------------------------------------------------------------------
  // Constructors                                                                 --
  //--------------------------------------------------------------------------------
  EspWiFiManager();
  EspWiFiManager(EspConfigManager *configManager);

  //--------------------------------------------------------------------------------
  // Initialisation des variable private                                          --
  //--------------------------------------------------------------------------------

  void setconfig(EspConfigManager *pconfigManager);
  void setconsole(EspConsole *pconsole);

  void setup();

  void setupAccessPoint();

  void setupStation();

  void begin();
  void loop();
  void disconnect();
  bool isConnected();

  bool isConnectedAsStation();
  bool isAccespointactif();

  
};

#endif // ESPWIFIMANAGER_H


