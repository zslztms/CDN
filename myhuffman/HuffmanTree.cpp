//
// Created by wxxxx on 2020/11/17.
//
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "HuffmanTree.h"
#include "Queue.h"


void CreatHuffman(HuffmanTree &HT, double *w, int n)
{
    if (n == 0)
    {
        printf("您指定的文件是一个空文件 :");
        return ;
    }
    if (n == 1)
    {
        printf("您指定的文件只有一种字符。");
        return ;
    }

    int m = 2 * n - 1;             //m为总结点数
    int i;                     //计数变量
    int s1, s2;

    HT = (HuffmanTree)malloc((m + 1)*sizeof(HTNode));    //动态分配m+1单位数组存放m个节点，0号下标不使用
    HuffmanTree p = HT;   //p指向结点，操作指针

    p++;            //0号不用
    w++;

    for (i = 1; i <= n; i++, p++, ++w)    //给1-n号结点赋初始值，权重分别对应w的第一号到第n号
        *p = { *w,0,0,0 };
    for (; i <= m; i++, p++)           //剩下非叶子结点全部权重赋值为0
        *p = { 0,0,0,0 };

    for (i = n + 1; i <= m; i++)                          //开始构造Huffman树
    {
        Select(HT, i - 1, s1, s2);//每一次在第一个结点到第i-1个结点中选出parent为0，且weight最小的两个节点，下标为s1,s2
        HT[s1].parent = i;             //s1,s2号元素双亲为i号结点
        HT[s2].parent = i;
        HT[i].lchild = s1;             //i号元素左右孩子为s1号和s2号结点
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;  //i号结点权重为s1,s2权重之和
    }

    printf("\n 哈夫曼树创建成功  。 \n\n\n");

}

