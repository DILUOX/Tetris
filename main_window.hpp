#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP
#include "window.hpp"
#include "ui.hpp"



class MainWindow : public ParentWindow{
public:
    MainWindow(const unsigned int width, const unsigned int height, bool fullscreen_): ParentWindow(width,height){
        genv::gout.open(width,height,fullscreen_);
        genv::gout<<genv::refresh;
        ui = Interface();
        screen_id = 0;
    }

    int Window_loop();

    void refresh_frame(){
        genv::gout<<genv::move_to(0,0)<<genv::color(0,0,0)<<genv::box(width,height);
    }
private:

    genv::event ev;

    Interface ui;
};





#endif // MAIN_WINDOW_HPP
