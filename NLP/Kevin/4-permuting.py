#Generate the alphabet
lst = [chr(i) for i in range( ord('A'), (ord('Z') + 1 ) ) ]
lst1 = [] 
for i  in range(26):
 lst1.append(chr(i+65)) 
print(lst)
print(lst1)

#python also permutes 
import random
import copy
lstPy  = copy.deepcopy(lst) #preserve the original list
random.shuffle(lst) #permute original list
for i in range(26):
 print(lstPy[i] + ' ' + lst[i]  + ' ' )

