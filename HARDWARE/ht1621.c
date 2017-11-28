
#include "ht1621.h"
#include "delay.h"

extern uint8_t Slot_Rand;
extern uint8_t Slot_Rand1;
extern uint8_t Which_Song;
extern uint8_t Gam_Err_Val;
extern uint8_t Gam_Sco_Val;
extern uint8_t Gam_Vol_Val; 
extern uint8_t Gam_Mod_Val;
extern uint8_t Gam_Sud_Val;
extern uint8_t Gam_Sud_Val;
extern uint8_t Gam_Spd_Val;
extern uint16_t Battery_Val;
extern uint16_t Mod1_Sco_Val;
extern uint16_t Mod2_Sco_Val;
extern uint16_t Slot_Sco_Val;
extern BitStatus Bat_IsCharg;
extern BitStatus Gam_IsBegin;
extern BitStatus Mode_OfPiano;
extern uint16_t Gam_Sco_[7];
extern uint8_t Max_Err_Tim[8];

extern uint8_t Slot_Time;
extern uint8_t dijicizhongjiang;

HTB_RAM Htb_Ram;

//extern const uint8_t Temp1[7];
/*******************************************************************************
 * �� �� ��: Ht1621_Gpio_Init
 * ����˵��: ��ʼ��HT��MCU�����Ĺܽ�
 * ��    ��: void
 * �� �� ֵ: void
 ******************************************************************************/
static void Ht1621_Gpio_Init(void)
{
	GPIO_Init(HT_PORT, (GPIO_Pin_TypeDef)(HT_WR|								// HT_WR
	  									  HT_RD|								// HT_RD
										  HT_DATA),GPIO_MODE_OUT_PP_LOW_FAST);	// HT_DATA						
	GPIO_Init(HT_PORT, HT_CS,GPIO_MODE_OUT_PP_HIGH_FAST);						// HT_CS
	GPIO_Init(HT_PORT0, HT_LEDB,GPIO_MODE_OUT_PP_LOW_SLOW);
}

/*******************************************************************************
 * �� �� ��: Ht1621_send_high_bit
 * ����˵��: ��HT�������ݣ���λΪ����or��ַ���Ӹߵ���д��
 * ��    ��: data��������ַ;len������;
 * �� �� ֵ: void
 ******************************************************************************/
static void Ht1621_send_high_bit(uint8_t data, uint8_t len)
{
	uint8_t i;
	for (i=0; i<len; i++)
	{
		(data&0x80)?GPIO_WriteHigh(HT_PORT,HT_DATA):							// HT_DATA = 1
		  			GPIO_WriteLow(HT_PORT,HT_DATA);								// HT_DATA = 0
		delay_us(2);
		GPIO_WriteHigh(HT_PORT,HT_WR);
		delay_us(2);
		GPIO_WriteLow(HT_PORT,HT_WR);
		data <<= 1;
	}
}
/*******************************************************************************
 * �� �� ��: Ht1621_send_low_bit
 * ����˵��: ��HT�������ݣ���λΪ���ݣ��Ӹߵ���д��or����
 * ��    ��: data������;len������;
 * �� �� ֵ: void
 ******************************************************************************/
static void Ht1621_send_low_bit(uint8_t data, uint8_t len)
{
	uint8_t i;
	for (i=0; i<len; i++)
	{
		(data&0x01)?GPIO_WriteHigh(HT_PORT,HT_DATA):							// HT_DATA = 1
		  			GPIO_WriteLow(HT_PORT,HT_DATA);								// HT_DATA = 0
		delay_us(2);
		GPIO_WriteHigh(HT_PORT,HT_WR);
		delay_us(2);
		GPIO_WriteLow(HT_PORT,HT_WR);
		data >>= 1;
	}
}
/*******************************************************************************
 * �� �� ��: Ht1621_send_cmd
 * ����˵��: ��HT��������
 * ��    ��: command������;
 * �� �� ֵ: void
 ******************************************************************************/
