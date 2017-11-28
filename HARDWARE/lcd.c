
#include "lcd.h"

typedef struct
{
	u8 T2   : 1;
	u8 T1   : 1;
	u8 T3   : 1;
	u8 T4   : 1;
	u8 X4   : 1;
	u8 Re   : 2;
	u8 X5   : 1;
} HTB_SEG_0;

typedef struct
{
	u8 X1   : 1;
	u8 X2   : 1;
	u8 X3   : 1;
	u8 Re   : 1;
	u8 DA   : 1;
	u8 DF   : 1;
	u8 DE   : 1;
	u8 Lx   : 1;
} HTB_SEG_1;

typedef struct
{
	u8 DB   : 1;
	u8 DG   : 1;
	u8 DC   : 1;
	u8 DD   : 1;
	u8 DA   : 1;
	u8 DF   : 1;
	u8 DE   : 1;
	u8 Lx   : 1;
} HTB_SEG_2;

typedef struct
{
	u8 DB   : 1;
	u8 DG   : 1;
	u8 DC   : 1;
	u8 DD   : 1;
	u8 Re   : 4;
} HTB_SEG_3;

typedef union
{
  	uint8_t htb_ram[7];

	typedef struct
	{
		HTB_SEG_0 Seg_0_1;
		HTB_SEG_1 Seg_3_4;
		
		HTB_SEG_2 Seg_5_6;
		HTB_SEG_2 Seg_7_8;
		HTB_SEG_2 Seg_9_10;
		HTB_SEG_2 Seg_11_12;
		
		HTB_SEG_3 Seg_13_14;
	} Htb_Ram
}HTB_RAM;

HTB_RAM Htb_Ram;
















