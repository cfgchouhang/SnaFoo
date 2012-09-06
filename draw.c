#include"snake.h"

void draw(GtkWidget *dr,cairo_t *cr,int x,int y,int w,int h,float r,float g,float b)
{
    cairo_set_source_rgb(cr,r,g,b);
    cairo_rectangle(cr,x,y,w,h);
    cairo_fill(cr);
    gtk_widget_draw(dr,cr);
}

void draw_snake(GtkWidget *dr,cairo_t *cr,Snake s[])
{
    int i;
    for(i=0;i<SNAKE_NUM;i++){
        int h = s[i].h,t = s[i].t+1;
        /*draw_unit(dr,cr,s[i].posi[h][0]
                   ,s[i].posi[h][1]
                   ,0,1.0,0);
        */
        draw_head(dr,cr,s[i].posi[h][0],s[i].posi[h][1],s[i].dir,s[i].color);
        
        while(t<h){
            draw_body(dr,cr,s[i].posi[t][0],s[i].posi[t][1],s[i].color,-1);
            t++;
        }
    }
}

void draw_turn(GtkWidget *dr,cairo_t *cr,int row,int col,double rgb[3][3],int dir){
    int posi[5][2];
    row *= UNIT;
    col *= UNIT;
    draw_unit(dr,cr,row,col,0,0,0);
    if(dir==-1)
        draw_unit(dr,cr,row,col,rgb[0][0],rgb[0][1],rgb[0][2]);
    else{
    draw_unit(dr,cr,row,col,0,0,0);
    cairo_destroy(cr);
    cr = gdk_cairo_create(gtk_widget_get_window(dr));
    cairo_set_source_rgb(cr,rgb[0][0],rgb[0][1],rgb[0][2]);
    if(!dir){
        cairo_move_to(cr,col,row);
        cairo_line_to(cr,col+UNIT/2,row);
        cairo_arc(cr,col+UNIT/2,row+UNIT/2,UNIT/2,-M_PI/2,0);
        cairo_line_to(cr,col+UNIT,row+UNIT);
        cairo_line_to(cr,col,row+UNIT);
        cairo_close_path(cr);
        cairo_fill(cr);
    }
    else if(dir==1){
        cairo_move_to(cr,col+UNIT,row);
        cairo_line_to(cr,col+UNIT/2,row);
        cairo_arc_negative(cr,col+UNIT/2,row+UNIT/2,UNIT/2,M_PI*3/2,M_PI);
        cairo_line_to(cr,col,row+UNIT);
        cairo_line_to(cr,col+UNIT,row+UNIT);
        cairo_close_path(cr);
        cairo_fill(cr);

    }
    else if(dir==2){
        cairo_move_to(cr,col,row);
        cairo_line_to(cr,col,row+UNIT/2);
        cairo_arc_negative(cr,col+UNIT/2,row+UNIT/2,UNIT/2,M_PI,M_PI/2);
        cairo_line_to(cr,col+UNIT,row+UNIT);
        cairo_line_to(cr,col+UNIT,row);
        cairo_close_path(cr);
        cairo_fill(cr);
    }
    else if(dir==3){
        cairo_move_to(cr,col+UNIT,row);
        cairo_line_to(cr,col+UNIT,row+UNIT/2);
        cairo_arc(cr,col+UNIT/2,row+UNIT/2,UNIT/2,0,M_PI/2);
        cairo_line_to(cr,col,row+UNIT);
        cairo_line_to(cr,col,row);
        cairo_close_path(cr);
        cairo_fill(cr);
    }
    }
}
void draw_body(GtkWidget *dr,cairo_t *cr,int row,int col,double rgb[3][3],int dir)
{
    int posi[5][2];
    draw_turn(dr,cr,row,col,rgb,dir);
    row *= UNIT;
    col *= UNIT;
    posi[0][0] = row+UNIT/2; posi[0][1] = col;
    posi[1][0] = row+UNIT; posi[1][1] = col+UNIT/2;
    posi[2][0] = row+UNIT/2; posi[2][1] = col+UNIT;
    posi[3][0] = row; posi[3][1] = col+UNIT/2;
    posi[4][0] = -1;
    draw_detail(cr,posi,rgb[1]);
}

