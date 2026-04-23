/*
NAME: DIKSHA
PROJECT NAME: INVERTED SEARCH
PROJECT DESCRIPTION: This project implements an Inverted Index system in C to efficiently map words
 to the files in which they appear. It uses a hash table of size 27, where each index stores 
 a linked list of words, and each word node maintains a sub-linked list of filenames along with 
 their frequency count. The program supports creating the database from multiple text files, 
 searching for words, displaying the stored data, updating from a saved file, and saving 
 the database. This project demonstrates practical implementation of hashing, file handling, 
 dynamic memory allocation, and linked list data structures for building a 
 basic search engine model.
*/
#include "inverted.h"


int main(int argc,char *argv[])
{
    if(argc<2)// Check if no input files are given in command line
    {
        printf("Invalid arguments\n");
        return 0;
    }
    int database_created=0;// Flag to check whether database is created
    int database_updated=0;// Flag to check whether database is updated
    Slist *head=NULL;

    hash_t arr[27];// Declare hash table of size 27
    //initializing hash table index and link
    for(int i=0;i<27;i++)// Initialize hash table
    {
        arr[i].index=i;// Assign index value
        arr[i].mainlink=NULL;// Initialize main link to NULL
    }
    int i=1;// Start from argv[1]
    while(argv[i]!=NULL) // Traverse command-line arguments
    {
        if(validate_files(argv[i])==SUCCESS)// Validate each file
        {
            if(find_node(head,argv[i])==SUCCESS)// Check if file already exists in list
            {
                printf("INFO: %s duplicate found\n",argv[i]);
            }
            else
            {
                insert_at_last(&head,argv[i]);// Insert valid file into linked list
            }
        }
        i++;// Move to next argument
    }
    printf("INFO: Valid files are: ");
    print_list(head);
    int opt;

    while(1)
    {
        printf("\n:::MENU:::\n");
        printf("\n1.Create database\n2.Display database\n3.Search database\n4.update database\n5.Save\n6.Exit\n\n");// Print menu options
        printf("Enter the option: ");
        scanf("%d",&opt);
        switch(opt)// Switch based on user choice
        {
            case 1:
            if(database_created==1)// Check if database already created
            {
                printf("INFO: database already created\n");
                break;
            }
            database_created=1;// Set created flag
            create_database(head,arr);// Create inverted index database
            printf("INFO: Database created successfully\n");
            break;

            case 2:
            if(database_created==0 && database_updated==0)// Check if database empty
            printf("INFO: Database is empty\n");

            else
            display_database(arr); // Display database
            break;

            case 3:
            search(arr); // Search word in database
            break;

            case 4:
            if(database_updated==1)// Check if already updated
            {
                printf("INFO: Database already updated\n");
                break;
            }
    
            if(update_database(arr)==SUCCESS)// Set updated flag if successful
            database_updated=1;

            else
            printf("ERROR: Update database failed\n");
            break;

            case 5:
            save_database(arr); // Save database to file
            break;

            case 6:
            return 0;

            default:
            printf("ERROR: Invalid Option\n");
        }
    }
}


int validate_files(char *file)
{
    char *ch=strchr(file,'.');// Find '.' in file name to check extension
    if(ch==NULL || strcmp(ch,".txt")!=0)// If extension is not .txt
    {
        printf("INFO: %s has invalid extesion\n",file);
        return FAILURE;
    }

    FILE *fptr=fopen(file,"r");// Open file in read mode
    if(fptr==NULL)// If file does not exist
    {
        printf("INFO: %s file does not exist\n",file);
        return FAILURE;
    }
    fseek(fptr,0,SEEK_END);// Move file pointer to end
    if(ftell(fptr)==0) // Check if file size is zero
    {
        printf("INFO: %s is empty\n",file);
        fclose(fptr);// Close file
        return FAILURE;
    }
    fclose(fptr);
    return SUCCESS;
    
   
}