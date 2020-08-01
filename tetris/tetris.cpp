#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#include<math.h>

int lwall=20;
int rwall=1020;
int uwall=20;
int dwall=520;

int unit=50;
int angle=0;
int current_block_lane;
int lanes=(rwall-lwall)/unit;
int lane_height[20+3];
int current_block_top_points[3];
int current_block_bottom_points[3];
int current_block_x;
int current_block_y;
int shape;
int erase_flag=0;
int current_block_color=7;
int game_status=1;


int game_speed=1;
int points=0;
char choice;


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
    outtextxy(695,210,"TETRIS");
    outtextxy(650,240,"PRESS J TO MOVE LEFT");
    outtextxy(650,270,"PRESS L TO MOVE RIGHT");
    outtextxy(650,300,"PRESS A TO ROTATE LEFT");
    outtextxy(650,330,"PRESS D TO ROTATE RIGHT");
    outtextxy(650,360,"PRESS S TO SPEED UP THE BLOCK");
    outtextxy(650,390,"PRESS E TO EXIT");
    outtextxy(650,420,"PRESS P TO PAUSE");
    outtextxy(650,450,"PRESS ANY KEY TO CONTINUE");
    getch();
}

void draw_block(int shape_no,int angle,int x,int y)
{
    //angle can be 0,1,2or 3
    current_block_x=x;
    current_block_y=y;

    setfillstyle(SOLID_FILL,current_block_color);
    setcolor(current_block_color);
    if(erase_flag==1)
    {
        setfillstyle(SOLID_FILL,BLACK);
        setcolor(BLACK);
        erase_flag=0;
    }

    if(shape_no==1)
    {
        bar(x-(3*unit/2),y-(3*unit/2),x+(3*unit/2),y+(3*unit/2));
    }
    else if(shape_no==2)
    {
        if(angle==0||angle==2)
            bar(x-(unit/2),y-(3*unit/2),x+(unit/2),y+(3*unit/2));
        else if(angle==1||angle==3)
            bar(x-(3*unit/2),y-(unit/2),x+(3*unit/2),y+(unit/2));
    }
    else if(shape_no==3)
    {
        if(angle==0){
            bar(x-(unit/2),y-(3*unit/2),x+(unit/2),y+(3*unit/2));
            bar(x-(3*unit/2),y-(3*unit/2),x-(unit/2),y-(unit/2));}
        else if(angle==1){
            bar(x-(3*unit/2),y-(unit/2),x+(3*unit/2),y+(unit/2));
            bar(x-(3*unit/2),y+(3*unit/2),x-(unit/2),y-(unit/2));}
        else if(angle==2){
            bar(x-(unit/2),y-(3*unit/2),x+(unit/2),y+(3*unit/2));
            bar(x+(unit/2),y+(unit/2),x+(3*unit/2),y+(3*unit/2));}
        else if(angle==3){
            bar(x-(3*unit/2),y-(unit/2),x+(3*unit/2),y+(unit/2));
            bar(x+(unit/2),y-(unit/2),x+(3*unit/2),y-(3*unit/2));}
    }
    else if(shape_no==4)
    {
        if(angle==0){
            bar(x-(unit/2),y-(3*unit/2),x+(unit/2),y+(3*unit/2));
            bar(x+(unit/2),y-(unit/2),x+(3*unit/2),y-(3*unit/2));}
        else if(angle==1){
            bar(x-(3*unit/2),y-(unit/2),x+(3*unit/2),y+(unit/2));
            bar(x-(3*unit/2),y-(3*unit/2),x-(unit/2),(y-unit/2));}
        else if(angle==2){
            bar(x-(unit/2),y-(3*unit/2),x+(unit/2),y+(3*unit/2));
            bar(x-(3*unit/2),y+(3*unit/2),x-(unit/2),y+(unit/2));}
        else if(angle==3){
            bar(x-(3*unit/2),y-(unit/2),x+(3*unit/2),y+(unit/2));
            bar(x+(unit/2),y+(unit/2),x+(3*unit/2),y+(3*unit/2));}
    }
    else if(shape_no==5)
    {
        if(angle==0){
            bar(x-(unit/2),y-(3*unit/2),x+(unit/2),y+(3*unit/2));
            bar(x+(unit/2),y+(unit/2),x+(3*unit/2),y-(unit/2));}
        else if(angle==1){
            bar(x-(3*unit/2),y-(unit/2),x+(3*unit/2),y+(unit/2));
            bar(x-(unit/2),y-(unit/2),x+(unit/2),y-(3*unit/2));}
        else if(angle==2){
            bar(x-(unit/2),y-(3*unit/2),x+(unit/2),y+(3*unit/2));
            bar(x-(3*unit/2),y+(unit/2),x-(unit/2),y-(unit/2));}
        else if(angle==3){
            bar(x-(3*unit/2),y-(unit/2),x+(3*unit/2),y+(unit/2));
            bar(x-(unit/2),y+(3*unit/2),x+(unit/2),y+(unit/2));}
    }
}

