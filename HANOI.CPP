//  Program for tower of hanoi
//  Program developed by Manish Kumar Srivastava
#include <iostream.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
void  show_man_hanoi(int n);
void show_hanoi(int n);
int steps=0;
 union REGS i,o;
initmouse()
{
	i.x.ax=0;
	int86(0x33,&i,&o);
	return(o.x.ax);
}

showmouseptr()
{
	i.x.ax=1;
	int86(0x33,&i,&o);
	return(0);
}

hidemouseptr()
{
	i.x.ax=2;
	int86(0x33,&i,&o);
	return(0);
}

getmousepos(int *button,int *x,int *y)
{
	i.x.ax=3;
	int86(0x33,&i,&o);
	*button=o.x.bx;
	*x=o.x.cx;
	*y=o.x.dx;
	return(0);
}
// structure for storing disks information on each peg
int x,y;
struct pegs {
		  int pdata;
		  struct pegs * next;
		  struct pegs * back;
		};
typedef struct pegs peg;
void delet(peg **list,int *no);
void pegin(peg **list,int no);
void draw(peg *p1,int x);
////////////////////////////////////////////////////////////////////
struct data1 {
	      char fp;     //source peg
	      char tp;     // destination peg
	      int dn;
	      };
typedef struct data1 info;
// process structure for storing  steps
struct nodetype{
	        struct nodetype * next;
	        struct nodetype * back;
	        info data;
	        };
typedef struct nodetype node;
node * list1=NULL;
// function for inserting step into process queue
void insert(char from, char to,int n1)
{
node *p,*q;
p=new node;
p->data.fp=from;
p->data.tp=to;
p->data.dn=n1;
if(list1==NULL){
	     list1=p;
	     p->next=list1;
	     p->back=list1;
	     return;
	     }
p->next=list1;
p->back=list1->back;
list1->back->next=p;
list1->back=p;
}
// front step remove from process queue
void del()
{
if(list1->next==list1)  {
		   list1=NULL;
		   return;
		   }
list1->back->next=list1->next;
list1->next->back=list1->back;
list1=list1->next;
}
// function for returning no of disks on peg
int show(peg * p1)
{
peg *p;
p=p1;
int steps=0;
if(p1==NULL) return 0;
do {
  //printf("\n move disc %d from %c to %c ",p->data.dn,p->data.fp,p->data.tp);
    p=p->next;
    steps++;
    }while(p!=p1);
return steps;
}
////////////////////////////////////////////////////////////////
void hanoi_tower(char peg1,char peg3,char peg2,int n)
{
 if(n<=0) {
	  printf("error");
	  return;
	  }
    if(n==1) {
	    //printf<<"\n move disc 1 from "<<peg1<<" to "<<peg3;
	    insert(peg1,peg3,1);
	    return;
	    }
       else
	  {
	  hanoi_tower(peg1,peg2,peg3,n-1);
	  //  printf<<"\n move disc " <<n<<" from "<<peg1<<" to "<<peg3;
	   insert(peg1,peg3,n);
	  hanoi_tower(peg2,peg3,peg1,n-1);
	 // hanoi_tower(peg2,peg1,peg3,n-1);
	  }
       }


void move(char px,char py,int n,int x1,int x2,int x3,peg *p1,peg *p2,peg *p3,int m)
{
 peg * p,*q;
 int l,i,j,h1,h2,flag=0,col[10],wx,wy;
 // initilize p as source peg and i as source x co_ordinate
 if(px=='x') {
	      i=x1;
	      p=p1;
	      }
      if(px=='y') {
		i=x2;
		p=p2;
		}
        if(px=='z') {
		  i=x3;
		  p=p3;
		  }
  // initilize q as destination peg and j as destination x co_ordinate
  if(py=='x') {
	      j=x1;
	      q=p1;
	     }
     if(py=='y') {
		j=x2;
		q=p2;
		}
	if(py=='z') {
		   j=x3;
		   q=p3;
		   }
h1=show(p);
h2=show(q);
h1=y-70-h1*10;
h2=y-70-h2*10;
l=3*n*10+10;
i-=l/2;
j-=l/2;
while(1)
 {
   if(h1==h2 && i==j) break;     // i.e. disk reaches to destination
   if(h1<=250) flag=1;
   wx=wherex();
   wy=wherey();
   gotoxy(10,100);
   printf("moves= %d",m);
   gotoxy(wx,wy);
   col[0]=i; col[1]=h1; col[2]=i+l; col[3]=h1;
   col[4]=col[2]; col[5]=h1+10; col[6]=col[4]-l; col[7]=col[5];
   draw(p1,x1);
   draw(p2,x2);
   draw(p3,x3);
   moveto(i,h1);
   linerel(l,0);
   linerel(0,10);
   linerel(-l,0);
   linerel(0,-10);
   setfillstyle(SOLID_FILL,n);
   fillpoly(4,col);
   delay(25);
   cleardevice();
   // disk moves from down to up ( up to y=150 )
   if(h1>250 && flag==0) {
		        h1-=5;
		        //if(h1<=250) h1=250;
		        continue;
		        }
   // disk moves from  left to right
   if(i<j) {
	    i+=5;
	    if(i>j) i=j;
	    continue ;
	    }
    // disk moves from right to left
     if(i>j) {
	      i-=5;
	      continue;
	      }
     // disk moves from up to down
      if(h1<h2 && flag==1) {
			  h1+=5;
			  if(h1>h2) h1=h2;
			  continue;
			 }
    }
}
//////////////////////////////////////////////////////////////////
//    gives disk no of upper most disk
int upperdisk(peg *p)
{
if(p==NULL) return 10;
return p->pdata;
}
///////////////////////////////////////////////////////////////
void main()
 {
  int n,ch,i=1,s,j;
   textmode(C40);
   textbackground(15);
    textcolor(14+BLINK);

  do
  {
  clrscr();
  printf("\n\n\t     TOWER OF HANOI");
  printf("\n\n\n\t 1-> Auto Play\n\t 2-> Manual Play \n\t 3-> Exit ");
  printf("\n\n   Enter your choice ........");

       s=50;
 for(j=0;j<7;j++) {
sound(s); delay(100); nosound();
 sound(2*s); delay(100); nosound();
sound(3*s); delay(100); nosound();
 s+=50; }
  scanf("%d",&ch);
  if(ch!=3)
  {
  printf("\n\n  Enter no of discs...");
  cin>>n;
  }
  switch(ch)
  {
  case 1:
   hanoi_tower('x','z','y',n);
  show_hanoi(n);
  break;
  case 2: show_man_hanoi(n);
	 break;
  case 3: i=0;
  }
  }while(i);
  }
