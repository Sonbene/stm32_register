#include "MPU6050.h"

#define SMPLRT_DIV_REG 		0x19
#define GYRO_CONFIG_REG		0x1B
#define ACCEL_CONFIG_REG	0x1C
#define	ACCEL_XOUT_H_REG 	0x3B
#define TEMP_OUT_H_REG		0x41
#define GYRO_XOUT_H_REG		0x43
#define PWR_MGMT_1_REG		0x6B
#define WHO_AM_I_REG		0x75

#define MPU6050_ADDRESS		0x68

uint8_t  MPU6050_Init()
{
	uint8_t check = 0;
	uint8_t Data = 0;
	uint8_t reg = WHO_AM_I_REG;

	//Check device ID WHO_AM_I

  //HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDRESS, WHO_AM_I_REG, 1, &check, 1, 100);
	SON_I2C_Master_Transmit(MPU6050_ADDRESS, &reg, 1);
	SON_I2C_Master_Receive(MPU6050_ADDRESS, &check, 1);
	if(check == 0x68)//0x68 will be returned by the sensor
	{
		// power management register 0X6B we should write all 0's to wake the sensor up
		Data = 0;
		reg = PWR_MGMT_1_REG;
		//HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDRESS, PWR_MGMT_1_REG, 1, &Data, 1, 100);
		SON_I2C_Master_Transmit(MPU6050_ADDRESS, &reg, 1);
		SON_I2C_Master_Transmit(MPU6050_ADDRESS, &Data, 1);

		// Set DATA RATE of 1KHz by writing SMPLRT_DIV register
		Data = 0x07;
		reg = SMPLRT_DIV_REG;
		//HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDRESS, SMPLRT_DIV_REG, 1, &Data, 1, 100);
		SON_I2C_Master_Transmit(MPU6050_ADDRESS, &reg, 1);
		SON_I2C_Master_Transmit(MPU6050_ADDRESS, &Data, 1);

		// Set accelerometer configuration in ACCEL_CONFIG Register
		// XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> ? 2g
		Data = 0x00;
		reg = ACCEL_CONFIG_REG;
		//HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDRESS, ACCEL_CONFIG_REG, 1, &Data, 1, 100);
		SON_I2C_Master_Transmit(MPU6050_ADDRESS, &reg, 1);
		SON_I2C_Master_Transmit(MPU6050_ADDRESS, &Data, 1);

		// Set Gyroscopic configuration in GYRO_CONFIG Register
		// XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> ? 250 ?/s
		Data = 0x00;
		reg = GYRO_CONFIG_REG;
		//HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDRESS, GYRO_CONFIG_REG, 1, &Data, 1, 100);
		SON_I2C_Master_Transmit(MPU6050_ADDRESS, &reg, 1);
		SON_I2C_Master_Transmit(MPU6050_ADDRESS, &Data, 1);
		return 0;
	}
	return 1;
}

void MPU6050_Read_Accel(MPU6050_t *dataStruct)
{
	uint8_t data_rec[6];
	uint8_t reg = ACCEL_XOUT_H_REG;
	//HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDRESS, ACCEL_XOUT_H_REG, 1, data_rec, 6, 100);
	SON_I2C_Master_Transmit(MPU6050_ADDRESS, &reg, 1);
	SON_I2C_Master_Receive(MPU6050_ADDRESS, data_rec, 6);

	dataStruct->Accel_XOUT = (int16_t)(data_rec[0] << 8 | data_rec[1]);
	dataStruct->Accel_YOUT = (int16_t)(data_rec[2] << 8 | data_rec[3]);
	dataStruct->Accel_ZOUT = (int16_t)(data_rec[4] << 8 | data_rec[5]);

	 /*** convert the RAW values into acceleration in 'g'
         we have to divide according to the Full scale value set in FS_SEL
         I have configured FS_SEL = 0. So I am dividing by 16384.0
         for more details check ACCEL_CONFIG Register              ****/
	dataStruct->Ax = dataStruct->Accel_XOUT / 16384.0;
	dataStruct->Ay = dataStruct->Accel_YOUT / 16384.0;
	dataStruct->Ax = dataStruct->Accel_ZOUT / 16384.0;
}


