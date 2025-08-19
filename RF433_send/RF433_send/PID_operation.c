#define uchar unsigned char
#define uint  unsigned int
int  ek=0,ek_1=0,ek_sum=0;
int  Kp=2,Kd=9;
float Ki=0.1;
void PID_format()
{
	ek=0;
	ek_1=0;
	ek_sum=0;
}
PID_operation(int Set_data,Cur_data)//PID?????
{
  	int Kp_coe=0, Ki_coe=0, Kd_coe=0,U_k=0;
		ek_1=ek;
		ek=(Set_data-Cur_data);//??????
	  ek_sum+=ek;
	  if(ek_sum>800) ek_sum=800;
	  else if(ek_sum<-800) ek_sum=-800;
		Kp_coe=Kp*ek;
		Ki_coe=Ki*ek_sum;
		Kd_coe=Kd*(ek-ek_1);
		U_k=Kp_coe+Ki_coe+Kd_coe;
		if(U_k<0) U_k=0;
		else if(U_k>100)U_k=100;
		return(U_k);
 }
	