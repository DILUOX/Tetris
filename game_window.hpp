#ifndef GAME_HPP
#define GAME_HPP
#include "window.hpp"


class Game_window : public ParentWindow{
public:
    Game_window(const int width,const int height):ParentWindow(width, height){
        screen_id=0;
    }


};


#endif // GAME_HPP
