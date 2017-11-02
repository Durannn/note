//中断法
#include<reg52.h>
unsigned char flag, a;
void main()
{
	TMOD = 0x20;//定时器1为工作方式2
	TH1 = 0xfd;
	TL1 = 0xfd;
	TR1 = 0;
	REN = 1;
	SM0 = 0;
	SM1 = 1;
	EA = 1;
	ES = 1;
	while(1)
	{
		if(flag == 1)
		{
			ES = 0;
			flag = 0;
			SBUF = a;//接收缓存器的SBUF
			while(!TI)
			TI = 0;	 //返回值
			ES = 1;
		}	
	}
}
void ser() interrupt 4
{
	RI = 0;
	P1 = SBUF;//发送缓存器的SBUF
	a = SBUF;
	flag = 1;
}