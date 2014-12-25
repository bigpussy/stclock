
#include<STC12C5A60S2.h>
#include<string.h>
#include<pwm.h>
#include<ds1302.h>
#include<lcd1602.h>

/*********************************************************************************************
�����������뼶CPU��ʱ����
��  �ã�DELAY_MS (?);
��  ����1~65535����������Ϊ0��
����ֵ����
��  ����ռ��CPU��ʽ��ʱ�������ֵ��ͬ�ĺ���ʱ��
��  ע��Ӧ����1T��Ƭ��ʱi<600��Ӧ����12T��Ƭ��ʱi<125
/*********************************************************************************************/
void DELAY_MS (unsigned int a){
	unsigned int i;
	while( a-- != 0){
		for(i = 0; i < 600; i++);
	}
}
/*********************************************************************************************/
// ������ʾ�Ĵ�������
void print_xq(void){
		switch (xq)
		{
			case 0x01:print(0x8b,"MON");
			case 0x02:print(0x8b,"TUE");
			case 0x03:print(0x8b,"WED");
			case 0x04:print(0x8b,"THU");
			case 0x05:print(0x8b,"FRI");
			case 0x06:print(0x8b,"SAT");
			case 0x07:print(0x8b,"SUN");
		}
}

/*********************************************************************************************/
// ��ʾ��Ŀ ʱ�䲿�� �ڵ�һ��ȫ����ʾʱ��
/*********************************************************************************************/    
void RealTime_Display(void){
	read_clockS();  //���ȶ�ȡʱ��
	print(0x80,"20");
	print2(0x82,yy/16+0x30);
	print2(0x83,yy%16+0x30);
	print(0x84,"-");            // ��ʾ��
	//
	print2(0x85,mo/16+0x30);
	print2(0x86,mo%16+0x30);
	print(0x87,"-");            // ��ʾ��
	//
	print2(0x88,dd/16+0x30);
	print2(0x89,dd%16+0x30);
	
	print_xq();
	
	print2(0x40,hh/16+0x30);//Сʱ
	print2(0x41,hh%16+0x30);
	print(0x42,":");            // ��ʾcgram��һ����ģ"��"
	//
	print2(0x43,mm/16+0x30);//����
	print2(0x44,mm%16+0x30);
	print(0x45,":");            // ��ʾcgram��һ����ģ"."
	//
	print2(0x46,ss/16+0x30);//��
	print2(0x47,ss%16+0x30);
	//
}
/********************************************************************************************/

/********************************************************************************************/
//������
/********************************************************************************************/

void main (void){   
	PWM_init();	
	LCM2402_Init();//LCM2402��ʼ��  
	BACK = 0;	//�б���
	PWM0_set(0xA0); //ƫѹ���� Խ����Ļ����Խ��
	Init_1302();
	while(1){ //���߳�// 
		read_clockS();
		RealTime_Display(); 
		DELAY_MS(1000);   //1����ʱ
	}
}