#include <stdio.h>
#include <string.h>
#include "queue.h"


/**
 * @brief Create a new, empty queue.
 * An empty queue is one pointing to a valid structure, but the head field has value NULL.
 * A NULL queue is one for which the pointer has value NULL
 * 
 */
queue_t *queue_new() {
    // calloc 将分配的内存空间初始化为 0
    queue_t *newQueue = (queue_t *) calloc(1, sizeof(queue_t));
    return newQueue;
}

/**
 * @brief Free all storage used by a queue.
 * 
 * @return queue_t* 
 */
void queue_free(queue_t *myQueue) {
    // 1 释放链条
    while (myQueue->head != NULL) {
        list_ele_t *diminish = queue_remove_head(myQueue);
        free(diminish->value);
        free(diminish);
    }

    // 2 释放 queue 头
    free(myQueue);
    myQueue->head = NULL;
    myQueue->tail = NULL;

    myQueue = NULL;
}

/**
 * @brief Attempt to insert a new element at the head of the queue (LIFO discipline).
 * 
 * @param myQueue 
 * @param addHead 
 */
void queue_insert_head(queue_t *myQueue, char *addHead) {
    // 1 新建节点
    list_ele_t *newNode = create_node(addHead);
    
    // 2 链入节点
    if (myQueue->head == NULL) {
        myQueue->head = myQueue->tail = newNode;
    } else {
        newNode->next = myQueue->head;
        myQueue->head->pre = newNode;
        myQueue->head = newNode;    
    }
    ++myQueue->size;
}

/**
 * @brief Construct a new queue insert tail objectAttempt to insert a new element at the tail of the queue (FIFO discipline).
 * 
 * @param myQueue 
 * @param addTail 
 */
void queue_insert_tail(queue_t *myQueue, char *addTail) {
    // 1 新建节点
    list_ele_t *newNode = create_node(addTail);
    
    // 2 链入节点
    if (myQueue->tail == NULL) {
        myQueue->head = myQueue->tail = newNode;
    } else {
        newNode->pre = myQueue->tail;
        myQueue->tail->next = newNode;
        myQueue->tail = newNode;
    }
    ++myQueue->size;
}

/**
 * @brief Attempt to remove the element at the head of the queue.
 * 
 */
list_ele_t *queue_remove_head(queue_t *myQueue) {
    // 头节点为 NULL，直接返回
    if (myQueue->head == NULL) return NULL;
    // 头节点非空，需要 free
    list_ele_t *diminish = NULL;
    if (myQueue->head->next != NULL) {
        diminish = myQueue->head;
        myQueue->head->next->pre = NULL;
        myQueue->head = myQueue->head->next;
    } else {
        diminish = myQueue->head;
        myQueue->head = NULL;  // 需要置为 NULL, 否则下次判断为 非NULL，将再次 free
        myQueue->tail = NULL;
    }
    --(myQueue->size);
    return diminish;
}

/**
 * @brief Compute the number of elements in the queue.
 * 
 * @return unsigned int 
 */
unsigned int queue_size(queue_t *myQueue) {
    return myQueue->size;
}


/**
 * @brief Reorder the list so that the queue elements are reversed in order. This function should not 
 * allocate or free any list elements (either directly or via calls to other functions that allocate or free list 
 * elements.) Instead, it should rearrange the existing elements.
 * 
 */
void queue_reverse(queue_t *myQueue) {
    if (myQueue->size == 0 || myQueue->size == 1) return;

    // 实现为双向链表，直接交换头尾指针，即可实现 Reverse ---------------- 这么做不行 因为pre和next指针名不一样，需要改变访问规则才可
    // 除了交换头尾指针，还需要交换 pre next指针
    // 1 先以此 交换 pre next 指针
    list_ele_t *item = myQueue->head;
    list_ele_t *temp = item->next;
    item->next = item->pre;
    item->pre = temp;
    while (item->pre != NULL) {
        item = item->pre;
        list_ele_t *temp = item->next;
        item->next = item->pre;
        item->pre = temp;
    }

    // 2 再交换头尾指针
    list_ele_t *front = myQueue->head;
    myQueue->head = myQueue->tail;
    myQueue->tail = front;
}

/**
 * @brief Create a node object
 * 
 * @param str 
 * @return list_ele_t* 
 */
list_ele_t *create_node(char *str) {
    list_ele_t *newNode = (list_ele_t *) calloc(1, sizeof(list_ele_t));
    newNode->value = (char *) calloc(strlen(str)+1, sizeof(char));
    // 方案一：不使用 str 指针 外部需要释放
    // strcpy(newNode->value, str);
    // 方案二：直接使用这根指针
    newNode->value = str;
    return newNode;
}


int main() {

    queue_t *my_queue = queue_new();
    
    char *s1 = "我是头";
    char *s2 = "我是中";
    char *s3 = "我是尾";

    char *head = (char *) calloc(1, strlen(s1)+1);
    strcpy(head, s1);
    char *zhong = (char *) calloc(1, strlen(s2)+1);
    strcpy(zhong, s2);
    char *tail = (char *) calloc(1, strlen(s3)+1);
    strcpy(tail, s3);
    
    
    // insert
    queue_insert_tail(my_queue, head);
    printf("size: %u\n", my_queue->size);
    queue_insert_tail(my_queue, zhong);
    printf("size: %u\n", my_queue->size);
    queue_insert_tail(my_queue, tail);
    printf("size: %u\n", my_queue->size);


    // reverse
    // queue_reverse(my_queue);
    
    // 测试释放头部
    // list_ele_t *diminish = queue_remove_head(my_queue);
    // printf("value: %s\n", diminish->value);
    // free(diminish->value);
    // free(diminish);

    // diminish = queue_remove_head(my_queue);
    // printf("value: %s\n", diminish->value);
    // free(diminish->value);
    // free(diminish);
    
    // diminish = queue_remove_head(my_queue);
    // printf("value: %s\n", diminish->value);
    // free(diminish->value);
    // free(diminish);
    
    
    // free整个
    // queue_free(my_queue);


    // size
    printf("size: %u\n", queue_size(my_queue));


    // print
    if (my_queue == NULL) return 0;
    list_ele_t *to_print = my_queue->head;

    if (to_print == NULL) return 0;
    printf("head value: %s\n", to_print->value);
    while (to_print->next != NULL) {
        to_print = to_print->next;
        printf("value: %s\n", to_print->value);
    }

    


    return 0;
}