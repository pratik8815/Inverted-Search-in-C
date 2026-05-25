#include "inverted_ser.h"
#include <string.h>
#include <ctype.h>

void validate_files(char *argv[],F_node **head)
{
    int i = 1;

    while(argv[i] != NULL)
    {
        FILE *fptr = fopen(argv[i],"r");

        // file is not present
        if(fptr == NULL)
        {
            printf("ERROR : %s File is not found\n",argv[i]);
            i++;
            continue;
        }

        // check empty file

        char ch = fgetc(fptr);
        //printf("First char %c\n",ch); // to debug
        if(ch == EOF)
        {
            printf("ERROR : %s is Empty\n",argv[i]);
            fclose(fptr);
            i++;
            continue;
        }
        rewind(fptr);

        // check duplicate
        
        if(check_duplicate(*head, argv[i]) == FAILURE)
        {
            printf("ERROR : %s is a duplicate file\n",argv[i]);
            fclose(fptr);
            i++;
            continue;
        }

        // the at call a function for inseart file at last

        insert_last(head,argv[i]);
        
        fclose(fptr);
        i++;
    }
    
}

// perform check duplicate function to check wether the file if already in th linked list
int check_duplicate(F_node *head,char *file_name)
{
    F_node *temp = head;

    while(temp != NULL)
    {
        if(strcmp(temp -> f_node, file_name) == 0)
        {
            return FAILURE;
        }
        temp = temp -> link;
    }
    return SUCCESS;
    
}

void print_FileList(F_node *head)
{
    F_node *temp = head;
    if(temp == NULL)
    {
        printf("No valid File\n");
        return;
    }

    printf("Valid Files are:\n");
    while(temp != NULL)
    {
        printf("%s -> ",temp -> f_node);
        temp = temp -> link;
    }
    printf("NULL\n");
}

int create_database(hash_t *arr,char *word,char *filename)
{

    int index = tolower(word[0]) - 'a';
    if(index < 0 || index >= 27)
    {
        return FAILURE;
    }

    M_node *m_temp = arr[index].slink;
    //M_node *prev = NULL;

    //run a loop to find the word
    while(m_temp != NULL)
    {
        if(strcmp(m_temp -> word, word) == 0)
        {
            break;
        }
        //prev = m_temp;
        m_temp = m_temp -> main_link;
    }

    // check for word is already present

    if(m_temp != NULL)
    {
        S_node *s_temp = m_temp -> sub_link;
        //S_node *sprev = NULL;

        while(s_temp != NULL)
        {
            if(strcmp(s_temp -> file_name, filename) == 0)
            {
                s_temp -> word_count++;
                return SUCCESS;
            }
            //sprev = s_temp;
            s_temp = s_temp -> s_link;
        }

       // file not found then create new sub node

       S_node *s_new = malloc(sizeof(S_node));

       if(s_new == NULL)
       {
            return FAILURE;
       }

       strcpy(s_new -> file_name, filename);
       s_new -> word_count = 1;
       s_new -> s_link = m_temp -> sub_link;

       m_temp -> sub_link = s_new;
       m_temp -> file_count++;
       
       return SUCCESS;
    }

    // if word not found then create new main node and store it 
    M_node *m_new = malloc(sizeof(M_node));
    if(m_new == NULL)
    {
        return FAILURE;
    }

    strcpy(m_new -> word,word);
    m_new -> file_count = 1;
   
    
    // create first sub node

    S_node *s_new = malloc(sizeof(S_node));
    if(s_new == NULL)
    {
        free(m_new);
        return FAILURE;
    }
    strcpy(s_new -> file_name, filename);
    s_new -> word_count = 1;
    s_new -> s_link = NULL;

    m_new -> sub_link = s_new;
    
    m_new -> main_link = arr[index].slink;
    arr[index].slink = m_new;

    return SUCCESS;
}

