/*
 *     若程序显示无法打开文件，请在mgraph.cpp第10行和第27行自行修改文件路径名；
 *     本程序使用Floyd算法实现。
 */
#include"mgraph.h"
int main()
{
    mgraph G;
    G.vexnum=0;
    for(int i=0;i<maxvertices;i++)
        for(int j=0;j<maxvertices;j++)
            G.edge[i][j]=maxweight;
    create(G);
    while(1){//程序主窗口
        printf(" << =================== 功   能   选   择 ================ >>  \n\n");
        printf("【1】 ： 两地间最短路径\n");
        printf("【2】 ： 删除城市\n");
        printf("【3】 ： 退出程序   \n");
        printf("请选择功能 ： ");
        int ch;
        scanf("%d", &ch);
        while(getchar()!='\n') continue;
        switch (ch)
        {
            case 1:
                shortpath(G);//最短路径
                break;
            case 2:
                while (1)
                {
                    printf("【a】 ： 删除城市  \n\n");
                    printf("【b】 ： 最短路径 \n\n");
                    printf("【c】 ： 返回主菜单 \n\n");
                    printf("	请选择功能 :");
                    char ch2;
                    scanf("%c", &ch2);
                    while(getchar()!='\n') continue;
                    switch (ch2)
                    {
                        case 'a':
                            int n;
                            printf("请输入要删除的城市编号：");
                            scanf("%d",&n);
                            while(getchar()!='\n') continue;
                            for(int i=0;i<=G.vexnum;i++){
                                G.edge[i][n]=maxweight;
                                G.edge[n][i]=maxweight;
                            }
                            continue;
                        case 'b':
                            shortpath(G);//最短路径
                            continue;
                        case 'c':
                            create(G);
                            printf("铁路网已复原\n");
                            break;
                        default:
                        {
                            printf("输入有误，请重新输入!\n");
                            continue;
                        }
                    }
                    break;
                }
                break;
            case 3:
                exit(0);

            default:                     //错误输入处理
            {
                printf("功能选择错误，请重新选择正确的选项 ! \n");
                break;
            }//default

        }
    }
}
