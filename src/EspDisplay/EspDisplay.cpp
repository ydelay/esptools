#include <EspDisplay.h>

// Méthode de la section private : -------------------------------------------------------------------------------------

void EspDisplay::drawpage(page_t page){
    D_CLASS::clearBuffer();
    D_CLASS::drawStr(x, y1, pages[page][ligne_1].c_str());    
    D_CLASS::drawStr(x, y2, pages[page][ligne_2].c_str());    
    D_CLASS::drawStr(x, y3, pages[page][ligne_3].c_str());    
    D_CLASS::drawStr(x, y4, pages[page][ligne_4].c_str());
    if(WifiDisplayState) {
        displayWiFiconnectionbar();
    }   
    lastpage = page;
    D_CLASS::sendBuffer();
}

void EspDisplay::displayWiFiconnectionbar(){
    if (WiFiSSID > -60)
    {
        D_CLASS::drawFrame(D_CLASS::getDisplayWidth() - 3, 1, 2, 10);
    }
    if (WiFiSSID > -70)
    {
        D_CLASS::drawFrame(D_CLASS::getDisplayWidth() - 7, 3, 2, 8);
    }
    if (WiFiSSID > -80)
    {
        D_CLASS::drawFrame(D_CLASS::getDisplayWidth() - 11, 5, 2, 6);
    }
    if (WiFiSSID > -90)
    {
        D_CLASS::drawFrame(D_CLASS::getDisplayWidth() - 15, 7, 2, 4);
    }
    if (WiFiSSID > -95)
    {
        D_CLASS::drawFrame(D_CLASS::getDisplayWidth() - 19, 9, 2, 2);
    }
}



// Méthode de la section public : --------------------------------------------------------------------------------------

EspDisplay::EspDisplay (const u8g2_cb_t *rotation, uint8_t clock, uint8_t data, uint8_t reset) : D_CLASS(rotation, clock, data, reset)
{
    // u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, rotation, u8x8_byte_arduino_sw_i2c, u8x8_gpio_and_delay_arduino);
    // u8x8_SetPin_SW_I2C(getU8x8(), clock,  data,  reset);
    // U8G2_SSD1306_128X64_NONAME_F_SW_I2C(rotation, clock, data, reset);
    currentpage = page_1;
    currentmode = NORMAL;
    WifiDisplayState = true;
    rotatetime = 10000;
}

void EspDisplay::begin(){
    D_CLASS::begin();
    D_CLASS::setFont(FontByDefault);
    D_CLASS::clearBuffer();
    clearpage(page_1);
    clearpage(page_2);
    clearpage(page_3);
    clearpage(page_4);
}

void EspDisplay::setFont(const uint8_t *font){
    D_CLASS::setFont(font);
}

void EspDisplay::setCurrentPage(page_t page){
    currentpage = page;
}


void EspDisplay::println(page_t page, ligne_t ligne, String text){
    setln(page,ligne,text);
    drawpage(page);
}

void EspDisplay::println(ligne_t ligne, String text){
    setln(currentpage,ligne,text);
    drawpage(currentpage);
}

 void EspDisplay::setln(page_t page,ligne_t ligne, String text){
    pages[page][ligne] = text;
 }

 void EspDisplay::setln(ligne_t ligne, String text){
    pages[currentpage][ligne] = text;
 }

void EspDisplay::clearpage(page_t page){
    for (uint8_t i = 0; i < nb_ligne; i++)
    {
        pages[page][i] = "";
    }
}

void EspDisplay::displayWiFi(bool state){
    WifiDisplayState = state;
}

void EspDisplay::displaypage(page_t page){
    drawpage(page);
}   
void EspDisplay::setMode(displaymode_t mode){
    currentmode = mode;
}   

void EspDisplay::setrotateTime(ulong time){
    rotatetime = time;
}

void EspDisplay::setWiFiSSID(int8_t ssid){
    WiFiSSID = ssid;
}

void EspDisplay::handle(displaymode_t mode)
{
    long now = millis();
    if (now - lastdisplaytime > rotatetime)
    {
        lastdisplaytime = now;


        if (mode == ROTATE)
        {
            if (lastpage == page_4)
            {
                lastpage = page_1;
            }
            else
            {
                lastpage++;
            }
            drawpage(lastpage);
        }
    }
}

void EspDisplay::handle(){
    handle(currentmode);
}

void EspDisplay::displayWiFiconnectionbar(const uint8_t wifissid){
    WiFiSSID = wifissid;
    displayWiFiconnectionbar();
}  
// Fin de la classe EspDisplay : --------------------------------------------------------------------------------------