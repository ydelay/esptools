#include <EspConfigWebserver.h>
#include <esp_ota_ops.h>
#include <esp_partition.h>


// --------------------------------------------------------------
// Constructor  -  Initialize the webserver                    --
// --------------------------------------------------------------

EspConfigWebserver::EspConfigWebserver()
{
    _espconsole = nullptr;
    _espconsoleactive = false;
    espWiFi = nullptr;
    espConfig = nullptr;
}

// --------------------------------------------------------------
// Méthode pour gére le Webserver                              --
// --------------------------------------------------------------

void EspConfigWebserver::Setup()
{
    espWebserver.on("/", HTTP_GET, std::bind(&EspConfigWebserver::handledeviceinfo, this));
    espWebserver.on("/index.html", HTTP_GET, std::bind(&EspConfigWebserver::handledeviceinfo, this));
    espWebserver.on("/w3.css", HTTP_GET, std::bind(&EspConfigWebserver::handlecss, this));
    espWebserver.on("/device", HTTP_GET, std::bind(&EspConfigWebserver::handledeviceinfo, this));
    espWebserver.on("/device/info", HTTP_GET, std::bind(&EspConfigWebserver::handledeviceinfo, this));
    espWebserver.on("/device/detail", HTTP_GET, std::bind(&EspConfigWebserver::handledevicedetail, this));
    espWebserver.on("/device/config", HTTP_GET, std::bind(&EspConfigWebserver::handledeviceconfig, this));
    espWebserver.on("/device/submit", HTTP_POST, std::bind(&EspConfigWebserver::handledevicesubmit, this));
    espWebserver.on("/mqtt", HTTP_GET, std::bind(&EspConfigWebserver::handlemqttinfo, this));
    espWebserver.on("/mqtt/info", HTTP_GET, std::bind(&EspConfigWebserver::handlemqttinfo, this));
    espWebserver.on("/mqtt/config", HTTP_GET, std::bind(&EspConfigWebserver::handlemqttconfig, this));
    espWebserver.on("/mqtt/submit", HTTP_POST, std::bind(&EspConfigWebserver::handlemqttsubmit, this));
    espWebserver.on("/wifi", HTTP_GET, std::bind(&EspConfigWebserver::handlewifiinfo, this));
    espWebserver.on("/wifi/info", HTTP_GET, std::bind(&EspConfigWebserver::handlewifiinfo, this));
    espWebserver.on("/wifi/scan", HTTP_GET, std::bind(&EspConfigWebserver::handlewifiscan, this));
    espWebserver.on("/wifi/config", HTTP_GET, std::bind(&EspConfigWebserver::handlewificonfig, this));
    espWebserver.on("/wifi/submit", HTTP_POST, std::bind(&EspConfigWebserver::handlewifisubmit, this));
}

void EspConfigWebserver::SetConsole(EspConsole *console)
{
    this->_espconsole = console;
    this->_espconsoleactive = true;
}

void EspConfigWebserver::SetDebug(boolean debug)
{
    _debug = debug;
}

#ifdef ESP32
    void EspConfigWebserver::SetWifi(WiFiClass *wifi)
    {
        espWiFi = wifi;
    }
#elif defined(ESP8266)
    void EspConfigWebserver::SetWifi(ESP8266WiFiClass *wifi)
    {
        espWiFi = wifi;
    }
#endif

void EspConfigWebserver::SetConfig(EspConfigManager *config)
{
    espConfig = config;
}

// --------------------------------------------------------------
// Méthode pour gérer le webserver                             --
// --------------------------------------------------------------

void EspConfigWebserver::begin()
{   
    espWebserver.begin(espConfig->getWEBPort());
}

void EspConfigWebserver::handleClient()
{
    espWebserver.handleClient();
}

void EspConfigWebserver::stop()
{
    espWebserver.stop();
}

// --------------------------------------------------------------
// Méthode pour gérer les requêtes HTTP                        --
// --------------------------------------------------------------

void EspConfigWebserver::handleNotFound() // OK adapted
{
    if (!espWebserver.authenticate(espConfig->getWEBUser().c_str(), espConfig->getWEBPassword().c_str())) {
      return espWebserver.requestAuthentication();
    }
    espWebserver.send(404, "text/plain", "Page not found\n");
}

void EspConfigWebserver::handlecss() // OK adapted
{
  
    String lw3css(reinterpret_cast<const __FlashStringHelper *>(w3css));
    espWebserver.send(200, "text/css", lw3css);
}


void EspConfigWebserver::handledeviceinfo() // OK adapted
{
    if (!espWebserver.authenticate(espConfig->getWEBUser().c_str(), espConfig->getWEBPassword().c_str())) {
      return espWebserver.requestAuthentication();
    }
    _debug & _espconsoleactive ? _espconsole->println("handledeviceinfo : Start"):0;
    String pagehtml(Construire_deviceinfohtml());
    espWebserver.send(200, "text/html", pagehtml);
    _debug & _espconsoleactive ? _espconsole->println("handledeviceinfo : finished"):0;
}

void EspConfigWebserver::handledevicedetail()
{
    if (!espWebserver.authenticate(espConfig->getWEBUser().c_str(), espConfig->getWEBPassword().c_str())) {
      return espWebserver.requestAuthentication();
    }
    _debug & _espconsoleactive ? _espconsole->println("handledevicedetail : Start"):0;
    String pagehtml(Construire_devicedetailhtml());
    espWebserver.send(200, "text/html", pagehtml);
    _debug & _espconsoleactive ? _espconsole->println("handledevicedetail : finished"):0;

}

void EspConfigWebserver::handledeviceconfig()
{
    if (!espWebserver.authenticate(espConfig->getWEBUser().c_str(), espConfig->getWEBPassword().c_str())) {
      return espWebserver.requestAuthentication();
    }

    _debug & _espconsoleactive ? _espconsole->println("handledeviceconfig : Start"):0;
    String pagehtml(Construire_deviceconfightml());
    espWebserver.send(200, "text/html", pagehtml);
    _debug & _espconsoleactive ? _espconsole->println("handledeviceconfig : finished"):0;

}

