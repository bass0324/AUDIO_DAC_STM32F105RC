//#include "stm32f1xx_hal.h"
#include "ch.h"
#include "hal.h"
#include "test.h"

#define tda7468_i2c_base_address 			0x88

typedef enum {
	TDA7468_REGISTERS_INPUT_SELECT_MIC,	//register 0x00; default should be 0x20
	TDA7468_REGISTERS_INPUT_GAIN,		//register 0x01; default should be 0x00
	TDA7468_REGISTERS_SURROUND,		//register 0x02; default should be 0x00
	TDA7468_REGISTERS_VOLUME_LEFT,		//register 0x03; default should be 0x00
	TDA7468_REGISTERS_VOLUME_RIGHT,		//register 0x04; default should be 0x00
	TDA7468_REGISTERS_TREBLE_BASS,		//register 0x05; default should be 0xFF
	TDA7468_REGISTERS_OUTPUT,		//register 0x06; default should be 0x01
	TDA7468_REGISTERS_BASS_ALC		//register 0x07; default should be 0x00
} TDA7468_REGISTERS;
#define TDA7468_REGISTERS_STRINGS                    (const char*[8]){"INPUT SELECT MIC", "INPUT GAIN", "SURROUND", "VOLUME LEFT", "VOLUME RIGHT", "TREBLE BASS", "OUTPUT", "BASS ALC"}

// INPUT SELECT & MIC VARIABLES
#ifndef TDA7468_INPUT_SELECT_MIC_SHIFTS 
//const uint8_t TDA7468_INPUT_SELECT_MIC_SHIFTS[4] = {0, 2, 3, 5};
//const uint8_t TDA7468_INPUT_SELECT_MIC_MASK[4] = {0x03, 0x04, 0x18, 0x20};
//#define TDA7468_INPUT_SELECT_MIC_SHIFTS	    (const uint8_t[4]){0, 2, 3, 5}
//#define TDA7468_INPUT_SELECT_MIC_MASK	    (const uint8_t[4])(0x03, 0x04, 0x18, 0x20}
#endif
#define TDA7468_INPUT_SELECT_MIC_STRINGS    (const char*[4]){"INPUT SELECT", "INPUT MUTE", "MIC GAIN", "MIC ENABLE"}

typedef enum {	
	TDA7468_INPUT_SELECT_INPUT1,		//value 0x00; INPUT 1 
	TDA7468_INPUT_SELECT_INPUT2, 		//value 0x01; INPUT 2
	TDA7468_INPUT_SELECT_INPUT3, 		//value 0x02; INPUT 3
	TDA7468_INPUT_SELECT_INPUT4		//value 0x03; INPUT 4
} TDA7468_INPUT_SELECT;
#define TDA7468_INPUT_SELECT_STRINGS	(const char*[4]){"INPUT 1", "INPUT 2", "INPUT 3", "INPUT 4"}

typedef enum {
	TDA7468_INPUT_MUTE_OFF,			//value 0x00; MUTE OFF
	TDA7468_INPUT_MUTE_ON			//value 0x04; MUTE ON
} TDA7468_INPUT_MUTE;
#define TDA7468_INPUT_MUTE_STRINGS      (const char*[2]){"OFF", "ON"}

typedef enum {
	TDA7468_MIC_GAIN_14DB,			//value 0x00
	TDA7468_MIC_GAIN_10DB,			//value 0x08
	TDA7468_MIC_GAIN_6DB,			//value 0x10
	TDA7468_MIC_GAIN_0DB			//value 0x18
} TDA7468_MIC_GAIN;
#define TDA7468_MIC_GAIN_STRINGS	(const char*[4]){"14DB", "10DB", "6DB", "0DB"}

typedef enum {
	TDA7468_MIC_ON,				//value 0x00
	TDA7468_MIC_OFF				//value 0x20
} TDA7468_MIC;
#define TDA7468_MIC_STRINGS    (const char*[2]){"ON", "OFF"}

