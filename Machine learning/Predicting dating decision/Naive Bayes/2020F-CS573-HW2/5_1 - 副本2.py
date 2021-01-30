import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

training_set=pd.read_csv('trainingSet.csv',sep=',')
test_set=pd.read_csv('testSet.csv',sep=',')


Prob_dict_label_0 = dict()
Prob_dict_label_1 = dict()
Prob_dict = (Prob_dict_label_0, Prob_dict_label_1)

t_frac = 1
nbins = 5

def nbc(t_frac):
    
   
    df = training_set.sample(frac = t_frac,  random_state = 47)
   
    for label in range (2):
        for columns_to_search in df.columns.drop(['decision']):
            if columns_to_search in ['gender', 'samerace']:
                max_bin = 2
            elif columns_to_search in ['field']:
                max_bin = 210
            else:
                max_bin = nbins
                
            Prob_dict[label][columns_to_search] = []
            for i in range (max_bin):
                n_this_att = len( df[(df[columns_to_search] == i) & (df['decision'] == label)]) + 1
                
                Prob_dict[label][columns_to_search].append(n_this_att/(len(df[df['decision'] == label]) + max_bin))            
            
        Prob_dict[label].update({'prob_label' : (len(df[df['decision'] == label]))/len(df.index)})
    
            
    return  0

nbc(t_frac)

print (Prob_dict_label_0, '\n\n\n\n')

print (Prob_dict_label_1)
T = np.asarray (test_set)
#print (T)
result = []
for row in T:
    p0 = Prob_dict[0]['prob_label']
    q0 = Prob_dict[1]['prob_label']
    c=0
    for name in test_set.columns:
        if name == 'decision':
            continue
        a = row[c]
        
        p0*=Prob_dict[0][name][a]
        q0*=Prob_dict[1][name][a]
          
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