#include <stdbool.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "dictionary.h"

int main(void)
{

    FILE* inptr= fopen("small", "r");

    if (inptr== NULL)
    {

        printf("Cannot open the dictionary\n");
        fclose(inptr);
        return 1;
    }


char c[1];

string s[100];

int i =0; int j=0;


while(fread(c ,1 ,1, inptr))
{
    
    if (c[0]!= '\n' )
    {
        s[i][j] = c[0];
        j++;
    } else if (c[0]== '\n')
    {
        s[i][j]= '\0';
        i++;
        j=0;

    }
    
}

for (int z=0; z<3 ; z++)
{

printf("%s\n", s[z]);

}

fclose(inptr);




    
    
    
    
    
    
    
    

    
    
    
    return 0;
}