#include<iostream.h>
#include<graphics.h>
#include<stdlib.h>
#include<conio.h>
#include<process.h>
#include<dos.h>
#include<stdio.h>
#include<stddef.h>
#include<fstream.h>
#include<string.h>


#define MAXMENUS 6
#define MAXITEMS 9

#define TRUE 1
#define False 0

#define F1 59
#define ESC 27
#define ENTER 13

#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77

#define TAB 9
#define PGUP 73
#define PGDN 81
#define HOME 71
#define END 79
#define DEL 83
#define BKSP 8

#define BUFFLEN 4096

#define FileLength 8

#define PasswordLength 15
#define PwdSymbol '*'

//using namespace std;

char ScreenBuffer[BUFFLEN];
class Theme
{
	public:
		int FILE_BAR_BACKGROUND_COLOR,BAR_COLOR;
		int MENU_COLOR,MENU_BACKGROUND;
		int MENU_ACTIVE_COLOR,MENU_ACTIVE_BACKGROUND;
		int TASKBAR_COLOR,TASKBAR_BACKGROUND,TASKBAR_INFO_COLOR;
		int HELP_COLOR;
		int SCREEN_COLOR,SCREEN_BACKGROUND;
		int TEXT_COLOR;
}Obj;
class User
{
	public:
	char user[20],password[12];
	char Mobile[10];
		void setdata()
		{
			char confirm_password[12];
			cin>>user;
			//strcpy(user,str);
			gotoxy(18,7);
			cin>>password;
			gotoxy(18,9);
			cin>>confirm_password;
			if(strcmp(password,confirm_password)!=0)
			{
				cout<<"password not matched";
			}
			gotoxy(18,12);
			cin>>Mobile;
		}
		friend istream& operator >>(istream& is,User& u)
		{
			is >> u.user;
			is >> u.password;
			is >> u.Mobile;
			return is;
		}
		friend ostream& operator >>(ostream& os,User& u)
		{
			os << u.user<<" "<< u.password<<" "<< u.Mobile <<endl;
			return os;
		}
};
class Product
{
	public:
	char category[14],name[20];
	char mobile[12],address[30],landmark[25];
	int price,pincode;
	void setdata()
	{
		_setcursortype(_NORMALCURSOR);
		gotoxy(17,4);
		cin >> name;
		gotoxy(17,6);
		cin >> category;
		gotoxy(46,6);
		cin >> price;
		gotoxy(17,8);
		cin >> landmark;
		gotoxy(17,9);
		cin >> address;
		gotoxy(17,11);
		cin >> pincode;
		gotoxy(38,11);
		cin >> mobile;
		_setcursortype(_NOCURSOR);
	}
	friend istream& operator >>(istream& is,Product& p)
	{

			is >> p.name;
			is >> p.category;
			is >> p.price;
			is >> p.landmark;
			is >> p.address;
			is >> p.pincode;
			is >> p.mobile;
			return is;
	}
	friend ostream& operator >>(ostream& os,Product& p)
	{
			os << p.name<<" "<< p.category<<" "<< p.price<<" "<< p.landmark<<" "<< p.address;
			os <<" "<< p.pincode<<" "<< p.mobile<< endl;;
			return os;
	}
};

char ch;
void Welcome(void);
void Add_Menu(void);
void Open(void);
void EXIT(void);
void Help(void);
void MenuAction(int);
void Home_Menu(void);
void Account_Menu(void);
void Filter_Menu(void);
void Search_Menu(void);
void BEEP(void);
void SignUP(void);
void Login(void);
char *Menu[MAXMENUS]={" HOME "," FILTER "," SEARCH "," SELL "," ACCOUNT "," EXIT "};
char *MenuInfo[MAXMENUS]={
				"Products for Sell..",
				"Sort as you like...",
				"Search for product.",
				"Add product to Sell",
				"Manage Account.....",
				"Exit program (ESC)."
				};


int X=0,Y=0;
int FMI=0,EMI=0,AMI=0;
int Menu_Item=0;
int FLength,PwLength;

