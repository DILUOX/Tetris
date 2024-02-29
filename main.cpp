#include "main_window.hpp"
using namespace genv;



int main()
{
    const bool fullscreen = false;


    MainWindow * window = new MainWindow(WIDTH, HEIGHT, fullscreen);
    window->Window_loop();
    delete window;
    return 0;
}
