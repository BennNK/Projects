import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

x = []

y = []

z = []



for N in [2,5,10,50,100,200]:

    nbins = N
    
#discretize
    df=pd.read_csv('dating.csv',sep=',')


    for columns_to_search in df.columns.drop(['gender','race', 'race_o', 'samerace', 'field', 'decision' ]):
        this_column = np.array(df[columns_to_search])
        
        this_column_min = 0
        this_column_max = 10
        
        if columns_to_search in ['age', 'age_o']:
            this_column_min = 18
            this_column_max = 58
        
        if columns_to_search in ['attractive_important','sincere_important','intelligence_important','funny_important','ambition_important','shared_interests_important','pref_o_attractive','pref_o_sincere','pref_o_intelligence','pref_o_funny','pref_o_ambitious','pref_o_shared_interests']:
            this_column_min = 0
            this_column_max = 1
       
        if columns_to_search in ['interests_correlate']:
            this_column_min = -1
            this_column_max = 1
        
        
        bin_width=(this_column_max-this_column_min)/nbins
        bins = np.arange (this_column_min + bin_width, this_column_min+nbins*bin_width, bin_width)
        
        this_column_binned = np.digitize (this_column, bins, right = True)
        df[columns_to_search] = this_column_binned
        
    #df.to_csv('dating-binned2.csv', index=False)
#end of discretize

#split
    test_set = df.sample(frac = 0.2,  random_state = 47)
    training_set = df.drop(test_set.index)
#end of split
    
#train and test   
        
    Prob_dict_label_0 = dict()
    Prob_dict_label_1 = dict()
    Prob_dict = (Prob_dict_label_0, Prob_dict_label_1)
    
    t_frac = 1
    
    
    def nbc(t_frac):
           
        df = training_set.sample(frac = t_frac,  random_state = 47)
       
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
        
        
        
    nbc(t_frac)
    test_acc = tests(test_set)
    train_acc = tests(training_set)
    
    x.append(nbins)
    y.append(test_acc)
    z.append(train_acc)   
    
    
    
    test_acc = "{:.2f}".format(test_acc)
    train_acc = "{:.2f}".format(train_acc)
    print ('Bin size:', nbins)
    print ('Training Accuracy:', train_acc)
    print ('Testing Accuracy:', test_acc)

#plot
fig,ax = plt.subplots()
plt.xlabel('bin number')
plt.ylabel('accuracy')  
plt.plot(x,y,"x-",label="test accuracy")
plt.plot(x,z,"+-",label="training accuracy")
plt.legend(loc=[0.5, 1], prop={'size': 12})  
