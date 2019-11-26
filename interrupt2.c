#include "gba1.h"
#define KEY_IN (~(*(hword *) KEY_STATUS) & KEY_ALL)
#define CURRENT_TIME *((unsigned short *)0x0400010C)

/* �֐��̃v���g�^�C�v�錾 */
void display_time(hword);
void int_handler(void);

int main(void) {
	
	volatile unsigned short time;
	unsigned short timer_on = 0;

	/* ��ʏ��������[�`�� */
	*((unsigned short *)IOBASE) = 0xF03;

	/* �^�C�}���������[�`�� */
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
	
	// �����\��
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
	
	/* ���͒lval�̌���(i+1)�ݒ� (i=3�̏ꍇ4���\��)*/
	i = 3;

	/* ������̍Ō��NULL�R�[�h�}�� */
	buf[i+1] = 0;
	
	/* �ŉ��ʌ��̕����i10�Ŋ������]��j��}�����C���͒l��10�Ŋ��� */
	for(; i >= 0; i--) {
		buf[i] = char_data[mod(val, 10)];
		val = div(val, 10);
	}
	
	/* ������S�̂�\�� */
	prints(buf);
	
	return;
}

void int_handler(void){

	if(*((unsigned short *)0x04000202) == 0x0020){

		*((unsigned short *)0x04000208) = 0x0000;

		/* time �\���ʒu�ݒ� */
		locate(25, 0);
		display_time(CURRENT_TIME);

		*((unsigned short *)0x04000202) = 0x0020;
	
		*((unsigned short *)0x04000208) = 0x0001;

		/* �����\���ʒu�ݒ� */
		locate(15, 7);

	}else if(*((unsigned short *)0x04000202) == 0x1000){

		*((unsigned short *)0x04000208) = 0x0000;

		/* �����\���ʒu�ݒ� */
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

		/* �����\���ʒu�ݒ� */
		locate(15, 7);

	}
}