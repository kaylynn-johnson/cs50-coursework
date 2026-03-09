#include <cs50.h>
#include <stdio.h>

typedef struct
{
    string name;
    int votes;
} candidate;

candidate get_candidate(void);

int main(void)
{

    candidate president[3];
    for (int i = 0; i < 3; i++)
    {
        president[i] = get_candidate();
    }

    for (int j = 0; j < 3; j++)
    {
        printf("Candidate %i is named %s and has %i votes.\n", j+1, president[j].name, president[j].votes);
    }
}

candidate get_candidate(void)
{
    candidate new_candidate;
    new_candidate.name = get_string("Name: ");
    new_candidate.votes = get_int("Votes: ");

    return new_candidate;
}
