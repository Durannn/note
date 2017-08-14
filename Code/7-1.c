#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
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

void write_com(uchar com)//д�����Ӻ���
{
	lcdrs = 0;
	P0 = com;
	delay(5);
	lcden = 1;
	delay(5);
	lcden = 0;
}

void write_data(uchar data1)//д�����Ӻ���
{
	lcdrs = 1;
	P0 = data1;
	delay(5);
	lcden = 1;
	delay(5);
	lcden = 0;
}

void init()	//��ʼ������
{
	dula = 0;
	wela = 0;//����ܹ�
	lcden = 0;
	write_com(0x80);//����ָ���ʼ��
	write_com(0x10);//����
	write_com(0x38);//д����
	write_com(0x0f); //д����
	write_com(0x06); //д����

}

void main()
{
	init();
	write_data('1');//write_data(0x31);
	delay(20);
	write_data('B');
	while(1);
}