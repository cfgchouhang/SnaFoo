#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<gtk/gtk.h>
#include<cairo.h>
#include<math.h>

#define UNIT 20 
#define SNAKE_MAX 500
#define WIDTH 600 
#define HEIGHT 600
#define MAP_LEN 30
#define SNAKE_NUM 2

typedef struct map{
    int barrier;
    int food;
    int exist;
    int dir;
}Map;

typedef struct snake{
    unsigned int posi[SNAKE_MAX][2];
    unsigned int h,t;
    double color[3][3];
    int dir,dirx,diry;// dir 0,left 1,right 2,up 3,down
}Snake;

typedef struct plate{
    GtkWidget *dr,*label,*dialog,*mbtn,*btn[3];
    cairo_t *cr;
    guint32 interval;
    guint timeoutid;
    Snake snake[2];
    Map map[MAP_LEN][MAP_LEN];
    int state,keyevent,menu;
    int score,mode,tmpm,pass,win;
}Plate;

//set
void init_plate(Plate *p,GtkWidget *fixed,int w,int h);
//void new_game(GtkWidget *btn,Plate *p);
void new_game(Plate *p);
void response(Plate *p);
void show_result(Plate *p,char *m);
void win_game();
//void pause_game(GtkWidget *btn,gpointer d);
void pause_game(gpointer d);
void change_mode(GtkWidget *btn,Plate *p);
void set_map_snake(GtkWidget *dr,cairo_t *cr,Plate *p);
void show_score(GtkWidget *l,int s);

//draw
gboolean draw_plate(GtkWidget *w,cairo_t *cr,gpointer data);
void draw(GtkWidget *dr,cairo_t *cr,int row,int col,int w,int h,float r,float g,float b);
void draw_snake(GtkWidget *dr,cairo_t *cr,Snake s[],int n,Map m[][MAP_LEN]);
void draw_head(GtkWidget *dr,cairo_t *cr,int row,int col,int dir,double rgb[3][3]);
void draw_body(GtkWidget *dr,cairo_t *cr,int row,int col,double rgb[3][3],int dir);
void draw_turn(GtkWidget *dr,cairo_t *cr,int row,int col,double rgb[3][3],int dir);
void draw_detail(cairo_t *cr,int posi[][2],double rgb[3]);
void draw_food(GtkWidget *dr,cairo_t *cr,int row,int col);
void draw_unit(GtkWidget *dr,cairo_t *cr,int row,int col,float r,float g,float b);
//act
int push(Plate *p,int s,int row,int col);
int pop(Plate *p,int s);
void modify(int *r,int *c);
gboolean automove(Plate *p);
void turn_left(Plate *p,int s);
void turn_up(Plate *p,int s);
void turn_right(Plate *p,int s);
void turn_down(Plate *p,int s);
gboolean food(Plate *p);
gboolean erasefood(Map m[MAP_LEN][MAP_LEN]);
//control
void open_menu(Plate *p);
void set_player(cairo_t *cr,int m);
void set_menu(cairo_t *cr);
void arrow_menu(cairo_t *cr,int opt);
void close_menu(Plate *p);
gboolean key_press(GtkWidget *w,GdkEvent *e,Plate *p);
