#include "sleep.h"

void ForceInputs()
{
    uint8_t P = SRTC.getADCPin();
    /* Unused GPIO PINS */
    pinMode(0, INPUT);  /*  ??      */
    pinMode(2, INPUT);  /*  ??      */
    pinMode(13, INPUT); /*  ??      */
    pinMode(15, INPUT); /*  ??      */
    pinMode(20, INPUT); /*  ??      */
    pinMode(36, INPUT); /*  ??      */
    pinMode(37, INPUT); /*  ??      */
    pinMode(38, INPUT); /*  ??      */
    pinMode(39, INPUT); /*  ??      */
                        /* RS232 */
    pinMode(3, INPUT);  /*  RX      */
                        /* BUTTONS */
    pinMode(26, INPUT); /* BTN1     */
    pinMode(25, INPUT); /* BTN2     */
    if (UP_PIN != 32)
    {
        pinMode(32, INPUT); /* BTN3     */
    }
    if (UP_PIN != 35 && P != 35)
    {
        pinMode(35, INPUT); /* ADC/BTN3 */
    }
    pinMode(4, INPUT); /* BTN4     */
                       /* BATTERY */
    // pinMode(27,INPUT);  /* INT      */
    // if (P != 33) pinMode(33,INPUT);  /* ADC      */
    // if (P != 34) pinMode(34,INPUT);  /* ADC      */
    /* RTC */
    pinMode(21, INPUT); /* SDA      */
    pinMode(22, INPUT); /* SCL      */
                        /* DISPLAY */
    pinMode(5, INPUT);  /*  CS      */
    pinMode(9, INPUT);  /* RES      */
    pinMode(10, INPUT); /*  DC      */
    pinMode(18, INPUT); /* SLCK     */
    pinMode(19, INPUT); /* BUSY     */
    pinMode(23, INPUT); /* MOSI     */
                        /* BMA 423 */
    pinMode(12, INPUT); /* INT2     */
    pinMode(14, INPUT); /* INT1     */
}

void goSleep()
{
    log("goSleep activated");
    
#if DEBUG && SCREEN_SLEEP_INFO
    display.setCursor(50, 190);
    display.setFont();
    display.setTextSize(2);
    display.print("Sleeping");
    display.display(PARTIAL_UPDATE);
#endif

    display.hibernate();
    ForceInputs();
    turnOffWifi();
    esp_sleep_enable_ext1_wakeup(UP_MASK | DOWN_MASK | MENU_MASK | BACK_MASK, ESP_EXT1_WAKEUP_ANY_HIGH); // Enable deep sleep wake on button press
    esp_deep_sleep_start();
}
