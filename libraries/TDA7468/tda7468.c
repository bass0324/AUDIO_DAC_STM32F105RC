#include <tda7468.h>

const uint8_t initTxBuffer[] = {0x10, 0x20, 0x00, 0x18, 0x00, 0x00, 0xFF, 0x01, 0x00};
const uint8_t TDA7468_INPUT_SELECT_MIC_SHIFTS[4] = {0, 2, 3, 5};
const uint8_t TDA7468_INPUT_SELECT_MIC_MASK[4] = {0x03, 0x04, 0x18, 0x20};
const uint8_t TDA7468_SURROUND_MODE_REGISTER_SHIFTS[4] = {0, 1, 3, 6};
const uint8_t TDA7468_SURROUND_MODE_REGISTER_MASK[4] = {0x01, 0x06, 0x38, 0x40};
const uint8_t TDA7468_BASS_ALC_REGISTER_SHIFTS[6] = {0, 1, 2, 3, 5, 7};
const uint8_t TDA7468_BASS_ALC_REGISTER_MASK[6] = {0x01, 0x02, 0x04, 0x18, 0x60, 0x80};

int tda7468_i2c_write_all(I2CDriver *i2cp, TDA7468TypeDef *tda7468_registers) {
	uint8_t aTxBuffer[] = { (uint8_t) 0x10,
					(uint8_t)(((*tda7468_registers).InputSelect.InputSelect << TDA7468_INPUT_SELECT_MIC_SHIFTS[0]) |
						((*tda7468_registers).InputSelect.InputMute << TDA7468_INPUT_SELECT_MIC_SHIFTS[1]) |
						((*tda7468_registers).InputSelect.MicGain << TDA7468_INPUT_SELECT_MIC_SHIFTS[2]) |
						((*tda7468_registers).InputSelect.MicControl << TDA7468_INPUT_SELECT_MIC_SHIFTS[3])),
					(uint8_t)(*tda7468_registers).InputGain,
					(uint8_t)(((*tda7468_registers).Surround.SurroundMode << TDA7468_SURROUND_MODE_REGISTER_SHIFTS[0]) |
						((*tda7468_registers).Surround.Gain << TDA7468_SURROUND_MODE_REGISTER_SHIFTS[1]) |
						((*tda7468_registers).Surround.Mixing << TDA7468_SURROUND_MODE_REGISTER_SHIFTS[2]) |
						((*tda7468_registers).Surround.BufferGain << TDA7468_SURROUND_MODE_REGISTER_SHIFTS[3])),
					(uint8_t)(((*tda7468_registers).VolumeLeft.onedbSteps) |//<< (uint8_t)*TDA7468_VOLUME_SHIFTS[0] |
						((*tda7468_registers).VolumeLeft.eightdbSteps) |//<< (uint8_t)*TDA7468_VOLUME_SHIFTS[1] |
						((*tda7468_registers).VolumeLeft.Volume2)),//<< (uint8_t)*TDA7468_VOLUME_SHIFTS[2],
					(uint8_t)(((*tda7468_registers).VolumeRight.onedbSteps) |//<< (uint8_t)*TDA7468_VOLUME_SHIFTS[0] |
						((*tda7468_registers).VolumeRight.eightdbSteps) |//<< (uint8_t)*TDA7468_VOLUME_SHIFTS[1] |
						((*tda7468_registers).VolumeRight.Volume2)),//<< (uint8_t)*TDA7468_VOLUME_SHIFTS[2],
					(uint8_t)(((*tda7468_registers).TrebleBass.Treble) |
						((*tda7468_registers).TrebleBass.Bass)),
					(uint8_t)(*tda7468_registers).Output,
					(uint8_t)(((*tda7468_registers).BassALC.ALCMode << TDA7468_BASS_ALC_REGISTER_SHIFTS[0]) |
						((*tda7468_registers).BassALC.Detector << TDA7468_BASS_ALC_REGISTER_SHIFTS[1]) |
						((*tda7468_registers).BassALC.ReleaseCurrentCircuit << TDA7468_BASS_ALC_REGISTER_SHIFTS[2]) |
						((*tda7468_registers).BassALC.AttackTimeResistor << TDA7468_BASS_ALC_REGISTER_SHIFTS[3]) |
						((*tda7468_registers).BassALC.Threshold << TDA7468_BASS_ALC_REGISTER_SHIFTS[4]) |
						((*tda7468_registers).BassALC.AttackMode << TDA7468_BASS_ALC_REGISTER_SHIFTS[5]))
	};
	uint8_t aRxBuffer[] = {0};;
	//int error = HAL_I2C_Master_Transmit(I2cHandle, (uint16_t)tda7468_i2c_base_address, (uint8_t*)aTxBuffer, 9, 10000);
	i2cAcquireBus(i2cp);
	int error = i2cMasterTransmit(i2cp, tda7468_i2c_base_address >> 1, &aTxBuffer[0], 9, &aRxBuffer[0], 0);
	//int error = i2cMasterTransmitTimeout(i2cp, (i2caddr_t)tda7468_i2c_base_address, &initTxBuffer[0], 9, &aRxBuffer[0], 0, TIME_INFINITE);
	//int error = i2cMasterTransmit(i2cp, 0x88 >> 1, &initTxBuffer[0], 9, &aRxBuffer[0], 0);
	i2cReleaseBus(i2cp);
	return error;
}

