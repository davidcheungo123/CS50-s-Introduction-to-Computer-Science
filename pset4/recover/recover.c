#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>
#define BLOCK_SIZE 512
#define FILE_NAME_SIZE 8
typedef uint8_t BYTE;

bool found_jpeg(BYTE s[]);

int main(int argc, char *argv[])
{






 if ( argc != 2)
 {
    printf("Usage: ./recover image\n");
    return 1;
 }

     FILE *infile= fopen(argv[1], "r");
     
if (infile == NULL)
{
    fclose(infile);
    printf("The forensic file cannot be opened\n");
    return 1;
}

BYTE buffer[BLOCK_SIZE];

bool found_first_jpeg= false;
int file_index=0;
FILE * outfile;

while (fread(buffer, 512, 1, infile))
{
    if (found_jpeg(buffer))
    {
    if (!found_first_jpeg)
    {
        found_first_jpeg= true;
    } 
    
    char filename[FILE_NAME_SIZE];
    
    sprintf(filename, "%03i.jpg", file_index);
    file_index++;
    
     outfile = fopen(filename, "w" );
    
    if (outfile == NULL)
    {
        return 1;
    }
    
    fwrite(buffer , BLOCK_SIZE, 1, outfile  );
    
    
    } else if (found_first_jpeg)
    {
    fwrite(buffer , BLOCK_SIZE, 1, outfile  );
    }
    
}

fclose(outfile);
fclose(infile);



}

bool found_jpeg(BYTE s[BLOCK_SIZE])
{
 
 return s[0] == 0xff && s[1]== 0xd8 && s[2]== 0xff && (s[3] & 0xf0)== 0xe0; 

}










     
 
