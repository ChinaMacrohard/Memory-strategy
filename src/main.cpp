#include <bits/stdc++.h>
#include <windows.h>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
#define CLS color(7),system("cls")
using namespace std;
struct Button
{
	int x,y,color;
	string name;
	int len;
};
void GetPos(POINT &pt)
{
	HWND hwnd=GetForegroundWindow();
	GetCursorPos(&pt);
	ScreenToClient(hwnd,&pt);
	pt.y=pt.y/16;
	pt.x=pt.x/16;
}
void color(int a)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
}

void gto(int x,int y)
{
	COORD pos;
	pos.X=y*2;
	pos.Y=x;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

Button NewButton(int x,int y,int color,string name)
{
	Button t;
	t.x=x;
	t.y=y;
	t.name=name;
	t.color=color;
	t.len=name.length();
	return t;
}

bool Preserve(Button A)
{
	gto(A.x,A.y),color(A.color),printf("%s",(A.name).c_str());
	POINT pt;
	GetPos(pt);
	if(pt.y==A.x&&(pt.x>=A.y&&pt.x<=A.y+A.len/4)) {
		color(A.color+16),gto(A.x,A.y),printf("%s",(A.name).c_str());
		if(KEY_DOWN(MOUSE_MOVED)) return 1;
	}
	return 0;
}

void hind_cursor()
{
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);
	CursorInfo.bVisible=false;
	SetConsoleCursorInfo(handle, &CursorInfo);
}

int rc()
{
    int cl=rand()%15+1;
    return cl;
}

int len,speed,cnt=1,now=0,nx,ny;
Button px[100][100];
bool fp[100][100]= {false};
short flag=2;

int main()
{
	system("title ¼ÇÒä¹¥ÂÔ github:ChinaMacrohard");
	srand((unsigned)time(NULL));
	hind_cursor();
	cout<<"Speed(seconds):";
	cin>>speed;
	speed*=500;
	cout<<"Length:";
	cin>>len;
	CLS;
	for(int i=1; i<=len; i++)
		for(int j=1; j<=len; j++)
			px[i][j]=NewButton(i+1,j+1,17,"  ");
	do {
		now=0;
		flag=2;
		nx=rand()%len+1;
		ny=rand()%len+1;
		while(fp[nx][ny])
		{
			nx=rand()%len+1;
			ny=rand()%len+1;
		}
		px[nx][ny].color=(rc())*17;
		while(px[nx][ny].color==17)
			px[nx][ny].color=(rc())*17;
		CLS;
		cout<<"Round: "<<cnt;
		_sleep(1500);
		CLS;
		while(now<=speed)
		{
			for(int i=1; i<=len; i++)
			{
				for(int j=1; j<=len; j++)
				{
					if(Preserve(px[i][j]))
					{
						if(i==nx && j==ny)
						{
							cnt++;
							flag=1;
						}
						else
							flag=0;
					}
				}
			}
			if(flag==1 || flag==0)
				break;
			now+=20;
			_sleep(20);
		}
		if(now>=speed)break;
	}
	while(flag!=0);
	CLS;
	cout<<"You lost!"<<endl<<"You have played "<<cnt-1<<" turns."<<endl;
	return 0;
}
