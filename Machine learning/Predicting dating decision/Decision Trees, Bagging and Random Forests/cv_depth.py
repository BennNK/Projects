import pandas as pd
import numpy as np
import math
import random
import matplotlib.pyplot as plt
import scipy.stats as sp


DT_test_acc = []
DT_test_err = []

BT_test_acc = []
BT_test_err = []

RF_test_acc = []
RF_test_err = []


global_caller = 0

#tree nodes
class Node:
    def __init__(self):
        self.depth = None
        self.predicted_label = None
        self.values_of_this_attribute = []
        self.child_nodes = []
        self.attribute_loc = None

        

def Build_tree (df, parent_node = None, attribute_list = None):
    

    #create a node
    node = Node()
    
    if parent_node != None:
        node.depth = parent_node.depth + 1
    else:
        node.depth = 0
        attribute_list = df.columns.tolist()
    
    #stop criteria
    if df.empty:
        return None
    
    n_examples = len(df)
    sum_ = df['decision'].sum()
    if node.depth == max_depth or n_examples < 50 or len(df.columns) == 1:
        if sum_ > n_examples/2:
            node.predicted_label = 1
        else:
            node.predicted_label = 0
        # print ('depth', node.depth, node.predicted_label, node.values_of_this_attribute, node.attribute_loc)
        return node
    
    if sum_ == 0:
        node.predicted_label = 0
        # print ('depth', node.depth, node.predicted_label, node.values_of_this_attribute, node.attribute_loc)
        return node
    if sum_ == n_examples:
        node.predicted_label = 1
        # print ('depth', node.depth, node.predicted_label, node.values_of_this_attribute, node.attribute_loc)
        return node
    
    
    
    att_todrop = ['decision']
    #downsize attributes for random forest
 
    if global_caller == '3' or global_caller == 3:

        att_list = df.columns.tolist()
        attribute_list_copy = att_list.copy()
        attribute_list_copy.remove('decision')
        att_sample = random.sample(attribute_list_copy, min(global_p_sqrt, len(attribute_list_copy)))
        # print('att_sample',att_sample)
        drop = [x for x in attribute_list_copy if x not in att_sample]
        att_todrop = att_todrop + drop
         
    
    #select best att
    
    best_att = None
    best_gini = 1 - (len(df[df['decision'] ==  0])/n_examples)**2 - (len(df[df['decision'] ==  1])/n_examples)**2
    
    for colname in df.columns.drop(att_todrop):
        gini = 0
        
        for i in [0,1]:
            df_i = df[df[colname] ==  i]
            df_i_label_0 = df_i[df_i['decision'] ==  0]
            df_i_label_1 = df_i[df_i['decision'] ==  1]
            n_df_i = len(df_i)
            if n_df_i ==0:
                continue
            n_label_0 = len(df_i_label_0)
            n_label_1 = len(df_i_label_1)
            #print ('colname',colname,'n_examples',n_examples,'n_df_i',n_df_i,'\n')
            gini += n_df_i/n_examples*(1 - (n_label_0/n_df_i)**2 - (n_label_1/n_df_i)**2)
            
        if gini < best_gini:
            best_gini = gini
            best_att = colname
     
    if best_att == None:
        node.predicted_label = 1 # can ramdonize
        # print ('depth', node.depth, node.predicted_label, node.values_of_this_attribute, node.attribute_loc)
        return node
    
    node.attribute_loc = attribute_list.index(best_att)
    
  
    
    #push value into values_of_this_attribute
    
    att_col = df[best_att].to_numpy()
    unique = np.unique(att_col)

    node.values_of_this_attribute = unique
    #print('node.values_of_this_attribute',node.values_of_this_attribute)
   # node.values_of_this_attribute.append(1)
    
 
    
    #loop values_of_this_attribute: cut df and call Biuld_tree (cut_df, node):
    for i in node.values_of_this_attribute:
        cut_df = df[df[best_att] ==  i]
        cut_df = cut_df.drop(columns=[best_att])
        node.child_nodes.append(Build_tree (cut_df, node, attribute_list))
    
    
    
    #print ('root', node.depth, node.predicted_label, node.values_of_this_attribute, node.attribute_loc)
    # if node.child_nodes != None:
    #     print ('child', node.child_nodes)
    
    # ,
    return node
   
        

