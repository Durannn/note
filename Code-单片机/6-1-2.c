//�жϷ�
#include<reg52.h>
unsigned char flag, a;
void main()
{
	TMOD = 0x20;//��ʱ��1Ϊ������ʽ2
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
			SBUF = a;//���ջ�������SBUF
			while(!TI)
			TI = 0;	 //����ֵ
			ES = 1;
		}	
	}
}
void ser() interrupt 4
{
	RI = 0;
	P1 = SBUF;//���ͻ�������SBUF
	a = SBUF;
	flag = 1;
}