// INPUT GAIN VARIABLES
#define TDA7468_INPUT_GAIN_STRINGS	(const char*[8]){"0DB", "2DB", "4DB", "6DB", "8DB", "10DB", "12DB", "14DB"}
typedef enum {
	TDA7468_INPUT_GAIN_0DB,			//value 0x00
	TDA7468_INPUT_GAIN_2DB,			//value 0x01
	TDA7468_INPUT_GAIN_4DB,			//value 0x02
	TDA7468_INPUT_GAIN_6DB,			//value 0x03
	TDA7468_INPUT_GAIN_8DB,			//value 0x04
	TDA7468_INPUT_GAIN_10DB,		//value 0x05
	TDA7468_INPUT_GAIN_12DB,		//value 0x06
	TDA7468_INPUT_GAIN_14DB			//value 0x07
} TDA7468_INPUT_GAIN;

// SURROUND MODE VARIABLES
//const uint8_t TDA7468_INPUT_SELECT_MIC_SHIFTS[4] = {0, 2, 3, 5};
//const uint8_t TDA7468_INPUT_SELECT_MIC_MASK[4] = {0x03, 0x04, 0x18, 0x20};
//const uint8_t TDA7468_SURROUND_MODE_REGISTER_SHIFTS[4] = {0, 1, 3, 6};
//const uint8_t TDA7468_SURROUND_MODE_REGISTER_MASK[4] = {0x01, 0x06, 0x38, 0x40};
//#define TDA7468_SURROUND_MODE_REGISTER_SHIFTS     	(const uint8_t*[4]){0, 1, 3, 6}
//#define TDA7468_SURROUND_MODE_REGISTER_MASK       	(const uint8_t*[4]){0x01, 0x06, 0x38, 0x40}
#define TDA7468_SURROUND_MODE_REGISTER_STRINGS  (const char*[4]){"SURROUND MODE", "SURROUND GAIN", "SURROUND MIX", "SURROUND BUFFER GAIN"}

typedef enum {
	TDA7468_SURROUND_MODE_OFF,		//value 0x00
	TDA7468_SURROUND_MODE_ON		//value 0x01
} TDA7468_SURROUND_MODE;
#define TDA7468_SURROUND_MODE_STRINGS  	(const char*[2]){"OFF", "ON"}

typedef enum {
	TDA7468_SURROUND_GAIN_0DB,		//value 0x00
	TDA7468_SURROUND_GAIN_6DB,		//value 0x02
	TDA7468_SURROUND_GAIN_9DB,		//value 0x04
	TDA7468_SURROUND_GAIN_12DB		//value 0x06
} TDA7468_SURROUND_GAIN;
#define TDA7468_SURROUND_GAIN_STRINGS      (const char*[4]){"0DB", "6DB", "9DB", "12DB"}

typedef enum {
	TDA7468_SURROUND_MIX_INVERT_100,	//value 0x00
	TDA7468_SURROUND_MIX_INVERT_50,		//value 0x08
	TDA7468_SURROUND_MIX_INVERT_25,		//value 0x10
	TDA7468_SURROUND_MIX_ZERO, 		//value 0x18
	TDA7468_SURROUND_MIX_NONINVERT_25,	//value 0x20
	TDA7468_SURROUND_MIX_NONINVERT_50,	//value 0x28
	TDA7468_SURROUND_MIX_NONINVERT_100,	//value 0x30
	TDA7468_SURROUND_MIX_MUTE		//value 0x38
} TDA7468_SURROUND_MIX;
#define TDA7468_SURROUND_MIX_STRINGS      (const char*[8]){"INVERT 100", "INVERT 50", "INVERT 25", "0", "NONINVERT 25", "NONINVERT 50", "NONINVERT 100", "MUTE"}

