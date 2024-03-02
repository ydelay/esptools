#ifndef ESPCONFIGWEBSERVER_H
#define ESPCONFIGWEBSERVER_H
#include <Arduino.h>
#include <EspConfigManager.h>
#include <EspConsole.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <string>
#include <EspConfigPagehtml.h>

class EspConfigWebserver
{

private:

    enum topic {Device,MQTT,WiFi};
    enum subtopic {Info,Scan,Config,Detail,Web};

    ESP8266WiFiClass *espWiFi;
    EspConfigManager *espConfig;
    ESP8266WebServer espWebserver;
    EspConsole *console;
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
    void SetWifi(ESP8266WiFiClass *wifi);
    void SetConfig(EspConfigManager *config);


    // --------------------------------------------------------------
    // Méthode pour gérer le webserver                             --
    // --------------------------------------------------------------

    void begin();
    void handleClient();
    void stop();

};
#endif // ESPCONFIGWEBSERVER_H