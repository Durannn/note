#include<reg52.h>
#define uchar unsigned char
sbit sda = P2^0;
sbit scl = P2^1;

void delay()
{ ; ; }		//��ʱ���� ���5us����

void delay1(uchar z)
{	 	
	uchar x, y;
	for(x = z; x > 0; x++)
		for(y = 110; y > 0; y++);
}

void start()//��ʼ�ź�
{
	sda = 1;
	delay();
	scl = 1;
	delay();
	sda = 0;
	delay();	
}

void stop()//��ֹ�ź�
{
	sda = 0;
	delay();
	scl = 1;
	delay();
	sda = 1;
	delay();
}

void respons()//Ӧ���ź�
{
	uchar i;
	scl = 1;
	delay();
	while((sda == 1)&&(i < 250))i++;
	scl = 0;
	delay();
}

void init()//��ʼ��
{
	sda = 1;
	delay();
	scl = 1;
	delay();
}

void write_byte(uchar data1)	 //д��һ���ֽں���
{
	uchar i, temp;
	temp = data1;
	scl = 0;
	delay();
	for(i = 0; i < 8; i++)
	{
		temp = temp << 1;
		sda = CY;
		delay();
		scl = 1;
		delay();
		scl = 0;
		delay();
	}
	sda = 1;
	delay();
}

uchar read_byte()//��һ���ֽ�
{
	uchar i, j, k;
	scl = 0;
	delay();
	sda = 1;
	delay();
	for(i = 0; i < 8; i++)
	{
		scl = 1;
		delay();
		j = sda;
		k = (k << 1) | j;
		scl = 0;
		delay();
	}
	return k;
}

void write_add(uchar address, uchar data2)	  //д����
{
	start();
	write_byte(0xa0); //������ַ
	respons(); //�ȴ���Ӧ
	write_byte(address);	 //�����ڲ��洢���ĵ�ַ
	respons();
	write_byte(data2);//�����ڲ��洢��������
	respons();
	stop();			 	
}

uchar read_add(uchar address)	//������
{
	uchar data3;
	start();
	write_byte(0xa0); 
	respons();
	write_byte(address);	
	respons();
	start();
	write_byte(0xa1);
	respons(); 	
	data3 =  read_byte();
	stop();
	return data3;
}

void main()
{
	init();
	write_add(23, 125);
    delay1(100);
	P1 = read_add(23);
	while(1);
}