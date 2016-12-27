//
// Created by yunbo on 4/6/16.
//

#include "myLib.h"
int detectCollision(struct _ball ball1, int ballSpeedX, int ballSpeedY){
    int newx = ball1.centerX+ballSpeedX;
    int newy = ball1.centerY-ballSpeedY;
    struct brick *ptr = allBrick;
    int result = 0;
    for(unsigned int i=0;i< sizeof(allBrick)/ sizeof(allBrick[0]);i++){
        if(ptr->visible){
            if (inRect(ball1.centerX, newy, *ptr)) {
                ptr->visible = 0;
                score++;
                drawScore();

                return 1;
            } else if (inRect(newx, ball1.centerY, *ptr)) {
                ptr->visible = 0;
                score++;
                drawScore();

                return 2;
            }
        }
        ptr++;
    }
    if(inPlayer(ball1.centerX,newy,player1)){
        ptr->visible = 0;
        return 1;
    }else if(inPlayer(newx,ball1.centerY,player1)){
        ptr->visible = 0;
        return 2;
    }

    return result;
}

int inRect(int x, int y, struct brick brick1){
    return x>=brick1.posx && x-15<=brick1.posx && y>=brick1.posy&&y<=brick1.posy+6;
}
int inPlayer(int x,int y, struct player player1){
    return x>=player1.x && x-17<=player1.x && y>=player1.y&&y<=player1.y+5;
}
