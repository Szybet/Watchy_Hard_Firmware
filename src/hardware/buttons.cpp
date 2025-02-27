#include "buttons.h"

int RTC_DATA_ATTR UP_PIN = 32;
uint64_t RTC_DATA_ATTR UP_MASK = GPIO_SEL_32;
buttonState buttonPressed = None;
TaskHandle_t buttonTask;

buttonState useButton(bool allButtons)
{
    if (allButtons == false && buttonPressed == Back)
    {
        return None;
    }
    buttonState buttonPressedTmp = buttonPressed;
    buttonPressed = None;

    // log("Used button by UI: " + getButtonString(buttonPressedTmp));
    if (buttonPressedTmp != None)
    {
        log("Used button by UI: " + getButtonString(buttonPressedTmp));
    }

    return buttonPressedTmp;
}

void initButtons()
{
    if (SRTC.getType() == PCF8563)
    {
        if (HWVer == 1.5)
        {
            UP_PIN = 32;
            UP_MASK = GPIO_SEL_32;
        }
        else
        {
            UP_PIN = 35;
            UP_MASK = GPIO_SEL_35;
        }
    }

    pinMode(MENU_PIN, INPUT);
    pinMode(BACK_PIN, INPUT);
    pinMode(UP_PIN, INPUT);
    pinMode(DOWN_PIN, INPUT);
}

void setButton(buttonState button)
{
    log("setButton called: " + getButtonString(button));
    vibrateMotor();
    buttonPressed = button;
    resetSleepDelay();
}

#define ADD_BUTTON_DELAY 4
#define SMALL_BUTTON_DELAY_MS 25
void loopButtonsTask(void *parameter)
{
    while (true)
    {
        delayTask(BUTTON_TASK_DELAY);
        if (digitalRead(BACK_PIN) == HIGH)
        {
            /// setButton(Back);
            // delayTask(BUTTON_TASK_DELAY / ADD_BUTTON_DELAY);
            int startime = millis();
            int elapsedtime = 0;

            while (digitalRead(BACK_PIN) == HIGH && elapsedtime < BUTTON_LONG_PRESS_MS)
            {
                delayTask(SMALL_BUTTON_DELAY_MS);
                elapsedtime = millis() - startime;
            }
            log("elapsed time: " + String(elapsedtime) + " BUTTON_LONG_PRESS_MS:" + String(BUTTON_LONG_PRESS_MS));
            if (elapsedtime > BUTTON_LONG_PRESS_MS)
            {
                setButton(LongBack);
                while (digitalRead(BACK_PIN) == HIGH)
                {
                    delayTask(SMALL_BUTTON_DELAY_MS);
                }
                continue;
            }
            if (digitalRead(BACK_PIN) == HIGH)
            {
                setButton(Back);
                continue;
            }
        }
        else if (digitalRead(MENU_PIN) == HIGH && buttonPressed != Back)
        {
            setButton(Menu);
            delayTask(BUTTON_TASK_DELAY / ADD_BUTTON_DELAY);
        }
        else if (digitalRead(UP_PIN) == HIGH && buttonPressed != Menu && buttonPressed != Back)
        {
            setButton(Up);
            delayTask(BUTTON_TASK_DELAY / ADD_BUTTON_DELAY);
        }
        else if (digitalRead(DOWN_PIN) == HIGH && buttonPressed != Up && buttonPressed != Menu && buttonPressed != Back)
        {
            setButton(Down);
            delayTask(BUTTON_TASK_DELAY / ADD_BUTTON_DELAY);
        }
    }
}

void initButtonTask()
{
    xTaskCreate(
        loopButtonsTask,
        "buttonTask",
        2000,
        NULL,
        0,
        &buttonTask);
}

#if DEBUG
void dumpButtons()
{
    if (digitalRead(MENU_PIN) == 1)
    {
        log("Menu button pressed");
    }
    else if (digitalRead(BACK_PIN) == 1)
    {
        log("Back button pressed");
    }
    else if (digitalRead(UP_PIN) == 1)
    {
        log("Up button pressed");
    }
    else if (digitalRead(DOWN_PIN) == 1)
    {
        log("Down button pressed");
    }
}

String getButtonString(buttonState state)
{
    switch (state)
    {
    case None:
        return "None";
    case Back:
        return "Back";
    case Menu:
        return "Menu";
    case Up:
        return "Up";
    case Down:
        return "Down";
    case LongBack:
        return "LongBack";
    case LongMenu:
        return "LongBack";
    }
    return "None";
}
#endif
