#include <stdio.h>
#include <cs50.h>

int positive_input(void);

int main(void)
{

int n= positive_input();
for (int i=1; i<n+1 ;i++)
{
for (int j=0;j<n-i;j++)
{
printf(" ");
}
for (int k=0;k<i;k++)
{
printf("#");
}
printf("  ");
for (int z=0;z<i;z++)
{
printf("#");
}

printf("\n");
}

}


int positive_input(void)
{
int n;
do
{
n= get_int("Height: ");
}
while (n<1 || n>8);

return n;
}