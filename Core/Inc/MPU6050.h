#ifndef MPU6050_H
#define MPU6050_H

#include "main.h"
#include "I2C.h"


typedef struct
{
	int16_t Accel_XOUT;
	int16_t Accel_YOUT;
	int16_t Accel_ZOUT;
	double Ax;
	double Ay;
	double Az;

	double temp;

	int16_t Gyro_XOUT;
	int16_t Gyro_YOUT;
	int16_t Gyro_ZOUT;
	double Gx;
	double Gy;
	double Gz;
}MPU6050_t;

uint8_t MPU6050_Init(void);
void MPU6050_Read_Accel(MPU6050_t *dataStruct);
void MPU6050_Read_Gyro(MPU6050_t *dataStruct);
void MPU6050_Read_Temp(MPU6050_t* dataStruct);
void MPU6050_Read_All(MPU6050_t* dataStruct);


#endif


