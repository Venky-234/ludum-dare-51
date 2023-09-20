#pragma once
#include<raylib.h>
#include "game_object.h"
#include<stdio.h>
#include<stdbool.h>
// using only 64x64 textures (VRAM) in gpu
double currentTime;
float one_sec;
int count;
const int screenWidth;
const int screenHeight;
game_object player;
Font countDown;
Sound cds;
Sound last5;
void init_object(
    const char* file_name,
    Vector2 position,
    game_object* game_object_pointer,
    bool hide,
    int col
)
{
    game_object_pointer -> tex = LoadTexture(file_name);
    game_object_pointer -> pos = position;
    game_object_pointer -> hide = hide;
    game_object_pointer -> col = col;
}

// KEYSTROKE ORDER -> UP, DOWN, LEFT, RIGHT
void mov_object(
    game_object* game_object_pointer,
    float speed,
    int keystrokes[4]
)
{
    if(IsKeyDown(keystrokes[0]) && game_object_pointer -> pos.y > 324)
        game_object_pointer -> pos.y -= speed;
    if(IsKeyDown(keystrokes[1]) &&  game_object_pointer -> pos.y < 900-64)
        game_object_pointer -> pos.y += speed;
    if(IsKeyDown(keystrokes[2]) &&  game_object_pointer -> pos.x > 0)
        game_object_pointer -> pos.x -= speed;
    if(IsKeyDown(keystrokes[3]) && game_object_pointer -> pos.x < 900-64)
        game_object_pointer -> pos.x += speed;
}

bool checkCollision(
    game_object* go1,
    game_object* go2
)
{
    Rectangle box1 = {
        go1 -> pos.x,
        go1 -> pos.y,
        64,
        64
    };
    Rectangle box2 = {
        go2 -> pos.x,
        go2 -> pos.y,
        64,
        64
    };
    if(CheckCollisionRecs(box1, box2)){
        return true;
    }
    else{
        return false;
    }
}

bool checkTime(double timeSinceLastCall){
    if((currentTime+11)-GetTime() <= 6.00){
        DrawTextEx(
            countDown,
            TextFormat("%d",(int)((currentTime+11)-GetTime())),
            (Vector2){
                player.pos.x + 15,
                player.pos.y + 5
            },
            60,
            0.5,
            BLACK
        );
    }
    else{
        DrawTextEx(
            countDown,
            TextFormat("%d",(int)((currentTime+11)-GetTime())),
            (Vector2){
                player.pos.x + 15,
                player.pos.y + 5
            },
            40,
            0.1,
            BLACK
        );
    }
    if(GetTime() - one_sec >= 1.00 && (currentTime+11)-GetTime() >= 6.00){
        PlaySound(cds);
        one_sec = GetTime();
    }
    if(GetTime() - one_sec >= 1.00 && (currentTime+11)-GetTime() <= 6.00){
        PlaySound(last5);
        one_sec = GetTime();
    }
    if(GetTime() - currentTime >= timeSinceLastCall){
        currentTime = GetTime();
        return true;
    }
    else{
        return false;
    }
}

void random_coordinates(game_object* gjp, int min, int max){
    gjp -> pos.x = GetRandomValue(200 ,700);
    gjp -> pos.y = GetRandomValue(330,800);
}
bool pressed = false;
void startMenu(){
    while(!pressed && !WindowShouldClose()){
        BeginDrawing();
        DrawTextEx(
            LoadFont("res//fonts//title_font.ttf"),
            "10 SECOND MUSHIES",
            (Vector2){300, 50},
            50,
            0.1,
            (Color){255,255,255,255}
        );    
        DrawText("press enter to start",400, 70, 50,SKYBLUE);
        if(IsKeyDown(KEY_SPACE)){
            pressed = true;
        }
        EndDrawing();
    }
}
void tutorial(){

}