#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
void cls(),enter(),intro(),mainMenu(),loginPage(),registerPage(),caesar(const char code[]),loadData();
void town(),home(),printScore(),saveToFile(),blackSmith(),buyWeap(),printMap(),loadMap(),miniGame(),shot(),printHuntMap();
bool caesarCheck(const char code[], const char pass[]);

struct User{
	int id;
	char name[100];
	char pass[100];
	int weaponId;
	int score;
}user[1000];
int no,log;

struct Sort{
	char name[100];
	int score;
}sort[1000];

void mergeSort(Sort sort[], int left, int right), merge(Sort sort[],int left, int mid, int right);

char map[50][50],temp;
char huntMap[15][40];

char playerWeapon[100];
int playerScore,weaponDamage;
int playerHp,weaponId,playerX,playerY;

bool newadd,game,mini;

int ammo,stock,enemy;

int xenemy,yenemy,hpenemy;
int x1,x2,x3,x4;
int y1,y2,y3,y4;

void printHuntMap(){
	puts("+----------------------------------------+");
	for(int j=0;j<15;j++){
		printf("|");
		for(int i=0;i<40;i++){
			if(i>=x1 && i<=x2 && j>=y1 && j<=y2 && huntMap[j][i]!='X' && huntMap[j][i]!='S'){
				printf("H");
			}
			else if(i>=x1 && i<=x2 && j>=y1 && j<=y2 && huntMap[j][i]=='S')
				printf("%c",huntMap[j][i]);
			else
				if(huntMap[j][i]=='S')
					printf(" ");
				else 
					printf("%c",huntMap[j][i]);
		}
		printf("|");
		puts("");
	}
	printf("+----------------------------------------+"); printf("\tEnemy Hp : %d\n",hpenemy);
	puts("\n");
	printf("\tAmmo 	: %d\tPress q for exit\n", ammo);
	printf("\tHp	: %d\tPress r for reload,your stock is : %d\n", playerHp,stock);
	puts("\n\t\tPress[Enter] to attack");
	printf(" \t\tEnemy Count : %d\n", enemy);
}

void shot(){
	if(rand()%10 == 0){
		huntMap[yenemy][xenemy] = ' ';
		xenemy = rand()%40;
		yenemy = rand()%15; 
		huntMap[yenemy][xenemy] = 'S';
	}
	else if(xenemy>=x1 && xenemy<=x2 && yenemy>=y1 && yenemy<=y2)
		hpenemy-=(rand()%weaponDamage);
		
	if(hpenemy<=0){
		user[log].score=+(rand()%100);
		huntMap[yenemy][xenemy] = 'X';
		xenemy = rand()%40;
		yenemy = rand()%15; 
		huntMap[yenemy][xenemy] = 'S';
		hpenemy = rand()%200;
		enemy--;
	}
}

void miniGame(){
	mini = true;ammo=24,stock=5;enemy=5;
	x1=10;y1=5;
	x2=18;y2=9;
	x3=10;y3=9;
	x4=18;y4=5;
	xenemy = rand()%40;
	yenemy = rand()%15;
	huntMap[yenemy][xenemy] = 'S';
	hpenemy = rand()%200;
	char move;
	int count=-1;
	do{
		cls();
		if(!enemy){
			puts("Game Over!!\nPlease Come Again");
			enter();
			break;
		}
		count++;
		count%=3;
		if(count==0)
			playerHp-=(rand()%10+1);
			
		if(playerHp<=0){
			puts("Your Hp is below 1, go Rest!!");
			enter();
			break;
		}
		printHuntMap();
		move ='\0';
		move = getch();
		switch(move){
			case 'w':
				if(y1-1>=0){
					y1--;y2--;
					y3--;y4--;	
				}
				break;
			case 's':
				if(y2+1<=15){
					y1++;y2++;
					y3++;y4++;
				}
				break;
			case 'a':
				if(x1-1>=0){
					x1-=2;x2-=2;
					x3-=2;x4-=2;
				}
				break;
			case 'd':
				if(x2+1<=40){
					x1+=2;x2+=2;
					x3+=2;x4+=2;
				}
				break;
			case 'r':
				if(stock<=0) {
					puts("No Ammo");
					enter();
				}
				else{
					ammo = 24;
					stock--;
				}
				break;
			case 'q':
				mini = false;
				break;
			case '\r':
				if(ammo<=0) {
					puts("No Ammo");
					enter();
				}
				else{
					ammo--;
					shot();
				}
		}
	}while(mini);
}