void EspConfigWebserver::handledevicesubmit()
{
    // devicename: 13737612     espConfig.setDeviceName()
    // devicelocation:          espConfig.setDeviceLocation()
    // devicedescription:       espConfig.setDeviceDescription()
    // webuser: admin           espConfig.setWEBUser()
    // webpassword: pwd4admin   espConfig.setWEBPassword()
    // webport: 8080            espConfig.setWEBPort()
    // otapassword:             espConfig.setOTAPassword()
    // otaenable: on            espConfig.setOTAActivate()
    // otaport: 8266            espConfig.setOTAPort()

    if (!espWebserver.authenticate(espConfig->getWEBUser().c_str(), espConfig->getWEBPassword().c_str())) {
      return espWebserver.requestAuthentication();
    }

    if (espWebserver.hasArg("devicename") && espWebserver.hasArg("devicelocation") && espWebserver.hasArg("devicedescription"))
    {
        // devicename: 13737612     espConfig.setDeviceName()
        // devicelocation:          espConfig.setDeviceLocation()
        // devicedescription:       espConfig.setDeviceDescription()
        _debug & _espconsoleactive ? _espconsole->println("handledevicesubmit : devicename     = " + espWebserver.arg("devicename")):0;
        _debug & _espconsoleactive ? _espconsole->println("handledevicesubmit : devicelocation     = " + espWebserver.arg("devicelocation")):0;
        _debug & _espconsoleactive ? _espconsole->println("handledevicesubmit : devicedescription = " + espWebserver.arg("devicedescription")):0;
        espConfig->setDeviceName(espWebserver.arg("devicename").c_str());
        espConfig->setDeviceLocation(espWebserver.arg("devicelocation").c_str());
        espConfig->setDeviceDescription(espWebserver.arg("devicedescription").c_str());
    }

    if (espWebserver.hasArg("webuser") && espWebserver.hasArg("webpassword") && espWebserver.hasArg("webport"))
    {
        // webuser: admin           espConfig.setWEBUser()
        // webpassword: pwd4admin   espConfig.setWEBPassword()
        // webport: 8080            espConfig.setWEBPort()
        _debug & _espconsoleactive ? _espconsole->println("handledevicesubmit : webuser     = " + espWebserver.arg("webuser")):0;
        _debug & _espconsoleactive ? _espconsole->println("handledevicesubmit : webpassword     = " + espWebserver.arg("webpassword")):0;
        _debug & _espconsoleactive ? _espconsole->println("handledevicesubmit : webport = " + espWebserver.arg("webport")):0;
        espConfig->setWEBUser(espWebserver.arg("webuser").c_str());
        espConfig->setWEBPassword(espWebserver.arg("webpassword").c_str());
        espConfig->setWEBPort(espWebserver.arg("webport").toInt());
    }


    // otapassword:             espConfig.setOTAPassword()
    // otaport: 8266            espConfig.setOTAPort()
    if (espWebserver.hasArg("otapassword") && espWebserver.hasArg("otaport"))
    {
        _debug & _espconsoleactive ? _espconsole->println("handledevicesubmit : otapassword = " + espWebserver.arg("otapassword")):0;
        _debug & _espconsoleactive ? _espconsole->println("handledevicesubmit : otaport = " + espWebserver.arg("otaport")):0;
        espConfig->setOTAPassword(espWebserver.arg("otapassword").c_str());
        espConfig->setOTAPort(espWebserver.arg("otaport").toInt());

    }

    // otaenable: on            espConfig.setOTAActivate()
    if (espWebserver.hasArg("otaenable"))
    {
        _debug & _espconsoleactive ? _espconsole->println("handledevicesubmit : otaenable     = " + espWebserver.arg("otaenable")):0;
        if (espWebserver.arg("otaenable") == "on")
        {
            espConfig->setOTAEnable(true);
            _debug & _espconsoleactive ? _espconsole->println("handledevicesubmit : otaenable saved as true"):0;
            if (espConfig->getOTAEnable())
            {
                _debug & _espconsoleactive ? _espconsole->println("handledevicesubmit : otaenable still as true"):0;
            }
        }
        else
        {
            espConfig->setOTAEnable(false);
            _debug & _espconsoleactive ? _espconsole->println("handledevicesubmit : otaenable saved as false"):0;
        }
    }
    else
    {
        espConfig->setOTAEnable(false);
        _debug & _espconsoleactive ? _espconsole->println("handledevicesubmit : otaenable saved as false"):0;
    }


    espConfig->save();
    String strconfig = "POST completed : \n\n";
    espWebserver.send(200, "text/plain", strconfig);

}

void EspConfigWebserver::handlemqttinfo()
{
    if (!espWebserver.authenticate(espConfig->getWEBUser().c_str(), espConfig->getWEBPassword().c_str())) {
      return espWebserver.requestAuthentication();
    }
    _debug & _espconsoleactive ? _espconsole->println("handlemqttinfo : Start"):0;
    String pagehtml(Construire_mqttinfohtml());
    espWebserver.send(200, "text/html", pagehtml);
}

void EspConfigWebserver::handlemqttconfig()
{
    if (!espWebserver.authenticate(espConfig->getWEBUser().c_str(), espConfig->getWEBPassword().c_str())) {
      return espWebserver.requestAuthentication();
    }
    _debug & _espconsoleactive ? _espconsole->println("handlemqttconfig : Start"):0;
    String pagehtml(Construire_mqttconfightml());
    espWebserver.send(200, "text/html", pagehtml);
}

// mqttserverip: (IP unset)            espConfig->setMQTTServer()
// mqttport: 0                         espConfig->setMQTTPort()
// mqttuser:                           espConfig->setMQTTUser()
// mqttpassword: <!--%PASSWORD%-->     espConfig->setMQTTPassword()

void EspConfigWebserver::handlemqttsubmit()
{
    _debug & _espconsoleactive ? _espconsole->println("handlemqttsubmit : Start"):0;
    IPAddress l_IP;
    if (!espWebserver.authenticate(espConfig->getWEBUser().c_str(), espConfig->getWEBPassword().c_str())) {
      return espWebserver.requestAuthentication();
    }

    // mqttuser:                           espConfig->setMQTTUser()
    // mqttpassword: <!--%PASSWORD%-->     espConfig->setMQTTPassword()
    if (espWebserver.hasArg("mqttuser") && espWebserver.hasArg("mqttpassword"))
    {
        // Utilisez ssid et password ici
        _debug & _espconsoleactive ? _espconsole->println("handlemqttsubmit : mqttuser     = " + espWebserver.arg("mqttuser")):0;
        _debug & _espconsoleactive ? _espconsole->println("handlemqttsubmit : mqttpassword = " + espWebserver.arg("mqttpassword")):0;
        espConfig->setMQTTUser(espWebserver.arg("mqttuser").c_str());
        espConfig->setMQTTPassword(espWebserver.arg("mqttpassword").c_str());
    }

    // mqttport: 0                         espConfig->setMQTTPort()
    if (espWebserver.hasArg("mqttport"))
    {
        _debug & _espconsoleactive ? _espconsole->println("handlemqttsubmit : mqttport = " + espWebserver.arg("mqttport")):0;
        espConfig->setMQTTPort(espWebserver.arg("mqttport").toInt());

    }

    if (espWebserver.hasArg("mqttserverip"))
    {
        // Utilisez mqttserverip ici
        _debug & _espconsoleactive ? _espconsole->println("handlemqttsubmit : mqttserverip      = " + espWebserver.arg("mqttserverip")):0;
        // mqttserverip: (IP unset)            espConfig->setMQTTServer()
        if (espWebserver.arg("mqttserverip") == "(IP unset)")
        {
            l_IP.fromString("0.0.0.0");
            espConfig->setMQTTServer(l_IP);
        }
        else
        {
            l_IP.fromString(espWebserver.arg("mqttserverip"));
            espConfig->setMQTTServer(l_IP);
        }
    }
    espConfig->save();
    String strconfig = "POST completed : \n\n";
    espWebserver.send(200, "text/plain", strconfig);
    _debug & _espconsoleactive ? _espconsole->println("handlemqttsubmit : End"):0;

}

void EspConfigWebserver::handlewifiinfo()
{
    if (!espWebserver.authenticate(espConfig->getWEBUser().c_str(), espConfig->getWEBPassword().c_str())) {
      return espWebserver.requestAuthentication();
    }
    _debug & _espconsoleactive ? _espconsole->println("handlewifiinfo : Start"):0;
    String pagehtml(Construire_wifiinfohtml());
    espWebserver.send(200, "text/html", pagehtml);
    _debug & _espconsoleactive ? _espconsole->println("handlewifiinfo : finished"):0;
}

