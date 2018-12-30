#include <descriptor.h>
#include <interrupt.h>
#include <video.h>
#include <keymap.h>

unsigned char *vram;/* 声明变量vram、用于BYTE [...]地址 */
int x,y;
void main(void)
{
	struct BOOTINFO *binfo = (struct BOOTINFO*) 0x0ff0;
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
	
	init_screen8(binfo->vram, binfo->scrnx, binfo->scrny);

	init_mouse_cursor(mcursor, COL8_848484);
	putblock(vram, xsize, 16, 16, 80, 80, mcursor, 16);
	
	init_mouse();
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
