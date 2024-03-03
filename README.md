# esptools

Librairie contenant mes outils pour la création de controleur IOT

## EspConfigManager

Cette classe permet de gérer une configuration en EEPROM de tel manière à garder les information en cas d'arrêt du microcontroleur.

Les information sauvegardée sont :

### Wifi :

:::row:::
    :::column span="":::
    Mode Station :

    * SSID
    * Passkey WEPA
    * Modes station actif ou non
    * Configuration IP DHCP ou manuelle
        * Adresse IP
        * Subnet
        * Routeur
        * Serveur DNS
    :::column-end:::
    :::column span="":::
    Mode access point :

    * SSID du réseau publié
    * Passkey WEPA du réseau publié
    * Modes accesspoint actif ou non
    * Configuration IP par défault ou personalisé
        * Adresse IP
        * Subnet
        * Routeur
        * Serveur DNS
    :::column-end:::
:::row-end:::
