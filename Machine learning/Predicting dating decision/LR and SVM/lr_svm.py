import numpy as np
import pandas as pd
import math


#lr
def lr(trainingSet, testSet):
    tol = 0.00001
    lamda = 0.01
    step_size = 0.01
    df = trainingSet

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
            product = np.matmul(w,df_no_label_matrix[i])
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
            
    acc = "{:.2f}".format(1 - miss_classification_count/N)
    print ('Training Accuracy LR:',acc)
    np.savetxt("predicted_labels_train.csv", predicted_labels, delimiter=",")
    
    #test

    df = testSet
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
            
    acc = "{:.2f}".format(1 - miss_classification_count/N)
    print ('Testing Accuracy LR:',acc)
    np.savetxt("test_labels.csv", predicted_labels, delimiter=",")
    
        
    
    return 0



#svm
def svm(trainingSet, testSet):
    tol = 0.00001
    lamda = 0.01
    step_size = 0.5
    df = trainingSet
    
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
        

        
        df_no_label_matrix_transpose = np.transpose(df_no_label_matrix)
        y_i_hat = np.matmul(w,df_no_label_matrix_transpose)
        
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
        if np.matmul(w,df_no_label_matrix[i]) < 0:
            predicted_labels [i] = -1
        
        if predicted_labels[i] != y_i[i]:
            miss_classification_count += 1
            
    acc = "{:.2f}".format(1 - miss_classification_count/N)
    print ('Training Accuracy SVM:',acc)
    np.savetxt("SVM_predicted_labels_train.csv", predicted_labels, delimiter=",")
    
    
    
    #test
    df = testSet
    
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
        if np.matmul(w,df_no_label_matrix[i]) < 0:
            predicted_labels [i] = -1
        
        if predicted_labels[i] != y_i[i]:
            miss_classification_count += 1
            
    acc = "{:.2f}".format(1 - miss_classification_count/N)
    print ('Testing Accuracy SVM:',acc)
    #np.savetxt("SVM_predicted_labels_test.csv", predicted_labels, delimiter=",")        
    
    
    return 0  
        
        
#main   

# test = pd.read_csv('testSet.csv',sep=',')
# train = pd.read_csv('trainingSet.csv',sep=',')
# svm(train, test)

       
trainingDataFilename = input("input trainingDataFilename:")
testDataFilename = input("input testDataFilename:")
modelIdx = input("modelIdx:")

#trainingSet.csv
#testSet.csv

train = pd.read_csv(trainingDataFilename,sep=',')

test = pd.read_csv(testDataFilename,sep=',')    

            
if modelIdx == '1':
    lr(train, test)

if modelIdx == '2':
    svm(train, test)

    