#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar code table[] = {"I LIKE MCU!"};
uchar code table1[] = {"DURAN"};
uchar num;
sbit lcden = P3^4;
sbit lcdrs = P3^5;
sbit wela = P2^6;
sbit dula = P2^6;

void delay(uint z)
{
 	uint x,y;
	for(x = z; x > 0; x--);
		for(y = 110; y > 0; y--);
}

void write_com(uchar com)//写命令子函数
{
	lcdrs = 0;
	P0 = com;
	delay(5);
	lcden = 1;
	delay(5);
	lcden = 0;
}

void write_data(uchar data1)//写数据子函数
{
	lcdrs = 1;
	P0 = data1;
	delay(5);
	lcden = 1;
	delay(5);
	lcden = 0;
}

void init()	//初始化函数
{
	dula = 0;
	wela = 0;//数码管关
	lcden = 0;
	write_com(0x01);//清屏 
	write_com(0x80 + 0x10);//数据指针初始化
	write_com(0x38);//写命令
	write_com(0x0f); //写命令
	write_com(0x06); //写命令

}

void main()
{
	init();
	for(num = 0;num < 11;num++)
	{
		write_data(table[num]);
		delay(20);
	}
	write_com(0x80 + 0x53);//编辑以下内容显示的起始位置 0x80为从第一行开始，0x80+0x40为从第二行开始 
	                       //0x80+0x40+0x03即为从第二行第四位开始显示
	for(num = 0;num < 5;num++)
	{
		write_data(table1[num]);
		delay(20);
	} 
	for(num = 0; num < 16; num++)
	{
		write_com(0x18);//整屏左移
		delay(200);	
	} 
	while(1);
}