static void Ht1621_send_cmd(uint8_t command)
{
  	__disable_interrupt();
	GPIO_WriteLow(HT_PORT,HT_CS);												// Ƭѡ
	Ht1621_send_high_bit(0x80, 4);												// ����ģʽ
	Ht1621_send_high_bit(command, 8);											// ��������
	GPIO_WriteHigh(HT_PORT,HT_CS);
	__enable_interrupt();
}
/*******************************************************************************
 * �� �� ��: Ht1621_send_dat
 * ����˵��: ��HT��������
 * ��    ��: addr����ַ;data������;
 * �� �� ֵ: void
 ******************************************************************************/
//static void Ht1621_send_dat(uint8_t addr, uint8_t data)							// addr ���� 0��1��2��3��4��5������31.
//{
//  	__disable_interrupt();
//	GPIO_WriteLow(HT_PORT,HT_CS);
//	Ht1621_send_high_bit(0xA0, 3);												// ����ģʽ
//	Ht1621_send_high_bit(addr<<2, 6);											// ��ַ
//	Ht1621_send_low_bit(data, 4);												// д�������
//	GPIO_WriteHigh(HT_PORT,HT_CS);
//	__enable_interrupt();
//}
/*******************************************************************************
 * �� �� ��: Ht1621_write_all
 * ����˵��: ��HT��������,����ģʽ
 * ��    ��: addr����ַ;p������ָ��;len������;
 * �� �� ֵ: void
 ******************************************************************************/
void Ht1621_write_all(uint8_t addr, uint8_t *p, uint8_t len)
{
	uint8_t i;
	
	GPIO_WriteLow(HT_PORT,HT_CS);
	Ht1621_send_high_bit(0xA0, 3);
	Ht1621_send_high_bit(addr<<2, 6);
	
	for (i=0; i<len; i++, p++)
	{
		Ht1621_send_low_bit(*p, 8);
	}
	GPIO_WriteHigh(HT_PORT,HT_CS);
}
/*******************************************************************************
 * �� �� ��: Ht1621_clr_all_display
 * ����˵��: ��HT��������,����ģʽ
 * ��    ��: addr����ַ;p������ָ��;len������;
 * �� �� ֵ: void
 ******************************************************************************/
//void Ht1621_clr_all_display(void)
//{
//	uint8_t i;
//	uint8_t addr = 0;
//	
//	for (i=0; i<32; i++)
//	{
//		Ht1621_send_dat(addr, 0x00);
//		Ht1621_send_dat(addr+1, 0x00);
//		addr += 2;
//	}
//}
/*******************************************************************************
 * �� �� ��: Ht1621_all_display
 * ����˵��: ��ʾLCD��ȫ���ֶ�
 * ��    ��: void
 * �� �� ֵ: void
 ******************************************************************************/
//void Ht1621_all_display(void)
//{
//	uint8_t i;
//	uint8_t addr = 0;
//	
//	for (i=0; i<32; i++)
//	{
//		Ht1621_send_dat(addr, 0x0F);
//		Ht1621_send_dat(addr+1, 0x0F);
//		addr += 2;
//	}	
//}
/*******************************************************************************
 * �� �� ��: Ht1621_Init
 * ����˵��: ��ʼ��Ht1621
 * ��    ��: void
 * �� �� ֵ: void
 ******************************************************************************/
void Ht1621_Init(void)
{
  	Ht1621_Gpio_Init();
	Ht1621_send_cmd(HT_SYS_EN);													// ��ϵͳ����
	Ht1621_send_cmd(HT_RCOSC);													// Ƭ��RC����
	Ht1621_send_cmd(HT_BISA1_3_COM);											// 1/3ƫѹ 4��������
	Ht1621_send_cmd(HT_LCD_ON);													// ����LCD���
//	Ht1621_send_cmd(HT_TONE_OFF);												// �ر�TONE���
//	Ht1621_send_cmd(HT_TIMER_DIS);												// ʱ�����ʧЧ
//	Ht1621_send_cmd(HT_WDT_DIS);
//	Ht1621_clr_all_display();
}
/*******************************************************************************
 * �� �� ��: Ht1621_Show_One_Num
 * ����˵��: �ڵ�ַaddr����ʾ����data
 * ��    ��: addr: 0-6,�˿�LCD����ʾ7������;
			 num: 0-f,���ְ���0-f;
 * �� �� ֵ: void
 ******************************************************************************/
