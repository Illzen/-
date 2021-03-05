#include<stdio.h>															//调用需要的头文件 
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<windows.h> 
#include<conio.h>
struct data
{																			//学生数据 ： 
	int number;																//学号 
	int clas;																//班级 
	char name[20];															//学生名字
	int r;																	//正确次数 
	int w;																	//错误次数 
};																								
struct data_list
{																			//链表 
	struct data student;													//保存学生数据 
	struct data_list* next;													//指向下一项 
};																							
void menu(struct data_list*);												//声明menu()
void start(int,struct data_list*);											//声明start()
void leave(struct data_list*);												//声明leave() 
void load(struct data_list*);												//声明laod() 
void rand_quiz(struct data_list*); 											//声明rand_quiz() 
void struct_sort(struct data_list*,int);									//声明struct_sort() 
void choose(struct data_list*,struct data_list*,int);						//声明choose() 
void output(struct data_list*);												//声明output() 
void edit(struct data_list*);												//声明edit() 
int lim(struct data_list*);													//声明lim() 
FILE *base;																	//声明全局变量文件指针base 
int main()																	//主函数 
{	
	struct data_list *head,*pm;												//声明结构体指针pm和head 
	system("color 70");														//设置窗口颜色 
	system("mode con cols=41 lines=30");									//设置程序窗口大小								
	head=(struct data_list*)malloc(sizeof(struct data_list));				//从head开始创建链表 
	head->next=(struct data_list*)malloc(sizeof(struct data_list));			
	pm=head->next;					
	load(pm);																//传入链表至load函数 
	pm=head->next;
	while(1)
	{
		menu(pm);															//菜单 
	}
}
int lim(struct data_list *pl)												//lim，计算链表长度 
{
	struct data_list *ph;
	int n=0;
	ph=pl;
	while(pl->next->next != NULL)
	{
		pl=pl->next;
		n++;
	}
	pl=ph;
	return n-1;
}
void edit(struct data_list *pe)												//edit，实现编辑功能 
{
	struct data_list *pd,*pt;
	int i,n=1,j;
	char x=' ';
	while(x!='q')															//打印、刷新edit界面 
	{
		x=' ';
		pd=pe;
		i=1;
		system("cls");
		puts("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
		puts("┃    学号   班级   姓名   正确   错误  ┃");
		puts("┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃");
		while(pd->next->next != NULL)										//输出链表 
		{
			printf("┃");
			if(n==i)
			{
				printf("%3d→",i);											//设置光标 
			}
			else
			{
				printf("%3d  ",i);
			}
			printf("%6d%6d",pd->student.number,pd->student.clas);
			printf("%8s",pd->student.name);
			printf("%6d%6d ┃\n",pd->student.r,pd->student.w);
			pd=pd->next;
			i++;
		}
		puts("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
		puts(" 上/下(w/s)添加(a)编辑(e)删除(d)退出(q)");					
		x=getch();															//读取下一个按键 
		pd=pe;																//将指针移动至链表首个存储信息的节点 
		if(x=='w')															//光标上移 
		{
			n--;
			if(n<0)
			{
				n=0;
			}
		}
		else if(x=='s')														//光标下移 
		{
			n++;
			if(n>=lim(pe))
			{
				n=lim(pe)+1;
			}
		}
		else if(x=='e')														//编辑选中条目 
		{
			j=1;
			while(j<n)
			{
				pd=pd->next;
				j++;
			}
			puts("格式:num class    name right wrong");
			printf("  %6d%6d",pd->student.number,pd->student.clas);
			printf("%8s",pd->student.name);
			printf("%6d%6d     \n     ",pd->student.r,pd->student.w);
			scanf("%d %d ",&pd->student.number,&pd->student.clas);
        	scanf("%s ",&pd->student.name);
        	scanf("%d %d",&pd->student.r,&pd->student.w);
		}
		else if(x=='a')														//追加节点 
		{
			while(pd->next->next!=NULL)
			{
				pd=pd->next;
			}
			puts("格式:num class name right wrong");
			scanf("%d %d ",&pd->student.number,&pd->student.clas);
        	scanf("%s ",&pd->student.name);
        	scanf("%d %d",&pd->student.r,&pd->student.w);
       		pd->next=(struct data_list*)malloc(sizeof(struct data_list));
       		pd=pd->next;
       		pd->next=(struct data_list*)malloc(sizeof(struct data_list));
       		pd=pd->next;
       		pd->next=NULL;
		}
		else if(x=='d')														//删除节点 
		{
			pt=pd;
			j=1;
			while(j<n-1)
			{
				pt=pt->next;
				j++;
			}
			pd=pt->next->next;
			free(pt->next);
			pt->next=pd;
		}
		else
		{
			puts("未知操作");
		}
	}
}
void output(struct data_list *po)											//output，输出查询界面 
{
	struct data_list *pu;
	pu=po;
	char x=' ';
	while(x!='q')
	{
		system("cls");
		puts("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
		puts("┃    学号   班级   姓名   正确   错误  ┃");
		puts("┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃");
		while(pu->next->next != NULL)										//输出链表 
		{
			printf("┃   %6d%6d",pu->student.number,pu->student.clas);
			printf("%8s",pu->student.name);
			printf("%6d%6d   ┃\n",pu->student.r,pu->student.w);
			pu=pu->next;
		}
		puts("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
		puts("\t按学号排序(a)按分数排序(d)退出(q)");
		x=getch();
		pu=po;
		if(x=='a')															//根据选择调用struct_sort的不同模式 
		{
			struct_sort(pu,1);
		}
		else if(x=='d')
		{
			struct_sort(pu,2);
		}
		else
		{
			;
		}
	}
}
void choose(struct data_list *cb,struct data_list *ca,int mode)				//choose，比较并交换两个节点 
{
	struct data_list ct;
	int sign=0;
	if(mode==0)																//mode0，按序号递增判断，班级相同时调用 
	{
		if(cb->student.number<ca->student.number)
		{
			sign=1;
		}
	}
	else if(mode==1)														//mode1，按班级递增判断，分数相同时调用 
	{
		if(cb->student.clas<ca->student.clas)
		{
			sign=1;
		}
		else if(cb->student.clas==ca->student.clas)
		{
			choose(cb,ca,0);
		}
		else
			;
	}
	else if(mode==2)														//mode2，按分数递减判断
	{
		if((cb->student.r-cb->student.w) > (ca->student.r-ca->student.w))
		{
			sign=1;
		}
		else if((cb->student.r-cb->student.w)==(ca->student.r-ca->student.w))
		{
			choose(cb,ca,1);
		}
		else
			;		
	}
	else
	{
		puts("未知错误\n");
	}
	if(sign==1)																// 判断成功时交换两节点信息 
	{
		ct.student.clas=cb->student.clas;
		ct.student.number=cb->student.number;
		ct.student.r=cb->student.r;
		ct.student.w=cb->student.w;
		strcpy(ct.student.name,cb->student.name);
		cb->student.clas=ca->student.clas;
		cb->student.number=ca->student.number;
		cb->student.r=ca->student.r;
		cb->student.w=ca->student.w;
		strcpy(cb->student.name,ca->student.name);
		ca->student.clas=ct.student.clas;
		ca->student.number=ct.student.number;
		ca->student.r=ct.student.r;
		ca->student.w=ct.student.w;
		strcpy(ca->student.name,ct.student.name);
	}
}
void struct_sort(struct data_list *ps,int mode)								//struct_sort，结构体排序 
{
	struct data_list *pa,*pb;
	int a,b;
	pa=ps;
	a=0;
	while(pa->next->next!=NULL)												//冒泡排序法，调用choose 
	{
		if(a>lim(ps))
		{
			break;
		}
		pb=pa->next;
		b=0;
		while(pb->next->next!=NULL)
		{
			if((a+b)>lim(ps))
			{
				break;
			}
			choose(pb,pa,mode);
			b++;
			pb=pb->next;
		}
		pa=pa->next;
		a++;
	}
}
void rand_quiz(struct data_list *ph)										//rand_quiz，随机提问功能 
{
	srand((unsigned int)time(NULL));
	int i=0,n;
	char x;
	struct data_list *pr;
	pr=ph->next;
	system("cls");
	i=lim(ph); 
	n=rand();	
	n=(n+i)%(i+1);															//生成区间内随机值 
	puts("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	printf("┃随机号数生成为%d                       ┃\n",n);
	pr=ph;												 
	for(i=0;i<n;i++)
	{
		pr=pr->next;
	}
	puts("┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃");
	puts("┃    学号   班级   姓名   正确   错误  ┃");
	printf("┃   %6d%6d",pr->student.number,pr->student.clas);				//调用对应节点信息 
	printf("%8s",pr->student.name);
	printf("%6d%6d   ┃\n",pr->student.r,pr->student.w);
	puts("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	puts("\t\t回答正确/回答错误(y/n)");
	while(x!='y'&&x!='n')													//判断正误 
	{
		x=' ';
		x=getch();
	}
	if(x=='y')																//计分 
	{
		pr->student.r++;
	}
	else if(x=='n')
	{
		pr->student.w++;
	}
	else
	{
		puts("计分失败\n");
	}
	puts("计分完成,按任意键继续                 ");
	getch();
}
void load(struct data_list *pl)												//load，启动时加载文件，创建链表 
{
	puts("打开文件\n");
	if((base=fopen("base.txt","r"))==NULL)
	{
        printf("打开文件失败，创建新文件\n");
        base=fopen("base.txt","w");
        Sleep(100); 
		printf("创建成功"); 
    }   
    Sleep(100);
    puts("创建链表\n");
    while(!feof(base))														//读取文件内信息 
	{
        fscanf(base,"%d %d ",&pl->student.number,&pl->student.clas);
        fscanf(base,"%s ",&pl->student.name);
        fscanf(base,"%d %d",&pl->student.r,&pl->student.w);
        pl->next=(struct data_list*)malloc(sizeof(struct data_list));
        pl=pl->next;
        pl->next=NULL;
    }
    Sleep(80);
    puts("创建完成\n");
    fclose(base);
    Sleep(80);
    puts("初始化完成\n");
    Sleep(80);
}
void leave(struct data_list *pl)											//leave，退出时将链表保存至文件内 
{
	system("cls");																								
	puts("打开文件\n");
	Sleep(100);
	if((base=fopen("base0.txt","w"))==NULL)
	{
        printf("Can not open file\n");
        exit(1);
    }
    Sleep(80);
    puts("保存中\n");
    while(pl->next->next != NULL)											//写入链表数据至文件中 
	{
		fprintf(base,"%d %d",pl->student.number,pl->student.clas);
		fprintf(base," %s",pl->student.name);
		fprintf(base," %d %d\n",pl->student.r,pl->student.w);
		pl = pl->next;
	}
	fclose(base);
	system("del base.txt");													//替换原文件 
	system("rename base0.txt base.txt");
	Sleep(80);
	puts("保存成功\n");
	Sleep(100);
	puts("再见\n");															//
	Sleep(80);																//
	exit(1);																//
}																																														
void start(int i,struct data_list *ps)										//start，判定选择并调用对应函数 
{		
	struct data_list *pq;
	pq=ps;																					
		switch(i)																						
		{																						
			case 1:
				{
					rand_quiz(pq);
					break;
				}																							
			case 2:
				{
					struct_sort(pq,1);
					pq=ps;
					output(pq);
					break;
				}
			case 3:
				{
					edit(pq);
					break;
				}																							
			case 4:
				{
					leave(pq);
					break;
				}
			default:
				{
					puts("选项错误");
					break;
				}																							
		}	
}
void menu(struct data_list* pm)												//menu,输出程序主界面 
{
	char i=' ';
	int x;
	while(i>'5'||i<'1')
	{
		system("cls");
		i=' ';
		puts("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");//制表符占2字节 
		puts("┃             课堂提问管理系统         ┃"); 
		puts("┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃");
		puts("┃1.随机提问              2.浏览信息    ┃");

		puts("┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃");
		puts("┃3.编辑                  4.退出        ┃");
		puts("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
      printf("输入序号以执行下一步操作:%c            \n",i);
		i=getch();															//抓取输入字符 
	}
	if(i=='1')
	{
		x=1;
	}
	else if(i=='2')
	{
		x=2;
	}
	else if(i=='3')
	{
		x=3;
	}
	else if(i=='4')
	{
		x=4;
	}
	Sleep(100);
	start(x,pm);
}
