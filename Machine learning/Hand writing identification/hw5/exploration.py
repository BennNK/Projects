import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import matplotlib.patches as mpatches

np.random.seed(0)

df = pd.read_csv('digits-raw.csv',sep=',')
# print(df)
df_matrix = df.to_numpy()
# print(df_matrix)


for i in range(10):
    
    pick_matrix = df_matrix[np.where(df_matrix[:,1] == i)]
    num_rows, num_cols = pick_matrix.shape
    
    random_index = np.random.choice(num_rows, size=1) 
    pix = pick_matrix[random_index].copy()
    pix = np.delete(pix, [0,1], 1)
    pix = np.reshape(pix, (28, 28))
    im = plt.imshow(pix, cmap='Greys', vmin=1, vmax=255, alpha = 1)
    im.cmap.set_under('k',alpha = 0)
    plt.savefig('digit '+str(i))
    plt.clf()



n = 1000
df = pd.read_csv('digits-embedding.csv',sep=',')
random_indices = np.random.randint(0, len(df), size=n)
df = df.iloc[random_indices,:]
df_matrix = df.to_numpy()
# df_matrix = np.delete(df_matrix, 0, 1)
data = df_matrix[:,2:]
labels = df_matrix[:,1]

cmaps = ['#1f77b4', '#ff7f0e', '#2ca02c', '#d62728', '#9467bd', '#8c564b', '#e377c2', '#7f7f7f', '#bcbd22', '#17becf']


fig,ax = plt.subplots()


for i in range(n):
    color = int(labels[i])
    plt.scatter(data[i][0], data[i][1], c = cmaps[color])
    
patch = []
for i in range(10):
    patch.append( mpatches.Patch(color=cmaps[i], label='digit '+str(i)))
    plt.legend(handles = patch)
    
plt.xlabel('t-SNE first column')
plt.ylabel('t-SNE second column')
plt.show()