#include"snake.h"

void init_plate(Plate *p,GtkWidget *fixed,int w,int h)
{
    int i,j;
    p->dr = gtk_drawing_area_new();
    gtk_widget_set_size_request(p->dr,w,h);
    gtk_widget_set_app_paintable(p->dr,TRUE);
    gtk_fixed_put(GTK_FIXED(fixed),p->dr,0,0);
    p->state = 0;
    p->mode = p->tmpm = 1;
    p->menu = 0;
    p->inmenu = 0;
    p->interval = 150;
    for(i=0;i<SNAKE_NUM;i++){
        p->snake[i].h = 0;
        p->snake[i].t = 0; 
    }
    for(i=0;i<3;i++){
        p->snake[0].color[i][0] = 0;
        p->snake[0].color[i][2] = 0;
        p->snake[1].color[i][0] = 0;
        p->snake[1].color[i][1] = 0;
    }
    for(i=0;i<30;i++)
        for(j=0;j<30;j++)
            p->map[i][j].food = 0;
    p->snake[0].color[0][1] = 1;
    p->snake[0].color[1][1] = 0.73;
    p->snake[0].color[2][1] = 0.58;
    p->snake[1].color[0][2] = 1;
    p->snake[1].color[1][2] = 0.7;
    p->snake[1].color[2][2] = 0.5;
    
}

void new_game(/*GtkWidget *btn,*/Plate *p)
{
    int i,j;
    p->mode = p->tmpm;
    p->menu = 0;
    p->inmenu = 0;
    p->cr = gdk_cairo_create(gtk_widget_get_window(p->dr));
    p->state = 1;
    p->win = 0;
    p->score = 0;
    p->snake[0].dir = 1;
    p->snake[0].dirx = 1;
    p->snake[0].diry = 0;
    p->snake[1].dir = 1;
    p->snake[1].dirx = 1;
    p->snake[1].diry = 0;
    p->score = 0;
    show_score(p->label,p->score);
    /*
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(p->mbtn)))
        p->mode = 2;
    else
        p->mode = 1;
    */
    for(i=0;i<SNAKE_NUM;i++){
        p->snake[i].h = 0;
        p->snake[i].t = 0;
    }
    draw(p->cr,0,0,WIDTH,HEIGHT,0,0,0);
    set_map_snake(p->dr,p->cr,p);
    draw_snake(p->dr,p->cr,p->snake,p->mode,p->map);
    food(p);
}

void win_game()
{
    FILE *s = fopen("./Data/game_state","r");
    FILE *o = fopen("./Data/game_state","w");
    char c[10];
    fscanf(s,"%s",c);
    fprintf(s,"%s","map");
}

void response(Plate *p){
    gtk_widget_destroy(p->dialog);
    new_game(p);
    //if(p->win){
       // win_game();
       // new_game(/*p->btn[0],*/p);
    //}
}
void show_result(Plate *p,char *m)
{
    GtkWidget *area,*label;
    p->dialog = gtk_dialog_new_with_buttons("",NULL,GTK_DIALOG_MODAL,
        "OK",0,NULL);
    area = gtk_dialog_get_content_area(GTK_DIALOG(p->dialog));
    label = gtk_label_new(m);
    g_signal_connect_swapped(p->dialog,"response",
        G_CALLBACK(response),p);
    gtk_container_add(GTK_CONTAINER(area),label);
    gtk_widget_show_all(p->dialog);
}

void pause_game(/*GtkWidget *btn,*/gpointer data)
{
    int *s = (int *)data;
    if(!(*s))return ;
    *s = *s==1 ? 3:1;
    /*
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(btn)))
        *s = 3;
    else 
        *s = 1;
    */
}

void change_mode(GtkWidget *btn,Plate *p)
{
    if(!p->state){
        p->mode = p->mode==1 ? 2:1;
        /*
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(btn))) 
            p->mode = 2;
        else
            p->mode = 1;
        */
    }
}

void set_map_snake(GtkWidget *dr,cairo_t *cr,Plate *p)
{
    FILE *state,*map;
    Map (*m)[MAP_LEN] = p->map;
    char load[10],load_map[20];
    int i,j,k;
    state = fopen("./Data/game_state","r");
    fscanf(state,"%s",load);
    strcpy(load_map,"./Data/map/");
    strcat(load_map,load);
    map = fopen(load_map,"r");
    fscanf(map,"%d %d %d",&i,&j,&k);
    while(j<k)
        push(p,0,i,j++);
    if(p->mode==2){
        fscanf(map,"%d %d %d",&i,&j,&k);
        while(j<k)
            push(p,1,i,j++);
    }
    else
        fseek(map,9,SEEK_CUR);
    fscanf(map,"%d",&p->pass);
    for(i=0;i<MAP_LEN;i++){
        for(j=0;j<MAP_LEN;j++){
            fscanf(map,"%1d",&m[i][j].exist);
            if(m[i][j].exist)
                draw_unit(dr,cr,i*UNIT,j*UNIT,0.645,0.645,0.707);
            m[i][j].food = 0;
            m[i][j].dir = -1;
        }
    }
}

void show_score(GtkWidget *l,int score)
{
    char s[100];
    sprintf(s,"<span font_desc=\"12\"\
        foreground=\"black\">Score : %d</span>",score);
    gtk_label_set_markup(GTK_LABEL(l),s);
}


