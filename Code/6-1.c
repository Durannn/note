//��ѯ��
#include<reg52.h>
void main()
{
	TMOD = 0x20;//��ʱ��1Ϊ������ʽ2
	TH1 = 0xfd;
	TL1 = 0xfd;
	TR1 = 0;
	REN = 1;
	SM0 = 0;
	SM1 = 1;
	while(1)
	{
		if(RI == 1);	 //����Ƿ��յ�����
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