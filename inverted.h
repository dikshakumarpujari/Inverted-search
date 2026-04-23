#include<string.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAILURE -1

typedef struct node
{
    char filename[25];
    struct node *link;
}Slist;

typedef struct node1
{
    int word_count;
    char filename[25];
    struct node1 *sublink;
}sub_node_t;


typedef struct node2
{
    int file_count;
    char word[50];
    sub_node_t*sub_link;
    struct node2 *mainlink;
}main_node_t;

typedef struct node3
{
    int index;
    main_node_t *mainlink;
}hash_t;

int insert_at_last(Slist **head, char* data);
int validate_files(char *file);
int find_node(Slist *head, char* data);
void print_list(Slist *head);
int validate_files(char *file);
void create_database(Slist *head,hash_t arr[]);
void insert_node(hash_t arr[],char *word,char* filename,int index);
void display_database(hash_t arr[]);
void save_database(hash_t arr[]);
void search(hash_t arr[]);
int update_database(hash_t *arr);
int file_exists(hash_t *arr, char *filename);