void HuffmanCoding(HuffmanTree HT, HuffmanCode &HC, int n)
{//从叶子结点到根结点逆向求n个叶子的哈弗曼树HT的哈夫曼编码，n个叶子的编码存在HC[1]-HC[n]指向的字符串中
    HC = (HuffmanCode)malloc((n + 1)*sizeof(char *));
    char *cd = (char *)malloc(n*sizeof(char));            //分配编码工作空间
    cd[n - 1] = '\0';
    int start;                      //start用来标志最后存放在cd里面的编码的起始位置
    int c, f;                      //f记录双亲下标，c始终是上一个f
    for (int i = 1; i <= n; i++)   //从第一个叶子到第n个逐一求哈弗曼编码
    {
        start = n - 1;     //初始位置在cd的最后一个位置
        for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
        {
            if (HT[f].lchild == c)
                cd[--start] = '0';
            else
                cd[--start] = '1';
        }
        HC[i] = (char *)malloc((n - start)*sizeof(char));      //给第i个叶子的编码分配存储空间
        strcpy(HC[i], &cd[start]);
    }

    free(cd);     //释放工作空间
}
void CreatTable(HuffmanTree &HT, int n,char *content,HuffmanCode &HC){
    Node tnode[n+1];
    for(int i=1;i<=n;i++){
        tnode[i].data=content[i];
        for(int j=0;j<20;j++){
            tnode[i].code[j]=HC[i][j];
        }
    }
    FILE *ftable;
    printf("		请输入编码表将要存放的位置及文件：");
    char source[100];
    scanf("%s",source);
    while(getchar()!='\n') continue;
    ftable=fopen(source,"wb");
    for(int i=0;i<=n;i++) {

        fwrite( tnode+i, sizeof(Node) , 1, ftable);

    }
    fclose(ftable);
//    FILE *ftable2;
//    ftable2=fopen(source,"rb+");
//    for(int i=0;i<=n;i++){
//
//        fread(tnode+i,sizeof(Node),1,ftable2);
//        printf("%c  :  %s",tnode[i].data,tnode[i].code);
//
//
//    }
}
void HuffmanDecoding(void)    //根据哈弗曼树HT解码
{
    postion3:printf("请输入你要进行解压缩的编码文件 ：");
    char source[100];
    scanf("%s",source);
    while(getchar()!='\n') continue;
    printf("请输入对应的编码表文件 ：");
    char tablename[100];
    scanf("%s",tablename);
    while(getchar()!='\n') continue;
    printf("请输入解压缩到哪个文件 ：");
    char des[100];
    scanf("%s",des);
    while(getchar()!='\n') continue;
    FILE *fp1;           //fp1指向源文件
    FILE *fp2;           //fp1指向目标文件
    FILE *fp3;           //fp1指向编码表
    if ((fp1 = fopen(source, "rb")) == nullptr)
    {//错误处理
        printf("不能打开你指定的编码文件，请检查你是否输入有误。\n");
        goto postion3;
    }
    if ((fp3 = fopen(tablename, "rb")) == nullptr)
    {//错误处理
        printf("不能打开你指定的编码表文件，请检查你是否输入有误。\n");
        goto postion3;
    }
    if ((fp2 = fopen(des, "wt")) == nullptr)
    {//错误处理
        printf("不能打开你指定的解码文件，请检查你是否输入有误。\n");
        goto postion3;
    }

    fseek(fp3,0,SEEK_END);
    int n =ftell(fp3)/sizeof(Node)-1;
    fseek(fp3,0,SEEK_SET);

    Node tnode[n+1];
    for(int i=0;i<=n;i++) {

        fread(&tnode[i], sizeof(Node) , 1, fp3);

    }
//    for(int i=1;i<=n;i++){
//        printf("%c   :    %s ",tnode[i].data,tnode[i].code);
//    }
//    int ssss;
//    scanf("%d",&ssss);
    unsigned char ch;          //临时存放文件里的每一个字符
    fseek(fp1,0,SEEK_END);
    int x=ftell(fp1);
    fseek(fp1,0,SEEK_SET);
    ch =fgetc(fp1);
    char res[20]="";

//    int l=0;
    for(int l=0;l<x;l++){
        for (int j = 0; j < 8; j++) {
            //与运算，一个个位读取
            if (ch & 128) {
                strcat(res,"1");
//                res[l]='1';
//                res[l+1]='\0';
//                l++;
            }
            else{
                strcat(res,"0");
//                res[l]='0';
//                res[l+1]='\0';
//                l++;
            }
//            else{
//                printf("致命错误！！");
//                exit(0);
//            }
            for (int i = 1; i <= n; i++) {
//                int s=0;
//                while(res[s]!='\0'&&tnode[i].code[s]!='\0'&&res[s]==tnode[i].code[s])
//                    s++;
//                if(res[s]=='\0'&&tnode[i].code[s]=='\0'){
//                    fprintf(fp2,"%c",tnode[i].data);
////                    fwrite((char *)tnode[i].data,sizeof(char),1,fp2);//写入
//                    for(int u=0;u<20;u++)
//                        res[u]='\0';
//                    break;
//                }
                if (strcmp(res,tnode[i].code)==0) {
                    fprintf(fp2,"%c",tnode[i].data);      //写入
                    res[0]='\0';
                    break;
                }
            }
            ch = ch << 1; //左移一位
        }
        ch=(unsigned char)fgetc(fp1);
    }
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    printf("		\n\n	解压缩成功！ \n\n\n");
}
void HuffmanImformation(int n,double *w,char *content,HuffmanCode HC)
{
    printf("		字符			权值				哈夫曼编码		\n");
    for (int i = 1; i <= n; i++)
    {
        if (content[i]=='\n')
            printf("		回车		", content[i]);
        else if(content[i]==' ')
            printf("		空格		", content[i]);
        else if (content[i] == '	')
            printf("		制表		", content[i]);
        else
            printf("		%c		", content[i]);
        printf("	%lf		", w[i]);
        printf("	%s		\n", HC[i]);
    }
    puts("\n\n\n");
}