typedef enum {
	TDA7468_SURROUND_BUFFER_GAIN_6DB,	//value 0x00
	TDA7468_SURROUND_BUFFER_GAIN_0DB	//value 0x40
} TDA7468_SURROUND_BUFFER_GAIN;
#define TDA7468_SURROUND_BUFFER_GAIN_STRINGS      (const char*[2]){"6DB", "0DB"}

//VOLUME VARIABLES
//const uint8_t TDA7468_VOLUME_SHIFTS[3] = {0, 3, 6};
//const uint8_t TDA7468_VOLUME_MASK[3] = {0x07, 0x38, 0xC0};
#define TDA7468_VOLUME_SHIFTS			(const uint8_t*[3]){0, 3, 6}
#define TDA7468_VOLUME_MASK			(const uint8_t*[3]){0x07, 0x38, 0xC0}
#define TDA7468_VOLUME_REGISTER_STRINGS      (const char*[3]){"VOLUME1 1DB", "VOLUME1 8DB", "VOLUME2 8DB"}

#define TDA7468_VOLUME1_1DB_STEPS_0DB			0x00
#define TDA7468_VOLUME1_1DB_STEPS_1DB			0x01
#define TDA7468_VOLUME1_1DB_STEPS_2DB			0x02
#define TDA7468_VOLUME1_1DB_STEPS_3DB			0x03
#define TDA7468_VOLUME1_1DB_STEPS_4DB			0x04
#define TDA7468_VOLUME1_1DB_STEPS_5DB			0x05
#define TDA7468_VOLUME1_1DB_STEPS_6DB			0x06
#define TDA7468_VOLUME1_1DB_STEPS_7DB			0x07
#define TDA7468_VOLUME1_8DB_STEPS_0DB			0x00
#define TDA7468_VOLUME1_8DB_STEPS_8DB			0x08
#define TDA7468_VOLUME1_8DB_STEPS_16DB			0x10
#define TDA7468_VOLUME1_8DB_STEPS_24DB			0x18
#define TDA7468_VOLUME1_8DB_STEPS_32DB			0x20
#define TDA7468_VOLUME1_8DB_STEPS_40DB			0x28
#define TDA7468_VOLUME1_8DB_STEPS_48DB			0x30
#define TDA7468_VOLUME1_8DB_STEPS_56DB			0x38
#define TDA7468_VOLUME2_8DB_STEPS_0DB			0x00
#define TDA7468_VOLUME2_8DB_STEPS_8DB			0x40
#define TDA7468_VOLUME2_8DB_STEPS_16DB			0x80
#define TDA7468_VOLUME2_8DB_STEPS_24DB			0xC0

//TREBLE AND BASS VARIABLES
//const uint8_t TDA7468_TREBLE_BASS_SHIFTS[2] = {0, 4};
//const uint8_t TDA7468_TREBLE_BASS_MASK[2] = {0x0F, 0xF0};
#define TDA7468_TREBLE_BASS_SHIFTS		(const uint8_t*[2]){0, 4}
#define TDA7468_TREBLE_BASS_MASK		(const uint8_t*[2]){0x0F, 0xF0}
#define TDA7468_TREBLE_BASS_REGISTER_STRINGS      (const char*[2]){"TREBLE", "BASS"}

