#include "main_window.hpp"
//#include <iostream>
using namespace genv;


void MainWindow::draw_background(){
    for(unsigned int i = 0; i<2;i++){               //setting up walls on the two sides of the screen
        for(unsigned int j = 0; j <height/200; j++){
            background->draw(i*600,j*200);
        }
    }
    genv::gout<<genv::refresh;

}




int MainWindow::Window_loop()
{
    ui.operate(ev);
    while(true)
    {

        gin >> ev;

        if(app_state==-1){
            gameover->draw(0,0);
            if(ev.keycode==key_escape){
                draw_background();
                app_state = 0;
            }
        }
        else{
            refresh_frame();
        }

        screen_id=ui.operate(ev);
        if(screen_id==1)
        {
            tetris.set_events(ev);
            app_state=tetris.operate();

        }
        else if(screen_id==2)
        {
            break;
        }
        if(ev.type!=ev_timer){
            gout<<refresh;
        }



    }
    return 0;
}