void EspConfigWebserver::handlewifiscan()
{
    if (!espWebserver.authenticate(espConfig->getWEBUser().c_str(), espConfig->getWEBPassword().c_str())) {
      return espWebserver.requestAuthentication();
    }
    _debug & _espconsoleactive ? _espconsole->println("handlewifiscan : Start"):0;
    String pagehtml(Construire_wifiscanhtml());
    espWebserver.send(200, "text/html", pagehtml);
    _debug & _espconsoleactive ? _espconsole->println("handlewifiscan : finished"):0;
}

void EspConfigWebserver::handlewificonfig()
{
    if (!espWebserver.authenticate(espConfig->getWEBUser().c_str(), espConfig->getWEBPassword().c_str())) {
      return espWebserver.requestAuthentication();
    }
    _debug & _espconsoleactive ? _espconsole->println("handlewificonfig : Start"):0;
    String pagehtml(Construire_wificonfightml());
    espWebserver.send(200, "text/html", pagehtml);
    _debug & _espconsoleactive ? _espconsole->println("handlewificonfig : finished"):0;
}

void EspConfigWebserver::handlewifisubmit() // OK adapted
{
    // Réponse envoyée
    // "STAssid": "delayfamilyUPC",           espConfig->setClientWiFiSSID()
    // "STApassword": "wifipassword",         espConfig->setClientWiFiPassword()
    // "stamode": "active",                   espConfig->setClientWiFiToActivate()
    // "stadhcp": "checked",                  !espConfig->setClientWiFiManualIP()
    // "STAadress": "192.168.0.130",          espConfig->setClientAdresse()
    // "STAsubnet": "255.255.255.0",          espConfig->setClientSubnet()
    // "STAgateway": "192.168.0.1",           espConfig->setClientGateway()
    // "STAdns": "192.168.0.1",               espConfig->setClientDNS()
    // "APssid": "ESP8266-OLED-Test1+WiFi",   espConfig->setAccesspointWiFiSSID()
    // "APpassword": "apwifi",                espConfig->setAccesspointWiFiPassword()
    // "apmode": "active",                    espConfig->setAccesspointWiFiToActivate()
    // "IPdefault": "checked",                !espConfig->setAccesspointWiFiManualIP()
    // "APadress": "192.168.10.1",            espConfig->setAccesspointAdresse()
    // "APsubnet": "255.255.255.0",           espConfig->setAccesspointSubnet()
    // "APgateway": "192.168.10.1",           espConfig->setAccesspointGateway()
    // "APdns": "192.168.10.1"                espConfig->setAccesspointDNS()

    // "STAssid": "delayfamilyUPC",           espConfig->setClientWiFiSSID()
    // "STApassword": "wifipassword",         espConfig->setClientWiFiPassword()

    IPAddress l_IP;
    if (!espWebserver.authenticate(espConfig->getWEBUser().c_str(), espConfig->getWEBPassword().c_str())) {
      return espWebserver.requestAuthentication();
    }
    if (espWebserver.hasArg("STAssid") && espWebserver.hasArg("STApassword"))
    {
        // Utilisez ssid et password ici
        _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : STAssid     = " + espWebserver.arg("STAssid")):0;
        _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : STApassword = " + espWebserver.arg("STApassword")):0;
        espConfig->setClientWiFiSSID(espWebserver.arg("STAssid").c_str());
        espConfig->setClientWiFiPassword(espWebserver.arg("STApassword").c_str());
    }

    // "stamode": "active",                   espConfig->setClientWiFiToActivate()
    if (espWebserver.hasArg("stamode"))
    {
        _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : stamode     = " + espWebserver.arg("stamode")):0;
        if (espWebserver.arg("stamode") == "active")
        {
            espConfig->setClientWiFiToActivate(true);
            _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : stamode saved as true"):0;
            if (espConfig->getClientWiFiToActivate())
            {
                _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : stamode still as true"):0;
            }
        }
        else
        {
            espConfig->setClientWiFiToActivate(false);
            _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : stamode saved as false"):0;
        }
    }
    else
    {
        espConfig->setClientWiFiToActivate(false);
        _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : stamode saved as false"):0;
    }

    // "stadhcp": "checked",                  !espConfig->setClientWiFiManualIP()
    if (espWebserver.hasArg("stadhcp"))
    {
        _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : stadhcp     = " + espWebserver.arg("stadhcp")):0;
        if (espWebserver.arg("stadhcp") == "checked")
        {
            espConfig->setClientWiFiManualIP(false);
            _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : stadhcp saved as false"):0;
        }
        else
        {
            espConfig->setClientWiFiManualIP(true);
            _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : stadhcp saved as true"):0;
        }
    }
    else
    {
        espConfig->setClientWiFiManualIP(true);
        _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : stadhcp saved as true"):0;
    }

    // "STAadress": "192.168.0.130",          espConfig->setClientAdresse()
    // "STAsubnet": "255.255.255.0",          espConfig->setClientSubnet()
    // "STAgateway": "192.168.0.1",           espConfig->setClientGateway()
    // "STAdns": "192.168.0.1",               espConfig->setClientDNS()
    if (espWebserver.hasArg("STAadress") && espWebserver.hasArg("STAsubnet") && espWebserver.hasArg("STAgateway") && espWebserver.hasArg("STAdns"))
    {
        // Utilisez adresse, subnet, gateway et dns ici
        _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : STAadress   = " + espWebserver.arg("STAadress")):0;
        _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : STAsubnet   = " + espWebserver.arg("STAsubnet")):0;
        _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : STAgateway  = " + espWebserver.arg("STAgateway")):0;
        _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : STAdns      = " + espWebserver.arg("STAdns")):0;
        // "STAadress": "192.168.0.130",          espConfig->setClientAdresse()
        if (espWebserver.arg("STAadress") == "(IP unset)")
        {
            l_IP.fromString("0.0.0.0");
            espConfig->setClientAdresse(l_IP);
        }
        else
        {
            l_IP.fromString(espWebserver.arg("STAadress"));
            espConfig->setClientAdresse(l_IP);
        }
        // "STAsubnet": "255.255.255.0",          espConfig->setClientSubnet()
        if (espWebserver.arg("STAsubnet") == "(IP unset)")
        {
            l_IP.fromString("0.0.0.0");
            espConfig->setClientSubnet(l_IP);
        }
        else
        {
            l_IP.fromString(espWebserver.arg("STAsubnet"));
            espConfig->setClientSubnet(l_IP);
        }
        // "STAgateway": "192.168.0.1",           espConfig->setClientGateway()
        if (espWebserver.arg("STAgateway") == "(IP unset)")
        {
            l_IP.fromString("0.0.0.0");
            espConfig->setClientGateway(l_IP);
        }
        else
        {
            l_IP.fromString(espWebserver.arg("STAgateway"));
            espConfig->setClientGateway(l_IP);
        }
        // "STAdns": "192.168.0.1",               espConfig->setClientDNS()
        if (espWebserver.arg("STAdns") == "(IP unset)")
        {
            l_IP.fromString("0.0.0.0");
            espConfig->setClientDNS(l_IP);
        }
        else
        {
            l_IP.fromString(espWebserver.arg("STAdns"));
            espConfig->setClientDNS(l_IP);
        }
    }

    // "APssid": "ESP8266-OLED-Test1+WiFi",   espConfig->setAccesspointWiFiSSID()
    // "APpassword": "apwifi",                espConfig->setAccesspointWiFiPassword()
    if (espWebserver.hasArg("APssid") && espWebserver.hasArg("APpassword"))
    {
        // Utilisez APssid et APpassword ici
        _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : APssid      = " + espWebserver.arg("APssid")):0;
        _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : APpassword  = " + espWebserver.arg("APpassword")):0;
        espConfig->setAccesspointWiFiSSID(espWebserver.arg("APssid").c_str());
        espConfig->setAccesspointWiFiPassword(espWebserver.arg("APpassword").c_str());
    }

    // "apmode": "active",                    espConfig->setAccesspointWiFiToActivate()
    if (espWebserver.hasArg("apmode"))
    {
        _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : apmode      = " + espWebserver.arg("apmode")):0;
        // Utilisez apmode ici
        if (espWebserver.arg("apmode") == "active")
        {
            espConfig->setAccesspointWiFiToActivate(true);
            _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : apmode saved as true"):0;
        }
        else
        {
            espConfig->setAccesspointWiFiToActivate(false);
            _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : apmode saved as false"):0;
        }
    }
    else
    {
        espConfig->setAccesspointWiFiToActivate(false);
        _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : apmode saved as false"):0;
    }

    // "IPdefault": "checked",                !espConfig->setAccesspointWiFiManualIP()
    if (espWebserver.hasArg("IPdefault"))
    {
        _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : IPdefault   = " + espWebserver.arg("IPdefault")):0;
        // Utilisez IPdefault ici
        if (espWebserver.arg("IPdefault") == "checked")
        {
            espConfig->setAccesspointWiFiManualIP(false);
            _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : IPdefault saved as false"):0;
        }
        else
        {
            espConfig->setAccesspointWiFiManualIP(true);
            _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : IPdefault saved as true"):0;
        }
    }
    else
    {
        espConfig->setAccesspointWiFiManualIP(true);
        _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : IPdefault saved as true"):0;
    }

    // "APadress": "192.168.10.1",            espConfig->setAccesspointAdresse()
    // "APsubnet": "255.255.255.0",           espConfig->setAccesspointSubnet()
    // "APgateway": "192.168.10.1",           espConfig->setAccesspointGateway()
    // "APdns": "192.168.10.1"                espConfig->setAccesspointDNS()
    if (espWebserver.hasArg("APadress") && espWebserver.hasArg("APsubnet") && espWebserver.hasArg("APgateway") && espWebserver.hasArg("APdns"))
    {

        // Utilisez adresse, subnet, gateway et dns ici

        _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : APadress    = " + espWebserver.arg("APadress")):0;
        _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : APsubnet    = " + espWebserver.arg("APsubnet")):0;
        _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : APgateway   = " + espWebserver.arg("APgateway")):0;
        _debug & _espconsoleactive ? _espconsole->println("handleFormWiFiconfig : APdns       = " + espWebserver.arg("APdns")):0;

        // "APadress": "192.168.10.1",            espConfig->setAccesspointAdresse()
        if (espWebserver.arg("APadress") == "(IP unset)")
        {
            l_IP.fromString("0.0.0.0");
            espConfig->setAccesspointAdresse(l_IP);
        }
        else
        {
            l_IP.fromString(espWebserver.arg("APadress"));
            espConfig->setAccesspointAdresse(l_IP);
        }
        // "APsubnet": "255.255.255.0",           espConfig->setAccesspointSubnet()
        if (espWebserver.arg("APsubnet") == "(IP unset)")
        {
            l_IP.fromString("0.0.0.0");
            espConfig->setAccesspointSubnet(l_IP);
        }
        else
        {
            l_IP.fromString(espWebserver.arg("APsubnet"));
            espConfig->setAccesspointSubnet(l_IP);
        }
        // "APgateway": "192.168.10.1",           espConfig->setAccesspointGateway()
        if (espWebserver.arg("APgateway") == "(IP unset)")
        {
            l_IP.fromString("0.0.0.0");
            espConfig->setAccesspointGateway(l_IP);
        }
        else
        {
            l_IP.fromString(espWebserver.arg("APgateway"));
            espConfig->setAccesspointGateway(l_IP);
        }
        // "APdns": "192.168.10.1"                espConfig->setAccesspointDNS()
        if (espWebserver.arg("APdns") == "(IP unset)")
        {
            l_IP.fromString("0.0.0.0");
            espConfig->setAccesspointDNS(l_IP);
        }
        else
        {
            l_IP.fromString(espWebserver.arg("APdns"));
            espConfig->setAccesspointDNS(l_IP);
        }
    }
    espConfig->save();
    String strconfig = "POST completed : \n\n";
    espWebserver.send(200, "text/plain", strconfig);
}


