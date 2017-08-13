 //第一个数码管亮1，1s后第二个数码管亮2；依次继续	（动态显示）
 #include<reg52.h>
 #include<intrins.h>
 #define uint unsigned int
 #define uchar unsigned char
 sbit dula = P2^6;
 sbit wela = P2^7;
 uchar code table[] = {
 0x3f, 0x06, 0x5b, 0x4f,
 0x66, 0x6d, 0x7d, 0x07,
 0x7f, 0x6f, 0x77, 0x7c,
 0x39, 0x5e, 0x79, 0x71};
 uchar temp;
 uchar aa;
 uchar num;
 void main()
 {
 	num = 0;
	aa = 0;
 	TMOD = 0x01;
	TH0 = (65536 - 50000) / 256;
	TL0 = (65536 - 50000) % 256;
	EA = 1;//开总中断
	ET0 = 1;//开定时器0中断
	TR0 = 1;
 	temp = 0xfe;
	P1 = temp;
	dula = 1;
	P0 = table[0];
	dula = 0;
	wela = 1;
	P0 = 0xfe;
	wela = 0;
 	while(1)
	{

		if(aa == 20)
		{
			aa = 0;	
			dula = 1;
			P0 = table[num];
			dula = 0;
			num++;
			if(num == 6)
				num =0;
			wela = 1;
			P0 = _crol_(P0,1);
			wela = 0;
			if(P0 == 0xc0)
				P0 = 0xfe;

				
		}
	}
 }

 void timer0() interrupt 1
 {
 	TH0 = (65536 - 50000) / 256;
	TL0 = (65536 - 50000) % 256;
	aa++;
		
				
			
 }
