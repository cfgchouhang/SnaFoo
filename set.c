#include"snake.h"

void init_plate(Plate *p,GtkWidget *fixed,int w,int h)
{
	int i;
	p->dr = gtk_drawing_area_new();
	gtk_widget_set_size_request(p->dr,w,h);
	gtk_widget_set_app_paintable(p->dr,TRUE);
	gtk_fixed_put(GTK_FIXED(fixed),p->dr,0,35);
	p->state = 0;
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
	p->snake[0].color[0][1] = 1;
	p->snake[0].color[1][1] = 0.73;
	p->snake[0].color[2][1] = 0.58;
	
	p->snake[1].color[0][2] = 1;
	p->snake[1].color[1][2] = 0.7;
	p->snake[1].color[2][2] = 0.5;
	
}

void new_game(GtkWidget *btn,Plate *p)
{
	int i,j;
	if(p->cr)
		cairo_destroy(p->cr);
	p->cr = gdk_cairo_create(gtk_widget_get_window(p->dr));
	p->state = 1;
    p->score = 0;
	p->snake[0].dir = 1;
	p->snake[0].dirx = 1;
	p->snake[0].diry = 0;
	
	p->snake[1].dir = 0;
	p->snake[1].dirx = -1;
	p->snake[1].diry = 0;
	p->score = 0;
	
	for(i=0;i<SNAKE_NUM;i++){
		p->snake[i].h = 0;
		p->snake[i].t = 0;
	}
	draw(p->dr,p->cr,0,0,WIDTH,HEIGHT,0,0,0);
    set_map(p->dr,p->cr,p->map);
    for(i=12;i<19;i++)
		push(p,0,19,i);
	if(SNAKE_NUM>1)
	    for(i=18;i>=12;i--)
	    	push(p,1,20,i);
	
	draw_snake(p->dr,p->cr,p->snake);
	food(p);
}

void set_map(GtkWidget *dr,cairo_t *cr,Map m[][MAP_LEN])
{
    FILE *state,*map;
    char load[10],load_map[20];
    int i,j;
    state = fopen("./Data/game_state","r");
    fscanf(state,"%s",load);
    strcpy(load_map,"./Data/map/");
    strcat(load_map,load);
    map = fopen(load_map,"r");
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

void pause_game(GtkWidget *btn,gpointer data)
{
	Plate *p = (Plate *)data;
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(btn)))
		p->state = 3;
	else 
		p->state = 1;
}

void showscore(GtkWidget *l,int score)
{
	char s[100];
	sprintf(s,"<span font_desc=\"12\"\
		foreground=\"black\">Score : %d</span>",score);
	gtk_label_set_markup(GTK_LABEL(l),s);
}

/*gboolean expose(GtkWidget *widget,cairo_t *cr,Plate *p)
{
	p->cr = cr;
	if(p->snake.h!=p->snake.t)
		draw_snake(p->dr,p->cr,&p->snake);
	return TRUE;
}*/

