//
// Created by yunbo on 4/4/16.
//
#include "myLib.h"
#include "BrickBreakerStart.h"
#include "gameoverScene.h"
#include "playerBoard.h"
#include "ball.h"
int main() {
    REG_DISPCTL = MODE3 | BG2_ENABLE;
while(1){
    score = 0;
    player1.x = 111;
    player1.y = 140;
    ball1.centerX = 120;
    ball1.centerY = 136;
    int px = 111;
    int playerSpeed = 3;
    int ballSpeedX = 1;
    int ballSpeedY = 2;
    int launched=0;
    drawImage3(0, 0, BRICKBREAKERSTART_WIDTH, BRICKBREAKERSTART_HEIGHT, BrickBreakerStart);
    while (KEY_DOWN_NOW(BUTTON_SELECT));
    while (1) {
        if (KEY_DOWN_NOW(BUTTON_START)) {
            drawRect(0, 0, 240, 160, WHITE);
            drawRect(0,0,240,12,BLACK);
            drawString(2,2,"Brick Breaker",WHITE);
            drawString(2,130,"SCORE:",WHITE);
            waitForVBlank();
            drawLevel(level1);
            drawPlayer(px, 140);
            drawBall(ball1.centerX, ball1.centerY);
            launched = 0;
            drawScore();
            waitForVBlank();
            break;
        }
    }
    while (1) {
        if (KEY_DOWN_NOW(BUTTON_SELECT)) {
            break;
        }
        while (KEY_DOWN_NOW(BUTTON_SELECT));

        if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
            //while(KEY_DOWN_NOW(BUTTON_RIGHT)){}
            drawRect(px, 140, PLAYERBOARD_WIDTH, PLAYERBOARD_HEIGHT, WHITE);
            if (px + PLAYERBOARD_WIDTH + playerSpeed < 240) {
                px += playerSpeed;
            }
            player1.x = px;
            drawPlayer(px, 140);
            if (!launched) {
                drawRect(ball1.centerX - 4, ball1.centerY - 4, BALL_WIDTH, BALL_HEIGHT, WHITE);
                ball1.centerX = px + 9;
                drawBall(ball1.centerX, ball1.centerY);
            }
        } else if (KEY_DOWN_NOW(BUTTON_LEFT)) {
            //while(KEY_DOWN_NOW(BUTTON_LEFT)){}
            drawRect(px, 140, PLAYERBOARD_WIDTH, PLAYERBOARD_HEIGHT, WHITE);
            if (px - playerSpeed >= 0) {
                px -= playerSpeed;
            }
            player1.x = px;
            drawPlayer(px, 140);
            if (!launched) {
                drawRect(ball1.centerX - 4, ball1.centerY - 4, BALL_WIDTH, BALL_HEIGHT, WHITE);
                ball1.centerX = px + 9;
                drawBall(ball1.centerX, ball1.centerY);
            }
        }
        if (KEY_DOWN_NOW(BUTTON_A)) {
            while (KEY_DOWN_NOW(BUTTON_A)) { }
            launched = 1;
        }
        if (launched) {
            drawRect(ball1.centerX - 4, ball1.centerY - 4, BALL_WIDTH, BALL_HEIGHT, WHITE);
            ball1.centerX += ballSpeedX;
            ball1.centerY -= ballSpeedY;
            reDrawBrick();
            drawPlayer(px, 140);
            drawBall(ball1.centerX, ball1.centerY);
            if (ball1.centerY - ballSpeedY <= 15) {
                ballSpeedY = -ballSpeedY;
            } else if (ball1.centerX + ballSpeedX >= 237) {
                ballSpeedX = -ballSpeedX;
            } else if (ball1.centerX + ballSpeedX <= 3) {
                ballSpeedX = -ballSpeedX;
            } else if (ball1.centerY - ballSpeedY >= 158) {
                drawImage3(0, 0, GAMEOVERSCENE_WIDTH, GAMEOVERSCENE_HEIGHT, gameoverScene);
                drawString(2,2,"Final Score:",YELLOW);
                drawChar(2,80,'0'+score/10,YELLOW);
                drawChar(2,86,'0'+score%10,YELLOW);
                break;
            }
            if (detectCollision(ball1, ballSpeedX, ballSpeedY) == 1) {
                ballSpeedY = -ballSpeedY;
            } else if (detectCollision(ball1, ballSpeedX, ballSpeedY) == 2) {
                ballSpeedX = -ballSpeedX;
            }
            int cnt = 0;
            for(unsigned int i=0;i< sizeof(allBrick)/ sizeof(allBrick[0]);i++){
                if(!allBrick[i].visible){
                    cnt++;
                }
            }
            if(cnt == sizeof(allBrick)/ sizeof(allBrick[0])){
                drawImage3(0, 0, GAMEOVERSCENE_WIDTH, GAMEOVERSCENE_HEIGHT, gameoverScene);
                drawString(2,2,"Final Score:",YELLOW);
                drawChar(2,80,'0'+score/10,YELLOW);
                drawChar(2,85,'0'+score%10,YELLOW);
                break;
            }

        }
        waitForVBlank();
    }
    while (!KEY_DOWN_NOW(BUTTON_SELECT)) {
    }
}
    return 0;
}
