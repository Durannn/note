  #include<reg52.h>
  #include<intrins.h>
  #define uint unsigned int
  #define uchar unsigned char
  void delay(uint z);
  uchar temp;
  void main()
  {
  	 temp = 0xfe;
	 P1 = temp;
	 while(1)
	 {
		temp = _crol_(temp,1);
		delay(10);
		P1 = temp;
	 }
   }
 void delay(uint z)
  {
  	uint x, y;
	for(x = 100; x > 0; x--)
		for(y = z; y > 0; y--);

  }	  
  
