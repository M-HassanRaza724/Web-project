# include <iostream>
# include<windows.h>
# include<conio.h>
using namespace std;

int lax = 23, lbx = 46, ly = 1;
int e_lax = 23, e_lbx = 46, e_ly = 1;
int Px = 27,Py = 26;
int Ex[3] ={3,29,52};
int Ey[3] ={2,2,2};
int speed = 30;
int bulletX[100];
int bulletY[100];
bool isBulletActive[100];
int bulletCount = 0;
int score = 0;
int e_health[3] = {40,40,40};
bool healthChange[4];

int e_bulletX[100];
int e_bulletY[100];
bool is_e_BulletActive[100];
int e_bulletCount = 0;

char light = 220,block = 219,pistol0 = 200,line = 219;
string pistol = {pistol0};
string car[9],enemy1[9],enemy2[9],enemy3[9];


void gotoxy(int x, int y);
char getCharAtxy(short int x, short int y);

void initialize_vehicles();
void print_header();
void print_road();

void print_lines();
void erase_lines();
void move_lines(int);

void print_car();
void erase_car();
void move_car_left();
void move_car_right();
void move_car_up(int i);
void move_car_down(int i);

void erase_enemy(int n);
void print_enemy1();
void print_enemy2();
void print_enemy3();

void move_enemy1(int i);
void move_enemy2(int i);
void move_enemy3(int i);

void generate_p_Bullet();
void move_p_Bullet();
void print_p_Bullet(int x,int y);
void erase_p_Bullet(int x,int y);
void make_p_BulletInactive(int index);
bool enemyBulletCollision();
void addScore();
int p_bulletTargetX(int index);
void printScore();

void generate_e_Bullet();
void move_e_Bullet();
void print_e_Bullet(int x,int y);
void erase_e_Bullet(int x,int y);
void make_e_BulletInactive(int index);
bool playerBulletCollision();
int e_bulletTargetX(int index);

void e_healthCal();
void healthDisplay(int character,int x,int y);

