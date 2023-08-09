#include "main_window.hpp"
using namespace genv;

int main()
{
    const unsigned int width = 800;
    const unsigned int height = 800;
    const bool fullscreen = false;

    MainWindow * window = new MainWindow(width, height, fullscreen);
    window->Window_loop();
    delete window;
    return 0;
}
