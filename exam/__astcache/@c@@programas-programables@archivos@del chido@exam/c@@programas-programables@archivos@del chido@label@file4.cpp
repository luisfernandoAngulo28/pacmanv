#include <iostream>
#include <conio.h>
#include <tchar.h>
#include <time.h>
#include <windows.h>
#include "UMatrizC.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;

void gotoxy(int x , int y){
COORD c;
c.X=x;
c.Y=y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void hideCursor(){
CONSOLE_CURSOR_INFO cursor;
cursor.dwSize=100;
cursor.bVisible=false;
SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

int life =5;
int const screenHeight=32;
int const screenWidth=32;
MatrizC* mapm =new  MatrizC;
MatrizC* stagem =new  MatrizC;
//stagem.dimensionar(22,22);

class ser{
public:
int x;
int y;
char dir;
int delay;
int count_delay;

 void dibuja(){
 if (dir=='U') mapm->poner(y,x,1);
 else if (dir=='D') mapm->poner(y,x,2) ;
 else if (dir=='L')  mapm->poner(y,x,3);
 else if (dir=='R' || dir=='S')  mapm->poner(y,x+1,4);
 }

 void move(){
  dead();
  if (count_delay == delay) {
	if (dir=='U' && !collision(x,y-1)) y--;
	if (dir=='D' && !collision(x,y+1)) y++;
	if (dir=='L' && !collision(x+1,y)) x++;
	if (dir=='R' && !collision(x-1,y)) x--;
   count_delay = 0;
  }
  count_delay++;
  eat();
 }

  bool collision(int fx , int fy){
   if (mapm->elemento(fy,fx)== 9) return true;
   return false;
  }

  void dead(){
   if (mapm->elemento(y,x) ==5) {
   dir = 'S' ;
   x=10;
   y=15;
   life--;
   }
  }

  void eat(){
   if (mapm->elemento(y,x) == 8) {
   stagem->poner(y,x,' ');
   }
  }
};

void llenar(string texto){
	char x;
	char  sos;
	int i=1;
	int j=1;
	ifstream archivo;//"C://admin//esg.txt"
	archivo.open(texto.c_str(),ios::in);
	if (archivo.fail()){
		cout<<"no";
	}else{
	  while (!archivo.eof()){
	  archivo.get(x);
	  sos=x;
	  if (x!=10) {
	   if (!archivo.eof()) {
	   stagem->poner(i,j,x);
	   }
	  j++;
	   if (j>=screenWidth) {
		i++;
		j=1;
	   }
	  }else{
	   i++;
	   j=1;
	   }

	  }

	 }

}


ser explorador;


void setup(){
srand(time(NULL));
/*explorador.x=10;
explorador.y=15;
explorador.dir='S';
explorador.delay=2; */

for (int i = 0; i < screenHeight ; i++) {
		for (int j = 0; j < screenWidth; j++) {
			  if (stagem->elemento(i,j)=='v') {
				explorador.x=j;
				explorador.y=i;
				explorador.dir='S';
				explorador.delay=2;
			  }
		}
}


}

void layoutm(){
 // for (int i = 0; i < 7; i++) fantasmatico[i].draw();
	for (int i = 1; i < screenHeight+1 ; i++) {
	  for (int j = 1; j < screenWidth+1; j++) {
		 if (stagem->elemento(i,j) == '#') mapm->poner(i,j,9);
		 else if (stagem->elemento(i,j) == '.') mapm->poner(i,j,8);
		 //else if  (stagem->elemento(i,j) == 'v'){ mapm->poner(i,j,1); explorador.x=j; explorador.y=i; }
		 else mapm->poner(i,j,0);
	  }
	}

}


void displaym (){
 //gotoxy(1,2); cout <<"LIFE:  "<<life;
 layoutm();
 explorador.dibuja();
	  for (int i = 1; i < screenHeight+1 ; i++) {
		cout<<endl;
		for (int j = 1; j < screenWidth; j++) {
           gotoxy(j+1,i);
		   if (mapm->elemento(i,j) == 9) cout << char(219);
		   if (mapm->elemento(i,j)  == 8) cout << char(250);
		   if (mapm->elemento(i,j)  == 1) cout << char(86);
		   if (mapm->elemento(i,j)  == 2) cout << char(94);
		   if (mapm->elemento(i,j)  == 3) cout << char(62);
		   if (mapm->elemento(i,j)  == 4) cout << char(60);
		   if (mapm->elemento(i,j)  == 5) cout << char(234);
		   if (mapm->elemento(i,j) == 0) cout << " ";
		}
	  }

}
 void input(){ 
  if (kbhit()) {
   switch(getch()){
	case 80:
	if (!explorador.collision(explorador.x,explorador.y+1) && (explorador.y<screenWidth-1))
	explorador.y++; explorador.dir = 'D';
	break;

	case 72:
	if (!explorador.collision(explorador.x,explorador.y-1)&& (explorador.y>0))
	explorador.y--; explorador.dir = 'U';
	break;

	case 75:
	if (!explorador.collision(explorador.x-1,explorador.y)&& (explorador.x>0))
	explorador.x--; explorador.dir = 'L';
	break;

	case 77:
	if (!explorador.collision(explorador.x+1,explorador.y)&& (explorador.x<screenHeight-2))
	explorador.x++; explorador.dir = 'R';
	break;

   }
   explorador.eat();
  }
 }


void movements(){
 explorador.move();
}

int main()
{

stagem->dimensionar(screenHeight,screenWidth+1);
mapm->dimensionar(screenHeight,screenWidth+1);
llenar("a.txt");
setup();
 HWND s = GetConsoleWindow();
 MoveWindow(s,300,200,550,550,true);
 hideCursor();
 setup();
 displaym();
/*explorador.x=2;
explorador.y=2;
cout<<endl<<stagem->to_str()<<endl;
cout<<mapm->to_str()<<endl;

*/

 while (life>0){
   displaym();
   //explorador.x++;
   input();
 }


 system("pause");
}
