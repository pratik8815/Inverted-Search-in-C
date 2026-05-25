#ifndef INVERTED_SER_H
#define INVERTED_SER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS   1
#define FAILURE   0

// sub node
typedef struct sub_node
{
    int word_count;
    char file_name[50];
    struct sub_node *s_link;
} S_node;

// main node
typedef struct main_node
{
    int file_count;
    char word[45];
    S_node *sub_link;
    struct main_node *main_link;
} M_node;

// file list
typedef struct file
{
    char f_node[100];
    struct file *link;
} F_node;

// hash table
typedef struct hash_table
{
    int index;
    M_node *slink;
} hash_t;


int create_database(hash_t *arr,char *word,char *filename);
void Display_Database(hash_t *arr);
int Search_Database(hash_t *arr);
void Save_Database(hash_t *arr);
int Update_Database(hash_t *arr,F_node **head);

void validate_files(char *argv[],F_node **head);
int check_duplicate(F_node *head,char *filename);
int insert_last(F_node **head,char *filename);
void print_FileList(F_node *head);
#endif