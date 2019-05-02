#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
using namespace std;

namespace YCZL_Code{
	const int CODE_SIZE=300005;
	const int P=998244353;
	const int g=3;
	long long Pow(long long a,long long p){
		static long long ret;
		for(ret=1;p;p>>=1,a=a*a%P)if(p&1)ret=ret*a%P;
		return ret;
	}

	namespace Poly{
		int Rev[CODE_SIZE];void Init_Rev(int l){for(int i=1;i<l;i++)Rev[i]=Rev[i>>1]>>1|(i&1?l>>1:0);}
		int DFT(long long *Arr,int n,int ty){
			static int l;l=1;while(l<=n)l<<=1;
			Init_Rev(l);
			for(int i=1;i<l;i++)if(i<Rev[i])swap(Arr[i],Arr[Rev[i]]);
			for(int len=2,k=1;len<=l;len<<=1,k<<=1){
				long long unit=Pow(Pow(g,(P-1)/len),ty);
				for(int i=0;i<l;i+=len){
					long long omega=1;
					for(int j=i;j<i+k;j++){
						long long tmp=omega*Arr[j+k]%P;
						Arr[j+k]=Arr[j]-tmp;if(Arr[j+k]<0)Arr[j+k]+=P;
						Arr[j]+=tmp;if(Arr[j]>=P)Arr[j]-=P;
						omega=omega*unit%P;
					}
				}
			}
			if(ty==P-2){
				long long Pw=Pow(l,P-2);
				for(int i=0;i<l;i++)Arr[i]=Arr[i]*Pw%P;
			}
			return l;
		}
	};

	template<class T>void YCZL_Rd(T &r){
		static char c;r=0;
		for(int i=1;i<=8;i++){
			c=getchar();
			r<<=4;
			if(c=='4')r+=10;
			else if(c=='A')r+=4;
			else if(c>='B' and c<='F')r+=c-'A'+10;
			else r+=c-'0';
		}
	}
	template<class T>void YCZL_Wt(T r){
		static int O[15];
		for(int i=1;i<=8;i++)O[i]=r&15,r>>=4;
		for(int i=8;i>=1;i--){
			if(O[i]==4)putchar('A');
			else if(O[i]==10)putchar('4');
			else if(O[i]<10)putchar(O[i]+'0');
			else putchar(O[i]-10+'A');
		}
	}
	long long CODE[CODE_SIZE];
	char STR[CODE_SIZE];
	int Wtime[CODE_SIZE];
	void Rd_code(){
		freopen("replay.gm2","r",stdin);
		int n;YCZL_Rd(n);n=Pow(n,P-2);
		int l=1;while(l<=n)l<<=1;
		for(int i=0;i<l;i++)YCZL_Rd(CODE[i]);
		for(int i=1;i<=n;i++)YCZL_Rd(Wtime[i]);
		Poly::DFT(CODE,n,P-2);
		for(int i=0;i<=n;i++)STR[i]=CODE[i];
	}
	void Wt_code(){
		freopen("replay.gm2","w",stdout);
		int n=strlen(STR);YCZL_Wt(Pow(n,P-2));
		for(int i=0;i<=n;i++)CODE[i]=STR[i];
		int l=Poly::DFT(CODE,n,1);
		for(int i=0;i<l;i++)YCZL_Wt(CODE[i]);
		for(int i=1;i<=n;i++)YCZL_Wt(Wtime[i]);
		int dy=rand()%100;
		for(int i=1;i<=dy;i++)YCZL_Wt((unsigned)rand()*rand()*rand()*rand()*rand()%P);
	}
};

namespace _BASIC_ART_{

#define RED 12
#define BLUE 11
#define YELLOW 14
#define GREEN 10
#define PINK 13

#define DRED 4
#define DBLUE 9
#define DYELLOW 6
#define DGREEN 2
#define DPINK 5

#define WHITE 15
#define BLACK 0
#define GREY 7
#define DGREY 8

	void color(int a) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
	}
	void color(int x,int y){
		color((x<<4)+y);
	}
	void c7(){
		color(GREY);
	}
	void gotoxy(int x,int y) {
		COORD pos;
		pos.X=2*(y-1);
		pos.Y=x-1;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
	}
	const int COL[]={BLACK,RED,BLUE,YELLOW,GREEN,PINK,DBLUE,DGREY,DYELLOW};

	char trc(char c){
		if(c>='A' and c<='Z')return c-'A';
		if(c==-32){
			c=getche();
			if(c==72)return 'w';
			else if(c==75)return 'a';
			else if(c==80)return 's';
			else if(c==77)return 'd';
			else if(c==83)return 'k';
		}
		else if(c=='#')return 'h';
		else if(c=='\n' or c=='\r')return 'z';
		else if(c==8)return 'k';
		return c;
	}
	int Cho(int cnt,int fir=1){
		int pos=fir;
		c7();gotoxy(4+fir,1);printf("-->");
		char c;
		do{
			gotoxy(5,1);color(BLACK);c=trc(getche());
			c7();
			gotoxy(4+pos,1);printf("   ");
			if(c=='w')pos=pos==1?cnt:pos-1;
			if(c=='s')pos=pos==cnt?1:pos+1;
			gotoxy(4+pos,1);printf("-->");
		}while(c!='z' and c!='k');
		system("cls");
		return c=='k'?-1:pos;
	}
};using namespace _BASIC_ART_;

