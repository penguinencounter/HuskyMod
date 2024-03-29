//
// Created by penguinencounter on 3/28/24.
//

#ifndef HUSKYMOD_HUSKYLENS_H
#define HUSKYMOD_HUSKYLENS_H

#include "fpioa.h"
namespace hl
{
enum devices_t
{
    NoDevices = 0,
    RGBLed = 1,
    WhiteLed = 2,
    Buttons = 4,
    AllDevices = RGBLed | WhiteLed | Buttons
};

inline devices_t operator|(devices_t left, devices_t right)
{
    return devices_t(int(left) | int(right));
}

const int GPIO_LEARN = 5;
const int GPIO_DIAL_LEFT = 2;
const int GPIO_DIAL_PRESS = 3;
const int GPIO_DIAL_RIGHT = 4;

struct button_state
{
    bool learn : 1;
    bool dial_left : 1;
    bool dial_press : 1;
    bool dial_right : 1;
};

/**
 * Setup devices.
 */
void setup(devices_t devices);

/**
 * Set up the RGB LED for usage.
 */
void setup_rgb();
/**
 * Set the color of the RGB LED.
 */
void set_rgb(double r, double g, double b);

/**
 * Set up the two white LEDs for usage.
 */
void setup_white();
/**
 * Set the brightness of the white LEDs.
 */
void set_white(double brightness);

/**
 * Configure the GPIO pins connected to the Buttons and dial.
 */
void setup_buttons();

/**
 * Get the state of the physical Buttons.
 */
button_state get_buttons();
} // namespace hl

#endif // HUSKYMOD_HUSKYLENS_H
