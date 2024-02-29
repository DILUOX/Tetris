#ifndef UI_HPP
#define UI_HPP


#include <iostream>
#include <vector>
#include <string>
#include <sstream>


#include "graphics.hpp"
#include "exceptions.hpp"


//Global game variables containing info about ui formatting

static const int HEIGHT = 800;
static const int WIDTH = 1000;


static const int borderSizePx = 1;
static const int BLOCK_SIZE = 50;
static const int TOP = 0;
static const int BOTTOM = HEIGHT;
static const int LEFT_SIDE = 200;
static const int RIGHT_SIDE = WIDTH-LEFT_SIDE;

static const int MIDDLE = (RIGHT_SIDE-LEFT_SIDE) / 2 + LEFT_SIDE  - BLOCK_SIZE ;


//UI Sturcture and class definition

struct RGB {
    unsigned char r, g, b;
};

RGB getRandomRGBColor() ;


class coordinate
{
public:


    coordinate() : x(0), y(0) {}

    coordinate(int _x, int _y):x(_x),y(_y) {}

    int get_x()const
    {
        return x;
    }


    int get_y()const
    {
        return y;
    }


    void set_x(int x_)
    {
        if(x_< LEFT_SIDE || x_ > RIGHT_SIDE)
        {
            throw Nullptr_stat_int_err();
        }
        //print();
        x=x_;
    }


    void set_y(int y_)
    {
        y=y_;
    }
    void print()
    {

        std::stringstream message;
        message<< "X: " + std::to_string(get_x()) + "Y: " + std::to_string(get_y()) + ';';
        std::string formatted_msg = "";
        std::getline(message,formatted_msg, ';');
        std::cout<<formatted_msg<<std::endl;
    }

private:
    int x;
    int y;
};







class Object
{

public:
    Object(int id,int x, int y):id(id), position(x,y)
    {
        state = 0;
    }

    const int get_id()
    {
        return id;
    }

    const virtual int return_value()
    {
        return 0;
    }

    coordinate get_centerpos()          //returns center position of the object
    {

        coordinate tmp(position.get_x() + buttonlength_x/2, position.get_y()+buttonlength_y/2);
        return tmp;
    }
    const coordinate get_pos()  //returns the position of the far left corner
    {
        return position;
    }
    virtual void draw()
    {
    }

    virtual void set_input(genv::event e)
    {
    }

    const bool is_clicked(genv::event e)
    {
        return position.get_x()<e.pos_x && e.pos_x<position.get_x()+buttonlength_x
               && position.get_y()<e.pos_y && e.pos_y<position.get_y()+buttonlength_y;
    }

protected:
    int id;

    coordinate position;

    const int buttonlength_x = 100;

    const int buttonlength_y = 50;

    int state;
};


class Button : public Object
{
public:
    Button(int id, int x, int y, std::string label) : Object(id,x,y), label(label)
    {
    }

    const virtual int return_value();

    virtual void draw();

    virtual void set_input(genv::event e);



private:
    std::string label;

};



class Interface
{
public:
    Interface()
    {
        ui_elements = {new Button(1,MIDDLE,200,"Play"), new Button(2,MIDDLE,270,"Exit")};

        screen_state = 0;
    }
    ~Interface()
    {
        ui_elements.erase(ui_elements.begin(),ui_elements.end());
    }

    int operate(genv::event e);
private:
    std::vector<Object*> ui_elements;
    int screen_state;
};

//template class coord_arr<coordinate>;


#endif // UI_HPP