const int H=60,W=60;
const int PM			=10;
const int FOCUS			=10;
const int CHOC			=20;
const int SIGHT			=5;
const int CITY_PERCENT	=15;
const int REP_SIZE		=100005;
const int SK_CNT		=8;
const double BOOM_RANGE	=7.05;
const double BOOM_B		=3.0;
const double BOOM_K		=0.005;
const char VERSION[]="0.10.5";
const int HOME_DIST[SK_CNT+1]={0,90,70,60,50,40,35,30,25};
const int Skpro[SK_CNT+1]={0,50,40,35,30,20,55,30,35};
const int dx[]={1,0,-1,0},dy[]={0,1,0,-1};

inline bool Unfish(int x,int y){return x>=1 and x<=H and y>=1 and y<=W;}
inline bool Fish(int x,int y){return x<1 or x>H or y<1 or y>W;}
inline int Dis(int x,int y,int xx,int yy){return abs(x-xx)+abs(y-yy);}

int n,diffi;
int totc,rnd;
int plid;
int seed;
int mode;
bool Replay,god;
int sighter;

int ty[H+5][W+5];
int lv[H+5][W+5];
int die[PM];
int Plr[PM];
int sk[PM];
bool Spell[SK_CNT+5];
int ar6;bool hv6[H+5][W+5];
int saved;
bool boom[H+5][W+5];

struct Country{
	int c;
	int hx,hy;
	int square,army,city;
	int Seen[H+5][W+5];
	void getseen(int x,int y){
		for(int i=-SIGHT;i<=SIGHT;i++)
			for(int j=-SIGHT;j<=SIGHT;j++)
				if(Unfish(x+i,y+j) and Dis(i,j,0,0)<=SIGHT)
					Seen[x+i][y+j]++;
	}
	void loseseen(int x,int y){
		for(int i=-SIGHT;i<=SIGHT;i++)
			for(int j=-SIGHT;j<=SIGHT;j++)
				if(Unfish(x+i,y+j) and Dis(i,j,0,0)<=SIGHT and lv[x+i][y+j]!=2)
					Seen[x+i][y+j]--;
	}
	int Imp[H+5][W+5],ifree;
	void chos(int &x,int &y,int &xx,int &yy){
		int d=0;
		bool f=false;
		do{
			x=rand()%H+1,y=rand()%W+1,d=rand()&3;
			xx=x+dx[d],yy=y+dy[d];
			if(Fish(xx,yy))f=false;
			else if(ty[x][y]!=c)f=false;
			else if(ty[x][y]==ty[xx][yy])f=false;
			else f=true;
		}while(!f);
	}
	vector<int>Ix,Iy;
	void Init(){
		Ix.clear(),Iy.clear();
		for(int i=1;i<=H;i++)
			for(int j=1;j<=W;j++)
				if(Imp[i][j])
					for(int q=1;q<=Imp[i][j];q++)
						Ix.push_back(i),Iy.push_back(j);
	}
	int dH(int x,int y,int p){return Dis(x,y,Ix[p],Iy[p]);}
	void Choose(int &x,int &y,int &xx,int &yy){
		int d=2e9;
		int tt=rand()%FOCUS<ifree;
		if(tt){
			for(int i=1;i<=CHOC;i++){
				int x0,y0,xx0,yy0;
				chos(x0,y0,xx0,yy0);
				int d0=ty[xx0][yy0]!=0;
				if(d0<d)d=d0,x=x0,y=y0,xx=xx0,yy=yy0;
			}
		}else{
			int k=rand()%Ix.size();
			for(int i=1;i<=CHOC;i++){
				int x0,y0,xx0,yy0;
				chos(x0,y0,xx0,yy0);
				int d0=dH(xx0,yy0,k);
				if(d0<d)d=d0,x=x0,y=y0,xx=xx0,yy=yy0;
			}
		}
	}
}C[PM];

