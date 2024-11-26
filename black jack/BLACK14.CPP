#include<iostream.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
#include<process.h>
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<DOS.h>
#include<fstream.h>
#include<graphics.h>
class card
{
	public:
	char number;
	char sign;
	int value;
}c;
class player
{
	public:
	char name[50];
	int total;
	int check;
	int wincheck;
	int bustcheck;
	int amount;
	int bet;
	int broke;
	player()
	{
		total=0;
		check=0;
		wincheck=0;
		bustcheck=0;
		amount=1000;
		bet=0;
		broke=0;
	}
	void reset()
	{
		total=0;
		check=0;
		wincheck=0;
		bustcheck=0;
	}

}p[6];
class high
{
	int score;
	char n[50];
	public:
	high(player &p)
	{
		score=p.amount;
		strcpy(n,p.name);
	}
	high()
	{
		score=0;
	}
	void dis()
	{
		cout<<"Name: "<<n<<endl;
		cout<<"Score: "<<score<<endl;
	}
	int getscore()
	{
		return score;
	}
};
/*char* str(int x)
{
	char s[10];
	itoa(x,s,10);
	return s;
}*/
void titlescreen()
{
	clrscr();
	cleardevice();
	setbkcolor(0);
	setcolor(4);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 7);
	outtextxy(150,200,"BLACKJACK");
	/*outtextxy(230,260,"*");
	delay(1000);
	outtextxy(280,260,"*");
	delay(1000);
	outtextxy(330,260,"*");
	delay(1000);
	outtextxy(380,260,"*");
	delay(100);
	cleardevice();*/
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	outtextxy(230,300,"press any key to start");
	getch();
}
void naming(player p[],char n[])
{
	strcpy(p[0].name,n);
	strcpy(p[1].name,"Bot 1");
	strcpy(p[2].name,"Bot 2");
	strcpy(p[3].name,"Bot 3");
	strcpy(p[4].name,"Bot 4");
	strcpy(p[5].name,"Bot 5");
	strcpy(p[6].name,"Dealer");
}
void draw(card &c)
{
	c.value=1+rand()%(14-1);
	c.sign=random(4);
}
void display(int num, int sym)
{
	char ch;
	char number, symbol;
	cout<<"your card is\n";
	if(num>1 && num<=10)
	{	number='0';
	}
	else
	{	switch(num)
		{	case 1: number='A';
				break;
			case 11: number='J';
				break;
			case 12: number='Q';
				break;
			case 13: number='K';
		}
	}
	switch(sym)
	{	case 1: symbol=6;
			break;
		case 2: symbol=3;
			break;
		case 3: symbol=5;
			break;
		case 4: symbol=4;
	}
	ifstream x;
	x.open("comdeck.txt",ios::in);
	if(!x)
	{	cout<<"File error, check file location"<<endl;
		exit(0);
	}
	while(!x.eof())
	{	x.get(ch);
		if(ch=='N')
		{       if(number=='0')
			{	cout<<num;
			}
			else
			cout<<number;
		}
		else if(ch=='S')
		{	cout<<symbol;
		}
		else
		cout<<ch;
	}
	cout<<endl;
	x.close();
}
void hit(card &c,player &p)
{
	draw(c);
	display(c.value,c.sign);
	if(c.value!=1)
	{
		if(c.value==11 || c.value==12 || c.value==13)
		{
			p.total+=10;
		}
		else
		{
			p.total+=c.value;
		}
	}
	else
	{
		if(c.value+11>21)
		{
			p.total+=1;
		}
		else
		{
			p.total+=11;
			p.check=1;
		}
	}
}
void hit1(card &c,player &p)
{
	draw(c);
	if(c.value!=1)
	{
		if(c.value==11 || c.value==12 || c.value==13)
		{
			p.total+=10;
		}
		else
		{
			p.total+=c.value;
		}
	}
	else
	{
		if(c.value+11>21)
		{
			p.total+=1;
		}
		else
		{
			p.total+=11;
			p.check=1;
		}
	}
}
int bot_play(card &c,player &p,int bot_num)
{
	clrscr();
	cleardevice();
	cout<<"bot "<<bot_num<<"'s turn\n";
	getch();
	int choice;
	if(p.total<=12)
	{
		hit1(c,p);
		clrscr();
	}
	else if(p.total>13 && p.total<17)
	{
		if(p.check!=1)
		{
			int r=random(2);
			if(r==0)
			{
				hit1(c,p);
				clrscr();
			}
			else if(r==1)
			{
				cout<<"bot "<<bot_num<<" stays\n";
				getch();
				return 1;
			}
		}
		else
		{
			hit1(c,p);
			clrscr();
			if(p.total>21)
			{
				p.total-=10;
				p.check=0;
			}
		}
	}
	else if(p.total>=17 && p.total<21)
	{
		if(p.check!=1)
		{
			cout<<"bot "<<bot_num<<" stays\n";
			getch();
			return 1;
		}
		else
		{

			choice=random(2);
			if(choice==0)
			{
				p.check=0;
				p.total-=10;
				hit1(c,p);
				clrscr();
			}
			else
			{
				cout<<"bot "<<bot_num<<" stays\n";
				getch();
				return 1;
			}

		}
	}
	if(p.total==21)
	{
		cout<<"bot "<<bot_num<<"'s turn\n";
		cout<<"bot "<<bot_num<<" gets a blackjack!!!\n";
		getch();
		p.wincheck=1;
		return 1;
	}
	else if(p.total>21)
	{
		cout<<"bot "<<bot_num<<"'s turn\n";
		cout<<p.name<<" busted\n";
		p.bustcheck=1;
		getch();
	}
	return 0;
}
void dealer_play(card c,player &p,int max)
{
	clrscr();
	cleardevice();
	cout<<"Dealers turn\n";
	getch();
	p.total=0;
	for(int j=0;j<6;j++)
	{
		if(p.total<18)
		{
			hit1(c,p);
			clrscr();
			if(p.total>max && p.total<21)
			{
				cout<<"Dealers turn\n";
				cout<<"dealers total is now "<<p.total<<endl;
				cout<<"dealer wins\n";
				getch();
				return;
			}
			else if(p.total>21)
			{
				if(p.check==1)
				{
					p.total-=10;
					p.check=0;
				}
			}
		}
		else if(p.total==21)
		{
			cout<<"Dealers turn\n";
			cout<<"dealer gets a blackjack\n";
			p.wincheck=1;
			getch();
			return;
		}
		else if(p.total>21)
		{
			cout<<"Dealers turn\n";
			cout<<"Dealer busted\n";
			p.bustcheck=1;
			getch();
			return;
		}
	}
	cout<<"Dealers turn\n";
	cout<<"dealers total is "<<p.total;
	getch();
}
int user_play(card c,player &p)
{
	start:
	clrscr();
	cleardevice();
	int ch;
	cout<<"Players turn\n";
	cout<<"Your total is "<<p.total<<endl;
	cout<<"1.Hit\n2.Stay\n\n";
	cin>>ch;
	switch(ch)
	{
		case 1: hit(c,p);
			cout<<"Your total is now "<<p.total<<endl;
			if(p.total==21)
			{
				p.wincheck=1;
			}
			else if(p.total>21)
			{
				if(p.check!=1)
				{
					cout<<"busted\n";
					getch();
					p.bustcheck=1;
				}
				else
				{
					p.total-=10;
					p.check=0;
				}
			}
			getch();
			return 0;
		case 2: getch();
			return 1;
		default:cout<<"Invalid choice\n";
			getch();
			clrscr();
			goto start;
	}
}
void bets(player p[])
{
	start:
	randomize();
	clrscr();
	cleardevice();
	char ch[2];
	outtextxy(100,180,"current amounts are ");
	for(int j=0,k=200;j<6;j++,k+=20)
	{
		outtextxy(100,k,p[j].name);
		outtextxy(200,k,": ");
		char s[10];
		itoa(p[j].amount,s,10);
		outtextxy(210,k,s);
	}
	outtextxy(400,180,"Emter Your Bets");
	outtextxy(400,200,"1.10$");
	outtextxy(400,220,"2.20$");
	outtextxy(400,240,"3.50$");
	outtextxy(400,260,"4.100$");
	outtextxy(400,280,"5.250$");
	outtextxy(400,300,"6.500$");
	outtextxy(400,320,"Enter your choice");
	ch[0]=getch();
	ch[1]='\0';
	outtextxy(540,320,ch);
	getch();
	switch(ch[0])
	{
		case '1': p[0].bet=10;
			break;
		case '2': p[0].bet=20;
			break;
		case '3': p[0].bet=50;
			break;
		case '4': p[0].bet=100;
			break;
		case '5': p[0].bet=250;
			break;
		case '6': p[0].bet=500;
			break;
		default:cout<<"invalid choice\n";
			goto start;
	}
	clrscr();
	cleardevice();
	char s[3],st[100];
	itoa(p[0].bet,s,10);
	strcpy(st,p[0].name);
	strcat(st," bet ");
	strcat(st,s);
	strcat(st,"$");
	outtextxy(250,150,st);
	int temp;
	for(int i=1,m=170;i<=5;i++,m+=20)
	{
		if(p[i].broke!=1)
		{
			if(p[i].amount<100)
			{
				temp=random(2);
			}
			else if(p[i].amount>100 && p[i].amount<500)
			{
				temp=random(3);
			}
			else if(p[i].amount>=500 && p[i].amount<=1500)
			{
				temp=random(4)+1;
			}
			else
			{
				temp=random(3)+3;
			}
			switch(temp)
			{
				case 0:	p[i].bet=10;
					break;
				case 1: p[i].bet=20;
					break;
				case 2: p[i].bet=50;
					break;
				case 3: p[i].bet=100;
					break;
				case 4: p[i].bet=250;
					break;
				case 5: p[i].bet=500;
					break;
				default:p[i].bet=10;
			}
			itoa(p[i].bet,s,10);
			strcpy(st,p[i].name);
			strcat(st," bet ");
			strcat(st,s);
			strcat(st,"$");
			outtextxy(250,m,st);
		}
	}
	getch();
}

