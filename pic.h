#include "graphics.hpp"
#include <fstream>

struct pixel
{
    int r,g,b;
};


struct texture
{
    pixel * pic;
    int width, height;

    texture(char filename[])
    {
        std::ifstream file_("brick.kep");
        file_>>width>>height;
        pic = new pixel[width*height];
        int tail = 0;

        for(int y = 0; y<height; y++)
        {
            for(int x = 0; x<width; x++)
            {
                file_>>pic[tail].r>>pic[tail].g>>pic[tail].b;
                tail++;
            }
        }
    }
    void draw(int x_, int y_)
    {
        int tail=0;
        for(int y = 0; y<height; y++)
        {
            for(int x = 0; x<width; x++)
            {
                pixel pcs = pic[tail];
                genv::gout<<genv::move_to(x+x_,y+y_)<<genv::color(pcs.r,pcs.g,pcs.b)<<genv::dot;
                tail++;
            }
        }
    }


};
