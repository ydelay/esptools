#include "EspWiFiManager.h"

EspWiFiManager::EspWiFiManager()
{
}

EspWiFiManager::EspWiFiManager(EspConfigManager *pconfigManager)
{
    config = pconfigManager;
    EspWiFiManager();
}

void EspWiFiManager::setconfig(EspConfigManager *pconfigManager)
{
    config = pconfigManager;
}

void EspWiFiManager::setconsole(EspConsole *pconsole)
{
    _espconsole = pconsole;
    _espconsoleactive = true;
}

int EspWiFiManager::getbestChannel()
{
    return bestChannel;
}

void EspWiFiManager::setup()
{

    if (config == NULL)
    {
        _debug & _espconsoleactive ? _espconsole->println("Error: EspWiFiManager::setup() called without a valid EspConfigManager object"):0;
        return;
    }
    if (config->getAccesspointWiFiToActivate() and config->getClientWiFiToActivate())
    {
        _debug & _espconsoleactive ? _espconsole->println("Both Access Point and Station WiFi are activated."):0;
        mode = WIFI_AP_STA;
        setupAccessPoint();
        setupStation();
    }

    else if (config->getAccesspointWiFiToActivate())
    {
        _debug & _espconsoleactive ? _espconsole->println("Access Point WiFi is activated."):0;
        mode = WIFI_AP;
        setupAccessPoint();
    }
    else if (config->getClientWiFiToActivate())
    {
        _debug & _espconsoleactive ? _espconsole->println("Station WiFi is activated."):0;
        mode = WIFI_STA;
        setupStation();
    }
    else
    {
        _debug & _espconsoleactive ? _espconsole->println("No WiFi is activated."):0;
        mode = WIFI_OFF;
    }
}
void EspWiFiManager::setupAccessPoint()
{
    if (config == NULL)
    {
        _debug & _espconsoleactive ? _espconsole->println("Error: EspWiFiManager::setupAccessPoint() called without a valid EspConfigManager object"):0;
        return;
    }

    WiFi.mode(mode);

    if (config->getAccesspointWiFiManualIP())
    {
        IPAddress ip(config->getAccesspointAdresse());
        IPAddress gateway(config->getAccesspointGateway());
        IPAddress subnet(config->getAccesspointSubnet());

        WiFi.softAPConfig(ip, gateway, subnet);
    }
}

void EspWiFiManager::setupStation()
{
    WiFi.mode(mode);

    if (config == NULL)
    {
        _debug & _espconsoleactive ? _espconsole->println("Error: EspWiFiManager::setupStation() called without a valid EspConfigManager object"):0;
        return;
    }

    if (config->getClientWiFiManualIP())
    {
        IPAddress ip(config->getClientAdresse());
        IPAddress gateway(config->getClientGateway());
        IPAddress subnet(config->getClientSubnet());
        IPAddress dns(config->getClientDNS());
        WiFi.config(ip, gateway, subnet, dns);
    }
}

void EspWiFiManager::begin()
{
    if (mode == WIFI_AP_STA)
    {
        WiFi.softAP(config->getAccesspointWiFiSSID().c_str(), config->getAccesspointWiFiPassword().c_str(), setBestChannel());
        WiFi.begin(config->getClientWiFiSSID().c_str(), config->getClientWiFiPassword().c_str());
        STAconnected = true;
        APconnected = true;
    }
    else if (mode == WIFI_AP)
    {
        WiFi.softAP(config->getAccesspointWiFiSSID().c_str(), config->getAccesspointWiFiPassword().c_str(), setBestChannel());
        APconnected = true;
    }
    else if (mode == WIFI_STA)
    {
        WiFi.begin(config->getClientWiFiSSID().c_str(), config->getClientWiFiPassword().c_str());
        STAconnected = true;
    }
}

void EspWiFiManager::loop()
{
    return;
}

void EspWiFiManager::disconnect()
{
    WiFi.disconnect();
    STAconnected = false;
    APconnected = false;
}

bool EspWiFiManager::isConnected()
{
    return STAconnected or APconnected;
}

bool EspWiFiManager::isConnectedAsStation()
{
    return STAconnected;
}

bool EspWiFiManager::isAccespointactif()
{
    return APconnected;
}

EspWiFiManager Accespointactif()
{
    return EspWiFiManager();
}

int EspWiFiManager::setBestChannel()
{
    const int MAX_CHANNELS = 13;
    //  sauvegarde l'état actuel de la connexion WiFi
    wl_status_t CurrentStatus = WiFi.status();
    WiFiMode_t Currentmode = WiFi.getMode();

    if (CurrentStatus == WL_CONNECTED)
    {
        WiFi.disconnect();
        delay(100);
    }

    // met le WiFi en mode station pour scanner les réseaux
    WiFi.mode(WIFI_STA);

    int rssiPerChannel[MAX_CHANNELS + 1] = {-100};
    int avgRssiPerChannel[MAX_CHANNELS + 1] = {-100};

    int n = WiFi.scanNetworks();

    if (n > 0)
    {
        for (int i = 0; i < n; ++i)
        {
            int channel = WiFi.channel(i);
            int rssi = WiFi.RSSI(i);
            rssiPerChannel[channel] = rssi;
        }
    }
    else
    {
        return 1;
    }

    // Calculer le RSSI moyen pour chaque canal et ses canaux adjacents
    _debug & _espconsoleactive ? _espconsole->println("RSSI moyen par canal:"):0;
    for (int i = 1; i <= MAX_CHANNELS; ++i)
    {
        if (i == 1)
        {
            avgRssiPerChannel[i] = (rssiPerChannel[i] + rssiPerChannel[i + 1]) / 2;
        }
        else if (i == MAX_CHANNELS)
        {
            avgRssiPerChannel[i] = (rssiPerChannel[i] + rssiPerChannel[i - 1]) / 2;
        }
        else
        {
            avgRssiPerChannel[i] = (rssiPerChannel[i - 1] + rssiPerChannel[i] + rssiPerChannel[i + 1]) / 3;
        }
        _debug & _espconsoleactive ? _espconsole->print("Channel "):0;
        _debug & _espconsoleactive ? _espconsole->print(i):0;
        _debug & _espconsoleactive ? _espconsole->print(" RSSI: "):0;
        _debug & _espconsoleactive ? _espconsole->println(avgRssiPerChannel[i]):0;        
    }

    // Trouver le canal avec le RSSI moyen le plus bas
    int minRssi = 0;
    int minRssiChannel = 1;
    for (int i = 1; i <= MAX_CHANNELS; ++i)
    {
        if (avgRssiPerChannel[i] < minRssi)
        {
            minRssi = avgRssiPerChannel[i];
            minRssiChannel = i;
        }
    }


    // restaure l'état de la connexion WiFi
    WiFi.mode(Currentmode);
    if (CurrentStatus == WL_CONNECTED and (Currentmode == WIFI_STA or Currentmode == WIFI_AP_STA))
    {
        WiFi.begin(config->getClientWiFiSSID().c_str(), config->getClientWiFiPassword().c_str());
        delay(100);
    }

    if (CurrentStatus == WL_CONNECTED and (Currentmode == WIFI_AP or Currentmode == WIFI_AP_STA))
    {
        WiFi.softAP(config->getAccesspointWiFiSSID().c_str(), config->getAccesspointWiFiPassword().c_str(), minRssiChannel);
        delay(100);
    }
    _debug & _espconsoleactive ? _espconsole->print("Canal choisi: "):0;
    _debug & _espconsoleactive ? _espconsole->println(minRssiChannel):0;
    bestChannel = minRssiChannel;
    return minRssiChannel;

}
