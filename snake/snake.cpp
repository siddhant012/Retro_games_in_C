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
char prev_choice;

int snake_length;
int new_tail_flag;
int three_tails_erase_flag;

struct block
{
    int x;
    int y;
    struct block *prev;
    struct block *next;
    int color;
};
struct block *head,*tail,*temp;

struct food
{
    int x;
    int y;
    int color;
};
struct food *food1;

int random(int ll,int ul)
{
    int num=ll+(rand()%(ul-ll+1));
    return num;
}

void set_variables()
{
    head=(struct block *)malloc(sizeof(struct block));
    tail=(struct block *)malloc(sizeof(struct block));
    temp=(struct block *)malloc(sizeof(struct block));
    food1=(struct food*)malloc(sizeof(struct food));

    lwall=20;
    rwall=520;
    uwall=20;
    dwall=520;

    unit=10;
    game_speed=15;
    game_status=1;
    points=0;
    choice='d';
    prev_choice='d';

    snake_length=10;
    new_tail_flag=0;
    three_tails_erase_flag=0;

}

void spawn_food()
{
    food1->color=random(1,14);
    food1->x=lwall-unit+unit*(int)(random(lwall+1,rwall-1)/unit);
    food1->y=uwall-2*unit+unit*(int)(random(uwall+1,dwall-1)/unit);
}

void draw_food()
{
    setfillstyle(SOLID_FILL,food1->color);
    setcolor(food1->color);
    bar(food1->x-unit/2,food1->y-unit/2,food1->x+unit/2,food1->y+unit/2);
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
    delay(3000);
    closegraph();
    exit(1);
}

void display_rules()
{
    setfillstyle(SOLID_FILL,WHITE);
    setcolor(WHITE);
    outtextxy(725,210,"SNAKE");
    outtextxy(695,240,"PRESS W TO MOVE UP");
    outtextxy(695,270,"PRESS S TO MOVE DOWN");
    outtextxy(695,300,"PRESS A TO MOVE LEFT");
    outtextxy(695,330,"PRESS D TO MOVE RIGHT");
    outtextxy(695,360,"PRESS P TO PAUSE");
    outtextxy(695,390,"PRESS ANY KEY TO CONTINUE");
    getch();
}

void draw_snake()
{
    temp=head;
    while(temp!=NULL)
    {
    setfillstyle(SOLID_FILL,temp->color);
    setcolor(temp->color);
    bar(temp->x-unit/2,temp->y-unit/2,temp->x+unit/2,temp->y+unit/2);
    temp=temp->prev;
    }
}

void erase_tail()
{
   if(three_tails_erase_flag==1)
   {
    int i=1;
    temp=tail;
    while(i++<=3){
    setfillstyle(SOLID_FILL,BLACK);
    setcolor(BLACK);
    bar(temp->x-unit/2,temp->y-unit/2,temp->x+unit/2,temp->y+unit/2);
    temp=temp->next;}
    three_tails_erase_flag=0;
   }
   else if(new_tail_flag==1)
    {
    temp=(struct block *)malloc(sizeof(struct block));
    temp->x=tail->x;
    temp->y=tail->y;
    temp->color=food1->color;
    temp->prev=NULL;
    temp->next=tail;
    tail->prev=temp;
    tail=temp;
    setfillstyle(SOLID_FILL,food1->color);
    setcolor(food1->color);
    bar(tail->x-unit/2,tail->y-unit/2,tail->x+unit/2,tail->y+unit/2);
    new_tail_flag=0;
    }
    else
    {
    setfillstyle(SOLID_FILL,BLACK);
    setcolor(BLACK);
    bar(tail->x-unit/2,tail->y-unit/2,tail->x+unit/2,tail->y+unit/2);
    }
}

void draw_new_tail()
{
new_tail_flag=1;
erase_tail();
snake_length++;
}

void init_game()
{
    initwindow(1920,1080);
    set_variables();
    display_rules();
    cleardevice();
    draw_boundary();
    spawn_food();
    draw_food();

    head->x=(rwall-lwall)/2;
    head->y=(dwall-uwall)/2;
    head->prev=NULL;
    head->next=NULL;
    head->color=random(1,14);
    temp=head;
    int i=2;
    struct block *new_block=(struct block *)malloc(sizeof(struct block));
    while(i++<=snake_length)
    {
        temp->prev=new_block;
        new_block->next=temp;
        new_block->x=temp->x-unit;
        new_block->y=temp->y;
        new_block->color=random(1,14);
        temp=new_block;
        new_block=(struct block *)malloc(sizeof(struct block));
    }
    temp=head;
    while(temp->prev!=NULL)
    temp=temp->prev;
    tail=temp;
    draw_snake();
}

void move_up()
{
    head->y=head->y-unit;
}

void move_down()
{
    head->y=head->y+unit;
}

void move_right()
{
    head->x=head->x+unit;
}

void move_left()
{
    head->x=head->x-unit;
}

void move_snake()
{
    temp=tail;
    while(temp->next!=NULL)
    {
        temp->x=temp->next->x;
        temp->y=temp->next->y;
        temp=temp->next;
    }
    if(choice=='a'&&prev_choice!='d')
        move_left();
    else if(choice=='a'&&prev_choice=='d'){
        move_right();
        choice='d';
    }
    else if(choice=='d'&&prev_choice!='a')
        move_right();
    else if(choice=='d'&&prev_choice=='a'){
        move_left();
        choice='a';
    }
    else if(choice=='s'&&prev_choice!='w')
        move_down();
    else if(choice=='s'&&prev_choice=='w'){
        move_up();
        choice='w';}
    else if(choice=='w'&&prev_choice!='s')
        move_up();
    else if(choice=='w'&&prev_choice=='s'){
        move_down();
        choice='s';}
}

void check_game_status()
{
    struct block *t=(struct block *)malloc(sizeof(struct block));
    temp=head;
    while(temp->prev!=NULL)
    {
        t=temp->prev;
        while(t!=NULL)
        {
         if(temp->x==t->x&&temp->y==t->y)
                game_status=0;
         t=t->prev;
        }
        temp=temp->prev;
    }
    if(head->x==lwall||head->x==rwall||head->y==uwall||head->y==dwall)
        game_status=0;
}

void check_points()
{
    if(head->x==food1->x&&head->y==food1->y)
    {
        points++;

        //erasing prevous food
        setfillstyle(SOLID_FILL,BLACK);
        setcolor(BLACK);
        bar(food1->x-unit/2,food1->y-unit/2,food1->x+unit/2,food1->y+unit/2);

        draw_new_tail();
        spawn_food();
        draw_food();
    }
    if(tail->color==tail->next->color&&tail->next->color==tail->next->next->color){
        three_tails_erase_flag=1;
        erase_tail();
        tail=tail->next->next->next;
        free(tail->prev->prev->prev);
        free(tail->prev->prev);
        free(tail->prev);
        tail->prev=NULL;
        snake_length=snake_length-3;
        }
}

int main()
{
    init_game();
    delay(1000/game_speed);
    while(1)
    {
        erase_tail();

        if(kbhit()){
        prev_choice=choice;
        choice=getch();}

        move_snake();
        draw_snake();

        check_game_status();
        if(game_status==0)
            display_score();

        check_points();

        delay(1000/game_speed);
    }

    return 0;
}
