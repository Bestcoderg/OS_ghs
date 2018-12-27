#include <descriptor.h>
#include <interrupt.h>
#include <video.h>

unsigned char *vram;/* 声明变量vram、用于BYTE [...]地址 */
int x,y;
void main(void)
{
	clear_screen();
	int xsize, ysize;
	char mcursor[256];
	vram = (unsigned char *) 0xa0000;/* 地址变量赋值 */
	xsize = 320;
	ysize = 200;

	init_gdt();
	init_idt();

	init_palette();/* 设定调色板 */

	init_keyboard();
	/* 根据 0xa0000 + x + y * 320 计算坐标 8*/
	
	boxfill8(vram, xsize, COL8_848484,  0,         0,          xsize -  1, ysize - 21);
	boxfill8(vram, xsize, COL8_C6C6C6,  0,         ysize - 20, xsize -  1, ysize - 19);
	boxfill8(vram, xsize, COL8_FFFFFF,  0,         ysize - 19, xsize -  1, ysize - 18);
	boxfill8(vram, xsize, COL8_C6C6C6,  0,         ysize - 18, xsize -  1, ysize -  1);
	

	init_mouse_cursor(mcursor, COL8_848484);
	putblock(vram, xsize, 16, 16, 80, 80, mcursor, 16);
	
	init_mouse();

	//x,y代表当前输出字符的位置
	x = 8;
	y = 24;
	int ti = 0;
	//asm volatile("int $44");
	//showString((unsigned char *) 0xa0000, 320, 8, 24, COL8_FFFFFF, "Welcome");
	for (;;) {
		//io_hlt();

		//if(x>300) x = 32;

		if(x >= 320){
			x = 8;
			y += 16;
			if(y>100) y =32;
		}
		
		keyboard_read();
		
		//mouse_read();
	}
}
