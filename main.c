#pragma once
#include "raylib.h"
#include<stdio.h>
#include<stdbool.h>
#include "game_object.h"
#include "game_functions.h"

double currentTime = 0.00;
float one_sec;
int score = 0;
int color;
const int screenWidth = 900;
const int screenHeight = 900;
bool start = true;
game_object player, background;
Font countDown;
Sound cds;
Sound last5;
bool running;
int main()
{   
    game_object collect[15];
     
    InitWindow(screenWidth,screenHeight, "Collect in 10");
    InitAudioDevice();

    init_object("res//textures//yellow_man.png",(Vector2){30, 800},&player,false,color);
    init_object("res//textures//background.png", (Vector2){0,0}, &background,false,color);

    countDown =  LoadFont("res//fonts//ARCADECLASSIC.TTF");
    Font title =  LoadFont("res//fonts//title_font.ttf");
    Font score_font = LoadFont("res//fonts//ARCADE.TTF");
    Sound death = LoadSound("res//sounds//loose.wav");
    Texture2D transition = LoadTexture("res//textures//transition.png");
    Texture2D start_background = LoadTexture("res//textures//start_background.png");
    Texture2D tutorial_background = LoadTexture("res//textures//tutorial_background.png");
    Texture2D death_screen = LoadTexture("res//textures//death_screen.png");
    //Shader bloom = LoadShader(0,TextFormat("res//shaders//bloom.fs", 330));
    cds = LoadSound("res//sounds//countDown.wav");
    last5 = LoadSound("res//sounds//last5.wav");

    SetTargetFPS(100);
    SetWindowIcon(LoadImage("res//textures//red_collect.png"));
    game_loop:
    score = 0;
    player.pos = (Vector2){30, 800};
    for(int i = 0; i < sizeof(collect)/sizeof(game_object);i++){
        color = GetRandomValue(0,3);
        UnloadTexture(collect[i].tex);
        if(color == 0){
            init_object("res//textures//red_collect.png",(Vector2){0,0},&collect[i], false,color);
        }
        if(color == 1){
            init_object("res//textures//green_collect.png",(Vector2){0,0},&collect[i], false,color);
        }
        if(color == 2){
            init_object("res//textures//blue_collect.png",(Vector2){0,0},&collect[i], false,color);
        }
        if(color == 3){
            init_object("res//textures//yellow_collect.png",(Vector2){0,0},&collect[i], false,color);
        }
        
        random_coordinates(&collect[i], 300, 700);

    }
    
    color = GetRandomValue(0,3);

    if(color == 0){
        UnloadTexture(player.tex);
        player.tex = LoadTexture("res//textures//red_man.png");
    } 
    if(color == 1){
        UnloadTexture(player.tex);
        player.tex = LoadTexture("res//textures//green_man.png");

    }   
    if(color == 2){
        UnloadTexture(player.tex);
        player.tex = LoadTexture("res//textures//blue_man.png");

    }          
    if(color == 3){
        UnloadTexture(player.tex);
        player.tex = LoadTexture("res//textures//yellow_man.png");

    }   
    //color = GetRandomValue(0,3); //both included
    bool pressed = false;
    running = true;
    while(!pressed)
    {
        BeginDrawing();
        DrawTexture(start_background,0,0,(Color){255,255,255,255});
        /*
        DrawTextEx(
        title,
        "SECOND MUSHIES",
        (Vector2){300, 50},
        70,
        0.1,
        (Color){255,255,255,255}
        );
        */    
        if(IsKeyPressed(KEY_SPACE)){
            pressed = true;
        }   
        ClearBackground(BLACK); 
        EndDrawing();
        if(WindowShouldClose()){
            exit();
        }
    }
    
    pressed = false;
    while (!pressed)
    {
        BeginDrawing();
        DrawTexture(tutorial_background,0,0,(Color){255,255,255,255});
        ClearBackground(BLACK);
        EndDrawing();
        if(IsKeyPressed(KEY_SPACE)){
            pressed = true;
        }  
        if(WindowShouldClose()){
            exit();
        }
    }
    currentTime = GetTime();
    one_sec = GetTime();
    //BeginShaderMode(bloom);
    while(running){
        
        BeginDrawing();
        
            mov_object(&player, 500*GetFrameTime(),(int[4]){KEY_W,KEY_S,KEY_A,KEY_D});

        DrawTexture(background.tex,background.pos.x,background.pos.y,(Color){255,255,255,255});
        DrawTexture(player.tex,player.pos.x,player.pos.y,(Color){255,255,255,255});
        if(WindowShouldClose()){
            exit();
        }

        if(checkTime(10.00)){
            color = GetRandomValue(0,3);
            player.pos = (Vector2){30, 800};
            
            for(int i = 0; i < sizeof(collect)/sizeof(game_object);i++){
                    color = GetRandomValue(0,3);
                    UnloadTexture(collect[i].tex);
                    if(color == 0){
                        init_object("res//textures//red_collect.png",(Vector2){0,0},&collect[i], false,color);
                    }
                    if(color == 1){
                        init_object("res//textures//green_collect.png",(Vector2){0,0},&collect[i], false,color);
                    }
                    if(color == 2){
                        init_object("res//textures//blue_collect.png",(Vector2){0,0},&collect[i], false,color);
                    }
                    if(color == 3){
                        init_object("res//textures//yellow_collect.png",(Vector2){0,0},&collect[i], false,color);
                    }
        
                    random_coordinates(&collect[i],100, 700); 
            }
            color = GetRandomValue(0,3); 
            if(color == 0){
                UnloadTexture(player.tex);
                player.tex = LoadTexture("res//textures//red_man.png");
            } 
            if(color == 1){
                UnloadTexture(player.tex);
                player.tex = LoadTexture("res//textures//green_man.png");

            }   
            if(color == 2){
                UnloadTexture(player.tex);
                player.tex = LoadTexture("res//textures//blue_man.png");

            }          
            if(color == 3){
                UnloadTexture(player.tex);
                player.tex = LoadTexture("res//textures//yellow_man.png");

            }   

        }
        
        if(color == 0){
            //DrawText("RED",0,400,40,RED);
            DrawTextEx(
            countDown,
            "Red",
            (Vector2){10, 125},
            100,
            0.1,
            //(Color){255,255,255,255}
            RED
            ); 
        }
        if(color == 1){
            //DrawText("GREEN",0,400,40,GREEN);
            DrawTextEx(
            countDown,
            "Green",
            (Vector2){10, 125},
            100,
            0.1,
            //(Color){255,255,255,255}
            GREEN
            );
        }
        if(color == 2){
            //DrawText("BLUE",0,400,40,BLUE);
            DrawTextEx(
            countDown,
            "Blue",
            (Vector2){10, 125},
            100,
            0.1,
            //(Color){255,255,255,255}
            BLUE
            );
        }
        if(color == 3){
            //DrawText("YELLOW",0,400,40,YELLOW);
            DrawTextEx(
            countDown,
            "Yellow",
            (Vector2){10, 125},
            100,
            0.1,
            YELLOW
            //(Color){255,255,255,255}
            );
        }
        DrawTexture(collect[0].tex,collect[0].pos.x,collect[0].pos.y,(Color){255,255,255,255});
        //DrawText(TextFormat("SCORE : %d", score),0, 101, 40, GREEN);
        
        DrawTextEx(
            score_font,
            TextFormat("SCORE : %d", score),
            (Vector2){6, 296},
            40,
            0.5,
            (Color){0,0,0,255}
            ); 
        
        //DrawFPS(0, 75);
        
        for(int i = 0; i < sizeof(collect)/sizeof(game_object);i++){
            if(collect[i].hide == false)
                DrawTexture(collect[i].tex,collect[i].pos.x,collect[i].pos.y,(Color){255,255,255,255});
            
            if(checkCollision(&player, &collect[i])){
                if(color == collect[i].col){
                    score += 1;
                    printf("collided with proper color\n");
                    collect[i].hide = true;
                    collect[i].pos = (Vector2){-100, 100};
                 }
                 else{
                    // break out of loop
                    running = false;
                
                 }
            }
        }

        ClearBackground(BLACK);
        EndDrawing();
     }
     //EndShaderMode();
        
    Font font = LoadFont("res//fonts//death_screen.TTF");
    SetTargetFPS(100);
    PlaySound(death);
    while(!WindowShouldClose()){
        BeginDrawing();
        DrawTexture(death_screen,0,0,(Color){255,255,255,255});
        DrawTextEx(
            score_font,
            TextFormat("SCORE : %d", score),
            (Vector2){332, 547},
            50,
            0.1,
            MAGENTA
        );
        /*
        DrawTextEx(
            font,
            "You lost",
            (Vector2){300, 50},
            40,
            0.1,
            (Color){255,255,255,255}
            ); 
        DrawTextEx(
            font,
            "Press R to restart",
            (Vector2){300, 90},
            40,
            0.1,
            (Color){255,255,255,255}
            );    
            */ 
        if(IsKeyDown(KEY_R)){
            goto game_loop; 
            
        }
        ClearBackground(BLACK);
        EndDrawing();
    }
        return 0;

    

}

