#ifdef ESP32
    #pragma message("ESP32 est défini")
#elif defined(ESP8266)
    #pragma message("ESP8266 est défini")
#else
    #error "Ni ESP32 ni ESP8266 n'est défini"
#endif
// --- Le micro controleur a un écran oled
#define ESPDISPLAY

#include <Arduino.h>
#include <ArduinoOTA.h>
#include <EspConsole.h>
#include <EspConfigManager.h>
#include <EspWifiManager.h>
#include <EspConfigWebserver.h>
#ifdef ESPDISPLAY
    #include <EspDisplay.h>
#endif

// ------- Définition des entrées sorties ----------------------------------------------------------
#if defined(ESP8266) && defined(ESPDISPLAY)
    #define PIN_OLED_CLOCK 14
    #define PIN_OLED_DATA 12
#endif

#if defined(ESP32) && defined(ESPDISPLAY)
    #define PIN_OLED_CLOCK 22
    #define PIN_OLED_DATA 21
#endif



// ------- Contante declaration --------------------------------------------------------------------

// Constante pour gérer l'affichage OLED
#ifdef ESPDISPLAY
    // constante pour défnnir les pages d'affichage
    const int pageinfo=0;
    const int pagewifi=1;
    const int pagesensor1=2;
    const int pagesensor2=3;
    // Configuration du timer de rotation de l'affichage
    const long DisplayRotateInterval = 5000;
#endif

// ------- put function declarations here: ---------------------------------------------------------

// Déclaration des fonction pour le Wifi
#ifdef ESP8266
    void onClientConnect(const WiFiEventStationModeConnected &event);
    void onClientDisconnect(const WiFiEventStationModeDisconnected &event);
    void onClientGotIP(const WiFiEventStationModeGotIP &event);
#endif // ESP8266

#ifdef ESP32
    void onClientConnect(WiFiEvent_t event, WiFiEventInfo_t info);
    void onClientDisconnect(WiFiEvent_t event, WiFiEventInfo_t info);
    void onClientGotIP(WiFiEvent_t event, WiFiEventInfo_t info);
#endif // ESP32


// Déclaration des fonction pour l'affichage
#ifdef ESPDISPLAY
  void displayWiFiconnectionInfo(const boolean connected);
  void displayWiFiconnectionStatus(const boolean connected);
#endif // ESPDISPLAY

// ------- Global Variable Déclaration -------------------------------------------------------------
// Déclaration des objects pour la gestion du programme
EspConfigManager *espConfig;
EspConsole *espConsole;
EspWiFiManager *espWiFi;
EspConfigWebserver *WebServer;
WiFiClient *espClient;

#ifdef ESPDISPLAY
  EspDisplay *espDisplay; 
#endif // ESPDISPLAY

boolean WifiConnected = false;


