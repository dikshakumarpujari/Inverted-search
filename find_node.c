#include "inverted.h"

int find_node(Slist *head, char* data)
{
    if(head==NULL)//Check node is created
    return FAILURE;
    Slist *temp=head;//Update the temp to head
    while(temp!=NULL)//Traverse till the last node
    {
         if(strcmp(temp->filename,data)==0)//compare the data with the given data to find
        {
            return SUCCESS;
        }
        else
        {
            temp=temp->link;//Move to the next node
        }
    }
    return FAILURE;
	
}
