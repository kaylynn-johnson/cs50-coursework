#include <cs50.h>
#include <stdio.h>

typedef struct node
{
    int num;
    struct node *next;
} node;

int main(void)
{
    node list = NULL;

    for (int i = 0; i < 3; i++)
    {
        new_num = get_int("Enter a new number: ");
        n = malloc(sizeof(node));
        n->num = new_num;
        n->next = NULL;

        
    }
}
