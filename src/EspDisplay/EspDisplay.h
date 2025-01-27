#ifndef ESPDISPLAY_H
#define ESPDISPLAY_H
#include <Arduino.h>
#include <U8g2lib.h>


#ifdef ESP8266
    using  D_CLASS = U8G2_SSD1306_128X64_NONAME_F_SW_I2C;
#endif
#ifdef ESP32
    using  D_CLASS = U8G2_SSD1306_128X64_NONAME_F_HW_I2C;
#endif

const uint8_t page_1 = 0;
const uint8_t page_2 = 1;
const uint8_t page_3 = 2;
const uint8_t page_4 = 3;

const uint8_t ligne_1 = 0;
const uint8_t ligne_2 = 1;
const uint8_t ligne_3 = 2;
const uint8_t ligne_4 = 3;

enum displaymode_t : uint8_t {
    NORMAL = 0,
    ROTATE = 1
};

using page_t = uint8_t;
using ligne_t = uint8_t;


class EspDisplay : public D_CLASS
{

private:

    const u8g2_uint_t x = 0;
    const u8g2_uint_t y1 = 12;
    const u8g2_uint_t y2 = y1+15;
    const u8g2_uint_t y3 = y2+15;
    const u8g2_uint_t y4 = y3+15;
    const uint nb_ligne = 4;
    const uint nb_page = 4;
    const uint8_t *FontByDefault = u8g2_font_helvR10_tf;
    String pages[4][4];
    
    uint8_t currentpage;
    bool WifiDisplayState;
    ulong rotatetime;
    ulong lastdisplaytime;
    page_t lastpage;
    displaymode_t currentmode;
    int8_t WiFiSSID;

    void displayWiFiconnectionbar();
    void drawpage(page_t page);



public:

    EspDisplay(const u8g2_cb_t *rotation, uint8_t clock, uint8_t data, uint8_t reset = U8X8_PIN_NONE);   
    void begin();
    void begin(uint8_t adress);
    void setFont(const uint8_t *font);
    void setCurrentPage(page_t page);
    void println(page_t page, ligne_t ligne, String text);
    void println(ligne_t ligne, String text);
    void setln(page_t page,ligne_t ligne, String text);
    void setln(ligne_t ligne, String text);
    void clearpage(page_t page);
    void displayWiFi(bool state);
    void displaypage(page_t page);
    void setMode(displaymode_t mode);
    void setrotateTime(ulong time);
    void setWiFiSSID(int8_t ssid);
    void handle(displaymode_t mode);
    void handle();
    void displayWiFiconnectionbar(const uint8_t wifissid);

}; 


#endif // ESPDISPLAY_H