/////////////////////////////////////////////////////////////
void  show_man_hanoi(int n)
  {
  int gdriver = DETECT, gmode;
int i,j,k=0,x1,c=0,x2,x3,length,ny,disk,d,d1,button,px,py,col[10];
char rd,id;
if (n<=0) return;
peg *p1=NULL,*p2=NULL,*p3=NULL,**p4=NULL;
/* initialize graphics and local variables */

initgraph(&gdriver, &gmode, "C:\\TURBOC3\\BGI");
x = getmaxx();
y = getmaxy();
x1=x/4-15;
x2=x/2+5;
x3=3*x/4+20;
setbkcolor(DARKGRAY);
for(i=1;i<=n;i++) pegin(&p1,i);       // initilize the peg x
settextstyle(1,0,5);
outtextxy(x1,40,"TOWER OF HANOI");
draw(p1,x1);
draw(p2,x2);
draw(p3,x3);
    if(initmouse()==0)
  {
    closegraph();
    restorecrtmode();
  cout<<"\nmouse drive is not loaded...";
    exit(1);
    }
do
{
 showmouseptr();
 getmousepos(&button,&px,&py);
 cleardevice();
 gotoxy(5,3);
 printf("moves=%d",k);
 if(button &1==1)
  {
  // disk moves from source peg (x,y,z)
   if(px>=x1-20 && px<=x1+20&&c==0&&py<y-50-show(p1)*10 && py>y-60-show(p1)*10)
     {
       p4=&p1;
       j=1;
		 length=30*p1->pdata+10;
	 delet(&p1,&d);
	 c=1;
       }
  if(px>=x2-20 && px<=x2+20&&c==0 &&py<y-50-show(p2)*10 && py>y-60-show(p2)*10)
  {
       p4=&p2;
       j=2;
	 length=30*p2->pdata+10;
	 delet(&p2,&d);
	 c=1;
       }
   if(px>=x3-20 && px<=x3+20 &&c==0 &&py<y-50-show(p3)*10 && py>y-60-show(p3)*10)
     {
       p4=&p3;
       j=3;
	 length=30*p3->pdata+10;
	 delet(&p3,&d);
	 c=1;
       }
   while( button & 1==1 && c==1)
        {
	 gotoxy(5,3);
	 printf("moves=%d",k);
	 col[0]=px; col[1]=py; col[2]=px+length; col[3]=py;
	 col[4]=col[2]; col[5]=py+10; col[6]=col[4]-length; col[7]=col[5];
	 showmouseptr();
	 getmousepos(&button,&px,&py);
	 draw(p1,x1);
	 draw(p2,x2);
	 draw(p3,x3);
	 moveto(px,py);
	 linerel(length,0);
	 linerel(0,10);
	 linerel(-length,0);
	 linerel(0,-10);
	 setfillstyle(SOLID_FILL,d);
	 fillpoly(4,col);
	 delay(20);
	 cleardevice();
	}
	if(px<x3+20&&px>x3-50 && c==1 && py>y-150&&py<y-60 && upperdisk(p3)>d)
	{         // c= in contact
	    pegin(&p3,d);
	    if(j!=3) k++;
	    c=0;
	}
 else if(px<x2+20&&px>x2-50 && c==1 && py>y-150&&py<y-60&& upperdisk(p2)>d)
        {
	pegin(&p2,d);
	if(j!=2 ) k++;
	c=0;
	}
 else if(px<x1+20&&px>x1-50 && c==1 && py>y-150&&py<y-60 &&upperdisk(p1)>d)
	{
	pegin(&p1,d);
	if(j!=1) k++;
	c=0;
	}
	else
	    {
	      if(c)
		  pegin(p4,d);
	       p4=NULL;
	       c=0;
	     }
        c=0;
        }
    draw(p1,x1);
    draw(p2,x2);
    draw(p3,x3);
    delay(400);
    } while(!kbhit() && show(p3)<n);
draw(p1,x1);
draw(p2,x2);
draw(p3,x3);
settextstyle(1,0,5);
outtextxy(x1,40,"TOWER OF HANOI");
 printf("moves= %d",k);
getch();
closegraph();
}
// function for drawing pegs at any time
void draw(peg *p1,int x)
{
peg *mp=p1->back;
int i,j=1,length,c1,c2,col[10];
rectangle(x-5,y-150,x+5,y-60-show(p1)*10);
setfillstyle(SOLID_FILL,12);
floodfill(x-1,y-145,WHITE);

// textcolor(4+BLINK);

if(p1==NULL) return;
do{
    i=mp->pdata;
    length=3*i*10+10;
    c1=x-length/2;
    c2=y-60-j*10;
    col[0]=c1; col[1]=c2; col[2]=c1+length; col[3]=c2;
    col[4]=col[2]; col[5]=c2+10; col[6]=col[4]-length; col[7]=col[5];
    moveto(c1,c2);
    j++;
    linerel(length,0);
    linerel(0,10);
    linerel(-length,0);
    linerel(0,-10);
    setfillstyle(SOLID_FILL,i);
    fillpoly(4,col);
    mp=mp->back;
   } while(mp!=p1->back);
 }
