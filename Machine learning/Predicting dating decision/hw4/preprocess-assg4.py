import pandas as pd
import numpy as np

df=pd.read_csv('dating-full.csv',sep=',',nrows=6500)

n_row=len(df)

#should remove 'race','race_o','field'
df = df.drop(columns=['race','race_o','field'])


#1(iii)

columns_to_search = ['gender']
values_to_search = ['male']

# columns_to_search = ('gender', 'field')
# values_to_search = ('male', 'law')
for column, value in zip(columns_to_search,values_to_search):
   
    df = df.sort_values(by=[column])
    df = df.reset_index(drop=True)
    
    found_index = df.loc[df[column] == value].index[0]
           
    mapped_val = 0
    i=0
    while i < n_row-1:
        
        this_cell = str(df.loc[i,column])
        next_cell = str(df.loc[i+1,column])
        if this_cell != next_cell:
            df.loc[i,column] = int(mapped_val)
            mapped_val += 1
            i += 1
        else:
            df.loc[i,column] = int(mapped_val)
            i += 1
            
        # if (i-1)==found_index:
        #         #print ('Value assigned for', value, 'in column', column, ':', df.loc[i-1,column], '.')
                
    df.loc[i,column] = int(mapped_val)


        

#1(iv)

df['total_participant'] = df['attractive_important'] + df['sincere_important'] + df['intelligence_important'] + df['funny_important'] + df['ambition_important'] + df['shared_interests_important']
df['total_partner'] = df['pref_o_attractive'] + df['pref_o_sincere'] + df['pref_o_intelligence'] + df['pref_o_funny'] + df['pref_o_ambitious'] + df['pref_o_shared_interests']
df[['attractive_important','sincere_important','intelligence_important','funny_important','ambition_important','shared_interests_important']] = df[['attractive_important','sincere_important','intelligence_important','funny_important','ambition_important','shared_interests_important']].div(df.total_participant, axis=0)
df[['pref_o_attractive','pref_o_sincere','pref_o_intelligence','pref_o_funny','pref_o_ambitious','pref_o_shared_interests']] = df[['pref_o_attractive','pref_o_sincere','pref_o_intelligence','pref_o_funny','pref_o_ambitious','pref_o_shared_interests']].div(df.total_partner, axis=0)

# for i in ['attractive_important','sincere_important','intelligence_important','funny_important','ambition_important','shared_interests_important','pref_o_attractive','pref_o_sincere','pref_o_intelligence','pref_o_funny','pref_o_ambitious','pref_o_shared_interests' ]:
#     print ('Mean of', i, ':', round(df[i].mean() , 2))

df = df.drop(['total_participant', 'total_partner'], axis=1)

#df.to_csv('dating22.csv', index=False)



#bin
nbins = 2

for columns_to_search in df.columns.drop(['gender', 'samerace', 'decision' ]):
    
    # this_column_min = 0
    # this_column_max = 10
    
    # if columns_to_search in ['age', 'age_o']:
    #     this_column_min = 18
    #     this_column_max = 58
    
    # if columns_to_search in ['attractive_important','sincere_important','intelligence_important','funny_important','ambition_important','shared_interests_important','pref_o_attractive','pref_o_sincere','pref_o_intelligence','pref_o_funny','pref_o_ambitious','pref_o_shared_interests']:
    #     this_column_min = 0
    #     this_column_max = 1
   
    # if columns_to_search in ['interests_correlate']:
    #     this_column_min = -1
    #     this_column_max = 1
    
    
    
    # Bins = np.linspace(this_column_min, this_column_max, nbins + 1, endpoint=True)
    # df[columns_to_search] = pd.cut(df[columns_to_search], Bins, labels=False, include_lowest = True)
    df[columns_to_search] = pd.cut(df[columns_to_search], 2, labels=False, include_lowest = True)
    


#sampling
#df.to_csv('dating2.csv', index=False)

test_set = df.sample(frac = 0.2,  random_state = 47)
training_set = df.drop(test_set.index)
test_set.to_csv('testSet.csv', sep=',',  index=False)
training_set.to_csv('trainingSet.csv', sep=',',  index=False)
    
























