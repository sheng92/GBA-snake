#ifndef MYLIB_H
#define MYLIB_H

typedef unsigned char	u8;
typedef unsigned short	u16;
typedef unsigned int	u32;

// gba macros
#define REG_DISPCNT *(u16 *) 0x4000000
#define RGB(r,g,b) ((r)|((g)<<5)|((b)<<10))
#define OFFSET(r, c, rowlen)  ((r)*(rowlen)+(c))
#define SCANLINECOUNTER ((unsigned short *) 0x4000006)
#define MODE3 3
#define MODE4 4
#define BG2_ENABLE 1<<10

// Sheng Jiang
// button macros
#define BUTTONS (*(unsigned int *) 0x4000130)
#define BUTTON_A      (1<<0)
#define BUTTON_B      (1<<1)
#define BUTTON_SELECT (1<<2)
#define BUTTON_START  (1<<3)
#define BUTTON_RIGHT  (1<<4)
#define BUTTON_LEFT   (1<<5)
#define BUTTON_UP     (1<<6)
#define BUTTON_DOWN   (1<<7)
#define BUTTON_R      (1<<8)
#define BUTTON_L      (1<<9)
#define PRESSED(button) (~(BUTTONS)&button)

// color macros
#define BORDER RGB(0,0,0)
#define APPLE RGB(31,31,31)
#define SNAKE RGB(10,5,0)
#define GRASS RGB(5,24,0)
#define RED RGB(31,0,0)
#define ORANGE RGB(31,12,0)
#define YELLOW RGB(31,31,0)
#define GREEN RGB(0,31,0)
#define CYAN RGB(0,31,31)
#define BLUE RGB(0,0,31)
#define BLACK RGB(0,0,0)
#define WHITE RGB(31,31,31)


extern u16 *videoBuffer;


//function prototypes
void wait_for_vblank();
void setPixel(int r, int c, u16 color);
void drawRect(int r, int c, int height, int width, u16 color);
void drawHollowRect(int r, int c, int height, int width, u16 color);
void plotLine(int r0, int c0, int r1, int c1, u16 color);


#endif