struct AI{
	int id;
#define chx C[id].hx
#define chy C[id].hy
#define ct C[id]
	bool Danger(){
		for(int i=1;i<=H;i++)
			for(int j=1;j<=W;j++)
				if(ty[i][j] and ty[i][j]!=id){
					int c=ty[i][j],d=Dis(i,j,chx,chy);
					if(C[c].army>=1.5*ct.army){
						if(d<=12)return true;
					}else if(C[c].army>=1.0*ct.army){
						if(d<=9)return true;
					}else if(C[c].army>=0.3*ct.army){
						if(d<=7)return true;
					}else{
						if(d<=3)return true;
					}
				}
		return false;
	}
	bool Seec(int c){
		for(int i=1;i<=H;i++)
			for(int j=1;j<=W;j++)
				if(ct.Seen[i][j] and ty[i][j]==c)
					return true;
		return false;
	}

	int Enemy(){
		int c=-1;
		double w=2e9;
		static int Order[PM];
		for(int i=1;i<=n;i++)Order[i]=i;
		random_shuffle(Order+1,Order+n+1);
		for(int i=1;i<=n;i++){
			int x=Order[i];
			if(die[x])continue;
			if(x==id)continue;
			if(!Seec(x))continue;
			double dw=C[x].army;
			if(ct.Seen[C[x].hx][C[x].hy])dw/=1.5;
			if(mode!=3){
				if(sk[x]==6)dw*=1.5;
				if(sk[x]==1 and Spell[1])dw*=2;
				if(sk[x]==2 and Spell[2])dw*=1.5;
				if(sk[x]==7)dw*=0.9;
			}
			if(dw<w)c=x,w=dw;
		}
		return c;
	}

	bool Line(int x,int y,int c){
		if(ty[x][y]==id)return false;
		int xx=chx,yy=chy;
		for(int i=1;i<=H;i++)
			for(int j=1;j<=W;j++)
				if(ty[i][j]==id and Dis(i,j,x,y)<Dis(xx,yy,x,y))
					xx=i,yy=j;
		if(x==xx){
			if(y>yy){for(int i=1;i<=yy;i++)if(ty[x][i]==c)return true;}
			else {for(int i=yy;i<=n;i++)if(ty[x][i]==c)return true;}
			return false;
		}
		double k=1.0*(yy-y)/(xx-x);
		for(int i=min(x,xx);i<=max(x,xx);i++){
			double y0=y+k*(i-x);
			int yc=y0,yf=yc+1;
			if(Unfish(i,yc) and ct.Seen[i][yc] and ty[i][yc]==c)return true;
			if(Unfish(i,yf) and ct.Seen[i][yf] and ty[i][yf]==c)return true;
		}
		return false;
	}

	void Getatkp(int c,int &x,int &y){
		if(ct.Seen[C[c].hx][C[c].hy]){x=C[c].hx;y=C[c].hy;return;}
		int cnt=0;
		do x=rand()%H+1,y=rand()%W+1,cnt++;while(cnt<=2000 and !Line(x,y,c));
		if(cnt>=2000)x=chx,y=chy;
	}

	void chokd(int &x,int &y){
		int cnt=0;
		do x=rand()%H+1,y=rand()%W+1,cnt++;while(cnt<=20000 and (ct.Seen[x][y] or Dis(x,y,chx,chy)<10));
		if(cnt>=20000)x=chx,y=chy;
	}

	void X(int x,int y){
		ct.Imp[chx][chy]+=3;ct.Imp[x][y]+=FOCUS-3;ct.ifree=0;
	}
	void Xhome(int c){X(C[c].hx,C[c].hy);}

	void Out(){
		int x=H,y=W;
		if(ct.square<=200)Xhome(id);
		else if(mode!=3 and sk[id]==3)chokd(x,y),X(x,y);
		else ct.ifree=FOCUS;
	}

	void Choose(){
		memset(ct.Imp,0,sizeof(ct.Imp));
		bool dan=Danger();
		if(dan)Xhome(id);
		else{
			int c=Enemy();
			if(c==-1 or C[c].city>ct.city*1.2)Out();
			else{
				int x=1,y=1;
				Getatkp(c,x,y);
				X(x,y);
			}
		}
		ct.Init();
	}
}ai[PM];

void Make_Capital(){
	bool ck;
	do{
		static int Rnd[PM],tot;
		tot=0;for(int i=1;i<=n;i++)if(!die[i])Rnd[++tot]=i;
		random_shuffle(Rnd+1,Rnd+tot+1);
		for(int i=1;i<=tot;i++)C[Rnd[i]].hx=rand()%H+1,C[Rnd[i]].hy=rand()%W+1;
		ck=true;int lim=HOME_DIST[totc];
		for(int i=1;i<=tot and ck;i++)
			for(int j=1;j<i and ck;j++)
				if(Dis(C[Rnd[i]].hx,C[Rnd[i]].hy,C[Rnd[j]].hx,C[Rnd[j]].hy)<=lim)
					ck=false;
	}while(!ck);
	for(int i=1;i<=totc;i++){
		ty[C[i].hx][C[i].hy]=i;
		lv[C[i].hx][C[i].hy]=2;
	}
}
bool Mksk[SK_CNT+5];
void Make_Map(){
	Mksk[sk[plid]]=true;
	for(int i=1;i<=totc;i++){
		if(i==plid)continue;
		do sk[i]=rand()%SK_CNT+1;
		while(Mksk[sk[i]]);
		Mksk[sk[i]]=true;
	}
	for(int i=totc+1;i<=n;i++)die[i]=true;
	Make_Capital();
	for(int i=1;i<=n;i++){
		if(die[i])continue;
		C[i].city=C[i].square=1;
		C[i].c=i;
		C[i].getseen(C[i].hx,C[i].hy);
		C[i].Imp[C[i].hx][C[i].hy]=FOCUS;
		C[i].Init();
		ai[i].id=i;
	}
	for(int i=1;i<=H;i++)
		for(int j=1;j<=W;j++)
			if(lv[i][j]==0 and rand()%100<CITY_PERCENT)
				lv[i][j]=1;
}

