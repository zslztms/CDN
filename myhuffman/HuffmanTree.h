//
// Created by wxxxx on 2020/11/17.
//
//哈夫曼树结构的定义和相关操作函数
#ifndef HUFFMANTREE
#define HUFFMANTREE

typedef struct                //结点的定义  ,HTNode为结点类型，HuffmanTree为指向此类结点的指针类型
{
    double weight;           //权重（概率）
    unsigned int parent, lchild, rchild;   //双亲和左右孩子的下标
}HTNode, *HuffmanTree;

typedef struct           //叶子单独具有的属性定义，除了权值外，还有代表的字符和二进制码
{
    char data;         //代表的字符
    char code[20];        //以code开头的字符串表示该叶子结点的编码
}Node;

typedef char ** HuffmanCode;                                         //二维字符指针类型后面用Huffmancode表示
extern void HuffmanImformation(int n, double *w, char *content, HuffmanCode HC);    //显示哈夫曼树详细信息
extern void PrintTree(int pos, HuffmanTree HT);                                     //打印哈夫曼树的大致样子
extern void CompressTxt(void);              //压缩文件
extern void showmuch(void);
extern void HuffmanCoding(HuffmanTree HT, HuffmanCode &HC, int n);   //哈夫曼编码函数
extern void HuffmanDecoding(void);   //哈夫曼解码
extern void CreatHuffman(HuffmanTree &HT, double *w, int n);          //创建一个哈夫曼树
extern void CreatTable(HuffmanTree &HT,int n,char *content,HuffmanCode &HC);          //创建一个哈夫曼树
void Select(HuffmanTree HF, int i, int &s1, int &s2);    //在第一个结点到第i个结点中选出parent为0，且weight最小的两个节点，下标为s1,s2
int search(char p, char *content, int ptr);             //搜索content数组1号到ptr号是否有字符p，无返回0，有返回下标
void count(double *&w, int &n, char *&content);         //统计文本的所有字符的概率
//int searchtable(char p, Node *tnode, int n);       //从n个叶子中找到p字符
#endif // !HUFFMANTREE