void loadMap(){
	FILE *load = fopen("Map.txt", "r");
	int i=0;
	while(!feof(load)){
		fscanf(load, "%[^\n]\n", map[i]);
		i++;
	}
	printf("%d %d\n", i, strlen(map[i-1]));
	for(int j=0;j<i;j++){
		printf("%s\n", map[j]);
	}
}

void printMap(){
	if(playerHp<=0) playerHp=0;
	for(int i=0;i<18;i++){
		printf("%s", map[i]);
		if(i==15) printf("\tUser Name : %s", user[log].name);
		if(i==16) printf("\tUser HP : %d", playerHp);
		if(i==17) printf("\tUser Weapon : %s", playerWeapon);
		puts("");
	}
	puts("");
	puts("press [w|a|s|d] to move");
	puts("[H] : Home");
	puts("[B] : Blacksmith");
}

void buyWeap(){
	cls();
	puts("Welcome what do you want?");
	puts("1. The Dominator [0 point's]");
	puts("2. The Helmet [300 point's]");
	puts("3. Hecate [800 point's]");
	puts("4. Exit");
	char buy;
	do{
		printf(">> ");
		scanf("%c",&buy);getchar();
		switch(buy){
			case '1':
				user[log].score -= 0;
				user[log].weaponId = 0;
				weaponDamage = 30;
				strcpy(playerWeapon, "The Dominator");
				puts("Thanks for Buying!!");
				enter();
				break;
			case '2':
				if(user[log].score>=300){
					user[log].score -= 300;
					user[log].weaponId = 1;
					weaponDamage = 50;
					strcpy(playerWeapon, "The Helmet");
					puts("Thanks for Buying!!");
					enter();
				}
				else puts("You don't have enough score...\n");
				break;
			case '3':
				if(user[log].score>=800){
					user[log].score -= 800;
					user[log].weaponId = 2;
					weaponDamage = 120;
					strcpy(playerWeapon, "Hecate");
					puts("Thanks for Buying!!");
					enter();
				}
				else puts("You don't have enough score...\n");
				break;
		}
		if(buy>=49 && buy<=52) 
			break;
	}while(true);
}

void blackSmith(){
	cls();
	char input;
	do{
		puts("Blacksmith!!");
		puts("1. Look Weapon");
		puts("2. Exit");
		do{
			printf(">> ");
			scanf("%c",&input);getchar();
			if(input=='1')
				buyWeap();
			if(input=='1'||input=='2')
				break;
		}while(true);
	}while(input!='2');
}

void saveToFile(){
	FILE *data = fopen("User.txt","w");
	for(int i=0;i<no;i++){
		fprintf(data, "%d#%s#%s#%d#%d\n", user[i].id, user[i].name, user[i].pass,user[i].weaponId, user[i].score);
	}
	fprintf(data, "aodwoqkwd");
	fclose(data);
}

void printScore(){
	cls();
	puts("Leader Board Score");
	puts("================================");
	for(int i=0;i<no-1;i++){
		printf("%d %s\n", sort[i].score, sort[i].name);
	}
	enter();
}