void Print(int x,int y,bool tt=false){
	gotoxy(x,y);
	if(C[sighter].Seen[x][y] or god){
		int c=ty[x][y];
		color(COL[sk[c]]);
		if(C[c].hx==x and C[c].hy==y)putchar((boom[x][y]?'a':'A')+sk[c]-1);
		else if(lv[x][y] and boom[x][y])putchar(sk[ty[x][y]]==7?'_':'.');
		else putchar(".$#  *"[lv[x][y]]);
	}else color(DGREY,0),printf(" ");
	if(C[sighter].Imp[x][y] or tt){
		color(tt?WHITE:GREY,BLACK);
		printf("%c","0123456789X"[C[sighter].Imp[x][y]]);
	}else if(C[sighter].Seen[x][y] or god)color(BLACK,0),printf(" ");
	else color(DGREY,0),printf(" ");
}
void Princ(int c,bool tt=true){
	gotoxy(c+1,W+3);
	color(tt?COL[sk[c]]:BLACK);
	printf("%c : %5d / %7d / %5d",sk[c]+'A'-1,C[c].square,C[c].army,C[c].city);
	if(mode!=3 and sk[c]==6)printf(" / %d ",saved);
	c7();
}

char rep[REP_SIZE];int top;

int plidsk;
void Read_Rep(){
	YCZL_Code::Rd_code();
	sscanf(YCZL_Code::STR,"%d%d%d%d%s",&seed,&mode,&totc,&plidsk,rep+1);diffi=totc;
}
void Write_Rep(){
	sprintf(YCZL_Code::STR,"%d %d %d %d\n%s\n",seed,mode,diffi,sk[plid],rep+1);
	YCZL_Code::Wt_code();
}

void End(){
	freopen("con","r",stdin);
	for(int i=1;i<=H;i++)for(int j=1;j<=W;j++)C[sighter].Seen[i][j]=1,C[sighter].Imp[i][j]=0,Print(i,j);
	gotoxy(H+2,1);c7();
	system("pause");
	system("cls");
	if(Replay)return;
	c7();gotoxy(1,1);printf("要保存回放到replay.gm2吗(将会覆盖原文件)？");
	gotoxy(5,1);printf("\t是");
	gotoxy(6,1);printf("\t否");
	if(Cho(2,2)==1)Write_Rep();
}

int seentmp[H+5][W+5];
void Turn(int x,int y,int c){
	if(!god){
		for(int i=-SIGHT;i<=SIGHT;i++)
			for(int j=-SIGHT;j<=SIGHT;j++)
				if(Unfish(x+i,y+j) and Dis(i,j,0,0)<=SIGHT)
					seentmp[x+i][y+j]=C[sighter].Seen[x+i][y+j]?ty[x+i][y+j]:-1;
	}
	int o=ty[x][y];
	if(boom[x][y] and lv[x][y]){
		if(sk[c]==7)C[c].city++;
		if(sk[o]==7)C[o].city--;
	}
	else if(sk[o]==5 and lv[x][y]==5){
		lv[x][y]=0;
		C[o].city--;
	}
	else {if(lv[x][y])C[o].city--,C[c].city++;}
	ty[x][y]=c;
	C[o].square--,C[c].square++;
	if(o)C[o].loseseen(x,y);if(c)C[c].getseen(x,y);
	if(god){Print(x,y);return;}
	for(int i=-SIGHT;i<=SIGHT;i++)
		for(int j=-SIGHT;j<=SIGHT;j++)
			if(Unfish(x+i,y+j) and Dis(i,j,0,0)<=SIGHT){
				int sn=C[sighter].Seen[x+i][y+j]?ty[x+i][y+j]:-1;
				if(sn!=seentmp[x+i][y+j])Print(x+i,y+j);
			}
}

