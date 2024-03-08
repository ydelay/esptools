#ifndef ESPCONSOLE_H
#define ESPCONSOLE_H

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

/**
 * @brief A class representing a console interface.
 * 
 * This class inherits from the Stream class and provides methods for interacting with a console.
 */
class EspConsole : public Stream {
  public:
    /**
     * @brief Default constructor.
     */
    EspConsole();    

    /**
     * @brief Initializes the console.
     */
    void begin();

    /**
     * @brief Ends the console.
     */
    void end();

    /**
     * @brief Checks if there is data available to read from the console.
     * 
     * @return The number of bytes available to read.
     */
    virtual int available();

    /**
     * @brief Reads a byte from the console.
     * 
     * @return The byte read from the console.
     */
    virtual int read();

    /**
     * @brief Peeks at the next byte in the console without removing it from the input buffer.
     * 
     * @return The next byte in the console.
     */
    virtual int peek();

    /**
     * @brief Flushes any pending data in the console output buffer.
     */
    virtual void flush();

    /**
     * @brief Writes a byte to the console.
     * 
     * @param c The byte to write.
     * @return The number of bytes written.
     */
    virtual size_t write(uint8_t c);

    /**
     * @brief Prints formatted data to the console.
     * 
     * @param format The format string.
     * @param ... The additional arguments to format.
     * @return The number of bytes written.
     */
    int printf(const char *format, ...);
};

#endif // ESPCONSOLE_H
