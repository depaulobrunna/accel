#include "mpu60x.h"
#include "mpu60x_registers.h"
#include "string.h"

#define REGISTERS_NUM        118

static void SystemClock_Config(void);
//static void Error_Handler(void);

static void i2c_init(void);

static I2C_HandleTypeDef I2cHandle;
//static MPU60x_States mpu_state;
//static MPU60x_Available mpu_available;

uint16_t test;
float test_2;
//static uint8_t aTxBuffer;
static uint8_t aRxBuffer[REGISTERS_NUM];
static uint8_t all[REGISTERS_NUM];

static uint16_t range = MPU60x_ACC_RANGE_ENCODE(MPU60x_RANGE_2_G);
//static uint8_t sample_rate_div = 0xFF;
//static uint8_t dlpf = 0x01;

int main(void)
{
	i2c_init();
	mpu60x_set_i2c(&I2cHandle);

	memset(&aRxBuffer[0], 0xFF, REGISTERS_NUM);
	memset(&all[0], 0xFF, REGISTERS_NUM);

	mpu60x_available();
	mpu60x_wake();

	mpu60x_set_accel_cfg(MPU60x_RANGE_2_G);

//	mpu60x_temperature_sensor_enable();
//	mpu60x_set_sample_rate( sample_rate_div, dlpf);

	while (1)
	{
	#if 0
		test = mpu60x_get_sensor( MPU60x_TEMPERATURE_SENSOR, MPU60x_NO_AXIS);
		PRINTS("temperature: %d\t", test);
		test_2 = MPU60x_BYTE_TO_FARHENHEIT(test);
		PRINTS("%4.2f\t", test_2);
		test_2 = MPU60x_FARHENHEIT_TO_CELSIUS(test_2);
		PRINTS("%4.2f.\n", test_2);
		HAL_Delay(1000);
	#else
		test = mpu60x_get_sensor(MPU60x_ACCELEROMETER, MPU60x_Z_AXIS);
		PRINTS("accelaration: %d\t", test);
		test_2 = MPU60x_BYTE_TO_G(range, test);
		PRINTS("%4.2f\t", test_2);
		test_2 = MPU60x_G_TO_SI(test_2);
		PRINTS("%4.2f.\n", test_2);
		HAL_Delay(1000);
	#endif
	}
}


static void i2c_init(void)
{
	HAL_StatusTypeDef status;

	I2cHandle.Instance             = I2C1;
	I2cHandle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
	I2cHandle.Init.ClockSpeed      = 400000;
	I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	I2cHandle.Init.DutyCycle       = I2C_DUTYCYCLE_16_9;
 	I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  	I2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;
  	I2cHandle.Init.OwnAddress1     = 0;
  	I2cHandle.Init.OwnAddress2     = 0;

	status = HAL_I2C_Init(&I2cHandle);
	return;
}
