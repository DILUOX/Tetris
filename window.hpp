#ifndef WINDOW_HPP
#define WINDOW_HPP
#include "graphics.hpp"

class ParentWindow{
public:
    ParentWindow(const int width, const int height): width(width), height(height){
        screen_id=0;
    }

    int Window_loop(){return 0;}

    void refresh_frame(){
        genv::gout<<genv::move_to(0,0)<<genv::color(0,0,0)<<genv::box(width,height);
    }
protected:
    const unsigned int width;
    const unsigned int height;
    int screen_id;
};


#endif // WINDOW_HPP
