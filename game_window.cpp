#include "game_window.hpp"
#include "exceptions.hpp"


using namespace genv;



void tetris_block::drawIt()
{
    for(coordinate * i:blocks)
    {
        int margin = 1;
        gout<<move_to(i->get_x(),i->get_y())<<color(0,0,0)<<box(BLOCK_SIZE,BLOCK_SIZE)<<move_to(i->get_x()+ margin,i->get_y() +margin)
            <<color(colorid*10,colorid*(-10),colorid*20)<<box(BLOCK_SIZE-margin*2,BLOCK_SIZE-margin*2);
    }
}

coordinate tetris_block::get_bottom()
{
    coordinate lowest_pos = coordinate();
    for(coordinate * coord: blocks)
    {
        if(coord->get_y()>lowest_pos.get_y())
        {
            lowest_pos = *coord;
        }
    }
    return lowest_pos;
}

coordinate tetris_block::get_left_position()
{
    coordinate minpos = coordinate(RIGHT_SIDE - BLOCK_SIZE,0);
    for(coordinate * coord : blocks)
    {
        if(minpos.get_x() > coord->get_x())
        {
            minpos=*coord;
        }
    }
    return minpos;
}

coordinate tetris_block::get_right_position()      //returns coords of the most right block
{
    coordinate maxpos = coordinate(LEFT_SIDE,0);
    for(coordinate * coord : blocks)
    {
        if(maxpos.get_x()<coord->get_x())
        {
            maxpos=*coord;
        }
    }
    return maxpos;
}

coordinate tetris_block::get_top(){
    coordinate minpos = coordinate(0,BOTTOM);

    for(coordinate * coord : blocks){
        if(minpos.get_y() > coord->get_y()){
            minpos = *coord;
        }
    }
    return minpos;
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

void tetris_block::move_down(int downcount,int rem_distance)
{

    int move_px_down = downcount * BLOCK_SIZE;


     if(!fallen && move_px_down + get_bottom().get_y() < BOTTOM)
        {
            for(coordinate * c : blocks)
            {
                c->set_y(
                    c->get_y() +( BLOCK_SIZE  * downcount)
                );
            }

        }

    if( (this->get_bottom().get_y() + move_px_down) < (this->get_top().get_y() - rem_distance)
      )
    {

    }
}

int calculate_y_diff(tetris_block * a, tetris_block * b){


    return 0;
}


int Game_window::remaining_distance(tetris_block * brick_under_me){
    tetris_block rookie_block = *stickies[stickies.size()-1];

    if(brick_under_me->get_left_position().get_x() <= rookie_block.get_left_position().get_x() &&
       brick_under_me->get_right_position().get_x() >= rookie_block.get_right_position().get_x()
       )
       {
            calculate_y_diff(&rookie_block, brick_under_me);

       }
    return 0;

}



bool Game_window::falldown()
{
    tetris_block * last = stickies[stickies.size()-1];
    if(last->get_bottom().get_y()<BOTTOM-BLOCK_SIZE && !last->return_state())
    {
        {
            last->move_down(1,remaining_distance());
        }
    }
    else
    {
        last->stop();
    }
    return last->return_state();

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
    tetris_block * newblock = new tetris_block(stickies.size(),RIGHT_SIDE);
    stickies.push_back(newblock);
}


void Game_window::fall()
{
    if(e.type==ev_timer)
    {
        if(falldown())
        {
            generate_block();
        }
        gout<<refresh;
    }


}



void Game_window::control()
{
    std::cout << e.keyname << " - down arrow"<<std::endl;

    tetris_block * last_brick = stickies[stickies.size()-1];
    if(last_brick->return_state())
    {
        return;
    }

    if(e.keyname=="Left" && e.keycode>0 && last_brick->get_left_position().get_x()>LEFT_SIDE)
    {
        last_brick->move_left();
    }
    if(e.keyname=="Right" && e.keycode>0 && last_brick->get_right_position().get_y()<RIGHT_SIDE-BLOCK_SIZE)
    {
        last_brick->move_right();
    }


    if(e.keyname=="Down" && e.keycode > 0 &&
            last_brick->get_bottom().get_y() < BOTTOM &&                    //checks if current position is in the air
            last_brick->get_bottom().get_y() + liftdown_speed*BLOCK_SIZE    //checking remaining way to fall
      )
    {
        for(std::size_t i = 0; i < stickies.size()-1; i++)
        {
            last_brick->move_down(liftdown_speed,BOTTOM - last_brick->get_bottom().get_y());
        }

    }

}


//checking two tetris figures if they are next to each other
//tetris_block * a, tetris_block * b is compared
//Use to detect if a tetris object has fallen on another



bool Game_window::compare_block_pos(tetris_block &a, tetris_block &b)
{
    return false;
}



bool Game_window::check_collosion(tetris_block * a, tetris_block * b)
{

    std::vector<coordinate*> a_block = a->return_positions();
    std::vector<coordinate*> b_block = b->return_positions();

    //Checking collision

    for(int i = 0; i<4; i++)
    {
        for(int j = i+1; j<4; j++)
        {
            if( (a_block[i]->get_x() == b_block[j]->get_x()) &&
                    (a_block[i]->get_y() == b_block[j]->get_y()+BLOCK_SIZE))
            {
                std::cout<<"Collision detected, stopping selected brick"<<std::endl;
                b->stop();
                return true;
            }
        }
    }

    return false;
}


bool Game_window::check_gameover()
{
    if(stickies.size()>1)
    {
        if(check_collosion(stickies[stickies.size()-1], stickies[stickies.size()-2]))
        {
            screen_id = -1;
            return true;
        }
    }

    return false;
}

int Game_window::operate()
{
    draw_screen();
    control();
    std::size_t max_vecsize = stickies.size();
    if(check_gameover()==true)
    {
        return 0;
    }
    for(std::size_t i = 0; i<max_vecsize; i++)            //stickies vector contains the tetris blocks
    {
        for(std::size_t j = i+1; j<max_vecsize; j++)
        {
            check_collosion(stickies[i], stickies[j]);
        }

    }
    fall();
    return 1;

}













