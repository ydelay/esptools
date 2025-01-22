# esptools

Librairie contenant mes outils pour la création de controleur IOT

## Microcontroleurs supportés

* Espressif8266
* Espressif32

## EspConfigManager

Cette classe permet de gérer une configuration en EEPROM de tel manière à garder les informations en cas d'arrêt du microcontroleur.

Les informations sauvegardées sont :

### Wifi :

#### Mode Station :

* SSID
* Passkey WEPA
* Modes station actif ou non
* Configuration IP DHCP ou manuelle
  * Adresse IP
  * Subnet
  * Routeur
  * Serveur DNS

#### Mode access point :

* SSID du réseau publié
* Passkey WEPA du réseau publié
* Modes accesspoint actif ou non
* Configuration IP par défault ou personalisé
  * Adresse IP
  * Subnet
  * Routeur
  * Serveur DNS

### Serveur Web

* User
* Password
* Port

### Device

* Device Name
* Device location
* Device description

### MQTT

* Adresse du server
* Port
* User
* Password

### Over The Air

* OTA a activer ou non
* Password
* Port

Les sources Esp32EepromInitialisation.cpp et Esp8266EepromInitialisation.cpp permettent d'initialiser un nouveau microcontroleur avec des valeurs par défaut.

Les constructeurs de la classe ne charge pas automatiquement dans une structure tampon les information contenu dans l'EEPROM. Il faut faire appel à la méthode load().
La structure sauvegardée est structurée de tel manière à minimiser les ré-écritures dans l'EEPROM lors des changement de valeur.

Les fonctions setXXX() mettent à jours la structure tampon et la structure qui sera sauvegardée.

La classe contien un pointeur vers une instance de la class EspConsole ceci afin de permettre le debug.

### Points d'amélioration

* [ ] Ajouter une méthode pour faire la config initiale d'un nouveau microcontroleur
* [ ] Mettre des tests si le pointeur vers une instance de EspConsole n'est pas initialisé
* [ ] Documenter comment ajouter des éléments dans la structure sauvegardée
* [ ] Merger les 2 sources pour faire la première initialisation d'un microcontroleur en supportant les ESP32 et ESP8266

## EspConfigWebserver

Cette classe implémente un Webserveur et les pages permettant de modifier la configuration du Microcontroleur, elle permet de modifier toutes les information contenue dans la classe EspConfigManager.

Les pages html sont stockées en Flash en utilisant PROGMEM et elle sont codées dans EspConfigPageshtml.h

Les pages utilisent un subset du css de w3school qui est également stocké en flash.

Les formulaires utilisent la méthode POST pour sauvegarder les données.

Cette classe inclus des pointeur vers des instanciations des classes EspConfigManager, EspConsole et ESP8266WiFiClass ou WiFiClass.

### Utilisation

Méthode à appeler dans la fonction setup()

```
 EspConfigWebserver::Setup()
 EspConfigWebserver::SetConsole(EspConsole *console)
 EspConfigWebserver::SetWifi(ESP8266WiFiClass *wifi)
 EspConfigWebserver::SetConfig(EspConfigManager *config)
 EspConfigWebserver::begin()
 
```

Méthode à appeler dans la fonction loop()

```

 EspConfigWebserver::handleClient()
 EspConfigWebserver::stop()
 
```

### Points d'amélioration

* [ ] Pour l'ESP32 ajouter les informations sur l'état de la mémoire et de la flash qui sont fournies par la classe ESP pour le 8266.