void Display_Database(hash_t *arr)
{
    printf("\n========================== DATABASE =========================\n");
    printf("Index | Word        | File Count | File Name       | Word Count\n");
    printf("---------------------------------------------------------------\n");

    for(int i = 0; i < 27; i++)
    {
        if(arr[i].slink != NULL)
        {
           
            M_node *m_temp = arr[i].slink;

            while(m_temp != NULL)
            {
                
                
                S_node *s_temp = m_temp -> sub_link;
                

                while(s_temp != NULL)
                {
                   printf("%-5d | %-10s | %-10d | %-15s | %-10d\n",i,m_temp->word,m_temp->file_count,s_temp->file_name,s_temp->word_count);

                    s_temp = s_temp -> s_link;
                }
                m_temp = m_temp -> main_link;
            }
        }
    }
    printf("===============================================================\n");
}
int Search_Database(hash_t *arr)
{
    char str[50];
    printf("Enter the Word YOU Want to Search:");
    scanf("%s",str);
    

    

    int index = tolower(str[0]) - 'a';
    if(index < 0 || index >= 27)
    {
        return FAILURE;
    }

    M_node *temp = arr[index].slink;

    int found = 0;

    while(temp != NULL)
    {
        if(strcmp(str,temp -> word) == 0)
        {
            printf("Word Found\n");
            printf("File Count : %d , Word : %s\n",temp -> file_count,temp -> word);
            

            S_node *sub_temp = temp -> sub_link;

            while(sub_temp != NULL)
            {
                printf("File Name : %s,   Word Count : %d\n",sub_temp -> file_name, sub_temp -> word_count);
                sub_temp = sub_temp -> s_link;
            }
            temp = temp -> main_link;

            found = 1;
            break;
        }
        temp = temp -> main_link;
    }
    if(!found)
    {
        printf("ERROR : word Not Found...\n");
        return FAILURE;
    }
    return SUCCESS;
    
}
void Save_Database(hash_t *arr)
{
    char fname[20];

    printf("Enter the file name :");
    scanf("%s", fname);

    FILE *fptr = fopen(fname,"w");

    if(fptr == NULL)
    {
        printf("Unable to open File\n");
        return;
    }

    
    for(int i = 0; i < 27; i++)
    {
        M_node *mtemp = arr[i].slink;

        while(mtemp != NULL)
        {
            fprintf(fptr, "#%d;%s;%d;", i, mtemp -> word, mtemp -> file_count);

            S_node *stemp = mtemp -> sub_link;

            while(stemp != NULL)
            {
                fprintf(fptr, "%s;%d;", stemp -> file_name, stemp -> word_count);
                stemp = stemp -> s_link;

            }

            fprintf(fptr, "#\n"); 

            mtemp = mtemp -> main_link;
        }
        
    }
        fclose(fptr);
        printf("Database saved successfully\n");
}

int Update_Database(hash_t *arr,F_node **head)
{
    char str[20];
    printf("Enter new file name:");
    scanf("%s", str);

    // validate the file through extension

    char *ptr = strstr(str, ".txt");
    if(ptr == NULL)
    {
        printf("Please Enter the .txt file\n");
        return FAILURE;
    }

    if(strcmp(ptr, ".txt"))
    {
        printf("Please Enter the .txt file\n");
        return FAILURE;
    }

    // first open the filee
    FILE *update = fopen(str, "r");

    if(update == NULL)
    {
        printf("This file is not Found\n");
        return FAILURE;
    }

    // check if the file is already present or not 
    if(check_duplicate(*head, str) == FAILURE)
    {
        printf("File is already exists in database\n");
        fclose(update);
        return FAILURE;
    }

    //check file is empty or not
    fseek(update, 0, SEEK_END);
    int size = ftell(update);

    if(size == 0)
    {
        printf("File is empty\n");
        fclose(update);
        return FAILURE;
    }
    rewind(update);

    insert_last(head, str);

    char word[50];

    while(fscanf(update, "%s", word) != EOF)
    {
        create_database(arr, word, str);
    }

    fclose(update);
    printf("Database Update Successfully\n");
    return SUCCESS;
}

int insert_last(F_node **head,char *filename)
{
    F_node *m_new = malloc(sizeof(F_node));

    if(m_new == NULL)
    {
        return FAILURE;
    }

    strcpy(m_new -> f_node,filename);
    m_new -> link = NULL;

    if(*head == NULL)
    {
        *head = m_new;
        return SUCCESS;
    }

    F_node *temp = *head;
    while(temp -> link != NULL)
    {
        temp = temp -> link;
    }

    temp -> link = m_new;
    return SUCCESS;

}   

