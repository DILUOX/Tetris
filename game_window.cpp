#include "game_window.hpp"
#include "exceptions.hpp"




/* BEGIN TETRIS BLOCK CLASS DEFINITION */


tetris_block::tetris_block(short id, int x, int y) : id(id), fallen(false),colorid(rand() % 14 + 1)
{
    vertex = coordinate(x,y);
}

void tetris_block::drawIt()const
{
    //drawing a box, starting from the upper left corner(position of the vertex)
    genv::gout<<genv::move_to(vertex.get_x(),vertex.get_y())<<genv::color(colorid*17,colorid*17,colorid*17)<<genv::box(BLOCK_SIZE,BLOCK_SIZE);
}

coordinate tetris_block::get_vertex() const
{
    return vertex;
}

void tetris_block::move_left()
{
    if(vertex.get_x()>LEFT_SIDE)
    {
        vertex.set_x(vertex.get_x()-BLOCK_SIZE);
    }
}

void tetris_block::move_right()
{
    if(vertex.get_x()< RIGHT_SIDE-BLOCK_SIZE)
    {
        vertex.set_x(vertex.get_x()+BLOCK_SIZE);
    }
}


void tetris_block::move_down(int move_px_down, int rem_distance){
    if(move_px_down<=rem_distance)
    {
        vertex.set_y(vertex.get_y()+move_px_down);
    }
}


/* END TETRIS BLOCK CLASS DEFINITION */




/* BEGIN GAME_WINDOW CLASS DEFINITION */



Game_window::Game_window(const int width,const int height) : ParentWindow(width, height)
{
    highest_pos = BOTTOM;
    std::vector<tetris_block> stickies = std::vector<tetris_block>();
    liftdown_speed = 50;
    numof_blocks = 0;
    generate_block();

    app_state = 1;
    srand(time(0));
}


void Game_window::generate_block(){
    int dir = 0;
    int prev_dir;
    //generating first block of the whole figure
    tetris_block * t = new tetris_block( numof_blocks,MIDDLE, TOP );
    stickies.push_back(t);


    //generating the rest of the figure
    for(int i = 0; i<BLOCK_COUNT-1;i++){
        prev_dir = dir;

        /***
        the position of the next block determined by a random number in range of 1-3
        these numbers mean the following:
            1- next block goes to the left of the previous block
            2- next block goes to the right of the previous block
            3- next block goes under the previous block
        ***/
        dir = rand()%3 +1;
        coordinate last_block = stickies.back()->get_vertex();
        switch(dir)
        {
        case 1:
            if(prev_dir==2){
                t = new tetris_block(numof_blocks,last_block.get_x()+BLOCK_SIZE,TOP);
                break;
            }
            t = new tetris_block(numof_blocks,last_block.get_x()-BLOCK_SIZE,TOP);
            break;
        case 2:
            if(prev_dir==1){
                t = new tetris_block(numof_blocks,last_block.get_x()-BLOCK_SIZE,TOP);
                break;
            }
            t = new tetris_block(numof_blocks,last_block.get_x()+BLOCK_SIZE, TOP);
            break;
        default:
            t = new tetris_block(numof_blocks,last_block.get_x(),last_block.get_y()+BLOCK_SIZE);
            break;
        }
        stickies.push_back(t);
    }


}



void Game_window::reset(){
    stickies.clear();
    highest_pos = BOTTOM;
    numof_blocks = 0;
    generate_block();
    app_state = 1;
}































