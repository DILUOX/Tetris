#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP
#include "window.hpp"
#include "game_window.hpp"
#include "pic.h"
#include "ui.hpp"



class MainWindow : public ParentWindow{
public:
    MainWindow(const unsigned int width, const unsigned int height, bool fullscreen_): ParentWindow(width,height), tetris(Game_window(width,height))
    {
        genv::gout.open(width,height,fullscreen_);
        genv::gin.timer(300);
        ui = Interface();
        screen_id = 0;

        std::string background_path("brick.kep");
        std::string gameover_path("gameover.kep");

        background = new texture(background_path);
        gameover = new texture(gameover_path);
        draw_background();

    }
    int Window_loop();

private:
    genv::event ev;
    Interface ui;
    Game_window tetris;
    texture * background;
    texture * gameover;

    void draw_background();

};





#endif // MAIN_WINDOW_HPP
