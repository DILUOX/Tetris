#include "game_window.hpp"

using namespace genv;

const int LEFT_SIDE = 200;
const int RIGHT_SIDE = 600;
const int BOTTOM = 800;
const int BLOCK_SIZE = 50;

void tetris_block::drawIt()
{
    for(coordinate * i:blocks)
    {
        int margin = 1;
        gout<<move_to(i->get_x(),i->get_y())<<color(0,0,0)<<box(BLOCK_SIZE,BLOCK_SIZE)<<move_to(i->get_x()+ margin,i->get_y() +margin)
            <<color(colorid*10,colorid*(-10),colorid*20)<<box(BLOCK_SIZE-margin*2,BLOCK_SIZE-margin*2);
    }
}

int tetris_block::get_bottom()
{
    int lowest_pos =0;
    for(coordinate * c: blocks)
    {
        if(c->get_y()>lowest_pos)
        {
            lowest_pos = c->get_y();
        }
    }
    return lowest_pos;
}

int tetris_block::get_left_position()
{
    int minpos = RIGHT_SIDE - BLOCK_SIZE;
    for(coordinate * c : blocks)
    {
        if(minpos>c->get_x())
        {
            minpos=c->get_x();
        }
    }
    return minpos;
}

int tetris_block::get_right_position()
{
    int maxpos = LEFT_SIDE;
    for(coordinate * c : blocks)
    {
        if(maxpos<c->get_x())
        {
            maxpos=c->get_x();
        }
    }
    return maxpos;
}

void tetris_block::move_left()
{
    if(!fallen)
    {
        for(coordinate * c : blocks)
        {
            c->set_x(c->get_x()-BLOCK_SIZE);
        }
    }

}

void tetris_block::move_right()
{
    if(!fallen)
    {
        for(coordinate * c : blocks)
        {
            c->set_x(c->get_x()+BLOCK_SIZE);
        }
    }

}



bool tetris_block::falldown()
{
    if(get_bottom()<BOTTOM-BLOCK_SIZE)
    {
        for(coordinate * c : blocks)
        {
            c->set_y(c->get_y()+BLOCK_SIZE);
        }
    }
    else
    {
        fallen = true;
    }
    return fallen;

}



void Game_window::draw_screen()
{
    for(tetris_block * brick : stickies)
    {
        brick->drawIt();
    }

}


void Game_window::generate_block()
{
    stickies.push_back(new tetris_block(1,RIGHT_SIDE));
}


void Game_window::fall()
{
    if(e.type==ev_timer)
    {
        if(stickies[stickies.size()-1]->falldown())
        {
            generate_block();
        }
        gout<<refresh;
    }


}

void Game_window::check_collosion(tetris_block * a, tetris_block * b)
{
    coordinate * a_block = a->return_positions();
    coordinate * b_block = b->return_positions();
    for(int i = 0; i<3; i++)
    {
        for(int j = i; j<3; j++)
        {
            if(a_block[i].get_x()==b_block->get_x() && a_block[i].get_y()==b_block[i].get_y()-BLOCK_SIZE)
            {
                a->stop();
                break;
            }
        }
    }
}

void Game_window::control()
{
    tetris_block * last_brick = stickies[stickies.size()-1];
    if(e.keyname=="Left" && e.keycode>0 && last_brick->get_left_position()>LEFT_SIDE)
    {
        last_brick->move_left();
    }
    if(e.keyname=="Right" && e.keycode>0 && last_brick->get_right_position()<RIGHT_SIDE-BLOCK_SIZE)
    {
        last_brick->move_right();
    }
}

void Game_window::operate()
{
    draw_screen();
    control();
    for(std::size_t i = 0; i<stickies.size()-1; i++){           //stickies vector contains the tetris blocks
        for(std::size_t j = i; j<stickies.size()-1; j++){
           // check_collosion(stickies[i],stickies[j]);
        }

    }

    fall();
}











