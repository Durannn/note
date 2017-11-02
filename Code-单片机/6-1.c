//查询法
#include<reg52.h>
void main()
{
	TMOD = 0x20;//定时器1为工作方式2
	TH1 = 0xfd;
	TL1 = 0xfd;
	TR1 = 0;
	REN = 1;
	SM0 = 0;
	SM1 = 1;
	while(1)
	{
		if(RI == 1);	 //检测是否收到数据
		{
			RI = 0;
			P1 = SBUF;
		}
	}
}
void ser() interrupt 4
{
	RI = 0;
	P1 = SBUF;
}