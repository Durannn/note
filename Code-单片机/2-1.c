  #include<reg52.h>
  #define uint unsigned int
  #define uchar unsigned char
  sbit D1 = P1^0;
 // void delay();
  void delay(uint z);
  void main()
  {
	 while(1)
	 {
	 	D1=0;
 		delay(10);
 		D1=1;
		delay(10);
	 }
   }
 /* void delay()
  {
  	uint x, y;
	for(x = 100; x > 0; x--)
		for(y = 600; y > 0; y--);

  }	  
  */
 void delay(uint z)
  {
  	uint x, y;
	for(x = z; x > 0; x--)
		for(y = 120; y > 0; y--);

  }	  
  
