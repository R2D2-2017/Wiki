/**
 * \LedController.hh
 * \brief     blink a led for a given time
 * \author    Koen de groot
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

class LedController {
public:

 /**
 * \brief constructor for a led
 *
 * \param[in]     p     the wiringPi pin number the led is connected to
 */

    LedController(int p);
    
 /**
 * \brief blink led a given time
 *
 * \param[in]     pin     the wiringPi pin number
 * \param[in]     time    duration the led will be on in MS
 */

    void blinkLed(int time);
    
private:
    int pin;
};