void home(){
	cls();
	char input;
	printf("%s Home!\n", user[log].name);
	do{
		puts("1. Look Leader");
		puts("2. Save");
		puts("3. Rest");
		puts("4. Exit");
		do{
			printf(">> ");
			scanf("%c",&input);getchar();
			switch(input){
				case '1':
					mergeSort(sort,0,newadd?no-2:no-3);
					printScore();
					break;
				case '2':
					user[log].score = playerScore;
					user[log].weaponId = weaponId;
					saveToFile();
					break;
				case '3':
					if(user[log].score>=10){
						user[log].score-=10;
						puts("Restore 100 HP, -10 score...");
						playerHp=100;
					}
					else puts("You don't have enough score...\n");
					enter();
					break;
			}
			if(input=='1' || input=='2' || input=='3' ||input=='4')
				break;
		}while(true);
		if(input=='4')
			break;
	}while(input!='4');
	
	
}

void town(){
	loadMap();
	char tempmap = '.';
	game = true;
	playerX=13;playerY=13;
	playerHp=100;
	do{
		cls();
		map[playerY][playerX] = 'V';
		printMap();
		temp = getch();
		map[playerY][playerX]=tempmap;
		switch(temp){
			case 'a':
				map[playerY][playerX-1] == '#' ? : playerX--;
				break;
			case 'd':
				map[playerY][playerX+1] == '#' ? : playerX++;
				break;
			case 'w':
				map[playerY-1][playerX] == '#' ? : playerY--;
				break;
			case 's':
				map[playerY+1][playerX] == '#' ? : playerY++;
				break;
		}
		tempmap = map[playerY][playerX];
		if(map[playerY][playerX] == ' ') {
			playerY++;
			miniGame();		
			tempmap = '.';
		}
		if(map[playerY][playerX] == 'B') blackSmith();
		if(map[playerY][playerX] == 'H') home();
	}while(game);
}

void loadData(){
	no=0;
	FILE *apa = fopen("User.txt","r");
	while(!feof(apa)){
		fscanf(apa, "%d#%[^#]#%[^#]#%d#%d\n",&user[no].id, user[no].name, user[no].pass,&user[no].weaponId, &user[no].score);
		
		strcpy(sort[no].name,user[no].name);
		sort[no].score = user[no].score;
//		printf("%d %s %s %d %d\n",user[no].id, user[no].name, user[no].pass,user[no].weaponId, user[no].score);
		no++;
	}
	fclose(apa);
}

bool caesarCheck(const char code[], const char pass[]){
	char password[100];
	int key;
	strcpy(password,"\0");
	for(int i=0;code[i]!='\0';i++){
		key = -1;
		if(code[i]>=48 && code[i]<=57)
			key = code[i]+4;
		else if(code[i]>=97 && code[i]<=122)
			key = code[i]-71;
		else if(code[i]>=65 && code[i]<=90)
			key = code[i]-65;
		else if(code[i]==' ') 
			printf(" ");
		else 
			printf("~");
		if(key==-1) 
			continue;
		key+=3;
		key%=62;
		if(key>=0 && key<=25)
			sprintf(password,"%s%c", password,key+65);
		else if(key>=26 && key<=51)
			sprintf(password,"%s%c", password,key+71);
		else if(key>=52 && key<=61)
			sprintf(password,"%s%c", password,key-4);
	}
	return strcmp(password,pass) ? false:true;
}

void caesar(const char code[]){
	char password[100];
	int key;
	strcpy(password,"\0");
	for(int i=0;code[i]!='\0';i++){
		key = -1;
		if(code[i]>=48 && code[i]<=57)
			key = code[i]+4;
		else if(code[i]>=97 && code[i]<=122)
			key = code[i]-71;
		else if(code[i]>=65 && code[i]<=90)
			key = code[i]-65;
		else if(code[i]==' ') 
			printf(" ");
		else 
			printf("~");
		if(key==-1) 
			continue;
		key+=3;
		key%=62;
		if(key>=0 && key<=25)
			sprintf(password,"%s%c", password,key+65);
		else if(key>=26 && key<=51)
			sprintf(password,"%s%c", password,key+71);
		else if(key>=52 && key<=61)
			sprintf(password,"%s%c", password,key-4);
	}
	strcpy(user[no].pass,password);
}