// --------------------------------------------------------------
// Méthode pour créer les pages html                           --
// --------------------------------------------------------------

String EspConfigWebserver::Construire_header(topic headertopic) // OK adapted
{
    String header(reinterpret_cast<const __FlashStringHelper *>(header_html));
    String str;
    str = espConfig->getDeviceName().c_str();
    header.replace("<!--%DEVICENAME%-->", str.c_str());
    switch (headertopic)
    {
    case topic::Device:
        header.replace("<!--%DEVICECOLOR%-->", "w3-blue");
        header.replace("<!--%MQTTCOLOR%-->", "w3-light-blue");
        header.replace("<!--%WIFICOLOR%-->", "w3-light-blue");
        break;
    case topic::MQTT:
        header.replace("<!--%DEVICECOLOR%-->", "w3-light-blue");
        header.replace("<!--%MQTTCOLOR%-->", "w3-blue");
        header.replace("<!--%WIFICOLOR%-->", "w3-light-blue");
        break;
    case topic::WiFi:
        header.replace("<!--%DEVICECOLOR%-->", "w3-light-blue");
        header.replace("<!--%MQTTCOLOR%-->", "w3-light-blue");
        header.replace("<!--%WIFICOLOR%-->", "w3-blue");
        break;
    }
    return header;
}


String EspConfigWebserver::Construire_deviceheader(subtopic wifitopic)
{
    String header(reinterpret_cast<const __FlashStringHelper *>(header_device_html));
    switch (wifitopic)
    {
    case subtopic::Info:
        header.replace("<!--%COLORINFO%-->", "w3-blue");
        header.replace("<!--%COLORDETAIL%-->", "w3-light-blue");
        header.replace("<!--%COLORCONFIG%-->", "w3-light-blue");
        break;
    case subtopic::Detail:
        header.replace("<!--%COLORINFO%-->", "w3-light-blue");
        header.replace("<!--%COLORDETAIL%-->", "w3-blue");
        header.replace("<!--%COLORCONFIG%-->", "w3-light-blue");
        break;
    case subtopic::Config:
        header.replace("<!--%COLORINFO%-->", "w3-light-blue");
        header.replace("<!--%COLORDETAIL%-->", "w3-light-blue");
        header.replace("<!--%COLORCONFIG%-->", "w3-blue");
        break;
    default:
        header.replace("<!--%COLORINFO%-->", "w3-light-blue");
        header.replace("<!--%COLORDETAIL%-->", "w3-light-blue");
        header.replace("<!--%COLORCONFIG%-->", "w3-light-blue");
        break;
    }
    return header;
}