struct dno{
	int x,y;
	bool operator <(const dno &b)const{
		return Dis(C[ty[x][y]].hx,C[ty[x][y]].hy,x,y)<Dis(C[ty[b.x][b.y]].hx,C[ty[b.x][b.y]].hy,b.x,b.y);
	}
}Dd[H*W+5];
int dtop;
void Die(int o,int p){
	die[o]=true;
	dtop=0;
	for(int i=1;i<=H;i++)for(int j=1;j<=W;j++)if(ty[i][j]==o)Dd[++dtop]=(dno){i,j};
	sort(Dd+1,Dd+dtop+1);
	for(int i=1;i<=dtop;i++)Turn(Dd[i].x,Dd[i].y,p);
	gotoxy(n-totc+12,W+3);
	color(COL[sk[o]]);printf("%c",sk[o]+'A'-1);
	c7();printf(" is beaten by ");
	color(COL[sk[p]]);printf("%c",sk[p]+'A'-1);
	c7();printf(" in round %5d !",rnd);
	C[p].army+=C[o].army>>1;
	totc--;
	if(o==plid or o==sighter)End(),exit(0);
	Princ(o,false);
	Princ(p);
}

bool Win(int u,int v,bool amr){
	if(v==0)return true;
	bool ret=rand()*rand()%(C[u].army+C[v].army+1)<C[u].army;
	if(Spell[1]){
		if(sk[u]==1 and rand()%100<40)ret=true;
		if(sk[v]==1 and rand()%100<40)ret=false;
	}
	int cnt=min(C[u].army,C[v].army)*2/C[v].square;
	if(amr){
		C[u].army-=(int)(cnt*(sk[u]==2 and Spell[2]?0.25:1));
		C[v].army-=(int)(cnt*(sk[v]==2 and Spell[2]?0.25:1));
		if(C[u].army<0)C[u].army=0;
		if(C[v].army<0)C[v].army=0;
	}
	Princ(v);
	return ret;
}

void Attack(int xx,int yy,int c,bool amr=true){
	int cc=ty[xx][yy];
	if(Win(c,cc,amr)){
		if(C[cc].hx==xx and C[cc].hy==yy)Die(cc,c);
		else Turn(xx,yy,c);
	}
}
void Boom(int x,int y){
	boom[x][y]=true;
	if(ty[x][y] and sk[ty[x][y]]!=7 and lv[x][y])C[ty[x][y]].city--;
	if(lv[x][y]==5)lv[x][y]=0;
	Print(x,y);if(ty[x][y])Princ(ty[x][y]);
}

void Go(int c){
	int x,y,xx,yy;C[c].Choose(x,y,xx,yy);
	Attack(xx,yy,c);
	Princ(c);
}

void Round(){
	rnd++;gotoxy(1,W+2);c7();printf("round %d",rnd);
	for(int i=1;i<=n;i++)if(!die[i] and (sk[i]==4 or die[4] or !Spell[4] or rand()%100<40))Go(i);
	for(int i=1;i<=n;i++)if(!die[i] and (sk[i]==4 or die[4] or !Spell[4] or rand()%100<40))C[i].army+=C[i].city;
}

#define cip C[plid].Imp
#define ifr C[plid].ifree
int cgx,cgy;int citm;
void Change_Imp(){
	cgx=C[plid].hx,cgy=C[plid].hy;
	if(sighter==plid)Print(cgx,cgy,true);
	while(true){
		char c;
		if(Replay){
			c=rep[++top];
			if(c!='z')Sleep(YCZL_Code::Wtime[top]);
		}
		else{
			gotoxy(H+1,W+2);color(BLACK);
			c=trc(getche());c7();
			rep[++top]=c;
			YCZL_Code::Wtime[top]=clock()-citm;citm=clock();
		}
		if(c=='w'){
			if(Fish(cgx-1,cgy))continue;
			Print(cgx,cgy);
			cgx--;
			if(sighter==plid)Print(cgx,cgy,true);
		}else if(c=='a'){
			if(Fish(cgx,cgy-1))continue;
			Print(cgx,cgy);
			cgy--;
			if(sighter==plid)Print(cgx,cgy,true);
		}else if(c=='s'){
			if(Fish(cgx+1,cgy))continue;
			Print(cgx,cgy);
			cgx++;
			if(sighter==plid)Print(cgx,cgy,true);
		}else if(c=='d'){
			if(Fish(cgx,cgy+1))continue;
			Print(cgx,cgy);
			cgy++;
			if(sighter==plid)Print(cgx,cgy,true);
		}else if(c=='+'){
			if(ifr<=0)continue;
			ifr--;
			cip[cgx][cgy]++;
			if(sighter==plid)Print(cgx,cgy,true);
		}else if(c=='-'){
			if(cip[cgx][cgy]<=0)continue;
			ifr++;
			cip[cgx][cgy]--;
			if(sighter==plid)Print(cgx,cgy,true);
		}else if(isdigit(c) or c=='o'){
			if(isdigit(c))c^=48;
			else c=10;
			int ifrw=ifr+cip[cgx][cgy]-c;
			if(ifrw<0 or ifrw>FOCUS)continue;
			ifr=ifrw;cip[cgx][cgy]=c;
			if(sighter==plid)Print(cgx,cgy,true);
		}else if(c=='k'){
			for(int i=1;i<=H;i++)
				for(int j=1;j<=W;j++)
					if(cip[i][j]){
						cip[i][j]=0;
						if(sighter==plid)Print(i,j);
					}
			ifr=FOCUS;
			if(sighter==plid)Print(cgx,cgy,true);
		}else if(c=='j'){
			if(ifr==FOCUS)continue;
			int xx,yy,dd=2e9;
			for(int i=1;i<=H;i++)
				for(int j=1;j<=W;j++)
					if(cip[i][j] and Dis(i,j,cgx,cgy)<dd)
						xx=i,yy=j,dd=Dis(i,j,cgx,cgy);
			if(sighter==plid)Print(cgx,cgy);
			cgx=xx,cgy=yy;
			if(sighter==plid)Print(cgx,cgy,true);
		}else if(c=='h'){
			int tmpx=cgx,tmpy=cgy;
			cgx=C[plid].hx,cgy=C[plid].hy;
			if(sighter==plid)Print(tmpx,tmpy);
			if(sighter==plid)Print(cgx,cgy,true);
		}
		else if(c=='z')break;
	}
	if(sighter==plid)Print(cgx,cgy);
	C[plid].Init();
};

