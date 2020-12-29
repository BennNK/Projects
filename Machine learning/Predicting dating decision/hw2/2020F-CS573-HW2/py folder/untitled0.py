import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import random
from scipy import spatial
import nltk

df=pd.read_csv('C:\\Users\\Ben\\Desktop\\cs573\\hw2\\2020F-CS573-HW2\\123.csv',sep=',')

print (df)
df = df.drop([0,1])
print (df)



a = [[255,255,100],
     [255,255,255],
     [123,123,34]]

b = [[0,0,0],
     [255,255,255],
     [123,123,34]]

b = np.array(b)
c = [[0,0,0],
     [0,0,0],
     [0,123,34]]

w1 = b[:,1:]
print(w1)

a = np.array([[0,0],
     [1,1],
     [2,2]])

b = np.array([[0,0],
     [1,1],
     ])

a = np.array([1,2,4,5])
b = np.array([2,2,3,5])
c = np.array([a,b])

print('c',c.T)
    

# b = np.array([
#      [[0,0,0],
#      [255,255,255],
#      [123,123,34]],
     
#      [[255,255,100],
#      [255,255,255],
#      [123,123,34]]
#      ])

# print (b[0][:,1:])
# print(np.mean(b[0][:,1:], axis=0))

b = [[0,0,0],
     [255,255,255],
     [123,123,34],
     [2223,123,34],
     ]
predicted_labels = [0,0,1,2]

clusters = [[] for i in range(3)]

for i,item in enumerate(b):
            clusters[predicted_labels[i]].append(item)
print (clusters, '\n')


# aa = np.array([1,1,1,2,3,5,5,1])
# unique_label = np.unique(aa, return_counts = True)
# print(unique_label,len(unique_label[0]))
# print(unique_label[1]/8)

a = np.array([[1,0],
              [1,5],
              [1,2],
              [2,3],
              [3,8],
              [1,9],
              [1,0],
              [1,0],
              
             ])

unique_label = np.unique(a, axis = 0, return_counts = True)
print(unique_label)
er = unique_label[1]

er = np.reshape(er, (2, 3))
print (er)

s = np.array([[2,0],
              [1,5],
              [1,2],
              [2,3],
              [3,8],
              [1,9],
              [3,0],
              [1,0]])

eee = np.array([[0,0]])

slic = np.array([[1600	,0	,-24.596	,3.86551]])
print (slic[:,2:])







asd = np.random.binomial(1, 0.7, 1)
print ('asd',asd)

string = "br"
tokens = nltk.word_tokenize(string)
tags = nltk.pos_tag(tokens)






F = [1,2,3,4]
f = [element * 2 for element in F]
print(np.mean(np.array([0.6266666666666667, 0.6, 0.5066666666666667, 0.5333333333333333, 0.49333333333333335, 0.5866666666666667, 0.6133333333333333, 0.5466666666666666, 0.5866666666666667, 0.56])))
print(np.mean(np.array([0.64, 0.615, 0.62, 0.595, 0.665, 0.555, 0.58, 0.56, 0.64, 0.66])))
print(np.mean(np.array([0.596, 0.604, 0.624, 0.604, 0.56, 0.596, 0.568, 0.598, 0.576, 0.574])))

print(np.mean(np.array([0.5933333333333334, 0.6226666666666667, 0.5866666666666667, 0.592, 0.592, 0.568, 0.5786666666666667, 0.5973333333333334, 0.5933333333333334, 0.5866666666666667])))
print(np.mean(np.array([0.603, 0.607, 0.588, 0.584, 0.58, 0.601, 0.575, 0.598, 0.576, 0.615])))



print(np.mean(np.array([0.6355555555555555, 0.6385185185185185, 0.6518518518518519, 0.6488888888888888, 0.6474074074074074, 0.6459259259259259, 0.6474074074074074, 0.6459259259259259, 0.6325925925925926, 0.6592592592592592])))
print(np.mean(np.array([0.625, 0.6216666666666667, 0.6227777777777778, 0.6244444444444445, 0.625, 0.6222222222222222, 0.6255555555555555, 0.6277777777777778, 0.6333333333333333, 0.6238888888888889])))
print(np.mean(np.array([0.5951111111111111, 0.5955555555555555, 0.5937777777777777, 0.5942222222222222, 0.5997777777777777, 0.5935555555555555, 0.6002222222222222, 0.5946666666666667, 0.6008888888888889, 0.5953333333333334])))

print(np.mean(np.array([0.593037037037037, 0.589925925925926, 0.5937777777777777, 0.5936296296296296, 0.5937777777777777, 0.5958518518518519, 0.5954074074074074, 0.5925925925925926, 0.5936296296296296, 0.5940740740740741])))
print(np.mean(np.array([0.5942222222222222, 0.5941111111111111, 0.5957777777777777, 0.5962222222222222, 0.5966666666666667, 0.5941111111111111, 0.5972222222222222, 0.5943333333333334, 0.597, 0.5926666666666667])))



cmaps = [
            'Greys', 'Purples', 'Blues', 'Greens', 'Oranges', 'Reds',
            'YlOrBr', 'YlOrRd', 'OrRd', 'PuRd', 'RdPu', 'BuPu',
            'GnBu', 'PuBu', 'YlGnBu', 'PuBuGn', 'BuGn', 'YlGn']

