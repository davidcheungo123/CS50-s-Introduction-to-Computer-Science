#include <stdio.h>
#include <cs50.h>
#include <math.h>

long checkfunction(void);

int main(void)
{
    long n=checkfunction();
    long MC_1 = (n/1000000000000000);
    long AE_1 = (n/100000000000000)%10;
    long AE_2 = (n/10000000000000) %100%10;
    long VI_1 = (n/1000000000000)  %1000%100%10;
    long i=10;
    long j=1;
    long digits_2=0;
    long digits_1=0;
    int k=0;
    int z=0;
    int Boolean_test;
    
    do{
        digits_2=((n/i) % 10)*2 ;
        k= (digits_2/10) + (digits_2%10); 
        z +=k ;
        i *=100;
    } while (n/i != 0);
    
    k=0;
    
    do{
        digits_1=(n/j)%10;
        k += digits_1;
        j *=100;
    } while (n/j !=0);
    
    Boolean_test= (z+k) %10;
    
    if (n>=10000000000000000 || n<1000000000000){
    printf("INVALID\n");
    } else if (Boolean_test ==0){
    
    if (MC_1!=0){
        
    if (MC_1 ==5 ) {
    if (AE_1==1 || AE_1==2|| AE_1==3 ||AE_1==4|| AE_1==5){
    printf("MASTERCARD\n");

    } else {
    printf("INVALID\n");
    }
    } else if (MC_1 ==4){
            
        printf("VISA\n");
        
        } else {
        printf("INVALID\n");
    }
    
    }
    
    

    
    
    if (MC_1==0 && AE_1 != 0){
        
        if (AE_1 == 3 && AE_2 ==4){
            
        printf("AMEX\n");
        
        } else if (AE_1==3 && AE_2 ==7) {
        
        printf("AMEX\n");
        } else {
            printf("INVALID\n");
        }
    }
    
    if (MC_1==0 && AE_1==0 && AE_2==0  ){
        if (VI_1 ==4){
            printf("VISA\n");
        } else {
    printf("INVALID\n");
    } 
    }
    } else {
        printf("INVALID\n");
    }
}



long checkfunction(void){
    long n;
     n = get_long("Number: ");

    return n;
}