main(){
    int i = 1;
    int damage = 1;

    initialize_vehicles();
    print_header();
    cout<<"\n\n\n\n\nPress any key to continue...";
    getch();
    system("cls");
    print_road();

    print_enemy1();
    print_enemy2();
    print_enemy3();
    print_car();
    while(true){

        //Iterations
        i++;
        if(i==999) 
            i = 10;   //control line lenght


        //left movement
        if(GetAsyncKeyState(VK_LEFT)){
                move_car_left();
        }
        //right movement
        if(GetAsyncKeyState(VK_RIGHT)){
                move_car_right();
        }
        //speed and vertical movement
        if(GetAsyncKeyState(VK_UP)){
                move_car_up(i);
            if((speed > 10) && (i%5 == 0)){
                speed--;
            }
        }
        if(GetAsyncKeyState(VK_DOWN)){
                move_car_down(i);
            if((speed < 30) && (i%5 == 0)){
                speed++;
            }
        }
        else{
            if((i%100 == 0) && (speed < 30))
                speed++;
        }
        if(GetAsyncKeyState(VK_SPACE))
            generate_p_Bullet();
        move_p_Bullet();
        if(i%999)
            generate_e_Bullet();
        move_e_Bullet();



        move_lines(i);

        move_enemy1(i);
        move_enemy2(i);
        move_enemy3(i);
        addScore();
        printScore();
        e_healthCal();
        healthDisplay(1,88,8);
        healthDisplay(2,88,9);
        healthDisplay(3,88,10);


        Sleep(speed);
    }

    return 0;
}
void gotoxy(int x, int y){

    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
char getCharAtxy(short int x, short int y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}


void generate_p_Bullet(){
    if(bulletCount<100){
        bulletX[bulletCount] = Px;
        bulletY[bulletCount] = Py-2;
        isBulletActive[bulletCount] = true;
        bulletCount++;
        gotoxy(Px,Py-2);
        cout<<'^';
        gotoxy(75,14);
        cout<<"Bullets: "<<100-bulletCount;
    }
}

void move_p_Bullet(){
    for (int i = 0; i < bulletCount; i++)
    {
        if(isBulletActive[i]){
            char next = getCharAtxy(bulletX[i],bulletY[i]-1);
            // gotoxy(0,38); cout << "Next char: " << next << " at (" << bulletX[i] << ", " << bulletY[i] - 1 << ")" << endl; // debug helper
            if(next != ' '){
                // gotoxy(0,39); cout << "Bullet collision detected at (" << bulletX[i] << ", " << bulletY[i] - 1 << ") at char: "<<next << endl; ///debug helper
                erase_p_Bullet(bulletX[i],bulletY[i]);
                make_p_BulletInactive(i);

            }else{
                erase_p_Bullet(bulletX[i],bulletY[i]);
                bulletY[i]--;
                print_p_Bullet(bulletX[i],bulletY[i]);
            }
                // gotoxy(0,40); cout << "Bullet state of bullet count "<<bulletCount<<" is "<< isBulletActive[i] << endl; ///debug helper
        }
    }
    
}
void print_p_Bullet(int x,int y){
    gotoxy(x,y);
    cout<<'^';

}
void erase_p_Bullet(int x,int y){
    gotoxy(x,y);
    cout<<' ';
}
void make_p_BulletInactive(int index){
    isBulletActive[index] = false;
}
bool enemyBulletCollision(){
    for (int i = 0; i < bulletCount; i++)
    {
        if(isBulletActive[i]){
            int targetXindex = p_bulletTargetX(i);
            if(targetXindex != -1 && bulletY[i]-1 == Ey[targetXindex]+8){
                // gotoxy(0,41); cout<<"bullet collision detected at enemy: "<<targetXindex; //debug Helper
                return true;
            }
        }
    }
    return false;
}
int p_bulletTargetX(int index){
    for (int j = 0; j < 3; j++)
    {
        for (int i = Ex[j]; i < Ex[j]+13; i++)
        {
            if(i == bulletX[index])
                return j;
        }
    }
    return -1;
}

void generate_e_Bullet(){
    if(Ex[2] == Px+3){
        e_bulletX[bulletCount] = Ex[2];
        e_bulletY[bulletCount] = Ey[2]+10;
        is_e_BulletActive[bulletCount] = true;
        e_bulletCount++;
    }

}
void move_e_Bullet(){
    for (int i = 0; i < e_bulletCount; i++)
    {
        if(is_e_BulletActive[i]){
            char next = getCharAtxy(e_bulletX[i],e_bulletY[i]+1);
            gotoxy(0,38); cout << "Next char: " << next << " at (" << e_bulletX[i] << ", " << e_bulletY[i]+1 << ")" << endl; // debug helper
            if(next != ' '){
                gotoxy(0,39); cout << "Bullet collision detected at (" << e_bulletX[i] << ", " << e_bulletY[i] << ") at char: "<<next << endl; ///debug helper
                erase_e_Bullet(e_bulletX[i],e_bulletY[i]);
                make_e_BulletInactive(i);
            }else{
                erase_e_Bullet(e_bulletX[i],e_bulletY[i]);
                e_bulletY[i]++;
                print_e_Bullet(e_bulletX[i],e_bulletY[i]);
            }
                gotoxy(0,40); cout << "Bullet state of bullet count "<<e_bulletCount<<" is "<< is_e_BulletActive[i] << endl; ///debug helper
        }
    }
    
}
void print_e_Bullet(int x,int y){
    gotoxy(x,y);
    cout<<'v';

}
void erase_e_Bullet(int x,int y){
    gotoxy(x,y);
    cout<<' ';
}
void make_e_BulletInactive(int index){
    is_e_BulletActive[index] = false;
}

// bool playerBulletCollision();
// int e_bulletTargetX(int index);

void e_healthCal(){
    for (int i = 0; i < bulletCount; i++)
    {
        if(isBulletActive[i]){
            int enemyHit = p_bulletTargetX(i);
            if(enemyHit != -1 && bulletY[i]-1 == Ey[enemyHit]+8 && e_health[enemyHit]>0){
                healthChange[enemyHit+1] = true;
                e_health[enemyHit]--;
            }
        }
    }
}
void healthDisplay(int character,int x,int y){
    int health_hearts = 0;
    if(healthChange[character]){
        gotoxy(x,y);
        cout<<"    ";
        gotoxy(x,y);
        healthChange[character] = false;
        if(e_health[character-1] != 0)
            health_hearts = (e_health[character-1]+10)/10;
        else
            health_hearts = 0;
        for (int i = 0; i < health_hearts; i++)
            cout<<'@';
        // gotoxy(88,11);  cout<<"Health of character "<<character<<" is changed "<<healthChange[character];    //debug helper
    }

}

void addScore(){
    if(enemyBulletCollision()){
        score++;
    }
}
void printScore(){
    gotoxy(80, 4);
    cout<<score;
}

void move_car_left(){
    if((getCharAtxy(Px-1,Py) == ' ' && getCharAtxy(Px-1,Py+8) == ' ')|| getCharAtxy(Px+14,Py) == line){
        erase_car();
        Px = Px-1;
        if((Px==23 || Px == 46))
            Px--;
        print_car();
    }
}

void move_car_right(){
    if((getCharAtxy(Px+14,Py) == ' ' && getCharAtxy(Px+14,Py+8) == ' ' ) || getCharAtxy(Px+14,Py) == line){
        erase_car();
        Px = Px+1;
        if((Px==23 || Px == 46))
            Px++;
        print_car();
    }
}
void move_car_up(int i){
    if((Py >= 25) && (i%2 == 0)){
        erase_car();
        Py = Py-1;
        print_car();
    }
}
void move_car_down(int i){
    if((Py < 26)&& (i%2 == 0)){
        erase_car();
        Py = Py+1;
        print_car();
    }
}


void move_enemy1(int i){ //vertical
    if(getCharAtxy(Ex[0]+4,Ey[0]+10) == ' '){
        erase_enemy(0);
        if(i%6 == 0){
            if(Ey[0]<11)
                Ey[0]++;
        }

        print_enemy1();
    }
}

void move_enemy2(int i){ //diagonal

    if(getCharAtxy(Ex[1]+1,Ey[1]) == ' ' && i%6 == 0){
        erase_enemy(1);
            if(Ey[1]<13)
                Ey[1]++;
    }
    if(getCharAtxy(Ex[1]+15,Ey[1]) == ' '){
        if((Ex[1]<52) && (i%6 == 0))
        Ex[1]++;
    }   

    print_enemy2();
}

void move_enemy3(int i){  //horizontal
    if(i%6 == 0){
        erase_enemy(2);
        if(Px+3<Ex[2]){
            if(getCharAtxy(Ex[2]-1,Ey[2]) == ' ' && Ex[2]> 20)
                Ex[2]--;
        }
        else if(Px-3>Ex[2]){
            if(getCharAtxy(Ex[2]+15,Ey[2]) == ' '&& Ex[2]<38)
                Ex[2]++;
        }
        print_enemy3();
    }
}

void print_lines(){
        gotoxy(lax,ly);
        cout<<line;
        gotoxy(lbx,ly);
        cout<<line;
        ly++;
        if(ly == 36)
            ly = 1;
}

void erase_lines(){

        gotoxy(e_lax,e_ly);
        cout<<" ";
        gotoxy(e_lbx,e_ly);
        cout<<" ";
        e_ly++;
        if(e_ly == 36)
            e_ly = 1;
        
}

void move_lines(int erase_permit){

    print_lines();
    if(erase_permit>9)  //decides the lenght of lines
        erase_lines();
}

void print_car(){

    gotoxy(Px,Py);
    cout<<car[0];
    gotoxy(Px,Py+1);
    cout<<car[1];
    gotoxy(Px,Py+2);
    cout<<car[2];
    gotoxy(Px,Py+3);
    cout<<car[3];
    gotoxy(Px,Py+4);
    cout<<car[4];
    gotoxy(Px,Py+5);
    cout<<car[5];
    gotoxy(Px,Py+6);
    cout<<car[6];
    gotoxy(Px,Py+7);
    cout<<car[7];
    gotoxy(Px,Py+8);
    cout<<car[8];
}
void erase_car(){
    string space = "              ";
    for (int i = 0; i < 9; i++)
    {
        gotoxy(Px,Py+i);
        cout<<space;
    }
    
}

void print_enemy1(){

    gotoxy(Ex[0],Ey[0]);
    cout<<enemy1[0];
    gotoxy(Ex[0],Ey[0]+1);
    cout<<enemy1[1];
    gotoxy(Ex[0],Ey[0]+2);
    cout<<enemy1[2];
    gotoxy(Ex[0],Ey[0]+3);
    cout<<enemy1[3];
    gotoxy(Ex[0],Ey[0]+4);
    cout<<enemy1[4];
    gotoxy(Ex[0],Ey[0]+5);
    cout<<enemy1[5];
    gotoxy(Ex[0],Ey[0]+6);
    cout<<enemy1[6];
    gotoxy(Ex[0],Ey[0]+7);
    cout<<enemy1[7];
    gotoxy(Ex[0],Ey[0]+8);
    cout<<enemy1[8];
}
void print_enemy2(){
    gotoxy(Ex[1],Ey[1]);
    cout<<enemy2[0];
    gotoxy(Ex[1],Ey[1]+1);
    cout<<enemy2[1];
    gotoxy(Ex[1],Ey[1]+2);
    cout<<enemy2[2];
    gotoxy(Ex[1],Ey[1]+3);
    cout<<enemy2[3];
    gotoxy(Ex[1],Ey[1]+4);
    cout<<enemy2[4];
    gotoxy(Ex[1],Ey[1]+5);
    cout<<enemy2[5];
    gotoxy(Ex[1],Ey[1]+6);
    cout<<enemy2[6];
    gotoxy(Ex[1],Ey[1]+7);
    cout<<enemy2[7];
    gotoxy(Ex[1],Ey[1]+8);
    cout<<enemy2[8];
}
void print_enemy3(){
    gotoxy(Ex[2],Ey[2]);
    cout<<enemy3[0];
    gotoxy(Ex[2],Ey[2]+1);
    cout<<enemy3[1];
    gotoxy(Ex[2],Ey[2]+2);
    cout<<enemy3[2];
    gotoxy(Ex[2],Ey[2]+3);
    cout<<enemy3[3];
    gotoxy(Ex[2],Ey[2]+4);
    cout<<enemy3[4];
    gotoxy(Ex[2],Ey[2]+5);
    cout<<enemy3[5];
    gotoxy(Ex[2],Ey[2]+6);
    cout<<enemy3[6];
    gotoxy(Ex[2],Ey[2]+7);
    cout<<enemy3[7];
    gotoxy(Ex[2],Ey[2]+8);
    cout<<enemy3[8];
}

void erase_enemy(int n){
    string space = "             ";
    for (int i = 0; i < 9; i++)
    {
        gotoxy(Ex[n],Ey[n]+i);
        cout<<space;
    }
}
void initialize_vehicles(){

car[0] = {' ',' ',' ','_',light,'_','_','_',light,'_',' ',' ',' '};
car[1] = "  /_______\\  ";
car[2] = " /         \\ ";
car[3] = "[|  \\   /  |]";
car[4] = " |   \\_/   | ";
car[5] = pistol+"|  | | |  | ";
car[6] = " |  | | |  | ";
car[7] = "[|___/_\\___|]";
car[8] = " |_________| ";

enemy1[0] = {' ',' ',' ','_',light,'_','_','_',light,'_',' ',' ',' '};
enemy1[1] = "  /_______\\  ";
enemy1[2] = " /         \\ ";
enemy1[3] = "[|  |   |  |]";
enemy1[4] = " |   \\_/   | ";
enemy1[5] = " |         | ";
enemy1[6] = " |  /---\\  | ";
enemy1[7] = "[|__|   |__|]";
enemy1[8] = " \\_________/ ";

enemy2[0] = {' ',' ',' ','_',light,'_','_','_',light,'_',' ',' ',' '};
enemy2[1] = "  /_______\\  ";
enemy2[2] = " /         \\ ";
enemy2[3] = "[|  \\___/  |]";
enemy2[4] = " |   |_|   | ";
enemy2[5] = " |         | ";
enemy2[6] = " |  /___\\  | ";
enemy2[7] = "[|_/_____\\_|]";
enemy2[8] = " \\_________/ ";  

enemy3[0] = {' ',' ',' ','_',light,'_','_','_',light,'_',' ',' ',' '};
enemy3[1] = "  /_______\\  ";
enemy3[2] = " /         \\ ";
enemy3[3] = "[| |     | |]";
enemy3[4] = " | |_____| | ";
enemy3[5] = " |         | ";
enemy3[6] = " |  /---\\  | ";
enemy3[7] = "[|_|     |_|]";
enemy3[8] = " \\_________/ ";
}
void print_header(){

    system("cls");
    cout<<"____________________________________________________________________________________________________________________________________________\n";
    cout<<"|                                                                                                                                          |\n";
    cout<<"| ######  ######     #####    #######  #######  ######    #####          #####   ###   ##    #####     #####   ######  #######   ######    |\n";
    cout<<"|   ##     ##  ##   ##   ##    ##  ##   ##  ##    ##     ##   ##        ##   ##   ##   ##   ##   ##   ##   ##    ##     ##  ##    ##  ##   |\n";
    cout<<"|   ##     ##  ##   ##   ##    ##       ##        ##     ##             ##        ##   ##   ##   ##   ##   ##    ##     ##        ##  ##   |\n";
    cout<<"|   ##     #####    #######    ####     ####      ##     ##              #####    #######   ##   ##   ##   ##    ##     ####      #####    |\n";
    cout<<"|   ##     ###      ##   ##    ##       ##        ##     ##                  ##   ##   ##   ##   ##   ##   ##    ##     ##        ###      |\n";
    cout<<"|   ##     ## ##    ##   ##    ##       ##        ##     ##   ##        ##   ##   ##   ##   ##   ##   ##   ##    ##     ##  ##    ## ##    |\n";
    cout<<"|   ##     ##  ###  ##   ##   ####     ####     ######    #####          #####    ##   ###   #####     #####     ##    #######    ##  ###  |\n";
    cout<<"|__________________________________________________________________________________________________________________________________________|\n";
}
void print_road(){
    gotoxy(0,0);
    cout<<"##############################################################################################"<<endl;
    cout<<"|                                                                    |                       |"<< endl;
    cout<<"|                                                                    |      --STATICS--      |"<< endl;
    cout<<"|                                                                    |                       |"<< endl;
    cout<<"|                                                                    |  SCORE :              |"<< endl;
    cout<<"|                                                                    |  HEALTH               |"<< endl;
    cout<<"|                                                                    |  DAMAGE: 1x           |"<< endl;
    cout<<"|                                                                    |                       |"<< endl;
    cout<<"|                                                                    |  ENEMY 1 health: @@@@ |"<< endl;
    cout<<"|                                                                    |  ENEMY 2 health: @@@@ |"<< endl;
    cout<<"|                                                                    |  ENEMY 3 health: @@@@ |"<< endl;
    cout<<"|                                                                    |                       |"<< endl;
    cout<<"|                                                                    |-----------------------|"<< endl;
    cout<<"|                                                                    |                       |"<< endl;
    cout<<"|                                                                    |                       |"<< endl;
    cout<<"|                                                                    |                       |"<< endl;
    cout<<"|                                                                    |                       |"<< endl;
    cout<<"|                                                                    |                       |"<< endl;
    cout<<"|                                                                    |                       |"<< endl;
    cout<<"|                                                                    |                       |"<< endl;
    cout<<"|                                                                    |-----------------------|"<< endl;
    cout<<"|                                                                    |                       |"<< endl;
    cout<<"|                                                                    |       --MENU--        |"<< endl;
    cout<<"|                                                                    |                       |"<< endl;
    cout<<"|                                                                    |  Press 0 to start     |"<< endl;
    cout<<"|                                                                    |  Press 1 for MainMenu |"<< endl;
    cout<<"|                                                                    |  Press 2 to exit      |"<< endl;
    cout<<"|                                                                    |                       |"<< endl;
    cout<<"|                                                                    |     --CONTROLS--      |"<< endl;
    cout<<"|                                                                    |                       |"<< endl;
    cout<<"|                                                                    |  Accelerate: up key   |"<< endl;
    cout<<"|                                                                    |  Break: down key      |"<< endl;
    cout<<"|                                                                    |  Left: down key       |"<< endl;
    cout<<"|                                                                    |  Right: down key      |"<< endl;
    cout<<"|                                                                    |  Shoot: space bar     |"<< endl;
    cout<<"|                                                                    |                       |"<< endl;
    cout<<"##############################################################################################"<<endl;
    // (64+24)x37
}