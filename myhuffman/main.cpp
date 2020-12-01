/*	程序名称：哈夫曼编码与解码
	主要功能：创建哈夫曼树，查看编码信息，打印大致哈夫曼树样子，压缩文件，解压文件
	健壮性  ：对一些非法输入输出进行了控制，当然应该还有很多不足的地方有待改进
	交互性  ：设置了一个主界面和四中分界面，在主界面与分界面之间可以自由跳转*/

#include <cstdio>
#include <cstdlib>
#include "HuffmanTree.h"
int main()
{
//    int mmmm=sizeof(Node);
//    printf("%d",mmmm);
//    scanf("%d",&mmmm);
    double *w;                   //存放每个字符概率
    char *content;               //存放字符，与w对应
    int n;                      //存放叶子数
    HuffmanTree HT;                  //HT代表哈弗曼树
    HuffmanCode HC;                  //存放每一个叶子的哈弗曼编码

    while (1)
    {//程序主窗口
        printf(" << =================== 功   能   选   择 ================ >>  \n\n");
        printf("【1】 ： 创建并观察哈夫曼树\n");
        printf("【2】 ： 文件压缩\n");
        printf("【3】 ： 文件解压缩 \n");
        printf("【4】 ： 查看压缩程度   \n");
        printf("【5】 ： 退出程序\n\n\n");
        printf("请选择功能 ： ");
        char ch;
        scanf("%c", &ch);
        while(getchar()!='\n') continue;
        switch (ch)
        {
            case '1':                     //显示当前哈夫曼编码详细信息
            {
                count(w, n, content);               //统计给定文本的各个字符的概率，得到w（每个字符的权重）和字符数目和content（内容）。
                CreatHuffman(HT, w, n);        //根据w构造了一颗有n个叶子的哈弗曼树HT
                HuffmanCoding(HT, HC, n);          //根据已经构造好的哈弗曼树HT求出每一个叶子的哈弗曼编码，且存储在HC里面
                CreatTable(HT,n,content,HC);
                while (1)
                {//功能2的弹出选项
                    printf("【a】 ： 显示当前哈夫曼编码详细信息  \n\n");
                    printf("【b】 ： 打印出“哈夫曼树”的大致样子 \n\n");
                    printf("【c】 ： 返回主菜单 \n\n");
                    printf("	请选择功能 :");
                    char ch2;
                    scanf("%c", &ch2);
                    while(getchar()!='\n') continue;
                    switch (ch2)
                    {
                        case 'a':
                            HuffmanImformation(n,w,content,HC);        //调用函数打印详细信息
                            continue;
                        case 'b':
                            PrintTree(2*n-1,HT);     //打印以HT[2*n-1]为根节点的哈夫曼树
                            continue;
                        case 'c':
                            break;
                        default:
                        {
                            printf("输入有误，请重新输入!\n");
                            continue;
                        }
                    }//switch
                    break;
                }//功能2的弹出选项
                break;
            }//case '1'

            case '2':                     //文件压缩
            {
                CompressTxt();          //文件压缩
                break;
            }//case '2'

            case '3':                    //文件解压缩
            {
                HuffmanDecoding();     //解码
                break;
            }//case '3'

            case '4':
            {
                showmuch();
                break;
            }
            case '5':                   //退出程序
                exit(0);

            default:                     //错误输入处理
            {
                printf("功能选择错误，请重新选择正确的选项 ! \n");
                break;
            }//default

        }//主界面switch
    }//主界面
}