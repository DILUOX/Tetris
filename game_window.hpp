#ifndef GAME_HPP
#define GAME_HPP
#include "window.hpp"
#include "ui.hpp"
#include <cstdlib>
#include <time.h>

 class tetris_block
    {
    public:
        tetris_block(int id, int width): id(id)
        {
            srand(time(0));
            int x = (rand() % 14)*50 + 50;
            int y = 0;
            for(int i =0; i<4; i++)
            {
                int direction = rand() % 3;
                if(x<0)
                {
                    x=0;
                }
                if(width<x)
                {
                    x=width-50;
                }
                if(direction==0)
                {
                    coordinate * k = new coordinate(x-50,y);
                    x-=50;
                    blocks.push_back(k);
                }
                else if(direction==1)
                {
                    coordinate * k = new coordinate(x+50,y);
                    x+=50;
                    blocks.push_back(k);
                }
                else if(direction==2)
                {
                    coordinate * k = new coordinate(x,y+50);
                    y+=50;
                    blocks.push_back(k);
                }


            }
            colorid = rand() % 14 + 1;
        }

        void drawIt();
        void falldown();
    private:
        int id;
        std::vector<coordinate*> blocks;
        char colorid;

};



class Game_window : public ParentWindow
{
public:
    Game_window(const int width,const int height):ParentWindow(width, height)
    {
        screen_id=0;
        stickies.push_back(new tetris_block(1,width));
    }
    void set_events(genv::event e_)
    {
        e=e_;
    }
    const int get_state()
    {
        return screen_id;
    }
    void operate();
    void draw_screen();

    void fall();




private:
    genv::event e;
    std::vector<tetris_block*> stickies;
};




#endif // GAME_HPP
