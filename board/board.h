/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for the ST INEMO-M1 Discovery board.
 */

/*
 * Board identifier.
 */
#define BOARD_ST_NUCLEO_F103RB
#define BOARD_NAME              "STMicroelectronics NUCLEO-F103RB"

/*
 * Board frequencies.
 */

#define STM32_LSECLK            32768
#define STM32_HSECLK            25000000

/*
 * MCU type, supported types are defined in ./os/hal/platforms/hal_lld.h.
 */
#define STM32F105xC

/*
 * IO pins assignments.
 */
#define NEXT_BUTTON             0
#define PREVIOUS_BUTTON         1
#define STOP_BUTTON             2
#define PLAY_PAUSE_BUTTON       3
#define MUTE_BUTTON             4
#define VOLUME_UP_BUTTON        5
#define VOLUME_DN_BUTTON        6
#define SOURCE_BUTTON           7
#define AUDIO_BUTTON            8
#define USART1_TX               9
#define USART1_RX               10
#define STM_USB_DM              11
#define STM_USB_DN              12
#define SWDIO                   13
#define SWCLK                   14
#define SPI3_NSS                15

#define PB0                     0
#define PB1                     1
#define BOOT1                   2
#define SPI3_SCK                3
#define SPI3_MISO               4
#define SPI3_MOSI               5
#define I2C1_SCL                6
#define I2C1_SDA                7
#define PB8                     8
#define PB9                     9
#define USART3_TX               10
#define USART3_RX               11
#define SPI2_NSS                12
#define SPI2_SCK                13
#define SPI2_MISO               14
#define SPI2_MOSI               15

#define VOLUME_DN_USB           0
#define VOLUME_UP_USB           1
#define MUTE_USB                2
#define NEXT_USB                3
#define VOLUME_UP_BT            4
#define VOLUME_DN_BT            5
#define DEBUG_LED1              6
#define DEBUG_LED2              7
#define DEBUG_LED3              8
#define DEBUG_LED4              9
#define NEXT_BT                 10
#define PREVIOUS_BT             11
#define PLAY_PAUSE_BT           12
#define PLAY_PAUSE_USB          13
#define PREVIOUS_USB            14
#define STOP_USB                15

#define GPIOD_OSC_IN            0
#define GPIOD_OSC_OUT           1
#define MUTE_BT                 2

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 *
 * The digits have the following meaning:
 *   0 - Analog input.
 *   1 - Push Pull output 10MHz.
 *   2 - Push Pull output 2MHz.
 *   3 - Push Pull output 50MHz.
 *   4 - Digital input.
 *   5 - Open Drain output 10MHz.
 *   6 - Open Drain output 2MHz.
 *   7 - Open Drain output 50MHz.
 *   8 - Digital input with PullUp or PullDown resistor depending on ODR.
 *   9 - Alternate Push Pull output 10MHz.
 *   A - Alternate Push Pull output 2MHz.
 *   B - Alternate Push Pull output 50MHz.
 *   C - Reserved.
 *   D - Alternate Open Drain output 10MHz.
 *   E - Alternate Open Drain output 2MHz.
 *   F - Alternate Open Drain output 50MHz.
 * Please refer to the STM32 Reference Manual for details.
 */

/*
 * Port A setup.
 * PA0	- Input with pull-up		(NEXT_BUTTON)
 * PA1	- Input with pull-up		(PREVIOUS_BUTTON)
 * PA2	- Input with pull-up		(STOP_BUTTON)
 * PA3	- Input with pull-up		(PLAY_PAUSE_BUTTON)
 * PA4	- Input with pull-up		(MUTE_BUTTON)
 * PA5	- Input with pull-up		(VOLUME_UP_BUTTON)
 * PA6	- Input with pull-up		(VOLUME_DN_BUTTON)
 * PA7	- Input with pull-up		(SOURCE_BUTTON)
 * PA8	- Input with pull-up		(AUDIO_BUTTON)
 * PA9	- Alternate PP output 50MHz	(USART1_TX)
 * PA10	- Digital Input			(USART1_RX)
 * PA11	- Input with pull-down		(STM_USB_DM; UNUSED)
 * PA12	- Input with pull-down		(STM_USB_DN; UNUSED)
 * PA13	- Input with pull-up		(SWDIO)
 * PA14	- Input with pull-down		(SWCLK)
 * PA15	- Input with pull-up		(SPI3_NSS; UNUSED)
 */
