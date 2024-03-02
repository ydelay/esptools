#include <EspConfigManager.h>



EspConfigManager::EspConfigManager() {
    EEPROM.begin(EEPROM_SIZE);
}

EspConfigManager::EspConfigManager(const t_Device &device_config,
                                   const t_WiFi &wifi_client_config,
                                   const t_IP &ip_client_config,
                                   const t_WiFi &wifi_accesspoint_config,
                                   const t_IP &ip_accesspoint_config,
                                   const t_MQTT &mqtt_config,
                                   const t_WEB &web_config,
                                   const t_OTA &ota_config)
{
    EspConfigManager();
    /// setDeviceConfig(device_config);
    setDeviceName(device_config.Name);
    setDeviceDescription(device_config.Description);
    setDeviceLocation(device_config.Location);
    /// setWifiClientConfig(wifi_client_config);
    setClientWiFiSSID(wifi_client_config.SSID);
    setClientWiFiPassword(wifi_client_config.Password);
    setClientWiFiToActivate(wifi_client_config.toActivate);
    setClientWiFiManualIP(wifi_client_config.ManualIP);
    /// setIpClientConfig(ip_client_config);
    setClientAdresse(ip_client_config.Adresse);
    setClientGateway(ip_client_config.Gateway);
    setClientSubnet(ip_client_config.Subnet);
    setClientDNS(ip_client_config.DNS);
    /// setWifiAccessPointConfig(wifi_accesspoint_config);
    setAccesspointWiFiSSID(wifi_accesspoint_config.SSID);
    setAccesspointWiFiPassword(wifi_accesspoint_config.Password);
    setAccesspointWiFiToActivate(wifi_accesspoint_config.toActivate);
    setAccesspointWiFiManualIP(wifi_accesspoint_config.ManualIP);
    /// setIpAccessPointConfig(ip_accesspoint_config);
    setAccesspointAdresse(ip_accesspoint_config.Adresse);
    setAccesspointGateway(ip_accesspoint_config.Gateway);
    setAccesspointSubnet(ip_accesspoint_config.Subnet);
    setAccesspointDNS(ip_accesspoint_config.DNS);
    /// setMqttConfig(mqtt_config);
    setMQTTServer(mqtt_config.Server);
    setMQTTPort(mqtt_config.Port);
    setMQTTUser(mqtt_config.User);
    setMQTTPassword(mqtt_config.Password);
    /// setWebConfig(web_config);
    setWEBUser(web_config.User);
    setWEBPassword(web_config.Password);
    setWEBPort(web_config.Port);
    /// setOtaConfig(ota_config);
    setOTAEnable(ota_config.Enable);
    setOTAPassword(ota_config.Password);
    setOTAPort(ota_config.Port);
    save();
}

EspConfigManager::EspConfigManager(EspConsole *console)
{
    setConsole(console);
    EspConfigManager();
}

void EspConfigManager::setConsole(EspConsole *console)
{
    Console = console;
    initialized_console = true;
};

// méthode pour accéder au donnée de configuration du device ---------------------------------

void EspConfigManager::setMagic()
{
    strncpy(EEPROM_Config.Magic, L_EEPROM_MAGIC, L_EEPROM_MAGIC_SIZE);
};

void EspConfigManager::setDeviceName(const std::string &name)
{
    Config.Device.Name = name;
    strncpy(EEPROM_Config.DeviceName, name.c_str(), sizeof(EEPROM_Config.DeviceName));
};


void EspConfigManager::setDeviceName(const char *name){
    std::string strname = name;
    Config.Device.Name = strname;
    strncpy(EEPROM_Config.DeviceName, strname.c_str(), sizeof(EEPROM_Config.DeviceName));
}

void EspConfigManager::setDeviceName(const String name)
{
    Config.Device.Name = name.c_str();
    strncpy(EEPROM_Config.DeviceName, name.c_str(), sizeof(EEPROM_Config.DeviceName));
}

void EspConfigManager::setDeviceDescription(const std::string &description)
{
    Config.Device.Description = description;
    strncpy(EEPROM_Config.DeviceDescription, description.c_str(), sizeof(EEPROM_Config.DeviceDescription));
};

void EspConfigManager::setDeviceLocation(const std::string &location)
{
    Config.Device.Location = location;
    strncpy(EEPROM_Config.DeviceLocation, location.c_str(), sizeof(EEPROM_Config.DeviceLocation));
};

