#include"snake.h"

void open_menu(Plate *p)
{
    p->inmenu = 1;
    p->state = 3;
    cairo_destroy(p->cr);
    p->cr = gdk_cairo_create(gtk_widget_get_window(p->dr));
    cairo_set_source_rgba(p->cr,1.0,1.0,0,0.875);
    cairo_rectangle(p->cr,210,190,190,220);
    cairo_fill(p->cr);
    set_menu(p->cr);
}

void set_menu(cairo_t *cr)
{
    cairo_text_extents_t extents;
    const char *n = "New",*s = "From Saved",*e = "End";
    
    cairo_select_font_face(cr,"Sans",
        CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr,40);
    //New
    cairo_text_extents(cr,n,&extents);
    cairo_move_to(cr,275,245);
    cairo_text_path(cr,"New");
    cairo_set_source_rgb(cr,0.74,0.48,1);
    cairo_fill_preserve(cr);
    cairo_set_source_rgb(cr,0,0,0);
    cairo_set_line_width(cr,1.5);
    cairo_stroke(cr);
    //Saved
    cairo_move_to(cr,270,310);
    cairo_text_path(cr,"Saved");
    cairo_set_source_rgb(cr,0.74,0.48,1);
    cairo_fill_preserve(cr);
    cairo_set_source_rgb(cr,0,0,0);
    cairo_stroke(cr);
    cairo_set_line_width(cr,2.5);
    cairo_move_to(cr,310,280);
    cairo_curve_to(cr,240,235,250,360,293,317);
    cairo_stroke(cr);
    //End
    cairo_move_to(cr,275,375);
    cairo_text_path(cr,"End");
    cairo_set_source_rgb(cr,0.74,0.48,1);
    cairo_fill_preserve(cr);
    cairo_set_line_width(cr,1.5);
    cairo_set_source_rgb(cr,0,0,0);
    cairo_stroke(cr);
}

void close_menu(Plate *p)
{
    int i,j;
    cairo_destroy(p->cr);
    p->cr = gdk_cairo_create(gtk_widget_get_window(p->dr));
    cairo_set_source_rgb(p->cr,0,0,0);
    cairo_rectangle(p->cr,220,190,190,220);
    cairo_fill(p->cr);
    draw_snake(p->dr,p->cr,p->snake,p->mode,p->map);
    for(i=9;i<21;i++)
        for(j=10;j<21;j++)
            if(!p->map[i][j].exist&&p->map[i][j].food)
                draw_food(p->dr,p->cr,i,j);
    p->inmenu = 0;
    p->state = 1;
    
}

