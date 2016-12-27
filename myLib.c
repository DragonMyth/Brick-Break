//
// Created by yunbo on 4/4/16.
//
#include "myLib.h"
#include "playerBoard.h"
#include "ball.h"
unsigned short *videoBuffer = (unsigned short *)0x6000000;
struct brick allBrick[42] ;
struct player player1;
struct _ball ball1;
int score;

void drawImage3(int r,int c, int width, int height, const u16 *image){
    for(int i=0;i<height;i++){
        DMA[DMA_CHANNEL_3].src = image+i*width;
        DMA[DMA_CHANNEL_3].dst = videoBuffer+c+240*(i+r);
        DMA[DMA_CHANNEL_3].cnt = (width) |
                                 DMA_SOURCE_INCREMENT |
                                 DMA_DESTINATION_INCREMENT |
                                 DMA_ON;
    }
}
void drawRect(int x,int y, int width,int height, u16 color){

    volatile u16 colorn = color;
    for(int i=0;i<height;i++){
        /*
        for(int j=0;j<height;j++){
            videoBuffer[x+i+(y+j)*240]=image[i+j*width];
        }*/
        DMA[DMA_CHANNEL_3].src = &colorn;
        DMA[DMA_CHANNEL_3].dst = videoBuffer+x+240*(i+y);
        DMA[DMA_CHANNEL_3].cnt = (width) |
                                 DMA_SOURCE_FIXED |
                                 DMA_DESTINATION_INCREMENT |
                                 DMA_ON;
    }
}

struct brick makeBrick(struct brick brick1, int x, int y, u16 color, int visible ){
    brick1.posx = x;
    brick1.posy = y;
    brick1.visible = 1;
    brick1.color = color;
    brick1.visible = visible;
    return brick1;
}

void drawBrick(struct brick brick1){
    int x = brick1.posx;
    int y = brick1.posy;
    u16 color = brick1.visible ? brick1.color : WHITE;
    drawRect(x,y,15,6,color);
}

void drawPlayer(int x, int y){
    drawImage3(y,x,PLAYERBOARD_WIDTH,PLAYERBOARD_HEIGHT,playerBoard);
}

void drawBall(int centX, int centY){
    drawImage3(centY-BALL_HEIGHT/2,centX-BALL_WIDTH/2,BALL_WIDTH,BALL_HEIGHT,ball);
}

void drawLevel(const char* level){
    int x = 8;
    int y = 30;
    int i = 0;
    while(i<42){
        switch (*level){
            case 'r':
                allBrick[i] = makeBrick(allBrick[i],x,y,RED,1);
                drawBrick(allBrick[i]);
                x +=16;
                i++;

                break;
            case 'g':
                allBrick[i] = makeBrick(allBrick[i],x,y,GREEN,1);
                drawBrick(allBrick[i]);
                x +=16;
                i++;

                break;
            case 'b':
                allBrick[i] = makeBrick(allBrick[i],x,y,BLUE,1);
                drawBrick(allBrick[i]);
                x +=16;
                i++;

                break;
            case '%':
                allBrick[i] = makeBrick(allBrick[i],x,y,WHITE,0);
                drawBrick(allBrick[i]);
                x +=16;
                i++;
                break;
            case '\n':
                x = 8;
                y +=7;
                break;

        }
        level++;
    }
}

void reDrawBrick(){
    for(int i=0;i<42;i++){
        drawBrick(allBrick[i]);
    }
}

void waitForVBlank() {
    while (SCANLINECOUNTER > 160);
    while (SCANLINECOUNTER < 160);
}
void drawScore(){

    drawRect(165,0,30,12,BLACK);
    drawChar(2,165,'0'+score/10,WHITE);
    drawChar(2,171,'0'+score%10,WHITE);
}
void setPixel(int r, int c, u16 color)
{
    videoBuffer[OFFSET(r, c, 240)] = color;
}


