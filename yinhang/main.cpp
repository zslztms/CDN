#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdint.h>
typedef int ElemType;
enum is_vip_or_not{is_vip,not_vip};
typedef struct {
    int arrival;      // 客户到达银行的时间
    int service_time; // 客户办理业务所需时间
    is_vip_or_not _vip;
} customer;
enum status {idle, busy};
typedef struct {
    status cur_status;  // 窗口当前状态：忙or闲
    int cur_start_time; // 当前状态开始的时间
    int cur_customer;   // 当前服务客户的编号（如果在忙）
} window;
typedef struct {
    ElemType *elem; // 基地址
    int queuesize;  // 当前分配内存大小
    int front, rear;
} SqQueue;
void EnQueue_sq(SqQueue &Q, ElemType e) {
    Q.elem[Q.rear] = e; Q.rear = Q.rear+1;
}
bool DeQueue_sq(SqQueue &Q, ElemType *e) {
    if (Q.front == Q.rear) return false;
    *e = Q.elem[Q.front]; Q.front = Q.front+1;
    return true;
}
int QueueLength_sq(SqQueue Q) {
    return Q.rear - Q.front ;
}
void print_menu(void){
    printf("====银行模拟系统====\n");
    printf("1.简易银行模拟系统  2.普通银行模拟系统\n");
    printf("3.退出系统\n");
}
void bank_simulation(int nc, customer *cust, int nw, window *win,int all_open_time) {
    int t = 0;
    int c, w;
    int idw = nw;
    int acc;
    long int all_wait_time=0;
    long int all_use_time=0;
    printf("Bank open now\n" );
    SqQueue Q;
    Q.elem=(ElemType*)malloc( nc*sizeof(ElemType));
    Q.queuesize=nc;
    Q.front=0;
    Q.rear=0;

    for(acc=0;acc<nw;acc++)
        win[acc].cur_status=idle;
     // 所有窗口状态初始化为idle
    while (t <= all_open_time || QueueLength_sq(Q) > 0 || idw < nw) {
        if (t <= all_open_time)
            for (c=0; c<nc; ++c)
                if (cust[c].arrival == t) {
                    EnQueue_sq(Q, c);
                    printf("%d号客户于%d时间进入队列\n", c, t);
                }
        for (w=0; w<nw; w++)
            if (win[w].cur_status == busy) {
                c = win[w].cur_customer;
                if ((t - win[w].cur_start_time) >= cust[c].service_time) {
                    win[w].cur_status = idle;
                    printf("%d号客户于%d时间在%d号窗口服务结束\n",c,t,w);
                    win[w].cur_start_time = t;
                    idw++;
                }
            }
        for (w=nw-1; w>=0; w--) {
            if (win[w].cur_status == idle && QueueLength_sq(Q) > 0) {
                DeQueue_sq(Q, &c);
                printf("%d号客户于%d时间在%d号窗口接受服务\n",c,t,w);
                all_wait_time =all_wait_time - cust[c].arrival + t;
                idw--;
                win[w].cur_customer=c;
                win[w].cur_status = busy; // 将窗口状态改为busy
                win[w].cur_start_time = t;
                all_use_time =all_use_time + cust[c].service_time;
            }
        }
        t++;
    }
    printf("Bank close now\n");
    printf("客户平均等待时间为：%f\n",((float)all_wait_time)/nc);
    printf("窗口的平均占用率为：%f\n",((float)all_use_time)/(nw*t));
}
void bank_simulation_plus(int nc, customer *cust, int nw, window *win,int all_open_time,int max_stand_time,int number_of_vip) {
    int t = 0;
    int x = 0;
    int c, w;
    int idw = nw;
    int acc;
    long int all_wait_time=0;
    long int all_use_time=0;
    int number_of_leave=0;
    long int all_vip_wait_time=0;
    long int all_no_vip_wait_time=0;
    printf("Bank open now\n" );
    SqQueue Q;
    Q.elem=(ElemType*)malloc( nc*sizeof(ElemType));
    Q.queuesize=nc;
    Q.front=0;
    Q.rear=0;
    SqQueue VIPQ;
    VIPQ.elem=(ElemType*)malloc( nc*sizeof(ElemType));
    VIPQ.queuesize=nc;
    VIPQ.front=0;
    VIPQ.rear=0;
    for(acc=0;acc<nw;acc++)
        win[acc].cur_status=idle;
    // 所有窗口状态初始化为idle
    while (t <= all_open_time || QueueLength_sq(Q) > 0 ||QueueLength_sq(VIPQ) > 0 || idw < nw) {
        if (t <= all_open_time)
            for (c=0; c<nc; ++c)
                if (cust[c].arrival == t) {
                    if(cust[c]._vip==not_vip) {
                        EnQueue_sq(Q, c);
                        printf("%d号客户于%d时间进入队列\n", c, t);
                    }
                    else{
                        EnQueue_sq(VIPQ, c);
                        printf("%d号客户于%d时间进入VIP队列\n", c, t);
                    }
                }
        for (w=0; w<nw; w++)
            if (win[w].cur_status == busy) {
                c = win[w].cur_customer;
                if ((t - win[w].cur_start_time) >= cust[c].service_time) {
                    win[w].cur_status = idle;
                    printf("%d号客户于%d时间在%d号窗口服务结束\n",c,t,w);
                    win[w].cur_start_time = t;
                    idw++;
                }
            }
        for(x=Q.front;x<Q.rear;x++)
        {
            if(t-cust[Q.elem[x]].arrival>=max_stand_time) {
                DeQueue_sq(Q, &Q.elem[x]);
                printf("%d号客户等了%d分钟后离开了银行\n",Q.elem[x],max_stand_time);
                number_of_leave++;
                all_wait_time+=max_stand_time;
                all_no_vip_wait_time+=max_stand_time;
            }
        }
        for(x=VIPQ.front;x<VIPQ.rear;x++)
        {
            if(t-cust[VIPQ.elem[x]].arrival>=max_stand_time) {
                DeQueue_sq(VIPQ, &VIPQ.elem[x]);
                printf("%d号客户等了%d分钟后离开了银行\n",VIPQ.elem[x],max_stand_time);
                number_of_leave++;
                all_wait_time+=max_stand_time;
                all_vip_wait_time+=max_stand_time;
            }
        }
        for (w=nw-1; w>=0; w--) {
            if (win[w].cur_status == idle && QueueLength_sq(VIPQ) > 0) {
                DeQueue_sq(VIPQ, &c);
                printf("%d号客户于%d时间在%d号窗口接受VIP服务\n",c,t,w);
                all_wait_time =all_wait_time - cust[c].arrival + t;
                all_vip_wait_time = all_vip_wait_time -cust[c].arrival +t;
                idw--;
                win[w].cur_customer=c;
                win[w].cur_status = busy; // 将窗口状态改为busy
                win[w].cur_start_time = t;
                all_use_time =all_use_time + cust[c].service_time;
            }
            else if (win[w].cur_status == idle && QueueLength_sq(Q) > 0) {
                DeQueue_sq(Q, &c);
                printf("%d号客户于%d时间在%d号窗口接受服务\n",c,t,w);
                all_wait_time =all_wait_time - cust[c].arrival + t;
                all_no_vip_wait_time=all_no_vip_wait_time-cust[c].arrival + t;
                idw--;
                win[w].cur_customer = c;
                win[w].cur_status = busy; // 将窗口状态改为busy
                win[w].cur_start_time = t;
                all_use_time =all_use_time + cust[c].service_time;
            }
        }
        t++;
    }
    printf("Bank close now\n");
    printf("客户平均等待时间为：%f\n",((float)all_wait_time)/nc);
    printf("普通客户平均等待时间为：%f\n",((float)all_no_vip_wait_time)/(nc-number_of_vip));
    printf("VIP客户平均等待时间为：%f\n",((float)all_vip_wait_time)/number_of_vip);
    printf("窗口的平均占用率为：%f\n",((float)all_use_time)/(nw*t));
    printf("顾客的离开率为：%f\n",((float)number_of_leave)/nc);
}
int get_number(void){
    int i;
    while(scanf("%d",&i)!=1||(i<1||i>3)){
        printf("ERROR!请输入1~3的数字!请重新输入！\n");
        while(getchar()!='\n') continue;
    }
    return i;
}
int main(){
    customer cust[100000];
    window win[1000];
    int num_choice;
    int i;
    int all_open_time;
    int customer_number;
    int window_number;
    int customer_min_time;
    int customer_max_time;
    int max_stand_time;
    int number_of_vip;
    print_menu();
    while(1) {
        num_choice = get_number();
        switch (num_choice) {
            case 1:
                srand((unsigned) time(NULL));
                printf("请输入银行开门时长(单位为分钟):");
                scanf("%d", &all_open_time);
                printf("请输入预估客户数量：");
                scanf("%d", &customer_number);
                printf("请输入客户办理业务所需最少时间:");
                scanf("%d", &customer_min_time);
                printf("请输入客户办理业务所需最多时间:");
                scanf("%d", &customer_max_time);
                for (i = 0; i < customer_number; i++) {
                    cust[i].arrival = (int) rand() % all_open_time;
                    cust[i].service_time = (int) (rand() % (customer_max_time - customer_min_time + 1) + customer_min_time);
                }
                printf("请输入开通窗口数量：");
                scanf("%d", &window_number);
                bank_simulation(customer_number, cust, window_number, win, all_open_time);
                print_menu();
                break;
            case 2:
                srand((unsigned) time(NULL));
                printf("请输入银行开门时长(单位为分钟):");
                scanf("%d", &all_open_time);
                printf("请输入预估客户数量：");
                scanf("%d", &customer_number);
                printf("请输入客户办理业务所需最少时间:");
                scanf("%d", &customer_min_time);
                printf("请输入客户办理业务所需最多时间:");
                scanf("%d", &customer_max_time);
                printf("请输入客户最大容忍等待时间(若不需要请输入-1):");
                scanf("%d",&max_stand_time);
                if(max_stand_time<0)
                    max_stand_time=100*all_open_time;
                printf("请输入VIP客户的数量:");
                scanf("%d",&number_of_vip);
                for (i = 0; i < customer_number; i++) {
                    cust[i].arrival = (int) rand() % all_open_time;
                    cust[i].service_time = (int) (rand() % (customer_max_time - customer_min_time + 1) + customer_min_time);
                }
                for(i=0;i<number_of_vip;i++){
                    cust[i]._vip=is_vip;
                }
                for(i=number_of_vip;i<customer_number;i++){
                    cust[i]._vip=not_vip;
                }
                printf("请输入开通窗口数量：");
                scanf("%d", &window_number);
                bank_simulation_plus(customer_number, cust, window_number, win, all_open_time,max_stand_time,number_of_vip);
                print_menu();
                break;
            case 3:
                printf("Bye\n");
                exit(0);
        }
    }
}
