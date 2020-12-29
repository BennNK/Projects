import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

training_set=pd.read_csv('trainingSet.csv',sep=',')
test_set=pd.read_csv('testSet.csv',sep=',')

Prob_dict_label_0 = dict()
Prob_dict_label_1 = dict()


t_frac = 1
nbins = 5

def nbc(t_frac):
    
   
    df = training_set.sample(frac = t_frac,  random_state = 47)
   
      
    for columns_to_search in df.columns.drop(['decision']):
        if columns_to_search in ['gender', 'samerace']:
            max_bin = 2
        elif columns_to_search in ['field']:
            max_bin = 210
        else:
            max_bin = nbins
            
        Prob_dict_label_0[columns_to_search] = []
        for i in range (max_bin):
            n_this_att = len( df[(df[columns_to_search] == i) & (df['decision'] == 0)]) + 1
            
            Prob_dict_label_0[columns_to_search].append(n_this_att/(len(df[df['decision'] == 0]) + max_bin))
            
            
    for columns_to_search in df.columns.drop(['decision']):
        if columns_to_search in ['gender', 'samerace']:
            max_bin = 2
        elif columns_to_search in ['field']:
            max_bin = 210
        else:
            max_bin = nbins
            
        Prob_dict_label_1[columns_to_search] = []    
        for i in range (max_bin):
            temp = len( df[(df[columns_to_search] == i) & (df['decision'] == 1)]) + 1
           
            Prob_dict_label_1[columns_to_search].append(temp/(len(df[df['decision'] == 1]) + max_bin))
            
    Prob_dict_label_0.update({'prob_label_0' : (len(df[df['decision'] == 0]))/len(df.index)})
    Prob_dict_label_1.update({'prob_label_1' : (len(df[df['decision'] == 1]))/len(df.index)})
            
 
    return  0

nbc(t_frac)

# print (Prob_dict_label_0, '\n\n\n\n')

# print (Prob_dict_label_1)
T = np.asarray (test_set)
#print (T)
result = []
for row in T:
    p0 = Prob_dict_label_0['prob_label_0']
    q0 = Prob_dict_label_1['prob_label_1']
    c=0
    for name in test_set.columns:
        if name == 'decision':
            continue
        a = row[c]
        
        p0*=Prob_dict_label_0[name][a]
        q0*=Prob_dict_label_1[name][a]
          
        c+=1
           
    if p0>q0:
        result.append(0)
    else:
        result.append(1)
labels = test_set['decision'].tolist()

count = 0
for i in range(len(test_set)):
    if result[i] == labels [i]:
        count = count + 1
Accu = count/len(test_set)

print (Accu)

        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        


#print ( Prob_dict_label_0)