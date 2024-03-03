#ifndef ESPCONFIGMANAGER_H
#define ESPCONFIGMANAGER_H
#undef NEW_CONFIG_STRUCT

#include <Arduino.h>
#include <IPAddress.h>
#include <EEPROM.h>
#include <string>
#include <EspConsole.h>


// Définition des structures de données de configuration --------------------------------------------

struct t_Device
{
    std::string Name;
    std::string Description;
    std::string Location;
};

struct t_WiFi
{
    std::string SSID;
    std::string Password;
    bool toActivate;
    bool ManualIP;
};

struct t_IP
{
    IPAddress Adresse;
    IPAddress Subnet;
    IPAddress Gateway;
    IPAddress DNS;
};

struct t_MQTT
{
    IPAddress Server;
    std::string User;
    std::string Password;
    int Port;
};

struct t_WEB
{
    std::string User;
    std::string Password;
    int Port;
};

struct t_OTA
{
    bool Enable;
    std::string Password;
    int Port;
};

struct t_Config
{
    t_Device Device;
    t_WiFi STAWiFi;
    t_IP IPSTA;
    t_WiFi APWiFi;
    t_IP IPAP;
    t_MQTT MQTT;
    t_WEB WEB;
    t_OTA OTA;
};

class EspConfigManager
{

private:
    // Définition des constantes pour la structure EEPROM_Config ----------------------------------------
    static const int EEPROM_SIZE = 2048;
    static constexpr const char *L_EEPROM_MAGIC = "EEPROM";
    static const int L_EEPROM_MAGIC_SIZE = 7;
    static const int WIFI_MAX_SSID_SIZE = 32;
    static const int WIFI_MAX_PASSWORD_SIZE = 64;
    static const int MQTT_MAX_USER_SIZE = 32;
    static const int MQTT_MAX_PASSWORD_SIZE = 64;
    static const int WEB_MAX_USER_SIZE = 32;
    static const int WEB_MAX_PASSWORD_SIZE = 64;
    static const int DEVICE_MAX_NAME_SIZE = 32;
    static const int DEVICE_MAX_DESCRIPTION_SIZE = 255;
    static const int DEVICE_MAX_LOCATION_SIZE = 128;
    static const int OTA_MAX_PASSWORD_SIZE = 64;

    // Définition des paramètre par defaut de la config -------------------------------------------------

    static constexpr const char *L_DEFAULT_WIFI_USER = "admin";
    static constexpr const char *L_DEFAULT_WIFI_PASSWORD = "pwd4admin";
    static constexpr const char *L_DEFAULT_WEB_USER = "admin";
    static constexpr const char *L_DEFAULT_WEB_PASSWORD = "pwd4admin";
    static const int16_t DEFAULT_WEB_PORT = 8080;

    struct
    {
        t_Device Device;
        t_WiFi Client_WiFi;
        t_IP Client_IP;
        t_WiFi Accesspoint_WiFi;
        t_IP Accesspoint_IP;
        t_MQTT MQTT;
        t_WEB WEB;
        t_OTA OTA;
    } Config;
    boolean initialized = false;
    boolean initialized_console = false;
    EspConsole *Console;

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
    } EEPROM_Config;


