#include"snake.h"

void open_menu(Plate *p) {
    p->state = 3;
    cairo_destroy(p->cr);
    p->cr = gdk_cairo_create(gtk_widget_get_window(p->dr));
    cairo_set_source_rgb(p->cr,1.0,1.0,0);
    cairo_rectangle(p->cr,210,190,210,220);
    cairo_fill(p->cr);
    set_menu(p->cr);
    arrow_menu(p->cr,p->menu);
}

void set_menu(cairo_t *cr)
{
    cairo_text_extents_t extents;
    const char *n = "New",*s = "From Saved",*e = "End";
    
    cairo_select_font_face(cr,"Sans",
        CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr,40);
    cairo_text_extents(cr,n,&extents);
    //New
    cairo_move_to(cr,280,245);
    cairo_text_path(cr,"New");
    //Saved
    cairo_move_to(cr,280,310);
    cairo_text_path(cr,"Saved");
    /*
    cairo_set_line_width(cr,2.5);
    cairo_move_to(cr,310,280);
    cairo_curve_to(cr,240,235,250,360,293,317);
    cairo_stroke(cr);
    */
    //End
    cairo_move_to(cr,280,375);
    cairo_text_path(cr,"End");

    cairo_set_source_rgb(cr,0.74,0.48,1);
    cairo_set_line_width(cr,1.0);
    cairo_fill_preserve(cr);
    cairo_set_source_rgb(cr,0,0,0);
    cairo_stroke(cr);

}

void arrow_menu(cairo_t *cr,int opt)
{
    int v = 0;
    if(opt==1)
        v = 60;
    if(opt==2)
        v = 125;
    cairo_set_source_rgb(cr,1.0,1.0,0);
    cairo_rectangle(cr,220,190,50,220);
    cairo_fill(cr);
    cairo_move_to(cr,220,220+v);
    cairo_line_to(cr,245,220+v);
    cairo_line_to(cr,245,207.5+v);
    cairo_line_to(cr,270,232.5+v);
    cairo_line_to(cr,245,257.5+v);
    cairo_line_to(cr,245,245+v);
    cairo_line_to(cr,220,245+v);
    cairo_close_path(cr);
    cairo_set_source_rgb(cr,1.0,0.398,0);
    cairo_fill(cr);
}

void close_menu(Plate *p)
{
    int i,j;
    cairo_destroy(p->cr);
    p->cr = gdk_cairo_create(gtk_widget_get_window(p->dr));
    cairo_set_source_rgb(p->cr,0,0,0);
    cairo_rectangle(p->cr,210,190,210,230);
    cairo_fill(p->cr);
    draw_snake(p->dr,p->cr,p->snake,p->mode,p->map);
    for(i=9;i<21;i++)
        for(j=10;j<21;j++)
            if(!p->map[i][j].exist&&p->map[i][j].food)
                draw_food(p->dr,p->cr,i,j);
    p->state = 1;
}