// <!--%DEVICENAME%-->        : Config.getDeviceName()
// <!--%DEVICEID%-->          : ESP.getChipId()
// <!--%DEVICELOCATION-->     : Config.getDeviceLocation()
// <!--%DEVICEDESCRIPTION%--> : Config.getDeviceDescription()
// <!--%DEVICEVCC%-->         : ESP.getVcc()
// <!--%DEVICELASTRESET%-->   : ESP.getResetReason()
// <!--%WEBUSER%-->           : espConfig->getWEBUser().c_str()
// <!--%WEBPASSWORD%-->       : Config.getWebPassword()
// <!--%WEBPORT%-->           : Config.getWebPort()
// <!--%WEBSTATUS%-->         : Webserver.status()
// <!--%COREVERSION%-->       : ESP.getCoreVersion()
// <!--%SDKVERSION%-->        : ESP.getSdkVersion()    
// <!--%FLASHSTATUS%-->       : ESP.checkFlashCRC()
// <!--%OTAACTIVATED%-->      : Config.getOTAActivate()
// <!--%OTAPASSWORD%-->       : Config.getOTAPassword()

String EspConfigWebserver::Construire_deviceinfohtml(){   
    #ifdef ESP8266
        uint16_t vcc = ESP.getVcc();
        float fvcc = vcc / 1024;
        String strvcc = String(fvcc, 2);
    #elif defined(ESP32)
        esp_chip_info_t chip_info;
        esp_chip_info(&chip_info);
        String strvcc = "N/A";
    #endif
    String page  = Construire_header(topic::Device);
    page += Construire_deviceheader(subtopic::Info);
    page += String(reinterpret_cast<const __FlashStringHelper *>(device_info_html));
    page.replace("<!--%DEVICENAME%-->", espConfig->getDeviceName().c_str());
    #ifdef ESP8266
        page.replace("<!--%DEVICEID%-->", String(ESP.getChipId()).c_str());
    #elif defined(ESP32)
        page.replace("<!--%DEVICEID%-->", "N/A");
    #endif
    page.replace("<!--%DEVICELOCATION%-->", espConfig->getDeviceLocation().c_str());
    page.replace("<!--%DEVICEDESCRIPTION%-->", espConfig->getDeviceDescription().c_str());
    page.replace("<!--%DEVICEVCC%-->", strvcc);
    #ifdef ESP8266
        page.replace("<!--%DEVICELASTRESET%-->", ESP.getResetReason().c_str());
    #elif defined(ESP32)
        esp_reset_reason_t reset_reason = esp_reset_reason();
        const char* reset_reason_str = "";
        switch (reset_reason) {
            case ESP_RST_POWERON: reset_reason_str = "Power on"; break;
            case ESP_RST_EXT: reset_reason_str = "External reset"; break;
            case ESP_RST_SW: reset_reason_str = "Software reset"; break;
            case ESP_RST_PANIC: reset_reason_str = "Software panic"; break;
            case ESP_RST_INT_WDT: reset_reason_str = "Interrupt watchdog"; break;
            case ESP_RST_TASK_WDT: reset_reason_str = "Task watchdog"; break;
            case ESP_RST_WDT: reset_reason_str = "Other watchdog"; break;
            case ESP_RST_DEEPSLEEP: reset_reason_str = "Deep sleep"; break;
            case ESP_RST_BROWNOUT: reset_reason_str = "Brownout"; break;
            case ESP_RST_SDIO: reset_reason_str = "SDIO"; break;
            default: reset_reason_str = "Unknown"; break;
        }
        page.replace("<!--%DEVICELASTRESET%-->", reset_reason_str);
    #endif
    page.replace("<!--%WEBUSER%-->", espConfig->getWEBUser().c_str());
    page.replace("<!--%WEBPASSWORD%-->", espConfig->getWEBPassword().c_str());
    page.replace("<!--%WEBPORT%-->", String(espConfig->getWEBPort()));
    page.replace("<!--%WEBSTATUS%-->",  "Running");
    #ifdef ESP8266
        page.replace("<!--%COREVERSION%-->", ESP.getCoreVersion().c_str());
        page.replace("<!--%SDKVERSION%-->", String(ESP.getSdkVersion()));
        page.replace("<!--%FLASHSTATUS%-->", ESP.checkFlashCRC() ? "OK" : "KO");
    #elif defined(ESP32)

        page.replace("<!--%COREVERSION%-->", String(chip_info.revision).c_str());
        page.replace("<!--%SDKVERSION%-->", esp_get_idf_version());
        const esp_partition_t *running = esp_ota_get_running_partition();
        uint8_t sha_256[ESP_PARTITION_HASH_LEN];
        if (esp_partition_get_sha256(running, sha_256) == ESP_OK) 
        {
            page.replace("<!--%FLASHSTATUS%-->", "OK");
        } 
        else 
        {
            page.replace("<!--%FLASHSTATUS%-->", "KO");
        }
 
    #endif
    page.replace("<!--%OTAACTIVATED%-->", espConfig->getOTAEnable() ? "Activated" : "Deactivated");
    page.replace("<!--%OTAPASSWORD%-->", espConfig->getOTAPassword().c_str());
    page.replace("<!--%OTAPORT%-->", String(espConfig->getOTAPort()));
    page += Construire_footer();
    return page;
}

// <!--%FREEHEAP%-->           : ESP.getFreeHeap()
// <!--%HEAPFRAGMENTATION%-->  : ESP.getHeapFragmentation()
// <!--%HEAPMAXFREEBLOCK%-->   : ESP.getMaxFreeBlockSize() 
// <!--%FLASHCHIPID%-->        : ESP.getFlashChipId()
// <!--%FLASHCHIPSIZE%-->      : ESP.getFlashChipSize()
// <!--%FLASHREALSIZE%-->      : ESP.getFlashChipRealSize()
// <!--%FLASHCIPSPEED%-->      : ESP.getFlashChipSpeed()
// <!--%SKETCHSIZE%-->         : ESP.getSketchSize()
// <!--%SKETCHFREESPACE%-->    : ESP.getFreeSketchSpace()
// <!--%SKETCHMD5%-->          : ESP.getSketchMD5()

