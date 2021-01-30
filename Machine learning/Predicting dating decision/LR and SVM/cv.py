import numpy as np
import pandas as pd
import math
import matplotlib.pyplot as plt
import scipy.stats as sp





NBC_train_acc = []
NBC_train_err = []
NBC_test_acc = []
NBC_test_err = []

LR_train_acc = []
LR_train_err = []
LR_test_acc = []
LR_test_err = []


SVM_train_acc = []
SVM_train_err = []
SVM_test_acc = []
SVM_test_err = []

F = [0.025, 0.05, 0.075, 0.1, 0.15, 0.2]



#NBC constants etc
Prob_dict_label_0 = dict()
Prob_dict_label_1 = dict()
Prob_dict = (Prob_dict_label_0, Prob_dict_label_1)
nbins = 5



#NBC functions
def nbc_tests(df):
    
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




def nbc(trainingSet, testSet):

        
       
    df = trainingSet.copy()
   
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
        
        
    test_copy = testSet.copy()    
    test_acc = nbc_tests(test_copy)
    train_acc = nbc_tests(df)
    
    Acc = [train_acc,test_acc]
        
     
    return  Acc






#lr
def lr(trainingSet, testSet):
   # print('lr',testSet)
    tol = 0.00001
    lamda = 0.01
    step_size = 0.01
    df = trainingSet.copy()

    n_att = len(df.columns)
    n_iter = 500
    
    df.insert(0, 'intercept', 1)
    df_no_label = df.iloc[:, :-1]
    df_no_label_matrix = df_no_label.to_numpy()
    w = np.zeros(n_att)
    y_i = df.loc[:,'decision']
    y_i = y_i.values
    #print (y_i)
    
    N = len(df)
    #print (N)
    
    for n in range(n_iter):
        y_i_hat = np.zeros(N)
        for i in range(N):
            # print (w)
            # print (df_no_label_matrix[i])
            
            #print ('i',i, 'n',n)
            product = np.dot(w,df_no_label_matrix[i])
            #print (product)
            if product>50:
                y_i_hat[i] = 1
            elif product<-50:
                y_i_hat[i] = 0
            else:
                y_i_hat[i] = 1/(1+math.exp(0-product))
            #print (y_i_hat[i])
            
        
        gradients = np.zeros(n_att)
        
        
        #new method
        
        y_i_temp = y_i_hat - y_i
        
        gradients = np.matmul(y_i_temp,df_no_label_matrix) + lamda * w
 
        #end of new method
        
        
        
        descent = step_size *  gradients
        distance = np.linalg.norm(descent)
        if distance < tol:
            break
        w = w - descent
        #print (n, distance)
        #print (w)
      
    predicted_labels = np.zeros(N)
    miss_classification_count = 0
    for i in range(N):
        product = np.dot(w,df_no_label_matrix[i])

        if product>50:
            p = 1
        elif product<-50:
            p = 0
        else:
            p = 1/(1+math.exp(0-product))
        
        if p>0.5:
            predicted_labels[i] = 1
        
        if predicted_labels[i] != y_i[i]:
            miss_classification_count += 1
            
    train_acc = 1 - miss_classification_count/N
    # print ('Training Accuracy LR:',acc)
    # np.savetxt("predicted_labels_train.csv", predicted_labels, delimiter=",")
    
    #test

    df = testSet.copy()
    df.insert(0, 'intercept', 1)
    df_no_label = df.iloc[:, :-1]
    df_no_label_matrix = df_no_label.to_numpy()
    
    y_i = df.loc[:,'decision']
    y_i = y_i.values
    N = len(df)
    
    predicted_labels = np.zeros(N)
    miss_classification_count = 0
    for i in range(N):
        product = np.matmul(w,df_no_label_matrix[i])

        if product>50:
            p = 1
        elif product<-50:
            p = 0
        else:
            p = 1/(1+math.exp(0-product))
        
        if p>0.5:
            predicted_labels[i] = 1
        
        if predicted_labels[i] != y_i[i]:
            miss_classification_count += 1
            
    test_acc = 1 - miss_classification_count/N
    # print ('Testing Accuracy LR:',acc)
    # np.savetxt("test_labels.csv", predicted_labels, delimiter=",")
    
    Acc = [train_acc,test_acc]
        
    
    return Acc



