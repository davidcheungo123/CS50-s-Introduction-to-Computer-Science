#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>


int main(void) 
{

    string input_text= get_string("Text: ");
    int words= 0 , letters = 0, sentences =0 ;
    int n = strlen(input_text);
    int i, j;
    
    for (i = 0; i <= n ; i++)
    {
        
        
    
       if (n!=0)
       {
           if (input_text[i]== ' ' || input_text[i]== '\0')
           {
               words++;
           }
       } 
       else 
       {
           words=0;
       }
    
       if (input_text[i]>= 'A' && input_text[i]<= 'Z')
       {
        
        letters++;
       } 
       else if (input_text[i] >= 'a' && input_text[i] <= 'z')
       {
           letters++;
       }
       if (input_text[i]=='.' || input_text[i]=='!' || input_text[i]=='?')
       {
    
       if (input_text[i]=='.' && input_text[i-1]== 'r' && input_text[i-2]=='M'){
       break;
       } else if (input_text[i]=='.' && input_text[i-1]== 's' && input_text[i-2]=='r' && input_text[i-3]=='M'){
       break;
       } else if (input_text[i]=='.' && input_text[i-1]== 's' && input_text[i-2]=='M'){
       break;
       } else if (input_text[i]=='.' && input_text[i-1]== 's' && input_text[i-2]=='s' && input_text[i-3]=='i' && input_text[i-4]=='M'){
       break;
       }
    
    sentences++;
    
    }
    
    
    }


    
    
    
    float L = (100/ (float)words)*(letters), S= (100/(float)words)*(sentences);
    
    
    float index= 0.0588*L-0.296*S-15.8;
    
    int index_1 = round(index);
    
    
    
    
    if (index_1<1){
    printf("Before Grade 1\n");
    } else if (index_1>=16){
    printf("Grade 16+\n");
    } else {
    printf("Grade %i\n", index_1);
    }
    
    
    
    
}
