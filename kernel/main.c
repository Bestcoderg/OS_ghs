#include <descriptor.h>
#include <interrupt.h>
#include <video.h>
#include <keymap.h>
#include "mouse.h"
#include "sheet.h"
int x,y; //输入的字符的位置的坐标
int mx,my; //鼠标的位置
void main(void)
{
	struct BOOTINFO *binfo = (struct BOOTINFO*) 0x0ff0;
	int xsize, ysize;
	char mcursor[256];
	MOUSE_DEC mdec;
	char s[40];
	SHTCTL *shtctl;
	SHEET *sht_back, *sht_mouse;
	unsigned char *buf_back;

	//clear_screen();
	init_gdt();
	init_idt();
	io_sti();

	init_keyboard();
	init_mouse();
	init_palette();/* 设定调色板 */
	mdec.phase = 0;


	shtctl = shtctl_init(binfo->vram, binfo->scrnx, binfo->scrny);
	sht_back  = sheet_alloc(shtctl);
	sht_mouse = sheet_alloc(shtctl);
	buf_back = (unsigned char *) 0x810000;
	
	sheet_setbuf(sht_back, buf_back, binfo->scrnx, binfo->scrny, -1); /* 没有透明色 */
	sheet_setbuf(sht_mouse, mcursor, 16, 16, 99); /* 透明色号99 */
	 

	init_screen8(buf_back, binfo->scrnx, binfo->scrny);/* 加载背景色 */
	//init_screen8(binfo->vram, binfo->scrnx, binfo->scrny);/* 加载背景色 */
	init_mouse_cursor(mcursor, COL8_848484);
	mx = (binfo->scrnx - 16) / 2;
    my = (binfo->scrny - 28 - 16) / 2;  

	//putblock(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16); /* 描画鼠标 */
	

    sheet_slide(shtctl, sht_mouse, mx, my);
	sheet_updown(shtctl, sht_back,  0);
	sheet_updown(shtctl, sht_mouse, 1);

	//x,y代表当前输出字符的位置
	x = 8;
	y = 24;
	int ti = 0;
	int i;
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
			//showFont8(buf_back, binfo->scrnx, x, y, COL8_FFFFFF, systemFont+  keymap[scode*3] * 16);
			x+=8;
		}
		i = mouse_read();
		if (i != -1) {
			if (mouse_decode(&mdec, i) != 0) {
				/* 3字节都凑齐了，所以把它们显示出来*/
				if ((mdec.btn & 0x01) != 0) {
					s[1] = 'L';
				}
				if ((mdec.btn & 0x02) != 0) {
					s[3] = 'R';
				}
				if ((mdec.btn & 0x04) != 0) {
					s[2] = 'C';
				}
				/* 鼠标指针的移动 */
				//boxfill8(binfo->vram, binfo->scrnx, COL8_848484, mx, my, mx + 15, my + 15); /* 隐藏鼠标 */
				mx += mdec.x;
				my += mdec.y;
				if (mx < 0) {
					mx = 0;
				}
				if (my < 0) {
					my = 0;
				}
				if (mx > binfo->scrnx - 16) {
					mx = binfo->scrnx - 16;
				}
				if (my > binfo->scrny - 16) {
					my = binfo->scrny - 16;
				}
				//putblock(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16); /* 描画鼠标 */
				sheet_slide(shtctl, sht_mouse, mx, my); /* 包含sheet_refresh含sheet_refresh */
			}
		}
	}
}
