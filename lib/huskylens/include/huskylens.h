//
// Created by penguinencounter on 3/28/24.
//

#ifndef HUSKYMOD_HUSKYLENS_H
#define HUSKYMOD_HUSKYLENS_H

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

inline devices_t operator|(const devices_t left, const devices_t right)
{
    return static_cast<devices_t>(static_cast<int>(left) | static_cast<int>(right));
}

constexpr int GPIO_LEARN = 5;
constexpr int GPIO_DIAL_LEFT = 2;
constexpr int GPIO_DIAL_PRESS = 3;
constexpr int GPIO_DIAL_RIGHT = 4;

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
void init(devices_t devices);

/**
 * Set up the RGB LED for usage.
 */
void rgb_init();
/**
 * Set the color of the RGB LED.
 */
void rgb_set(double r, double g, double b);

/**
 * Set up the two white LEDs for usage.
 */
void white_init();
/**
 * Set the brightness of the white LEDs.
 */
void white_set(double brightness);

/**
 * Configure the GPIO pins connected to the Buttons and dial.
 */
void buttons_init();

/**
 * Get the state of the physical Buttons.
 */
button_state buttons_get();
} // namespace hl

#endif // HUSKYMOD_HUSKYLENS_H