void scorecard(player p[])
{
	clrscr();
	cleardevice();
	outtextxy(280,150,"scorecard");
	for(int i=0,j=200;i<=6;i++,j+=20)
	{
		outtextxy(250,j,p[i].name);
		if(p[i].broke==1)
		{
			outtextxy(350,j,": broke");
		}
		else if(p[i].bustcheck!=1)
		{
			char s[50],t[10];
			itoa(p[i].total,t,10);
			strcpy(s,": ");
			strcat(s,t);
			outtextxy(350,j,s);
		}
		else
		{
			outtextxy(350,j,": busted");
		}
	}
	getch();
}

void compare(player p[])
{
	//clrscr();
	//cleardevice();
	int flag=0;
	scorecard(p);
	getch();
	clrscr();
	cleardevice();
	for(int i=0,j=200;i<6;i++,j+=20)
	{


		outtextxy(240,j,p[i].name);
		if(p[6].bustcheck!=1)
		{
			if(p[i].total>p[6].total && p[i].bustcheck!=1)
			{
				outtextxy(300,j," wins");
				flag=1;
				if(p[i].total==21)
				{
					p[i].amount+=(1.5*p[i].bet);
				}
				else
				{
					p[i].amount+=p[i].bet;
				}
			}
			else if(p[i].total==p[6].total)
			{
				flag=2;
				outtextxy(300,j," draw");
			}
			else
			{
				outtextxy(300,j," loses");
				p[i].amount-=p[i].bet;
			}
		}
		else
		{
			if(p[i].bustcheck!=1 && p[i].broke!=1)
			{
				outtextxy(300,j," wins");
				flag=1;
				if(p[i].total==21)
				{
					p[i].amount+=(1.5*p[i].bet);
				}
				else
				{
					p[i].amount+=p[i].bet;
				}
			}
			else
			{
				outtextxy(300,j," loses");
				p[i].amount-=p[i].bet;
			}

		}

	}
	if(flag==0)
	{
		outtextxy(240,320,"dealer wins");
	}
	else if(flag==2)
	{
		outtextxy(240,320,"dealer draws");
	}
	getch();
}