def decisionTree (trainingSet, testSet):
    #learn tree
    root_node = Build_tree (trainingSet)
    # print ('root', root_node.depth, root_node.predicted_label, root_node.values_of_this_attribute, root_node.attribute_loc)
   
    acc = []
    Acc = [0]
    
    #report accuracy
    for _set in [testSet]:
        _set_matrix = _set.to_numpy()

        n_rows, n_cols = _set_matrix.shape
        n_match = 0
        
        for i in range(n_rows):
            node = root_node
            while(node.predicted_label == None):
                col_idx = node.attribute_loc
                child_idx = _set_matrix[i, col_idx]
                node = node.child_nodes[child_idx]
                
            if node.predicted_label == _set_matrix[i, n_cols - 1]:
                n_match+= 1
        
        acc_prec = n_match/n_rows
        Acc.append(acc_prec)
        # acc.append("{:.2f}".format(acc_prec))
    
    # print('Training Accuracy DT:', acc[0])
    # print('Test Accuracy DT:', acc[1])

    
    
    return Acc


def bagging (trainingSet, testSet):
    n_trees = 30
    
    average_labels = np.zeros((2, max([len(trainingSet), len(testSet)])))

    
    for i in range(n_trees):
        # print (i)
        bootstrap_set = trainingSet.sample(frac = 1,  replace = True)

        root_node = Build_tree (bootstrap_set)
        
        # print ('root', root_node.depth, root_node.predicted_label, root_node.values_of_this_attribute, root_node.attribute_loc)
        
        #predicted labels of testset
        
        for _set, k in zip([trainingSet, testSet], range(2)):

            _set_matrix = _set.to_numpy()
            n_rows, n_cols = _set_matrix.shape
                    
            for j in range(n_rows):
                node = root_node
                while(node.predicted_label == None):
                    col_idx = node.attribute_loc
                    child_idx = _set_matrix[j, col_idx]
                    node = node.child_nodes[child_idx]
                    
                average_labels[k,j] += node.predicted_label
    
    # np.savetxt("average_labels.csv", average_labels, delimiter=",")
    average_labels = average_labels/n_trees
    # np.savetxt("a.csv", average_labels, delimiter=",")
    average_labels = np.rint(average_labels)
    # np.savetxt("b.csv", average_labels, delimiter=",")
    
    # n_match = 0
    # _set_matrix = trainingSet.to_numpy()
    # n_rows, n_cols = _set_matrix.shape
    
    # for i in range(n_rows):
        
    #     if average_labels[0,i] == _set_matrix[i, n_cols - 1]:
    #             n_match+= 1
    
    
    # Acc = [0,0]
    # acc_prec = n_match/n_rows
    # acc = "{:.2f}".format(acc_prec)
    # print('Training Accuracy BT:', acc)
    # Acc[0] = acc_prec
    
    Acc = [0,0]
    n_match = 0
    _set_matrix = testSet.to_numpy()
    n_rows, n_cols = _set_matrix.shape
    
    for i in range(n_rows):
        
        if average_labels[1,i] == _set_matrix[i, n_cols - 1]:
                n_match+= 1
    
    
    acc_prec = n_match/n_rows
    acc = "{:.2f}".format(acc_prec)
    # print('Testing Accuracy BT:', acc)
    Acc[1] = acc_prec
    
    return Acc



def randomForests(trainingSet, testSet):
    n_trees = 30
    
    average_labels = np.zeros((2, max([len(trainingSet), len(testSet)])))

    
    for i in range(n_trees):
        # print (i)
        bootstrap_set = trainingSet.sample(frac = 1,  replace = True)

        root_node = Build_tree (bootstrap_set)
        
        # print ('root', root_node.depth, root_node.predicted_label, root_node.values_of_this_attribute, root_node.attribute_loc)
        
        #predicted labels of testset
        
        for _set, k in zip([trainingSet, testSet], range(2)):

            _set_matrix = _set.to_numpy()
            n_rows, n_cols = _set_matrix.shape
                    
            for j in range(n_rows):
                node = root_node
                while(node.predicted_label == None):
                    col_idx = node.attribute_loc
                    child_idx = _set_matrix[j, col_idx]
                    node = node.child_nodes[child_idx]
                    
                average_labels[k,j] += node.predicted_label
    
    # np.savetxt("average_labels.csv", average_labels, delimiter=",")
    average_labels = average_labels/n_trees
    # np.savetxt("a.csv", average_labels, delimiter=",")
    average_labels = np.rint(average_labels)
    # np.savetxt("b.csv", average_labels, delimiter=",")
    
    # n_match = 0
    # _set_matrix = trainingSet.to_numpy()
    # n_rows, n_cols = _set_matrix.shape
    
    # for i in range(n_rows):
        
    #     if average_labels[0,i] == _set_matrix[i, n_cols - 1]:
    #             n_match+= 1
    
    
    # Acc = [0,0]
    # acc_prec = n_match/n_rows
    # acc = "{:.2f}".format(acc_prec)
    # print('Training Accuracy BT:', acc)
    # Acc[0] = acc_prec
    
    Acc = [0,0]
    n_match = 0
    _set_matrix = testSet.to_numpy()
    n_rows, n_cols = _set_matrix.shape
    
    for i in range(n_rows):
        
        if average_labels[1,i] == _set_matrix[i, n_cols - 1]:
                n_match+= 1
    
    
    acc_prec = n_match/n_rows
    acc = "{:.2f}".format(acc_prec)
    # print('Testing Accuracy BT:', acc)
    Acc[1] = acc_prec
    
    return Acc
        





