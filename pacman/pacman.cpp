#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<time.h>
#include<math.h>

int lwall;
int rwall;
int uwall;
int dwall;

int unit;
int game_speed;
int game_status;
int points;
char choice;
char buffer_choice;
int iteration;

int map_color;
int pacman_radius;
int pacman_color;
int pacman_x;
int pacman_y;
int points_color;
int pacman_erase_flag;

struct monster
{
    int x;
    int y;
    int radius;
    int color;
    char choice='d';
    void *image;
    int erase_flag=0;
    int active_flag=0;
};
struct monster monster1,monster2,monster3;
int monster_speed;

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
    char str[10]="POINTS:";
    points=points/2;
    str[8]=(48+points%10);
    points=points/10;
    str[7]=(48+points%10);
    outtextxy(650,300,"GAME OVER.");
    moveto(650,330);
    outtext(str);
    delay(3000);
    closegraph();
    exit(1);
}

void display_rules()
{
    setfillstyle(SOLID_FILL,WHITE);
    setcolor(WHITE);

    outtextxy(725,210,"PACMAN");
    outtextxy(695,240,"PRESS W TO MOVE UP");
    outtextxy(695,270,"PRESS S TO MOVE DOWN");
    outtextxy(695,300,"PRESS A TO MOVE LEFT");
    outtextxy(695,330,"PRESS D TO MOVE RIGHT");
    outtextxy(695,360,"PRESS P TO PAUSE");
    outtextxy(695,390,"PRESS ANY KEY TO CONTINUE");
    getch();
}

void draw_map(short int a[])
{
    int i,j;
    for(i=0;i<31;i++)
    {
      for(j=0;j<28;j++)
      {
          if(a[i*28+j]==1){
          setfillstyle(SOLID_FILL,map_color);
          setcolor(map_color);
          bar(unit*j-unit/2,unit*i-unit/2,unit*j+unit/2,unit*i+unit/2);}
          else{
          setfillstyle(SOLID_FILL,points_color);
          setcolor(points_color);
          circle(unit*j,unit*i,2);}
      }
    }
}

void set_variables()
{
    lwall=20;
    rwall=520;
    uwall=20;
    dwall=520;

    unit=25;
    game_speed=5;
    game_status=1;
    iteration=0;
    points=0;
    choice='d';
    buffer_choice='d';
    map_color=8;
    pacman_radius=unit/2+1;
    pacman_color=10;
    pacman_x=unit*13;
    pacman_y=unit*16;
    points_color=6;
    pacman_erase_flag=0;

    monster_speed=10;
    monster1.x=12*unit;
    monster1.y=13*unit;
    monster1.radius=unit/2+1;
    monster1.color=12;
    monster1.choice='d';
    monster1.active_flag=0;
    monster1.erase_flag=0;
}

void init_game()
{
 set_variables();
 short int map_1[868]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                       1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
                       1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1,
                       1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1,
                       1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                       1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1,
                       1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1,
                       1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,
                       1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,
                       1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,
                       1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,
                       1,1,1,1,1,1,0,1,1,0,1,1,1,0,0,1,1,1,0,1,1,0,1,1,1,1,1,1,
                       1,1,1,1,1,1,0,1,1,0,1,0,0,0,0,0,0,1,0,1,1,0,1,1,1,1,1,1,
                       1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,
                       1,1,1,1,1,1,0,1,1,0,1,0,0,0,0,0,0,1,0,1,1,0,1,1,1,1,1,1,
                       1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,
                       1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,
                       1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,
                       1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,
                       1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
                       1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1,
                       1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1,
                       1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,
                       1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1,
                       1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1,
                       1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1,
                       1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,
                       1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,
                       1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,
                       1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
  initwindow(1920,1080);
  draw_map(&map_1[0]);
}

