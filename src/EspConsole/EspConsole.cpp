#include <Stream.h>
#ifdef ESP32
    #include <WebServer.h>
    #include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#else
    #error "Ni ESP32 ni ESP8266 n'est défini"
#endif
#include <TelnetStream.h>
#include <Print.h>
#include <EspConsole.h>

    EspConsole::EspConsole() {}

    void EspConsole::begin() {
      // if (Serial) {
        Serial.begin(115200);
      // } else {
        TelnetStream.begin();
      // }
    }
    void EspConsole::end() {
      // if (Serial) {
        Serial.end();
      // } else {
        TelnetStream.stop();
      // }
    }
    int EspConsole::available() {
      if (Serial) {
        return Serial.available();
      } else {
        return TelnetStream.available();
      }
    }
    int EspConsole::read() {
      if (Serial) {
        return Serial.read();
      } else {
        return TelnetStream.read();
      }
    }
    int EspConsole::peek() {
      if (Serial) {
        return Serial.peek();
      } else {
        return TelnetStream.peek();
      }
    }
    void EspConsole::flush() {
      if (Serial) {
        Serial.flush();
      } else {
        TelnetStream.flush();
      }
    }
    size_t EspConsole::write(uint8_t c) {
      // if (Serial) {
        Serial.write(c);
      // } else {
        return TelnetStream.write(c);
      // }
    }
    
    int EspConsole::printf(const char *format, ...) {

      char buf[128];
      va_list args;
      va_start(args, format);
      int len = vsnprintf(buf, sizeof(buf), format, args);
      va_end(args);
      Print::write((const uint8_t *)buf, len);
      return len;
    }
