#define RINGHT 1
#define ERROR 0
#define EMPTRY -1
#define FULL -2
#define N 2
#define PRICE 5
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
// 定义停车场节点
typedef struct StackNode {
    int plateNumber;
    int arrivalTime;
} StackNode;

// 定义停车场栈
typedef struct ParkingStack {
    StackNode* cars;  // 存储停车场的数组
    int top;                // 栈顶指针，采用这种形式我觉得比原来双指针的模式方便很多，主要表现在-1为初始化，加一为序号，再加1为个数，而且方便统计个数
    int capacity;           // 停车场容量
} ParkingStack;
// 初始化停车场
void initParkingStack(ParkingStack* stack, int capacity) {
    stack->cars = (StackNode*)malloc(capacity * sizeof(StackNode));
    stack->top = -1;
    stack->capacity = capacity;
}
// 停车场栈是否为空
int StackEmpty(ParkingStack* stack) {
    return stack->top == -1;//如果为头指针为-1，则返回真
}
// 停车场栈是否已满
int StackFull(ParkingStack* stack) {
    return stack->top == stack->capacity - 1;
}
// 停车场栈入栈
void push(ParkingStack* stack, int plateNumber, int arrivalTime) {
    if (StackFull(stack)) {
        printf("停车场已满，无法停车。\n");
        return;
    }

    stack->top++;
    stack->cars[stack->top].plateNumber = plateNumber;
    stack->cars[stack->top].arrivalTime = arrivalTime;

    printf("车辆 %d 进入停车场，停车位置为 %d。\n", plateNumber, stack->top + 1);
}
//停车场出栈
int pop(ParkingStack* stack) {
    if (StackEmpty(stack)) {
        printf("停车场已空，无车辆可离开。\n");
        return -1;
    }
    int value = stack->cars[stack->top].plateNumber;
    stack->top--;
    return value;
}
void printStack(ParkingStack* stack) {
    if (StackEmpty(stack)) {
        printf("停车场已空\n");
        return;
    }

    else {
        int x = stack->top;
        printf("停车场布局:");
        while (x > -1) {
            printf(" %d ", stack->cars[x].plateNumber);
            /*stack->top--*/

            x--;//因为传进去动态指针，所以stack->top--，后续的top就都改变了
        }
        return;
    }
}

// 停车场中是否存在指定车牌号的车辆
int isCarInParkingStack(ParkingStack* stack, int licensePlate) {
    for (int i = 0; i <= stack->top; i++) {
        if (stack->cars[i].plateNumber == licensePlate) {
            return i;
        }
    }
    return -1;
}
// 定义便道队列节点
typedef struct QueueNode {
    int plateNumber;
    int arrivalTime;
    struct QueueNode* next;
} QueueNode;

// 定义便道队列
typedef struct WaitingQueue {
    QueueNode* front;
    QueueNode* rear;
} WaitingQueue;
// 初始化便道队列
void initWaitingQueue(WaitingQueue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

// 便道队列是否为空
int QueueEmpty(WaitingQueue* queue) {
    return queue->front == NULL;
}
// 入队到便道
void enqueue(WaitingQueue* queue, int plateNumber, int arrivalTime) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->plateNumber = plateNumber;
    newNode->arrivalTime = arrivalTime;
    newNode->next = NULL;

    if (QueueEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    }
    else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    printf("车辆%d进入便道。\n", plateNumber);

}
int dequeue(WaitingQueue* queue) {
    if (QueueEmpty(queue)) {
        printf("队列为空，无法进行出队操作。\n");
        return 0;
    }


    int value = queue->front->plateNumber;
    QueueNode* temp = queue->front;
    queue->front = queue->front->next;
    free(temp);

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    return value;
}
void printQueue(WaitingQueue* queue) {
    if (queue->front == NULL) {
        printf("队列为空\n");
        return;
    }
    printf("队列中布局：");
    QueueNode* current = queue->front;
    while (current != NULL) {
        printf("%d ", current->plateNumber);
        current = current->next;
    }
    printf("\n");
}
// 操作菜单
void displayMenu() {
    printf("操作菜单\n");
    printf("车辆到达请输入A\n");
    printf("车辆离开请输入D\n");
    printf("退出请输入E\n");
}
void destroyParkingStack(ParkingStack* stack) {
    free(stack->cars);
}