//100 Extra for management
char OutputFile[FileLength+100],Password[PasswordLength+100];
char InputFile[FileLength+100];
char Pass[PasswordLength+100];
int main()
{
	asm{
	//"movb $0x0, %%ah;"
	    //"movb $0x10, %%al;"
	    //"int $0x10;"
	    //:
	    //:"r"(alphabet)
	    //:"%ah","%al"

		mov ah,0X10
		mov al,0X10     //set Graphics Mode(Full screen)
		int 0X10
	};
	textmode(3);
	Welcome();
	getch();
	return 0;
}
void Welcome(void)
{
	FILE *fp;
	fp=fopen("PROEX.INF","rb");
	if(!fp)
	{
		Obj.FILE_BAR_BACKGROUND_COLOR=10;
		Obj.BAR_COLOR=0;
		Obj.MENU_COLOR=0;
		Obj.MENU_BACKGROUND=10;
		Obj.MENU_ACTIVE_COLOR=10;
		Obj.MENU_ACTIVE_BACKGROUND=0;
		Obj.TASKBAR_COLOR=0;
		Obj.TASKBAR_BACKGROUND=10;
		Obj.TASKBAR_INFO_COLOR=10;
		Obj.HELP_COLOR=4;
		Obj.SCREEN_COLOR=10;
		Obj.SCREEN_BACKGROUND=7;
		Obj.TEXT_COLOR=0;
	}
	else
	{
		fread(&Obj,sizeof(Obj),1,fp);
	}
	fclose(fp);  	//Close the File
	/*window(1,1,80,25);
	textcolor(Obj.TEXT_COLOR);
	textbackground(0);*/

	_setcursortype(_NOCURSOR);
	//clrscr();
	int x;
	gotoxy(1,1);
	textbackground(Obj.FILE_BAR_BACKGROUND_COLOR);
	for(x=0;x<80;x++)
	{
		cprintf(" ");
	}
	window(1,25,80,25);
	gotoxy(1,1);
	textbackground(Obj.TASKBAR_BACKGROUND);

       //	gotoxy(3,2);
     /*	window(3,2,8,7);
      //	readimagefile("12312.jpg",3,2,8,7);     */


	for(x=0;x<80;x++)
	{
		cprintf(" ");
	}
	window(1,1,80,25);
	textcolor(Obj.SCREEN_COLOR);
	textbackground(Obj.SCREEN_BACKGROUND);



	gotoxy(1,2);
	for(x=1;x<=80*23;x++)
		cprintf(" ");

	textcolor(Obj.HELP_COLOR);
	textbackground(Obj.TASKBAR_BACKGROUND);
	gotoxy(1,25);
	cprintf("F1: HELP  |");
	while(TRUE)
	{
		gotoxy(1,1);
		highvideo();
		textcolor(15);
		textbackground(4);
		cprintf("Rent2buy.com ");

		textcolor(Obj.MENU_COLOR);
		textbackground(Obj.MENU_BACKGROUND);
		gotoxy(16,1);
		cprintf(Menu[0]);

		gotoxy(24,1);
		cprintf(Menu[1]);

		gotoxy(34,1);
		cprintf(Menu[2]);

		gotoxy(44,1);
		cprintf(Menu[3]);

		gotoxy(52,1);
		cprintf(Menu[4]);

		gotoxy(63,1);
		cprintf(Menu[5]);
		textcolor(Obj.TASKBAR_COLOR);
		textbackground(Obj.TASKBAR_BACKGROUND);
		gotoxy(13,25);
		cprintf(MenuInfo[Menu_Item]);

		switch(Menu_Item)
		{
			case 0:
				X=16;
				break;
			case 1:
				X=24;
				break;
			case 2:
				X=34;
				break;
			case 3:
				X=44;
				break;
			case 4:
				X=52;
				break;
			case 5:
				X=63;
		}
		textcolor(YELLOW);
		textbackground(BLACK);

		gotoxy(X,1);
		cprintf(Menu[Menu_Item]);

		ch=getch();

		if(ch==0)
			ch = getch();
		switch(ch)
		{
				case F1:
    //					Help();
					break;
				case ESC:
					EXIT();
					break;
				case RIGHT_ARROW:
					Menu_Item++;
					if(Menu_Item>5)
						Menu_Item=0;
					break;
				case LEFT_ARROW:
					Menu_Item--;
					if(Menu_Item<0)
						Menu_Item=5;
					break;
				case ENTER:
				case DOWN_ARROW:
					MenuAction(Menu_Item);
					break;
		}

	}
}


