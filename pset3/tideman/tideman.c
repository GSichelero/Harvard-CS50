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
    int strength;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count = 0;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, string ranks[]);
void record_preferences(string ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool circle_lock(int candidate_winner, int candidate_loser, int head_circle);

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
        pairs[i].strength = 0;
    }

    // Normalize preferences for future updates
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            preferences[i][j] = 0;
        }
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        string ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
            else
            {
                ranks[j] = name;
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
bool vote(int rank, string name, string ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(string ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            for (int k = 0; k < candidate_count; k++)
            {
                if (strcmp(ranks[i], candidates[k]) == 0)
                {
                    for (int l = 0; l < candidate_count; l++)
                    {
                        if (strcmp(ranks[j], candidates[l]) == 0)
                        {
                            preferences[k][l]++;
                        }
                    }
                }
            }
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > 0)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pairs[pair_count].strength = preferences[i][j];
                pair_count++;
            }
            if (preferences[j][i] > 0)
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pairs[pair_count].strength = preferences[j][i];
                pair_count++;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
    {
        pair pair_lock = pairs[i];
        for (int j = i + 1; j < pair_count; j++)
        {
            if (pairs[i].strength < pairs[j].strength)
            {
                pairs[i] = pairs[j];
                pairs[j] = pair_lock;
            }
        }
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (pairs[i].winner == j)
            {
                for (int k = 0; k < candidate_count; k++)
                {
                    if (pairs[i].loser == k)
                    {
                        if (circle_lock(j, k, j))
                        {
                            locked[j][k] = true;
                        }
                    }
                }
            }
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    bool winner[candidate_count];
    for (int i =  0; i < candidate_count; i++)
    {
        winner[i] = true;
    }

    for (int i =  0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j])
            {
                winner[j] = false;
            }
        }
    }

    for (int i =  0; i < candidate_count; i++)
    {
        if (winner[i])
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

// Verify if the lock is creating a circle
bool circle_lock(int candidate_winner, int candidate_loser, int head_circle)
{
    for (int l = 0; l < candidate_count; l++)
    {
        if (locked[candidate_loser][l])
        {
            if (l == head_circle)
            {
                return false;
            }
            //candidate_winner = candidate_loser;
            //candidate_loser = l;
            return circle_lock(candidate_loser, l, head_circle);
        }
    }

    return true;
}

