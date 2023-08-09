#ifndef UI_HPP
#define UI_HPP
#include "graphics.hpp"
#include <vector>




struct coordinate
{
public:

    coordinate(int x, int y):x(x),y(y) {}
    int get_x()
    {
        return x;
    }
    int get_y()
    {
        return y;
    }
    void set_y(int y_){
        y=y_;
    }

private:
    int x;
    int y;
};




class Object
{

public:
    Object(int id,int x, int y):id(id), position(x,y) {
        state = 0;
    }

    const int get_id(){
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
        ui_elements = {new Button(1,350,200,"Play"), new Button(2,350,270,"Exit")};

        screen_state = 0;
    }
    ~Interface(){
        ui_elements.erase(ui_elements.begin(),ui_elements.end());
    }

    int operate(genv::event e);
private:
    std::vector<Object*> ui_elements;
    int screen_state;
};




#endif // UI_HPP
