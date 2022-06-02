/*
 * @file cord.c
 * @brief Implementation of cords library
 *
 * 15-513 Introduction to Computer Systems
 *
 * TODO: fill in your name and Andrew ID below
 * @author XXX <XXX@andrew.cmu.edu>
 */

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "cord-interface.h"
#include "xalloc.h"

/***********************************/
/* Implementation (edit this part) */
/***********************************/

/**
 * @brief Checks if a cord is valid
 * @param[in] R
 * @return
 */
bool is_cord(const cord_t *R) {
    // 1 非 NULL
    if (R == NULL) return false;
    // 2 叶子节点
    if (R->left == NULL && R->right == NULL) {
        // data len 要求
        if (R->data == NULL) return false;
        if (R->len != strlen(R->data)) reurn false;
    }
    // 3 非叶子节点
    if (R->left != NULL && R->right != NULL) {
        // 递归判断左右两个叶子是否为合法 cord
        if (!is_cord(R->left)) return false;
        if (!is_cord(R->right)) return false;
        if (R->len != cord_length(R)) return false;
    }

    return true;
}

/**
 * @brief Returns the length of a cord
 * @param[in] R
 * @return
 */
size_t cord_length(const cord_t *R) {
    if (!is_cord(R)) return 0;
    return R->len;
//    if (R->right == NULL && R->left == NULL) return R->len;
//    if (R->right != NULL && R->left != NULL) return R->len + cord_length(R->right) + cord_length(R->left);
//
//    return 0;
}

/**
 * @brief Allocates a new cord from a string
 * @param[in] s
 * @return
 */
const cord_t *cord_new(const char *s) {
    cord_t *new_cord = (cord_t *)calloc(1, sizeof(cord_t));
    new_cord->data = s;
    new_cord->len = strlen(s);

    return new_cord;
}

/**
 * @brief Concatenates two cords into a new cord
 * @param[in] R
 * @param[in] S
 * @return
 */
const cord_t *cord_join(const cord_t *R, const cord_t *S) {
    cord_t *new_cord = (cord_t *)calloc(1, sizeof(cord_t));
    new_cord->left = R;
    new_cord->right = S;
    new_cord->len = cord_length(R) + cord_length(S);

    return new_cord;
}

/**
 * @brief Converts a cord to a string
 * @param[in] R
 * @return
 */
char *cord_tostring(const cord_t *R) {
    // 这个递归不断开辟内存 释放内存 写的不好
    // 修改一下函数的接口，加入一个 cursor 可以避免递归开辟多次内存、释放多次内存
    char *result = malloc(cord_length(R) + 1);
    char *cur = result;
    if (R->left != NULL)
    {
        char *new = cord_tostring(R->left);
        strcat(cur, new);
        cur += cord_length(R->left);
        free(new);
    }

    if (R->data != NULL)
    {
        strcat(cur, R->data);
        cur += (R->len-cord_length(R->left)-cord_length(R->right));
    }
    if (R->right != NULL)
    {
        char *new = cord_tostring(R->right);
        strcat(cur, new);
        free(new);
    }

    return result;
}

/**
 * @brief Returns the character at a position in a cord
 *
 * @param[in] R  A cord
 * @param[in] i  A position in the cord
 * @return The character at position i
 *
 * @requires i is a valid position in the cord R
 */
char cord_charat(const cord_t *R, size_t i) {
    assert(i <= cord_length(R));
    if (i < cord_length(R->left)) return cord_charat(R->left, i);
    if (i < R->len-cord_length(R->right)) return R->data[i-cord_length(R->left)];
    if (i < cord_length(R)) return cord_charat(R->right, i-(R->len-cord_length(R->right)));

    return '\0';
}

/**
 * @brief Gets a substring of an existing cord
 * HINT: in your recursive function, try to first identify all the cases where
 *      it is possible to return immediately without any new allocation
 * @param[in] R   A cord
 * @param[in] lo  The low index of the substring, inclusive
 * @param[in] hi  The high index of the substring, exclusive
 * @return A cord representing the substring R[lo..hi-1]
 *
 * @requires lo and hi are valid indexes in R, with lo <= hi
 */
const cord_t *cord_sub(const cord_t *R, size_t lo, size_t hi) {
    assert(lo <= hi && hi <= cord_length(R));
    // 直接 return NULL
    if (lo >= hi || hi > cord_length(R)) return NULL;
    // 直接返回
    if (lo == 0 && hi == cord_length(R)) {
        const cord_t *new_cord = R;
        return new_cord;
    }

    // TODO 完善其他情况





    return NULL;
}
