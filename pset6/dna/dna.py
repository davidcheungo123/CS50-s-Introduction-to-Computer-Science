from sys import argv, exit

import csv








def main():
    
    
    if len(argv)!=3:
        
        print("Usage: python dna.py data.csv sequence.txt")
        
        exit(1)
        
        
    continuous_numbers_count=[]
    
    csv_path= argv[1]
    txt_path= argv[2]
    
    with open(csv_path) as csv_file:
        
        reader= csv.reader(csv_file)
        
        
        all_sequences= next(reader)[1:]
        
        

            
        

    
        with open(txt_path) as txt_file:
            
            s= txt_file.read()
            
            for i in all_sequences:
                
                numbers= get_the_number(s,i)
                
                continuous_numbers_count.append(numbers)
                
                
                
            
                
            print_match(reader, continuous_numbers_count)

                
def get_the_number(s,sequence):
    
    
    s=s.lower()
    
    sequence=sequence.lower()

    lowest_index= []

    count=0

    count_number=1


    while sequence in s:

        lowest_index.append(s.find(sequence))
    
        s=s.replace(sequence, " "*len(sequence) , 1)
    
        count+=1
    


    num_vector=[]
    
    
    for j in range(len(lowest_index)):
    
        num_count=1
    

    
        z=0
    
        while j+z < len(lowest_index)-1:
        
        
            if int(lowest_index[j+z+1] - lowest_index[j+z]) == len(sequence) :
            
                z+=1
        
                num_count+=1
            
            else:
                break
        
        
        num_vector.append(num_count)
    

    return max(num_vector)
    
def print_match(reader, actual):
    
    for line in reader:
        
        person = line[0]
        values = [int(val) for val in line[1:]]
        
        if values == actual:
            print(person)
            return
        
    print("No match")
            
            
main()
            

    
    
    
        
        
    
    
    
    
    
    