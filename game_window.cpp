#include "game_window.hpp"
#include "exceptions.hpp"




/* BEGIN TETRIS BLOCK CLASS DEFINITION */


tetris_block::tetris_block(short id, int x, int y, RGB color) : id(id), fallen(false),colorid(color)
{
    vertex = coordinate(x,y);
}


void tetris_block::drawIt()const
{
    //drawing a box, starting from the upper left corner(position of the vertex)
    genv::gout<<genv::move_to(vertex.get_x(),vertex.get_y())<<genv::color(0,0,0)<<genv::box(BLOCK_SIZE,BLOCK_SIZE)
    //drawing the meshgrid
    <<genv::move_to(vertex.get_x()+borderSizePx,vertex.get_y()+borderSizePx)<<genv::color(colorid.r,colorid.g,colorid.b)<<genv::box(BLOCK_SIZE-borderSizePx*2,BLOCK_SIZE-borderSizePx*2);

}
coordinate tetris_block::get_vertex()const
{
    return vertex;
}

void tetris_block::set_vertex(int x, int y){
    this->vertex.set_x(x);
    this->vertex.set_y(y);

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
    srand(time(0));
    highest_pos = BOTTOM;
    std::vector<tetris_block*> bricks = std::vector<tetris_block*>();
    liftdown_speed = 50;
    numof_blocks = 0;
    generate_block();

    app_state = 1;

}


//Random direction based tetramino generating algorithm:
//the position of the next block determined by a random number in range of 1-3
//these numbers mean the following:
//    1- next block goes to the left of the previous block
//    2- next block goes to the right of the previous block
//    3- next block goes under the previous block

void Game_window::generate_block(){
    int dir = 0,prev_dir;
    RGB colorid = getRandomRGBColor();
    coordinate last_block = coordinate(0,0);

    //generating first block
    tetris_block * t = new tetris_block( numof_blocks,MIDDLE, TOP,colorid );
    bricks.push_back(t);

    //generating the rest
    for(unsigned int i = 0; i<BLOCK_COUNT-1;i++)
    {
        prev_dir = dir;
        dir = rand()%3 +1;
        last_block = bricks.back()->get_vertex();

        switch(dir)
        {
            case 1:
                if(prev_dir==2)
                {
                    t = new tetris_block(numof_blocks, last_block.get_x() + BLOCK_SIZE, last_block.get_y(), colorid );
                    dir = 2;
                    break;
                }
                t = new tetris_block(numof_blocks, last_block.get_x() - BLOCK_SIZE, last_block.get_y(), colorid );
                break;
            case 2:
                if(prev_dir==1)
                {
                    t = new tetris_block(numof_blocks, last_block.get_x() - BLOCK_SIZE,last_block.get_y() ,colorid );
                    dir = 1;
                    break;
                }
                t = new tetris_block(numof_blocks, last_block.get_x() + BLOCK_SIZE, last_block.get_y(),colorid );
                break;
            default:
                t = new tetris_block(numof_blocks, last_block.get_x(), last_block.get_y() + BLOCK_SIZE, colorid) ;
                break;
        }
        bricks.push_back(t);

    }
    numof_blocks++;

}

//Reset gamestate

void Game_window::reset(){
    bricks.clear();
    highest_pos = BOTTOM;
    numof_blocks = 0;
    generate_block();
    app_state = 1;
}


//Simple rendering

void Game_window::draw_screen()const{
    for(auto it : bricks){it->drawIt();}
}


void Game_window::fall(){
    //don't want this shit to happen
    if(bricks.empty()){
        return;
    }

    for(std::size_t it = bricks.size(); it>bricks.size()-BLOCK_COUNT; it--){
        bricks[it-1]->set_vertex(bricks[it-1]->get_vertex().get_x(),bricks[it-1]->get_vertex().get_y()+liftdown_speed);
    }

}


//checking collision by comparing block coordinates brute force like
//starting from the end of the vector
//only the falling pieces are being compared

bool Game_window::check_collision()
{
    bool collided = false;
    for(std::size_t falling_piece_index = bricks.size();  falling_piece_index>bricks.size()-BLOCK_COUNT;falling_piece_index--)
    {
        if(bricks[falling_piece_index-1]->get_vertex().get_y() == BOTTOM-BLOCK_SIZE)
        {
            bricks[falling_piece_index-1]->stop();
            collided = true;
            continue;
        }
        for(std::size_t it = bricks.size()-BLOCK_COUNT; it>0; it--)
        {
            //falling block is beneath another
            if( (bricks[it-1]->get_vertex().get_x() == bricks[falling_piece_index-1]->get_vertex().get_x()) &&
               (bricks[it-1]->get_vertex().get_y() == ( bricks[falling_piece_index-1]->get_vertex().get_y() + BLOCK_SIZE))  )
            {
                bricks[falling_piece_index-1]->stop();
                collided = true;
            }
        }
    }
    return collided;
}

//Main game function

int Game_window::operate(){


    this->draw_screen();

    if(e.type==genv::ev_timer) fall();
    if(this->check_collision() ){
        generate_block();
    }

    genv::gout<<genv::refresh;

    return app_state;
}



























