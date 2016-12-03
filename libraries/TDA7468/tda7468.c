#include <tda7468.h>

//extern uint8_t initTxBuffer[];

int tda7468_i2c_write_all(I2C_HandleTypeDef *I2cHandle, TDA7468TypeDef *tda7468_registers) {
	uint8_t aTxBuffer[] = { (uint8_t) 0x10,
							(uint8_t)((*tda7468_registers).InputSelect.InputSelect |
								(*tda7468_registers).InputSelect.MicGain |
								(*tda7468_registers).InputSelect.MicControl),
							(*tda7468_registers).InputGain,
							(uint8_t)((*tda7468_registers).Surround.SurroundMode |
								(*tda7468_registers).Surround.Gain |
								(*tda7468_registers).Surround.Mixing |
								(*tda7468_registers).Surround.BufferGain),
							(uint8_t)((*tda7468_registers).VolumeLeft.onedbSteps |
								(*tda7468_registers).VolumeLeft.eightdbSteps |
								(*tda7468_registers).VolumeLeft.Volume2),
							(uint8_t)((*tda7468_registers).VolumeRight.onedbSteps |
								(*tda7468_registers).VolumeRight.eightdbSteps |
								(*tda7468_registers).VolumeRight.Volume2),
							(uint8_t)((*tda7468_registers).TrebleBass.Treble |
								(*tda7468_registers).TrebleBass.Bass),
							(*tda7468_registers).Output,
							(uint8_t)((*tda7468_registers).BassALC.ALCMode |
								(*tda7468_registers).BassALC.Detector |
								(*tda7468_registers).BassALC.ReleaseCurrentCircuit |
								(*tda7468_registers).BassALC.AttackTimeResistor |
								(*tda7468_registers).BassALC.Threshold |
								(*tda7468_registers).BassALC.AttackMode)
	};
	int error = HAL_I2C_Master_Transmit(I2cHandle, (uint16_t)tda7468_i2c_base_address, (uint8_t*)aTxBuffer, 9, 10000);
	return error;
}

int tda7468_i2c_write_single(I2C_HandleTypeDef *I2cHandle, uint8_t registerValue, uint8_t txData) {
	uint8_t aTxBuffer[] = {registerValue, txData};
	int error = HAL_I2C_Master_Transmit(I2cHandle, (uint16_t)tda7468_i2c_base_address, (uint8_t*)aTxBuffer, 2, 10000);
	return error;
}

int tda7468_init(I2C_HandleTypeDef *I2cHandle,TDA7468TypeDef *tda7468_registers) {
	//*tda7468_registers = initTypeDef;
	tda7468_i2c_write_all(I2cHandle, tda7468_registers);
	//HAL_I2C_Master_Transmit(I2cHandle, (uint16_t)tda7468_i2c_base_address, (uint8_t*)initTxBuffer, 9, 10000);
	return 0;
}

int tda7468_set_input_select_register(I2C_HandleTypeDef *I2cHandle,InputSelectTypeDef *inputSelectTypeDef) {
	int error = tda7468_i2c_write_single(	I2cHandle,
								(uint8_t)tda7468_input_select_mic_register,
								(uint8_t)((*inputSelectTypeDef).InputSelect |
										(*inputSelectTypeDef).MicGain |
										(*inputSelectTypeDef).MicControl));
	return error;
}

int tda7468_set_input_gain_register(I2C_HandleTypeDef *I2cHandle,uint8_t *inputGainSetting){
	int error = tda7468_i2c_write_single(	I2cHandle,
											(uint8_t)tda7468_input_gain_register,
											*inputGainSetting);
	return error;
}
int tda7468_set_surround_register(I2C_HandleTypeDef *I2cHandle,SurroundTypeDef *surroundTypeDef){
	int error = tda7468_i2c_write_single(	I2cHandle,
											(uint8_t)tda7468_surround_register,
											(uint8_t)((*surroundTypeDef).SurroundMode |
													(*surroundTypeDef).Gain |
													(*surroundTypeDef).Mixing |
													(*surroundTypeDef).BufferGain) );
	return error;
}
int tda7468_set_volume_left_register(I2C_HandleTypeDef *I2cHandle,VolumeTypeDef *volumeLeftTypeDef){
	int error = tda7468_i2c_write_single(	I2cHandle,
											(uint8_t)tda7468_volume_left_register,
											(uint8_t)((*volumeLeftTypeDef).onedbSteps |
													(*volumeLeftTypeDef).eightdbSteps |
													(*volumeLeftTypeDef).Volume2));
	return error;
}
int tda7468_set_volume_right_register(I2C_HandleTypeDef *I2cHandle,VolumeTypeDef *volumeRightTypeDef){
	int error = tda7468_i2c_write_single(	I2cHandle,
											(uint8_t)tda7468_volume_right_register,
											(uint8_t)((*volumeRightTypeDef).onedbSteps |
													(*volumeRightTypeDef).eightdbSteps |
													(*volumeRightTypeDef).Volume2));
	return error;
}
int tda7468_set_treble_bass_register(I2C_HandleTypeDef *I2cHandle,TrebleBassTypeDef *trebleBassTypeDef) {
	int error = tda7468_i2c_write_single(	I2cHandle,
											(uint8_t)tda7468_treble_bass_register,
											(uint8_t)((*trebleBassTypeDef).Treble |
													(*trebleBassTypeDef).Bass) );
	return error;
}
int tda7468_set_output_register(I2C_HandleTypeDef *I2cHandle,uint8_t *outputSetting){
	int error = tda7468_i2c_write_single(	I2cHandle,
											(uint8_t)tda7468_output_register,
											*outputSetting);
	return error;
}
int tda7468_set_bass_alc_register(I2C_HandleTypeDef *I2cHandle,BassALCTypeDef *bassALCTypeDef){
	int error = tda7468_i2c_write_single(	I2cHandle,
											(uint8_t)tda7468_bass_alc_register,
											(uint8_t)((*bassALCTypeDef).ALCMode |
													(*bassALCTypeDef).Detector |
													(*bassALCTypeDef).ReleaseCurrentCircuit |
													(*bassALCTypeDef).AttackTimeResistor |
													(*bassALCTypeDef).Threshold |
													(*bassALCTypeDef).AttackMode) );
	return error;
}
