#include "inverted.h"

void create_database(Slist *head, hash_t arr[])
{
    Slist *temp = head;// Pointer to traverse
    char word_buffer[50]; // Buffer to store each word

    while(temp != NULL)// Loop through all files
    {
        if(file_exists(arr, temp->filename))// Skip if file already indexed
        {
            temp = temp->link;// Move to next file
            continue;
        }

        FILE *fptr = fopen(temp->filename, "r");// Open file in read mode
        if(fptr == NULL)// If file not opened
        {
            temp = temp->link;// Move to next file
            continue;
        }

        while(fscanf(fptr, "%s", word_buffer) == 1)// Read words one by one
        {
            int ind;// Index variable

            if(word_buffer[0] >= 'A' && word_buffer[0] <= 'Z')// Uppercase index
                ind = word_buffer[0] - 'A';
            else if(word_buffer[0] >= 'a' && word_buffer[0] <= 'z') // Lowercase index
                ind = word_buffer[0] - 'a';
            else
                ind = 26;   // Special characters index

            insert_node(arr, word_buffer, temp->filename, ind);// Insert word
        }

        fclose(fptr);
        temp = temp->link; // Move to next file
    }
}
void insert_node(hash_t arr[],char *word,char* filename,int index)
{
    /*if hash_link part is NULL*/
    main_node_t *maintemp=arr[index].mainlink;
    main_node_t *mainprev = NULL;// Previous main node
    if(maintemp==NULL) // If no word at index
    {
        main_node_t *new_main=malloc(sizeof(main_node_t));// Allocate main node
        sub_node_t *new_sub = malloc(sizeof(sub_node_t));// Allocate sub node
        strcpy(new_main->word, word);// Copy word
        new_main->file_count = 1;// Initialize file count
        new_main->mainlink = NULL;// Set next main link
        new_main->sub_link = new_sub;

        strcpy(new_sub->filename,filename);// Store filename
        new_sub->word_count=1;// Initialize word count
        new_sub->sublink = NULL;// Set sub link NULL


        new_main->sub_link = new_sub;
        arr[index].mainlink = new_main;
        return;

    } 
    while(maintemp!=NULL) // Traverse main list
    {
        /* check if the word is in the same file then increment the count*/
        if(strcmp(maintemp->word,word)==0)// If word found
        {
            sub_node_t *sub_temp=maintemp->sub_link;// Traverse sub list
             while(sub_temp != NULL)
            {
                if(strcmp(sub_temp->filename, filename) == 0)// Check if file already exists
                {
                    sub_temp->word_count++;// Increment word count
                    return;
                }
                sub_temp = sub_temp->sublink;// Move to next sub node
        }
        /*if the word is present in the different file*/
        sub_node_t *new_sub = malloc(sizeof(sub_node_t)); // Allocate memory for new sub node
            strcpy(new_sub->filename, filename);// Copy filename
            new_sub->word_count = 1;// Initialize word count
            new_sub->sublink = maintemp->sub_link;// Insert new sub node at beginning

            maintemp->sub_link = new_sub; // Update sub link
            maintemp->file_count++; // Increase file count


            return;
        
    }
    mainprev=maintemp;// Store current node as previous
    maintemp = maintemp->mainlink;// Move to next main node
}
/*if word is not common then*/
    main_node_t *new_main = malloc(sizeof(main_node_t));// Allocate memory for new main node
    sub_node_t *new_sub = malloc(sizeof(sub_node_t));// Allocate memory for new sub node

    strcpy(new_main->word, word);// Copy word
    new_main->file_count = 1;// Initialize file count
    new_main->mainlink = NULL;// Set next main link as NULL
    new_main->sub_link = new_sub;// Attach sub node

    strcpy(new_sub->filename, filename);// Copy filename
    new_sub->word_count = 1;// Initialize word count
    new_sub->sublink = NULL; // Set next sub link as NULL

    mainprev->mainlink = new_main; // Attach new main node at end of list
}
void display_database(hash_t arr[])
{
    printf("\nIndex  File_count   Word    Word_count  Filename\n");
    for(int i=0;i<27;i++)// Loop through all 27 hash indexes (A–Z + special)
    {
        if(arr[i].mainlink!=NULL) // Check if current index contains any word
        {
            main_node_t *maintemp=arr[i].mainlink; // Get first main node at this index

            while(maintemp!=NULL)// Traverse main linked list
            {
            printf("%d",i);
            printf("               %d     %s",maintemp->file_count,maintemp->word);
            sub_node_t *sub_temp=maintemp->sub_link;// Get first sub node 
            while(sub_temp!=NULL)// Traverse sub linked list
            {
                printf("           %d      %s",sub_temp->word_count,sub_temp->filename);
                sub_temp=sub_temp->sublink;// Move to next sub node
            }
            printf("\n");
            maintemp=maintemp->mainlink;// Move to next main node
        }
    }
}
}
void save_database(hash_t arr[])
{
    char file_name[50];// Declare character array to store output file name
    printf("Enter the File name to store the data: ");
    scanf(" %s",file_name);
    char *dot=strchr(file_name,'.'); // Find position of '.' in file name to check extension
    if(dot==NULL || strcmp(dot,".txt")!=0)// Check if extension is not .txt
    {
        printf("%s has invalid extesion\n",file_name);
        return ;
    }

    FILE *fptr=fopen(file_name,"w");// Open file in write mode
    if(fptr==NULL)// If file opening fails
    {
        printf("%s file does not exist\n",file_name);
        return;
    }
    for(int i=0;i<27;i++)// Traverse all 27 hash indexes
    {
        if(arr[i].mainlink!=NULL)// Check if index contains words
        {
            main_node_t *maintemp=arr[i].mainlink;// Get first main node at this index
            while(maintemp!=NULL)// Traverse main linked list
            {
            fprintf(fptr,"#%d;",i);
            fprintf(fptr,"%d;%s;",maintemp->file_count,maintemp->word);
            sub_node_t *sub_temp=maintemp->sub_link;// Get first sub node
            while(sub_temp!=NULL)// Traverse sub linked list
            {
                fprintf(fptr,"%d;%s;",sub_temp->word_count,sub_temp->filename);
                sub_temp=sub_temp->sublink;
            }
            fprintf(fptr,"#\n");
            maintemp=maintemp->mainlink;// Move to next main node
        }
    }
}
fclose(fptr);
printf("Database saved SUCCESFULLY\n");
}
void search(hash_t arr[])
{
    char word[25]; // Declare array to store word
    printf("Enter the word to search: ");
    scanf(" %s",word);
    int index;// Variable to store hash index
            if(word[0]>='A'&&word[0]<='Z')//If it is alphabet
            index=word[0]-'A';
            else if(word[0]>='a'&&word[0]<='z')//If it is alphabet
            index=word[0]-'a';//find the index
            else
            index=26;
        if(arr[index].mainlink!=NULL)
     {
        main_node_t *maintemp=arr[index].mainlink;
    while(maintemp!=NULL)// Traverse main linked list
    {
        if(strcmp(maintemp->word,word)==0)// Compare stored word with searched word
        {
            printf("%s is present in %d files\n",maintemp->word,maintemp->file_count);
        
        sub_node_t *sub_temp=maintemp->sub_link;// Get first sub node
        while(sub_temp!=NULL)// Traverse sub linked list
        {
            printf("in %s %d times\n",sub_temp->filename,sub_temp->word_count);
            sub_temp=sub_temp->sublink;
        }
        return;
    }
        maintemp=maintemp->mainlink;// Move to next sub node
    }

}
printf("%s Not found in database\n",word);
}