void MenuAction(int x)
{
	switch(x)
	{
		case 0:
			Home_Menu();
			break;
		case 1:
			Filter_Menu();
			break;
		case 2:
			Search_Menu();
			break;
		case 3:
			Add_Menu();
			break;
		case 4:
			Account_Menu();
			break;
		case 5:
			EXIT();
			break;
		default:
		{
			BEEP();
			Welcome();
		}
       }
}

void Home_Menu(void)
{
   Product p;
   //	window(1,2,85,24);
   int i=1;
   int Y = 3;
   ifstream file("ProductData.txt",ios::in);
   textattr(0XF0+BLINK);
   while(i<5)
   {
	file >> p;
	gotoxy(1,Y++);
	cprintf(" %d. ",i);
	cprintf(" %s ",p.name);
	gotoxy(1,Y);
	cprintf("  %s ",p.category);
	gotoxy(25,Y++);
	cprintf("Cost: %d Rs ",p.price);
	gotoxy(3,Y++);
	cprintf("Address : %s,\n",p.landmark);
	gotoxy(13,Y++);
	cprintf("%s,\n",p.address);
	gotoxy(13,Y++);
	cprintf("%d\n",p.pincode);
	gotoxy(13,Y++);
	cprintf("Phone : %s",p.mobile);
	i++;
   }
}
void Filter_Menu()
{
	window(24,2,55,9);
	textbackground(14);
	clrscr();
	gotoxy(1,1);
	textbackground(1);
	clreol();
	gotoxy(15,1);
	cprintf("SORT");
	textattr(0x6F);
	gotoxy(2,3);
	cprintf("PRICE : ");
	textattr(0x6E);
	gotoxy(2,5);
	cprintf("Min : ");
	gotoxy(18,5);
	cprintf("Max : ");
	gotoxy(13,7);
	textattr(0x31);
	cprintf(" Filter ");
	textbackground(7);
	gotoxy(8,5);
	for(int i=0;i<7;i++)
		cprintf(" ");
	gotoxy(24,5);
	for(i=0;i<7;i++)
		cprintf(" ");
	ch = getch();
	if(ch == ESC)
		Welcome();
	int min,max;
	_setcursortype(_NORMALCURSOR);
	gotoxy(9,5);
	cin >> min;
	gotoxy(25,5);
	cin >> max;
	_setcursortype(_NOCURSOR);
	gotoxy(13,7);
	textattr(0X31+BLINK);
	cprintf(" Filter ");
	Welcome();
}

void Search_Menu()
{
	window(34,2,65,9);
	textbackground(14);
	clrscr();
	gotoxy(1,1);
	textbackground(1);
	clreol();
	gotoxy(15,1);
	cprintf("SEARCH");
	textattr(0x6F);
	gotoxy(2,3);
	cprintf("NAME/CATEGORY : ");
	textattr(0x6E);
	gotoxy(2,5);
	cprintf("Enter : ");

	gotoxy(13,7);
	textattr(0x31);
	cprintf(" Search ");
	textbackground(7);
	gotoxy(12,5);
	for(int i=0;i<18;i++)
		cprintf(" ");
	ch = getch();
	if(ch == ESC)
		Welcome();
	char find[17];
	_setcursortype(_NORMALCURSOR);
	gotoxy(13,5);
	cin >> find;
	_setcursortype(_NOCURSOR);
	gotoxy(13,7);
	textattr(0X31+BLINK);
	cprintf(" Search ");
	Welcome();
}