void PrintTree(int pos, HuffmanTree HT)
{//打印哈夫曼树HT
    printf("\n\n << ===================哈夫曼树图形化=================== >>  \n\n");
    printf("\n\n 0代表实际不存在的叶子，由于屏幕有限，暂时不支持太大的哈夫曼树显示  \n\n");
    int e;            //临时接收出队列的元素
    int level=1;
    int level1=level;
    LinkQueue Q;             //建立工作队列
    InitQueue(Q);           //初始化队列Q
    EnQueue(Q, pos,1);          //哈夫曼树树根位置入队列
    while (!QueueEmpty(Q))    //队列非空
    {
        DeQueue(Q, e,level);    //对头元素出队列
        if (e == 0)
        {
            if (level == level1)
                printf(" 0    ");
            else
                printf("\n0    ");
            level1 = level;
            continue;
        }

        else if (level == level1)
        {
            printf(" %.3f", HT[e].weight);
        }
        else
        {
            printf("\n%.3f", HT[e].weight);
        }
        level1 = level;
        EnQueue(Q, HT[e].lchild, level + 1);
        EnQueue(Q, HT[e].rchild, level + 1);
    }
    puts("\n\n\n\n");


/*━━━━━━━━━━━━━━━━━━━━━━ 图形化输出 ━━━━━━━━━━━━━━━━━━━━━━

// 以图形化形式输出当前结构，仅限内部测试使用
        int tlevel, width;
        int i, j, k, w;
        int begin;
        int distance;
        char** tmp;
        LinkQueue Q;
        InitQueue(Q);           //初始化队列Q
        HuffmanTree e;
        HuffmanTree pmt=HT;
        // 遇到空树则无需继续计算
        if(HT->lchild==NULL&&HT->rchild==NULL){
            printf("\n");
            return;
        }
        while(pmt->lchild != nullptr) {   // （完全）二叉树结构高度
            tlevel++;
            pmt=pmt->lchild;
        }

        width = (int)pow(2, tlevel)-1;   // （完全）二叉树结构宽度

        // 动态创建行
        tmp = (char **)malloc(tlevel* sizeof(char *));

        // 动态创建列
        for(i = 0; i < tlevel; i++) {
            tmp[i] = (char*)malloc(width* sizeof(char));

            // 初始化内存值为空字符
            for(int s=1;s<width;s++) {
                tmp[i][s] = '\0';
            }
        }

        // 借助队列实现层序遍历
        InitQueue(&Q);
        EnQueue(&Q, T);

        // 遍历树中所有元素，将其安排到二维数组tmp中合适的位置
        for(i = 0; i < tlevel; i++) {
            w        = (int) pow(2, i);             // 二叉树当前层的宽度
            distance = width / w;                   // 二叉树当前层的元素间隔
            begin    = width / (int) pow(2, i + 1); // 二叉树当前层首个元素之前的空格数

            for(k = 0; k < w; k++) {
                DeQueue(&Q, &e);

                if(e == NULL) {
                    EnQueue(&Q, NULL);
                    EnQueue(&Q, NULL);
                } else {
                    j = begin + k * (1 + distance);
                    tmp[i][j] = e->data;

                    // 左孩子入队
                    EnQueue(&Q, e->lchild);

                    // 右孩子入队
                    EnQueue(&Q, e->rchild);
                }
            }
        }

        for(i = 0; i < tlevel; i++) {
            for(j = 0; j < width; j++) {
                if(tmp[i][j] != '\0') {
                    printf("%c", tmp[i][j]);
                } else {
                    printf(" ");
                }
            }
            printf("\n");
        }
    }*/
}

