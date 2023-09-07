#include "game_window.hpp"
#include "exceptions.hpp"


using namespace genv;


void tetris_block::validate_geometry()
{
    for(std::size_t i = 1; i < 4 ; i++){
        coordinate * c1 = blocks[i];
        coordinate * c2 = blocks[i-1];
        if(c1->get_x()==c2->get_x() && c1->get_y() == c2->get_y()){
            int dir = rand()% 2 - 1;
            c2->set_x(c2->get_x() + dir*50);
            c2->set_y(c2->get_y() + dir*50);
        }
    }

}




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

coordinate tetris_block::get_top()
{
    coordinate minpos = coordinate(0,BOTTOM);

    for(coordinate * coord : blocks)
    {
        if(minpos.get_y() > coord->get_y())
        {
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

void tetris_block::move_down(int move_px_down,int rem_distance)
{
    if(!fallen)
    {
        if( move_px_down < rem_distance ){
            for(coordinate * c : blocks)
            {
                c->set_y(
                    c->get_y() +( move_px_down)
                );
            }
        }
        else if(move_px_down == rem_distance){
            for(coordinate * c : blocks)
            {
                c->set_y(
                    c->get_y() +( move_px_down)
                );
            }
            //stop();
        }


    }

}



void Game_window::draw_screen()
{
    if(app_state !=-1){
        for(tetris_block * brick : stickies)
        {
            brick->drawIt();
        }
    }


}


void Game_window::generate_block()
{
    tetris_block * newblock = new tetris_block(stickies.size(),RIGHT_SIDE);
    stickies.push_back(newblock);
}




bool Game_window::falldown()
{
    tetris_block * last = stickies[stickies.size()-1];
    if(last->get_bottom().get_y()<BOTTOM-BLOCK_SIZE && !last->return_state())
    {
        {
            last->move_down(liftdown_speed,BOTTOM-last->get_bottom().get_y());
        }
    }
    else
    {
        last->stop();
    }
    return last->return_state();

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


std::vector<coordinate*> is_parallel(std::vector<coordinate*> a, std::vector<coordinate*> b)     //returns the parallel  blocks
{
    std::vector<coordinate*> par_blocks_count;
    for(std::size_t i = 0; i < a.size(); i++)
    {
        for(std::size_t j = 0; j < b.size(); j++)
        {
            if(a[i]->get_x() == b[j]->get_x())
            {
                par_blocks_count.push_back(b[j]);
            }
        }
    }
    return par_blocks_count;
}


coordinate* Game_window::tallest_under_me(tetris_block * me)          //returns the coordinates of the highest block under the given block
{
    if(stickies.size()<2){
        return nullptr;
    }

    std::vector<coordinate*> blocks_under;

    for(std::size_t i = 0; i < stickies.size(); i++)        //selecting only the parallel blocks
    {
        if(stickies[i] != me)
        {
            std::vector<coordinate*> par_blocks = is_parallel(me->return_positions(), stickies[i]->return_positions());

            for(coordinate * c : par_blocks)
            {
                blocks_under.push_back(c);

            }
        }



    }

    int highest_y = 8001;
    std::size_t id = 0;
    for(std::size_t i = 0; i < blocks_under.size(); i++)    //choosing the lowest y coordinate from parallel blocks
    {
        if(blocks_under[i]->get_y() < highest_y)
        {
            highest_y = blocks_under[i]->get_y();
            id = i;
        }
    }
    if(highest_y == 8001)
    {

        return nullptr;
    }

    return blocks_under[id];

}




void Game_window::control()
{
    std::cout << e.keyname << " - arrow was pressed!"<<std::endl;

    tetris_block * last_brick = stickies[stickies.size()-1];

    if(last_brick->return_state())
    {
        return;
    }

    if(e.keyname=="Left" && e.keycode>0 && last_brick->get_left_position().get_x()>LEFT_SIDE)
    {
        last_brick->move_left();
    }
    if(e.keyname=="Right" && e.keycode>0 && last_brick->get_right_position().get_x()<RIGHT_SIDE-BLOCK_SIZE)
    {
        last_brick->move_right();
    }


    if(e.keyname=="Down" && e.keycode > 0 )                  //checks if current position is in the air
    {
        coordinate * rem_y = tallest_under_me(last_brick);
        int remaining_distance = 0;

        if(rem_y != nullptr){
            remaining_distance = rem_y->get_y() - (last_brick->get_bottom().get_y() + BLOCK_SIZE);
            last_brick->move_down(remaining_distance,remaining_distance);   //moving to the brick under
        }

        else{
            remaining_distance = BOTTOM - (last_brick->get_bottom().get_y()+ BLOCK_SIZE);
            last_brick->move_down(remaining_distance, remaining_distance);    //moving to the floor
        }
    }

    if(e.keyname=="S" && e.keycode > 0){
        if(app_state==3){
            app_state = 1;
        }
        else{
            app_state = 3;
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

    if(a->return_state() && b->return_state()){
        return false;
    }

    std::vector<coordinate*> a_block = a->return_positions();
    std::vector<coordinate*> b_block = b->return_positions();

    //Checking collision


    for(int i = 0; i<4; i++)
    {
        for(int j = 0; j<4; j++)
        {
            if( (a_block[i]->get_x() == b_block[j]->get_x()) && (
                    (a_block[i]->get_y() == b_block[j]->get_y()+BLOCK_SIZE) ||
                        (a_block[i]->get_y() == b_block[j]->get_y() ) )

               )
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
        tetris_block * tmp = stickies[stickies.size()-1];
        if(tmp->return_state()==true && tmp->get_top().get_y()==TOP)
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
        app_state = -1;
        return app_state;
    }
    for(std::size_t i = 0; i<max_vecsize; i++)            //stickies vector contains the tetris blocks
    {
        for(std::size_t j = i+1; j<max_vecsize; j++)
        {
            check_collosion(stickies[i], stickies[j]);
        }

    }
    if(app_state!=3){
        fall();
    }

    return app_state;

}













