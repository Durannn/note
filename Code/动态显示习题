/*利用动态扫描和定时器1在数码管上显示出从7654321开始以1/10秒的速度往下递减直至765398并保持显示此数，与此同时利用定时器0以500MS速度进行
流水灯从上至下移动，当数码管上数减到停止时，实验板上流水灯也停止然后开始闪烁，3秒后（用T0定时）流水灯全部关闭、数码管上显示出“HELLO”。到此保持住
*/
#include<reg52.h>
#include<intrins.h>
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
uchar temp, t0, t1, bai, shi, ge, flag, flag1;
uint shu;
void init();
void delay(uint z);
void display(uchar shiwan, uchar wan, uchar qian, uchar bai, uchar shi, uchar ge);
void main()
{
	init();
	while(1)
	{
		if(flag1 != 1)
			display(7, 6, 5, bai, shi, ge);
		else
			display(16, 17, 18, 18, 19, 20);
	}
}
void init()//初始化函数
{
	shu = 432;
	t0 = 0;
	t1 = 0;
	temp = 0xfe;
	P1 = temp;
	TMOD = 0x11;
	TH0 = (65536 - 50000) / 256;
	TL0 = (65536 - 50000) % 256;
	TH1 = (65536 - 50000) / 256;
	TL1 = (65536 - 50000) % 256;
	EA = 1;	//开总中断
	ET0 = 1;//开定时器中断
	ET1 = 1;
	TR0 = 1;//启动定时器
	TR1 = 1;
}
void timer0() interrupt 1
{
	TH0 = (65536 - 50000) / 256;
	TL0 = (65536 - 50000) % 256;
	t0++;
	if(flag != 1)
	{
		if(t0 == 10)
		{
			t0 = 1;
			temp = _crol_(temp, 1);
			P1 = temp;
		}
	}
	else
	{
		if(t0 % 4 == 0)
			P1 = ~P1;
		if(t0 == 60)
		{
			TR0 = 0;
			P1 = 0xff;
			flag1 = 1;
		}
			
	}		
}
void timer1() interrupt 3
{
	TH1 = (65536 - 50000) / 256;
	TL1 = (65536 - 50000) % 256;
	t1++;
	if(t1 == 2)
	{
		t1 = 0;
		shu--;
		bai = shu / 100;
		shi = shu % 100 /10;
		ge = shu / 10;
		if(shu == 398)
		{
			TR0 = 0;
			TH0 = (65536 - 50000) / 256;
			TL0 = (65536 - 50000) % 256;
			flag = 1;
			t0 = 0;
			TR0 = 1;
			P1 = 0xff;
			TR1 = 0;
		}	
	}
		
}
void display(uchar shiwan, uchar wan, uchar qian, uchar bai, uchar shi, uchar ge)
 {		
 	    dula = 1;
	    P0 = table[shiwan];
		dula = 0; 
		P0 = 0xff;
		wela = 1;
		P0 = 0xfe;
		wela = 0;
		delay(5);
		dula = 1;
	    P0 = table[wan];
		dula = 0;
		P0 = 0xff;
		wela = 1;
		P0 = 0xfd;
		wela = 0;
		delay(5);
		dula = 1;
	    P0 = table[qian];
		dula = 0;
		P0 = 0xff;
		wela = 1;
		P0 = 0xfb;
		wela = 0;
		delay(5);
 	    dula = 1;
	    P0 = table[bai];
		dula = 0; 
		P0 = 0xff;
		wela = 1;
		P0 = 0xf7;
		wela = 0;
		delay(5);
		dula = 1;
	    P0 = table[shi];
		dula = 0;
		P0 = 0xff;
		wela = 1;
		P0 = 0xef;
		wela = 0;
		delay(5);
		dula = 1;
	    P0 = table[ge];
		dula = 0;
		P0 = 0xff;
		wela = 1;
		P0 = 0xdf;
		wela = 0;
		delay(5);	
 }
void delay(uint z)
{
 	uint x,y;
	for(x = z; x > 0; x--);
		for(y = 110; y > 0; y--);
}
