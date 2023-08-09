#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP
#include "window.hpp"
#include "game_window.hpp"

#include "ui.hpp"



class MainWindow : public ParentWindow{
public:
    MainWindow(const unsigned int width, const unsigned int height, bool fullscreen_): ParentWindow(width,height), tetris(Game_window(width,height)){
        genv::gout.open(width,height,fullscreen_);
        genv::gout<<genv::refresh;
        ui = Interface();
        screen_id = 0;
        genv::gin.timer(600);
    }

    int Window_loop();

private:

    genv::event ev;
    Interface ui;
    Game_window tetris;

};





#endif // MAIN_WINDOW_HPP
