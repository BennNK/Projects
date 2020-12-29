import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

df=pd.read_csv('dating.csv',sep=',')

nbins = 5

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

    dups = pd.DataFrame(df.pivot_table(index = [columns_to_search], aggfunc ='size'))
    
    n = nbins - 1
    dups = dups.reindex(range(n+1), fill_value= 0)   
    
    dups = dups.iloc[:,0].values
    
    print (columns_to_search, ':', dups)


    df.to_csv('dating-binned.csv', index=False)
    
    
    