struct cnode{int xx,yy;}Cnode[4*H*W+5];int ctop;
int Findid(int s){
	int id=0;for(int i=1;i<=n;i++)if(sk[i]==s)id=i;
	return id;
}
void Spell3(){
	int id=Findid(3);
	ctop=0;
	for(int i=1;i<=H;i++)
		for(int j=1;j<=W;j++){
			if(ty[i][j]!=id)continue;
			for(int d=0;d<4;d++){
				int xx=i+dx[d],yy=j+dy[d];
				if(Unfish(xx,yy) and ty[xx][yy]!=id)Cnode[++ctop]=(cnode){xx,yy};
			}
		}
	for(int i=1;i<=ctop;i++)Attack(Cnode[i].xx,Cnode[i].yy,id,false);
}
void Spell4(){
	int id=Findid(4);
	C[id].army*=1.05;
}
void Spell5(){
	int id=Findid(5);
	for(int i=1;i<=H;i++)
		for(int j=1;j<=W;j++){
			if(ty[i][j]!=id)continue;
			if(rand()%20==0 and lv[i][j]==0 and !boom[i][j]){
				lv[i][j]=5;
				C[id].city++;
				Print(i,j);
			}
		}
	Princ(id);
}
void Spell6(){
	int id=Findid(6);
	if(saved==-1){
		ar6=C[id].army;
		for(int i=1;i<=H;i++)
			for(int j=1;j<=W;j++)
				hv6[i][j]=ty[i][j]==id;
	}else{
		C[id].army=max(C[id].army,ar6);
		for(int i=1;i<=H;i++)
			for(int j=1;j<=W;j++)
				if(hv6[i][j] and ty[i][j]!=id)
					Turn(i,j,id);
		ar6=max(ar6,C[id].army);
		for(int i=1;i<=H;i++)
			for(int j=1;j<=W;j++)
				hv6[i][j]|=ty[i][j]==id;
	}
	saved=3;
	Princ(id);
}
int Calc_city(int x,int y,int rg){
	int c=0;
	for(int i=x-rg;i<=x+rg;i++)
		for(int j=y-rg;j<=y+rg;j++)
			if(Unfish(i,j) and !boom[i][j] and lv[i][j] and sk[ty[i][j]]!=7 and ty[i][j])
				c++;
	return c;
}
void Spell7(){
	int x,y,cn=2,mx=-1;
	int range=min(BOOM_RANGE,BOOM_B+BOOM_K*C[Findid(7)].square);
	for(int i=1;i<=H;i++)
		for(int j=1;j<=W;j++){
			int c=Calc_city(i,j,range);
			if(c>mx)mx=c,x=i,y=j,cn=2;
			else if(c==mx){
				if(rand()%cn==0)x=i,y=j;
				cn++;
			}
		}
	for(int i=x-range;i<=x+range;i++)
		for(int j=y-range;j<=y+range;j++)
			if(Unfish(i,j) and !boom[i][j] and lv[i][j])
				Boom(i,j);
}
void Get_8pos(int &x,int &y){
	int id=Findid(8);
	int cnt=0;
	do{
		x=rand()%H+1,y=rand()%W+1;
		if(ty[x][y]==0 and Dis(x,y,C[id].hx,C[id].hy)<=sqrt(C[id].square)*3)return;
		cnt++;
	}while(cnt<=20000);
	cnt=0;
	while(true){
		x=rand()%H+1,y=rand()%W+1;
		if(sk[ty[x][y]]==8)continue;
		for(int d=0;d<4;d++){
			int xx=x+dx[d],yy=y+dy[d];
			if(Unfish(xx,yy) and sk[ty[xx][yy]]==8)return;
		}
	}
}
void Find_8near(int cx,int cy,int &x,int &y){
	int cn=2,mn=1e9;
	for(int i=1;i<=H;i++)
		for(int j=1;j<=W;j++){
			if(sk[ty[i][j]]==8)continue;
			int c=Dis(i,j,cx,cy);
			if(c<mn)mn=c,x=i,y=j,cn=2;
			else if(c==mn){
				if(rand()%cn==0)x=i,y=j;
				cn++;
			}
		}
}
void Spell8(){
	int id=Findid(8);
	int x,y;Get_8pos(x,y);
	int umbc=min(120.5,max(60.5,C[id].square*0.20));
	for(int i=1;i<=umbc;i++){
		int xx,yy;Find_8near(x,y,xx,yy);
		Attack(xx,yy,id,false);
	}
}

