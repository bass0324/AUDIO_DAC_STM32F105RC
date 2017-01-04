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

#include "ch.h"
#include "hal.h"
#include "test.h"
#include "tda7468.h"

/*
 * Red LED blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {

  (void)arg;
  chRegSetThreadName("blinker");
  while (true) {
    palClearPad(GPIOC, DEBUG_LED1);
    chThdSleepMilliseconds(500);
    palSetPad(GPIOC, DEBUG_LED1);
    chThdSleepMilliseconds(500);
    palClearPad(GPIOC, DEBUG_LED1);
    chThdSleepMilliseconds(500);
    palClearPad(GPIOC, DEBUG_LED2);
    chThdSleepMilliseconds(500);
    palSetPad(GPIOC, DEBUG_LED2);
    chThdSleepMilliseconds(500);
    palClearPad(GPIOC, DEBUG_LED2);
    chThdSleepMilliseconds(500);
    palClearPad(GPIOC, DEBUG_LED3);
    chThdSleepMilliseconds(500);
    palSetPad(GPIOC, DEBUG_LED3);
    chThdSleepMilliseconds(500);
    palClearPad(GPIOC, DEBUG_LED3);
    chThdSleepMilliseconds(500);
    palClearPad(GPIOC, DEBUG_LED4);
    chThdSleepMilliseconds(500);
    palSetPad(GPIOC, DEBUG_LED4);
    chThdSleepMilliseconds(500);
    palClearPad(GPIOC, DEBUG_LED4);
    chThdSleepMilliseconds(500);
  }
}

int InitTda7468(I2CDriver *i2cp) {
static InputSelectTypeDef inputSelect = {(uint8_t)TDA7468_INPUT_SELECT_INPUT1,
                                      (uint8_t)TDA7468_INPUT_MUTE_OFF,
                                      (uint8_t)TDA7468_MIC_GAIN_0DB,
                                      (uint8_t)TDA7468_MIC_OFF};
static uint8_t inputGain = TDA7468_INPUT_GAIN_14DB;
static SurroundTypeDef surround = {      (uint8_t)TDA7468_SURROUND_MODE_OFF,
                                      (uint8_t)TDA7468_SURROUND_GAIN_0DB,
                                      (uint8_t)TDA7468_SURROUND_MIX_ZERO,
                                      (uint8_t)TDA7468_SURROUND_BUFFER_GAIN_0DB};
static VolumeTypeDef volumeLeft = {      (uint8_t)TDA7468_VOLUME1_1DB_STEPS_0DB,
                                      (uint8_t)TDA7468_VOLUME1_8DB_STEPS_0DB,
                                      (uint8_t)TDA7468_VOLUME2_8DB_STEPS_0DB};
static VolumeTypeDef volumeRight = {     (uint8_t)TDA7468_VOLUME1_1DB_STEPS_0DB,
                                      (uint8_t)TDA7468_VOLUME1_8DB_STEPS_0DB,
                                      (uint8_t)TDA7468_VOLUME2_8DB_STEPS_0DB};
static TrebleBassTypeDef trebleBass = {  (uint8_t)TDA7468_TREBLE_0DB,
                                      (uint8_t)TDA7468_BASS_0DB};
static uint8_t output = (uint8_t)TDA7468_OUTPUT_MUTE_OFF;
static BassALCTypeDef bassALC = {        (uint8_t)TDA7468_BASS_ALC_OFF,
                                      (uint8_t)TDA7468_BASS_ALC_DETECTOR_OFF,
                                      (uint8_t)TDA7468_RELEASE_CURRENT_CIRCUIT_OFF,
                                      (uint8_t)TDA7468_ATTACK_TIME_RESISTOR_12P5K,
                                      (uint8_t)TDA7468_BASS_ALC_THRESHOLD_700MV,
                                      (uint8_t)TDA7468_ALC_ATTACK_MODE_FIXED_RES};
TDA7468TypeDef tda7468Registers = {   inputSelect,
                                      inputGain,
                                      surround,
                                      volumeLeft,
                                      volumeRight,
                                      trebleBass,
                                      output,
                                      bassALC};
  tda7468_i2c_write_all(i2cp, &tda7468Registers);
}

void setInputLed(uint8_t inputSelect) {
	if (inputSelect == 0)
		palSetPad(GPIOC, DEBUG_LED1);
	else
		palClearPad(GPIOC, DEBUG_LED1);

	if (inputSelect == 1)
                palSetPad(GPIOC, DEBUG_LED2);
        else
                palClearPad(GPIOC, DEBUG_LED2);

	if (inputSelect == 2)
                palSetPad(GPIOC, DEBUG_LED3);
        else
                palClearPad(GPIOC, DEBUG_LED3);

	if (inputSelect == 3)
                palSetPad(GPIOC, DEBUG_LED4);
        else
                palClearPad(GPIOC, DEBUG_LED4);
}

/*
 * Application entry point.
 */
int main(void) {
  static InputSelectTypeDef inputSelect;
  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  /*
   * Activates the serial driver 2 using the driver default configuration.
   */
  sdStart(&SD3, NULL);

  /*
   * Activate the I2C Driver
   */
  palSetPadMode(GPIOB, 6, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
  palSetPadMode(GPIOB, 7, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);

  I2CConfig i2cConfig = {
    OPMODE_I2C,
    100000,
    STD_DUTY_CYCLE
  };
  //i2cInit();
  i2cStart(&I2CD1, &i2cConfig);
  chThdSleepMilliseconds(100);  

  InitTda7468(&I2CD1);

  /*
   * Creates the blinker thread.
   */
  //chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state.
   */
  while (true) {
    if (!palReadPad(GPIOA, AUDIO_BUTTON)) {
      if (inputSelect.InputSelect < 3) {
	inputSelect.InputSelect++;
      } else {
        inputSelect.InputSelect = 0;
      }
	setInputLed(inputSelect.InputSelect);
	tda7468_set_input_select_register(&I2CD1, &inputSelect);
    }
    chThdSleepMilliseconds(500);
  }
}