int tda7468_i2c_write_single(I2CDriver *i2cp, uint8_t registerValue, uint8_t txData) {
	uint8_t aTxBuffer[] = {registerValue, txData};
	uint8_t aRxBuffer[] = {0};
	//int error = HAL_I2C_Master_Transmit(I2cHandle, (uint16_t)tda7468_i2c_base_address, (uint8_t*)aTxBuffer, 2, 10000);
	i2cAcquireBus(i2cp);
	int error = i2cMasterTransmit(i2cp, tda7468_i2c_base_address >> 1, &aTxBuffer[0], 2, &aRxBuffer[0], 0);
	i2cReleaseBus(i2cp);
	return error;
}

int tda7468_init(I2CDriver *i2cp,TDA7468TypeDef *tda7468_registers) {
	/*I2CConfig i2cConfig = {
		OPMODE_I2C,
		100000,
		STD_DUTY_CYCLE
	};
	i2cStart(i2cp, i2cConfig);*/
	//*tda7468_registers = initTypeDef;
	tda7468_i2c_write_all(i2cp, tda7468_registers);
	//HAL_I2C_Master_Transmit(I2cHandle, (uint16_t)tda7468_i2c_base_address, (uint8_t*)initTxBuffer, 9, 10000);
	return 0;
}

int tda7468_set_input_select_register(I2CDriver *i2cp, InputSelectTypeDef *inputSelectTypeDef) {
	int error = tda7468_i2c_write_single(	i2cp,
								(uint8_t)TDA7468_REGISTERS_INPUT_SELECT_MIC,
								(uint8_t)((*inputSelectTypeDef).InputSelect |
										(*inputSelectTypeDef).MicGain |
										(*inputSelectTypeDef).MicControl));
	return error;
}

int tda7468_set_input_gain_register(I2CDriver *i2cp, uint8_t *inputGainSetting){
	int error = tda7468_i2c_write_single(	i2cp,
											(uint8_t)TDA7468_REGISTERS_INPUT_GAIN,
											*inputGainSetting);
	return error;
}
int tda7468_set_surround_register(I2CDriver *i2cp, SurroundTypeDef *surroundTypeDef){
	int error = tda7468_i2c_write_single(	i2cp,
											(uint8_t)TDA7468_REGISTERS_SURROUND,
											(uint8_t)((*surroundTypeDef).SurroundMode |
													(*surroundTypeDef).Gain |
													(*surroundTypeDef).Mixing |
													(*surroundTypeDef).BufferGain) );
	return error;
}
int tda7468_set_volume_left_register(I2CDriver *i2cp, VolumeTypeDef *volumeLeftTypeDef){
	int error = tda7468_i2c_write_single(	i2cp,
											(uint8_t)TDA7468_REGISTERS_VOLUME_LEFT,
											(uint8_t)((*volumeLeftTypeDef).onedbSteps |
													(*volumeLeftTypeDef).eightdbSteps |
													(*volumeLeftTypeDef).Volume2));
	return error;
}
int tda7468_set_volume_right_register(I2CDriver *i2cp, VolumeTypeDef *volumeRightTypeDef){
	int error = tda7468_i2c_write_single(	i2cp,
											(uint8_t)TDA7468_REGISTERS_VOLUME_RIGHT,
											(uint8_t)((*volumeRightTypeDef).onedbSteps |
													(*volumeRightTypeDef).eightdbSteps |
													(*volumeRightTypeDef).Volume2));
	return error;
}
int tda7468_set_treble_bass_register(I2CDriver *i2cp, TrebleBassTypeDef *trebleBassTypeDef) {
	int error = tda7468_i2c_write_single(	i2cp,
											(uint8_t)TDA7468_REGISTERS_TREBLE_BASS,
											(uint8_t)((*trebleBassTypeDef).Treble |
													(*trebleBassTypeDef).Bass) );
	return error;
}
int tda7468_set_output_register(I2CDriver *i2cp, uint8_t *outputSetting){
	int error = tda7468_i2c_write_single(	i2cp,
											(uint8_t)TDA7468_REGISTERS_OUTPUT,
											*outputSetting);
	return error;
}
int tda7468_set_bass_alc_register(I2CDriver *i2cp, BassALCTypeDef *bassALCTypeDef){
	int error = tda7468_i2c_write_single(	i2cp,
											(uint8_t)TDA7468_REGISTERS_BASS_ALC,
											(uint8_t)((*bassALCTypeDef).ALCMode |
													(*bassALCTypeDef).Detector |
													(*bassALCTypeDef).ReleaseCurrentCircuit |
													(*bassALCTypeDef).AttackTimeResistor |
													(*bassALCTypeDef).Threshold |
													(*bassALCTypeDef).AttackMode) );
	return error;
}