#---------------main------------
trainingSet = pd.read_csv('trainingSet.csv',sep=',')
testSet = pd.read_csv('testSet.csv',sep=',')

trainingSet_shuffled = trainingSet.sample(frac = 1,  random_state = 18)
df = trainingSet_shuffled.sample(frac = 0.5,  random_state = 32)

global_p_sqrt = round(math.sqrt(len(trainingSet.columns)))

Depth = [3,5,7,9]

df = df.reset_index(drop=True)
S = np.array_split(df, 10)

for max_depth in Depth:
    print('max_depth',max_depth)

    dt_test_acc = []

    bt_test_acc = []

    rf_test_acc = []
    
    for i in range(10):
        # print('i',i)
        test_set = S[i]
        S_c = df.drop(S[i].index)
        training_set = S_c
        
        dt_acc = decisionTree(training_set, test_set)
        bt_acc = bagging(training_set, test_set)
        global_caller = 3
        rf_acc = randomForests(training_set, test_set)
        global_caller = 0
        
       
        dt_test_acc.append(dt_acc[1])
     
        bt_test_acc.append(bt_acc[1])
   
        rf_test_acc.append(rf_acc[1])
    
    #t-test
    # print('dt_test_acc',dt_test_acc)
    # print('bt_test_acc', bt_test_acc)
    # print('rf_test_acc',rf_test_acc)
    
    test_t_test = sp.ttest_ind(dt_test_acc, bt_test_acc)
    print ('t statistics for DT and BT', test_t_test)
    
    test_t_test = sp.ttest_ind(dt_test_acc, rf_test_acc)
    print ('t statistics for DT and RF', test_t_test)
    
    test_t_test = sp.ttest_ind(bt_test_acc, rf_test_acc)
    print ('t statistics for BT and RF', test_t_test)
        
    #calc average acc and eror
    DT_test_acc.append(np.mean(dt_test_acc))
    DT_test_err.append(np.std(dt_test_acc)/math.sqrt(10))
    #print('NBC_train_acc',NBC_train_acc,'NBC_train_err',NBC_train_err,'NBC_test_acc',NBC_test_acc,'NBC_test_err',NBC_test_err)
    
   
    BT_test_acc.append(np.mean(bt_test_acc))
    BT_test_err.append(np.std(bt_test_acc)/math.sqrt(10))
    
    
   
    RF_test_acc.append(np.mean(rf_test_acc))
    RF_test_err.append(np.std(rf_test_acc)/math.sqrt(10))
    
    
#plot
fig,ax = plt.subplots()
plt.xlabel('depth limit')
plt.ylabel('test accuracy')


plt.plot(Depth,DT_test_acc,label="DT_test_acc")
plt.errorbar(Depth,DT_test_acc,yerr=DT_test_err,fmt='o',ecolor='r',color='b',elinewidth=2,capsize=4)

plt.plot(Depth,BT_test_acc,label="BT_test_acc")
plt.errorbar(Depth,BT_test_acc,yerr=BT_test_err,fmt='o',ecolor='r',color='b',elinewidth=2,capsize=4)

plt.plot(Depth,RF_test_acc,label="RF_test_acc")
plt.errorbar(Depth,RF_test_acc,yerr=RF_test_err,fmt='o',ecolor='r',color='b',elinewidth=2,capsize=4)

plt.legend(loc=[0.5, 1], prop={'size': 12}) 





# print (tree.depth, tree.predicted_label,tree.values_of_this_attribute, tree.child_nodes[0].depth, tree.child_nodes[1].depth,tree.attribute_loc)

















    
    
