/*
Name - Pratik Satsure
Batch Id - 25026_079

Project Title - Inverted Search (Inverted Index) using Hashing in C

Project Description

This project implements an Inverted Search system using the C programming 
language. The system reads multiple text files, processes their contents, 
and builds an inverted index that maps each word to the list of files in 
which it appears, along with the number of occurrences.

A hash table is used to efficiently store and retrieve words. 
Each index in the hash table represents a list of words starting 
with a particular character. For every word, a main node stores the 
word and the number of files it appears in, while sub-nodes store 
file names and word counts.

The project supports operations such as:

Validating input files
Creating the database (indexing words)
Displaying the database
Searching for a word
Updating the database with new files
Saving the database to a file

This system is similar to how search engines organize data for fast 
retrieval.

Objectives
To understand the concept of inverted indexing
To implement hashing techniques for fast data access
To work with dynamic memory allocation and linked lists
To perform file handling operations in C
To design a modular and menu-driven application


Conclusion

The Inverted Search project successfully demonstrates the implementation of an 
efficient text search system using hashing and linked lists in C. 
It provides fast retrieval of words across multiple files and 
highlights important concepts like data structures, file handling, and 
memory management. This project builds a strong foundation for understanding 
real-world applications such as search engines and indexing systems.
*/

#include <stdio.h>
#include "inverted_ser.h"
int main(int argc,char *argv[])
{
    if(argc == 1)
    {
        printf("ERROR : No File Is Present\n");
        return FAILURE;
    }

    //F_node *temp = NULL;
    F_node *head = NULL;

    
    
    // call validate file list fun
    validate_files(argv, &head);

    if(head == NULL)
    {
        printf("No valid file is there...\n");
        return 0;
    }
    print_FileList(head);
   
    // create hash table
    hash_t arr[27];

    for(int i = 0; i < 27; i++)
    {
        arr[i].index = i;
        arr[i].slink = NULL;
    }

    int option;
    while(1)
    {
        
        printf("Select your choice:\n1. Create Database\n2. Display Database\n3. Save Database\n4. Search\n5. Update Databse\n6. Exit\n\nEnter your choice : ");
        scanf("%d",&option);

        switch(option)
        {
            case 1:
            {
                F_node *temp = head;
                char word[50];

                while(temp != NULL)
                {
                    FILE *fptr = fopen(temp -> f_node, "r");

                    while(fscanf(fptr, "%s", word) != EOF)
                    {
                        create_database(arr,word,temp -> f_node);
                    }
                    fclose(fptr);
                    temp = temp -> link;
                }
                printf("Database created successfully\n");
                break;
            }
            
            case 2:
                Display_Database(arr);
                break;

            case 3:
                Save_Database(arr);
                break;

            case 4:
                Search_Database(arr);
                break;

            case 5:
                Update_Database(arr,&head);
                break;

            case 6:
                break;

            default:
                printf("Invalid Input : Please enter the valid option\n");
        }   


    }
    
    return 0;


}