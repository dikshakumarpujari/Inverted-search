#include "inverted.h"

void print_list(Slist *head)
{
	if (head == NULL)//Check if node is created
	{
		printf("INFO : List is empty\n");
	}
    else
    {
	    while (head)//if created		
	    {
		    printf("%s -> ", head -> filename);//Print the filename
		    head = head -> link;//Move to the next node
	    }

	    printf("NULL\n");
    }
}