#svm
def svm(trainingSet, testSet):
    #print('svm',testSet)
    # print('train',trainingSet)
    # print('test',testSet)
    
    tol = 0.00001
    lamda = 0.01
    step_size = 0.5
    df = trainingSet.copy()
    
    n_att = len(df.columns)
    N = len(df)
    n_iter = 500
    
    df.insert(0, 'intercept', 1)
    df_no_label = df.iloc[:, :-1]
    df_no_label_matrix = df_no_label.to_numpy()
    w = np.zeros(n_att)
    y_i = df.loc[:,'decision']
    y_i = y_i.values
    for i in range(N):
        if y_i[i] == 0:
            y_i[i] = -1
    
    
    for n in range(n_iter):
        
        y_i_hat = np.zeros(N)
        
        for i in range(N):
             y_i_hat[i] = np.dot(w,df_no_label_matrix[i])
        
        gradients = np.zeros(n_att)
        
        
        
        #new method
        y_i_temp = y_i.copy()
        for i in range(N):
            if y_i[i] * y_i_hat[i] >= 1 : 
                y_i_temp[i] = 0
        
        gradients = N * lamda * w - np.matmul(y_i_temp,df_no_label_matrix)
        gradients = gradients/N
        
        #end of new method
        
        
        


        
        descent = step_size * gradients
        distance = np.linalg.norm(descent)
        if distance < tol:
            break
        w = w - descent
        #print (n, distance)
        
    predicted_labels = np.ones(N)
    miss_classification_count = 0
    for i in range(N):
        if np.dot(w,df_no_label_matrix[i]) < 0:
            predicted_labels [i] = -1
        
        if predicted_labels[i] != y_i[i]:
            miss_classification_count += 1
            
    train_acc = 1 - miss_classification_count/N
    #print ('Training Accuracy SVM:',acc)
    #np.savetxt("SVM_predicted_labels_train.csv", predicted_labels, delimiter=",")
    
    
    
    #test
    df = testSet.copy()
    
    n_att = len(df.columns)
    N = len(df)
    
    df.insert(0, 'intercept', 1)
    df_no_label = df.iloc[:, :-1]
    df_no_label_matrix = df_no_label.to_numpy()
    y_i = df.loc[:,'decision']
    y_i = y_i.values
    for i in range(N):
        if y_i[i] == 0:
            y_i[i] = -1
            
    predicted_labels = np.ones(N)
    miss_classification_count = 0
    for i in range(N):
        if np.dot(w,df_no_label_matrix[i]) < 0:
            predicted_labels [i] = -1
        
        if predicted_labels[i] != y_i[i]:
            miss_classification_count += 1
            
    test_acc = 1 - miss_classification_count/N
    #print ('Testing Accuracy SVM:',acc)
    #np.savetxt("SVM_predicted_labels_test.csv", predicted_labels, delimiter=",")        
    
    Acc = [train_acc,test_acc]
    
    return Acc  
        
        
#---------------main------------

#pre-process data for NBC
df=pd.read_csv('dating-full.csv',sep=',')

#df=pd.read_csv('C:\\Users\\Ben\\Desktop\\cs573\\hw2\\2020F-CS573-HW2\\123.csv',sep=',')

n_row=len(df)

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

#print ('Quotes removed from',count_of_changed_cells,'cells \n')


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

#print ('Standardized',count_of_changed_cells,'cells to lower case \n')


#1(iii)

columns_to_search = ['gender', 'race', 'race_o', 'field']
values_to_search = ['male', 'European/Caucasian-American', 'Latino/Hispanic American', 'law']

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
        #        print ('Value assigned for', value, 'in column', column, ':', df.loc[i-1,column], '.')
                
    df.loc[i,column] = int(mapped_val)
    
        

#1(iv)

df['total_participant'] = df['attractive_important'] + df['sincere_important'] + df['intelligence_important'] + df['funny_important'] + df['ambition_important'] + df['shared_interests_important']
df['total_partner'] = df['pref_o_attractive'] + df['pref_o_sincere'] + df['pref_o_intelligence'] + df['pref_o_funny'] + df['pref_o_ambitious'] + df['pref_o_shared_interests']
df[['attractive_important','sincere_important','intelligence_important','funny_important','ambition_important','shared_interests_important']] = df[['attractive_important','sincere_important','intelligence_important','funny_important','ambition_important','shared_interests_important']].div(df.total_participant, axis=0)
df[['pref_o_attractive','pref_o_sincere','pref_o_intelligence','pref_o_funny','pref_o_ambitious','pref_o_shared_interests']] = df[['pref_o_attractive','pref_o_sincere','pref_o_intelligence','pref_o_funny','pref_o_ambitious','pref_o_shared_interests']].div(df.total_partner, axis=0)

# for i in ['attractive_important','sincere_important','intelligence_important','funny_important','ambition_important','shared_interests_important','pref_o_attractive','pref_o_sincere','pref_o_intelligence','pref_o_funny','pref_o_ambitious','pref_o_shared_interests' ]:
#     print ('Mean of', i, ':', round(df[i].mean() , 2))

df = df.drop(['total_participant', 'total_partner'], axis=1)



#binning

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
    
    # print (columns_to_search, ':', dups)


    df.to_csv('dating-binned.csv', index=False)




#end 

df = pd.read_csv('trainingSet.csv',sep=',')
df_nbc = pd.read_csv('dating-binned.csv', sep=',', nrows=6500)
df = df.sample(frac = 1,  random_state = 18)
df_nbc = df_nbc.sample(frac = 1,  random_state = 18)
df = df.reset_index(drop=True)
df_nbc = df_nbc.reset_index(drop=True)
S = np.array_split(df, 10)
S_nbc = np.array_split(df_nbc, 10)


