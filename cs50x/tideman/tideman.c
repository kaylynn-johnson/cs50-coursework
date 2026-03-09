#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
            preferences[i][j] = 0;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);
        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    // check that name is valid
    // add the name to the rank-th index in ranks
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            // found the candidate so move on to the other stuff
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    // loop through preferences 3D array and add one for the spot of first over all the rest
    // for example: rank candidate indexes are 0, 1, 2, 3
    // add one to preferences[0][1], preferences[0][2] & preferences[0][3]
    // add one to preferences[1][2] & preferences[1][3] and so on
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // adds the preference over all the other candidates after it
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    // Loop through preferences and look at comparison of [i][j] number vs [j][i] number
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                // If [i][j] > [j][i], add one to pair_count and add winner = i and loser = j to pairs array
                // only look for the over because the other will be checked when i reaches where j is at now
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // Use sorting method and link between pairs and preferences to put from highest to lowest
    // Going to swap method (bubble but the opposite way)
    bool swap;
    pair intermediate_pair;
    for (int i = 0; i < pair_count; i++)
    {
        swap = false;
        for (int j = 0; j < pair_count - 1; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j + 1].winner][pairs[j + 1].loser])
            {
                // need to swap to put the higher pair first
                // will leave ties alone
                swap = true;
                intermediate_pair = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = intermediate_pair;
            }
        }
        if (!swap)
        {
            // list is sorted
            break;
        }
    }

    // print out sorted pairs
    //for (int k = 0; k < pair_count; k++)
    //{
        //printf("Winner: %s, Loser: %s\n", candidates[pairs[k].winner], candidates[pairs[k].loser]);
    //}

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    // loop through pairs in outer loop
    // at inner loop, look for outer winner = inner loser
    // if yes, look for inner winner = outer loser
    bool cycle;
    printf("There are %i pairs and %i candidates\n", pair_count, candidate_count);
    for (int i = 0; i < pair_count; i++)
    {
        printf("i = %i; winner = %s; loser = %s\n", i, candidates[pairs[i].winner], candidates[pairs[i].loser]);
        cycle = false;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][pairs[i].winner] && locked[pairs[i].loser][j])
            {
                // you would be creating a cycle here
                printf("Found a cycle between candidates %s, %s, and %s\n", candidates[j], candidates[pairs[i].winner], candidates[pairs[i].loser]);
                cycle = true;
                break;
            }
        }
        if (!cycle)
        {
            // assign true to locked
            locked[pairs[i].winner][pairs[i].loser] = true;
            printf("Locked in %s over %s\n", candidates[pairs[i].winner], candidates[pairs[i].loser]);
        }
        else
        {
            printf("Did not lock in %s over %s\n", candidates[pairs[i].winner], candidates[pairs[i].loser]);
        }
    }

    for (int k = 0; k < candidate_count; k++)
    {
        for (int l = 0; l < candidate_count; l++)
        {
            if (locked[k][l])
            {
                printf(" T ");
            }
            else {
                printf(" F ");
            }
        }
        printf("\n");
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    // find the number of times second column of locked is true
    // then print out min (should be zero)
    int max_edges_index = -1;
    int max_edges_cnt = -1;
    for (int i = 0; i < candidate_count; i++)
    {
        int row_edge_cnt = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j])
            {
                row_edge_cnt++;
            }
        }
        if (row_edge_cnt > max_edges_cnt)
        {
            // currently the winner
            max_edges_index = i;
        }
    }

    printf("%s\n", candidates[max_edges_index]);

    //int candidate_edge_losses[candidate_count];
    //for (int i = 0; i < candidate_count; i++)
    //{
        // start at zero
    //    candidate_edge_losses[i] = 0;
    //    for (int j = 0; j < candidate_count; j++)
    //    {
    //        if (locked[j][i])
    //        {
    //            candidate_edge_losses[i]++;
    //        }
    //    }
    //}

    // now find min in candidate_edge_wins
    //int min_edges_count = 1000; // start at candidate 0
    //int min_edges_index = -1;
    //for (int k = 0; k < candidate_count; k++)
    //{
    //    if (candidate_edge_losses[k] < min_edges_count)
    //    {
    //        min_edges_count = candidate_edge_losses[k];
    //        min_edges_index = k;
    //    }
    //}

    // print out candidate at max_edges_index
    //printf("%s\n", candidates[min_edges_index]);
    return;
}
