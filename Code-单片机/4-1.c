//按键
#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit dula = P2^6;
sbit wela = P2^7;
uchar code table[] = {
0x3f, 0x06, 0x5b, 0x4f,
0x66, 0x6d, 0x7d, 0x07,
0x7f, 0x6f, 0x77, 0x7c,
0x39, 0x5e, 0x79, 0x71,
0x36, 0x79, 0x38, 0x3f, 0};
uchar num;
sbit D1 = P1^0;
sbit K1 = P3^4;
void delay(uint z);
void main()
{
	num = 0;
	P3 = 0xff;
	wela = 1;
	P0 = 0xfe;
	wela = 0;
	while(1)
	{
		if(K1 == 0)
		{
			delay(10);	 //消抖	
			if(K1 == 0)
			{ 	 
				 D1 = 0;
				 num++;
				 if(num == 10)
					num = 0;
			}
			while(!K1);
			delay(10);	//消抖
			while(!K1);
		}
		else
			D1 = 1;	
		dula = 1;
		P0 = table[num];
		dula = 0;	
	}
}
void delay(uint z)
{
 	uint x,y;
	for(x = z; x > 0; x--);
		for(y = 110; y > 0; y--);
}
