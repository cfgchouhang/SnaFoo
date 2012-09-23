#include"snake.h"

void open_menu(Plate *p)
{
    p->inmenu = 1;
    p->state = 3;
    cairo_set_source_rgba(p->cr,1.0,0.45,0,0.5);
    cairo_rectangle(p->cr,250,200,100,200);
    cairo_fill(p->cr);
}

void close_menu(Plate *p)
{
    int i,j;
    cairo_set_source_rgb(p->cr,0,0,0);
    cairo_rectangle(p->cr,250,200,100,200);
    cairo_fill(p->cr);
    draw_snake(p->dr,p->cr,p->snake,p->mode,p->map);
    for(i=10;i<20;i++)
        for(j=12;j<18;j++)
            if(!p->map[i][j].exist&&p->map[i][j].food)
                draw_food(p->dr,p->cr,i,j);
    p->inmenu = 0;
    p->state = 1;
    
}