void draw_head(GtkWidget *dr,cairo_t *cr,int row,int col,int dir,double rgb[3][3])
{
    cairo_destroy(cr);
    cr = gdk_cairo_create(gtk_widget_get_window(dr));
    int posi[10][2];
    row *= UNIT;
    col *= UNIT;
    switch(dir){
        case 0://left
            posi[0][0] = row; posi[0][1] = col+UNIT;
            posi[1][0] = row+3; posi[1][1] = col+8;
            posi[2][0] = row+UNIT/2; posi[2][1] = col;
            posi[3][0] = row+17; posi[3][1] = col+8;
            posi[4][0] = row+UNIT; posi[4][1] = col+UNIT;
            posi[5][0] = -1;
            draw_detail(cr,posi,rgb[0]);
            posi[0][0] = row; posi[0][1] = col+UNIT;
            posi[1][0] = row+10; posi[1][1] = col;
            posi[2][0] = row+UNIT; posi[2][1] = col+UNIT;
            posi[3][0] = -1;
            draw_detail(cr,posi,rgb[2]);
            cairo_set_source_rgb(cr,0,0,0);
            cairo_arc(cr,col+15,row+ 5,2,0,2*M_PI);
            cairo_arc(cr,col+15,row+15,2,0,2*M_PI);
            cairo_fill(cr);
            break;
        case 1://rigth
            posi[0][0] = row; posi[0][1] = col;
            posi[1][0] = row+3; posi[1][1] = col+12;
            posi[2][0] = row+UNIT/2; posi[2][1] = col+UNIT;
            posi[3][0] = row+17; posi[3][1] = col+12;
            posi[4][0] = row+UNIT; posi[4][1] = col;
            posi[5][0] = -1;
            draw_detail(cr,posi,rgb[0]);
            posi[0][0] = row; posi[0][1] = col;
            posi[1][0] = row+UNIT/2; posi[1][1] = col+UNIT;
            posi[2][0] = row+UNIT; posi[2][1] = col;
            posi[3][0] = -1;
            draw_detail(cr,posi,rgb[2]);
            cairo_set_source_rgb(cr,0,0,0);
            cairo_arc(cr,col+5,row+ 5,2,0,2*M_PI);
            cairo_arc(cr,col+5,row+15,2,0,2*M_PI);
            cairo_fill(cr);
            break;
        case 2://up
            posi[0][0] = row+UNIT; posi[0][1] = col;
            posi[1][0] = row+8; posi[1][1] = col+3;
            posi[2][0] = row; posi[2][1] = col+UNIT/2;
            posi[3][0] = row+8; posi[3][1] = col+17;
            posi[4][0] = row+UNIT; posi[4][1] = col+UNIT;
            posi[5][0] = -1;
            draw_detail(cr,posi,rgb[0]);
            posi[0][0] = row+UNIT; posi[0][1] = col;
            posi[1][0] = row; posi[1][1] = col+UNIT/2;
            posi[2][0] = row+UNIT; posi[2][1] = col+UNIT;
            posi[3][0] = -1;
            draw_detail(cr,posi,rgb[2]);
            cairo_set_source_rgb(cr,0,0,0);
            cairo_arc(cr,col+ 5,row+15,2,0,2*M_PI);
            cairo_arc(cr,col+15,row+15,2,0,2*M_PI);
            cairo_fill(cr);
            break;
        case 3://down
            posi[0][0] = row; posi[0][1] = col;
            posi[1][0] = row+12; posi[1][1] = col+3;
            posi[2][0] = row+UNIT; posi[2][1] = col+UNIT/2;
            posi[3][0] = row+12; posi[3][1] = col+17;
            posi[4][0] = row; posi[4][1] = col+UNIT;
            posi[5][0] = -1;
            draw_detail(cr,posi,rgb[0]);
            posi[0][0] = row; posi[0][1] = col;
            posi[1][0] = row+UNIT; posi[1][1] = col+UNIT/2;
            posi[2][0] = row; posi[2][1] = col+UNIT;
            posi[3][0] = -1;
            draw_detail(cr,posi,rgb[2]);
            cairo_set_source_rgb(cr,0,0,0);
            cairo_arc(cr,col+ 5,row+ 5,2,0,2*M_PI);
            cairo_arc(cr,col+15,row+ 5,2,0,2*M_PI);
            cairo_fill(cr);

            break;
    }
}

void draw_food(GtkWidget *dr,cairo_t *cr,int row,int col)
{
    draw_unit(dr,cr,row*UNIT,col*UNIT,0,0,1.0);
}

void draw_detail(cairo_t *cr,int posi[][2],double color[3])
{
    int i = 1;
    cairo_move_to(cr,posi[0][1],posi[0][0]);
    while(posi[i][0]>-1){
        cairo_line_to(cr,posi[i][1],posi[i][0]);
        i++;
    }
    cairo_close_path(cr);
    cairo_set_source_rgb(cr,color[0],color[1],color[2]);
    cairo_fill(cr);
}

void draw_unit(GtkWidget *dr,cairo_t *cr,int row,int col,float r,float g,float b)
{
    cairo_destroy(cr);
    cr = gdk_cairo_create(gtk_widget_get_window(dr));
    cairo_set_source_rgb(cr,r,g,b);
    cairo_rectangle(cr,col,row,UNIT,UNIT);
    cairo_fill(cr);
    //gtk_widget_draw(dr,cr);
}