int main() {
    ParkingStack parkingstack;
    initParkingStack(&parkingstack, N);
    ParkingStack parkingstack_tmp;

    initParkingStack(&parkingstack_tmp, N);

    WaitingQueue waitingqueue;
    initWaitingQueue(&waitingqueue);


    char operation[2];
    int licensePlate;
    int time;
    int stayingtime;
    while (1) {
        displayMenu();
        printf("请输入操作编号：");
        scanf("%s", &operation);

        if (strcmp(operation, "A") == 0) { // 车辆到达
            printf("请输入车牌号码：");
            scanf("%d", &licensePlate);
            while (isCarInParkingStack(&parkingstack, licensePlate) != -1) {
                printf("输入不合法，车子已在停车场\n");
                printf("请输入车牌号码：");
                scanf("%d", &licensePlate);
            }
            printf("请输入到达时间：");
            scanf("%d", &time);
            while (time < parkingstack.cars[parkingstack.top].arrivalTime) {
                printf("输入不合法，请重新输入到达时间：");
                scanf("%d", &time);
            }




            if (StackFull(&parkingstack)) {
                enqueue(&waitingqueue, licensePlate, 0);
            }
            else {
                push(&parkingstack, licensePlate, time);
            }
            printStack(&parkingstack);
            printQueue(&waitingqueue);
        }
        else if (strcmp(operation, "D") == 0) { // 车辆离开
            printf("请输入车牌号码：");
            scanf("%d", &licensePlate);
            printf("请输入离开时间：");
            scanf("%d", &time);

            if (isCarInParkingStack(&parkingstack, licensePlate) != -1) {
                while (parkingstack.top - isCarInParkingStack(&parkingstack, licensePlate) > 0) {
                    push(&parkingstack_tmp, pop(&parkingstack), 0);
                    // parkingstack->top--;自减已经在pop内有定义了

                }
                stayingtime = time - parkingstack.cars[parkingstack.top].arrivalTime;
                printf("车辆%d已经离开停车场，停留时间为%d,需要缴费%d元\n", licensePlate, stayingtime, stayingtime * PRICE);
                pop(&parkingstack);

                while (parkingstack_tmp.top >= 0) {
                    push(&parkingstack, pop(&parkingstack_tmp), 0);

                }
                if (QueueEmpty(&waitingqueue)) {
                    printf("便道上没有车,所以后续没有车进入停车场");
                }
                else {
                    /* printf("请输入便道上第一辆车的进入时间：");
                     scanf("%d", &time);*/
                    push(&parkingstack, dequeue(&waitingqueue), time);//上一辆车离开就是你进去的时间
                }
            }
            else {

                printf("停车场中不存在车牌号为 %d 的车辆。\n", licensePlate);
            }
            printStack(&parkingstack);
            printQueue(&waitingqueue);
        }
        else if (strcmp(operation, "E") == 0) { // 退出
            /* free(&parkingstack.cars);
             free(&parkingstack_tmp.cars);
             free(&waitingqueue);*///自己产生自己销毁，不用重复free
            destroyParkingStack(&parkingstack);
            destroyParkingStack(&parkingstack_tmp);//其实这里多余了，因为那啥，它会自动删除的
            printf("退出ing！\n");
            break;
        }
        else {
            printf("无效操作，请重新输入。\n");
        }
    }

    return 0;
}















//int main() {
//    ParkingStack* parkingstack ;
//    initParkingStack(parkingstack, N);
//    ParkingStack* parkingstack_tmp ;
//    
//    initParkingStack(parkingstack_tmp, N);
//
//    WaitingQueue* waitingqueue ;
//    initWaitingQueue(waitingqueue);
//
//
//    char operation[2];
//    int licensePlate;
//    int time;
//    while (1) {
//        displayMenu();
//        printf("请输入操作编号：");
//        scanf("%s", &operation);
//
//        if (strcmp(operation, "A") == 0) { // 车辆到达
//            printf("请输入车牌号码：");
//            scanf("%d", &licensePlate);
//            printf("请输入到达时间：");
//            scanf("%d", &time);
//
//
//
//            if (StackFull(parkingstack)) {
//                enqueue(waitingqueue, licensePlate, 0);
//            }
//            else {
//                push(parkingstack, licensePlate, time);
//            }
//        }
//        else if (strcmp(operation, "D") == 0) { // 车辆离开
//            printf("请输入车牌号码：");
//            scanf("%d", &licensePlate);
//            printf("请输入离开时间：");
//            scanf("%d", &time);
//
//            if (isCarInParkingStack(parkingstack, licensePlate) != -1) {
//                while (parkingstack->top - isCarInParkingStack(parkingstack, licensePlate) > 0) {
//                    push(parkingstack_tmp, pop(parkingstack), 0);
//                    // parkingstack->top--;自减已经在pop内有定义了
//
//                }
//                pop(parkingstack);
//                while (parkingstack_tmp->top >= 0) {
//                    push(parkingstack, pop(parkingstack_tmp), 0);
//                }
//                if (QueueEmpty(waitingqueue)) {
//
//                }
//                else {
//                    printf("请输入便道上第一辆车的进入时间：");
//                    scanf("%d", &time);
//                    push(parkingstack, dequeue(waitingqueue), time);
//                }
//            }
//            else {
//
//                printf("停车场中不存在车牌号为 %d 的车辆。\n", licensePlate);
//            }
//        }
//        else if (strcmp(operation, "E") == 0) { // 退出
//            free(parkingstack);
//            free(parkingstack_tmp);
//            free(waitingqueue);
//            printf("退出ing！\n");
//            break;
//        }
//        else {
//            printf("无效操作，请重新输入。\n");
//        }
//    }
//
//    return 0;
//}