void rotate_left()
{
    angle++;
    if(angle==4)
        angle=0;
}

void rotate_right()
{
    angle--;
    if(angle==-1)
        angle=3;
}

void move_down()
{
   current_block_y=current_block_y+1;
}

void spawn_block()
{
    shape=random(1,5);
    current_block_lane=random(1,20);
    current_block_color=random(1,14);
    angle=0;
    current_block_x=lwall+(current_block_lane-1)*unit+unit/2;
    current_block_y=uwall-(3*unit/2);
}

void erase_previous_block()
{
    //erasing previous block
   erase_flag=1;
   draw_block(shape,angle,current_block_x,current_block_y);
}

void assign_block_high_low_points()
{
    if(shape==1){
        current_block_top_points[0]=current_block_y-(3*unit/2);
        current_block_top_points[1]=current_block_y-(3*unit/2);
        current_block_top_points[2]=current_block_y-(3*unit/2);

        current_block_bottom_points[0]=current_block_y+(3*unit/2);
        current_block_bottom_points[1]=current_block_y+(3*unit/2);
        current_block_bottom_points[2]=current_block_y+(3*unit/2);}
    else if(shape==2)
    {
        if(angle==0||angle==2){
            current_block_top_points[0]=0;
            current_block_top_points[1]=current_block_y-(3*unit/2);
            current_block_top_points[2]=0;

            current_block_bottom_points[0]=0;
            current_block_bottom_points[1]=current_block_y+(3*unit/2);
            current_block_bottom_points[2]=0;}
        else if(angle==1||angle==3){
            current_block_top_points[0]=current_block_y-(unit/2);
            current_block_top_points[1]=current_block_y-(unit/2);
            current_block_top_points[2]=current_block_y-(unit/2);

            current_block_bottom_points[0]=current_block_y+(unit/2);
            current_block_bottom_points[1]=current_block_y+(unit/2);
            current_block_bottom_points[2]=current_block_y+(unit/2);}
    }
    else if(shape==3)
    {
        if(angle==0){
            current_block_top_points[0]=current_block_y-(3*unit/2);
            current_block_top_points[1]=current_block_y-(3*unit/2);
            current_block_top_points[2]=0;

            current_block_bottom_points[0]=current_block_y-(unit/2);
            current_block_bottom_points[1]=current_block_y+(3*unit/2);
            current_block_bottom_points[2]=0;}
        else if(angle==1){
            current_block_top_points[0]=current_block_y-(unit/2);
            current_block_top_points[1]=current_block_y-(unit/2);
            current_block_top_points[2]=current_block_y-(unit/2);

            current_block_bottom_points[0]=current_block_y+(3*unit/2);
            current_block_bottom_points[1]=current_block_y+(unit/2);
            current_block_bottom_points[2]=current_block_y+(unit/2);}
        else if(angle==2){
            current_block_top_points[0]=0;
            current_block_top_points[1]=current_block_y-(3*unit/2);
            current_block_top_points[2]=current_block_y+(unit/2);

            current_block_bottom_points[0]=0;
            current_block_bottom_points[1]=current_block_y+(3*unit/2);
            current_block_bottom_points[2]=current_block_y+(3*unit/2);}
        else if(angle==3){
             current_block_top_points[0]=current_block_y-(unit/2);
             current_block_top_points[1]=current_block_y-(unit/2);
             current_block_top_points[2]=current_block_y-(3*unit/2);

             current_block_bottom_points[0]=current_block_y+(unit/2);
             current_block_bottom_points[1]=current_block_y+(unit/2);
             current_block_bottom_points[2]=current_block_y+(unit/2);}
    }
    else if(shape==4)
    {
        if(angle==0){
              current_block_top_points[0]=0;
              current_block_top_points[1]=current_block_y-(3*unit/2);
              current_block_top_points[2]=current_block_y-(3*unit/2);

              current_block_bottom_points[0]=0;
              current_block_bottom_points[1]=current_block_y+(3*unit/2);
              current_block_bottom_points[2]=current_block_y-(unit/2);}
        else if(angle==1){
              current_block_top_points[0]=current_block_y-(3*unit/2);
              current_block_top_points[1]=current_block_y-(unit/2);
              current_block_top_points[2]=current_block_y-(unit/2);

              current_block_bottom_points[0]=current_block_y+(unit/2);
              current_block_bottom_points[1]=current_block_y+(unit/2);
              current_block_bottom_points[2]=current_block_y+(unit/2);}
        else if(angle==2){
              current_block_top_points[0]=current_block_y+(unit/2);
              current_block_top_points[1]=current_block_y-(3*unit/2);
              current_block_top_points[2]=0;

              current_block_bottom_points[0]=current_block_y+(3*unit/2);
              current_block_bottom_points[1]=current_block_y+(3*unit/2);
              current_block_bottom_points[2]=0;}
        else if(angle==3){
              current_block_top_points[0]=current_block_y-(unit/2);
              current_block_top_points[1]=current_block_y-(unit/2);
              current_block_top_points[2]=current_block_y-(unit/2);

              current_block_bottom_points[0]=current_block_y+(unit/2);
              current_block_bottom_points[1]=current_block_y+(unit/2);
              current_block_bottom_points[2]=current_block_y+(3*unit/2);}
    }
    else if(shape==5)
    {
        if(angle==0){
              current_block_top_points[0]=0;
              current_block_top_points[1]=current_block_y-(3*unit/2);
              current_block_top_points[2]=current_block_y-(unit/2);

              current_block_bottom_points[0]=0;
              current_block_bottom_points[1]=current_block_y+(3*unit/2);
              current_block_bottom_points[2]=current_block_y+(unit/2);}
        else if(angle==1){
              current_block_top_points[0]=current_block_y-(unit/2);
              current_block_top_points[1]=current_block_y-(3*unit/2);
              current_block_top_points[2]=current_block_y-(unit/2);

              current_block_bottom_points[0]=current_block_y+(unit/2);
              current_block_bottom_points[1]=current_block_y+(unit/2);
              current_block_bottom_points[2]=current_block_y+(unit/2);}
        else if(angle==2){
              current_block_top_points[0]=current_block_y-(unit/2);
              current_block_top_points[1]=current_block_y-(3*unit/2);
              current_block_top_points[2]=0;

              current_block_bottom_points[0]=current_block_y+(unit/2);
              current_block_bottom_points[1]=current_block_y+(3*unit/2);
              current_block_bottom_points[2]=0;}
        else if(angle==3){
              current_block_top_points[0]=current_block_y-(unit/2);
              current_block_top_points[1]=current_block_y-(unit/2);
              current_block_top_points[2]=current_block_y-(unit/2);

              current_block_top_points[0]=current_block_y+(unit/2);
              current_block_top_points[1]=current_block_y+(3*unit/2);
              current_block_top_points[2]=current_block_y+(unit/2);
              }
    }

}