int detect_pacman_collision(char ch)
{
    if(ch=='a'&&((getpixel(pacman_x-pacman_radius-3,pacman_y-pacman_radius+1)==map_color)||getpixel(pacman_x-pacman_radius-3,pacman_y+pacman_radius-1)==map_color))
        return 1;
    else if(ch=='d'&&((getpixel(pacman_x+pacman_radius+3,pacman_y-pacman_radius+1)==map_color)||getpixel(pacman_x+pacman_radius+3,pacman_y+pacman_radius-1)==map_color))
        return 1;
    else if(ch=='w'&&((getpixel(pacman_x-pacman_radius+1,pacman_y-pacman_radius-3)==map_color)||getpixel(pacman_x+pacman_radius-1,pacman_y-pacman_radius-3)==map_color))
        return 1;
    else if(ch=='s'&&((getpixel(pacman_x-pacman_radius+1,pacman_y+pacman_radius+3)==map_color)||getpixel(pacman_x+pacman_radius-1,pacman_y+pacman_radius+3)==map_color))
        return 1;
    else
        return 0;
}

void move_left()
{
        pacman_x=pacman_x-game_speed;
}

void move_right()
{
        pacman_x=pacman_x+game_speed;
}

void move_up()
{
        pacman_y=pacman_y-game_speed;
}

void move_down()
{
        pacman_y=pacman_y+game_speed;
}

void draw_pacman(int x,int y)
{
    pacman_x=x;
    pacman_y=y;
    if(pacman_erase_flag==1)
    {
    //erasing previous pacman
    setfillstyle(SOLID_FILL,BLACK);
    setcolor(BLACK);
    fillellipse(x,y,pacman_radius,pacman_radius);
    pacman_erase_flag=0;
    }
    else
    {
    //drawing new pacman
    setfillstyle(SOLID_FILL,pacman_color);
    setcolor(pacman_color);
    fillellipse(x,y,pacman_radius,pacman_radius);
    }
}

void update_pacman_position()
{
    //erasing previous pacman
    pacman_erase_flag=1;
    draw_pacman(pacman_x,pacman_y);

    if(buffer_choice=='e'){
    display_score();
    exit(1);}
    else if(buffer_choice=='p'){
        getch();}

    if(detect_pacman_collision(buffer_choice)==0)
    {
        choice=buffer_choice;
        if(buffer_choice=='d')
            move_right();
        else if(buffer_choice=='a')
            move_left();
        else if(buffer_choice=='w')
            move_up();
        else if(buffer_choice=='s')
            move_down();
    }

    else if(detect_pacman_collision(choice)==0)
    {
        if(choice=='d')
            move_right();
        else if(choice=='a')
            move_left();
        else if(choice=='w')
            move_up();
        else if(choice=='s')
            move_down();
    }

}

void check_game_status()
{
if(getpixel(pacman_x+pacman_radius+1,pacman_y)==monster1.color||getpixel(pacman_x-pacman_radius-1,pacman_y)==monster1.color||getpixel(pacman_x,pacman_y+pacman_radius+1)==monster1.color||getpixel(pacman_x,pacman_y-pacman_radius-1)==monster1.color)
    display_score();
}

void check_points()
{
if(getpixel(pacman_x+pacman_radius+1,pacman_y)==points_color||getpixel(pacman_x-pacman_radius-1,pacman_y)==points_color||getpixel(pacman_x,pacman_y+pacman_radius+1)==points_color||getpixel(pacman_x,pacman_y-pacman_radius-1)==points_color)
points++;
}

void draw_monster(int x,int y,int monster_no)
{
    if(monster_no==1)
    {
    monster1.x=x;
    monster1.y=y;
    if(monster1.erase_flag==1)
    {
    //erasing previous monster1
    setfillstyle(SOLID_FILL,BLACK);
    setcolor(BLACK);
    fillellipse(x,y,monster1.radius,monster1.radius);
    monster1.erase_flag=0;
    }
    else
    {
    //storing image before monster was present
    monster1.image=malloc((int)imagesize(monster1.x-monster1.radius,monster1.y-monster1.radius,monster1.x+monster1.radius,monster1.y+monster1.radius));
    getimage(monster1.x-monster1.radius,monster1.y-monster1.radius,monster1.x+monster1.radius,monster1.y+monster1.radius,monster1.image);
    //drawing new monster1
    setfillstyle(SOLID_FILL,monster1.color);
    setcolor(monster1.color);
    fillellipse(x,y,monster1.radius,monster1.radius);
    }
    }
}