void CompressTxt(void)
{

    postion2:printf("请输入你要进行压缩的文件 ：");
    char source[100];
    scanf("%s",source);
    while(getchar()!='\n') continue;
    printf("请输入对应的编码表文件 ：");
    char tablename[100];
    scanf("%s",tablename);
    while(getchar()!='\n') continue;
    printf("请输入压缩到哪个文件 ：");
    char des[100];
    scanf("%s",des);
    while(getchar()!='\n') continue;
    FILE *fp1;           //fp1指向源文件
    FILE *fp2;           //fp1指向目标文件
    FILE *fp3;           //fp1指向编码表
    if ((fp1 = fopen(source, "rt")) == NULL)
    {//错误处理
        printf("不能打开你指定的源文件，请重新输入。\n");
        goto postion2;
    }
    if ((fp3 = fopen(tablename, "rb")) == NULL)
    {//错误处理
        printf("不能打开你指定的编码表文件，请重新输入。\n");
        goto postion2;
    }
    if ((fp2 = fopen(des, "wb")) == NULL)
    {//错误处理
        printf("不能打开你指定的目标文件，请重新输入。\n");
        goto postion2;
    }
    fseek(fp3,0,SEEK_END);
    int n =ftell(fp3)/sizeof(Node)-1;
    fseek(fp3,0,SEEK_SET);

    Node tnode[n+1];
    for(int i=0;i<=n;i++) {

        fread(tnode+i, sizeof(Node) , 1, fp3);

    }
    fclose(fp3);
    //以二进制形式写入编码结果
    char ch;
    unsigned char buff = NULL; //临时存储
    int bitLen = 0;
    ch=fgetc(fp1);
    while (ch!=EOF) {
        for (int i = 1; i <= n; i++) {
            if (ch == tnode[i].data) {
                for (int j = 0; j < strlen(tnode[i].code); j++) {

                    buff = buff << 1; //左移1位

                    if (tnode[i].code[j] == '0')
                        buff = buff | 0;  //或运算
                    else
                        buff = buff | 1;

                    bitLen++;
                    if (bitLen == 8) {    //八位凑够一个字节写入文件
                        fwrite((char *) &buff,sizeof(buff), 1,fp2);
                        bitLen = 0;
                        buff = NULL;
                    }
                }
            }
        }
        ch=fgetc(fp1);
    }
    for (int i = 0; i < 8 - bitLen; i++) {
        buff = buff << 1; //左移1位
    }
    fwrite((unsigned char *) &buff,sizeof(unsigned char), 1,fp2);

//    char p;          //临时存放文件里的每一个字符
//    p = fgetc(fp1);
//    int pos;              //用于定位
//    unsigned char buff = NULL; //临时存储
//    char buffer[100000000]="";
//    int bitLen = 0;
//    while (p != EOF)
//    {//循环读取文件每一个字符直到遇到文件终止符EOF
//        pos = searchtable(p, tnode, n);       //从n个叶子中找到p字符
//        if (pos == 0)
//        {//该字符并没有与之对应的哈夫曼编码
//            printf("指定压缩文件有当前哈夫曼树不支持的字符,请重新选择一个支持的文件： \n");
//            goto postion4;
//        }
//        //以二进制形式写入编码结果
//        strcat(buffer,tnode[pos].code);
//        p = fgetc(fp1);         //接着读取下一个字符
//    }
//    for(int i=0;i<strlen(buffer);i++){
//        buff = buff << 1; //左移1位
//        if(buffer[i]='0'){
//            buff = buff | 0;  //或运算
//        }
//        else if(buffer[i]='1'){
//            buff = buff | 1;
//        }
//        else{
//            printf("致命错误！\n");
//            exit(0);
//        }
//        bitLen++;
//        if (bitLen == 8) {    //八位凑够一个字节写入文件
//            fwrite((char *) &buff, sizeof(buff), 1, fp2);
//            bitLen = 0;
//            buff = NULL;
//        }
//    }
//    for (int i = 0; i < 8 - bitLen; i++) {
//        buff = buff << 1; //左移1位
//    }
//    fwrite((char *) &buff, sizeof(buff), 1, fp2);
    fclose(fp1);                        //关闭文件
    fclose(fp2);
    printf("\n文件压缩完成\n\n\n");
}