int detect_collision()
{
    if(current_block_lane>1)
    {
    if(current_block_bottom_points[0]==lane_height[current_block_lane-2]||current_block_bottom_points[1]==lane_height[current_block_lane-1]||current_block_bottom_points[2]==lane_height[current_block_lane])
    return 1;
    }
    else if(current_block_lane<=1&&(current_block_bottom_points[1]==lane_height[current_block_lane-1]||current_block_bottom_points[2]==lane_height[current_block_lane]))
    return 1;
    else
    return 0;
}

void update_lane_height()
{
    if(current_block_lane>1)
    lane_height[current_block_lane-2]=current_block_top_points[0];
    lane_height[current_block_lane-1]=current_block_top_points[1];
    lane_height[current_block_lane]=current_block_top_points[2];
    for(int i=0;i<=22;i++)
        if(lane_height[i]==0)
        lane_height[i]=dwall;
}

void left()
{
    current_block_lane--;
    if(current_block_lane==0)
        current_block_lane=1;
    erase_previous_block();
    current_block_x=lwall+(current_block_lane-1)*unit+unit/2;
    current_block_y=current_block_y;
}

void right()
{
   // if(current_block_y==(current_block_bottom_points[2]-current_block_top_points[2]/2)&&getpixel(current_block_x+3*unit/2+1,current_block_y)==0)
     //   return;
    //else if(current_block_y!=(current_block_bottom_points[2]-current_block_top_points[2]/2)&&getpixel(current_block_x+3*unit/2+1,current_block_y)==0&&getpixel(current_block_x+unit/2+1,current_block_y)!=0)
      //  return;
     // if(current_block_bottom_points[2]-current_block_top_points[2]==current_block_y+unit)
      //{
        //  if(getpixel(current_block_x+3*unit/2+1,current_block_y-unit)!=0)
          //  return;
      //}
     current_block_lane++;
    if(current_block_lane==lanes+1)
        current_block_lane=lanes;
    erase_previous_block();
    current_block_x=lwall+(current_block_lane-1)*unit+unit/2;
    current_block_y=current_block_y;
}

