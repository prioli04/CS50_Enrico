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
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
bool DFS(int node, bool visited[], bool stack[]);
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
    bool is_candidate = false;

    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            is_candidate = true;
        }
    }

    return is_candidate;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    int id_1, id_2;

    for (int i = 0; i < candidate_count; i++)
    {
        id_1 = ranks[i];

        for (int j = i + 1; j < candidate_count; j++)
        {
            id_2 = ranks[j];
            preferences[id_1][id_2]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    int pref_1, pref_2;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            pref_1 = preferences[i][j];
            pref_2 = preferences[j][i];

            if (pref_1 > pref_2)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }

            else if (pref_1 < pref_2)
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
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
    // Bubble Sort
    pair placeholder;
    int counter = pair_count;
    int strength_1, strength_2;

    while (counter > 0)
    {
        for (int i = 0; i < counter - 1; i++)
        {
            strength_1 = preferences[pairs[i].winner][pairs[i].loser];
            strength_2 = preferences[pairs[i + 1].winner][pairs[i + 1].loser];

            if (strength_1 < strength_2)
            {
                placeholder= pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = placeholder;
            }
        }
        counter--;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    int winner_id, loser_id;

    for (int i = 0; i < pair_count; i++)
    {
        winner_id = pairs[i].winner;
        loser_id = pairs[i].loser;
        locked[winner_id][loser_id] = true;

        int node = winner_id;
        bool visited[candidate_count], stack[candidate_count];

        for (int cand = 0; cand < candidate_count; cand++)
        {
            visited[cand] = false;
            stack[cand] = false;
        }

        if (DFS(node, visited, stack))
        {
            locked[winner_id][loser_id] = false;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        int zeros_counter = 0;

        for (int j = 0; j < candidate_count; j++)
        {
            if (!locked[j][i])
            {
                zeros_counter++;
            }
        }
        if (zeros_counter == candidate_count)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }

}

bool DFS(int node, bool visited[], bool stack[])
{
    if (stack[node])
    {
        return true;
    }
    else if (!stack[node] && visited[node])
    {
        return false;
    }
    else
    {
        visited[node] = true;
        stack[node] = true;
    }

    bool cycle = false;

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[node][i])
        {
            cycle = DFS(i, visited, stack);

            if (cycle)
            {
                return true;
            }
        }
    }

    stack[node] = false;
    return false;
}