String EspConfigWebserver::Construire_devicedetailhtml()
{
    String page = Construire_header(topic::Device);
    page += Construire_deviceheader(subtopic::Detail);
    page += String(reinterpret_cast<const __FlashStringHelper *>(device_detail_html));
    #ifdef ESP8266
        page.replace("<!--%FREEHEAP%-->", String(ESP.getFreeHeap()));
        page.replace("<!--%HEAPFRAGMENTATION%-->", String(ESP.getHeapFragmentation()));
        page.replace("<!--%HEAPMAXFREEBLOCK%-->", String(ESP.getMaxFreeBlockSize()));
        page.replace("<!--%FLASHCHIPID%-->", String(ESP.getFlashChipId()));
        page.replace("<!--%FLASHCHIPSIZE%-->", String(ESP.getFlashChipSize()));
        page.replace("<!--%FLASHREALSIZE%-->", String(ESP.getFlashChipRealSize()));
        page.replace("<!--%FLASHCIPSPEED%-->", String(ESP.getFlashChipSpeed()));
        page.replace("<!--%SKETCHSIZE%-->", String(ESP.getSketchSize()));
        page.replace("<!--%SKETCHFREESPACE%-->", String(ESP.getFreeSketchSpace()));
        page.replace("<!--%SKETCHMD5%-->", ESP.getSketchMD5().c_str());
    #elif defined(ESP32)
        page.replace("<!--%FREEHEAP%-->", String(esp_get_free_heap_size()));
        page.replace("<!--%HEAPFRAGMENTATION%-->", String(heap_caps_get_free_size(MALLOC_CAP_8BIT)));
        page.replace("<!--%HEAPMAXFREEBLOCK%-->", String(esp_get_minimum_free_heap_size()));
        page.replace("<!--%FLASHCHIPID%-->", String(ESP.getEfuseMac()));
        page.replace("<!--%FLASHCHIPSIZE%-->", String(ESP.getFlashChipSize()));
        page.replace("<!--%FLASHCHIPSIZE%-->", String(ESP.getFlashChipSize()));
        page.replace("<!--%FLASHCIPSPEED%-->", String(ESP.getFlashChipSpeed()));
        const esp_partition_t *running_partition = esp_ota_get_running_partition();
        if (running_partition != NULL) 
        {
            // Obtenir la taille de la partition
            size_t sketch_size = running_partition->size;
            page.replace("<!--%SKETCHSIZE%-->", String(sketch_size));
        } 
        else 
        {
            page.replace("<!--%SKETCHSIZE%-->", "N/A");
        }

        page.replace("<!--%SKETCHFREESPACE%-->", String(ESP.getFreeSketchSpace()));
        const esp_app_desc_t* app_desc = esp_ota_get_app_description();
        page.replace("<!--%SKETCHMD5%-->", String(app_desc->version));
    #endif
    return page;
}

String EspConfigWebserver::Construire_deviceconfightml()
{
    String page = Construire_header(topic::Device);
    page += Construire_deviceheader(subtopic::Config);
    page += String(reinterpret_cast<const __FlashStringHelper *>(device_config_html));
    page.replace("<!--%DEVICENAME%-->", espConfig->getDeviceName().c_str());
    page.replace("<!--%DEVICELOCATION%-->", espConfig->getDeviceLocation().c_str());
    page.replace("<!--%DEVICEDESCRIPTION%-->", espConfig->getDeviceDescription().c_str());
    page.replace("<!--%WEBUSER%-->", espConfig->getWEBUser().c_str());
    page.replace("<!--%WEBPASSWORD%-->", espConfig->getWEBPassword().c_str());
    page.replace("<!--%WEBPORT%-->", String(espConfig->getWEBPort()));
    page.replace("<!--%OTASTATUS%-->", espConfig->getOTAEnable() ? "checked" : "");
    page.replace("<!--%OTAPASSWORD%-->", espConfig->getOTAPassword().c_str());
    page.replace("<!--%OTAPORT%-->", String(espConfig->getOTAPort()));
    page += Construire_footer();
    return page;
}

String EspConfigWebserver::Construire_mqttheader(subtopic mqtttopic)
{
    String header(reinterpret_cast<const __FlashStringHelper *>(header_mqtt_html));
    switch (mqtttopic)
    {
    case subtopic::Info:
        header.replace("<!--%COLORINFO%-->", "w3-blue");
        header.replace("<!--%COLORCONFIG%-->", "w3-light-blue");
        break;
    case subtopic::Config:
        header.replace("<!--%COLORINFO%-->", "w3-light-blue");
        header.replace("<!--%COLORCONFIG%-->", "w3-blue");
        break;
    default:
        header.replace("<!--%COLORINFO%-->", "w3-light-blue");
        header.replace("<!--%COLORCONFIG%-->", "w3-light-blue");
        break;
    }
    return header;
}

  // <!--%MQTTSERVERADDRESS%-->
  // <!--%MQTTSERVERPORT%-->
  // <!--%MQTTUSER%-->
  // <!--%MQTTPASSWORD%-->


String EspConfigWebserver::Construire_mqttinfohtml(){   
    String page = Construire_header(topic::MQTT);
    page += Construire_mqttheader(subtopic::Info);
    page += String(reinterpret_cast<const __FlashStringHelper *>(mqtt_info_html));
    page.replace("<!--%MQTTSERVERADDRESS%-->", espConfig->getMQTTServer().toString());
    page.replace("<!--%MQTTSERVERPORT%-->", String(espConfig->getMQTTPort()));
    page.replace("<!--%MQTTUSER%-->", espConfig->getMQTTUser().c_str());
    page.replace("<!--%MQTTPASSWORD%-->", espConfig->getMQTTPassword().c_str());
    page += Construire_footer();
    return page;
}

  // TAG de la page è remplacer  
  // <!--%MQTTSERVERADDRESS%-->
  // <!--%MQTTSERVERPORT%-->
  // <!--%MQTTUSER%-->
  // <!--%MQTTPASSWORD%-->

String EspConfigWebserver::Construire_mqttconfightml()
{
    String page = Construire_header(topic::MQTT);
    page += Construire_mqttheader(subtopic::Config);
    page += String(reinterpret_cast<const __FlashStringHelper *>(mqtt_config_html));
    page.replace("<!--%MQTTSERVERADDRESS%-->", espConfig->getMQTTServer().toString());
    page.replace("<!--%MQTTSERVERPORT%-->", String(espConfig->getMQTTPort()));
    page.replace("<!--%MQTTUSER%-->", espConfig->getMQTTUser().c_str());
    page.replace("<!--%MQTTPASSWORD%-->", espConfig->getMQTTPassword().c_str());
    page += Construire_footer();
    return page;
}

String EspConfigWebserver::Construire_wifiheader(subtopic wifitopic){   
    String header(reinterpret_cast<const __FlashStringHelper *>(header_wifi_html));
    switch (wifitopic)
    {
    case subtopic::Info:
        header.replace("<!--%COLORINFO%-->", "w3-blue");
        header.replace("<!--%COLORSCAN%-->", "w3-light-blue");
        header.replace("<!--%COLORCONFIG%-->", "w3-light-blue");
        break;
    case subtopic::Scan:
        header.replace("<!--%COLORINFO%-->", "w3-light-blue");
        header.replace("<!--%COLORSCAN%-->", "w3-blue");
        header.replace("<!--%COLORCONFIG%-->", "w3-light-blue");
        break;
    case subtopic::Config:
        header.replace("<!--%COLORINFO%-->", "w3-light-blue");
        header.replace("<!--%COLORSCAN%-->", "w3-light-blue");
        header.replace("<!--%COLORCONFIG%-->", "w3-blue");
        break;
    default:
        header.replace("<!--%COLORINFO%-->", "w3-light-blue");
        header.replace("<!--%COLORSCAN%-->", "w3-light-blue");
        header.replace("<!--%COLORCONFIG%-->", "w3-light-blue");
        break;
    }
    return header;
}