void MPU6050_Read_Gyro(MPU6050_t *dataStruct)
{
	uint8_t data_rec[6];
	uint8_t reg = GYRO_XOUT_H_REG;
	//HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDRESS, GYRO_XOUT_H_REG, 1, data_rec, 6, 100);
	SON_I2C_Master_Transmit(MPU6050_ADDRESS, &reg, 1);
	SON_I2C_Master_Receive(MPU6050_ADDRESS, data_rec, 6);
	dataStruct->Gyro_XOUT = (int16_t)(data_rec[0] << 8 | data_rec[1]);
	dataStruct->Gyro_YOUT = (int16_t)(data_rec[2] << 8 | data_rec[3]);
	dataStruct->Gyro_ZOUT = (int16_t)(data_rec[4] << 8 | data_rec[5]);

	/*** convert the RAW values into dps (?/s)
         we have to divide according to the Full scale value set in FS_SEL
         I have configured FS_SEL = 0. So I am dividing by 131.0
         for more details check GYRO_CONFIG Register    ***/

	dataStruct->Gx = dataStruct->Gyro_XOUT / 131.0;
	dataStruct->Gy = dataStruct->Gyro_YOUT / 131.0;
	dataStruct->Gz = dataStruct->Gyro_ZOUT / 131.0;
}

void MPU6050_Read_Temp(MPU6050_t* dataStruct)
{
	uint8_t data_rec[2];
	int16_t temp;

	//HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDRESS, TEMP_OUT_H_REG, 1, data_rec, 2, 100);
	uint8_t reg = TEMP_OUT_H_REG;
	SON_I2C_Master_Transmit(MPU6050_ADDRESS, &reg, 1);
	SON_I2C_Master_Receive(MPU6050_ADDRESS, data_rec, 2);

	temp = (int16_t)(data_rec[0] << 8 | data_rec[1]);

	dataStruct->temp = (float)(temp/340.0 + 36.53);
}

void MPU6050_Read_All(MPU6050_t* dataStruct)
{
	uint8_t data_rec[14];
	int16_t temp;
	//HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDRESS, ACCEL_XOUT_H_REG, 1, data_rec, 16, 100);
	uint8_t reg = ACCEL_XOUT_H_REG;
	SON_I2C_Master_Transmit(MPU6050_ADDRESS, &reg, 1);
	SON_I2C_Master_Receive(MPU6050_ADDRESS, data_rec, 14);

	dataStruct->Accel_XOUT = (int16_t)(data_rec[0] << 8 | data_rec[1]);
	dataStruct->Accel_YOUT = (int16_t)(data_rec[2] << 8 | data_rec[3]);
	dataStruct->Accel_ZOUT = (int16_t)(data_rec[4] << 8 | data_rec[5]);

	temp = (int16_t)(data_rec[6] << 8 | data_rec[7]);

	dataStruct->Gyro_XOUT = (int16_t)(data_rec[8] << 8 | data_rec[9]);
	dataStruct->Gyro_YOUT = (int16_t)(data_rec[10] << 8 | data_rec[11]);
	dataStruct->Gyro_ZOUT = (int16_t)(data_rec[12] << 8 | data_rec[13]);

	dataStruct->Ax = dataStruct->Accel_XOUT / 16384.0;
	dataStruct->Ay = dataStruct->Accel_YOUT / 16384.0;
	dataStruct->Az = dataStruct->Accel_ZOUT / 16384.0;

	dataStruct->temp = (float)(temp/340.0 + 36.53);

	dataStruct->Gx = dataStruct->Gyro_XOUT / 131.0;
	dataStruct->Gy = dataStruct->Gyro_YOUT / 131.0;
	dataStruct->Gz = dataStruct->Gyro_ZOUT / 131.0;
}















