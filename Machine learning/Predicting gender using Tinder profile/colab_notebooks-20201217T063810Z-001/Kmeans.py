
import pandas as pd
import numpy as np
import os
import nltk
import sys
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.naive_bayes import MultinomialNB
from sklearn.model_selection import train_test_split
from sklearn.model_selection import KFold
from scipy import sparse

import texthero as hero
from texthero import preprocessing
from nltk import FreqDist
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import silhouette_score
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
from sklearn import metrics
import nltk
# nltk.download('punkt')
# nltk.download('averaged_perceptron_tagger')
from collections import Counter


from mpl_toolkits.mplot3d import Axes3D
import math


pd.set_option('mode.chained_assignment', None)

np.set_printoptions(threshold=10)

F = [0.075, 0.2, 0.5,0.75, 1]
# F = [0.075]

profiles = pd.read_csv('profiles.csv',sep=',',nrows = 10000)
df = profiles
df.loc[df.sex == 'm', 'sex'] = 1
df.loc[df.sex == 'f', 'sex'] = 0



#clean essays (how?)
essays=['essay0','essay1','essay2','essay3','essay4','essay5','essay6','essay7','essay8','essay9']
# df = profiles[essays]
for i in essays:
    profiles[i] = hero.clean(profiles[i])
    profiles[i] = [n.replace('br','') for n in profiles[i]]




Test_ac = []
Test_er = []
Train_ac = []
Train_er = []




