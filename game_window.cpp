#include "game_window.hpp"

using namespace genv;



void tetris_block::drawIt(){
    for(coordinate * i:blocks){
        gout<<move_to(i->get_x(),i->get_y())<<color(0,0,0)<<box(50,50)<<move_to(i->get_x()+ 1,i->get_y() +1)<<color(colorid*10,colorid*(-10),colorid*20)<<box(48,48);
    }
}

void tetris_block::falldown(){
    for(coordinate * c : blocks){
        c->set_y(c->get_y()+50);
    }
}


void Game_window::draw_screen(){
    for(tetris_block * brick : stickies){
        brick->drawIt();
    }

}


void Game_window::fall(){
    if(e.type==ev_timer){
        for(tetris_block * brick : stickies){
            brick->falldown();
        }
        gout<<refresh;
    }

}

void Game_window::operate(){
    draw_screen();
    fall();
}