void disp(player p[])
{
	outtextxy(100,180,"current amounts are ");
	for(int j=0,i=200;j<6;j++,i+=20)
	{
		outtextxy(100,i,p[j].name);
		outtextxy(200,i,": ");
		char s[10];
		itoa(p[j].amount,s,10);
		outtextxy(210,i,s);
	}
	getch();
}
void check(player p[],int &plr,int b[])
{
	clrscr();
	if(p[0].amount<=0)
	{
		plr=1;
		cout<<"your balance is zero. cant continue playing\n";
		getch();
		exit(0);
	}

	for(int i=0;i<5;i++)
	{
		if(p[i+1].amount<=0)
		{
			p[i+1].broke=1;
			b[i]=1;
		}
	}
}
void highscore(player p)
{
	fstream file("highs.txt", ios::in | ios::out | ios::binary);
	ofstream fout("temp.txt", ios::out);
	high h(p);
	high s;
	int flag=0,f=0,c=0;
	while(file.read((char*)&s,sizeof(s)) && c<=5)
	{
		f=1;
		if(flag==0)
		{
			if(s.getscore()<h.getscore())
			{
				fout.write((char*)&h,sizeof(h));
				c++;
				flag=1;
			}
			fout.write((char*)&s,sizeof(s));
			c++;
		}
		else
		{
			fout.write((char*)&s,sizeof(s));
		}
	}
	if(f!=1)
	{
		fout.write((char*)&h,sizeof(h));
	}
	file.close();
	fout.close();
	remove("highs.txt");
	rename("temp.txt","highs.txt");
}
void display()
{
	clrscr();
	cleardevice();
	high h;
	ifstream fin("highs.txt", ios::in | ios::binary);
	if(!fin)
	{
		cout<<"error in opening the file\n";
		return;
	}
	cout<<"\t\tHIGH SCORES\n\n";
	while(fin.read((char*)&h,sizeof(h)))
	{
		h.dis();
		cout<<endl;
	}
	fin.close();
	getch();
}
void rules()
{
	clrscr();
	cleardevice();
	ifstream fin("bjrules.txt", ios::in);
	if(!fin)
	{
		cout<<"error in opening file\n";
		getch();
		return;
	}
	char str[50];
	while(!fin.eof())
	{
		fin>>str;
		cout<<str<<' ';
	}
	getch();
}