#define TDA7468_TREBLE_NEG_14DB				0x00
#define TDA7468_TREBLE_NEG_12DB				0x01
#define TDA7468_TREBLE_NEG_10DB				0x02
#define TDA7468_TREBLE_NEG_8DB				0x03
#define TDA7468_TREBLE_NEG_6DB				0x04
#define TDA7468_TREBLE_NEG_4DB				0x05
#define TDA7468_TREBLE_NEG_2DB				0x06
#define TDA7468_TREBLE_0DB				0x07
#define TDA7468_TREBLE_14DB				0x08
#define TDA7468_TREBLE_12DB				0x09
#define TDA7468_TREBLE_10DB				0x0A
#define TDA7468_TREBLE_8DB				0x0B
#define TDA7468_TREBLE_6DB				0x0C
#define TDA7468_TREBLE_4DB				0x0D
#define TDA7468_TREBLE_2DB				0x0E
#define TDA7468_TREBLE_0DB2				0x0F
#define TDA7468_BASS_NEG_14DB				0x00
#define TDA7468_BASS_NEG_12DB				0x10
#define TDA7468_BASS_NEG_10DB				0x20
#define TDA7468_BASS_NEG_8DB				0x30
#define TDA7468_BASS_NEG_6DB				0x40
#define TDA7468_BASS_NEG_4DB				0x50
#define TDA7468_BASS_NEG_2DB				0x60
#define TDA7468_BASS_0DB				0x70
#define TDA7468_BASS_14DB				0x80
#define TDA7468_BASS_12DB				0x90
#define TDA7468_BASS_10DB				0xA0
#define TDA7468_BASS_8DB				0xB0
#define TDA7468_BASS_6DB				0xC0
#define TDA7468_BASS_4DB				0xD0
#define TDA7468_BASS_2DB				0xE0
#define TDA7468_BASS_0DB2				0xF0

// OUTPUT VARIABLES
#define TDA7468_OUTPUT_MUTE_ON 				0x00
#define TDA7468_OUTPUT_MUTE_OFF				0x01

//BASS ALC VARIABLES
//const uint8_t TDA7468_INPUT_SELECT_MIC_SHIFTS[4] = {0, 2, 3, 5};
//const uint8_t TDA7468_INPUT_SELECT_MIC_MASK[4] = {0x03, 0x04, 0x18, 0x20};
//const uint8_t TDA7468_SURROUND_MODE_REGISTER_SHIFTS[4] = {0, 1, 3, 6};
//const uint8_t TDA7468_SURROUND_MODE_REGISTER_MASK[4] = {0x01, 0x06, 0x38, 0x40};
//const uint8_t TDA7468_BASS_ALC_REGISTER_SHIFTS[6] = {0, 1, 2, 3, 5, 7};
//const uint8_t TDA7468_BASS_ALC_REGISTER_MASK[6] = {0x01, 0x02, 0x04, 0x18, 0x60, 0x80};
//#define TDA7468_BASS_ALC_REGISTER_SHIFTS	(const uint8_t*[6]){0, 1, 2, 3, 5, 7}
//#define TDA7468_BASS_ALC_REGISTER_MASK		(const uint8_t*[6]){0x01, 0x02, 0x04, 0x18, 0x60, 0x80}
#define TDA7468_BASS_ALC_REGISTER_STRINGS      (const char*[6]){"BASS ALC", "BASS ALC DETECTOR", "RELEASE CURRENT CIRCUIT", "ATTACK TIME RESISTOR", "BASS ALC THRESHOLD", "ALC ATTACK MODE"}

typedef enum {
	TDA7468_BASS_ALC_OFF,			//value 0x00
	TDA7468_BASS_ALC_ON			//value 0x01
} TDA7468_BASS_ALC;
#define TDA7468_BASS_ALC_STRINGS      (const char*[2]){"OFF", "ON"}

typedef enum {
	TDA7468_BASS_ALC_DETECTOR_OFF,			//value 0x00
	TDA7468_BASS_ALC_DETECTOR_ON			//value 0x02
} TDA7468_BASS_ALC_DETECTOR;
#define TDA7468_BASS_ALC_DETECTOR_STRINGS      (const char*[2]){"OFF", "ON"}

typedef enum {
	TDA7468_RELEASE_CURRENT_CIRCUIT_OFF,			//value 0x00
	TDA7468_RELEASE_CURRENT_CIRCUIT_ON			//value 0x04
} TDA7468_RELEASE_CURRENT_CIRCUIT;
#define TDA7468_RELEASE_CURRENT_CIRCUIT_STRINGS      (const char*[2]){"OFF", "ON"}

