//DS12C887
#include<reg52.h>
#include<define.h>

void delay(uint z)
{
	uint x, y;
	for(x = z; x > 0; x--)
		for(y = 110; y > 0; y--);
}

void didi()
{
	beep = 0;
	delay(50);
	beep = 1;
	delay(50);
	beep = 0;
	delay(50);
	beep = 1;
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
	EA = 1;
	EX0 = 1;
	IT0 = 1;//不跳变沿触发方式
	dula = 0;
	wela = 0;
	lcden = 0;
//	set_time();
	set_alarm(13, 52, 0);
	write_ds(0x0b, 0x26);
	read_ds(0x0c);
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
	if(flag1 == 1)
	{
		if(s2 == 0)
		{
			delay(5);
			if(s2 == 0)
			{
				while(!s2)
				flag1= 0;
			}
		}
			if(s3 == 0)
		{
			delay(5);
			if(s3 == 0)
			{
				while(!s3)
				flag1= 0;
			}
		}
	}
	if(s1 == 0)
	{
		delay(5);
		if(s1 == 0)
		{
			s1num++;
			flag = 1;
			flag1 = 0;
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
				flag = 0;
				write_ds(0, miao);
				write_ds(2, fen);
				write_ds(4, shi);
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

void write_ds(uchar add, uchar data1)
{
	dscs = 0;
	dsas = 1;
	dsds = 1;
	dsrw = 1;
	P0 = add;
	dsas = 0;
	dsrw = 0;
	P0 = data1;
	dsrw = 1;
	dsas = 1;
	dscs = 1;

}

uchar read_ds(uchar add)
{
	uchar ds_data1;
	dsas = 1;
	dsds = 1;
	dsrw = 1;
	dscs = 0;
	P0 = add;
	dsas = 0;
	dsds = 0;
	P0 = 0xff;
	ds_data1 = P0;
	dsds = 1;
	dsas = 1;
	dscs = 1;
	return ds_data1;
}

void set_time()
{
	write_ds(4, 10);
	write_ds(2, 32);
}

void set_alarm(uchar ashi, uchar afen, uchar amiao)
{
	write_ds(1, amiao);
	write_ds(3, afen);
	write_ds(5, ashi);
}

void main()
{
	init();
	while(1)
	{
		keyscan();
		if(flag1 == 1)
			didi();
		if(flag == 0)
		{
			miao = read_ds(0);
			fen = read_ds(2);
			shi = read_ds(4);
			write_sfm(10,miao);	
			write_sfm(7,fen);	
			write_sfm(4,shi);		
		}
	}
}

void exter() interrupt 0
{
	uchar c;
	beep = 0;
	flag1 = 1;
	c = read_ds(0x0c);
}