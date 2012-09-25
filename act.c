#include"snake.h"

int push(Plate *p,int s,int row,int col)
{
    if((p->snake[s].h+1)%SNAKE_MAX!=p->snake[s].t){
        p->snake[s].h = (p->snake[s].h+1)%SNAKE_MAX;
        p->snake[s].posi[p->snake[s].h][0] = row;
        p->snake[s].posi[p->snake[s].h][1] = col;
        p->map[row][col].exist = 1;
        return 1;
    }
    return -1;
}

int pop(Plate *p,int s)
{
    if(p->snake[s].h!=p->snake[s].t){
        p->snake[s].t = (p->snake[s].t+1)%SNAKE_MAX;
        int row = p->snake[s].posi[p->snake[s].t][0];
        int col = p->snake[s].posi[p->snake[s].t][1];
        p->map[row][col].exist = 0;
        return p->snake[s].t;
    }
    return -1;
}

void modify(int *r,int *c)
{
    *r %= MAP_LEN;
    *c %= MAP_LEN;
    if(*r<0)
        *r += MAP_LEN;
    if(*c<0)
        *c += MAP_LEN;
}

gboolean automove(Plate *p)
{
    if(!p->state){
        g_source_remove(p->timeoutid);
        p->interval = 150;
        p->timeoutid =
                g_timeout_add(p->interval,(GSourceFunc)automove,p);
        return TRUE;
    }
    if(p->state==3)
        return TRUE;
    while(p->state==2);
    p->state = 2;
    int i;
    for(i=0;i<p->mode;i++){
    pop(p,i);
    int headr = p->snake[i].posi[p->snake[i].h][0];
    int headc = p->snake[i].posi[p->snake[i].h][1];
    int tailr = p->snake[i].posi[p->snake[i].t][0];
    int tailc = p->snake[i].posi[p->snake[i].t][1];
    int r,c;

    r = headr+p->snake[i].diry;
    c = headc+p->snake[i].dirx;
    modify(&r,&c);
    if(p->map[r][c].exist){
        p->state = 0;
        show_result(p,"Game Over");
        return TRUE;
    }
    draw_body(p->dr,p->cr,headr,headc,p->snake[i].color,p->map[headr][headc].dir);
    push(p,i,r,c);
    draw_head(p->dr,p->cr,r,c,p->snake[i].dir,p->snake[i].color);
    if(p->map[r][c].food){
        p->score += 2;
        show_score(p->label,p->score);
        if(p->score>=p->pass){
            p->state = 0;
            p->win = 1;
            show_result(p,"Game Pass");
            return TRUE;
        }
        food(p);
        if(p->interval>50){
            g_source_remove(p->timeoutid);
            p->interval -= 20;
            p->timeoutid =
                g_timeout_add(p->interval,(GSourceFunc)automove,p);
        }
    }
    if(!p->map[tailr][tailc].food){
        draw_unit(p->dr,p->cr,tailr*UNIT,tailc*UNIT,0,0,0);
    }
    else{
        p->map[tailr][tailc].food = 0;
        p->snake[i].t--;
        if(p->snake[i].t<0)
            p->snake[i].t += SNAKE_MAX;
        p->map[tailr][tailc].exist = 1;
    }
    if(p->map[tailr][tailc].dir!=-1){
        p->map[tailr][tailc].dir = -1;
    }
    }
    p->state = 1;
    return TRUE;
}

gboolean key_press(GtkWidget *w,GdkEvent *e,Plate *p)
{
    guint keyval = ((GdkEventKey *)e)->keyval;
    //printf("%x\n",keyval);
    
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
        if(p->inmenu)
            close_menu(p);
        else
            open_menu(p);
    }
    if(!p->state||p->state==3)return TRUE;
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

void turn_left(Plate *p,int s)
{
    int headr = p->snake[s].posi[p->snake[s].h][0];
    int headc = p->snake[s].posi[p->snake[s].h][1];
    int d = p->snake[s].dir;
    if(!p->map[headr][headc-1].exist){
        if(d==2)
            p->map[headr][headc].dir = 0;
        else if(d==3)
            p->map[headr][headc].dir = 3;
        p->snake[s].dir = 0;
        p->snake[s].dirx = -1;
        p->snake[s].diry = 0;
    }
}

void turn_right(Plate *p,int s)
{
    int headr = p->snake[s].posi[p->snake[s].h][0];
    int headc = p->snake[s].posi[p->snake[s].h][1];
    int d = p->snake[s].dir;
    if(!p->map[headr][headc+1].exist){
        if(d==2)
            p->map[headr][headc].dir = 1;
        else if(d==3)
            p->map[headr][headc].dir = 2;
        p->snake[s].dir = 1;
        p->snake[s].dirx = +1;
        p->snake[s].diry =  0;
    }
}

void turn_up(Plate *p,int s)
{
    int headr = p->snake[s].posi[p->snake[s].h][0];
    int headc = p->snake[s].posi[p->snake[s].h][1];
    int d = p->snake[s].dir;
    if(!p->map[headr-1][headc].exist){
        if(d==0)
            p->map[headr][headc].dir = 2;
        else if(d==1)
            p->map[headr][headc].dir = 3;
        p->snake[s].dir = 2;
        p->snake[s].dirx = 0;
        p->snake[s].diry = -1;
    }
}

void turn_down(Plate *p,int s)
{
    int headr = p->snake[s].posi[p->snake[s].h][0];
    int headc = p->snake[s].posi[p->snake[s].h][1];
    int d = p->snake[s].dir;
    if(!p->map[headr+1][headc].exist){
        if(d==0)
            p->map[headr][headc].dir = 1;
        else if(d==1)
            p->map[headr][headc].dir = 0;
        p->snake[s].dir = 3;
        p->snake[s].dirx =  0;
        p->snake[s].diry = +1;
    }
}

gboolean food(Plate *p)
{
    int i,j,a;
    do{
    a = 0;
    srand(time(NULL));
    i = rand()%30;
    srand(time(NULL));
    j = rand()%30;
    if(i<29&&p->map[i+1][j].exist)
        a++;
    if(i>0&&p->map[i-1][j].exist)
        a++;
    if(j<29&&p->map[i][j+1].exist)
        a++;
    if(j>0&&p->map[i][j-1].exist)
        a++;
    }while(p->map[i][j].exist||a>2);
    draw_food(p->dr,p->cr,i,j);
    p->map[i][j].food = 1;
    return TRUE;
}

