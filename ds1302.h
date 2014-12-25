

sbit clock_clk = P1^0;
sbit clock_dat = P1^1;
sbit clock_Rst = P1^2;

sbit a0 = ACC^0;
sbit a7 = ACC^7;

unsigned char yy,mo,dd,xq,hh,mm,ss;


void write_clock_byte(unsigned char dd){
	unsigned char i;
	ACC = dd;
	for(i = 8; i > 0; i--){
		clock_dat = a0;		
		clock_clk = 1; clock_clk = 0; 
		ACC = ACC>>1;
	}
}

unsigned char read_clock_byte(void){
	unsigned char i;	
	for(i = 8; i > 0;i--){
		ACC = ACC>>1;
		a7 = clock_dat;
		clock_clk = 1; clock_clk = 0;		
	}	
	return(ACC);
}

void write_clock(unsigned char ord,unsigned char dd){
	clock_clk = 0;
	clock_Rst = 0;
	clock_Rst = 1;
	write_clock_byte(ord);
	write_clock_byte(dd);
	clock_Rst = 0;
	clock_clk = 1;
}

unsigned char read_clock(unsigned char ord){
	unsigned char dd = 0;	
	clock_Rst = 0;
	clock_clk = 0;
	clock_Rst = 1;
	write_clock_byte(ord);
	dd = read_clock_byte();
	clock_Rst = 0;
	clock_clk = 1;
	return(dd);
}

void read_clockS(void){
	ss = read_clock(0x81);
	mm = read_clock(0x83);
	hh = read_clock(0x85);
	dd = read_clock(0x87);
	mo = read_clock(0x89);
	yy = read_clock(0x8d);
	xq = read_clock(0x8b);
	xq = xq%16;
}

void Init_1302(void){
	unsigned char f;
	//if(read_clock(0x81)==0x80){
		write_clock(0x8e,0x00); //允许写操作
		write_clock(0x8c,0x10);  //年
		write_clock(0x8a,0x01);  //星期
		write_clock(0x88,0x01);  //月
		write_clock(0x86,0x01);  //日
		write_clock(0x84,0x00);  //小时
		write_clock(0x82,0x00);  //分钟
		write_clock(0x80,0x50);   //秒 
	//}
	write_clock(0x8e,0x80);
}