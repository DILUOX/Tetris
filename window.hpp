#ifndef WINDOW_HPP
#define WINDOW_HPP
#include "ui.hpp"

static const RGB backgroundColor = {70, 119, 212};  //St. Marie like blue

class ParentWindow{
public:
    ParentWindow(const int width, const int height): width(width), height(height){
        screen_id=0;
        app_state=1;
    }

    int Window_loop(){return 0;}

    void refresh_frame(){
        genv::gout<<genv::move_to(200,0)<<genv::color(backgroundColor.r,backgroundColor.g,backgroundColor.b)<<genv::box(width-400,height);
    }

    void log(std::string * msg){
        std::cout << *msg << std::endl;
    }
protected:
    const unsigned int width;
    const unsigned int height;
    int screen_id;
    int app_state;
};


#endif // WINDOW_HPP
