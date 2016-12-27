#ifndef MYLIB_H_
#define MYLIB_H_

#define REG_DISPCTL *(unsigned short *)0x4000000
#define MODE3 3
#define BG2_ENABLE (1<<10)

extern unsigned short *videoBuffer;

#define COLOR(r, g, b)   ((r) | (g)<<5 | (b)<<10)
#define RED COLOR(31,0,0)
#define GREEN COLOR(0, 31, 0)
#define BLUE COLOR(0,0,31)
#define WHITE COLOR(31,31,31)
#define YELLOW COLOR(31,31,0)
#define BLACK 0

#define OFFSET(r, c, rowlen) ((r)*(rowlen) + (c))
#define SCANLINECOUNTER (*(volatile unsigned short *)0x4000006)

// Buttons

#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT	(1<<2)
#define BUTTON_START	(1<<3)
#define BUTTON_RIGHT	(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)

#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)

#define BUTTONS *(volatile unsigned int *)0x4000130
//DMA
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct {
	const volatile void *src;
	volatile void *dst;
	volatile u32 cnt;
} DMA_CONTROLLER;

#define DMA ((volatile DMA_CONTROLLER*) 0x40000B0)
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)
struct brick{
	int posx;
	int posy;
	u16 color;
	int visible;
};
struct player{
	int x;
	int y;
};
struct _ball{
	int centerX;
	int centerY;
};

extern const char* level1;
extern struct player player1;

extern struct _ball ball1;

extern struct brick allBrick[42];
extern int score;

extern const unsigned char fontdata_6x8[12288];




//Prototypes
void drawImage3(int r,int c,int width,int height,const u16* image);
void drawRect(int x,int y,int width, int height,u16 color);
void drawBrick(struct brick brick1);
void waitForVBlank();
void drawLevel(const char* map);
void drawPlayer(int x, int y);
void drawBall(int centX, int centY);
struct brick makeBrick(struct brick brick1, int x,int y, u16 color, int visible);
int detectCollision(struct _ball ball1, int ballSpeedX, int ballSpeedY);
int inRect(int x,int y, struct brick brick1);
int inPlayer(int x,int y, struct player player1);
void reDrawBrick();
void drawScore();
void drawChar(int row, int col, char ch, u16 color);
void drawString(int row, int col, char *str, u16 color);
void setPixel(int r, int c, u16 color);
#endif