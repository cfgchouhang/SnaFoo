#include"snake.h"

void open_menu(Plate *p) {
    p->state = 3;
    cairo_destroy(p->cr);
    p->cr = gdk_cairo_create(gtk_widget_get_window(p->dr));
    cairo_set_source_rgb(p->cr,1.0,1.0,0);
    cairo_rectangle(p->cr,190,190,230,230);
    cairo_fill(p->cr);
    set_menu(p->cr);
    set_popt(p->cr,p->mode);
    arrow_menu(p->cr,p->menu);
}

void set_popt(cairo_t *cr,int m)
{
    cairo_text_extents_t extents;
    char p[4];
    sprintf(p,"%dP",m);
    cairo_select_font_face(cr,"Sans",
        CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);
    cairo_move_to(cr,360,390);
    cairo_set_font_size(cr,28);
    cairo_text_extents(cr,p,&extents);
    cairo_show_text(cr,p);
}

void set_menu(cairo_t *cr)
{
    cairo_text_extents_t extents;
    const char *n = "New",*s = "From Saved",*e = "End";
    cairo_select_font_face(cr,"Sans",
        CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr,40);
    //cairo_text_extents(cr,n,&extents);
    //New
    cairo_move_to(cr,260,245);
    cairo_text_path(cr,"New");
    //Saved
    cairo_move_to(cr,260,310);
    cairo_text_path(cr,"Saved");
        //End
    cairo_move_to(cr,260,375);
    cairo_text_path(cr,"End");

    cairo_set_source_rgb(cr,0.74,0.48,1);
    cairo_set_line_width(cr,1.0);
    cairo_fill_preserve(cr);
    cairo_set_source_rgb(cr,0,0,0);
    cairo_stroke(cr);

    cairo_set_line_width(cr,3.0);
    cairo_move_to(cr,320,280);
    cairo_curve_to(cr,430,210,430,385,350,317);
    cairo_move_to(cr,351,317);
    cairo_line_to(cr,356,335);
    cairo_move_to(cr,351,318);
    cairo_line_to(cr,369,316.5);
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
    cairo_rectangle(cr,200,190,50,220);
    cairo_fill(cr);
    cairo_move_to(cr,200,220+v);
    cairo_line_to(cr,225,220+v);
    cairo_line_to(cr,225,207.5+v);
    cairo_line_to(cr,250,232.5+v);
    cairo_line_to(cr,225,257.5+v);
    cairo_line_to(cr,225,245+v);
    cairo_line_to(cr,200,245+v);
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
    cairo_rectangle(p->cr,190,190,230,230);
    cairo_fill(p->cr);
    draw_snake(p->dr,p->cr,p->snake,p->mode,p->map);
    for(i=9;i<21;i++)
        for(j=9;j<21;j++)
            if(!p->map[i][j].exist&&p->map[i][j].food)
                draw_food(p->dr,p->cr,i,j);
    p->state = 1;
    p->mode = p->tmpm;
}

gboolean key_press(GtkWidget *w,GdkEvent *e,Plate *p)
{
    guint keyval = ((GdkEventKey *)e)->keyval;
    printf("%x\n",keyval);
    if(keyval==0x0065)
        gtk_main_quit();
    /*
    if(keyval==0x0070)
        pause_game(p->btn[1],&p->state);
    if(keyval==0x0032)
        change_mode(p->mbtn,p);
    */
    if(keyval==0x006e&&p->state!=3)
        new_game(p);
    if(keyval==0xff1b){
        if(p->state==3)
            close_menu(p);
        else
            open_menu(p);
    }
    if(!p->state)return TRUE;
    if(p->state==3){
        switch(keyval){
            case 0xff52:
                p->menu = !p->menu ? 0:p->menu-1;
                arrow_menu(p->cr,p->menu);
                break;
            case 0xff54:
                p->menu = p->menu==2 ? 2:p->menu+1;
                arrow_menu(p->cr,p->menu);
                break;
            case 0xff0d:
                if(!p->menu)
                    new_game(p);
                else if(p->menu==1)
                    ;
                else if(p->menu==2)
                    gtk_main_quit();
                break;
            case 0x0031:
                p->tmpm = 1;
                set_popt(p->cr,p->tmpm);
                break;
            case 0x0032:
                p->tmpm = 2;
                set_popt(p->cr,p->tmpm);
                break;
        }
        return TRUE;
    }
    while(p->state==2);
    p->state = 2;
    switch(keyval){
        case 0xff51:
            if(p->snake[0].diry!=0)
                turn_left(p,0);break;
        case 0xff52:
            if(p->snake[0].dirx!=0)
                turn_up(p,0);break;
        case 0xff53:
            if(p->snake[0].diry!=0)
                turn_right(p,0);break;
        case 0xff54:
            if(p->snake[0].dirx!=0)
                turn_down(p,0);break;
            }
    if(p->mode==2){
        switch(keyval){
        case 0x006a:
            if(p->snake[1].diry!=0)
                turn_left(p,1);break;
        case 0x006b:
            if(p->snake[1].dirx!=0)
                turn_down(p,1);break;
        case 0x006c:
            if(p->snake[1].diry!=0)
                turn_right(p,1);break;
        case 0x0069:
            if(p->snake[1].dirx!=0)
                turn_up(p,1);break;
        }
    }
    p->state = 1;
    return FALSE;
}

