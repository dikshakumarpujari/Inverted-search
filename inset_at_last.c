#include "inverted.h"

int insert_at_last(Slist **head, char* data)
{
    /*Create a new node*/
    Slist *new=malloc(sizeof(Slist));
    if(new==NULL)//check whether the node is created or not
    {
        return FAILURE;
    }
    //Update the data
    strcpy(new->filename,data);
    new->link=NULL;

if(*head==NULL)//Check whether head is empty or not
{
    *head=new;//Update head
    return SUCCESS;
}
else
{
Slist *temp=*head;//Create temporary pointer
while(temp->link!=NULL)//Traverse till the end to get the last node
{
    temp=temp->link;//Update the temp
}
temp->link=new;//Update temp value to the new
return SUCCESS;
}
}