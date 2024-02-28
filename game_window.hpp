#ifndef GAME_HPP
#define GAME_HPP
#include "window.hpp"
#include <cstdlib>
#include <time.h>



class tetris_block
{
public:
    tetris_block(short id, int x, int y);
    void drawIt()const;
    coordinate get_vertex()const;
    bool return_state()const{ return fallen; }

    void move_left();
    void move_right();
    void move_down(int move_px_down, int rem_distance);
    void stop(){ fallen=true; }

private:
    short id;       // make it greater to unlock limit
    bool fallen;
    coordinate vertex;
    char colorid;

};


const int BLOCK_COUNT = 4;


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

    void draw_screen();

    void generate_block();

    bool check_gameover();

    bool falldown();

    void fall();

    void control();

    void reset();

    bool is_Colliding();

    void check_fullrow();




private:
    genv::event e;
    std::vector<tetris_block*> stickies;
    int liftdown_speed;
    int highest_pos;
    int numof_blocks;


};




#endif // GAME_HPP