/////////////////////////////////////////////////////////

void  show_hanoi(int n)
  {
  int gdriver = DETECT, gmode;
int i,j,x1,x2,x3,length,disk,d,m=0,wx,wy;
char rd,id;
if (n<=0) return;
peg *p1=NULL,*p2=NULL,*p3=NULL;
// initialize graphics and local variables
initgraph(&gdriver, &gmode, "c:\\TURBOC3\\bgi");
x = getmaxx();
y = getmaxy();
x1=x/4-15;
x2=x/2+5;
x3=3*x/4+20;
setbkcolor(DARKGRAY);
//textcolor(BLACK);
for(i=1;i<=n;i++) pegin(&p1,i);       // initilize the peg x
settextstyle(1,0,5);
outtextxy(x1,40,"TOWER OF HANOI");
gotoxy(10,100);
printf("moves= %d",m) ;
draw(p1,x1);
draw(p2,x2);
draw(p3,x3);
getch();
cleardevice();
do {
    wx=wherex();
    wy=wherey();
    gotoxy(wx+100,wy+100);
    printf("moves= %d",++m);
    gotoxy(wx,wy);
    draw(p1,x1);     // draws disks on peg x
    draw(p2,x2);      // draws disks on peg y
    draw(p3,x3);
    rd=list1->data.fp;
    id=list1->data.tp;
    disk=list1->data.dn;
    // disk moves from source peg (x,y,z)
    if(rd=='x') delet(&p1,&d);
	 if(rd=='y') delet(&p2,&d);
		if(rd=='z') delet(&p3,&d);
    // path of moving the disks
    move(list1->data.fp,list1->data.tp,list1->data.dn,x1,x2,x3,p1,p2,p3,m);
    // disk reaches to the source peg (x,y,z)
    if(id=='x') pegin(&p1,disk);
	  if(id=='y') pegin(&p2,disk);
		 if(id=='z') pegin(&p3,disk);
     //delete the Ist step of process from prcess queue ( Ist step is over )
     del();
     cleardevice();
     } while(list1!=NULL && !kbhit());
draw(p1,x1);
draw(p2,x2);
draw(p3,x3);
settextstyle(1,0,5);
outtextxy(x1,40,"TOWER OF HANOI");
 printf("moves= %d",m);
list1=NULL;
getch();
closegraph();
}



// disk reaches at destination peg
void pegin(peg **list,int no)
{
peg *q,*p;
q=new peg;
q->pdata=no;
if(*list==NULL) {
		 *list=q;
		 q->next=*list;
		 q->back=*list;
		 return;
		 }
if(q->pdata<(*list)->pdata)
    {
     q->next=*list;
     q->back=(*list)->back;
     (*list)->back->next=q;
     (*list)->back=q;
     *list=q;
      return;
      }
p=(*list)->next;
while(p!=*list && p->pdata<q->pdata){
				  p=p->next;
				  }
 q->next=p;
 q->back=p->back;
 p->back->next=q;
 p->back=q;
 }
//  disk leaves the source peg
void delet(peg **list,int *no)
{
  peg *p,*q;
  p=*list;
*no=(*list)->pdata;
	      if((*list)->next==*list){
				  *list=NULL;
				  free(p);
				  return;
				  }
  p->back->next=p->next;
   p->next->back=p->back;
   *list=(*list)->next;
   free(p);
   return;
   }
/////////////////////////////////////////////////////////////////