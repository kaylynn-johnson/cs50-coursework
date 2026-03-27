#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int num;
    struct node *next;
} node;

int main(void)
{
    node *list = NULL;

    for (int i = 0; i < 3; i++)
    {
        int new_num = get_int("Enter a new number: ");
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Malloc failed.\n");
            return 1;
        }
        n->num = new_num;
        n->next = NULL;

        n->next = list;
        list = n;

        //free(n);
    }

    // print numbers
    node *ptr = list;
    while (ptr != NULL)
    {
        printf("%i\n", ptr->num);
        ptr = ptr->next;
    }

    node *ptr2 = list;
    while (ptr != NULL)
    {
        node *tmp = ptr2;
        ptr2 = ptr2->next;
        free(tmp);
    }


}
