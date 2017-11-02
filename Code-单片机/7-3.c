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
	write_com(0x01);//���� 
	write_com(0x80 + 0x10);//����ָ���ʼ��
	write_com(0x38);//д����
	write_com(0x0f); //д����
	write_com(0x06); //д����

}

void main()
{
	init();
	for(num = 0;num < 11;num++)
	{
		write_data(table[num]);
		delay(20);
	}
	write_com(0x80 + 0x53);//�༭����������ʾ����ʼλ�� 0x80Ϊ�ӵ�һ�п�ʼ��0x80+0x40Ϊ�ӵڶ��п�ʼ 
	                       //0x80+0x40+0x03��Ϊ�ӵڶ��е���λ��ʼ��ʾ
	for(num = 0;num < 5;num++)
	{
		write_data(table1[num]);
		delay(20);
	} 
	for(num = 0; num < 16; num++)
	{
		write_com(0x18);//��������
		delay(200);	
	} 
	while(1);
}