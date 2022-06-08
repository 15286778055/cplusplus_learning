#ifndef _QUEUE
#define _QUEUE

#include <stdlib.h>

/* Linked list element */
typedef struct list_ele {
    char *value;
    struct list_ele *next;
    struct list_ele *pre;
} list_ele_t;

/* Queue structure */
typedef struct {
    list_ele_t *head; /* First element in the queue */
    list_ele_t *tail; /* Last element in the queue */
    unsigned int size;
} queue_t;



/* 定义需要实现的函数 */

/**
 * @brief Create a new, empty queue.
 * 
 * @return queue_t* 
 */
queue_t *queue_new();

/**
 * @brief Free all storage used by a queue.
 * 
 */
void queue_free(queue_t *myQueue);

/**
 * @brief Attempt to insert a new element at the head of the queue (LIFO discipline).
 * 
 */
void queue_insert_head(queue_t *myQueue, char *addHead);

/**
 * @brief Construct a new queue insert tail objectAttempt to insert a new element at the tail of the queue (FIFO discipline).
 * 
 */
void queue_insert_tail(queue_t *myQueue, char *addTail);

/**
 * @brief Attempt to remove the element at the head of the queue.
 * 
 */
list_ele_t *queue_remove_head(queue_t *myQueue);

/**
 * @brief Compute the number of elements in the queue.
 * 
 * @return unsigned int 
 */
unsigned int queue_size(queue_t *myQueue);


/**
 * @brief Reorder the list so that the queue elements are reversed in order. This function should not 
 * allocate or free any list elements (either directly or via calls to other functions that allocate or free list 
 * elements.) Instead, it should rearrange the existing elements.
 * 
 */
void queue_reverse(queue_t *myQueue);

/**
 * @brief Create a node object
 * 
 * @param str 
 * @return list_ele_t* 
 */
list_ele_t *create_node(char *str);


#endif