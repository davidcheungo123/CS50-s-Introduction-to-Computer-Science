import csv
import cs50
from sys import argv, exit


db=cs50.SQL("sqlite:///students.db")

if len(argv)!=2:
    
    print("error")
    exit(1)
    

with open(argv[1],"r") as inputfile:
    
    reader= csv.DictReader(inputfile)
    

    
    for row in reader:
        
        
        
        house = row["house"]
        birth = row["birth"]
            
        name = row["name"]
            
        splitname = name.split(" ")
        
        
            
        if len(splitname)==2:
            
            firstname= splitname[0]
            lastname =  splitname[1]
            middlename= None
            


            
        elif len(splitname)==3:
            firstname= splitname[0]
            middlename= splitname[1]
            lastname= splitname[2]
            
        db.execute("INSERT INTO students(first,middle,last,house, birth) VALUES (?,?,?,?,?)", firstname, middlename, lastname, house, birth)
            