void Add_Menu()
{
	Product p;
	ofstream fp;
	window(15,5,68,21);
	textbackground(14);
	clrscr();
	gotoxy(1,1);
	textbackground(GREEN);
	clreol();
	gotoxy(21,1);
	cprintf("PRODUCT INFO");
	textattr(0x60);
	gotoxy(3,4);
	cprintf("Product    : ");
	gotoxy(3,6);
	cprintf("Category   : ");
	gotoxy(37,6);
	cprintf("Price : ");
	gotoxy(3,8);
	cprintf("Address    : ");
	gotoxy(3,11);
	cprintf("Pincode    : ");
	gotoxy(29,11);
	cprintf("Phone : ");
	gotoxy(3,13);
	cprintf("Discribtion: ");
	gotoxy(16,4);
	textbackground(7);
	for(int i=0;i<36;i++)
		cprintf(" ");
	gotoxy(16,6);
	for(i=0;i<19;i++)
		cprintf(" ");
	gotoxy(45,6);
	for(i=0;i<7;i++)
		cprintf(" ");
	gotoxy(16,8);
	for(i=0;i<36;i++)
		cprintf(" ");
	gotoxy(16,9);
	for(i=0;i<36;i++)
		cprintf(" ");
	gotoxy(16,11);
	for(i=0;i<10;i++)
		cprintf(" ");
	gotoxy(37,11);
	for(i=0;i<15;i++)
		cprintf(" ");
	gotoxy(16,13);
	for(i=0;i<36;i++)
		cprintf(" ");
	gotoxy(16,14);
	for(i=0;i<36;i++)
		cprintf(" ");
	gotoxy(26,16);
	textattr(0x1E);
	cprintf(" SUBMIT ");
	ch = getch();
	if(ch == ESC)
		Welcome();
	ofstream f;
	f.open("ProductData.txt",ios::in|ios::out|ios::app);
	p.setdata();
	ch = getch();
	if(ch == ESC)
		Welcome();
	f >> p;
	f.close();
	gotoxy(26,16);
	textattr(0x1E+BLINK);
	cprintf(" SUBMIT ");
	Welcome();
}
void Login()
{
	gotoxy(16,11);
	textattr(0x1E);
	cprintf(" SUBMIT ");
	char u_name[20],passwo[20];
	_setcursortype(_NORMALCURSOR);
	gotoxy(18,4);
	cin >> u_name;
	gotoxy(18,7);
	cin >> passwo;
	gotoxy(16,11);
	textattr(0x1E+BLINK);
	cprintf(" SUBMIT ");
	ifstream file("USERDATA.txt",ios::in);
	User u;
	//file.read((char*)&u,sizeof(u));
	file >> u;

	//if(file.is_open())
	//{
		while(!file.eof())
		{

			if(strcmp(u_name,u.user)==0)
			{
				if(strcmp(passwo,u.password)==0)
				{
					Welcome();
					break;
				}
				else
				{
					gotoxy(18,1);
					cout<<" Wrong Username or Password ";
					getch();
					break;
				}
			}
	//		file.read((char*)&u,sizeof(u));
			file >> u;
		}
		file.close();
		_setcursortype(_NOCURSOR);
	//}
}

void SignUP()
{
	User u;
	ofstream f;
	textattr(0x60);
	gotoxy(3,9);
	cprintf("Confirm    : ");
	gotoxy(3,10);
	cprintf("password  ");
	gotoxy(3,12);
	cprintf("Phone no.  : ");
	textbackground(7);
	gotoxy(17,9);
	for(int i=0;i<19;i++)
		cprintf(" ");
	gotoxy(17,12);
	for(i=0;i<19;i++)
		cprintf(" ");
	char username[20];

	gotoxy(16,15);
	textattr(0x1E);
	cprintf(" SUBMIT ");
	gotoxy(18,4);
	_setcursortype(_NORMALCURSOR);
	//cin>>username;
	//f.open(username);
	f.open("UserData.txt",ios::in|ios::out|ios::app);
	u.setdata();
	gotoxy(16,15);
	textattr(0x1E+BLINK);
	cprintf(" SUBMIT ");
	ch = getch();
	if(ch == ESC)
		Welcome();
	f >> u;
       //	f.write((char*)&u,sizeof(u));
	f.close();
	_setcursortype(_NOCURSOR);
}