void setup() 
{
    // instancition des objets pour les classe définie dans Esptools
    
    espConsole = new EspConsole();
    espConfig = new EspConfigManager();
    espWiFi = new EspWiFiManager();
    WebServer = new EspConfigWebserver();
    espClient = new WiFiClient();

    #ifdef ESPDISPLAY
        #ifdef ESP32
            espDisplay = new EspDisplay(U8G2_R0,U8X8_PIN_NONE, PIN_OLED_CLOCK, PIN_OLED_DATA);
        #endif
        #ifdef ESP8266
            espDisplay = new EspDisplay(U8G2_R0, PIN_OLED_CLOCK, PIN_OLED_DATA,U8X8_PIN_NONE);
        #endif 
    #endif // ESPDISPLAY

    // Initialisation des objets
    espConfig->setConsole(espConsole);
    espWiFi->setconfig(espConfig);
    espWiFi->setconsole(espConsole);
    WebServer->SetConfig(espConfig);
    WebServer->SetWifi(&WiFi);
    WebServer->SetConsole(espConsole);

    // Chargement de la configuration
    espConfig->load();

    // Initialisation de l'affichage
    #ifdef ESPDISPLAY
        espDisplay->begin();
        espDisplay->setln(pageinfo, ligne_1, "WiFi Disconnected");
        espDisplay->setln(pageinfo, ligne_2, espConfig->getDeviceName().c_str());
        espDisplay->setln(pagewifi, ligne_1, "WiFi Disconnected");
        espDisplay->setln(pagewifi, ligne_2, "No WiFi");
        espDisplay->setln(pagesensor1,ligne_1, "SENSOR 1");
        espDisplay->setln(pagesensor1,ligne_2, "SENSOR 1 OFF");
        espDisplay->setln(pagesensor1,ligne_3, "SENSOR 1 ON");
        espDisplay->setln(pagesensor2,ligne_1, "SENSOR 2");
        espDisplay->setln(pagesensor2,ligne_2, "SENSOR 2 OFF");
        espDisplay->setln(pagesensor2,ligne_3, "SENSOR 2 ON");

        espDisplay->setrotateTime(DisplayRotateInterval);

    #endif // ESPDISPLAY

    // Configuration des Event Handler WiFi
    #ifdef ESP8266
        static WiFiEventHandler onClientConnectedHandler = WiFi.onStationModeConnected(onClientConnect);
        static WiFiEventHandler onClientDisconnectHandler = WiFi.onStationModeDisconnected(onClientDisconnect);
        static WiFiEventHandler onClientGotIPHandler = WiFi.onStationModeGotIP(onClientGotIP);
    #endif // ESP8266

    #ifdef ESP32
        WiFi.onEvent(onClientConnect, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_CONNECTED);
        WiFi.onEvent(onClientDisconnect, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
        WiFi.onEvent(onClientGotIP, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_GOT_IP);
    #endif // ESP32

    // Configuration du WiFi
    espWiFi->setup();
    espWiFi->begin();
    // Déclaration des Event Handler WiFi

    // Configuration du Web serveur pour la configuration
    WebServer->Setup();
    WebServer->begin();

    // Configuration du téléchargement à distance
    if(espConfig->getOTAEnable())
    {
        ArduinoOTA.setPassword(espConfig->getOTAPassword().c_str());
    }
}



void loop() 
{
  long now = millis();
  WebServer->handleClient();
  if (espConfig->getOTAEnable())
    {
      ArduinoOTA.begin();
      ArduinoOTA.handle();
    } 

  if (espWiFi->isConnected())
    {
    #ifdef ESPDISPLAY
        espDisplay->setln(pageinfo, ligne_1, "Wifi Connected");
        espDisplay->setln(pagewifi, ligne_1, "Wifi Connected");
        if (espWiFi->isAccespointactif())
        {
            espDisplay->setln(pageinfo, ligne_4, "Mode Accespoint");
        }
        if (espWiFi->isConnectedAsStation())
        {
            espDisplay->setln(pageinfo, ligne_4, "Mode station");
        }
    #endif // ESPDISPLAY
    }
  else
    {
        #ifdef ESPDISPLAY
            espDisplay->setln(pageinfo, ligne_1, "Wifi Disconnected");
            espDisplay->setln(pagewifi, ligne_1, "Wifi Disconnected");
            espDisplay->setln(pageinfo, ligne_4, "");
        #endif // ESPDISPLAY
    }
    delay(500);
    #ifdef ESPDISPLAY
        espDisplay->handle(ROTATE);
    #endif // ESPDISPLAY
}

#ifdef ESP8266
    void onClientConnect(const WiFiEventStationModeConnected &event)
    {
        // Cette fonction gère les evenment WiFi de conection
        espConsole->println("onConnect : Wifi Connected");
        WifiConnected = true;
    }
    void onClientDisconnect(const WiFiEventStationModeDisconnected &event)
    {
        // Cette fonction gère les évenement de déconection
        espConsole->println("onDisconnect 153 : Wifi Disconnected");
        WifiConnected = false;
    }
    void onClientGotIP(const WiFiEventStationModeGotIP &event)
    {
        // Cette fonction gère les événement d'acquisition de l'adresse IP
        espConsole->println("onGotIP 159 : Wifi GotIP");
        #ifdef ESPDISPLAY
            displayWiFiconnectionInfo(WiFi.isConnected());
        #endif // ESPDISPLAY
        espConsole->begin();
        espConsole->println("");
    
    }
#endif // ESP8266
#ifdef ESP32
    void onClientConnect(WiFiEvent_t event, WiFiEventInfo_t info) 
    {
        espConsole->println("onConnect : Wifi Connected");
        WifiConnected = true;
    }
    void onClientDisconnect(WiFiEvent_t event, WiFiEventInfo_t info) 
    {
        // Cette fonction gère les évenement de déconection
        espConsole->println("onDisconnect 153 : Wifi Disconnected");
        WifiConnected = false;
    }
    void onClientGotIP(WiFiEvent_t event, WiFiEventInfo_t info) 
    {
        // Cette fonction gère les événement d'acquisition de l'adresse IP
        espConsole->println("onGotIP 159 : Wifi GotIP");
        #ifdef ESPDISPLAY
            displayWiFiconnectionInfo(WiFi.isConnected());
        #endif // ESPDISPLAY
        espConsole->begin();
        espConsole->println("");
    }
#endif // ESP32

#ifdef ESPDISPLAY
    void displayWiFiconnectionStatus(const boolean connected)
        {
            if (connected)
            {
                espDisplay->setln(pageinfo, ligne_1, "Wifi Connected");
                espDisplay->setln(pagewifi, ligne_1, "Wifi Connected");
                espDisplay->displayWiFiconnectionbar(WiFi.RSSI());
            }
            else
            {
                espDisplay->setln(pageinfo, ligne_1, "Wifi Disconnected");
                espDisplay->setln(pagewifi, ligne_1, "Wifi Disconnected");
            }
        }

    void displayWiFiconnectionInfo(const boolean connected)
        {
            String IP = "IP  : " + WiFi.localIP().toString();
            String Gateway = "Rtr : " + WiFi.gatewayIP().toString();
            String DNS = "DNS : " + WiFi.dnsIP().toString();
            espDisplay->displayWiFiconnectionbar(WiFi.RSSI());
            espDisplay->setln(pagewifi, ligne_2, IP.c_str());
            espDisplay->setln(pagewifi,ligne_3, Gateway.c_str());
            espDisplay->setln(pagewifi,ligne_4, DNS.c_str());
        }
#endif // ESPDISPLAY
