#ifndef GAME_HPP
#define GAME_HPP
#include "window.hpp"
#include <cstdlib>
#include <time.h>



class tetris_block
{
public:
    tetris_block(short id, int x, int y, RGB color);
    void drawIt()const;
    coordinate get_vertex()const;
    void set_vertex(int x, int y);
    bool return_state()const{ return fallen; }
    void move_left();
    void move_right();
    void move_down(int move_px_down, int rem_distance);
    void stop(){ fallen=true; }

private:
    short id;       // make it greater to unlock limit
    bool fallen;
    coordinate vertex;
    RGB colorid;

};


const unsigned int BLOCK_COUNT = 4;


class Game_window : public ParentWindow
{
public:
    Game_window(const int width,const int height);

    void set_events(genv::event e_)
    {
        e=e_;
    }

    const int get_state()
    {
        return screen_id;
    }

    int operate();

    void draw_screen()const;

    void generate_block();

    void fall();

    bool check_collision();

    void control();//TODO

    void check_fullrow(); //TODO

    bool check_gameover(); //TODO

    void reset();



private:
    genv::event e;
    std::vector<tetris_block*> bricks;
    int liftdown_speed;
    int highest_pos;
    int numof_blocks;


};




#endif // GAME_HPP