// méthode pour accéder au donnée de configuration du client WiFi -----------------------------

void EspConfigManager::setClientWiFiSSID(const std::string &ssid)
    {
        Config.Client_WiFi.SSID = ssid;
        strncpy(EEPROM_Config.ClientWiFiSSID, ssid.c_str(), sizeof(EEPROM_Config.ClientWiFiSSID));
    };    

void EspConfigManager::setClientWiFiPassword(const std::string &password)
{
    Config.Client_WiFi.Password = password;
    strncpy(EEPROM_Config.ClientWiFiPassword, password.c_str(), sizeof(EEPROM_Config.ClientWiFiPassword));
};

void EspConfigManager::setClientWiFiToActivate(bool activate)
{
    Config.Client_WiFi.toActivate = activate;
    EEPROM_Config.ClientWiFiToActivate = activate;
};

void EspConfigManager::setClientWiFiManualIP(bool manual)
{
    Config.Client_WiFi.ManualIP = manual;
    EEPROM_Config.ClientWiFiManualIP = manual;
};

// méthode pour accéder au donnée de configuration du client IP -----------------------------
void EspConfigManager::setClientAdresse(const IPAddress &adresse)
{
    Config.Client_IP.Adresse = adresse;
    for (int i = 0; i < 4; i++)
    {
        EEPROM_Config.ClientAdresse[i] = adresse[i];
    }
};

void EspConfigManager::setClientSubnet(const IPAddress &subnet)
{
    Config.Client_IP.Subnet = subnet;
    for (int i = 0; i < 4; i++)
    {
        EEPROM_Config.ClientSubnet[i] = subnet[i];
    }
};

void EspConfigManager::setClientGateway(const IPAddress &gateway)
{
    Config.Client_IP.Gateway = gateway;
    for (int i = 0; i < 4; i++)
    {
        EEPROM_Config.ClientGateway[i] = gateway[i];
    }
};

void EspConfigManager::setClientDNS(const IPAddress &dns)
{
    Config.Client_IP.DNS = dns;
    for (int i = 0; i < 4; i++)
    {
        EEPROM_Config.ClientDNS[i] = dns[i];
    }
};

// méthode pour accéder au donnée de configuration du point d'accès WiFi -------------------------

    void EspConfigManager::setAccesspointWiFiSSID(const std::string &ssid)
    {
        Config.Accesspoint_WiFi.SSID = ssid;
        strncpy(EEPROM_Config.AccesspointWiFiSSID, ssid.c_str(), sizeof(EEPROM_Config.AccesspointWiFiSSID));
    };

    void EspConfigManager::setAccesspointWiFiPassword(const std::string &password)
    {
        Config.Accesspoint_WiFi.Password = password;
        strncpy(EEPROM_Config.AccesspointWiFiPassword, password.c_str(), sizeof(EEPROM_Config.AccesspointWiFiPassword));
    };

    void EspConfigManager::setAccesspointWiFiToActivate(bool activate)
    {
        Config.Accesspoint_WiFi.toActivate = activate;
        EEPROM_Config.AccesspointWiFiToActivate = activate;
    };

    void EspConfigManager::setAccesspointWiFiManualIP(bool manual)
    {
        Config.Accesspoint_WiFi.ManualIP = manual;
        EEPROM_Config.AccesspointWiFiManualIP = manual;
    };

// méthode pour accéder au donnée de configuration IP du point d'accès WiFi -----------------------

void EspConfigManager::setAccesspointAdresse(const IPAddress &adresse)
{
    Config.Accesspoint_IP.Adresse = adresse;
    for (int i = 0; i < 4; i++)
    {
        EEPROM_Config.AccesspointAdresse[i] = adresse[i];
    }
};

void EspConfigManager::setAccesspointSubnet(const IPAddress &subnet)
{
    Config.Accesspoint_IP.Subnet = subnet;
    for (int i = 0; i < 4; i++)
    {
        EEPROM_Config.AccesspointSubnet[i] = subnet[i];
    }
};

void EspConfigManager::setAccesspointGateway(const IPAddress &gateway)
{
    Config.Accesspoint_IP.Gateway = gateway;
    for (int i = 0; i < 4; i++)
    {
        EEPROM_Config.AccesspointGateway[i] = gateway[i];
    }
};

void EspConfigManager::setAccesspointDNS(const IPAddress &dns)
{
    Config.Accesspoint_IP.DNS = dns;
    for (int i = 0; i < 4; i++)
    {
        EEPROM_Config.AccesspointDNS[i] = dns[i];
    }
};    

