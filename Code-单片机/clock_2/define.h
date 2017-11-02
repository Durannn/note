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
sbit dscs = P1^4;
sbit dsas = P1^5;
sbit dsrw = P1^6;
sbit dsds = P1^7;
sbit dsirp = P3^3;
sbit beep = P2^3;
uchar count, s1num, flag, flag1;
char shi, fen, miao;
uchar code table[] = "  2017-8-16 WED";
uchar code table1[] = "      :  :  ";
void set_time();
void write_ds(uchar, uchar);
void set_alarm(uchar, uchar, uchar);
uchar read_ds(uchar);