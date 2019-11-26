#include "gba1.h"
#define KEY_IN (~(*(hword *) KEY_STATUS) & KEY_ALL)
#define CURRENT_TIME *((unsigned short *)0x0400010C)

/* 関数のプロトタイプ宣言 */
void display_time(hword);
void int_handler(void);

int main(void) {
	
	volatile unsigned short time;
	unsigned short timer_on = 0;

	/* 画面初期化ルーチン */
	*((unsigned short *)IOBASE) = 0xF03;

	/* タイマ初期化ルーチン */
	*((unsigned short *)0x04000100) = (0xFFFF - 1780);
	*((unsigned short *)0x04000104) = (0xFFFF - 100);
	*((unsigned short *)0x04000108) = (0xFFFF - 10);
	*((unsigned short *)0x0400010C) = 0x0000;

	*((unsigned short *)0x04000102) = 0x0080;
	*((unsigned short *)0x04000106) = 0x0084;
	*((unsigned short *)0x0400010A) = 0x00C4;
	*((unsigned short *)0x0400010E) = 0x0084;

	*((unsigned short *)0x04000102) = 0x0080;
	*((unsigned short *)0x04000200) = 0x1020;
	*((unsigned short *)0x04000208) = 0x0001;

	*((unsigned short *)0x04000132) = 0x43FF;
	
	// 文字表示
	locate(1, 5);
	prints("Press Any Key!");
	
	locate(1, 7);
	prints("Pressed Key = ");

	
	while (1) {}

	*((hword *)0x04000102) = 0x0080;

	return 0;

}


void display_time(hword val) {
	
	byte char_data[] = "0123456789";
	byte buf[6];
	hword tmp;
	int i;
	
	/* 入力値valの桁数(i+1)設定 (i=3の場合4桁表示)*/
	i = 3;

	/* 文字列の最後にNULLコード挿入 */
	buf[i+1] = 0;
	
	/* 最下位桁の文字（10で割った余り）を挿入し，入力値を10で割る */
	for(; i >= 0; i--) {
		buf[i] = char_data[mod(val, 10)];
		val = div(val, 10);
	}
	
	/* 文字列全体を表示 */
	prints(buf);
	
	return;
}

void int_handler(void){

	if(*((unsigned short *)0x04000202) == 0x0020){

		*((unsigned short *)0x04000208) = 0x0000;

		/* time 表示位置設定 */
		locate(25, 0);
		display_time(CURRENT_TIME);

		*((unsigned short *)0x04000202) = 0x0020;
	
		*((unsigned short *)0x04000208) = 0x0001;

		/* 文字表示位置設定 */
		locate(15, 7);

	}else if(*((unsigned short *)0x04000202) == 0x1000){

		*((unsigned short *)0x04000208) = 0x0000;

		/* 文字表示位置設定 */
		locate(15, 7);

		switch (KEY_IN) {

			case KEY_L: 		prints("L     "); break;

			case KEY_R: 		prints("R     "); break;
				
			case KEY_DOWN: 		prints("DOWN  "); break;

			case KEY_UP: 		prints("UP    "); break;

			case KEY_LEFT: 		prints("LEFT  "); break;

			case KEY_RIGHT: 	prints("RIGHT "); break;

			case KEY_START: 	prints("START "); break;

			case KEY_SELECT:	prints("SELECT"); break;

			case KEY_B: 		prints("B     "); break;

			case KEY_A: 		prints("A     "); break;

			default: 		prints("      "); break;
		}
		
		*((unsigned short *)0x04000202) = 0x1000;
	
		*((unsigned short *)0x04000208) = 0x0001;

		/* 文字表示位置設定 */
		locate(15, 7);

	}
}