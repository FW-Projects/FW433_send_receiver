#ifndef	__PID_OPERATION_H__
#define __PID_OPERATION_H__


#define uchar unsigned char
#define uint unsigned int
extern int   ek,ek_1,ek_sum;
extern int   Kp,Kd;
extern float Ki;
void PID_format();
PID_operation(int Set_data,Cur_data);//PID?????

#endif