void remove_filled_lines()
{
int i,j,flag=0;

for(i=dwall-unit/2;i>=uwall+unit/2;i=i-unit)
{
    for(j=lwall+1;j<=rwall-1;j=j+1){
    if(getpixel(j,i)==0&&getpixel(j,i+unit/2-1)==0){
        flag=1;break;}}

if(flag==0)
{
    void *p1,*p2;
    int area;

    area=imagesize(lwall+1,uwall+1,rwall-1,i-(unit/2));
    p1=malloc(area);
    getimage(lwall+1,uwall+1,rwall-1,i-(unit/2),p1);

    if(i!=dwall-unit/2){
    area=imagesize(lwall+1,i+(unit/2),rwall-1,dwall-1);
    p2=malloc(area);
    getimage(lwall+1,i+(unit/2),rwall-1,dwall-1,p2);}

    cleardevice();
    putimage(lwall+1,uwall+unit+1,p1,COPY_PUT);
    if(i!=dwall-unit/2)
    putimage(lwall+1,i+unit/2,p2,COPY_PUT);

    points++;
    i=0;
    for(i=0;i<lanes;i++)
        lane_height[i]=lane_height[i]+unit;
}
}
}

void check_game_status()
{
    int i;
    for(i=0;i<=lanes;i++){
        if(lane_height[i]<=uwall){
        game_status=0;break;}}
}
int main()
{
    initwindow(1920,1080);
    display_rules();
    cleardevice();
    spawn_block();
    assign_block_high_low_points();
    int i=0;
    for(i=0;i<22;i++)
        lane_height[i]=dwall;
    while(1)
    {
        draw_boundary();
        erase_previous_block();
        if(kbhit())
        {
            choice=getch();
            switch(choice)
            {
            case 'a':rotate_left();break;
            case 'd':rotate_right();break;
            case 'j':left();break;
            case 'l':right();break;
            case 'e':display_score();break;
            case 'p':getch();break;
            case 's':current_block_y+=15;break;
            default:break;
            }
        }
        move_down();
        assign_block_high_low_points();
        draw_block(shape,angle,current_block_x,current_block_y);
        if(detect_collision()==1){
             update_lane_height();
             spawn_block();
             assign_block_high_low_points();
             remove_filled_lines();
             //if(points%3==0)
            //game_speed=game_speed+1;
            }

        check_game_status();
        if(game_status==0)
            display_score();
        timedelay(10/game_speed);
    }
}