// méthode pour accéder au donnée de configuration du serveur MQTT --------------------------------

void EspConfigManager::setMQTTServer(const IPAddress &server)
{
    Config.MQTT.Server = server;
    for (int i = 0; i < 4; i++)
    {
        EEPROM_Config.MQTTServer[i] = server[i];
    }
};

void EspConfigManager::setMQTTUser(const std::string &user)
{
    Config.MQTT.User = user;
    strncpy(EEPROM_Config.MQTTUser, user.c_str(), sizeof(EEPROM_Config.MQTTUser));
};

void EspConfigManager::setMQTTPassword(const std::string &password)
{
    Config.MQTT.Password = password;
    strncpy(EEPROM_Config.MQTTPassword, password.c_str(), sizeof(EEPROM_Config.MQTTPassword));
};

void EspConfigManager::setMQTTPort(int port)
{
    Config.MQTT.Port = port;
    EEPROM_Config.MQTTPort = port;
};

// méthode pour accéder au donnée de configuration du serveur WEB gérant la configuration du device

void EspConfigManager::setWEBUser(const std::string &user)
{
    Config.WEB.User = user;
    strncpy(EEPROM_Config.WEBUser, user.c_str(), sizeof(EEPROM_Config.WEBUser));
};

void EspConfigManager::setWEBPassword(const std::string &password)
{
    Config.WEB.Password = password;
    strncpy(EEPROM_Config.WEBPassword, password.c_str(), sizeof(EEPROM_Config.WEBPassword));
};

void EspConfigManager::setWEBPort(int port)
{
    Config.WEB.Port = port;
    EEPROM_Config.WEBPort = port;
};

// méthode pour accéder au donnée de configuration OTA --------------------------------

void EspConfigManager::setOTAEnable(bool enable)
{
    Config.OTA.Enable = enable;
    EEPROM_Config.OTAEnable = enable;
};

void EspConfigManager::setOTAPassword(const std::string &password)
{
    Config.OTA.Password = password;
    strncpy(EEPROM_Config.OTAPassword, password.c_str(), sizeof(EEPROM_Config.OTAPassword));
};

void EspConfigManager::setOTAPort(int port)
{
    Config.OTA.Port = port;
    EEPROM_Config.OTAPort = port;
};



// méthode pour accéder au donnée de configuration du device ---------------------------------

std::string EspConfigManager::getMagic() const
{
    return EEPROM_Config.Magic;
};

std::string EspConfigManager::getDeviceName() const
{
    return Config.Device.Name;
};

std::string EspConfigManager::getDeviceDescription() const
{
    return Config.Device.Description;
};

std::string EspConfigManager::getDeviceLocation() const
{
    return Config.Device.Location;
};

// méthode pour accéder au donnée de configuration du client WiFi -----------------------------

std::string EspConfigManager::getClientWiFiSSID() const
{
    return Config.Client_WiFi.SSID;
};

std::string EspConfigManager::getClientWiFiPassword() const
{
    return Config.Client_WiFi.Password;
};

bool EspConfigManager::getClientWiFiToActivate() const
{
    return Config.Client_WiFi.toActivate;
};

bool EspConfigManager::getClientWiFiManualIP() const
{
    return Config.Client_WiFi.ManualIP;
};

// méthode pour accéder au donnée de configuration IP du client WiFi -----------------------------

IPAddress EspConfigManager::getClientAdresse() const
{
    return Config.Client_IP.Adresse;
};

IPAddress EspConfigManager::getClientSubnet() const
{
    return Config.Client_IP.Subnet;
};

IPAddress EspConfigManager::getClientGateway() const
{
    return Config.Client_IP.Gateway;
};

IPAddress EspConfigManager::getClientDNS() const
{
    return Config.Client_IP.DNS;
};

// méthode pour accéder au donnée de configuration du point d'accès WiFi -------------------------

std::string EspConfigManager::getAccesspointWiFiSSID() const
{
    return Config.Accesspoint_WiFi.SSID;
};

std::string EspConfigManager::getAccesspointWiFiPassword() const
{
    return Config.Accesspoint_WiFi.Password;
};

bool EspConfigManager::getAccesspointWiFiToActivate() const
{
    return Config.Accesspoint_WiFi.toActivate;
};

bool EspConfigManager::getAccesspointWiFiManualIP() const
{
    return Config.Accesspoint_WiFi.ManualIP;
};

