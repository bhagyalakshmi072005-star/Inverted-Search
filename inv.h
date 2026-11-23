#ifndef INV_H
#define INV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FNAME_SIZE 30
#define WORD_SIZE 30

typedef struct node{
    char filename[FNAME_SIZE];
    struct node *link;
}S_list;

typedef struct subnode{
    char filename[FNAME_SIZE];
    int word_count;
    struct subnode *link;
}subnode_t;

typedef struct mainnode{
    char word[WORD_SIZE];
    int file_count;
    subnode_t *sublink;
    struct mainnode *link;
}mainnode_t;

int file_validation(char *argv[],S_list **head);
int create_db(S_list *head,mainnode_t *arr[]);
int display_db(mainnode_t *arr[]);
int search_db(mainnode_t *arr[]);
int save_db(mainnode_t *arr[]);
int update_db(S_list **head,mainnode_t *arr[]);

#endif