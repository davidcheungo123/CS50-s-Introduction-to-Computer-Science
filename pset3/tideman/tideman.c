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

int candidate_count;
int pair_count ;

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

            if (vote(j, name, ranks)==false)
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
       for (int z=0 ; z< pair_count;z++){
           printf("Winner: %i, Loser:%i\n", pairs[z].winner,pairs[z].loser);
       }
    lock_pairs();
        for (int i=0; i< candidate_count; i++){
        for (int j=0; j< candidate_count; j++){
         printf("%d ", locked[i][j] );
    }
    printf("\n");
    
    }
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    int y=0;
    for (int i=0 ; i < candidate_count ;i++ )
    {
    if (strcmp(name,candidates[i])!=0)
    {
    y++;
    if (y== candidate_count){
    return false;
    break;
    }
    }   else  {
        ranks[rank]= i;
        return true;
        break;
    }

  
    }
    
    return true;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
   for (int i=0 ; i< candidate_count;i++)
   {
       for (int j=i+1 ; j<candidate_count;j++)
       {
           preferences[ranks[i]][ranks[j]]++;
       }
   }
    
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{

        for (int i=0 ; i< candidate_count;i++)
   {
       for (int j=i+1 ; j<candidate_count;j++)
       {
        if ( preferences[i][j] > preferences[j][i]){
            
            pairs[pair_count].winner=i;
            pairs[pair_count].loser=j;
            pair_count++;

        } else if ( preferences[i][j] < preferences[j][i]){
            pairs[pair_count].winner=j;
            pairs[pair_count].loser=i;
            pair_count++;

        }

       }
   }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int winner=0;
    int loser=0;
    int dummy;
    for (int i=0; i<pair_count; i++){
        
        for (int j= i+1 ; j <pair_count;j++){

            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser]){
        winner=pairs[i].winner;
        pairs[i].winner= pairs[j].winner;
        pairs[j].winner=winner;
                
        loser=pairs[i].loser;
        pairs[i].loser= pairs[j].loser;
        pairs[j].loser=loser;
            }  
        }
    


    }


    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int k=0; k< pair_count ; k++){
        locked[pairs[k].winner][pairs[k].loser]=true;
        locked[pairs[k].loser][pairs[k].winner]= false;
    }
    
    for (int i=0; i< candidate_count;i++){
        locked[i][i]= false;
    }
    int total=0;
    for (int z=0; z< candidate_count;z++){
        int row=0;
        for (int a=0; a< candidate_count ; a++){
            if (locked[z][a]==true){
             row++;
            }
            
        }
        if (row==1){
            total++;
        }
    }
    if (total==candidate_count){
        locked[pairs[pair_count-1].winner][pairs[pair_count-1].loser] = false;
    }
    
    
    return;
}

// Print the winner of the election
void print_winner(void)
{

    for (int i=0; i< candidate_count; i++){
    int test=0;
        for (int j=0; j< candidate_count; j++){
            if (locked[j][i]==false){
                test++;
            }
        }
    if (test== candidate_count){
        printf("%s\n", candidates[i]);
    }
    }
    return;
}

