import pandas as pd
import numpy as np
import math
import random




#tree nodes
class Node:
    def __init__(self):
        self.depth = None
        self.predicted_label = None
        self.values_of_this_attribute = []
        self.child_nodes = []
        self.attribute_loc = None

        
# node = Node()
# print(node.predicted_label)




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
 
    if modelIdx == '3' or modelIdx == 3:
        
        att_list = df.columns.tolist()
        attribute_list_copy = att_list.copy()
        attribute_list_copy.remove('decision')
        att_sample = random.sample(attribute_list_copy, min(global_p_sqrt, len(attribute_list_copy)))
        # print('att_sample',att_sample)
        drop = [x for x in attribute_list_copy if x not in att_sample]
        att_todrop = att_todrop + drop
        
        

        # print('att_todrop',att_todrop)
        # print('df.columns',df.columns)
         
    
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
    
    #report accuracy
    for _set in [trainingSet, testSet]:
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
        acc.append("{:.2f}".format(acc_prec))
    
    print('Training Accuracy DT:', acc[0])
    print('Test Accuracy DT:', acc[1])

    
    
    return 0


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
    
    n_match = 0
    _set_matrix = trainingSet.to_numpy()
    n_rows, n_cols = _set_matrix.shape
    
    for i in range(n_rows):
        
        if average_labels[0,i] == _set_matrix[i, n_cols - 1]:
                n_match+= 1
    
    acc_prec = n_match/n_rows
    acc = "{:.2f}".format(acc_prec)
    print('Training Accuracy BT:', acc)
    
    
    n_match = 0
    _set_matrix = testSet.to_numpy()
    n_rows, n_cols = _set_matrix.shape
    
    for i in range(n_rows):
        
        if average_labels[1,i] == _set_matrix[i, n_cols - 1]:
                n_match+= 1
    
    
    acc_prec = n_match/n_rows
    acc = "{:.2f}".format(acc_prec)
    print('Testing Accuracy BT:', acc)
    
    
    return 0



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
    
    n_match = 0
    _set_matrix = trainingSet.to_numpy()
    n_rows, n_cols = _set_matrix.shape
    
    for i in range(n_rows):
        
        if average_labels[0,i] == _set_matrix[i, n_cols - 1]:
                n_match+= 1
    
    acc_prec = n_match/n_rows
    acc = "{:.2f}".format(acc_prec)
    ('Training Accuracy RF:', acc)
    
    
    n_match = 0
    _set_matrix = testSet.to_numpy()
    n_rows, n_cols = _set_matrix.shape
    
    for i in range(n_rows):
        
        if average_labels[1,i] == _set_matrix[i, n_cols - 1]:
                n_match+= 1
    
    
    acc_prec = n_match/n_rows
    acc = "{:.2f}".format(acc_prec)
    print('Testing Accuracy RF:', acc)
    
    
    return 0
        





#main
trainingDataFilename = input("input trainingDataFilename:")
testDataFilename = input("input testDataFilename:")
modelIdx = input("modelIdx:")

trainingSet = pd.read_csv(trainingDataFilename,sep=',')

testSet = pd.read_csv(testDataFilename,sep=',')    

global_p_sqrt = round(math.sqrt(len(trainingSet.columns)))
max_depth = 8

            
if modelIdx == '1':
    decisionTree(trainingSet, testSet)

if modelIdx == '2':
    bagging(trainingSet, testSet)
    
if modelIdx == '3':
    randomForests(trainingSet, testSet)

#trainingSet.csv
#testSet.csv


# print (tree.depth, tree.predicted_label,tree.values_of_this_attribute, tree.child_nodes[0].depth, tree.child_nodes[1].depth,tree.attribute_loc)

















    
    