void Ht1621_Show_One_Num(uint8_t addr, uint8_t num, uint8_t add)
{
  	switch(addr)
	{
		case 1:
		{
		  	Ht1621_Show_Num(&Htb_Ram.HTB_SEG.Seg_3_4,&Htb_Ram.HTB_SEG.Seg_5_6,num,add);
		}break;
		case 2:
		{
		  	Ht1621_Show_Num(&Htb_Ram.HTB_SEG.Seg_5_6,&Htb_Ram.HTB_SEG.Seg_7_8,num,add);
		}break;
		case 3:
		{
		  	Ht1621_Show_Num(&Htb_Ram.HTB_SEG.Seg_7_8,&Htb_Ram.HTB_SEG.Seg_9_10,num,add);
		}break;
		case 4:
		{
		  	Ht1621_Show_Num(&Htb_Ram.HTB_SEG.Seg_9_10,&Htb_Ram.HTB_SEG.Seg_11_12,num,add);
		}break;
		case 5:
		{
		  	Ht1621_Show_Num(&Htb_Ram.HTB_SEG.Seg_11_12,&Htb_Ram.HTB_SEG.Seg_13_14,num,add);
		}break;
		default:break;
	}
}
/*******************************************************************************
 * �� �� ��: Ht1621_Show_Num
 * ����˵��: ��LCD�ĵ�addr��λ����ʾ����data
 * ��    ��: htb_ram: HT1621�ڴ�ṹ��ָ��
			 num: 0-6,��LCD��Ҫ��ʾ��λ��;
			 dat: 0-f,����0-9;
			 add: 0,����ʾ;1,������ʾ;
 * �� �� ֵ: void
 ******************************************************************************/
void Ht1621_Show_Num(Htb_Seg *htb_ram1,Htb_Seg *htb_ram2,uint8_t num,uint8_t add)
{
	switch(num)
	{
		case 0x00:
		{
			htb_ram1->DxA = add;htb_ram1->DxF = add;htb_ram1->DxE = add;
			htb_ram2->DxB = add;htb_ram2->DxG = 0;htb_ram2->DxC = add;htb_ram2->DxD =add;
		}break;
		case 0x01:
		{
			htb_ram1->DxA = 0;htb_ram1->DxF = 0;htb_ram1->DxE = 0;
			htb_ram2->DxB = add;htb_ram2->DxG = 0;htb_ram2->DxC = add;htb_ram2->DxD = 0;
		}break;
		case 0x02:
		{
			htb_ram1->DxA = add;htb_ram1->DxF = 0;htb_ram1->DxE = add;
			htb_ram2->DxB = add;htb_ram2->DxG = add;htb_ram2->DxC = 0;htb_ram2->DxD = add;
		}break;
		case 0x03:
		{
			htb_ram1->DxA = add;htb_ram1->DxF = 0;htb_ram1->DxE = 0;
			htb_ram2->DxB = add;htb_ram2->DxG = add;htb_ram2->DxC = add;htb_ram2->DxD = add;
		}break;
		case 0x04:
		{
			htb_ram1->DxA = 0;htb_ram1->DxF = add;htb_ram1->DxE = 0;
			htb_ram2->DxB = add;htb_ram2->DxG = add;htb_ram2->DxC = add;htb_ram2->DxD = 0;
		}break;
		case 0x05:
		{
			htb_ram1->DxA = add;htb_ram1->DxF = add;htb_ram1->DxE = 0;
			htb_ram2->DxB = 0;htb_ram2->DxG = add;htb_ram2->DxC = add;htb_ram2->DxD = add;
		}break;
		case 0x06:
		{
			htb_ram1->DxA = add;htb_ram1->DxF = add;htb_ram1->DxE = add;
			htb_ram2->DxB = 0;htb_ram2->DxG = add;htb_ram2->DxC = add;htb_ram2->DxD = add;
		}break;
		case 0x07:
		{
			htb_ram1->DxA = add;htb_ram1->DxF = 0;htb_ram1->DxE = 0;
			htb_ram2->DxB = add;htb_ram2->DxG = 0;htb_ram2->DxC = add;htb_ram2->DxD = 0;
		}break;
		case 0x08:
		{
			htb_ram1->DxA = add;htb_ram1->DxF = add;htb_ram1->DxE = add;
			htb_ram2->DxB = add;htb_ram2->DxG = add;htb_ram2->DxC = add;htb_ram2->DxD = add;
		}break;
		case 0x09:
		{
			htb_ram1->DxA = add;htb_ram1->DxF = add;htb_ram1->DxE = 0;
			htb_ram2->DxB = add;htb_ram2->DxG = add;htb_ram2->DxC = add;htb_ram2->DxD = add;
		}break;
		default: break;
	}
}
/*******************************************************************************
 * �� �� ��: Ht1621_Show_Bat
 * ����˵��: ��ʾ������־����������ʾ
 * ��    ��: bat: 0-3;
 * �� �� ֵ: void
 ******************************************************************************/
