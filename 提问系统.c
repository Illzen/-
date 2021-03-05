#include<stdio.h>															//������Ҫ��ͷ�ļ� 
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<windows.h> 
#include<conio.h>
struct data
{																			//ѧ������ �� 
	int number;																//ѧ�� 
	int clas;																//�༶ 
	char name[20];															//ѧ������
	int r;																	//��ȷ���� 
	int w;																	//������� 
};																								
struct data_list
{																			//���� 
	struct data student;													//����ѧ������ 
	struct data_list* next;													//ָ����һ�� 
};																							
void menu(struct data_list*);												//����menu()
void start(int,struct data_list*);											//����start()
void leave(struct data_list*);												//����leave() 
void load(struct data_list*);												//����laod() 
void rand_quiz(struct data_list*); 											//����rand_quiz() 
void struct_sort(struct data_list*,int);									//����struct_sort() 
void choose(struct data_list*,struct data_list*,int);						//����choose() 
void output(struct data_list*);												//����output() 
void edit(struct data_list*);												//����edit() 
int lim(struct data_list*);													//����lim() 
FILE *base;																	//����ȫ�ֱ����ļ�ָ��base 
int main()																	//������ 
{	
	struct data_list *head,*pm;												//�����ṹ��ָ��pm��head 
	system("color 70");														//���ô�����ɫ 
	system("mode con cols=41 lines=30");									//���ó��򴰿ڴ�С								
	head=(struct data_list*)malloc(sizeof(struct data_list));				//��head��ʼ�������� 
	head->next=(struct data_list*)malloc(sizeof(struct data_list));			
	pm=head->next;					
	load(pm);																//����������load���� 
	pm=head->next;
	while(1)
	{
		menu(pm);															//�˵� 
	}
}
int lim(struct data_list *pl)												//lim������������ 
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
void edit(struct data_list *pe)												//edit��ʵ�ֱ༭���� 
{
	struct data_list *pd,*pt;
	int i,n=1,j;
	char x=' ';
	while(x!='q')															//��ӡ��ˢ��edit���� 
	{
		x=' ';
		pd=pe;
		i=1;
		system("cls");
		puts("��������������������������������������������������������������������������������");
		puts("��    ѧ��   �༶   ����   ��ȷ   ����  ��");
		puts("��������������������������������������������������������������������������������");
		while(pd->next->next != NULL)										//������� 
		{
			printf("��");
			if(n==i)
			{
				printf("%3d��",i);											//���ù�� 
			}
			else
			{
				printf("%3d  ",i);
			}
			printf("%6d%6d",pd->student.number,pd->student.clas);
			printf("%8s",pd->student.name);
			printf("%6d%6d ��\n",pd->student.r,pd->student.w);
			pd=pd->next;
			i++;
		}
		puts("��������������������������������������������������������������������������������");
		puts(" ��/��(w/s)���(a)�༭(e)ɾ��(d)�˳�(q)");					
		x=getch();															//��ȡ��һ������ 
		pd=pe;																//��ָ���ƶ��������׸��洢��Ϣ�Ľڵ� 
		if(x=='w')															//������� 
		{
			n--;
			if(n<0)
			{
				n=0;
			}
		}
		else if(x=='s')														//������� 
		{
			n++;
			if(n>=lim(pe))
			{
				n=lim(pe)+1;
			}
		}
		else if(x=='e')														//�༭ѡ����Ŀ 
		{
			j=1;
			while(j<n)
			{
				pd=pd->next;
				j++;
			}
			puts("��ʽ:num class    name right wrong");
			printf("  %6d%6d",pd->student.number,pd->student.clas);
			printf("%8s",pd->student.name);
			printf("%6d%6d     \n     ",pd->student.r,pd->student.w);
			scanf("%d %d ",&pd->student.number,&pd->student.clas);
        	scanf("%s ",&pd->student.name);
        	scanf("%d %d",&pd->student.r,&pd->student.w);
		}
		else if(x=='a')														//׷�ӽڵ� 
		{
			while(pd->next->next!=NULL)
			{
				pd=pd->next;
			}
			puts("��ʽ:num class name right wrong");
			scanf("%d %d ",&pd->student.number,&pd->student.clas);
        	scanf("%s ",&pd->student.name);
        	scanf("%d %d",&pd->student.r,&pd->student.w);
       		pd->next=(struct data_list*)malloc(sizeof(struct data_list));
       		pd=pd->next;
       		pd->next=(struct data_list*)malloc(sizeof(struct data_list));
       		pd=pd->next;
       		pd->next=NULL;
		}
		else if(x=='d')														//ɾ���ڵ� 
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
			puts("δ֪����");
		}
	}
}
void output(struct data_list *po)											//output�������ѯ���� 
{
	struct data_list *pu;
	pu=po;
	char x=' ';
	while(x!='q')
	{
		system("cls");
		puts("��������������������������������������������������������������������������������");
		puts("��    ѧ��   �༶   ����   ��ȷ   ����  ��");
		puts("��������������������������������������������������������������������������������");
		while(pu->next->next != NULL)										//������� 
		{
			printf("��   %6d%6d",pu->student.number,pu->student.clas);
			printf("%8s",pu->student.name);
			printf("%6d%6d   ��\n",pu->student.r,pu->student.w);
			pu=pu->next;
		}
		puts("��������������������������������������������������������������������������������");
		puts("\t��ѧ������(a)����������(d)�˳�(q)");
		x=getch();
		pu=po;
		if(x=='a')															//����ѡ�����struct_sort�Ĳ�ͬģʽ 
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
void choose(struct data_list *cb,struct data_list *ca,int mode)				//choose���Ƚϲ����������ڵ� 
{
	struct data_list ct;
	int sign=0;
	if(mode==0)																//mode0������ŵ����жϣ��༶��ͬʱ���� 
	{
		if(cb->student.number<ca->student.number)
		{
			sign=1;
		}
	}
	else if(mode==1)														//mode1�����༶�����жϣ�������ͬʱ���� 
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
	else if(mode==2)														//mode2���������ݼ��ж�
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
		puts("δ֪����\n");
	}
	if(sign==1)																// �жϳɹ�ʱ�������ڵ���Ϣ 
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
void struct_sort(struct data_list *ps,int mode)								//struct_sort���ṹ������ 
{
	struct data_list *pa,*pb;
	int a,b;
	pa=ps;
	a=0;
	while(pa->next->next!=NULL)												//ð�����򷨣�����choose 
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
void rand_quiz(struct data_list *ph)										//rand_quiz��������ʹ��� 
{
	srand((unsigned int)time(NULL));
	int i=0,n;
	char x;
	struct data_list *pr;
	pr=ph->next;
	system("cls");
	i=lim(ph); 
	n=rand();	
	n=(n+i)%(i+1);															//�������������ֵ 
	puts("��������������������������������������������������������������������������������");
	printf("�������������Ϊ%d                       ��\n",n);
	pr=ph;												 
	for(i=0;i<n;i++)
	{
		pr=pr->next;
	}
	puts("��������������������������������������������������������������������������������");
	puts("��    ѧ��   �༶   ����   ��ȷ   ����  ��");
	printf("��   %6d%6d",pr->student.number,pr->student.clas);				//���ö�Ӧ�ڵ���Ϣ 
	printf("%8s",pr->student.name);
	printf("%6d%6d   ��\n",pr->student.r,pr->student.w);
	puts("��������������������������������������������������������������������������������");
	puts("\t\t�ش���ȷ/�ش����(y/n)");
	while(x!='y'&&x!='n')													//�ж����� 
	{
		x=' ';
		x=getch();
	}
	if(x=='y')																//�Ʒ� 
	{
		pr->student.r++;
	}
	else if(x=='n')
	{
		pr->student.w++;
	}
	else
	{
		puts("�Ʒ�ʧ��\n");
	}
	puts("�Ʒ����,�����������                 ");
	getch();
}
void load(struct data_list *pl)												//load������ʱ�����ļ����������� 
{
	puts("���ļ�\n");
	if((base=fopen("base.txt","r"))==NULL)
	{
        printf("���ļ�ʧ�ܣ��������ļ�\n");
        base=fopen("base.txt","w");
        Sleep(100); 
		printf("�����ɹ�"); 
    }   
    Sleep(100);
    puts("��������\n");
    while(!feof(base))														//��ȡ�ļ�����Ϣ 
	{
        fscanf(base,"%d %d ",&pl->student.number,&pl->student.clas);
        fscanf(base,"%s ",&pl->student.name);
        fscanf(base,"%d %d",&pl->student.r,&pl->student.w);
        pl->next=(struct data_list*)malloc(sizeof(struct data_list));
        pl=pl->next;
        pl->next=NULL;
    }
    Sleep(80);
    puts("�������\n");
    fclose(base);
    Sleep(80);
    puts("��ʼ�����\n");
    Sleep(80);
}
void leave(struct data_list *pl)											//leave���˳�ʱ�����������ļ��� 
{
	system("cls");																								
	puts("���ļ�\n");
	Sleep(100);
	if((base=fopen("base0.txt","w"))==NULL)
	{
        printf("Can not open file\n");
        exit(1);
    }
    Sleep(80);
    puts("������\n");
    while(pl->next->next != NULL)											//д�������������ļ��� 
	{
		fprintf(base,"%d %d",pl->student.number,pl->student.clas);
		fprintf(base," %s",pl->student.name);
		fprintf(base," %d %d\n",pl->student.r,pl->student.w);
		pl = pl->next;
	}
	fclose(base);
	system("del base.txt");													//�滻ԭ�ļ� 
	system("rename base0.txt base.txt");
	Sleep(80);
	puts("����ɹ�\n");
	Sleep(100);
	puts("�ټ�\n");															//
	Sleep(80);																//
	exit(1);																//
}																																														
void start(int i,struct data_list *ps)										//start���ж�ѡ�񲢵��ö�Ӧ���� 
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
					puts("ѡ�����");
					break;
				}																							
		}	
}
void menu(struct data_list* pm)												//menu,������������� 
{
	char i=' ';
	int x;
	while(i>'5'||i<'1')
	{
		system("cls");
		i=' ';
		puts("��������������������������������������������������������������������������������");//�Ʊ��ռ2�ֽ� 
		puts("��             �������ʹ���ϵͳ         ��"); 
		puts("��������������������������������������������������������������������������������");
		puts("��1.�������              2.�����Ϣ    ��");

		puts("��������������������������������������������������������������������������������");
		puts("��3.�༭                  4.�˳�        ��");
		puts("��������������������������������������������������������������������������������");
      printf("���������ִ����һ������:%c            \n",i);
		i=getch();															//ץȡ�����ַ� 
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