void showmuch(void){
    postion2:printf("请输入源文件的路径名 ：");
    char source[100];
    scanf("%s",source);
    while(getchar()!='\n') continue;
    printf("请输入压缩文件的路径名 ：");
    char des[100];
    scanf("%s",des);
    while(getchar()!='\n') continue;
    FILE *fp1;           //fp1指向源文件
    FILE *fp2;           //fp1指向目标文件
    if ((fp1 = fopen(source, "rt")) == nullptr)
    {//错误处理
        printf("不能打开你指定的源文件，请重新输入。\n");
        goto postion2;
    }
    if ((fp2 = fopen(des, "rt")) == nullptr)
    {//错误处理
        printf("不能打开你指定的压缩文件，请重新输入。\n");
        goto postion2;
    }
    int a1,a2;
    fseek(fp1,0,SEEK_END);
    a1=ftell(fp1);
    fclose(fp1);
    fseek(fp2,0,SEEK_END);
    a2=ftell(fp2);
    fclose(fp2);
    printf("压缩程度为%lf\n",((float)a2)/((float)a1));
}
void Select(HuffmanTree HF, int i, int &s1, int &s2)    //从HF数组的第一号结点到第i号结点中选出parent为0，且weight最小的两个结点的下标，记录在s1,s2中
{
    double min1 = 100;           //min1存放最小权重，初始值给一个大于1的值
    double min2 = 99;            //min2存放次小权重
    int minnum1 = 1;             //临时存放最小下标
    int minnum2 = 2;             //临时存放次小下标
    double temp_weight;
    int temp_num;
    for (int j = 1; j <= i; j++)
    {
        if (HF[j].parent == 0 && HF[j].weight < min2)
        {
            min2 = HF[j].weight;
            minnum2 = j;
        }
        if (min2 < min1)
        {
            temp_weight = min1;
            min1 = min2;
            min2 = temp_weight;

            temp_num = minnum1;
            minnum1 = minnum2;
            minnum2 = temp_num;
        }
    }
    s1 = minnum1;
    s2 = minnum2;
    /*double min = 100;           //min存放最小权重，初始值给一个大于1的值
    int minnum=1;             //临时存放最小下标
    for (int j = 1; j <= i; j++)         //找出第一个权值最小的结点
    {
    if (HF[j].parent == 0 && HF[j].weight < min)
    {
    min = HF[j].weight;
    minnum = j;;
    }
    }
    s1 = minnum;
    min = 100;
    minnum = 2;
    for (int j = 1; j <= i; j++)          //找出第二个权值最小的结点
    {
    if (HF[j].parent == 0 && HF[j].weight < min&&j != s1)
    {
    min = HF[j].weight;
    minnum = j;
    }
    }
    s2 = minnum;*/
}

int search(char p, char *content, int ptr)                   //在content数组1号到ptr位置里面找是否有字符p，无则返回0，有则返回位置
{
    for (int i = 1; i <= ptr; i++)
    {
        if (content[i] == p)
            return i;
    }
    return 0;
}
//int searchtable(char p, Node *tnode, int ptr)                   //在content数组1号到ptr位置里面找是否有字符p，无则返回0，有则返回位置
//{
//
//    for (int i = 1; i <= ptr; i++)
//    {
//        if (tnode[i].data == p)
//            return i;
//    }
//    return 0;
//}

void count(double *&w, int &n, char *&content)                         //统计指定文本各个字符出现的概率,字符和概率分别按顺序存在数组w和content中
{
    w = (double *)malloc(200 * sizeof(double));              //给w，content分配存储空间,0号位置不用，200足够
    for (int i = 1; i < 200; i++)  //初始化
        w[i] = 200;
    content = (char *)malloc(300* sizeof(char));

    int ptr = 1;                               //标记content末端下标
    char p;                                   //临时存放每一个字符
    int total = 0;                        //统计总共输入多少个字符
    int pos;                             //存放重复字符插入到哪一个位置
    char FileName[200];                   //存放文件名
    postion1:printf(" 请输入你要读取字符建立哈夫曼树的txt文件 ： ");

    scanf("%s",FileName);
    while(getchar()!='\n') continue;

    FILE *fp;           //fp为文件指针
    if ((fp = fopen(FileName, "r")) == nullptr)
    {//错误处理
        printf(" 不能打开你指定的文件，请重新输入!\n\n");
        goto postion1;                   //重新输入直到用户输入正确的路径
    }
    p = fgetc(fp);
    if (p < -1 || p >255)
    {
        printf("含有中文字符，暂不支持中文！请重新选择文件 \n");
        goto postion1;
    }
    while (p != EOF)
    {//循环读取文件每一个字符直到遇到文件终止符EOF
        ++total;      //字符总数加1
        if (search(p, content, ptr) == 0)
        {//在当前content已经存储的字符中没有p（p是一个新的字符)
            content[ptr] = p;      //在content末端插入p
            w[ptr] = 1;
            ++ptr;            //末端位置后移
        }
        else
        {//是一个之前已经读取的字符
            pos = search(p, content, ptr);   //找到p字符的位置pos
            ++w[pos];
        }
        p = fgetc(fp);       //接着往后读取
        if (p < -1 || p >255)
        {
            printf(" 含有中文字符，暂不支持中文！请重新选择文件 \n");
            goto postion1;
        }
    }

    for (int i = 1; i < ptr; i++)          //数量转化为概率
        w[i] = w[i] / total;

    n = ptr - 1;                       //叶子数


    fclose(fp);                        //关闭文件
}
