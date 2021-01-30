import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

df=pd.read_csv('dating.csv',sep=',')



for attributes_to_search in ['attractive_partner','sincere_partner','intelligence_parter','funny_partner','ambition_partner','shared_interests_partner']:
    success_rate_map= dict()   
    for i in df[attributes_to_search]:
        success_rate_map.update({i : 0})
           
    n_unique_val = len(success_rate_map) #number of unique values in this attribute c
    print ('number of distinct values for attribute', attributes_to_search, ':', n_unique_val)
    
    for key in success_rate_map:
        df_success = df.loc[(df[attributes_to_search] == key) & (df['decision'] == 1)]
        df_this_key = df.loc[df[attributes_to_search] == key]
        success_rate_map.update({key : len(df_success)/len(df_this_key)})
    
    
    #plot
    
    figsize = 11,9
    font1 = {'family' : 'Times New Roman','weight' : 'normal','size'   : 24}
    fig,ax = plt.subplots()

    plt.xlabel('value of this attribute')
    plt.ylabel('success_rate')
    ax.set_title(attributes_to_search)
    
    ax.scatter(success_rate_map.keys(),success_rate_map.values())
    