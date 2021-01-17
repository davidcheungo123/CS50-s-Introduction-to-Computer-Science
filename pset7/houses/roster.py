import cs50
from sys import argv, exit
import csv

if len(argv)!=2:

    print("error")
    exit(1)

db= cs50.SQL("sqlite:///students.db")





lists= db.execute("SELECT * FROM students WHERE house= (?) ORDER BY last, first ", argv[1])


for row in lists:
    
    if row["middle"] is None:
        
        print(f"{row['first']} {row['last']}, born {row['birth']}" )
        
    if row["middle"] is not None:
        
        print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}" )
    

            
        
            
        

 
            
            