void Account_Menu(void)
{
	int no=0,g=0,flg=0;
	char *ACC[2] = { " Login " , " Sign Up " };
	window(24,5,60,20);
	textbackground(14);
	clrscr();
	gotoxy(1,1);
	textbackground(GREEN);
	clreol();
	gotoxy(1,2);
	clreol();
	gotoxy(19,1);
	cprintf("|");
	gotoxy(19,2);
	cprintf("|");
	textattr(0x60);
	gotoxy(3,4);
	cprintf("Username   : ");
	gotoxy(2,5);
	cprintf("(without space)");
	gotoxy(3,7);
	cprintf("Password   : ");
	gotoxy(17,4);
	textbackground(7);
	for(int i=0;i<19;i++)
		cprintf(" ");
	gotoxy(17,4);
	for(i=0;i<19;i++)
		cprintf(" ");
	gotoxy(17,7);
	for(i=0;i<19;i++)
		cprintf(" ");
	while(TRUE)
	{
		gotoxy(4,2);
		textattr(0x2F);
		cprintf(ACC[0]);

		gotoxy(26,2);
		cprintf(ACC[1]);
		switch(no)
		{
			case 0:
				g=4;
				break;
			case 1:
				g=26;
		}
		textcolor(YELLOW);
		textbackground(BLACK);

		gotoxy(g,2);
		cprintf(ACC[no]);

		char ch=getch();

		if(ch==0)
			ch = getch();
		switch(ch)
		{
				case F1:
    //					Help();
					break;
				case ESC:
					flg=1;
					break;
				case RIGHT_ARROW:
					no++;
					if(no>1)
						no=0;
					break;
				case LEFT_ARROW:
					no--;
					if(no<0)
						no=1;
					break;
				case ENTER:
				case DOWN_ARROW:
					flg=1;
					if(no == 0)
						Login();
					else
						SignUP();
		}
		if(flg)
		{
			Welcome();
		}
	}
}
void BEEP(void)
{
	sound(666);
	delay(100);
	nosound();
}
void EXIT(void)
{
	textcolor(WHITE);
	textbackground(BLACK);


	_setcursortype(_NORMALCURSOR);
	clrscr();

	exit(1);
}

//--------------------------------------------------------------------------------


/*union REGS reg,i,o;
typedef enum Boolean
{false,true}boolean;
int etat();
int X();
int Y();
void MouseInit();
void MouseOn();
void MouseOff();
int Left();
int Right();
int MouseIn();
void cursor(int x,int y);
void MouseInit()
{
	reg.x.ax=0x00;
	int86(0x33,&i,&o);
}
void MouseOn()
{
	reg.x.ax=0x01;
	int86(0x33,&i,&o);
}
void MouseOff()
{
	reg.x.ax=0x02;
	int86(0x33,&i,&o);
}
int X()
{
	reg.x.ax=0x03;
	int86(0x33,&i,&o);
	return reg.x.cx;
}
int Y()
{
	reg.x.ax=0x03;
	int86(0x33,&i,&o);
	return reg.x.dx;
}
int Left()
{
	reg.x.ax=0x03;
	int86(0x33,&i,&o);
	return (reg.x.bx==1);
}
int Right()
{
	reg.x.ax=0x03;
	int86(0x33,&i,&o);
	return (reg.x.bx==2);
}
int etat(void)
{
	reg.x.ax=0x03;
	int86(0x33,&i,&o);
	return reg.x.bx;
}
int MouseIn(int x1,int x2,int y1,int y2)
{
	reg.x.ax=0x03;
	int86(0x33,&i,&o);
	reg.x.bx=2;
	return ((X()>=x1)&&(X()<=x2)&&(Y()<=y2)&&(Y()>=y1));
}
void cursor(int x,int y)
{
	while(!kbhit())
	{
		setcolor(0);
		outtextxy(x,y,"_");
		delay(150);
		setcolor(9);
		outtextxy(x,y,"__");
		delay(150);
	}
}
int main()
{
	int gd=DETECT,gm,maxx,maxy,button,x,y;
	initgraph(&gd,&gm,"C://TURBOC3//BGI");
	maxx=getmaxx();
	maxy=getmaxy();
	setbkcolor(8);
	setviewport(0,0,maxx,maxy,1);
	gotoxy(26,1);
	rectangle(10,10,200,465);
	setfillstyle(SOLID_FILL,YELLOW);
	floodfill(100,100,WHITE);
	getch();
	cleardevice();
	return 0;
}

  */
