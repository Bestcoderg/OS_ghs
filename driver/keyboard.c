/*
 * 初始化键盘相关函数
 */

#include <keyboard.h>
#include <interrupt.h>
<<<<<<< HEAD
<<<<<<< HEAD
=======
#include <keymap.h>
>>>>>>> 3567a07e740acdba4cf5b084e2d8cfd6c2f2df4f
=======
#include <keymap.h>
>>>>>>> 3567a07e740acdba4cf5b084e2d8cfd6c2f2df4f
#include <video.h>
#include "printk.h"
extern int x,y;
/*
 * 说明：注册键盘中断处理函数
 */
static KB_INPUT kb_in;

void init_keyboard()
{
	kb_in.count = 0;
	kb_in.p_head = kb_in.p_tail = kb_in.buf;
	register_interrupt_handler(IRQ1,keyboard_handler);
}

/*
 * 说明：键盘中断处理函数
 */
void keyboard_handler(pt_regs *regs)
{
	unsigned char scancode;
	//printk("keyboard down\n");
	scancode = io_in8(0x60);
	if(kb_in.count < KB_IN_BYTES){
		*(kb_in.p_head) = scancode;
		kb_in.p_head++;
		// 如果满了，又指向开始
		if(kb_in.p_head == kb_in.buf+KB_IN_BYTES){
			kb_in.p_head = kb_in.buf;
		}

	}
	kb_in.count++;
	//printk("0x%02X,",scancode);

}

<<<<<<< HEAD
<<<<<<< HEAD
int keyboard_read()
=======
void keyboard_read()
>>>>>>> 3567a07e740acdba4cf5b084e2d8cfd6c2f2df4f
=======
void keyboard_read()
>>>>>>> 3567a07e740acdba4cf5b084e2d8cfd6c2f2df4f
{
	unsigned char scancode;
    io_cli();
	if(kb_in.count > 0){
		scancode = *(kb_in.p_tail);
		kb_in.p_tail++;
		kb_in.p_tail++;
		// 如果读到了最后
		if(kb_in.p_tail == kb_in.buf + KB_IN_BYTES){
			kb_in.p_tail = kb_in.buf;
		}
		kb_in.count = kb_in.count - 2;
<<<<<<< HEAD
<<<<<<< HEAD
		io_sti();
		return scancode;
	}
    io_sti();
	return -1;
=======
=======
>>>>>>> 3567a07e740acdba4cf5b084e2d8cfd6c2f2df4f
		//boxfill8((unsigned char *) 0xa0000, 320, COL8_848484, 8, 24, 319, 40); //clean last char
		showString((unsigned char *) 0xa0000, 320, 0 , 8, COL8_000084, "Welcome to my OS");
		showFont8((unsigned char *) 0xa0000, 320, x, y, COL8_FFFFFF, systemFont+  keymap[scancode*3] * 16);
		x+=8;
		//showFont8((unsigned char *) 0xa0000, 320, 8, 40, COL8_FFFFFF,systemFont + (unsigned int)(num+'a')*16 );

		//printk("%c",keymap[scancode*3]);
		//print("key pressed", 0);
		//output a char
		
	}
    io_sti();
<<<<<<< HEAD
>>>>>>> 3567a07e740acdba4cf5b084e2d8cfd6c2f2df4f
=======
>>>>>>> 3567a07e740acdba4cf5b084e2d8cfd6c2f2df4f
}