void Ht1621_Show_Bat(uint8_t bat)
{
 	Htb_Ram.HTB_SEG.Seg_1_2.DxB = 1;
	switch(bat)
	{
		case 0:
		{
		  	Htb_Ram.HTB_SEG.Seg_1_2.DxD = 1;
			Htb_Ram.HTB_SEG.Seg_1_2.DxG = 0;
			Htb_Ram.HTB_SEG.Seg_1_2.DxB = 0;
			Htb_Ram.HTB_SEG.Seg_1_2.DxC = 0;
		}break;
		case 1:
		{
		  	Htb_Ram.HTB_SEG.Seg_1_2.DxD = 1;
			Htb_Ram.HTB_SEG.Seg_1_2.DxG = 1;
			Htb_Ram.HTB_SEG.Seg_1_2.DxB = 0;
			Htb_Ram.HTB_SEG.Seg_1_2.DxC = 0;
		}break;
		case 2:
		{
		  	Htb_Ram.HTB_SEG.Seg_1_2.DxD = 1;
			Htb_Ram.HTB_SEG.Seg_1_2.DxG = 1;
			Htb_Ram.HTB_SEG.Seg_1_2.DxB = 1;
			Htb_Ram.HTB_SEG.Seg_1_2.DxC = 0;
		}break;
		case 3:
		{
		  	Htb_Ram.HTB_SEG.Seg_1_2.DxD = 1;
			Htb_Ram.HTB_SEG.Seg_1_2.DxG = 1;
			Htb_Ram.HTB_SEG.Seg_1_2.DxB = 1;
			Htb_Ram.HTB_SEG.Seg_1_2.DxC = 1;
		}break;
		default: break;
	}
}
/*******************************************************************************
 * �� �� ��: Ht1621_Show_Mod
 * ����˵��: ��ʾģʽ
 * ��    ��: mod: 0-3;
 * �� �� ֵ: void
 ******************************************************************************/
