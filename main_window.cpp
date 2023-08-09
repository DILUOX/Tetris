#include "main_window.hpp"

using namespace genv;

int MainWindow::Window_loop(){
    while(gin >> ev) {
        refresh_frame();
        screen_id=ui.operate(ev);

        if(screen_id==2){
            break;
        }

        gout<<refresh;
    }
    return 0;
}
