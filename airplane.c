#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define RED(string) "\x1b[31m" string "\x1b[0m"
#define GREEN(string) "\x1b[32m" string "\x1b[0m"
#define YELLOW(string) "\x1b[33m" string "\x1b[0m"
#define WHITE(string) "\x1b[37m" string "\x1b[0m"

#define AIRPLANE_WIDTH 10
#define AIRPLANE_HEIGHT 5
#define MAX_BULLETS 1000

char order_move = 'e';
int AMMO = 50, Health = 12, Power = 1;
int score = 0;
short bullet_x[MAX_BULLETS], bullet_y[MAX_BULLETS];
short bulletCount = 0;
short enemyAirPlane_x = 0, enemyAirPlane_y = 1;
short enemyAirplaneHP = 3;
short CargoAirPlane_x, CargoAirPlane_y;
short Bomber_x = 0, Bomber_y = 0;
short cargoR = 0;
short bomberR = 0;
short mineR= 0;
short mine_x=0;
short mine_y=0;
short bomb_x,bomb_y;
bool cargoReward=true;
bool bombdrop=false;
bool checkbomb=false;
short reward_x=0,reward_y=0;
short airplane_x = 51, airplane_y = 23;
bool enemyShoot=false;
short enemyShoot_x=0,enemyshoot_y=0;
short selectedOption=0;
short cargoHealth=4;
short bomberHealth=3;
void gotoxy(short x, short y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void arrow(int is, int wantToBe) {
    if (is == wantToBe) {
        printf("" GREEN("====>"));
    } else {
        printf("     ");
    }
}

int menu() {
    int keynum = 0;
    int position = 1;
    while (1) {
        printf("\033[H\033[J");
        arrow(1, position);
        printf(RED("START THE GAME         \n"));
        arrow(2, position);
        printf(RED("LOG              \n"));
        arrow(3, position);
        printf(RED("QUIT             \n"));


       
            keynum = _getch();
            if (keynum == 72 && position != 1) {
                position--; // 'W' key
            } else if (keynum == 80 && position != 3) {
                position++; // 'S' key
            } else if (keynum == '\r'||keynum==27) { // Enter key
                break;
            
        }

    }
    return position;
}




void drawAirplane(short x, short y)
{
    if (Health >= 9)
    {
        gotoxy(x + 3, y);
        printf("" GREEN("/||\\"));
        gotoxy(x + 2, y + 1);
        printf("" GREEN("/ __ \\"));
        gotoxy(x + 1, y + 2);
        printf("" GREEN("/ /%.2d\\ \\"), Health);
        gotoxy(x, y + 3);
        printf("" GREEN("/  \\__/  \\"));
        gotoxy(x, y + 4);
        printf("" GREEN("\\_/====\\_/"));
    }
    else if (Health < 8 && Health >= 5)
    {
        gotoxy(x + 3, y);
        printf("" YELLOW("/||\\"));
        gotoxy(x + 2, y + 1);
        printf("" YELLOW("/ __ \\"));
        gotoxy(x + 1, y + 2);
        printf("" YELLOW("/ /%.2d\\ \\"), Health);
        gotoxy(x, y + 3);
        printf("" YELLOW("/  \\__/  \\"));
        gotoxy(x, y + 4);
        printf("" YELLOW("\\_/====\\_/"));
    }
    else
    {
        gotoxy(x + 3, y);
        printf("" RED("/||\\"));
        gotoxy(x + 2, y + 1);
        printf("" RED("/ __ \\"));
        gotoxy(x + 1, y + 2);
        printf("" RED("/ /%.2d\\ \\"), Health);
        gotoxy(x, y + 3);
        printf("" RED("/  \\__/  \\"));
        gotoxy(x, y + 4);
        printf("" RED("\\_/====\\_/"));
    }
}

void drawEnemyAirPlane()
{
    if (enemyAirplaneHP == 3)
    {
        gotoxy(enemyAirPlane_x, enemyAirPlane_y);
        printf("" GREEN("/-\\___/-\\"));
        gotoxy(enemyAirPlane_x, enemyAirPlane_y + 1);
        printf("" GREEN("\\       /"));
        gotoxy(enemyAirPlane_x + 1, enemyAirPlane_y + 2);
        printf("" GREEN("\\ (%d) /"), enemyAirplaneHP);
        gotoxy(enemyAirPlane_x + 2, enemyAirPlane_y + 3);
        printf("" GREEN("\\   /"));
        gotoxy(enemyAirPlane_x + 3, enemyAirPlane_y + 4);
        printf("" GREEN("\\_/"));
    }
    else if (enemyAirplaneHP == 2)
    {
        gotoxy(enemyAirPlane_x, enemyAirPlane_y);
        printf("" YELLOW("/-\\___/-\\"));
        gotoxy(enemyAirPlane_x, enemyAirPlane_y + 1);
        printf("" YELLOW("\\       /"));
        gotoxy(enemyAirPlane_x + 1, enemyAirPlane_y + 2);
        printf("" YELLOW("\\ (%d) /"), enemyAirplaneHP);
        gotoxy(enemyAirPlane_x + 2, enemyAirPlane_y + 3);
        printf("" YELLOW("\\   /"));
        gotoxy(enemyAirPlane_x + 3, enemyAirPlane_y + 4);
        printf("" YELLOW("\\_/"));
    }
    else if (enemyAirplaneHP == 1)
    {
        gotoxy(enemyAirPlane_x, enemyAirPlane_y);
        printf("" RED("/-\\___/-\\"));
        gotoxy(enemyAirPlane_x, enemyAirPlane_y + 1);
        printf("" RED("\\       /"));
        gotoxy(enemyAirPlane_x + 1, enemyAirPlane_y + 2);
        printf("" RED("\\ (%d) /"), enemyAirplaneHP);
        gotoxy(enemyAirPlane_x + 2, enemyAirPlane_y + 3);
        printf("" RED("\\   /"));
        gotoxy(enemyAirPlane_x + 3, enemyAirPlane_y + 4);
        printf("" RED("\\_/"));
    }
    else
    {
        enemyAirPlane_y = 24;
        enemyAirplaneHP = 3;
    }
}

void drawEnemyShoot(){
    gotoxy(enemyShoot_x,enemyshoot_y+enemyAirPlane_y);printf(""RED(":"));
}


void drawCargoAirPlane()
{

    gotoxy(CargoAirPlane_x + 4, CargoAirPlane_y);
    printf("" GREEN("\\/\\/"));
    gotoxy(CargoAirPlane_x + 4, CargoAirPlane_y + 1);
    printf("" GREEN("|  |"));
    gotoxy(CargoAirPlane_x, CargoAirPlane_y + 2);
    printf("" GREEN("____|  |____"));
    gotoxy(CargoAirPlane_x, CargoAirPlane_y + 3);
    printf("" GREEN("\\          /"));
    gotoxy(CargoAirPlane_x + 1, CargoAirPlane_y + 4);
    printf("" GREEN("\\__    __/"));
    gotoxy(CargoAirPlane_x + 4, CargoAirPlane_y + 5);
    printf("" GREEN("|  |"));
    gotoxy(CargoAirPlane_x + 4, CargoAirPlane_y + 6);
    printf("" GREEN("\\__/"));
}
void drawBomber()
{

    gotoxy(Bomber_x + 5, Bomber_y);
    printf("" RED("/--\\"));
    gotoxy(Bomber_x, Bomber_y + 1);
    printf("" RED("|\\__/    \\_"));
    gotoxy(Bomber_x, Bomber_y + 2);
    printf("" RED("| __      _|="));
    gotoxy(Bomber_x, Bomber_y + 3);
    printf("" RED("|/  \\    /"));
    gotoxy(Bomber_x + 5, Bomber_y + 4);
    printf("" RED("\\--/"));
}



void drawbomb(){
    gotoxy(bomb_x, bomb_y);
    printf("" RED("|_"));
    gotoxy(bomb_x, bomb_y + 1);
    printf("" RED("(_)"));
}

void drawMine() {
    gotoxy(mine_x + 1, mine_y); printf("" RED("___"));
    gotoxy(mine_x, mine_y + 1); printf("" RED("|(M)|"));
    gotoxy(mine_x, mine_y + 2); printf("" RED("|_%%_|"));
}


void moveAirPlane(short *airplane_x, short *airplane_y, char order)
{
    switch (order)
    {
    case 'w':
        if (*airplane_y != 1)
            (*airplane_y)--;
        break;
    case 's':
        if (*airplane_y != 23)
            (*airplane_y)++;
        break;
    case 'a':
        if (*airplane_x > 5)
            (*airplane_x) -= 3;
        break;
    case 'd':
        if (*airplane_x < 100)
            (*airplane_x) += 3;
        break;
    }
}

void moveEnemyAirPlane()
{
    (enemyAirPlane_y)++;
    if (enemyAirPlane_y > 23)
    {
        enemyAirPlane_x = rand() % 99;
        enemyAirPlane_y = 1;
        enemyAirplaneHP = 3;
        enemyshoot_y=rand()%10 + 1;
        enemyShoot_x=enemyAirPlane_x+5;
        enemyShoot=true;

    }
}

void moveCargoAirPlane()
{
    (CargoAirPlane_y)++;
    if (CargoAirPlane_y > 20)
    {
        cargoR = 0;
        CargoAirPlane_x = rand() % 99;
        CargoAirPlane_y = 1;
    }
}

void moveBomber()
{
    (Bomber_y)++;
    Bomber_x += 5;
    if(bomb_x>Bomber_x&&bomb_x<Bomber_x+5){
        checkbomb=true;
    }
    if (Bomber_y > 20||Bomber_x>100)
    {
        bomberR=0;
        Bomber_x = 1;
        Bomber_y = 1;
    }
}


void movebomb(){
    bomb_y+=2;
    if(bomb_y>23){
        bomb_x=0;
        bomb_y=0;
        bombdrop=false;
    }
}

void moveMine(){
    mine_y++;
    if(mine_y>23){
        mineR=0;
        mine_y=0;
        mine_x=1;
    }
}

void moveEnemyShoot(){
    enemyshoot_y+=5;
    if(enemyshoot_y>=21){
        enemyShoot_x=0;
        enemyshoot_y=0;
        enemyShoot=false;
    }
}

int checkCollisionWithMine(short airplane_x,short airplane_y){
        if (airplane_x < mine_x + AIRPLANE_WIDTH &&
        airplane_x + AIRPLANE_WIDTH > mine_x &&
        airplane_y < mine_y + AIRPLANE_HEIGHT &&
        airplane_y + AIRPLANE_HEIGHT > mine_y){
        return 1; // Collision occurred
    }
    return 0; // No collision


}


int checkCollisionWithEnemyAirPlane(short airplane_x, short airplane_y, short enemy_x, short enemy_y)
{
    if (airplane_x < enemy_x + AIRPLANE_WIDTH &&
        airplane_x + AIRPLANE_WIDTH > enemy_x &&
        airplane_y < enemy_y + AIRPLANE_HEIGHT &&
        airplane_y + AIRPLANE_HEIGHT > enemy_y)
    {
        return 1; // Collision occurred
    }
    return 0; // No collision

}

int checkCollisionWithEnemyShoot(){
        if (airplane_x < enemyShoot_x + AIRPLANE_WIDTH &&
        airplane_x + AIRPLANE_WIDTH > enemyShoot_x &&
        airplane_y <= enemyshoot_y+ AIRPLANE_HEIGHT &&
        airplane_y + AIRPLANE_HEIGHT+6 >= enemyshoot_y)
    {
        return 1; // Collision occurred
    }
    return 0; // No collision

}


int checkCollisionWithCargo(short airplane_x,short airplane_y){

        if (airplane_x < CargoAirPlane_x + AIRPLANE_WIDTH &&
        airplane_x + AIRPLANE_WIDTH > CargoAirPlane_x &&
        airplane_y < CargoAirPlane_y+ AIRPLANE_HEIGHT &&
        airplane_y + AIRPLANE_HEIGHT > CargoAirPlane_y)
    {
        return 1; // Collision occurred
    }
    return 0; // No collision



}   

int checkCollisionWithBomber(short airplane_x,short airplane_y){

    if (airplane_x < Bomber_x + AIRPLANE_WIDTH &&
        airplane_x + AIRPLANE_WIDTH > Bomber_x &&
        airplane_y < Bomber_y+ AIRPLANE_HEIGHT &&
        airplane_y + AIRPLANE_HEIGHT > Bomber_y)
    {
        return 1; // Collision occurred
    }
    return 0; // No collision



}



int checkBulletHit(short bullet_x, short bullet_y, short enemy_x, short enemy_y)
{
    if (bullet_y >= enemy_y &&bullet_y<=enemy_y +12 && bullet_x + 4 >= enemy_x && bullet_x + 4 <= enemy_x + AIRPLANE_WIDTH)
    {
        bulletCount = 0;
        return 1; // Hit
    }
    return 0; // No hit
}

int checkBulletHitcargo(short bullet_x, short bullet_y, short enemy_x, short enemy_y)
{
    if (bullet_y >= enemy_y && bullet_y<= enemy_y+12 && bullet_x + 4 >= enemy_x && bullet_x + 4 <= enemy_x + 11)
    {
        bulletCount = 0;
        return 1; // Hit
    }
    return 0; // No hit
}

int checkBulletHitbomber(short bullet_x, short bullet_y, short enemy_x, short enemy_y)
{
    if (bullet_y >= enemy_y && bullet_y<= enemy_y+12 && bullet_x + 4 >= enemy_x && bullet_x + 4 <= enemy_x + 11)
    {
        bulletCount = 0;
        return 1; // Hit
    }
    return 0; // No hit
}
void checkForReward(short airplane_x,short airplane_y){;
    if(airplane_y <= reward_y+3  && airplane_x  >= reward_x-3 && airplane_x + 5 <= reward_x + 16){
        cargoReward=true;
        if(rand()%5==0&&Power!=3){
            Power++;
            CargoAirPlane_y=21;

        }
        else if(rand()%5==2||rand()%5==3){
            AMMO+=20;
        }
        else {
            if(Health<30){
                Health+=5;
            }
            CargoAirPlane_y=21;
        }
    }
}
void AirPlaneShoot()
{
    for (int i = 0; i < bulletCount; i++)
    {
        if (Power == 1)
        {
            gotoxy(bullet_x[i] + 4, bullet_y[i] - 1);
            printf("" WHITE("."));
        }
        else if (Power == 2)
        {
            gotoxy(bullet_x[i] + 4, bullet_y[i] - 1);
            printf("" YELLOW(":"));
        }
        else
        {
            gotoxy(bullet_x[i] + 4, bullet_y[i] - 1);
            printf("" RED("|"));
        }
        bullet_y[i]-=8;
    }

    // Remove bullets that have reached the top
    for (int i = 0; i < bulletCount; i++)
    {
        if (bullet_y[i] < 0)
        {
            // Shift remaining bullets to fill the gap
            for (int j = i; j < bulletCount - 1; j++)
            {
                bullet_x[j] = bullet_x[j + 1];
                bullet_y[j] = bullet_y[j + 1];
            }
            bulletCount--;
        }
    }
}
int checkCollisionWithBomb(short airplane_x, short airplane_y) {
    if (airplane_x < bomb_x + AIRPLANE_WIDTH &&
        airplane_x + AIRPLANE_WIDTH > bomb_x &&
        airplane_y < bomb_y + AIRPLANE_HEIGHT &&
        airplane_y + AIRPLANE_HEIGHT > bomb_y){
        return 1; // Collision occurred
    }
    return 0; // No collision
}

void play(){
    enemyAirPlane_x = rand() % 99 + 1;
    while (Health > 0)
    {
        if (_kbhit())
        {
            order_move = _getch();
            if (order_move == ' ' && AMMO > 0 && bulletCount < MAX_BULLETS)
            {
                AMMO--;
                bullet_x[bulletCount] = airplane_x;
                bullet_y[bulletCount] = airplane_y;
                bulletCount++;
            }
        }

        Sleep(100);
        system("cls");

        moveAirPlane(&airplane_x, &airplane_y, order_move);
        moveEnemyAirPlane();

        drawAirplane(airplane_x, airplane_y);
        drawEnemyAirPlane();

        if(enemyAirPlane_y>=enemyshoot_y&&enemyShoot){
            moveEnemyShoot();
            drawEnemyShoot();
        }

        if(checkCollisionWithEnemyShoot()){
            enemyShoot=false;
            enemyShoot_x=0;
            enemyshoot_y=0;
            Health-=2;
        }

        if (cargoR == 0)
        {
            cargoR = rand();
        }
        else if (cargoR % 10 == 0&&cargoReward)
        {
            moveCargoAirPlane();
            drawCargoAirPlane();
        }
        else
        {
            cargoR = 0;
        }
        if (bomberR == 0)
        {
            bomberR = rand();
        }
        else if (bomberR % 20 == 0)
        {
            moveBomber();
            drawBomber();
            if(Bomber_x==1){
            bomb_x=rand()%50+5;

            }
        }
        else
        {
            bomberR = 0;
        }
        if(mineR==0){
            mineR=rand();
        }
        else if(mineR%15==0){
            moveMine();
            drawMine();
            if(mine_x==1){

            mine_x=rand()%100;
            }

        }
        else{
            mineR=0;
        }

        gotoxy(1, 28);
        printf("Score=%d\t\t Health=%d\t\t Ammo=%d\t\t Power=%d", score, Health, AMMO, Power);



        if (checkCollisionWithEnemyAirPlane(airplane_x, airplane_y, enemyAirPlane_x, enemyAirPlane_y))
        {
            Health -= 3;
            enemyAirplaneHP = 0;
            enemyAirPlane_y = 24;
            score += 150;
        }

        for (int i = 0; i < bulletCount; i++)
        {
            if (checkBulletHit(bullet_x[i], bullet_y[i], enemyAirPlane_x, enemyAirPlane_y))
            {
                enemyAirplaneHP -= Power;
                if (enemyAirplaneHP == 0)
                {
                    enemyAirPlane_y = 24;
                    score += 200;
                    enemyAirplaneHP = 3;
                }
            }
        }

        for (int i=0;i<bulletCount;i++){
            if(checkBulletHitcargo(bullet_x[i],bullet_y[i],CargoAirPlane_x,CargoAirPlane_y)){
                cargoHealth-= Power;
                if(cargoHealth<=0){
                cargoR=0;
                cargoReward=false;
                score+=100;
                reward_x=CargoAirPlane_x;
                reward_y=CargoAirPlane_y;
                CargoAirPlane_x=0;
                CargoAirPlane_y=30;

                }

            }
        }
        for (int i=0;i<bulletCount;i++){
            if(checkBulletHitbomber(bullet_x[i],bullet_y[i],Bomber_x,Bomber_y)){
                bomberHealth-=Power;
                if(bomberHealth<=0){
                bomberR=0;
                Bomber_y=30;
                score+=150;

                }

        }
        }
        if (!cargoReward){
            gotoxy(reward_x+3,reward_y+3);printf("__");
            gotoxy(reward_x+2,reward_y+4);printf("|__|");
            checkForReward(airplane_x,airplane_y);

        }
        if(checkbomb){
            bomb_y=Bomber_y;
            bomb_x=Bomber_x;
            bombdrop=true;
        }
        if(bombdrop){
            movebomb();
            drawbomb();
            checkbomb=false;
        }
        if (checkCollisionWithBomb(airplane_x, airplane_y)) {
        Health -= 8;
        bombdrop = false;
        bomb_x=0;
        bomb_y=0;
    }

    if (checkCollisionWithCargo(airplane_x,airplane_y)){
        cargoReward=true;
        cargoR=0;
        CargoAirPlane_x=0;
        CargoAirPlane_y=30;
        cargoHealth=4;
        Health-=2;
        if(Power>1){
            Power--;
        }
    }
    if(checkCollisionWithBomber(airplane_x,airplane_y)){
        Health-= 3;
        checkbomb=false;
        bomberR=0;
        Bomber_y=30;
        Bomber_x=1;
        bomberHealth=3;
        if(Power>1){
            Power--;
        }
    }

    if(checkCollisionWithMine(airplane_x, airplane_y)){
        Health-=5;
        mineR=0;
        mine_y=30;
        mine_x=1;
        if(Power>1){
            Power--;
        }        
    }

        AirPlaneShoot();

        score++;
        order_move = 'e';

    }

    system("cls");
    gotoxy(55, 12);
    printf("" RED("YOU LOSE"));
    gotoxy(53,13);printf(""GREEN("SCORE = %d "),score);
    gotoxy(52,14); printf("YOU FOUGHT WELL");
    gotoxy(48,15); printf(""YELLOW("ENTER YOUR NAME BRAVE WARRIOR:"));
    char name[100];
    Sleep(2000);
    scanf("%s",name);
FILE *logs, *temp;
logs = fopen("logs.txt", "r");
temp = fopen("temp.txt", "w");  // Open in write mode to clear existing content

char buffer[100000];
while (fgets(buffer, 100000, logs) != NULL)
{
    fprintf(temp, "%s", buffer);  
}

fclose(logs);
fclose(temp);

logs=fopen("logs.txt","w");
temp = fopen("temp.txt", "r");  
time_t t;
time(&t);
    fprintf(logs,"WARRIOR %s played at %s and  your SCORE was  %d\n\n",name,ctime(&t),score);
    while(fgets(buffer,100000,temp)!=NULL){
        fprintf(logs,"%s",buffer);
    }
    fclose(logs);
    fclose(temp);
    system("cls");
    gotoxy(55,12); printf(""GREEN("REST IN PEACE"));
    Sleep(5000);
    Health=12;
    AMMO=50;
    Power=1;
}

int main(void)
{
    HANDLE hOut;
CONSOLE_CURSOR_INFO ConCurInf;
 
hOut = GetStdHandle(STD_OUTPUT_HANDLE);
 
ConCurInf.dwSize = 10;
ConCurInf.bVisible = FALSE;
 
SetConsoleCursorInfo(hOut, &ConCurInf);
    srand(time(0));
    while(selectedOption!=3){
        selectedOption=menu();
        if(selectedOption==1){
            play();
        }
        else if(selectedOption==2){
            system("cls");
            char printBuffer[1000000];
            FILE *log = fopen("logs.txt","r");
            while(fgets(printBuffer,1000000,log)){
                printf("%s",printBuffer);
            }
            _getch();
        }
    }


    return 0;
}

