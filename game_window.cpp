#include <math.h>
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


void tetris_block::move_down(int move_px_down, int rem_distance)
{
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

    liftdown_speed = 50;    numof_blocks = 0;    generate_block();

    app_state = 1;

}


//Random direction based tetramino generating algorithm:
//the position of the next block determined by a random number in range of 1-3
//these numbers mean the following:
//    1- next block goes to the left of the previous block
//    2- next block goes to the right of the previous block
//    3- next block goes under the previous block

void Game_window::generate_block()
{
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

//Simple gravity

void Game_window::fall(){
    //don't want this shit to happen
    if(bricks.empty()){
        return;
    }
    for(std::size_t it = bricks.size(); it>bricks.size()-BLOCK_COUNT; it--)
    {
        if(!bricks[it-1]->return_state())
        {
            bricks[it-1]->move_down( BLOCK_SIZE,
                                    BOTTOM - bricks[it-1]->get_vertex().get_y() );
        }

    }

}






//checking collision by comparing block coordinates brute force like
//starting from the end of the vector
//only the falling pieces are being compared
//returns the type of collision

collide_status Game_window::check_collision()
{
    int min_x = RIGHT_SIDE;
    int max_x = LEFT_SIDE;
    coordinate current_vertex;
    coordinate other_vertex;

    collide_status status = COLLIDING_NONE;


    for(std::size_t falling_piece_index = bricks.size();  falling_piece_index>bricks.size()-BLOCK_COUNT;falling_piece_index--)
    {
        current_vertex = bricks[falling_piece_index-1]->get_vertex();

        int tmp_x = current_vertex.get_x();

        //searching if any sides reached a wall

        if(min_x > tmp_x) {min_x = tmp_x;}

        if(max_x < tmp_x) {max_x = tmp_x;}

        //case 1: block hits the bottom
        if(current_vertex.get_y() == BOTTOM-BLOCK_SIZE)
        {
            status = STOPPING;
            break;
        }


        for(std::size_t it = bricks.size()-BLOCK_COUNT; it>0; it--)
        {
            other_vertex = bricks[it-1]->get_vertex();

            //case 2: block hits another block on top
            if( other_vertex.get_x() == current_vertex.get_x() &&
                other_vertex.get_y() ==  (current_vertex.get_y() + BLOCK_SIZE ) )
            {
                status = STOPPING;
                break;
            }

            if(e.type != genv::ev_key){continue;}

            //case 3: block hits another block's side
            if( (other_vertex.get_y() !=  current_vertex.get_y())
               ){continue;}

            //hit it from the right
            if((other_vertex.get_x() == current_vertex.get_x() + BLOCK_SIZE)){
                return COLLIDING_RIGHT;
            }
            //hit it from the left
            if((other_vertex.get_x() == current_vertex.get_x() - BLOCK_SIZE)){
               return COLLIDING_LEFT;
            }

        }
    }

    if(status == STOPPING){
        for(std::size_t i = bricks.size();  i>bricks.size()-BLOCK_COUNT;i--)
        {
            bricks[i-1]->stop();
            highest_pos = std::min(this->highest_pos,bricks[i-1]->get_vertex().get_y());
        }
        return status;
    }

    if(min_x == LEFT_SIDE){
        return COLLIDING_LEFT;
    }

    if(max_x == RIGHT_SIDE-BLOCK_SIZE){
        return COLLIDING_RIGHT;
    }


    return status;
}


//Tetramino control function wrapping new piece generation


void Game_window::control(){

    //std::cout<<e.keycode<<" : "<<e.keyname<<'\n';

    collide_status block_status = check_collision();


    if(block_status == STOPPING){
        generate_block();
    }

    switch(e.keycode)
    {
        //Left arrow
        case 80:
            if(block_status == COLLIDING_LEFT)return;

            for(std::size_t it = bricks.size(); it>bricks.size()-BLOCK_COUNT; it--)
            {
                bricks[it-1]->move_left();
            }
            break;

        //Right arrow
        case 79:
            if(block_status == COLLIDING_RIGHT) return;
            for(std::size_t it = bricks.size(); it>bricks.size()-BLOCK_COUNT; it--){
                bricks[it-1]->move_right();
            }

        default:
            break;
    }


}

//Simple row checking. Returns -1 if there isn't any rows filled. Otherwise it returns the vertical position of the fulfilled row

int Game_window::check_fullrow()
{
    int row_vertical_pos;
    int max_in_row = 0;
    int current_in_row;

    for(int y = highest_pos; y < BOTTOM; y+=BLOCK_SIZE)
    {
        current_in_row = 0;
        for(tetris_block * t : bricks)
        {
            if(!t->return_state() || t->get_vertex().get_y()!=y) {continue;}
            current_in_row++;
        }
        if(current_in_row>max_in_row)
        {
            max_in_row = current_in_row;
            row_vertical_pos = y;
        }

    }

    if( max_in_row == ROW_LENGTH)
    {
        return row_vertical_pos;
    }

    return -1;

}


//delete a whole row. Use it with caution because if there isnt any full row it causes undefined behavior!

void Game_window::delete_row(int row_positon)
{
    int to_be_deleted[ROW_LENGTH] , tail = 0;

    for(std::size_t index = 0; index<bricks.size();index++)
    {
        if(bricks[index]->get_vertex().get_y() == row_positon)
        {
            to_be_deleted[tail] = index;
            tail++;
        }
    }

    for(int i = ROW_LENGTH-1; i>-1 ; i--){
        bricks.erase(bricks.begin()+ to_be_deleted[i]);
    }
}


//This function does the one-block fall mechanism after a row was deleted
//It makes all the blocks with smaller y positon than row_position go a block down

void Game_window::fall_after_delete(int row_position)
{
    for(std::size_t index = 0; index<bricks.size()-BLOCK_COUNT;index++)
    {
        if(bricks[index]->get_vertex().get_y() < row_position)
        {
            bricks[index]->move_down(BLOCK_SIZE,BLOCK_SIZE);
        }
    }

}


bool Game_window::check_gameover()
{
    return highest_pos == TOP || highest_pos == TOP+BLOCK_SIZE;
}


//Main game function

int Game_window::operate(){

    if(this->check_gameover())
    {
        return -1;
    }

    this->control();
    this->draw_screen();

    if(e.type==genv::ev_timer)
    {
        fall();
    }
    genv::gout<<genv::refresh;

    int row_position = this->check_fullrow();

    if(row_position != -1){
        this->delete_row(row_position);
        this->fall_after_delete(row_position);
    }



    return app_state;
}



