void loginPage(){
	cls();
	loadData();
	if(newadd) 
		no++;
	puts("Pyschopazz");
	enter();
	puts("Login Page\nHello, Let me know who are you");
	char username[100],password[100];
	bool find;
	do{
		find = false;;
		do{
			printf("Username : ");
			scanf("%[^\n]", username);getchar();
			if(strlen(username)<5) puts("Username must more than or equals 5 characters");
			else break;
		}while(true);	
		char password[100],temp;
		do{
			printf("Password : ");
			strcpy(password,"\0");
			do{
				temp = getch();
				if(temp == '\r')
					break;
				printf("*");
				sprintf(password,"%s%c", password,temp);
			}while(true);
		}while(password[0]=='\n');
		
		for(int i=0;i<no;i++){
			if(strcmp(username,user[i].name)==0){
				if(caesarCheck(password,user[i].pass)){
					find = true;
					log = i; break;
				}
			}
		}
		if(!find) puts("Wrong username or password");
	}while(!find);
	if(user[log].weaponId == 0){
		weaponDamage = 30;
		strcpy(playerWeapon, "The Dominator");
	}
	else if(user[log].weaponId == 1){
		weaponDamage = 50;
		strcpy(playerWeapon, "The Helmet");
	}
	else if(user[log].weaponId == 2){
		weaponDamage = 120;
		strcpy(playerWeapon, "Hecate");
	}
	town();
}

void registerPage(){
	cls();
	puts("Register\nHello, Let me know who are you");
	char username[100];
	do{
		printf("Username : ");
		scanf("%[^\n]", username);getchar();
		if(strlen(username)<5) puts("Username must more than or equals 5 characters");
		else break;
	}while(true);
	char password[100],temp;
	do{
		printf("Password : ");
		strcpy(password,"\0");
		do{
			temp = getch();
			if(temp == '\r')
				break;
			printf("*");
			sprintf(password,"%s%c", password,temp);
		}while(true);
	}while(password[0]=='\n');
	caesar(password);
	user[no].id = no;
	strcpy(user[no].name,username);
	user[no].score =0;
	user[no].weaponId =0;
	newadd = true;
}

void mainMenu(){
	cls();
	intro();
	puts("Are you new player or not? [ Y | N ]");
	char temp[10];
	do{
		printf(">> "); scanf("%[^\n]", temp);getchar();
	}while(strcmp(temp,"Y")!=0 && strcmp(temp,"N")!=0);
	switch(temp[0]){
		case 'Y':
			registerPage();
		case 'N':
			loginPage();
	}
}

void intro(){
	puts("A world where a human's state of mind and the criminal potential of their personality can be quantified.");
	puts("While all sorts of inclinations are recorded and policed, these measured numbers used to judge people's");
	puts("souls are commonly called one's... PSYCHO-PASS.");
	enter();
}

int main(){
	loadData();
	mainMenu();
	return 0;
}

void cls(){
	for(int i=0;i<30;i++)puts("");
}

void enter(){
	puts("Press enter to continue...");getchar();
}

void merge(Sort sort[], int left,int mid, int right){
	int kiri = mid - left + 1;
	int kanan = right - mid;
	
	Sort L[kiri],R[kanan];
	
	for(int x=0;x<kiri;x++)
	{
		L[x] = sort[left + x];
	}
	for(int y=0;y<kanan;y++)
	{
		R[y] = sort[mid + 1 + y];
	}
	
	int i=0,j=0,k=left;
	while(i<kiri && j<kanan)
	{
		if(L[i].score<=R[j].score)
		{
			sort[k] = L[i];
			i++;
		}
		else
		{
			sort[k] = R[j];
			j++;
		}
		k++;
	}
	
	while(i<kiri)
	{
		sort[k] = L[i];
		i++;k++;
	}
	
	while(j<kanan)
	{
		sort[k] = R[j];
		j++;k++;
	}
}

void mergeSort(Sort sort[],int left, int right){
	if(left<right)
	{
		int mid = (left + right) / 2;
		
		mergeSort(sort,left,mid);
		mergeSort(sort,mid+1,right);
		
		merge(sort,left,mid,right);
	}
}