// TAG de la page è remplacer
// <!--%SSID%--> : SSID du röseau
// <!--%RSSI%-->
// <!--%ACCESSPOINT%-->
// <!--%CANAL%-->
// <!--%IP%-->
// <!--%SUBNET%-->
// <!--%GATEWAY%-->
// <!--%DNS%-->
//
String EspConfigWebserver::Construire_wifiinfohtml() // 
{

    std::string lrssi = std::to_string(espWiFi->RSSI());
    lrssi += "dB";
    std::string lchannel = std::to_string(espWiFi->channel());


    String page = Construire_header(topic::WiFi);
    page += Construire_wifiheader(subtopic::Info);
    page += String(reinterpret_cast<const __FlashStringHelper *>(wifi_info_html));
    page.replace("<!--%SSID%-->", espWiFi->SSID());
    page.replace("<!--%RSSI%-->", lrssi.c_str());
    page.replace("<!--%ACCESSPOINT%-->", espWiFi->BSSIDstr());
    page.replace("<!--%CANAL%-->", lchannel.c_str());
    page.replace("<!--%IP%-->", espWiFi->localIP().toString());
    page.replace("<!--%SUBNET%-->", espWiFi->subnetMask().toString());
    page.replace("<!--%GATEWAY%-->", espWiFi->gatewayIP().toString());
    page.replace("<!--%DNS%-->", espWiFi->dnsIP().toString());
    page += Construire_footer();
    return page;
}

String EspConfigWebserver::Construire_wifiscanhtml() // OK adapted
{
    String ssid;
    uint8_t encryptionType;
    int32_t RSSI;
    uint8_t *BSSID;
    int32_t channel;
    bool isHidden;
    std::string lrssi;
    std::string lchannel;

    String wifiscanrows;
    String wifiscanonerow(reinterpret_cast<const __FlashStringHelper *>(wifi_scanrow_html));

    int nb_network = espWiFi->scanNetworks();

    for (int i = 0; i < nb_network; i++)
    {
        wifiscanrows += wifiscanonerow;
        #ifdef ESP8266
            espWiFi->getNetworkInfo(i, ssid, encryptionType, RSSI, BSSID, channel, isHidden);
            lrssi = std::to_string(RSSI);
            lrssi = lrssi + "dB";
            lchannel = std::to_string(channel);
        #elif defined(ESP32)
            ssid = espWiFi->SSID(i);
            encryptionType = espWiFi->encryptionType(i);
            RSSI = espWiFi->RSSI(i);
            BSSID = espWiFi->BSSID(i);
            channel = espWiFi->channel(i);
            lrssi = String(String(RSSI) + "dB").c_str();
            lchannel = String(channel).c_str();
        #endif
            
        // ENC_TYPE_WEP  = 5,
        // ENC_TYPE_TKIP = 2,
        // ENC_TYPE_CCMP = 4,
        // /* ... except these two, 7 and 8 are reserved in 802.11-2007 */
        // ENC_TYPE_NONE = 7,
        // ENC_TYPE_AUTO = 8

        wifiscanrows.replace("<!--%SSID%-->", ssid);
        wifiscanrows.replace("<!--%HIDDEN%-->", isHidden ? "Yes" : "No");
        wifiscanrows.replace("<!--%RSSI%-->", lrssi.c_str());
        wifiscanrows.replace("<!--%BSSID%-->", espWiFi->BSSIDstr(i).c_str());
        wifiscanrows.replace("<!--%CHANNEL%-->",lchannel.c_str());
        #ifdef ESP32
            switch (encryptionType)
            {
            case WIFI_AUTH_WEP:
                wifiscanrows.replace("<!--%ENCRYPT%-->", "WEP");
                break;
            case WIFI_AUTH_WPA_PSK:
                wifiscanrows.replace("<!--%ENCRYPT%-->", "WPA/PSK");
                break;
            case WIFI_AUTH_WPA2_PSK: 
                wifiscanrows.replace("<!--%ENCRYPT%-->", "WPA2/PSK");
                break;
            case WIFI_AUTH_OPEN:
                wifiscanrows.replace("<!--%ENCRYPT%-->", "NONE");
                break;
            case WIFI_AUTH_WPA_WPA2_PSK: 
                wifiscanrows.replace("<!--%ENCRYPT%-->", "WEPA/WPA2/PSK");
                break;
            case WIFI_AUTH_WPA2_ENTERPRISE: 
                wifiscanrows.replace("<!--%ENCRYPT%-->", "WPA2/EAS");
                break;
            case WIFI_AUTH_WPA3_PSK: 
                wifiscanrows.replace("<!--%ENCRYPT%-->", "WPA3/PSK");
                break;
            case WIFI_AUTH_WPA2_WPA3_PSK: 
                wifiscanrows.replace("<!--%ENCRYPT%-->", "WPA2/WPA3/PSK");
                break;
            case WIFI_AUTH_WAPI_PSK:
                wifiscanrows.replace("<!--%ENCRYPT%-->", "WAPI/PSK");
                break;
            default:    
                wifiscanrows.replace("<!--%ENCRYPT%-->", "UNKNOWN");
                break;
            }
        #elif defined(ESP8266)
            switch (encryptionType)
            {
            case ENC_TYPE_WEP:
                wifiscanrows.replace("<!--%ENCRYPT%-->", "WEP");
                break;
            case ENC_TYPE_TKIP:
                wifiscanrows.replace("<!--%ENCRYPT%-->", "TKIP");
                break;
            case ENC_TYPE_CCMP: 
                wifiscanrows.replace("<!--%ENCRYPT%-->", "WPA2-CCMP");
                break;
            case ENC_TYPE_NONE:
                wifiscanrows.replace("<!--%ENCRYPT%-->", "NONE");
                break;
            case ENC_TYPE_AUTO: 
                wifiscanrows.replace("<!--%ENCRYPT%-->", "AUTO");
                break;
            default:    
                wifiscanrows.replace("<!--%ENCRYPT%-->", "UNKNOWN");
                break;
            }
        #endif
            

    }

    String page = Construire_header(topic::WiFi);
    page += Construire_wifiheader(subtopic::Scan);
    page += String(reinterpret_cast<const __FlashStringHelper *>(wifi_scan_html));
    page.replace("<!--%NETLINE%-->", wifiscanrows);
    page += Construire_footer();
    return page;
}