#different fraction of data
for t_frac , K in zip(F, [[50], [200], [200], [500], [500]]) :
    print('t_frac',t_frac)
    temp = profiles.sample(frac = t_frac,  random_state = 32)
    pf = temp.copy()
    
    
    test_ac = []
    train_ac = []
    
    
    
    
    #split training and testing
    S = np.array_split(pf, 10)
    for ite in range(10):
        print('ite', ite)
        
        testSet = S[ite]
        temp = pf.drop(testSet.index)
        trainingSet = temp.copy()
        
        #---------work on training data
        df = trainingSet[essays]
        #combine 9 essays of every person
        df['dumb'] = np.zeros(len(df))
        df['row essays'] = df['essay0'] + " " + df['essay1'] + " " + df['essay2'] + " " + df['essay3'] + " " + df['essay4'] + " " + df['essay5'] + " " + df['essay6'] + " " + df['essay7'] + " " + df['essay8'] + " " + df['essay9'] 
        df = df.drop(columns = essays)
        
        df_essays_per_person = df.drop(columns = ['dumb'])
        df_essays_per_person.to_csv('essays_per_person.csv', sep=',',  index=False)
        
        #combine all essays
        df_essay_all_persons = df.groupby('dumb')['row essays'].apply(' '.join).reset_index()
        df_essay_all_persons = df_essay_all_persons.drop(columns = ['dumb'])
        df_essay_all_persons.to_csv('essay_all_persons.csv', sep=',',  index=False)
        
        
        #build vocabulary array of df_essay_all_persons
        string = df_essay_all_persons.iloc[0]['row essays']
        
        
        tokens = nltk.word_tokenize(string)
        tags = nltk.pos_tag(tokens)
        voc_pos_dict = Counter( tag for word,  tag in tags)
        voc_list = list(voc_pos_dict.keys())
        
        
        
        
        
        #build vocabulary frequency dictionaries of each person
        dict_traing_each_person = []
        for i in range(len(df)):
            # print(i)
            string = df.iloc[i]['row essays']
            tokens = nltk.word_tokenize(string)
            tags = nltk.pos_tag(tokens)
            dict_ = Counter( tag for word,  tag in tags)
            dict_traing_each_person.append(dict_)
                
        #convert training data essays into word frequencies
        X_train = np.zeros((len(df), len(voc_list)))
        for i in range(len(df)):
            # print('0', i)
            for j in range(len(voc_list)):
                if voc_list[j] in dict_traing_each_person[i]:
                    X_train[i][j] = dict_traing_each_person[i][voc_list[j]]
        
        Y_train = trainingSet.loc[:,['sex']].values
        Y_train = Y_train.astype(int)
        Y_train = Y_train.T
        Y_train = Y_train.flatten()
        
                    
        #---------work on testSet
        df = testSet[essays]
        #combine 9 essays of every person
        df['dumb'] = np.zeros(len(df))
        df['row essays'] = df['essay0'] + " " + df['essay1'] + " " + df['essay2'] + " " + df['essay3'] + " " + df['essay4'] + " " + df['essay5'] + " " + df['essay6'] + " " + df['essay7'] + " " + df['essay8'] + " " + df['essay9'] 
        df = df.drop(columns = essays)
        
        df_essays_per_person = df.drop(columns = ['dumb'])
        df_essays_per_person.to_csv('essays_per_person.csv', sep=',',  index=False)
        
        
        #build vocabulary frequency dictionaries of each person
        dict_test_each_person = []
        for i in range(len(df)):
            # print('2',i)
            string = df.iloc[i]['row essays']
            tokens = nltk.word_tokenize(string)
            tags = nltk.pos_tag(tokens)
            dict_ = Counter( tag for word,  tag in tags)
            dict_test_each_person.append(dict_)
        
        
        #convert test data essays into word frequencies
        X_test = np.zeros((len(df), len(voc_list)))
        for i in range(len(df)):
            # print('3',i)
            for j in range(len(voc_list)):
                if voc_list[j] in dict_test_each_person[i]:
                    X_test[i][j] = dict_test_each_person[i][voc_list[j]]
        
        Y_test = testSet.loc[:,['sex']].values
        Y_test = Y_test.astype(int)
        Y_test = Y_test.T
        Y_test = Y_test.flatten()
        
        
        
        #----------PCA
        # Standardizing the features
        X_train = StandardScaler().fit_transform(X_train)
        # np.savetxt("X_train.csv", X_train, delimiter = ",")
        X_test = StandardScaler().fit_transform(X_test)
        
        pca = PCA(.95)
        pca.fit(X_train)
        
        X_train = pca.transform(X_train)
        X_test = pca.transform(X_test)
        
        aa =  pca.explained_variance_ratio_
        
        
        
        
        
        
        # #plot first three Principle components
        # x = X_train[:, 0]
        # y = X_train[:, 1]
        # z = X_train[:, 2]
        
        # group = Y_train
        # cdict = {0: 'red', 1: 'blue'}
        
        # fig = plt.figure()
        # ax = Axes3D(fig)
        # for g in np.unique(group):
        #     ix = np.where(group == g)
        #     ax.scatter(x[ix], y[ix], z[ix], c = cdict[g], label = g, s = 30, alpha=0.5)
        
        # ax.set_zlabel('Third Principle Component', fontdict={'size': 15})
        # ax.set_ylabel('Second Principle Component', fontdict={'size': 15})
        # ax.set_xlabel('First Principle Component', fontdict={'size': 15})
        
        # ax.legend()
        # plt.show()
        
        

        
        #------------kmeans
        
        
        sil_score_max = -1 #this is the minimum possible score
        
        distortions = []
        
            
            
            
            
            
        
        for i in K:

            # print(i)
            km = KMeans(
                n_clusters=i, init='random',  max_iter=300,
        
            ).fit(X_train)
            
            Cluster_train = km.labels_
            Cluster_test = km.predict(X_test)
            distortions.append(km.inertia_)
            sil_score = silhouette_score(X_train, Cluster_train)
            # print("s SCORE",i ,sil_score)
            k = i
        
        # print('sex_cluster',cluster_sex)
        
        # # plot
        # fig3, ax3 = plt.subplots()
        # plt.plot(K, distortions, marker='o')
        # plt.title('Fraction = ' + str(t_frac))
        # plt.xlabel('Number of clusters')
        # plt.ylabel('WC-SSD')
        # plt.show()
        
        
        
        
        
        
        #assign gender to each cluster
        cluster_sex_train = np.array([Cluster_train, Y_train])
        cluster_sex_train = cluster_sex_train.T
        
        cluster_sex_map = []
        for i in range(k):
            cluster = cluster_sex_train[cluster_sex_train[:,0] == i, :]
            sex = cluster[:,1]
            sex = np.mean(sex)
            # cluster_sex_map.append(sex)
            if sex >= 0.5:
                cluster_sex_map.append(1)
            else:
                cluster_sex_map.append(0)
        
        
        #look at testset and calculate sex prediction accuracy
        
        n_match = 0
        
        
        # for i in range(len(Cluster_test)):
        
        #     p = cluster_sex_map[Cluster_test[i]]
        #     rand_sex = np.random.binomial(1, p, 1)
            
        #     if rand_sex[0] == Y_test[i]:
        #         n_match += 1
                
        for i in range(len(Cluster_test)):
            if cluster_sex_map[Cluster_test[i]] == Y_test[i]:
                n_match += 1
        
        test_acc = n_match/len(Cluster_test)
        test_ac.append(test_acc)
        # print(test_acc)
        
        #look at training and calculate sex prediction accuracy
        n_match = 0
        for i in range(len(Cluster_train)):
            if cluster_sex_map[Cluster_train[i]] == Y_train[i]:
                n_match += 1
        
        train_acc = n_match/len(Cluster_train)
        train_ac.append(train_acc)
        # print(train_acc)
    
    
    #calculate mean of test and train acc and error after 10 fold CV 
    Test_ac.append(np.mean(test_ac))
    Test_er.append(np.std(test_ac)/math.sqrt(10))
    Train_ac.append(np.mean(train_ac))
    Train_er.append(np.std(train_ac)/math.sqrt(10))
    
    print('test_ac',test_ac)
    print('train_ac',train_ac)
    


#plot acc over number of samples
fig2, ax2 = plt.subplots()

plt.xlabel('Training Examples')
plt.ylabel('Model Accuracy')

n_samples = [element * 9000 for element in F]

plt.plot(n_samples,Test_ac,label="Test Accuracy")
plt.errorbar(n_samples,Test_ac,yerr=Test_er,fmt='o',ecolor='r',color='b',elinewidth=2,capsize=4)
print('Train_er',Train_er)
print('Test_er',Test_er)



plt.plot(n_samples,Train_ac,label="Training Accuracy")
plt.errorbar(n_samples,Train_ac,yerr=Train_er,fmt='o',ecolor='r',color='b',elinewidth=2,capsize=4)

plt.legend(loc=[0.5, 1], prop={'size': 12}) 
