void Printsc(int c){
	gotoxy(c+22,W+3);
	if(Spell[sk[c]] and !die[c])color(COL[sk[c]]);
	else color(BLACK);
	printf("%c 触发了特技!",sk[c]+'A'-1);
	if(sk[c]==3 and !die[c] and Spell[3])Spell3();
	if(sk[c]==4 and !die[c] and Spell[4])Spell4();
	if(sk[c]==5 and !die[c] and Spell[5])Spell5();
	if(sk[c]==6 and !die[c] and Spell[6])Spell6();
	if(sk[c]==7 and !die[c] and Spell[7])Spell7();
	if(sk[c]==8 and !die[c] and Spell[8])Spell8();
}

void R100(){
	for(int i=1;i<=n;i++)if(!die[i])C[i].army+=15*C[i].square,Princ(i);
	if(mode==3)for(int i=1;i<=n;i++)Spell[sk[i]]=false;
	else if(mode==2)for(int i=1;i<=n;i++)Spell[sk[i]]=rand()%(i==plid?500:75)<Skpro[sk[i]];
	else for(int i=1;i<=n;i++)Spell[sk[i]]=rand()%100<Skpro[sk[i]];
	if(rnd==0)Spell[3]=Spell[5]=Spell[8]=false;
	for(int i=1;i<=n;i++)Printsc(i);
	Change_Imp();
	for(int i=1;i<=n;i++)if(!die[i] and i!=plid)ai[i].Choose();
	if(sighter!=plid)
		for(int i=1;i<=H;i++)
			for(int j=1;j<=W;j++)
				Print(i,j);
	for(int i=1;i<=100 and totc>1;i++)Round();
	if(saved>=0)saved--;
};

void Play(){
	saved=-1;
	c7();
	gotoxy(1,W+2);printf("round %d",rnd);
	gotoxy(1,W+10);
	if(mode==2)printf("EXTRA");
	else if(totc==2)printf("1v1");
	else if(totc==3)printf("SUPER EASY");
	else if(totc==4)printf("EASY");
	else if(totc==5)printf("NORMAL");
	else if(totc==6)printf("HARD");
	else if(totc==7)printf("LUNATIC");
	else if(totc==8)printf("SUPER LUNATIC");
	if(mode==3)printf(" (SPELLESS)");
	if(Replay)printf(" (REPLAY)");
	for(int i=1;i<=H;i++){
		for(int j=1;j<=W;j++)
			Print(i,j);
		gotoxy(i,W+1);c7();
		putchar('|');
	}
	gotoxy(H+1,1);for(int i=1;i<=W;i++)printf("--");printf("+");
	while(totc>1 and !die[sighter])R100();
}

void Choose_n(int st);
void Choose_mode(int st);
void ex_Choose_n();
void Choose_Sk();
void Choose_sighter();
void Choose_reptype(int st);

void Choose_n(int st=3){
	puts("选择难度");
	gotoxy(5,1);
	color(GREEN);puts("\tSUPER EASY\t-- NOIP 初赛的难度");
	color(BLUE);puts("\tEASY\t\t-- NOIP PJ的难度");
	color(YELLOW);puts("\tNORMAL\t\t-- NOIP TG的难度");
	color(DYELLOW);puts("\tHARD\t\t-- NOI的难度");
	color(PINK);puts("\tLUNATIC\t\t-- ZJOI的难度");
	color(RED);puts("\tSUPER LUNATIC\t-- YNOI的难度");
	color(WHITE);puts("\t1v1\t\t-- 特殊玩法用");
	c7();puts("PS: 在这个没有AI的版本下，其实都很菜");
	int c=Cho(7,st);
	if(c==-1)return Choose_mode(mode);
	if(c==7)diffi=totc=2;
	else diffi=totc=c+2;
}