void main()
{
	clrscr();
	char n[50];
	char ch[2];
	randomize();
	srand(time(NULL));
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "C:\\TC\\BGI");
	errorcode = graphresult();
	if (errorcode != grOk)
	{
		cout<<"error in graphics\n";
		exit(0);
	}
	cleardevice();
	titlescreen();
	cleardevice();
	outtextxy(200,200,"Welcome to Blackjack Program");
	outtextxy(200,220,"Enter your name:");
	char s[2];
	int x,y;
	for(int i=330,f=0,j=0;f!=1;i+=10,j++)
	{
		s[0]=getch();
		s[1]='\0';
		if(s[0]==13)
		{
			break;
		}
		outtextxy(i,220,s);
		n[j]=s[0];
	}
	getch();
	cleardevice();
	outtextxy(200,200,"Welcome ");
	outtextxy(270,200,n);
	naming(p,n);
	getch();
	do
	{

		clrscr();
		cleardevice();
		disp(p);
		outtextxy(400,200,"1.Play");
		outtextxy(400,220,"2.High Scores");
		outtextxy(400,240,"3.How to Play");
		outtextxy(400,260,"4.Exit");
		outtextxy(400,280,"Enter your choice ");
		ch[0]=getch();
		ch[1]='\0';
		outtextxy(540,280,ch);
		getch();
		clrscr();
		cleardevice();
		clrscr();
		switch(ch[0])
		{
			case '1':cleardevice();
				clrscr();
				for(int t=0;t<=6;t++)
				{
					p[t].reset();
				}
				int plr=0,b[5]={0,0,0,0,0},max=0;
				check(p,plr,b);
				bets(p);
				for(int i=0;i<6;i++)
				{
					if(plr==0 && p[0].bustcheck==0)
					{
						plr=user_play(c,p[0]);
						if(p[0].total>max && p[0].bustcheck==0)
						{
							max=p[0].total;
						}
						if(p[0].wincheck==1)
						{
							cout<<p[0].name<<" gets a blackjack\n";
							plr=1;
							getch();
						}
					}
					for(int j=0;j<5;j++)
					{
						if(b[j]!=1 && p[j+1].bustcheck==0)
						{
							b[j]=bot_play(c,p[j+1],j+1);
							if(p[j+1].total>max && p[j+1].bustcheck==0)
							{
								max=p[j+1].total;
							}
						}
					}
				}
				getch();
				dealer_play(c,p[6],max);
				compare(p);
				break;
			case '2': display();
				break;
			case '3': rules();
				break;
			case '4': highscore(p[0]);
				closegraph();
				exit(0);
				break;
			default:cout<<"invalid choice\n";
		}
	}while(1);
}