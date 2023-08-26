#ifndef WINDOW_HPP
#define WINDOW_HPP
#include "graphics.hpp"
#include "ui.hpp"

struct Color{
    Color(int r, int g, int b);
    void setcolor(){
        genv::gout<<genv::color(r,g,b);
    }
    int r,g,b;
};





class ParentWindow{
public:
    ParentWindow(const int width, const int height): width(width), height(height){
        screen_id=0;
    }

    int Window_loop(){return 0;}

    void refresh_frame(){
        genv::gout<<genv::move_to(200,0)<<genv::color(0,0,0)<<genv::box(width-400,height);
    }

    void log(std::string * msg){
        std::cout << *msg << std::endl;
    }
protected:
    const unsigned int width;
    const unsigned int height;
    int screen_id;
};


#endif // WINDOW_HPP
