#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct nodeReq{
    char* data;
    struct nodeReq *next;
    struct nodeReq *prev;
}nodeReq;

typedef struct linkedListReq{
    nodeReq *head;
} linkedListReq;

/**
 * allocates memory for linkedListReq and returns pointer to it
 */
linkedListReq* createLinkedListReq();
/**
 * adds node to linkedListReq
 */
void addLastNodeReq(linkedListReq *, char *);
/**
 * prints out linkedListReq
 */
void printListReq(linkedListReq *);
/**
 * deletes linkedListReq
 */
void deleteLinkedListReq(linkedListReq *);
#endif