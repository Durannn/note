#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit dula = P2^6;
sbit wela = P2^7;
sbit rs = P3^5;
sbit lcden = P3^4;
sbit s1 = P3^0;
sbit s2 = P3^1;
sbit s3 = P3^2;
sbit rd = P3^7;
uchar count, s1num;
char shi, fen, miao;
uchar code table[] = "  2017-8-16 WED";
uchar code table1[] = "    00:00:00";

void delay(uint z)
{
	uint x, y;
	for(x = z; x > 0; x--)
		for(y = 110; y > 0; y--);
}

void write_com(uchar com)//写指令函数
{
	rs = 0;
	lcden = 0;
	P0 = com;
	delay(5);
	lcden = 1;
	delay(5);
	lcden = 0;
}

void write_data1(uchar data1)//写数据函数
{
	rs = 1;
	lcden = 0;
	P0 = data1;
	delay(5);
	lcden = 1;
	delay(5);
	lcden = 0;
}

void init()//初始化函数
{
	uchar num;
	dula = 0;
	wela = 0;
	lcden = 0;
	write_com(0x38);
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
	write_com(0x80);
	for(num = 0; num <15; num++)
	{
		write_data1(table[num]);
		delay(5);
	}
	write_com(0x80 + 0x40);
	for(num = 0; num <12; num++)
	{
		write_data1(table1[num]);
		delay(5);
	}
	TMOD = 0x01;
	TH0 = (65536 - 50000) / 256;
	TL0 = (65536 - 50000) % 256;
	EA = 1;
	ET0 = 1;
	TR0 = 1;	

}

void write_sfm(uchar add, uchar data2)
{
	uchar shi, ge;
	shi = data2 / 10;
	ge = data2 % 10;
	write_com(0x80 + 0x40 + add);
	write_data1(0x30 + shi);
	write_data1(0x30 + ge);
}

void keyscan()
{
	rd = 0;
	if(s1 == 0)
	{
		delay(5);
		if(s1 == 0)
		{
			s1num++;
			while(!s1);
			if(s1num == 1)
			{
				TR0 = 0;
				write_com(0x80 + 0x40 + 10);
				write_com(0xf0);
			}	
		}
		if(s1num == 2)
			{
				write_com(0x80 + 0x40 + 7);
			}
			if(s1num == 3)
			{
				write_com(0x80 + 0x40 + 4);
			}
			if(s1num == 4)
			{
				s1num = 0;
				write_com(0x0c);
				TR0 = 1;
		}

	}
		if(s1num != 0)
		{
			if(s2 == 0)
			{
				delay(5);
				if(s2 == 0)
				{
					while(!s2);
					if(s1num == 1)
					{
					 	miao++;
						if(miao == 60)
							miao = 0;
						write_sfm(10, miao);
						write_com(0x80 + 0x40 + 10);
					}
					if(s1num == 2)
					{
						fen++;
						if(fen == 60)
							fen = 0;
						write_sfm(7, fen);
						write_com(0x80 + 0x40 + 7);
					}
					if(s1num == 3)
					{
						shi++;
						if(shi == 24)
							shi = 0;
						write_sfm(4, shi);
						write_com(0x80 + 0x40 + 4);
					}
				}	
			}
			if(s3 == 0)
			{
				delay(5);
				if(s3 == 0)
				{
					while(!s3);
					if(s1num ==1)
					{
						miao--;
						if(miao == -1)
							miao = 59;
						write_sfm(10, miao);
						write_com(0x80 + 0x40 + 10);	
					}
                    if(s1num ==2)
					{
						fen--;
						if(fen == -1)
							fen = 59;
						write_sfm(7, fen);
						write_com(0x80 + 0x40 + 7);	
					}
					if(s1num ==3)
					{
						shi--;
						if(shi == -1)
							shi = 23;
						write_sfm(4, shi);
						write_com(0x80 + 0x40 + 4);		
					}
				}
			}
		}		
}

void main()
{
	init();
	while(1)
	{
		keyscan();
		
	}
}

void timer0() interrupt 1
{
	TH0 = (65536 - 50000) / 256;
	TL0 = (65536 - 50000) % 256;
	count++;
	if(count == 18)
		{
			count = 0;
			miao++;
			if(miao == 60)
			{
				miao = 0;
				fen++;
				if(fen == 60)
				{
					fen = 0;
					shi++;
					if(shi == 24)
					{
						shi = 0;
						
					}
					write_sfm(4, shi);
				}
				write_sfm(7, fen);
			}
			write_sfm(10, miao);
		}
}