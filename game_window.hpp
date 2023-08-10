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
        int x = (rand() % 7)*50 + 200; //random x direction
        int y = 0;


        coordinate * k = new coordinate(x,y);      //generating first block
        blocks.push_back(k);
        int direction;


        for(int i =0; i<3; i++)                     //generating remaining blocks
        {
            direction = rand() % 3;                 //random direction given: value     meaning
            if(x<200)                                 //                          0    -   left
            {                                       //                          1    -   right
                x=200;                                //                          2    -   down
            }
            if(width<x)                             //the next block will be generated according to the direction
            {
                x=width-50;
            }
            if(direction==0)
            {
                k = new coordinate(x-50,y);
                x-=50;
                blocks.push_back(k);
            }
            else if(direction==1)
            {
                k = new coordinate(x+50,y);
                x+=50;
                blocks.push_back(k);
            }
            else if(direction==2)
            {
                k = new coordinate(x,y+50);
                y+=50;
                blocks.push_back(k);
            }
            k = nullptr;

        }
        fallen = false;
        colorid = rand() % 14 + 1;
    }

    void drawIt();
    bool falldown();

    int get_left_position();
    int get_right_position();
    int get_bottom();

    void move_left();
    void move_right();
    void stop(){
        fallen=true;
    }
    coordinate* return_positions(){
        coordinate * positions[4];
        int tmp=0;
        for(coordinate * c : blocks){
            positions[tmp]->set_x(c->get_x());
            positions[tmp]->set_y(c->get_y());
            tmp++;
        }
        return *positions;
    }

private:
    int id;
    bool fallen;
    std::vector<coordinate*> blocks;
    char colorid;

};



class Game_window : public ParentWindow
{
public:
    Game_window(const int width,const int height):ParentWindow(width, height)
    {
        screen_id=0;
        generate_block();
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
    void generate_block();

    void fall();

    void control();

    void check_collosion(tetris_block * a, tetris_block * b);


private:
    genv::event e;
    std::vector<tetris_block*> stickies;
};




#endif // GAME_HPP
