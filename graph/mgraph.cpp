//
// Created by wxxxx on 2020/12/1.
//
#include "mgraph.h"
void create(mgraph &G){
    FILE *in;
    FILE *in2;
    int d=0;
    int i,j;
    if((in=fopen("/home/wxxxx/桌面/clion-2020.2.4/CLionProjects/zuiduanlujing/dist.txt","r"))==NULL)//打开文件dist
    {
        printf("无法打开dist文件\n");
        exit(0);
    }//文件dist
    int arcnumber=0;
    int vexnumber=0;
    while((fscanf(in,"%d %d %d",&i,&j,&d)>0)){
        if(vexnumber<i)
            vexnumber=i;
        if(vexnumber<j)
            vexnumber=j;
        arcnumber++;
        G.edge[i][j]=d;
        G.edge[j][i]=d;
    }
    G.vexnum=vexnumber;
    if((in2=fopen("/home/wxxxx/桌面/clion-2020.2.4/CLionProjects/graph/city.txt","r"))==NULL)//打开文件city
    {
        printf("无法打开city文件\n");
        exit(0);
    }//文件city
    printf("邻接矩阵:\n");
    printf("  ");
    for(i=0;i<=G.vexnum;i++)
    {
        printf("%4d",i);
    }
    printf("\n");
    for(i=0;i<=G.vexnum;i++)
    {
        printf("%2d",i);
        for(j=0;j<=G.vexnum;j++)
        {
            if(G.edge[i][j]<maxweight)
            {
                printf("%4d",G.edge[i][j]);
            }
            else
            {
                printf("   #");
            }
        }
        printf("\n");
    }//输出邻接表
    printf("其中对应关系:\n");
    char c;
    while(fscanf(in2,"%c",&c)!=EOF) printf("%c",c); //从文本中读入并在控制台打印出来
    fclose(in);
    fclose(in2);
}

void shortpath(mgraph &G)
{
    weight d[maxvertices][maxvertices];
    int path[maxvertices][maxvertices];
    int i,j,k;
    for(i=0;i<=G.vexnum;i++)
        for(j=0;j<=G.vexnum;j++){
            d[i][j]=G.edge[i][j];
            path[i][j]=j;
        }

    for(k=0;k<=G.vexnum;k++)
        for(i=0;i<=G.vexnum;i++)
            for(j=0;j<=G.vexnum;j++){
                if(d[i][k]+d[k][j]<d[i][j]){
                    d[i][j]=d[i][k]+d[k][j];
                    path[i][j]=path[i][k];
                }
            }
    for(i=0;i<=G.vexnum;i++)
        d[i][i]=0;
    printf("城市距离表:\n");
    printf("    ");
    for(i=0;i<=G.vexnum;i++)
    {
        printf("%5d",i);
    }
    printf("\n");
    for(i=0;i<=G.vexnum;i++)
    {
        printf("%5d",i);
        for(j=0;j<=G.vexnum;j++)
        {
            if(d[i][j]<maxweight)
            {
                printf("%5d",d[i][j]);
            }
            else
            {
                printf("   # ");
            }
        }
        printf("\n");
    }
    int f,en;
    printf("请输入出发地编号和终点编号：");
    scanf("%d%d",&f,&en);
    while(getchar()!='\n') continue;
    if(d[f][en]>=maxweight){
        printf("从此天各一方！\n");
    }
    else {
        while (f != en) {
            printf("%d->", f);
            f = path[f][en];
        }
        printf("%d\n", en);
    }
}