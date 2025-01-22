#ifdef ESP32
    #pragma message("ESP32 est défini")
#elif defined(ESP8266)
    #pragma message("ESP8266 est défini")
#else
    #error "Ni ESP32 ni ESP8266 n'est défini"
#endif

#include <Arduino.h>
#include <EspConsole.h>
#include <EspConfigManager.h>
#include <EspWifiManager.h>
#include <EspConfigWebserver.h>
#include <EspDisplay.h>





void setup() {

}

void loop() {

}