#define VAL_GPIOACRL            0x88888888      /*  PA7...PA0 */
#define VAL_GPIOACRH            0x888884B8      /* PA15...PA8 */
#define VAL_GPIOAODR            0xFFFF57FF

/*
 * Port B setup.
 * PB0	- Input with pull-up		(PB0)
 * PB1	- Input with pull-up		(PB1)
 * PB2	- Input with pull-up		(BOOT1)
 * PB3	- Input with pull-up		(SPI3_SCK; UNUSED)
 * PB4	- Input with pull-up		(SPI3_MISO; UNUSED)
 * PB5	- Input with pull-up		(SPI3_MOSI; UNUSED)
 * PB6	- Alternate Open Drain 50MHz	(I2C1_SCL)
 * PB7	- Alternate Open Drain 50MHz	(I2C1_SDA)
 * PB8	- Input with pull-up		(PB8)
 * PB9	- Input with pull-up		(PB9)
 * PB10	- Alternate PP output 50MHz	(USART3_TX)
 * PB11	- Digital Input			(USART3_RX)
 * PB12	- Input with pull-up		(SPI2_NSS; UNUSED)
 * PB13	- Input with pull-up		(SPI2_SCK; UNUSED)
 * PB14	- Input with pull-up		(SPI2_MISO; UNUSED)
 * PB15	- Input with pull-up		(SPI2_MOSI; UNUSED)
 */
#define VAL_GPIOBCRL            0xFF888888      /*  PB7...PB0 */
#define VAL_GPIOBCRH            0x88884B88      /* PB15...PB8 */
#define VAL_GPIOBODR            0xFFFFFFFF

/*
 * Port C setup.
 * PC0  - Push-pull output
 * PC1  - Push-pull output
 * PC2  - Push-pull output
 * PC3  - Push-pull output
 * PC4  - Push-pull output
 * PC5  - Push-pull output
 * PC6  - Push-pull output
 * PC7  - Push-pull output
 * PC8  - Push-pull output
 * PC9  - Push-pull output
 * PC10 - Push-pull output
 * PC11 - Push-pull output
 * PC12 - Push-pull output
 * PC13 - Push-pull output
 * PC14 - Push-pull output
 * PC15 - Push-pull output
 */
#define VAL_GPIOCCRL            0x33333333      /*  PC7...PC0 */
#define VAL_GPIOCCRH            0x33333333      /* PC15...PC8 */
#define VAL_GPIOCODR            0xFFFF0000

/*
 * Port D setup.
 * Everything input with pull-up except:
 * PD0  - Normal input              	(GPIOD_OSC_IN).
 * PD1  - Normal input              	(GPIOD_OSC_OUT).
 * PD2	- Push-pull output		(MUTE_BT)
 */
#define VAL_GPIODCRL            0x88888344      /*  PD7...PD0 */
#define VAL_GPIODCRH            0x88888888      /* PD15...PD8 */
#define VAL_GPIODODR            0xFFFFFFFF

/*
 * Port E setup.
 * Everything input with pull-up except:
 */
#define VAL_GPIOECRL            0x88888888      /*  PE7...PE0 */
#define VAL_GPIOECRH            0x88888888      /* PE15...PE8 */
#define VAL_GPIOEODR            0xFFFFFFFF

/*
 * USB bus activation macro, required by the USB driver.
 */
#define usb_lld_connect_bus(usbp)

/*
 * USB bus de-activation macro, required by the USB driver.
 */
#define usb_lld_disconnect_bus(usbp)

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
