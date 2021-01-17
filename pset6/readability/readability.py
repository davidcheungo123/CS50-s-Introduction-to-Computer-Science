from cs50 import get_string

s = get_string("Text: ")

s_lower= s.lower()

letters_count= 0

words_count=0

sentences_count=0

for i in s_lower:
    
    
    if ord(i)>=97 and ord(i) <= 122:
        
        letters_count+=1
        
        
words_count = len(s_lower.split(' '))

    
if "mr." in s_lower:
        
    s_lower=s_lower.replace("mr.", '')
            
if "miss." in s_lower:
        
    s_lower= s_1.replace("miss.", '')
            
            
if "ms." in s_lower:
        
    s_lower= s_lower.replace("ms.", '')
            
if "mrs." in s_lower:
        
    s_lower= s_lower.replace("mrs.", '')
    
    
    
            
            
            
for i in s_lower:
    
    if i == '.' or i=='!' or i=='?':
        
        sentences_count+=1
        


Grade= round(0.0588*letters_count/(words_count/100) - 0.296*sentences_count/(words_count/100) -15.8 )


if Grade>=16:
    
    print("Grade 16+")
    
elif Grade<=1:
    
    print("Before Grade 1")
    
else:
    
    print(f"Grade {Grade}")
    







    
        
    



    


    






        
        