public:
    //------ Constructeur par défaut----------------------------------------------------------------
    EspConfigManager();

    // Constructeur avec paramètres pour initialiser les données de configuration ---------------
    EspConfigManager(const t_Device &device_config,
                     const t_WiFi &wifi_client_config,
                     const t_IP &ip_client_config,
                     const t_WiFi &wifi_accesspoint_config,
                     const t_IP &ip_accesspoint_config,
                     const t_MQTT &mqtt_config,
                     const t_WEB &web_config,
                     const t_OTA &ota_config);

    // Constructeur avec initialisation de console -----------------------------------------------
    EspConfigManager(EspConsole *console);

    // Méthode pour initialiser la console -------------------------------------------------------
    void setConsole(EspConsole *console);
    
    // méthode pour accéder au donnée de configuration du device ---------------------------------
    void setMagic();
    void setDeviceName(const std::string &name);
    void setDeviceName(const char *name);
    void setDeviceName(const String name);
    void setDeviceDescription(const std::string &description);
    void setDeviceLocation(const std::string &location);
    // méthode pour accéder au donnée de configuration du client WiFi -----------------------------
    void setClientWiFiSSID(const std::string &ssid);
    void setClientWiFiPassword(const std::string &password);
    void setClientWiFiToActivate(bool activate);
    void setClientWiFiManualIP(bool manual);
    // méthode pour accéder au donnée de configuration IP du client WiFi -----------------------------
    void setClientAdresse(const IPAddress &adresse);
    void setClientSubnet(const IPAddress &subnet);
    void setClientGateway(const IPAddress &gateway);
    void setClientDNS(const IPAddress &dns); 
     // méthode pour accéder au donnée de configuration de l'access point WiFi -----------------------------
    void setAccesspointWiFiSSID(const std::string &ssid);
    void setAccesspointWiFiPassword(const std::string &password);
    void setAccesspointWiFiToActivate(bool activate);
    void setAccesspointWiFiManualIP(bool manual);
     // méthode pour accéder au donnée de configuration IP du point d'accès WiFi -----------------------
    void setAccesspointAdresse(const IPAddress &adresse);
    void setAccesspointSubnet(const IPAddress &subnet);
    void setAccesspointGateway(const IPAddress &gateway);
    void setAccesspointDNS(const IPAddress &dns);
    // méthode pour accéder au donnée de configuration du serveur MQTT --------------------------------
    void setMQTTServer(const IPAddress &server);
    void setMQTTUser(const std::string &user);
    void setMQTTPassword(const std::string &password);
    void setMQTTPort(int port);
    // méthode pour accéder au donnée de configuration du serveur WEB gérant la configuration du device
    void setWEBUser(const std::string &user);
    void setWEBPassword(const std::string &password);
    void setWEBPort(int port);
    // méthode pour accéder au donnée de configuration OTA --------------------------------
    void setOTAEnable(bool enable);
    void setOTAPassword(const std::string &password);
    void setOTAPort(int port);
 
    // méthode pour accéder au donnée de configuration du device ---------------------------------
    std::string getMagic() const;
    std::string getDeviceName() const;
    std::string getDeviceDescription() const;
    std::string getDeviceLocation() const;
    // méthode pour accéder au donnée de configuration du client WiFi -----------------------------
    std::string getClientWiFiSSID() const;
    std::string getClientWiFiPassword() const;
    bool getClientWiFiToActivate() const;
    bool getClientWiFiManualIP() const;
    // méthode pour accéder au donnée de configuration IP du client WiFi -----------------------------
    IPAddress getClientAdresse() const;
    IPAddress getClientSubnet() const;
    IPAddress getClientGateway() const;
    IPAddress getClientDNS() const;
    // méthode pour accéder au donnée de configuration du point d'accès WiFi -------------------------
    std::string getAccesspointWiFiSSID() const;
    std::string getAccesspointWiFiPassword() const;
    bool getAccesspointWiFiToActivate() const;
    bool getAccesspointWiFiManualIP() const;
    // méthode pour accéder au donnée de configuration IP du point d'accès WiFi -----------------------
    IPAddress getAccesspointAdresse() const;
    IPAddress getAccesspointSubnet() const;
    IPAddress getAccesspointGateway() const;
    IPAddress getAccesspointDNS() const;
    // méthode pour accéder au donnée de configuration du serveur MQTT --------------------------------
    IPAddress getMQTTServer() const;
    std::string getMQTTUser() const;
    std::string getMQTTPassword() const;
    int getMQTTPort() const;
    // méthode pour accéder au donnée de configuration du serveur WEB gérant la configuration du device
    std::string getWEBUser() const;
    std::string getWEBPassword() const;
    int getWEBPort() const;
    // méthode pour accéder au donnée de configuration OTA --------------------------------
    bool getOTAEnable() const;
    std::string getOTAPassword() const;
    int getOTAPort() const;

    // méthode pour sauvegarder les donnée de configuration dans l'eeprom ------------------------------
    bool save();

    // méthode pour sauvegarder les donnée de configuration dans l'eeprom ------------------------------

    bool load();


//--------------------------------------------------------------------------------------------------
//                                                                                                --
// Méthode à utiliser si on veut changer la structure des données stockée dans l'EEPROM           --
//                                                                                                --
//--------------------------------------------------------------------------------------------------

#ifdef NEW_CONFIG_STRUCT
    bool copyConfigtoNew();
#endif // NEW_CONFIG_STRUCT

};
#endif // ESPCONFIGMANAGER_H