// méthode pour accéder au donnée de configuration IP du point d'accès WiFi -----------------------

IPAddress EspConfigManager::getAccesspointAdresse() const
{
    return Config.Accesspoint_IP.Adresse;
};

IPAddress EspConfigManager::getAccesspointSubnet() const
{
    return Config.Accesspoint_IP.Subnet;
};

IPAddress EspConfigManager::getAccesspointGateway() const
{
    return Config.Accesspoint_IP.Gateway;
};

IPAddress EspConfigManager::getAccesspointDNS() const
{
    return Config.Accesspoint_IP.DNS;
};

// méthode pour accéder au donnée de configuration du serveur MQTT --------------------------------

IPAddress EspConfigManager::getMQTTServer() const
{
    return Config.MQTT.Server;
};

std::string EspConfigManager::getMQTTUser() const
{
    return Config.MQTT.User;
};

std::string EspConfigManager::getMQTTPassword() const
{
    return Config.MQTT.Password;
};

int EspConfigManager::getMQTTPort() const
{
    return Config.MQTT.Port;
};

// méthode pour accéder au donnée de configuration du serveur WEB gérant la configuration du device

std::string EspConfigManager::getWEBUser() const
{
    return Config.WEB.User;
};

std::string EspConfigManager::getWEBPassword() const
{
    return Config.WEB.Password;
};

int EspConfigManager::getWEBPort() const
{
    return Config.WEB.Port;
};

// méthode pour accéder au donnée de configuration OTA --------------------------------

bool EspConfigManager::getOTAEnable() const
{
    return Config.OTA.Enable;
};

std::string EspConfigManager::getOTAPassword() const
{
    return Config.OTA.Password;
};

int EspConfigManager::getOTAPort() const
{
    return Config.OTA.Port;
};

// méthode pour sauvegarder les donnée de configuration dans l'eeprom ------------------------------


bool EspConfigManager::save() // todo: à implémenter
{
    if (EEPROM.length() > sizeof(EEPROM_Config))
    {
        EEPROM.put(0, EEPROM_Config);
        EEPROM.commit();
        load();
    }
    else
    {
        Console->println("Erreur de'écriture dans l'EEPROM pas assez de mémoire");
        return false;
    }
    return true;
}

bool EspConfigManager::load() 
{
    IPAddress l_IP;
    EEPROM.get(0, EEPROM_Config);
    if (String(EEPROM_Config.Magic) == String(L_EEPROM_MAGIC))
    {   
        Serial.println("EEPROM_Config.Magic == L_EEPROM_MAGIC");
        /// setDeviceConfig(device_config);
        setDeviceName(EEPROM_Config.DeviceName);
        setDeviceDescription(EEPROM_Config.DeviceDescription);
        setDeviceLocation(EEPROM_Config.DeviceLocation);
        /// setWifiClientConfig(wifi_client_config);
        setClientWiFiSSID(EEPROM_Config.ClientWiFiSSID);
        setClientWiFiPassword(EEPROM_Config.ClientWiFiPassword);
        setClientWiFiToActivate(EEPROM_Config.ClientWiFiToActivate);
        setClientWiFiManualIP(EEPROM_Config.ClientWiFiManualIP);
        /// setIpClientConfig(ip_client_config);
        for (int i = 0; i < 4; i++)
        {
            l_IP[i] = EEPROM_Config.ClientAdresse[i];
        }
        setClientAdresse(l_IP);
        for (int i = 0; i < 4; i++)
        {
            l_IP[i] = EEPROM_Config.ClientGateway[i];
        }
        setClientGateway(l_IP);
        for (int i = 0; i < 4; i++)
        {
            l_IP[i] = EEPROM_Config.ClientSubnet[i];
        }
        setClientSubnet(l_IP);
        for (int i = 0; i < 4; i++)
        {
            l_IP[i] = EEPROM_Config.ClientDNS[i];
        }
        setClientDNS(l_IP);
        /// setWifiAccessPointConfig(wifi_accesspoint_config);
        setAccesspointWiFiSSID(EEPROM_Config.AccesspointWiFiSSID);
        setAccesspointWiFiPassword(EEPROM_Config.AccesspointWiFiPassword);
        setAccesspointWiFiToActivate(EEPROM_Config.AccesspointWiFiToActivate);
        setAccesspointWiFiManualIP(EEPROM_Config.AccesspointWiFiManualIP);
        /// setIpAccessPointConfig(ip_accesspoint_config);
        for (int i = 0; i < 4; i++)
        {
            l_IP[i] = EEPROM_Config.AccesspointAdresse[i];
        }
        setAccesspointAdresse(l_IP);
        for (int i = 0; i < 4; i++)
        {
            l_IP[i] = EEPROM_Config.AccesspointGateway[i];
        }
        setAccesspointGateway(l_IP);
        for (int i = 0; i < 4; i++)
        {
            l_IP[i] = EEPROM_Config.AccesspointSubnet[i];
        }
        setAccesspointSubnet(l_IP);
        for (int i = 0; i < 4; i++)
        {
            l_IP[i] = EEPROM_Config.AccesspointDNS[i];
        }
        setAccesspointDNS(l_IP);
        /// setMqttConfig(mqtt_config);
        for (int i = 0; i < 4; i++)
        {
            l_IP[i] = EEPROM_Config.MQTTServer[i];
        }
        setMQTTServer(l_IP);
        setMQTTPort(EEPROM_Config.MQTTPort);
        setMQTTUser(EEPROM_Config.MQTTUser);
        setMQTTPassword(EEPROM_Config.MQTTPassword);
        /// setWebConfig(web_config);
        setWEBUser(EEPROM_Config.WEBUser);
        setWEBPassword(EEPROM_Config.WEBPassword);
        setWEBPort(EEPROM_Config.WEBPort);
        /// setOtaConfig(ota_config);
        setOTAEnable(EEPROM_Config.OTAEnable);
        setOTAPassword(EEPROM_Config.OTAPassword);
        setOTAPort(EEPROM_Config.OTAPort);
    }
    else
    {
        Serial.println("EEPROM_Config.Magic != L_EEPROM_MAGIC");
        return false;
    }
    return true;
}