# fig,ax = plt.subplots()
# plt.imshow(a, cmap=cmaps[1], vmin=1, vmax=255, alpha = 1)
# im2 = plt.imshow(b, cmap=cmaps[2], vmin=1, vmax=255, alpha = 1)
# im2.cmap.set_under('k',alpha = 0)
# im3 = plt.imshow(c, cmap=cmaps[3], vmin=1, vmax=255, alpha = 1)
# im3.cmap.set_under('k',alpha = 0)

# b = np.array(b)
# d = b[np.where(b[:,0] == 255)]

# print (d)

# ww = c

# print (ww)
# aa = ww[2].copy()
# print(aa)
# aa = np.reshape(aa, (3, 1))
# print(aa)




# plt.show()
    
# def fun(a, b=None):
#     if b != None:
#         print (a,b)

# a = 1
# fun(a)
# fun(a,2)

# df = df.drop(columns=['a','b','c'])
# if df.empty:
#     print(df)
#     print(len(df))
    
    
    

# #df[['a','b']]=df[['a','b']].div(df.c, axis=0)
# # print (df)

# # mean=[]

# # col = df.loc[:, 'a':'c']
# # print (col)


# # mean=col.mean(axis=0)
# # print(mean)

# x = [1,2,3]

# y =[1,2,3]

# z=[4,5,6]



# fig,ax = plt.subplots()

# plt.xlabel('bin number')
# plt.ylabel('accuracy')

# plt.plot(x,y,"x-",label="training accuracy")
# plt.plot(x,z,"+-",label="test accuracy")
# plt.legend(loc=[0.5, 1], prop={'size': 12})


# # test_set = df.sample(frac = 0.2,replace = False, random_state = 47)
# # print (test_set)
# # training_set = df.drop(test_set.index)
# # print (training_set)

#df = pd.DataFrame(np.random.randn(5,3), columns=list('abc'))

#df.reset_index(level=0, inplace=True)
# print (df)

# df = df.sort_values('a')

# print (df)



# colnames = df['a'].unique()
# print (type(colnames), '\n')
# colnames[::-1].sort()
# print (colnames, '\n')

# insert_loc=df.columns.get_loc('a') + 1

# this_colname = colnames[0]



# df.insert(insert_loc, this_colname, 0)
# df.loc[df['a'] == this_colname, [this_colname]] = 1
# print (df)

# mapped_vector = np.zeros(colnames.size - 1)
# print (mapped_vector)




# e = np.array_split(df, 3)

# print (e[0])




# a = [1,1,1,1]
# print (np.linalg.norm(a))

# c = df.loc[:,'c']
# c = c.values
# print (c)

# ma = df.to_numpy()
# print(ma)
# print(np.matmul(ma[0],ma[1]))

# a = np.ndarray[0,0,0]
# print ('a',a)


#print (ma[2][0])

# print (np.dot(ma[0],ma[1]))

# a = [0.9,0.8,0.7,0.6,0.6,0.6]
# b = [0.4,0.45,0.5,0.55,0.56,0.57]
# e = [0.006,0.006,0.006,0.006,0.006,0.005]
# F = [0.025, 0.05, 0.075, 0.1, 0.15, 0.2]

# NBC_train_acc = a
# NBC_train_err = e
# NBC_test_acc = b
# NBC_test_err = e

# LR_train_acc = [x - 0.1 for x in a]
# LR_train_err = e
# LR_test_acc = [x - 0.1 for x in b]
# LR_test_err = e


# SVM_train_acc = [x - 0.2 for x in a]
# SVM_train_err = e
# SVM_test_acc = [x - 0.2 for x in b]
# SVM_test_err = e


# F_NBC = [x*9*650 for x in F]
# print(F_NBC)

# F = [x*9*520 for x in F]
# print (F)


# fig,ax = plt.subplots()
# plt.xlabel('sample size')
# plt.ylabel('accuracy') 

# plt.plot(F_NBC,NBC_train_acc,label="NBC_train_acc")
# plt.plot(F_NBC,NBC_test_acc,label="NBC_test_acc")
# plt.errorbar(F_NBC,NBC_train_acc,yerr=NBC_train_err,fmt='o',ecolor='r',color='b',elinewidth=2,capsize=4)
# plt.errorbar(F_NBC,NBC_test_acc,yerr=NBC_test_err,fmt='o',ecolor='r',color='b',elinewidth=2,capsize=4)

# plt.plot(F,LR_train_acc,label="LR_train_acc")
# plt.plot(F,LR_test_acc,label="LR_test_acc")
# plt.errorbar(F,LR_train_acc,yerr=LR_train_err,fmt='o',ecolor='r',color='b',elinewidth=2,capsize=4)
# plt.errorbar(F,LR_test_acc,yerr=LR_test_err,fmt='o',ecolor='r',color='b',elinewidth=2,capsize=4)

# plt.plot(F,SVM_train_acc,label="SVM_train_acc")
# plt.plot(F,SVM_test_acc,label="SVM_test_acc")
# plt.errorbar(F,SVM_train_acc,yerr=SVM_train_err,fmt='o',ecolor='r',color='b',elinewidth=2,capsize=4)
# plt.errorbar(F,SVM_test_acc,yerr=SVM_test_err,fmt='o',ecolor='r',color='b',elinewidth=2,capsize=4)




# plt.legend(loc=[0.5, 1], prop={'size': 12}) 



    





























    

