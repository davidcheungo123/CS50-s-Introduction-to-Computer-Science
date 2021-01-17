#include <stdio.h> 
#include <ctype.h>
#include <string.h>
#include <cs50.h>


int main(int argc, string argv[]){
    
    int key_len = strlen(argv[1]);
    int i=0, j=0,z=0, repeated=0;
    
    for (i=0;i<key_len;i++){
    if (argv[1][i]>= 'a' && argv[1][i]<= 'z'){
    j++;
    }
    if (argv[1][i]>= 'A' && argv[1][i] <='Z'){
    j++;
    }
    for (z=0;z<key_len-i;z++){
    if (argv[1][i] == argv[1][key_len-z]){
    repeated++;
    }
    }
    }
    
    if (argc != 2){
        printf("Usage: ./substitution key\n");
        return 1;
    }  else if ( j != 26){
        printf("Key must contain 26 characters.\n");
        return 1;
    } else if (argc ==1){
        printf("Usage: ./substitution key\n");
        return 1;
    } else if (repeated !=0 ){
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (j==26 && repeated==0){ 
    
    for (i = 0 ; i < key_len ; i++) {
        
        argv[1][i]= toupper(argv[1][i]);
 
    }
    
    string plaintext= get_string("plaintext:   ");
    

    
    int plain_len= strlen(plaintext);
    
    
    int cipgertext[plain_len];
    
    
     for (i = 0 ; i < plain_len ; i++) {
        
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z'){
            
            int image= plaintext[i]-'a';
            
            cipgertext[i] =  argv[1][image] + 32 ;
            
            
    } else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            
            int image= plaintext[i]-'A';
            
            cipgertext[i] =  argv[1][image] ;
            
    } else {
        
        cipgertext[i]= plaintext[i];
        
    }
    
         
    
         
    }
    
    printf("ciphertext:  ");
    
    for (i = 0 ; i < plain_len ; i++){
    
    printf("%c", (char)cipgertext[i]);
        
    }
    printf("\n");
    
    
    
    

    
    
    
    
    
    
    
    
    

    
    
    return 0;
    }
    
    
}
