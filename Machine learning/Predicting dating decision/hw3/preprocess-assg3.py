import numpy as np
import pandas as pd

df=pd.read_csv('dating-full.csv',sep=',',nrows=6500)

n_row=len(df)

#HW3 1(i)

#1(i)
count_of_changed_cells = 0

columns_to_search = ['race', 'race_o', 'field']
for column in columns_to_search:
    i=0
    while i < n_row:
        original_string = str(df.loc[i,column])
        stripped_string = original_string.strip("'")
        if original_string!=stripped_string:
            count_of_changed_cells+=1
            df.loc[i,column]=stripped_string
        i+=1

# print ('Quotes removed from',count_of_changed_cells,'cells \n')


#1(ii)
count_of_changed_cells = 0

columns_to_search = ['field']
for column in columns_to_search:
    i=0
    while i < n_row:
        original_string = str(df.loc[i,column])
        lower_cased_string = original_string.lower()
        if original_string!=lower_cased_string:
            count_of_changed_cells+=1
            df.loc[i,column]=lower_cased_string
        i+=1

# print ('Standardized',count_of_changed_cells,'cells to lower case \n')


# #1(iii)

# columns_to_search = ['gender', 'race', 'race_o', 'field']
# values_to_search = ['male', 'European/Caucasian-American', 'Latino/Hispanic American', 'law']

# # columns_to_search = ('gender', 'field')
# # values_to_search = ('male', 'law')
# for column, value in zip(columns_to_search,values_to_search):
   
#     df = df.sort_values(by=[column])
#     df = df.reset_index(drop=True)
    
#     found_index = df.loc[df[column] == value].index[0]
           
#     mapped_val = 0
#     i=0
#     while i < n_row-1:
        
#         this_cell = str(df.loc[i,column])
#         next_cell = str(df.loc[i+1,column])
#         if this_cell != next_cell:
#             df.loc[i,column] = int(mapped_val)
#             mapped_val += 1
#             i += 1
#         else:
#             df.loc[i,column] = int(mapped_val)
#             i += 1
            
#         if (i-1)==found_index:
#                 print ('Value assigned for', value, 'in column', column, ':', df.loc[i-1,column], '.')
                
#     df.loc[i,column] = int(mapped_val)
    
        

#1(iv)

df['total_participant'] = df['attractive_important'] + df['sincere_important'] + df['intelligence_important'] + df['funny_important'] + df['ambition_important'] + df['shared_interests_important']
df['total_partner'] = df['pref_o_attractive'] + df['pref_o_sincere'] + df['pref_o_intelligence'] + df['pref_o_funny'] + df['pref_o_ambitious'] + df['pref_o_shared_interests']
df[['attractive_important','sincere_important','intelligence_important','funny_important','ambition_important','shared_interests_important']] = df[['attractive_important','sincere_important','intelligence_important','funny_important','ambition_important','shared_interests_important']].div(df.total_participant, axis=0)
df[['pref_o_attractive','pref_o_sincere','pref_o_intelligence','pref_o_funny','pref_o_ambitious','pref_o_shared_interests']] = df[['pref_o_attractive','pref_o_sincere','pref_o_intelligence','pref_o_funny','pref_o_ambitious','pref_o_shared_interests']].div(df.total_partner, axis=0)

# for i in ['attractive_important','sincere_important','intelligence_important','funny_important','ambition_important','shared_interests_important','pref_o_attractive','pref_o_sincere','pref_o_intelligence','pref_o_funny','pref_o_ambitious','pref_o_shared_interests' ]:
#     print ('Mean of', i, ':', round(df[i].mean() , 2))

df = df.drop(['total_participant', 'total_partner'], axis=1)

# df.to_csv('dating.csv', index=False)


#end of HW3 1(i)


#HW3 1(ii)
for columns_to_search in ['gender','race','race_o','field']:
    
    df = df.sort_values(columns_to_search)
    colnames = df[columns_to_search].unique()
    colnames[::-1].sort()
    insert_loc=df.columns.get_loc(columns_to_search) + 1
    
    
    for i in range(colnames.size):
        this_colname = colnames[i] + ' in column ' + columns_to_search
        this_colname_short = colnames[i]
        #print (this_colname)
        
        if i == 0:
            if this_colname in ['female in column gender','Black/African American in column race','Other in column race_o','economics in column field']:
                mapped_vector = np.zeros(colnames.size - 1)
                print ('Mapped vector for', this_colname, ':', mapped_vector)
        
        
        
        else:
            
            df.insert(insert_loc, this_colname, 0)
            df.loc[df[columns_to_search] == this_colname_short, [this_colname]] = 1
        
            if this_colname in ['female in column gender','Black/African American in column race','Other in column race_o','economics in column field']:
                #print (i)
                mapped_vector = np.zeros(colnames.size - 1)
                #print (mapped_vector.size)
                mapped_vector[mapped_vector.size - i] = 1
                print ('Mapped vector for', this_colname, ':', mapped_vector)
    
    df = df.drop([columns_to_search], axis=1)
    
    
df.to_csv('dating.csv', index=False)

test_set = df.sample(frac = 0.2,  random_state = 25)
training_set = df.drop(test_set.index)
test_set.to_csv('testSet.csv', sep=',',  index=False)
training_set.to_csv('trainingSet.csv', sep=',',  index=False)
    
























