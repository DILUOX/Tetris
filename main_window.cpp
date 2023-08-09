#include "main_window.hpp"

using namespace genv;

int MainWindow::Window_loop()
{
    ui.operate(ev);
    while(true)
    {

        gin >> ev;
        refresh_frame();


        screen_id=ui.operate(ev);
        if(screen_id==1)
        {
            tetris.set_events(ev);
            tetris.operate();

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
