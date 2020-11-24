#include "requirements.h"


linkedListReq* createLinkedListReq()
{
    linkedListReq *list = (linkedListReq*) malloc(sizeof(linkedListReq));
    list->head = NULL;
    return list;
}

void addLastNodeReq(linkedListReq *list, char* data)
{
    //create node and allocate memory.
    nodeReq *newNode = (nodeReq*) malloc(sizeof(nodeReq));
    newNode->data = (char*) malloc(sizeof(char) * 256);
    strncpy(newNode->data, data, 256);
    newNode->next = NULL;
    //check if there are elements in the list.
    if (list->head == NULL)
    {
        list->head = newNode;
        return;
    }
    nodeReq *curNode = list->head;

    while(curNode->next != NULL)
    {
        curNode = curNode->next;
    }
    //we should have last node in curNode by the end of the loop. 
    curNode->next = newNode;
    newNode->prev = curNode;
    return;
}

void printListReq(linkedListReq *list)
{
    if (list->head == NULL) return;
    nodeReq *head = list->head;
    while(head->next != NULL)
    {
        printf("%s ", head->data);
        head = head->next;
    }
    printf("%s\n", head->data);
    return;
}

void deleteLinkedListReq(linkedListReq *list)
{
    
    if (list == NULL) return;

    //checks if there are any elements in the linked list.
    if (list->head == NULL) 
    {
        free(list);
        return;
    }
    nodeReq *head = list->head;

    if (head->data != NULL) free(head->data);
    while(head->next != NULL)
    {
        head = head->next;
        free(head->data);
        free (head->prev);
    }
    free (head);
    free (list);
}