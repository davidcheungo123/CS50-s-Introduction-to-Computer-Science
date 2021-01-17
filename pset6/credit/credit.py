from cs50 import get_string,  get_int
from math import floor
import re

    
def main():
    

    
    while True:
        
        s= get_int("Number: ")
        
        t= str(s)
        
        if len(t) <= 12 or len(t) >=17:
            
            print("INVALID")
            exit(1)
        
        if (function_initial(s)):
            break
    
    s= str(s)
    
    if (re.search("^34|37",s) and len(s)==15 ):
        
        print("AMEX")
        
    elif (re.search("^51|52|53|54|55",s) and len(s)==16):
        
        print("MASTERCARD")
        
    elif (re.search("^4",s) and (len(s)==13 or len(s)==16)):
        
        print("VISA")
        
    else:
        
        print("INVALID")
    


    
def ten_power(i):

    z=1
    
    for a in range(i):
        
        z*=10
    
    return z
    
def function_initial(s):
    
    total=0
    
    for i in range(8):
        
        z=  floor((s % ten_power(2*i+2)) / ten_power(2*i+1))
        
        z*=2
    
        x=  z % 10 +  floor( (z%100) / 10)
    
        total += x

    
    for j in range(8):
        
        if j==0:
            
            a= floor(s % ten_power(2*j+1))
            
        else:
            a= floor((s % ten_power(2*j+1)) / ten_power(2*j))
            
        
        total+= a
            
    
    
    
    
    if (total%10) != 0:
        
        print("INVALID")
        
        return False

        
    else:
        
        return True
    

main()
    


    
    
    



        


        
        
        

    



    
    



        
    
    
    
    
    