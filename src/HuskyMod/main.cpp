//
// Created by penguinencounter on 3/28/24.
//
#include <bsp.h>
#include <fpioa.h>
#include <pwm.h>
#include <spi.h>
#include "huskylens.h"

void enable_pwms()
{
    pwm_set_enable(PWM_DEVICE_2, PWM_CHANNEL_0, 1);
    pwm_set_enable(PWM_DEVICE_2, PWM_CHANNEL_1, 1);
    pwm_set_enable(PWM_DEVICE_2, PWM_CHANNEL_2, 1);
}

void rgb(double r, double g, double b)
{
    pwm_set_frequency(PWM_DEVICE_2, PWM_CHANNEL_0, 100000.0, r);
    pwm_set_frequency(PWM_DEVICE_2, PWM_CHANNEL_1, 100000.0, g);
    pwm_set_frequency(PWM_DEVICE_2, PWM_CHANNEL_2, 100000.0, b);
}

int main()
{
    hl::setup(hl::AllDevices);

    // Unknown from 000537d2
    fpioa_set_function(0x2f, FUNC_CMOS_PCLK);
    fpioa_set_function(0x2e, FUNC_CMOS_XCLK);
    fpioa_set_function(0x2d, FUNC_CMOS_HREF);
    fpioa_set_function(0x2c, FUNC_CMOS_PWDN);
    fpioa_set_function(0x2b, FUNC_CMOS_VSYNC);
    fpioa_set_function(0x2a, FUNC_CMOS_RST);
    // Serial Camera Control Bus
    fpioa_set_function(0x28, FUNC_SCCB_SCLK);
    fpioa_set_function(0x29, FUNC_SCCB_SDA);
    // 00057ad4
    fpioa_set_function(0x06, FUNC_UART1_RX);
    fpioa_set_function(0x07, FUNC_UART1_TX);
    fpioa_set_function(0x22, FUNC_I2C0_SCLK); // conflict 1 (used to switch I2C and UART?)
    fpioa_set_function(0x23, FUNC_I2C0_SDA);  // conflict 2

    // 0005ac70; display (probably)
    fpioa_set_function(0x1b, FUNC_SPI1_SCLK);
    fpioa_set_function(0x1c, FUNC_SPI1_D0);
    fpioa_set_function(0x1a, FUNC_SPI1_D1);
    fpioa_set_function(0x1d, FUNC_SPI1_SS3);

    spi_init(SPI_DEVICE_1, SPI_WORK_MODE_0, SPI_FF_STANDARD, 8, 0);
    // 0005afaa
    fpioa_set_function(0x08, FUNC_I2C0_SCLK);
    fpioa_set_function(0x09, FUNC_I2C0_SDA);
    fpioa_set_function(0x04, FUNC_UART3_RX);
    fpioa_set_function(0x05, FUNC_UART3_TX);
    // 0005b080
    // fpioa_set_function(0x08,FUNC_I2C0_SCLK); // dup
    // fpioa_set_function(0x09,FUNC_I2C0_SDA); // dup
    // fpioa_set_function(0x22,FUNC_UART1_RX);  // conflict 1
    // fpioa_set_function(0x0a,FUNC_UART1_TX);

    // 0005bc72
    // conditional
    // fpioa_set_function(0x23,FUNC_UART1_TX); // conflict 2

    hl::set_rgb(0.0, 0.0, 0.0);
    hl::set_white(0.01);

    for(;;)
    {
        msleep(50);
        hl::button_state buttons = hl::get_buttons();
        bool set_1 = buttons.dial_left;
        bool set_2 = buttons.dial_press;
        bool set_3 = buttons.dial_right;
        bool button = buttons.learn;
        hl::set_rgb(0.2 * (set_1 | button) + 0.025, 0.2 * (set_2 | button) + 0.0, 0.2 * (set_3 | button) + 0.0);
    }
}