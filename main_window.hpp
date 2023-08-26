#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP
#include "window.hpp"
#include "game_window.hpp"
#include "pic.h"
#include "ui.hpp"



class MainWindow : public ParentWindow{
public:
    MainWindow(const unsigned int width, const unsigned int height, bool fullscreen_): ParentWindow(width,height), tetris(Game_window(width,height)){
        genv::gout.open(width,height,fullscreen_);
        genv::gin.timer(400);
        ui = Interface();
        screen_id = 0;
        char filename[] = {'b','r','i','c','k','.','k','e','p'};
        texture sidewalls(filename);
        for(unsigned int i = 0; i<2;i++){
            for(unsigned int j = 0; j <height/200; j++){
                sidewalls.draw(i*600,j*200);
            }
        }

        genv::gout<<genv::refresh;

    }

    int Window_loop();

private:
    genv::event ev;
    Interface ui;
    Game_window tetris;
    //texture sidewalls;
};





#endif // MAIN_WINDOW_HPP
