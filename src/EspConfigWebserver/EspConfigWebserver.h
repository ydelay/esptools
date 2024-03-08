#ifndef ESPCONFIGWEBSERVER_H
#define ESPCONFIGWEBSERVER_H

#ifdef ESP32
    #include <WebServer.h>
    #include <WiFi.h>
#elif defined(ESP8266)
    #include <ESP8266WebServer.h>
    #include <ESP8266WiFi.h>
#else
    #error "Ni ESP32 ni ESP8266 n'est défini"
#endif

#include <Arduino.h>
#include <EspConfigManager.h>
#include <EspConsole.h>
#include <string>
#include <EspConfigPagehtml.h>

class EspConfigWebserver
{

private:

    enum topic {Device,MQTT,WiFi};
    enum subtopic {Info,Scan,Config,Detail,Web};
    boolean _debug = false;
    boolean _espconsoleactive = false;

#ifdef ESP32
    WiFiClass *espWiFi;
    WebServer espWebserver;
#elif defined(ESP8266)
    ESP8266WiFiClass *espWiFi;
    ESP8266WebServer espWebserver;
#endif
    EspConfigManager *espConfig;
    EspConsole *_espconsole;
    // char *webserveruser = "admin";
    // char *webserverpassword = "pwd4admin";

   
    // --------------------------------------------------------------
    // Méthode pour gérer les requêtes HTTP                        --
    // --------------------------------------------------------------

    void handleNotFound();
    void handlecss();
    void handledeviceinfo();
    void handledevicedetail();
    void handledeviceconfig();
    void handledevicesubmit();
    void handlemqttinfo();
    void handlemqttconfig();
    void handlemqttsubmit();
    void handlewifiinfo();
    void handlewifiscan();
    void handlewificonfig();
    void handlewifisubmit();
    
    // --------------------------------------------------------------
    // Méthode pour construire les pages html  ok                  --
    // --------------------------------------------------------------
    String Construire_header(topic headertopic);
    String Construire_deviceheader(subtopic wifitopic);
    String Construire_deviceinfohtml();
    String Construire_devicedetailhtml();
    String Construire_deviceconfightml();
    String Construire_mqttheader(subtopic mqtttopic);
    String Construire_mqttinfohtml();
    String Construire_mqttconfightml();
    String Construire_wifiheader(subtopic wifitopic);
    String Construire_wifiinfohtml();
    String Construire_wifiscanhtml();
    String Construire_wificonfightml();
    String Construire_footer();

public:
    // --------------------------------------------------------------
    // Constructor                                                 --
    // --------------------------------------------------------------

    EspConfigWebserver();

    // --------------------------------------------------------------
    // Méthode pour configurer le Webserver                        --
    // --------------------------------------------------------------

    void Setup();
    void SetConsole(EspConsole *console);
    void SetDebug(boolean debug);
    #ifdef ESP8266
    void SetWifi(ESP8266WiFiClass *wifi);
    #endif
    #ifdef ESP32
    void SetWifi(WiFiClass *wifi);
    #endif
    
    void SetConfig(EspConfigManager *config);


    // --------------------------------------------------------------
    // Méthode pour gérer le webserver                             --
    // --------------------------------------------------------------

    void begin();
    void handleClient();
    void stop();

};
#endif // ESPCONFIGWEBSERVER_H