typedef enum {
	TDA7468_ATTACK_TIME_RESISTOR_12P5K,			//value 0x00
	TDA7468_ATTACK_TIME_RESISTOR_25K,			//value 0x08
	TDA7468_ATTACK_TIME_RESISTOR_50K,			//value 0x10
	TDA7468_ATTACK_TIME_RESISTOR_100K			//value 0x18
} TDA7468_ATTACK_TIME_RESISTOR;
#define TDA7468_ATTACK_TIME_RESISTOR_STRINGS      (const char*[4]){"12.5k", "25k", "50k", "100k"}

typedef enum {
	TDA7468_BASS_ALC_THRESHOLD_700MV,			//value 0x00
	TDA7468_BASS_ALC_THRESHOLD_485MV,			//value 0x20
	TDA7468_BASS_ALC_THRESHOLD_320MV,			//value 0x40
	TDA7468_BASS_ALC_THRESHOLD_170MV			//value 0x60
} TDA7468_BASS_ALC_THRESHOLD;
#define TDA7468_BASS_ALC_THRESHOLD_STRINGS      (const char*[4]){"700mV", "485mV", "320mV", "170mV"}

typedef enum {
	TDA7468_ALC_ATTACK_MODE_FIXED_RES,		//value 0x00
	TDA7468_ALC_ATTACK_MODE_ADAPTIVE		//value 0x80
} TDA7468_ALC_ATTACK_MODE;
#define TDA7468_ALC_ATTACK_MODE_STRINGS      (const char*[2]){"FIXED RESISTOR", "ADAPTIVE"}

typedef struct {
	uint8_t InputSelect;
	uint8_t InputMute;
	uint8_t MicGain;
	uint8_t MicControl;
} InputSelectTypeDef;

typedef struct {
	uint8_t SurroundMode;
	uint8_t Gain;
	uint8_t Mixing;
	uint8_t BufferGain;
} SurroundTypeDef;

typedef struct {
	uint8_t onedbSteps;
	uint8_t eightdbSteps;
	uint8_t Volume2;
} VolumeTypeDef;

typedef struct {
	uint8_t Treble;
	uint8_t Bass;
} TrebleBassTypeDef;

typedef struct {
	uint8_t ALCMode;
	uint8_t Detector;
	uint8_t ReleaseCurrentCircuit;
	uint8_t AttackTimeResistor;
	uint8_t Threshold;
	uint8_t AttackMode;
} BassALCTypeDef;

typedef struct {
	InputSelectTypeDef InputSelect;
	uint8_t InputGain;
	SurroundTypeDef Surround;
	VolumeTypeDef VolumeLeft;
	VolumeTypeDef VolumeRight;
	TrebleBassTypeDef TrebleBass;
	uint8_t Output;
	BassALCTypeDef BassALC;
} TDA7468TypeDef;

//uint8_t initTxBuffer[] = {0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x01, 0x00};

int tda7468_i2c_write_all(I2CDriver*,TDA7468TypeDef*);
int tda7468_i2c_write_single(I2CDriver*,uint8_t,uint8_t);
int tda7468_init(I2CDriver*,TDA7468TypeDef*);
int tda7468_set_input_select_register(I2CDriver*,InputSelectTypeDef*);
int tda7468_set_input_gain_register(I2CDriver*,uint8_t*);
int tda7468_set_surround_register(I2CDriver*,SurroundTypeDef*);
int tda7468_set_volume_left_register(I2CDriver*,VolumeTypeDef*);
int tda7468_set_volume_right_register(I2CDriver*,VolumeTypeDef*);
int tda7468_set_treble_bass_register(I2CDriver*,TrebleBassTypeDef*);
int tda7468_set_output_register(I2CDriver*,uint8_t*);
int tda7468_set_bass_alc_register(I2CDriver*,BassALCTypeDef*);
int tda7468_set_registers(I2CDriver*,TDA7468TypeDef*);
