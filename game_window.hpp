#ifndef GAME_HPP
#define GAME_HPP
#include "window.hpp"
#include <cstdlib>
#include <time.h>



class tetris_block
{
public:
    tetris_block(int id, int width): id(id)
    {
        srand(time(0));
        int x = 400;
        //random x direction
        int y = 0;


        coordinate * k = new coordinate(x,y);      //generating first block
        blocks.push_back(k);
        int direction;


        for(int i =0; i<3; i++)                     //generating remaining blocks
        {
            direction = rand() % 3;                 //random direction given: value     meaning
            if(x<200)                                 //                          0    -   left
            {
                //                          1    -   right
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
        this->validate_geometry();

        fallen = false;
        colorid = rand() % 14 + 1;
    }
    void validate_geometry();
    void drawIt();


    coordinate get_left_position();
    coordinate get_right_position();
    coordinate get_bottom();
    coordinate get_top();



    bool return_state(){
        return fallen;
    }

    void move_left();
    void move_right();
    void move_down(int move_px_down, int rem_distance);
    void stop()
    {
        fallen=true;
    }
    std::vector<coordinate*> return_positions()
    {

        /*for(int i = 0; i<4 ;i++){
            std::cout<<"Block no.: "<<id<<std::endl;
            std::cout<<"Returning x: "<<blocks[i]->get_x()<<", y: "<<blocks[i]->get_y()<<std::endl;
        }*/
        return blocks;
    }

private:
    int id;
    bool fallen;
    std::vector<coordinate*> blocks;
    char colorid;

};



class tetris_logic{
public:
    tetris_logic()
    {
        floor = std::vector<coordinate*>();
    }
    ~tetris_logic(){
        floor.erase(floor.begin(),floor.end());
    }
    void add_to_floor(tetris_block *t)
    {
        for(coordinate * c : t->return_positions()){
            floor.push_back(c);
        }

    }

private:
    std::vector<coordinate*> floor;

};





class Game_window : public ParentWindow
{
public:
    Game_window(const int width,const int height):ParentWindow(width, height)
    {
        screen_id = 0;
        std::vector<tetris_block*> stickies = std::vector<tetris_block*>();
        liftdown_speed = 50;
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

    int operate();

    void draw_screen();

    void generate_block();

    bool check_gameover();

    bool falldown();

    void fall();

    void control();



    bool compare_block_pos(tetris_block &a, tetris_block &b);

    bool check_collosion(tetris_block * a, tetris_block * b);

    coordinate* tallest_under_me(tetris_block * me);



private:
    genv::event e;
    std::vector<tetris_block*> stickies;
    int liftdown_speed;


};




#endif // GAME_HPP
