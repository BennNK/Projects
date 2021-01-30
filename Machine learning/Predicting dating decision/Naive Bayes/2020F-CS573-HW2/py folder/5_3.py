import numpy as np
import pandas as pd
import matplotlib.pyplot as plt





nbins = 5
x = []

y = []

z = []



def nbc(df):
       
    
   
    for label in range (2):
        for columns_to_search in df.columns.drop(['decision']):
            if columns_to_search in ['gender', 'samerace']:
                max_bin = 2
            elif columns_to_search in ['field']:
                max_bin = 210
            elif columns_to_search in ['race','race_o']:
                    max_bin = 5
            else:
                max_bin = nbins
                
            Prob_dict[label][columns_to_search] = []
            for i in range (max_bin):
                n_this_att = len( df[(df[columns_to_search] == i) & (df['decision'] == label)]) + 1
                
                Prob_dict[label][columns_to_search].append(n_this_att/(len(df[df['decision'] == label]) + max_bin))            
            
        Prob_dict[label].update({'prob_label' : (len(df[df['decision'] == label]))/len(df.index)})
    
            
    return  0


def tests(df):
    
        df['prediction'] = 0
        
        n_match = 0
        for i in range(len(df)):
            
            #df.to_csv('dating-binned3.csv', index=False)
            
            p_0 = Prob_dict[0]['prob_label']
            p_1 = Prob_dict[1]['prob_label']
           
            
            for j in df.columns.drop(['decision', 'prediction']):
                
                #print (i, j, 'p0', Prob_dict[0][j], df.iloc[i].loc[j] )
                p_0 = p_0*Prob_dict[0][j][df.iloc[i].loc[j]]
                p_1 = p_1*Prob_dict[1][j][df.iloc[i].loc[j]]
            
            if p_0 < p_1:
                df.iloc[i, df.columns.get_loc('prediction')] = 1
            if p_0 > p_1:
                df.iloc[i, df.columns.get_loc('prediction')] = 0
            if df.iloc[i].loc['prediction'] == df.iloc[i].loc['decision']:
                n_match += 1
            
                
        accu = n_match/len(df)
        #print (accu)       
            
        return accu
    
    
for t_frac in [0.01, 0.1, 0.2, 0.5, 0.6, 0.75, 0.9, 1]:
    
    Prob_dict_label_0 = dict()
    Prob_dict_label_1 = dict()
    Prob_dict = (Prob_dict_label_0, Prob_dict_label_1)
        
    training_set=pd.read_csv('trainingSet.csv',sep=',')
    training_set=training_set.sample(frac = t_frac,  random_state = 47)
    test_set=pd.read_csv('testSet.csv',sep=',')
    
    nbc(training_set)
    test_acc = tests(test_set)
    train_acc = tests(training_set)    
    
    x.append(t_frac)
    y.append(test_acc)
    z.append(train_acc) 
    
    test_acc = "{:.2f}".format(test_acc)
    train_acc = "{:.2f}".format(train_acc)
    
    print ("f :", t_frac)
    print ('Training Accuracy:', train_acc)
    print ('Test Accuracy:', test_acc)
    
    
    
#plot
fig,ax = plt.subplots()
plt.xlabel('f')
plt.ylabel('accuracy')  
plt.plot(x,y,"x-",label="test accuracy")
plt.plot(x,z,"+-",label="training accuracy")
plt.legend(loc=[0.5, 1], prop={'size': 12}) 






    