void Ht1621_Show_Mod(uint8_t mod)
{
	switch(mod)
	{
		case 0:
		{
		  	Htb_Ram.HTB_SEG.Seg_3_4.DxB = 0;
			Htb_Ram.HTB_SEG.Seg_3_4.DxG = 1;
			Htb_Ram.HTB_SEG.Seg_3_4.DxC = 0;
			Htb_Ram.HTB_SEG.Seg_3_4.Lx = 0;
		}break;
		case 1:
		{
		  	Htb_Ram.HTB_SEG.Seg_3_4.DxB = 1;
			Htb_Ram.HTB_SEG.Seg_3_4.DxG = 0;
			Htb_Ram.HTB_SEG.Seg_3_4.DxC = 0;
			Htb_Ram.HTB_SEG.Seg_3_4.Lx = 0;
		}break;
		case 2:
		{
		  	Htb_Ram.HTB_SEG.Seg_3_4.DxB = 0;
			Htb_Ram.HTB_SEG.Seg_3_4.DxG = 0;
			Htb_Ram.HTB_SEG.Seg_3_4.DxC = 0;
			Htb_Ram.HTB_SEG.Seg_3_4.Lx = 1;
		}break;
		case 3:
		{
		  	Htb_Ram.HTB_SEG.Seg_3_4.DxB = 0;
			Htb_Ram.HTB_SEG.Seg_3_4.DxG = 0;
			Htb_Ram.HTB_SEG.Seg_3_4.DxC = 1;
			Htb_Ram.HTB_SEG.Seg_3_4.Lx = 0;
		}break;
		default: break;
	}
}
/*******************************************************************************
 * �� �� ��: Ht1621_Show_Sud
 * ����˵��: ��ʾ����
 * ��    ��: sud: 0-3;
 * �� �� ֵ: void
 ******************************************************************************/
void Ht1621_Show_Sud(uint8_t sud)
{
  	Htb_Ram.HTB_SEG.Seg_1_2.DxA = 1;
	if(Gam_Mod_Val==0||Gam_Mod_Val==3)
		Htb_Ram.HTB_SEG.Seg_1_2.Lx = ((sud)?0:1);
	else
	  	Htb_Ram.HTB_SEG.Seg_1_2.Lx = 0;
}
/*******************************************************************************
 * �� �� ��: Bat_Charging
 * ����˵��: ��ʾ��綯��
 * ��    ��: void
 * �� �� ֵ: void
 ******************************************************************************/
void Bat_Charging(void)
{
  	static uint8_t i = 0;
	if(++i>3) i = 0;
	Ht1621_Show_Bat(i);
}
/*******************************************************************************
 * �� �� ��: Ht1621_BackL_On
 * ����˵��: ����LCD����
 * ��    ��: void
 * �� �� ֵ: void
 ******************************************************************************/
//void Ht1621_BackL_On(void)
//{
//	GPIO_WriteLow(HT_PORT0,HT_CTR1);
//}
/*******************************************************************************
 * �� �� ��: Ht1621_BackL_Off
 * ����˵��: �ر�LCD����
 * ��    ��: void
 * �� �� ֵ: void
 ******************************************************************************/
//void Ht1621_BackL_Off(void)
//{
//	GPIO_WriteHigh(HT_PORT0,HT_CTR1);
//}


/*----------------------------------------------------------------------------*/

/*******************************************************************************
 * �� �� ��: Ht1621_Show_BAT
 * ����˵��: ���ݵ�ص�����ʾ������־
 * ��    ��: bat: ADֵ
 * �� �� ֵ: void
 ******************************************************************************/
void Ht1621_Show_BAT(uint16_t bat)
{
	if(bat>600) Ht1621_Show_Bat(0x03);											//����4V
	else if(bat>580) Ht1621_Show_Bat(0x02);										//����3.8V
	else if(bat>560) Ht1621_Show_Bat(0x01);										//����3.6V
	else Ht1621_Show_Bat(0x00);													//С��3.6V
}
/*******************************************************************************
 * �� �� ��: Ht1621_Show_All
 * ����˵��: ����ģʽ��ʾ����ʾ������
 * ��    ��: gam_mod: ģʽ
 * �� �� ֵ: void
 ******************************************************************************/