void ex_Choose_n(){
	puts("选择难度");
	gotoxy(5,1);
	color(DPINK);puts("\tEXTRA   -- 从前有一位神仙，他闲着蛋疼，去AKIOI......");
	c7();puts("PS: 在这个AI很弱的版本下，其实很菜");
	int ret=Cho(1);
	if(ret==-1)Choose_mode(2);
}

void Choose_Sk(){
	puts("选择自机");
	gotoxy(5,1);
	color(COL[1]);printf("\tA");
	if(mode!=3)puts("\t特技:触发时,下一个百轮获得一定概率的战斗必胜");else puts("");
	color(COL[2]);printf("\tB");
	if(mode!=3)puts("\t特技:触发时,下一个百轮战斗减损兵力很少");else puts("");
	color(COL[3]);printf("\tC");
	if(mode!=3)puts("\t特技:触发时,对自身周围发动不损耗兵力的进攻");else puts("");
	color(COL[4]);printf("\tD");
	if(mode!=3)puts("\t特技:触发时,获得一定兵力,并且下一个百轮其他玩家速度减慢");else puts("");
	c7();printf("\t?");
	if(mode!=3)puts("\t特技:[???]");else puts("");
	color(COL[5]);printf("\tE");
	if(mode!=3)puts("\t特技:触发时,提升自身空地的生产力水平");else puts("");
	color(COL[6]);printf("\tF");
	if(mode!=3)puts("\t特技:触发时,将当前状态与存档取更优者并更新存档.一定时间不触发后存档会消失");else puts("");
	color(COL[7]);printf("\tG");
	if(mode!=3)puts("\t特技:触发时,在随机位置释放范围爆弹,将附近变为专有城市");else puts("");
	color(COL[8]);printf("\tH");
	if(mode!=3)puts("\t特技:触发时,在随机空地(若没有则选择边境)发动远程冲击波");else puts("");
	c7();
	int ret=Cho(SK_CNT+1,5);
	if(ret==-1){
		if(mode==1 or mode==3)Choose_n(totc==2?7:totc-2);
		else if(mode==2)ex_Choose_n();
		return;
	}
	if(ret==5)ret=rand()%SK_CNT+1;
	else if(ret>5)ret--;
	sk[plid]=ret;
}

void Choose_sighter(){
	puts("选择视角对应玩家");
	gotoxy(5,1);
	for(int i=1;i<=diffi;i++){
		if(i==plid)continue;
		gotoxy(i>=plid?3+i:4+i,1);
		color(COL[sk[i]]);
		printf("\t%c",sk[i]+'A'-1);
	}
	int c=Cho(diffi-1,1);
	if(c==-1)return Choose_reptype(2);
	if(c>=plid)c++;
	sighter=c;
}

void Choose_reptype(int st=1){
	puts("选择播放视角");
	gotoxy(5,1);
	color(GREEN);puts("\t第一人称视角");
	color(RED);puts("\t第二人称视角");
	color(YELLOW);puts("\t第三人称视角");
	color(BLUE);puts("\t第负一人称视角");
	int c=Cho(4,st);
	if(c==-1)return Choose_mode(4);
	if(c==3)god=true,sighter=0;
	else if(c==2)Choose_sighter();
	else if(c==1)sighter=plid;
	else sighter=plid,Replay=false;
}

void Choose_mode(int st=1){
	puts("国战模拟器 2");
	printf("version : %s",VERSION);
	gotoxy(5,1);
	color(RED);puts("\tGAME STAT");
	color(DPINK);puts("\tEXTRA START");
	color(YELLOW);puts("\tSPELLESS START");
	color(BLUE);puts("\tREPLAY");
	color(GREEN);puts("\tQUIT");
	mode=Cho(5,st);
	seed=time(NULL)+(long long)(new char);srand(seed);
	n=8;
	if(mode==1){
		Choose_n();
		sighter=plid=rand()%totc+1;
		Choose_Sk();Plr[plid]=true;
		Make_Map();Play();
		End();
	}else if(mode==2){
		diffi=totc=8;
		sighter=plid=rand()%n+1;
		ex_Choose_n();
		Choose_Sk();Plr[plid]=true;
		Make_Map();Play();
		End();
	}else if(mode==3){
		Choose_n();
		sighter=plid=rand()%totc+1;
		Choose_Sk();Plr[plid]=true;
		Make_Map();Play();
		End();
	}else if(mode==4){
		Replay=true;
		Read_Rep();
		srand(seed);Plr[plid=rand()%totc+1]=true;
		sk[plid]=plidsk;
		Make_Map();
		Choose_reptype();
		Play();
		End();
	}
}

int main(){
	system("mode con cols=210 lines=1000");
	Choose_mode();
	return 0;
}
