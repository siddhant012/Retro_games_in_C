#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#include<math.h>
#include<string.h>

int lwall=100;
int rwall=10000;
int uwall=70;
int dwall=700;

int game_status=1;
int points=0;

int x_speed=20;
int d_acc=5;
int u_acc=-70;
int iteration=0;

int bird_x=100;
int bird_y=(dwall-uwall)/2;
int bird_r=15;
int bird_y_speed=0;

int obstacle_height_ll=200;
int obstacle_height_ul=500;
int obstacle_width_ll=25;
int obstacle_width_ul=50;
int obstcale_limit=5;
int obstacle_spawn_distance=1300;
int obstacle_density=(obstacle_spawn_distance+200)/5;
struct obstacle
{
int width;
int height;
int pos;
struct obstacle *next;
};
struct obstacle *head=NULL,*traversal;

void draw_obstacle();
void spawn_obstacle();
void delete_obstacle();

void timedelay(int sec)
{
    clock_t c=clock();
    while(clock()-c<=sec);
}
int random(int ll,int ul)
{
    int num=ll+(rand()%(ul-ll+1));
    return num;
}
void draw_boundary()
{
cleardevice();
setfillstyle(SOLID_FILL,WHITE);
setcolor(WHITE);
int points[]={lwall,uwall,rwall,uwall,rwall,dwall,lwall,dwall,lwall,uwall};
drawpoly(5,points);
}
void draw_bird(int x,int y,int r)
{
    bird_x=x;
    bird_y=y;
    bird_r=r;
    setfillstyle(SOLID_FILL,BLUE);
    setcolor(BLUE);
    circle(bird_x,bird_y,bird_r);
    fillellipse(bird_x,bird_y,bird_r,bird_r);
}
void move()
{
    cleardevice();
    rwall=rwall-x_speed;
    lwall=lwall-x_speed;
    draw_boundary();
    iteration=iteration+x_speed;

    traversal=head;
    while(traversal!=NULL)
    {
        traversal->pos=traversal->pos-x_speed;
        traversal=traversal->next;
    }
    draw_obstacle();
}
void fly()
{
    if(bird_y==uwall+bird_r){bird_y=uwall+bird_r;return;}
    bird_y_speed=bird_y_speed+u_acc;
    bird_y=bird_y+bird_y_speed;
    if(bird_y-bird_r<=uwall+25){bird_y=uwall+bird_r;bird_y_speed=0;}
    cleardevice();
    draw_boundary();
    draw_bird(bird_x,bird_y,bird_r);
}
void down_acc_effect()
{
    bird_y_speed=bird_y_speed+d_acc;
    bird_y=bird_y+bird_y_speed;
    if(bird_y-bird_r<=uwall){bird_y=uwall+bird_r;bird_y_speed=0;}
    if(bird_y+bird_r>=dwall){bird_y=dwall-bird_r;bird_y_speed=0;game_status=0;}
    cleardevice();
    draw_boundary();
    draw_bird(bird_x,bird_y,bird_r);
    draw_obstacle();
}
void draw_obstacle()
{
    setfillstyle(SOLID_FILL,YELLOW);
    setcolor(YELLOW);
    traversal=head;
    while(traversal!=NULL)
    {
        bar(traversal->pos-(traversal->width/2),dwall,traversal->pos+(traversal->width/2),dwall-traversal->height);
        traversal=traversal->next;
    }
}
void spawn_obstacle()
{
    if(head==NULL)
    {
        head=(struct obstacle *)malloc(sizeof(struct obstacle));
        head->width=random(obstacle_width_ll,obstacle_width_ul);
        head->height=random(obstacle_height_ll,obstacle_height_ul);
        head->pos=bird_x+obstacle_spawn_distance+(head->width/2);
        head->next=NULL;
    }
    else
    {
        struct obstacle *new_obstacle;
        new_obstacle=(struct obstacle*)malloc(sizeof(struct obstacle));
        new_obstacle->width=random(obstacle_width_ll,obstacle_width_ul);
        new_obstacle->height=random(obstacle_height_ll,obstacle_height_ul);
        new_obstacle->pos=bird_x+obstacle_spawn_distance+(head->width/2);
        new_obstacle->next=NULL;
        traversal=head;
        while(traversal->next!=NULL)
            traversal=traversal->next;
        traversal->next=new_obstacle;
    }
}
void delete_obstacle()
{
    head=head->next;
    points++;
}
void update_game_status()
{
    if(bird_y-bird_r==uwall){game_status=0;}
    else if(bird_y+bird_r==dwall){game_status=0;}
    else
    {
        traversal=head;
        while(traversal!=NULL)
        {
            if(bird_y-bird_r>=dwall-traversal->height&&bird_y+bird_r<=dwall&&bird_x+bird_r<=traversal->pos+(traversal->width/2)&&bird_x-bird_r>=traversal->pos-(traversal->width/2))
                game_status=0;
                traversal=traversal->next;
        }
    }
}
void display_score()
{
    cleardevice();
    char str[]="POINTS:";
    str[7]=(48+points);
    outtextxy(650,300,"GAME OVER.");
    moveto(650,330);
    outtext(str);
    timedelay(3000);
    closegraph();
}
void display_rules()
{
    outtextxy(650,300,"PRESS W TO JUMP");
    outtextxy(650,330,"PRESS E TO EXIT");
    outtextxy(650,360,"PRESS P TO PAUSE");
    outtextxy(650,390,"PRESS ANY KEY TO CONTINUE");
    getch();
}
int main()
{
    initwindow(1920,1080,"");
    display_rules();
    cleardevice();
    char choice;

    while(1)
    {
        if(!game_status){display_score();return 0;}
        if(kbhit())
        {
            choice=getch();
            switch(choice)
            {
                case 'w':fly();break;
                case 'p':getch();break;
                case 'e':closegraph();return 0;break;
                default:break;
            }
        }
        update_game_status();
        if(iteration==obstacle_density)
        {
            iteration=0;
            if(head!=NULL&&head->pos<=bird_x-50)
                delete_obstacle();
            spawn_obstacle();

        }

        timedelay(100/x_speed);
        down_acc_effect();
        update_game_status();
        timedelay(1000/x_speed);
        move();
        update_game_status();
    }
    timedelay(3000);
    closegraph();
    return 0;
}
