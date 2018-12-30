#include <descriptor.h>
#include <interrupt.h>
#include <video.h>
#include <keymap.h>

int x,y; //鼠标的坐标
void main(void)
{
	struct BOOTINFO *binfo = (struct BOOTINFO*) 0x0ff0;
	int xsize, ysize;
	char mcursor[256];
	
	clear_screen();
	init_gdt();
	init_idt();

	init_palette();/* 设定调色板 */
	init_keyboard();
	init_mouse();
	
	init_screen8(binfo->vram, binfo->scrnx, binfo->scrny);/* 加载背景色 */

	init_mouse_cursor(mcursor, COL8_848484);
	putblock(binfo->vram, binfo->scrnx, 16, 16, 80, 80, mcursor, 16);
	
	//x,y代表当前输出字符的位置
	x = 8;
	y = 24;
	int ti = 0;
	for (;;) {
		showString(binfo->vram,binfo->scrnx , 0 , 8, COL8_000084, "Welcome to my OS");	
		int scode = keyboard_read();
		if (scode != -1) {
			if(x >= 320){
				x = 8;
				y += 16;
				if(y>100) y =32;
			}
			showFont8(binfo->vram, binfo->scrnx, x, y, COL8_FFFFFF, systemFont+  keymap[scode*3] * 16);
			x+=8;
		}
		
		//mouse_read();
	}
}
