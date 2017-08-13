#include<reg52.h>
sbit dula = P2^6;
sbit wela = P2^7;
sbit d1 = P1^0;
#define uint unsigned int
#define uchar unsigned char
void delay(uint z);
uchar num;
uchar code table[] = {
0x3f, 0x06, 0x5b, 0x4f,
0x66, 0x6d, 0x7d, 0x07,
0x7f, 0x6f, 0x77, 0x7c,
0x39, 0x5e, 0x79, 0x71};			 //code 放在程序存储器中，若不定义code ，则放在随机存储器中	
void main()
{
	EA = 1;	//开总中断
	EX0 = 1;//开外部中断0
	//TCON = 0X01;(等同于ITO = 1) 电平触发
	wela = 1;
	P0 = 0xea;//11101010
	wela = 0;
	while(1)
	{
		for(num = 0; num < 16; num++)
		{
			d1 = 1;
			dula = 1;
			P0 = table[num];
			dula = 0;
			delay(1000);	
		}
	}
}
void delay(uint z)
{
	uint x, y;
	for(x=z; x>0; x--);
		for(y=110; y>0; y--);
}
void exter0() interrupt 0
{
	d1 = 0;
}