String EspConfigWebserver::Construire_wificonfightml() // OK adapted
{

    // TAG de la page è remplacer
    // <!--%STASSID%-->     espConfig->getClientWiFiSSID()
    // <!--%STASSIDPW%-->   espConfig->getClientWiFiPassword()
    // <!--%STASTATUS%-->   espConfig->getClientWiFiToActivate()      valeur checked ou vide
    // <!--%STADHCP%-->     !espConfig->getClientWiFiManualIP()       valeur checked ou vide
    // <!--%STAIP%-->       espConfig->getClientAdresse().toString()
    // <!--%STASUBNET%-->   espConfig->getClientSubnet().toString()
    // <!--%STAGATEWAY%-->  espConfig->getClientGateway().toString()
    // <!--%STADNS%-->      espConfig->getClientDNS().toString()
    // <!--%APSSID%-->      espConfig->getAccesspointWiFiSSID()
    // <!--%APSSIDPW%-->    espConfig->getAccesspointWiFiPassword()
    // <!--%APSTATUS%-->    espConfig->getAccesspointWiFiToActivate() valeur checked ou vide
    // <!--%APCDEFAUT%-->   espConfig->getAccesspointWiFiManualIP()   valeur checked ou vide
    // <!--%APIP%-->        espConfig->getAccesspointAdresseIP().toString()
    // <!--%APSUBNET%-->    espConfig->getAccesspointSubnet().toString()
    // <!--%APGATEWAY%-->   espConfig->getAccesspointGateway().toString()
    // <!--%APDNS%-->       espConfig->getAccesspointDNS().toString()

    String WiFiFormTemplatehtml(reinterpret_cast<const __FlashStringHelper *>(wifi_config_html));
    String lstr;
    lstr = espConfig->getClientWiFiSSID().c_str();
    WiFiFormTemplatehtml.replace("<!--%STASSID%-->", lstr.c_str());
    _debug & _espconsoleactive ? _espconsole->println("Construire_wifiConfig : remplace <!--%STASSID%-->"):0;
    lstr = espConfig->getClientWiFiPassword().c_str();
    WiFiFormTemplatehtml.replace("<!--%STASSIDPW%-->", lstr.c_str());
    _debug & _espconsoleactive ? _espconsole->println("Construire_wifiConfig : remplace <!--%STASSIDPW%-->"):0;
    WiFiFormTemplatehtml.replace("<!--%STAIP%-->", espConfig->getClientAdresse().toString());
    _debug & _espconsoleactive ? _espconsole->println("Construire_wifiConfig : remplace <!--%STAIP%--> par " + espConfig->getClientAdresse().toString()):0;
    WiFiFormTemplatehtml.replace("<!--%STASUBNET%-->", espConfig->getClientSubnet().toString());
    _debug & _espconsoleactive ? _espconsole->println("Construire_wifiConfig : remplace <!--%STASUBNET%--> par " + espConfig->getClientSubnet().toString()):0;  
    WiFiFormTemplatehtml.replace("<!--%STAGATEWAY%-->", espConfig->getClientGateway().toString());
    _debug & _espconsoleactive ? _espconsole->println("Construire_wifiConfig : remplace <!--%STAGATEWAY%--> par " + espConfig->getClientGateway().toString()):0;
    WiFiFormTemplatehtml.replace("<!--%STADNS%-->", espConfig->getClientDNS().toString());
    _debug & _espconsoleactive ? _espconsole->println("Construire_wifiConfig : remplace <!--%STADNS%--> par " + espConfig->getClientDNS().toString()):0;

    if(espConfig->getClientWiFiToActivate()){
    WiFiFormTemplatehtml.replace("<!--%STASTATUS%-->", "checked value=\"active\"");
    _debug & _espconsoleactive ? _espconsole->println("Construire_wifiConfig : remplace <!--%STASTATUS%--> par checked value=\"active\""):0;
    }
    else {
    WiFiFormTemplatehtml.replace("<!--%STASTATUS%-->", "bobo value=\"active\"");
    _debug & _espconsoleactive ? _espconsole->println("Construire_wifiConfig : remplace <!--%STASTATUS%--> par bobo value=\"active\""):0;
    }


    if (!espConfig->getClientWiFiManualIP()){
    WiFiFormTemplatehtml.replace("<!--%STADHCP%-->", "checked value=\"checked\"");
    _debug & _espconsoleactive ? _espconsole->println("Construire_wifiConfig : remplace <!--%STADHCP%--> par checked value=\"checked\""):0;
    }
    else {
    WiFiFormTemplatehtml.replace("<!--%STADHCP%-->", "bobo value=\"checked\"");
    _debug & _espconsoleactive ? _espconsole->println("Construire_wifiConfig : remplace <!--%STADHCP%--> par bobo value=\"checked\""):0;
    }


    lstr=espConfig->getAccesspointWiFiSSID().c_str();
    WiFiFormTemplatehtml.replace("<!--%APSSID%-->", lstr.c_str());
    _debug & _espconsoleactive ? _espconsole->println("Construire_wifiConfig : remplace <!--%APSSID%-->"):0;
    lstr=espConfig->getAccesspointWiFiPassword().c_str();
    WiFiFormTemplatehtml.replace("<!--%APSSIDPW%-->", lstr.c_str());
    _debug & _espconsoleactive ? _espconsole->println("Construire_wifiConfig : remplace <!--%APSSIDPW%-->"):0; 
    if (espConfig->getAccesspointWiFiToActivate()){
    WiFiFormTemplatehtml.replace("<!--%APSTATUS%-->", "checked value=\"active\"");
    _debug & _espconsoleactive ? _espconsole->println("Construire_wifiConfig : remplace <!--%APSTATUS%--> par checked value=\"active\""):0;
    }
    else {
    WiFiFormTemplatehtml.replace("<!--%APSTATUS%-->", "bobo value=\"active\"");
    _debug & _espconsoleactive ? _espconsole->println("Construire_wifiConfig : remplace <!--%APSTATUS%--> par bobo value=\"active\""):0;

    }
    if (!espConfig->getAccesspointWiFiManualIP()){
    WiFiFormTemplatehtml.replace("<!--%APCDEFAUT%-->", "checked value=\"checked\"");
    _debug & _espconsoleactive ? _espconsole->println("Construire_wifiConfig : remplace <!--%APCDEFAUT%--> par checked value=\"checked\""):0;
    }
    else {
    WiFiFormTemplatehtml.replace("<!--%APCDEFAUT%-->", "bobo value=\"checked\"");
    _debug & _espconsoleactive ? _espconsole->println("Construire_wifiConfig : remplace <!--%APCDEFAUT%--> par bobo value=\"checked\""):0;
    }
    WiFiFormTemplatehtml.replace("<!--%APIP%-->", espConfig->getAccesspointAdresse().toString());
    _debug & _espconsoleactive ? _espconsole->println("Construire_wifiConfig : remplace <!--%APIP%--> par " + espConfig->getAccesspointAdresse().toString()):0; 
    WiFiFormTemplatehtml.replace("<!--%APSUBNET%-->", espConfig->getAccesspointSubnet().toString());
    _debug & _espconsoleactive ? _espconsole->println("Construire_wifiConfig : remplace <!--%APSUBNET%--> par " + espConfig->getAccesspointSubnet().toString()):0;
    WiFiFormTemplatehtml.replace("<!--%APGATEWAY%-->", espConfig->getAccesspointGateway().toString());
    _debug & _espconsoleactive ? _espconsole->println("Construire_wifiConfig : remplace <!--%APGATEWAY%--> par " + espConfig->getAccesspointGateway().toString()):0;
    WiFiFormTemplatehtml.replace("<!--%APDNS%-->", espConfig->getAccesspointDNS().toString());
    _debug & _espconsoleactive ? _espconsole->println("Construire_wifiConfig : remplace <!--%APDNS%--> par " + espConfig->getAccesspointDNS().toString()):0;
    
    String page = Construire_header(topic::WiFi);
    page += Construire_wifiheader(subtopic::Config);
    page += WiFiFormTemplatehtml;
    page += Construire_footer();
    
    return page;
}

String EspConfigWebserver::Construire_footer() // OK adapted
{
    String footer(reinterpret_cast<const __FlashStringHelper *>(footer_html));
    return footer;
}
