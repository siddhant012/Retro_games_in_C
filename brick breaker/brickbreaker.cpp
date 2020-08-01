#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>

int lwall=20;
int rwall=1020;
int uwall=20;
int dwall=520;

int ball_x=(rwall-lwall)/2;
int ball_y=(dwall-uwall)/2;
int ball_r=10;
int ball_x_speed=0;
int ball_y_speed=5;

int points=0;
int game_status=0;
int game_speed=20;
int choice;

int small_block_dimension=10;
int block_thickness=2*small_block_dimension;

int striker_length=100;
int striker_width=10;
int striker_x=(rwall-lwall)/2;
int striker_y=dwall-striker_width;
int striker_x_speed=40;

void timedelay(int msec)
{
    clock_t c=clock();
    while(clock()-c<=msec);
}

int random(int ll,int ul)
{
    int num=ll+(rand()%(ul-ll+1));
    return num;
}

void draw_boundary()
{
    setfillstyle(SOLID_FILL,WHITE);
    setcolor(WHITE);
    int points[]={lwall,uwall,lwall,dwall,rwall,dwall,rwall,uwall,lwall,uwall};
    drawpoly(5,points);
}

void display_score()
{
    cleardevice();
    setfillstyle(SOLID_FILL,WHITE);
    setcolor(WHITE);
    char str[9]="POINTS:";
    str[7]=(48+points);
    outtextxy(650,300,"GAME OVER.");
    moveto(650,330);
    outtext(str);
    timedelay(3000);
    closegraph();
    exit(1);
}

void display_rules()
{
    outtextxy(650,300,"PRESS A TO MOVE LEFT");
    outtextxy(650,330,"PRESS D TO MOVE RIGHT");
    outtextxy(650,360,"PRESS E TO EXIT");
    outtextxy(650,390,"PRESS P TO PAUSE");
    outtextxy(650,420,"PRESS ANY KEY TO CONTINUE");
    getch();
}
void draw_blocks()
{
    setfillstyle(SOLID_FILL,BLUE);
    setcolor(BLUE);
    int i,j;
    for(i=0;i<(int)(block_thickness/small_block_dimension);i++)
    {
        for(j=0;j<((rwall-lwall)/small_block_dimension);j++)
        {
        bar(lwall+(2*j+1)*(small_block_dimension/2)-small_block_dimension/2,uwall+(2*i+1)*(small_block_dimension/2)-small_block_dimension/2,lwall+(2*j+1)*(small_block_dimension/2)+small_block_dimension/2,uwall+(2*i+1)*(small_block_dimension/2+small_block_dimension/2));
        }
    }
}

void draw_striker(int x,int y)
{
    //erasing previous striker
    if(choice=='a')
    {
    setfillstyle(SOLID_FILL,BLACK);
    setcolor(BLACK);
    bar(x+striker_x_speed-(striker_length/2),y-striker_width,x+striker_x_speed+(striker_length/2),y+striker_width);
    }
    else if(choice=='d')
    {
    setfillstyle(SOLID_FILL,BLACK);
    setcolor(BLACK);
    bar(x-striker_x_speed-(striker_length/2),y-striker_width,x-striker_x_speed+(striker_length/2),y+striker_width);
    }

    striker_x=x;
    striker_y=y;
    setfillstyle(SOLID_FILL,YELLOW);
    setcolor(YELLOW);
    bar(x-(striker_length/2),y-striker_width,x+(striker_length/2),y+striker_width);
}

void move_left()
{
    striker_x=striker_x-striker_x_speed;
    if(striker_x<lwall+striker_length/2)
        striker_x=lwall+striker_length/2;
}

void move_right()
{
    striker_x=striker_x+striker_x_speed;
    if(striker_x>rwall-striker_length/2)
        striker_x=rwall-striker_length/2;
}

void draw_ball(int x,int y,int r)
{

    //erasing previous ball
    setfillstyle(SOLID_FILL,BLACK);
    setcolor(BLACK);
    circle(ball_x-ball_x_speed,ball_y-ball_y_speed,ball_r);
    fillellipse(ball_x-ball_x_speed,ball_y-ball_y_speed,ball_r,ball_r);

    ball_x=x;
    ball_y=y;
    ball_r=r;
    setfillstyle(SOLID_FILL,RED);
    setcolor(RED);
    circle(ball_x,ball_y,ball_r);
    fillellipse(ball_x,ball_y,ball_r,ball_r);
}

void ball_motion()
{
    ball_x=ball_x+ball_x_speed;
    ball_y=ball_y+ball_y_speed;

    //erasing previous ball before collisions
    setfillstyle(SOLID_FILL,BLACK);
    setcolor(BLACK);
    circle(ball_x-ball_x_speed,ball_y-ball_y_speed,ball_r);
    fillellipse(ball_x-ball_x_speed,ball_y-ball_y_speed,ball_r,ball_r);

    if(ball_x+ball_r>=rwall||ball_x-ball_r<=lwall)
    {
        ball_x_speed=ball_x_speed*-1;
    }
    if(ball_y+ball_r>=dwall-striker_width&&ball_x<=striker_x+striker_length/2&&ball_x>=striker_x-striker_length/2)
    {
        if(choice=='a')
        ball_x_speed=ball_x_speed-5;
        else if(choice=='d')
        ball_x_speed=ball_x_speed+5;
        ball_y_speed=ball_y_speed*-1;
        points++;
    }
    if(ball_y-ball_r<=uwall)
    {
        ball_y_speed=ball_y_speed*-1;
    }
    if(ball_y+ball_r>=dwall)
    {
        display_score();
    }
}
int main()
{
    int i,j;
    initwindow(1920,1080);
    display_rules();
    cleardevice();
    draw_blocks();
    while(1)
    {
    draw_boundary();
    draw_striker(striker_x,striker_y);
    ball_motion();
    draw_ball(ball_x,ball_y,ball_r);
    if(kbhit())
    {
        choice=getch();
        switch(choice)
        {
            case 'a':move_left();break;
            case 'd':move_right();break;
            case 'e':display_score();break;
            case 'p':getch();break;
            default:break;
        }
    }
    timedelay(600/game_speed);
    }
    getch();
    closegraph();
    return 0;
}