char make_decision(int monster_no)
{
    if(monster_no==1)
    {
        if(pacman_x-monster1.x>0&&((getpixel(monster1.x+monster1.radius+1,monster1.y-monster1.radius+1)!=map_color)&&getpixel(monster1.x+monster1.radius+1,monster1.y+monster1.radius-1)!=map_color))
        monster1.choice='d';
        else if(pacman_y-monster1.y<0&&((getpixel(monster1.x-monster1.radius+1,monster1.y-monster1.radius-1)!=map_color)&&getpixel(monster1.x+monster1.radius-1,monster1.y-monster1.radius-1)!=map_color))
        monster1.choice='w';
        else if(pacman_x-monster1.x<0&&((getpixel(monster1.x-monster1.radius-1,monster1.y-monster1.radius+1)!=map_color)&&getpixel(monster1.x-monster1.radius-1,monster1.y+monster1.radius-1)!=map_color))
        monster1.choice='a';
        else if(pacman_y-monster1.y>0&&((getpixel(monster1.x-monster1.radius+1,monster1.y+monster1.radius+1)!=map_color)&&getpixel(monster1.x+monster1.radius-1,monster1.y+monster1.radius+1)!=map_color))
        monster1.choice='s';
        else
        {
            /*if(((getpixel(monster1.x-monster1.radius-1,monster1.y-monster1.radius+1)!=map_color)&&getpixel(monster1.x-monster1.radius-1,monster1.y+monster1.radius-1)!=map_color))
                monster1.choice='a';
            else if(((getpixel(monster1.x+monster1.radius+1,monster1.y-monster1.radius+1)!=map_color)&&getpixel(monster1.x+monster1.radius+1,monster1.y+monster1.radius-1)!=map_color))
                monster1.choice='d';
            else if(((getpixel(monster1.x-monster1.radius+1,monster1.y+monster1.radius+1)!=map_color)&&getpixel(monster1.x+monster1.radius-1,monster1.y+monster1.radius+1)!=map_color))
                monster1.choice='s';
            else if(((getpixel(monster1.x-monster1.radius+1,monster1.y-monster1.radius-1)!=map_color)&&getpixel(monster1.x+monster1.radius-1,monster1.y-monster1.radius-1)!=map_color))
                monster1.choice='w';
            else*/
                monster1.choice=' ';
        }
        return monster1.choice;
    }
}

void update_monster_position(int monster_no)
{
     if(monster_no==1)
     {
         //erasing previous monster1
         monster1.erase_flag=1;
         draw_monster(monster1.x,monster1.y,1);

         //putting previous image
         if(monster1.image!=NULL){
         putimage(monster1.x-monster1.radius,monster1.y-monster1.radius,monster1.image,COPY_PUT);
         free(monster1.image);}

         if(monster1.active_flag==0)
         {
             if(monster1.x!=14*unit&&monster1.y!=11*unit){
             monster1.x=monster1.x+game_speed;
             monster1.y=monster1.y-game_speed;}
             else{
             monster1.y=monster1.y-unit;
             monster1.active_flag=1;}
         }
         else if(monster1.active_flag==1)
         {
             monster1.choice=make_decision(1);
             if(monster1.choice=='w')
                monster1.y=monster1.y-monster_speed/2;
             else if(monster1.choice=='s')
                monster1.y=monster1.y+monster_speed/2;
             else if(monster1.choice=='d')
                monster1.x=monster1.x+monster_speed/2;
             else if(monster1.choice=='a')
                monster1.x=monster1.x-monster_speed/2;
         }
     }
}

int main()
{
    init_game();
    delay(10/game_speed);
    while(1)
    {
        iteration++;
        if(kbhit())
        buffer_choice=getch();

        update_pacman_position();
        draw_pacman(pacman_x,pacman_y);

        if(iteration%2==0){
        update_monster_position(1);
        draw_monster(monster1.x,monster1.y,1);}

        check_game_status();
        if(game_status==0)
        display_score();

        check_points();

        delay(10/game_speed);
    }
    return 0;
}
