#include <descriptor.h>
#include <interrupt.h>
#include <video.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <keymap.h>
=======

>>>>>>> 3567a07e740acdba4cf5b084e2d8cfd6c2f2df4f
=======

>>>>>>> 3567a07e740acdba4cf5b084e2d8cfd6c2f2df4f
unsigned char *vram;/* 声明变量vram、用于BYTE [...]地址 */
int x,y;
void main(void)
{
<<<<<<< HEAD
<<<<<<< HEAD
	struct BOOTINFO *binfo = (struct BOOTINFO*) 0x0ff0;
=======
>>>>>>> 3567a07e740acdba4cf5b084e2d8cfd6c2f2df4f
=======
>>>>>>> 3567a07e740acdba4cf5b084e2d8cfd6c2f2df4f
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
	
<<<<<<< HEAD
<<<<<<< HEAD
	init_screen8(binfo->vram, binfo->scrnx, binfo->scrny);
=======
=======
>>>>>>> 3567a07e740acdba4cf5b084e2d8cfd6c2f2df4f
	boxfill8(vram, xsize, COL8_848484,  0,         0,          xsize -  1, ysize - 21);
	boxfill8(vram, xsize, COL8_C6C6C6,  0,         ysize - 20, xsize -  1, ysize - 19);
	boxfill8(vram, xsize, COL8_FFFFFF,  0,         ysize - 19, xsize -  1, ysize - 18);
	boxfill8(vram, xsize, COL8_C6C6C6,  0,         ysize - 18, xsize -  1, ysize -  1);
	
<<<<<<< HEAD
>>>>>>> 3567a07e740acdba4cf5b084e2d8cfd6c2f2df4f
=======
>>>>>>> 3567a07e740acdba4cf5b084e2d8cfd6c2f2df4f

	init_mouse_cursor(mcursor, COL8_848484);
	putblock(vram, xsize, 16, 16, 80, 80, mcursor, 16);
	
	init_mouse();

	//x,y代表当前输出字符的位置
	x = 8;
	y = 24;
	int ti = 0;
<<<<<<< HEAD
<<<<<<< HEAD
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
		
=======
=======
>>>>>>> 3567a07e740acdba4cf5b084e2d8cfd6c2f2df4f
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
		
<<<<<<< HEAD
>>>>>>> 3567a07e740acdba4cf5b084e2d8cfd6c2f2df4f
=======
>>>>>>> 3567a07e740acdba4cf5b084e2d8cfd6c2f2df4f
		//mouse_read();
	}
}
