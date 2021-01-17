#include "helpers.h"
#include <string.h>
#include <math.h>
#include <cs50.h>

int get_freq (int i, int j);

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{


    for (int i=0 ; i< height ; i++)
    {
        for (int j=0; j< width ; j++)
        {
           int total=image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
           int aver;
           
           if (total %3==2){
           aver = ceil((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3)+1;

           } else{
           aver = ceil((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3);
           
           }
        image[i][j].rgbtGreen =image[i][j].rgbtRed= image[i][j].rgbtBlue=   aver;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imagecopy[height][width];
    
    for (int i=0; i<height;i++)
    {
        for (int j=0; j<width;j++)
        {
            imagecopy[i][j].rgbtBlue= image[i][j].rgbtBlue;
            imagecopy[i][j].rgbtRed= image[i][j].rgbtRed;  
            imagecopy[i][j].rgbtGreen= image[i][j].rgbtGreen;
        }
    }
    
    for (int i=0 ; i< height ; i++)
    {
        for (int j=0; j< width/2 ; j++)
        {

            image[i][width-j-1].rgbtBlue= image[i][j].rgbtBlue;
            image[i][width-j-1].rgbtRed= image[i][j].rgbtRed;
            image[i][width-j-1].rgbtGreen= image[i][j].rgbtGreen;
            
        }
    }
    
        for (int i=0 ; i< height ; i++)
    {
        for (int j=width/2; j< width ; j++)
        {
            image[i][width-j-1].rgbtBlue= imagecopy[i][j].rgbtBlue;
            image[i][width-j-1].rgbtRed= imagecopy[i][j].rgbtRed;
            image[i][width-j-1].rgbtGreen= imagecopy[i][j].rgbtGreen;
            
        }

}
    return;
}

bool valid(int i, int j, int height , int width)
{
    return (i>=0 && i<height && j>=0 && j< width);
}

RGBTRIPLE get_blurred_pixel(int i, int j ,int height, int width, RGBTRIPLE image[height][width])
{
  int blueValue, redValue, greenValue ;
  blueValue= redValue = greenValue =0;
  int freq =0;
  
  for (int di = -1 ; di<= 1 ;di++)
  {
      for (int dj= -1 ;dj <= 1 ; dj++)          
      {
          int new_i= i+di; int new_j= j+ dj;
          
          if (valid(new_i,new_j,height,width))
          {
              freq++;
              
              blueValue+= image[new_i][new_j].rgbtBlue;
              redValue+=image[new_i][new_j].rgbtRed;
              greenValue+=image[new_i][new_j].rgbtGreen;
              
          }
          
      }
  }
  RGBTRIPLE blurred_pixel;
  
  blurred_pixel.rgbtBlue= round(blueValue / freq);
  blurred_pixel.rgbtRed= round(redValue / freq);
  blurred_pixel.rgbtGreen= round(greenValue / freq);
  
  
  
  return blurred_pixel;
  
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imagecopy[height][width];
    
     for (int i=0 ; i< height ; i++)
    {
        for (int j=0; j< width ; j++)
        {

         imagecopy[i][j]= get_blurred_pixel( i,  j, height, width, image);
        
        
        }
    }
    
         for (int i=0 ; i< height ; i++)
    {
        for (int j=0; j< width ; j++)
        {

         image[i][j]= imagecopy[i][j];
        
        
        }
    }
    
      
}




// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imagecopy[height+2][width+2];
    
    for (int i=0 ; i< height+2 ; i++)
    {
        for (int j=0; j < width+2; j++)
        {
            if (i==0 || j==0)
            {
                imagecopy[i][j].rgbtBlue=0;
                imagecopy[i][j].rgbtRed=0;
                imagecopy[i][j].rgbtGreen=0;
            } else if (i== height+1 || j == width+1)
            {
                imagecopy[i][j].rgbtBlue=0;
                imagecopy[i][j].rgbtRed=0;
                imagecopy[i][j].rgbtGreen=0;
            } else
            {
                imagecopy[i][j].rgbtBlue=image[i-1][j-1].rgbtBlue;
                imagecopy[i][j].rgbtRed=image[i-1][j-1].rgbtRed;
                imagecopy[i][j].rgbtGreen=image[i-1][j-1].rgbtGreen;
            }
            
            
        }
    }
    
    for (int i=1 ; i< height+1; i++)
    {

        
        
        for (int j=1 ; j< width+1 ; j++)
        {
        int G_x_Blue = round(-1*imagecopy[i-1][j-1].rgbtBlue+imagecopy[i-1][j+1].rgbtBlue+2*imagecopy[i][j+1].rgbtBlue+imagecopy[i+1][j+1].rgbtBlue-1*imagecopy[i+1][j-1].rgbtBlue-2*imagecopy[i][j-1].rgbtBlue);
        int G_x_Red= round(-1*imagecopy[i-1][j-1].rgbtRed+imagecopy[i-1][j+1].rgbtRed+2*imagecopy[i][j+1].rgbtRed+imagecopy[i+1][j+1].rgbtRed-1*imagecopy[i+1][j-1].rgbtRed-2*imagecopy[i][j-1].rgbtRed);
        int G_x_Green= round(-1*imagecopy[i-1][j-1].rgbtGreen+imagecopy[i-1][j+1].rgbtGreen+2*imagecopy[i][j+1].rgbtGreen+imagecopy[i+1][j+1].rgbtGreen-1*imagecopy[i+1][j-1].rgbtGreen-2*imagecopy[i][j-1].rgbtGreen);
       
        
        int G_y_Blue= round(-1*imagecopy[i-1][j-1].rgbtBlue-2*imagecopy[i-1][j].rgbtBlue-1*imagecopy[i-1][j+1].rgbtBlue+imagecopy[i+1][j+1].rgbtBlue+2*imagecopy[i+1][j].rgbtBlue+imagecopy[i+1][j-1].rgbtBlue);
        int G_y_Red= round(-1*imagecopy[i-1][j-1].rgbtRed-2*imagecopy[i-1][j].rgbtRed-1*imagecopy[i-1][j+1].rgbtRed+imagecopy[i+1][j+1].rgbtRed+2*imagecopy[i+1][j].rgbtRed+imagecopy[i+1][j-1].rgbtRed);
        int G_y_Green= round(-1*imagecopy[i-1][j-1].rgbtGreen-2*imagecopy[i-1][j].rgbtGreen-1*imagecopy[i-1][j+1].rgbtGreen+imagecopy[i+1][j+1].rgbtGreen+2*imagecopy[i+1][j].rgbtGreen+imagecopy[i+1][j-1].rgbtGreen);
        
         int G_2_Blue= round(sqrt((G_x_Blue)*(G_x_Blue)+(G_y_Blue)*(G_y_Blue)));
         int G_2_Red= round(sqrt((G_x_Red)*(G_x_Red)+(G_y_Red)*(G_y_Red)));
         int G_2_Green= round(sqrt((G_x_Green)*(G_x_Green)+(G_y_Green)*(G_y_Green)));
        
        if (G_2_Blue>255)
        {
            image[i-1][j-1].rgbtBlue=255;
        } else
        {
            image[i-1][j-1].rgbtBlue=G_2_Blue;
        }
        if ( G_2_Red>255)
        {
             image[i-1][j-1].rgbtRed=255;
        } else
        {
            image[i-1][j-1].rgbtRed=G_2_Red;
        }
        if (G_2_Green>255)
        {
            image[i-1][j-1].rgbtGreen=255;
        } else
        {
             image[i-1][j-1].rgbtGreen=G_2_Green;
        }
        
        
        
    
        }
        
        }
    
    return;
}