for t_frac in F:
    print ('f',t_frac)
    nbc_train_acc = []
    nbc_test_acc = []
    lr_train_acc = []
    lr_test_acc = []
    svm_train_acc = []
    svm_test_acc = []
    
    
    
    for i in range(10):
        print ('i',i)
        test_set = S[i]
        #print ('test_set_lr',test_set_lr)
        #print ('test_set_svm',test_set_svm)
        test_set_nbc = S_nbc[i]
        S_c = df.drop(S[i].index)
        S_c_nbc = df_nbc.drop(S_nbc[i].index)
        training_set = S_c.sample(frac = t_frac,  random_state = 32)
        #print ('training_set_lr',training_set_lr)
        #print('training_set_svm',training_set_svm)
        training_set_nbc = S_c_nbc.sample(frac = t_frac,  random_state = 32)
        
        nbc_acc = nbc(training_set_nbc, test_set_nbc)
        #print ('t_frac', t_frac, 'i',i,'nbc_acc',nbc_acc)
        
        svm_acc = svm(training_set, test_set)
        
        lr_acc = lr(training_set, test_set)
        
        nbc_train_acc.append(nbc_acc[0])
        nbc_test_acc.append(nbc_acc[1])
        
        lr_train_acc.append(lr_acc[0])
        lr_test_acc.append(lr_acc[1])
        
        svm_train_acc.append(svm_acc[0])
        svm_test_acc.append(svm_acc[1])
        
    NBC_train_acc.append(np.mean(nbc_train_acc))
    NBC_train_err.append(np.std(nbc_train_acc)/math.sqrt(10))
    NBC_test_acc.append(np.mean(nbc_test_acc))
    NBC_test_err.append(np.std(nbc_test_acc)/math.sqrt(10))
    #print('NBC_train_acc',NBC_train_acc,'NBC_train_err',NBC_train_err,'NBC_test_acc',NBC_test_acc,'NBC_test_err',NBC_test_err)
    
    LR_train_acc.append(np.mean(lr_train_acc))
    LR_train_err.append(np.std(lr_train_acc)/math.sqrt(10))
    LR_test_acc.append(np.mean(lr_test_acc))
    LR_test_err.append(np.std(lr_test_acc)/math.sqrt(10))
    
    
    SVM_train_acc.append(np.mean(svm_train_acc))
    SVM_train_err.append(np.std(svm_train_acc)/math.sqrt(10))
    SVM_test_acc.append(np.mean(svm_test_acc))
    SVM_test_err.append(np.std(svm_test_acc)/math.sqrt(10))
    


#plot
F_NBC = [x*9*650 for x in F]

F = [x*9*520 for x in F]


fig,ax = plt.subplots()
plt.xlabel('sample size')
plt.ylabel('accuracy') 

plt.plot(F_NBC,NBC_train_acc,label="NBC_train_acc")
plt.plot(F_NBC,NBC_test_acc,label="NBC_test_acc")
plt.errorbar(F_NBC,NBC_train_acc,yerr=NBC_train_err,fmt='o',ecolor='r',color='b',elinewidth=2,capsize=4)
plt.errorbar(F_NBC,NBC_test_acc,yerr=NBC_test_err,fmt='o',ecolor='r',color='b',elinewidth=2,capsize=4)

plt.plot(F,LR_train_acc,label="LR_train_acc")
plt.plot(F,LR_test_acc,label="LR_test_acc")
plt.errorbar(F,LR_train_acc,yerr=LR_train_err,fmt='o',ecolor='r',color='b',elinewidth=2,capsize=4)
plt.errorbar(F,LR_test_acc,yerr=LR_test_err,fmt='o',ecolor='r',color='b',elinewidth=2,capsize=4)

plt.plot(F,SVM_train_acc,label="SVM_train_acc")
plt.plot(F,SVM_test_acc,label="SVM_test_acc")
plt.errorbar(F,SVM_train_acc,yerr=SVM_train_err,fmt='o',ecolor='r',color='b',elinewidth=2,capsize=4)
plt.errorbar(F,SVM_test_acc,yerr=SVM_test_err,fmt='o',ecolor='r',color='b',elinewidth=2,capsize=4)




plt.legend(loc=[0.5, 1], prop={'size': 12}) 
    
    
#pairwise t test of SVM and LR accuracies, both training and testing

# print (LR_train_acc)
# print (SVM_train_acc)
# print (LR_test_acc)
# print (SVM_test_acc)

training_t_test = sp.ttest_rel(LR_train_acc, SVM_train_acc)
test_t_test = sp.ttest_rel(LR_test_acc, SVM_test_acc)



print ('t statistics for training', training_t_test)
print ('t statistics for test', test_t_test)


       
    
    




       


    