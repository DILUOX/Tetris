#include "ui.hpp"

using namespace genv;

const int Button::return_value()
{
    return state;

}

void Button::draw()
{
    gout<<move_to(position.get_x(),position.get_y());
    if(state==0)                //usual state
    {
        gout<<color(255,255,255);
    }
    else                        //mouse is on the button
    {
        gout<<color(255,255,0);
    }
    gout<<box(buttonlength_x, buttonlength_y)       //drawing the button
        <<move_to(get_centerpos().get_x()-gout.twidth(label)/2,get_centerpos().get_y()) //setting label position
        <<color(0,0,0)<<text(label);
}

void Button::set_input(event e)     //mouse states
{
    if(is_clicked(e))
    {

        if(e.button==btn_left)      //click state
        {
            state = 2;
        }
        else
        {
            state = 1;              //mouse is on the button state
        }
    }
    else
    {
        state = 0;                  //normal state
    }
}



int Interface::operate(event e)
{
    int val=0;
    if(screen_state==0)
    {
        for(Object * i : ui_elements)
        {
            i->set_input(e);
            i->draw();

            val=i->return_value();

            if(val==2)
            {
                if(i->get_id()==1)
                {
                    screen_state=1;
                }
                else{
                    screen_state=2;
                }

            }
        }
    }
    else if(screen_state==1 && e.keycode==key_escape)
    {
        screen_state=0;
    }



    return screen_state;


}