int update_database(hash_t *arr)
{
    char filename[25], line[100];// Declare variables to store file name and each line

    printf("Enter the saved file name: ");
    scanf("%s", filename);

    if (validate_files(filename) == FAILURE)// Validate input file and return FAILURE if invalid
        return FAILURE;

    FILE *fptr = fopen(filename, "r");// Open saved database file in read mode
    if (fptr == NULL)// If file opening fails, return FAILURE
        return FAILURE;

    while (fscanf(fptr, "%s", line) != EOF)// Read each formatted entry from file
    {
        int len = strlen(line); // Get length of current line

        if (line[0] != '#' || line[len - 1] != '#')
        {
            printf("ERROR: Invalid %s file format\n", filename);
            fclose(fptr);
            return FAILURE;
        }

        char *token = strtok(&line[1], ";");//get the first word from the file

        int index = atoi(token);// Convert index token to integer
        int file_count = atoi(strtok(NULL, ";"));// Get file count

        char word[50];// Declare variable to store word
        strcpy(word, strtok(NULL, ";"));// Copy word from token

        main_node_t *main = arr[index].mainlink;// Get main linked list at index
        main_node_t *prev_main = NULL;// Pointer to track previous main node
        int word_found = 0;// Flag to check if word exists

        /* Search if word exists */
        while (main != NULL)
        {
            if (strcmp(main->word, word) == 0)//compare the word
            {
                word_found = 1;
                break;
            }
            prev_main = main;// Store previous main node
            main = main->mainlink;// Move to next main node
        }

        /* If word NOT found */
        if (word_found == 0)
        {
            main_node_t *new_main = malloc(sizeof(main_node_t));// Allocate memory for new main node

            new_main->file_count = 0;// Initialize file count
            strcpy(new_main->word, word);// Copy word
            new_main->sub_link = NULL;// Initialize sub link
            new_main->mainlink = NULL;// Initialize main link

            for (int i = 0; i < file_count; i++)
            {
                sub_node_t *new_sub = malloc(sizeof(sub_node_t));// Allocate memory for sub node

                new_sub->word_count = atoi(strtok(NULL, ";")); // Get word count
                strcpy(new_sub->filename, strtok(NULL, ";"));// Copy filename
                new_sub->sublink = NULL;// Initialize sub link

                if (new_main->sub_link == NULL) // Attach first sub node
                {
                    new_main->sub_link = new_sub;
                }
                else
                {
                    sub_node_t *temp = new_main->sub_link;// Temporary pointer for traversal
                    while (temp->sublink != NULL)// Move to last sub node
                        temp = temp->sublink;

                    temp->sublink = new_sub;// Attach new sub node
                }

                new_main->file_count++;// Increment file count
            }

            if (arr[index].mainlink == NULL)// Attach new main node if list empty
            {
                arr[index].mainlink = new_main;
            }
            else
            {
                prev_main->mainlink = new_main;// Attach at end of main list
            }
        }
        else
        {
            /* Word exists → merge files */
            for (int i = 0; i < file_count; i++)
            {
                int wc = atoi(strtok(NULL, ";"));// Get word count
                char fname[25];
                strcpy(fname, strtok(NULL, ";"));// Copy filename

                sub_node_t *sub = main->sub_link;// Get sub linked list
                sub_node_t *prev_sub = NULL;// Track previous sub node
                int file_found = 0;// Flag to check file existence

                while (sub != NULL)
                {
                    if (strcmp(sub->filename, fname) == 0)//Compare the filename
                    {
                        file_found = 1;
                        break;
                    }
                    prev_sub = sub;// Store previous sub node
                    sub = sub->sublink;// Move to next sub node
                }

                if (file_found == 0)
                {
                    sub_node_t *new_sub = malloc(sizeof(sub_node_t));// Allocate memory for new sub node

                    new_sub->word_count = wc; // Set word count
                    strcpy(new_sub->filename, fname);// Copy filename
                    new_sub->sublink = NULL;

                    if (prev_sub == NULL)// Attach if first sub node
                        main->sub_link = new_sub;
                    else
                        prev_sub->sublink = new_sub;

                    main->file_count++;// Increment file count
                }
            }
        }
    }

    fclose(fptr);
    printf("INFO: Updated database successfully\n");
    return SUCCESS;
}



int file_exists(hash_t arr[], char *filename)
{
    for(int i = 0; i < 27; i++)// Traverse all 27 hash table indexes 
    {
        main_node_t *main = arr[i].mainlink;// Get main linked list at current index

        while(main != NULL)// Traverse main linked list
        {
            sub_node_t *sub = main->sub_link;// Get sub linked list

            while(sub != NULL)// Traverse sub linked list
            {
                if(strcmp(sub->filename, filename) == 0)// Compare stored filename with given filename
                    return 1;

                sub = sub->sublink;// Move to next sub node
            }

            main = main->mainlink;// Move to next main node
        }
    }

    return 0;
}