//--------------------------------------------------------------------------------------------------
//                                                                                                --
// Méthode à utiliser si on veut changer la structure des données stockée dans l'EEPROM           --
//                                                                                                --
//--------------------------------------------------------------------------------------------------

#ifdef NEW_CONFIG_STRUCT

void copy (char *dest, const char *src, size_t len)
{
    for (uint i=0; i<len; i++)
    {
        dest[i] = src[i];
    }
}

void copy (uint8_t *dest, const uint8_t *src, size_t len)
{
    for (uint i=0; i<len; i++)
    {
        dest[i] = src[i];
    }
}

bool EspConfigManager::copyConfigtoNew()
{
    struct
    {
        char Magic[L_EEPROM_MAGIC_SIZE];
        char DeviceName[DEVICE_MAX_NAME_SIZE + 1];
        char DeviceDescription[DEVICE_MAX_DESCRIPTION_SIZE + 1];
        char DeviceLocation[DEVICE_MAX_LOCATION_SIZE + 1];
        char ClientWiFiSSID[WIFI_MAX_SSID_SIZE + 1];
        char ClientWiFiPassword[WIFI_MAX_PASSWORD_SIZE + 1];
        bool ClientWiFiToActivate;
        bool ClientWiFiManualIP;
        uint8_t ClientAdresse[4];
        uint8_t ClientSubnet[4];
        uint8_t ClientGateway[4];
        uint8_t ClientDNS[4];
        char AccesspointWiFiSSID[WIFI_MAX_SSID_SIZE + 1];
        char AccesspointWiFiPassword[WIFI_MAX_PASSWORD_SIZE + 1];
        bool AccesspointWiFiToActivate;
        bool AccesspointWiFiManualIP;
        uint8_t AccesspointAdresse[4];
        uint8_t AccesspointSubnet[4];
        uint8_t AccesspointGateway[4];
        uint8_t AccesspointDNS[4];
        uint8_t MQTTServer[4];
        char MQTTUser[MQTT_MAX_USER_SIZE + 1];
        char MQTTPassword[MQTT_MAX_PASSWORD_SIZE + 1];
        int16_t MQTTPort;
        char WEBUser[WEB_MAX_USER_SIZE + 1];
        char WEBPassword[WEB_MAX_PASSWORD_SIZE + 1];
        int16_t WEBPort;
        bool OTAEnable;
        char OTAPassword[OTA_MAX_PASSWORD_SIZE + 1];
        int16_t OTAPort;
    } EEPROM_Config_NEW;

    copy(EEPROM_Config_NEW.Magic, EEPROM_Config.Magic, sizeof(EEPROM_Config.Magic));
    copy(EEPROM_Config_NEW.DeviceName, EEPROM_Config.DeviceName, sizeof(EEPROM_Config.DeviceName));
    copy(EEPROM_Config_NEW.DeviceDescription, EEPROM_Config.DeviceDescription, sizeof(EEPROM_Config.DeviceDescription));
    copy(EEPROM_Config_NEW.DeviceLocation, EEPROM_Config.DeviceLocation, sizeof(EEPROM_Config.DeviceLocation));
    copy(EEPROM_Config_NEW.ClientWiFiSSID, EEPROM_Config.ClientWiFiSSID, sizeof(EEPROM_Config.ClientWiFiSSID));
    copy(EEPROM_Config_NEW.ClientWiFiPassword, EEPROM_Config.ClientWiFiPassword, sizeof(EEPROM_Config.ClientWiFiPassword));
    EEPROM_Config_NEW.ClientWiFiToActivate = EEPROM_Config.ClientWiFiToActivate;
    EEPROM_Config_NEW.ClientWiFiManualIP = EEPROM_Config.ClientWiFiManualIP;
    copy(EEPROM_Config_NEW.ClientAdresse, EEPROM_Config.ClientAdresse, sizeof(EEPROM_Config.ClientAdresse));
    copy(EEPROM_Config_NEW.ClientGateway, EEPROM_Config.ClientGateway, sizeof(EEPROM_Config.ClientGateway));
    copy(EEPROM_Config_NEW.ClientSubnet, EEPROM_Config.ClientSubnet, sizeof(EEPROM_Config.ClientSubnet));
    copy(EEPROM_Config_NEW.ClientDNS, EEPROM_Config.ClientDNS, sizeof(EEPROM_Config.ClientDNS));
    copy(EEPROM_Config_NEW.AccesspointWiFiSSID, EEPROM_Config.AccesspointWiFiSSID, sizeof(EEPROM_Config.AccesspointWiFiSSID));
    copy(EEPROM_Config_NEW.AccesspointWiFiPassword, EEPROM_Config.AccesspointWiFiPassword, sizeof(EEPROM_Config.AccesspointWiFiPassword));
    EEPROM_Config_NEW.AccesspointWiFiToActivate = EEPROM_Config.AccesspointWiFiToActivate;
    EEPROM_Config_NEW.AccesspointWiFiManualIP = EEPROM_Config.AccesspointWiFiManualIP;
    copy(EEPROM_Config_NEW.AccesspointAdresse, EEPROM_Config.AccesspointAdresse, sizeof(EEPROM_Config.AccesspointAdresse));
    copy(EEPROM_Config_NEW.AccesspointGateway, EEPROM_Config.AccesspointGateway, sizeof(EEPROM_Config.AccesspointGateway));
    copy(EEPROM_Config_NEW.AccesspointSubnet, EEPROM_Config.AccesspointSubnet, sizeof(EEPROM_Config.AccesspointSubnet));
    copy(EEPROM_Config_NEW.AccesspointDNS, EEPROM_Config.AccesspointDNS, sizeof(EEPROM_Config.AccesspointDNS));
    copy(EEPROM_Config_NEW.MQTTServer, EEPROM_Config.MQTTServer, sizeof(EEPROM_Config.MQTTServer));
    EEPROM_Config_NEW.MQTTPort = EEPROM_Config.MQTTPort;
    copy(EEPROM_Config_NEW.MQTTUser, EEPROM_Config.MQTTUser, sizeof(EEPROM_Config.MQTTUser));
    copy(EEPROM_Config_NEW.MQTTPassword, EEPROM_Config.MQTTPassword, sizeof(EEPROM_Config.MQTTPassword));
    copy(EEPROM_Config_NEW.WEBUser, EEPROM_Config.WEBUser, sizeof(EEPROM_Config.WEBUser));
    copy(EEPROM_Config_NEW.WEBPassword, EEPROM_Config.WEBPassword, sizeof(EEPROM_Config.WEBPassword));
    EEPROM_Config_NEW.WEBPort = EEPROM_Config.WEBPort;
    if (EEPROM.length() > sizeof(EEPROM_Config_NEW))
    {
        EEPROM.put(0, EEPROM_Config_NEW);
        EEPROM.commit();
    }
    else
    {
        Console->println("Erreur de'écriture dans l'EEPROM pas assez de mémoire");
        return false;
    }
    return true;
}

#endif // NEW_CONFIG_STRUCT
