//
// Created by penguinencounter on 3/28/24.
//
#include <bsp.h>
#include <fpioa.h>
#include <gpiohs.h>
#include <plic.h>
#include <pwm.h>
#include <spi.h>
#include <sysctl.h>
#include <timer.h>

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
    // RGB LED
    fpioa_set_function(0x20, FUNC_TIMER2_TOGGLE1);
    fpioa_set_function(0x1e, FUNC_TIMER2_TOGGLE2);
    fpioa_set_function(0x1f, FUNC_TIMER2_TOGGLE3);
    // White LEDs
    fpioa_set_function(0x17, FUNC_TIMER1_TOGGLE1);

    // Buttons
    fpioa_set_function(0x27, FUNC_GPIOHS2);
    fpioa_set_function(0x26, FUNC_GPIOHS3);
    fpioa_set_function(0x25, FUNC_GPIOHS4);
    fpioa_set_function(0x24, FUNC_GPIOHS5);

    gpiohs_set_drive_mode(2, GPIO_DM_INPUT);
    gpiohs_set_drive_mode(3, GPIO_DM_INPUT);
    gpiohs_set_drive_mode(4, GPIO_DM_INPUT);
    gpiohs_set_drive_mode(5, GPIO_DM_INPUT);

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

    pwm_init(PWM_DEVICE_2);
    pwm_init(PWM_DEVICE_1);

    rgb(0.0, 0.0, 0.0);

    enable_pwms();

    pwm_set_frequency(PWM_DEVICE_1, PWM_CHANNEL_0, 100000.0, 0.01);
    pwm_set_enable(PWM_DEVICE_1, PWM_CHANNEL_0, 1);

    for(;;)
    {
        msleep(50);
        int set_1 = !gpiohs_get_pin(2);  // nav-left
        int set_2 = !gpiohs_get_pin(3);  // nav-press
        int set_3 = !gpiohs_get_pin(4);  // nav-right
        int button = !gpiohs_get_pin(5); // learn
        rgb(0.2 * (set_1 | button) + 0.025, 0.2 * (set_2 | button) + 0.0, 0.2 * (set_3 | button) + 0.0);
    }
}