void Ht1621_Show_All(uint8_t gam_mod)
{
	switch(gam_mod)																// ģʽ��ͬ,LCD��ʾ�����ݲ�ͬ
	{
		case 0x00:
		{
		  	Htb_Ram.HTB_SEG.Seg_7_8.Lx = 1;//L3
			Htb_Ram.HTB_SEG.Seg_9_10.Lx = 1;//L4
			Htb_Ram.HTB_SEG.Seg_11_12.Lx = 1;//L5
			
			if(Gam_IsBegin)	
			{
			  	Ht1621_Show_Sco(Gam_Sco_Val);
				Ht1621_Show_One_Num(4,Gam_Err_Val,1);							// �������
			}
			else
			{
			  	Ht1621_Show_Sco(Gam_Sco_[Gam_Spd_Val-1]);
				Ht1621_Show_One_Num(4,Max_Err_Tim[Gam_Spd_Val-1],1);			// ��������������
			}
			
			Ht1621_Show_One_Num(5,Gam_Spd_Val,1);								//��ǰ�ؿ�
		}break;
		case 0x01:
		{
		  	Htb_Ram.HTB_SEG.Seg_7_8.Lx = 1;//L3
			Htb_Ram.HTB_SEG.Seg_9_10.Lx = 1;//L4
			Htb_Ram.HTB_SEG.Seg_11_12.Lx = 0;//L5
			
			Ht1621_Show_Sco(Mod1_Sco_Val);
			
			Ht1621_Show_One_Num(4,Gam_Sud_Val,1);								//��ʾ��Ч
			
			Ht1621_Show_One_Num(5,0,0);
		}break;
		case 0x02:
		{
		  	Htb_Ram.HTB_SEG.Seg_7_8.Lx = 1;//L3
			Htb_Ram.HTB_SEG.Seg_9_10.Lx = 1;//L4
			
			Ht1621_Show_Sco(Mod2_Sco_Val);
			
			Ht1621_Show_One_Num(4,Mode_OfPiano,1);								//��ʾ��Ч
			if(Mode_OfPiano)
			{
				Ht1621_Show_One_Num(5,Which_Song,1);
				Htb_Ram.HTB_SEG.Seg_11_12.Lx = 1;//L5
			}
			else
			{
			  	Ht1621_Show_One_Num(5,Which_Song,0);
				Htb_Ram.HTB_SEG.Seg_11_12.Lx = 0;//L5
			}
		}break;
		case 0x03:
		{	
		  	Htb_Ram.HTB_SEG.Seg_7_8.Lx = 1;//L3
			Htb_Ram.HTB_SEG.Seg_9_10.Lx = 0;//L4
			Htb_Ram.HTB_SEG.Seg_11_12.Lx = 0;//L5
			
			Ht1621_Show_Sco(Slot_Sco_Val);//dijicizhongjiang
//			Ht1621_Show_Sco();
//			
 			Ht1621_Show_One_Num(4,0,0);
//			
//			Ht1621_Show_One_Num(5,Slot_Time,1);
		}break;
		default:break;
	}

	Ht1621_Show_Sud(Gam_Vol_Val);												// ������ʾ
	
	Ht1621_write_all(0x00, (uint8_t *)&Htb_Ram.HTB_Ram[0x00],0x07);
	  
	if(!Bat_IsCharg)															// û�г��ʱ ��ʾ����
		Ht1621_Show_BAT(Battery_Val);
}
/*******************************************************************************
 * �� �� ��: Ht1621_Show_Sco
 * ����˵��: ����ģʽ��ʾ����ʾ������
 * ��    ��: gam_mod: ����
 * �� �� ֵ: void
 ******************************************************************************/
void Ht1621_Show_Sco(uint16_t Sco_Val )
{
  	uint8_t gewei=0,shiwei=0,baiwei=0;
	
	baiwei = Sco_Val/100;
	shiwei = Sco_Val%100/10;
	gewei  = Sco_Val%10;
	
	
	if(baiwei==0)
	{
	  	if(shiwei==0)
		{
			Ht1621_Show_One_Num(1,baiwei,0);
			Ht1621_Show_One_Num(2,gewei,1);
			Ht1621_Show_One_Num(3,shiwei,0);
		}
		else
		{
			Ht1621_Show_One_Num(1,baiwei,0);
			Ht1621_Show_One_Num(2,shiwei,1);
			Ht1621_Show_One_Num(3,gewei,1);
		}
	}
	else
	{
		Ht1621_Show_One_Num(1,baiwei,1);
		Ht1621_Show_One_Num(2,shiwei,1);
		Ht1621_Show_One_Num(3,gewei,1);
	}
}
/*--------------Write-by-xiao-kai-2017-10-10-11-48----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/