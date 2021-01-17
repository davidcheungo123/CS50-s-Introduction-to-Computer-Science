// Implements a dictionary's functionality

#include <stdbool.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1000;

bool is_loaded_dict =false;

// Hash table
node *table[N];

unsigned int num_words=0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char check_word[strlen(word)];
    strcpy(check_word, word);
    
    for (int i=0; check_word[i]!= '\0' ; i++)
    {
        check_word[i] = tolower(check_word[i]);
    }
    
    int index = hash(check_word);
    if(table[index] !=NULL)
    {
        for ( node * temp = table[index] ; temp != NULL ; temp = temp->next)
        {
            if ( strcmp(temp->word, check_word )==0)
            {
                return true;
            }
        }
    }
    return false;
}

// Hashes word to a number
//adapted from http://www.cse.yorku.ca/~oz/hash.html 
unsigned int hash(const char *word)
{
      
    
        unsigned long hash = 5381;
        
        int c;

   while ((c = *word++))
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        hash=hash % N;
        
        return hash;


        
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    
    
    FILE* inptr= fopen(dictionary, "r");
    
    for (int i=0 ; i< N ; i++)
    {
        table[i]=NULL;
    }
    
    if (inptr==NULL)
    {
        fclose(inptr);
        printf("The dictionary cannot be opened");
    }
    
    char word[LENGTH+1];
    
    while (fscanf(inptr, "%s", word)!=EOF)
    {
        num_words++;
        


            node *new_nodeptr= malloc(sizeof(node));
            
            if (new_nodeptr == NULL)
                free(new_nodeptr);
            
            
            strcpy(new_nodeptr->word,word);
            int index=hash(word);

            

                new_nodeptr->next= table[index];
                table[index]= new_nodeptr;
            
 
    }
    fclose(inptr);  
    
    is_loaded_dict = true;
    
    return true;
    
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    
    if (!is_loaded_dict)
    return 0;
    
    return num_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    if (!is_loaded_dict)
    return false;
    
    for (int i=0; i<N ; i++)
    
    {
        if (table[i]!=NULL)
        {
            node* ptr = table[i];
            
            while(ptr!=NULL)
            {
                node*predptr = ptr;
                ptr= ptr->next;
                free(predptr);
            }
        }
    }
    
    return true;

}
