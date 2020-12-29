import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import matplotlib.patches as mpatches
import math
from scipy import spatial
from scipy import stats
from scipy.stats import entropy
import matplotlib.cm as cm

np.random.seed(0)
max_ite = 50


def kmeans(data_full, k):
    #process data etc
    data = data_full[:,2:]
    labels = data_full[:,1]
    
    #initialize centroid coordinates
    init_centroids = np.random.choice(len(labels), size=k, replace=False)
    # init_centroids = np.random.randint(0, len(labels), size=k)
    centroid_coords = []
    for i in init_centroids:
        centroid_coords.append(data[i])
    centroid_coords = np.array(centroid_coords)
    
    #initialize predicted_labels etc
    predicted_labels_old = np.full(len(labels),-1)
    clusters = [[]] * k
    
    #loop until meet stop criteria
    for ite in range(max_ite):
        # print(ite)
            
        #calculate predicted labels using current centroids
        tree = spatial.cKDTree(centroid_coords)
        mindist, predicted_labels = tree.query(data)
        
        #update clusters list
        clusters = [[] for i in range(k)]
        for i, item in enumerate(data_full):
            clusters[predicted_labels[i]].append(item)

        
        #stop criteria
        if ite == max_ite - 1:
            # print('yes2')
            break #....
        
        comparison = predicted_labels == predicted_labels_old 
        if comparison.all():
            # print('yes')
            break #...
        
        #update centroids etc
        predicted_labels_old = predicted_labels.copy()
        for i in range(k):
            slic = clusters[i]
            slic = np.array(slic)
            centroid_coords[i] = np.mean(slic[:,2:], axis=0)
        
    #calculations
    NMI = -1
    
    #----NMI (c=class, g = cluster)
        #p(c) and p(g) as vectors
    unique_labels = np.unique(labels, return_counts = True)
    C = len(unique_labels[0])
    p_c = unique_labels[1]/len(labels)
    
    unique_predicted_labels = np.unique(predicted_labels, return_counts = True)
    G = k
    p_g = unique_predicted_labels[1]/len(predicted_labels)
    
        #log(p(c)p(g)) matrix, size is C*G
    a = np.array([p_c])
    a = a.T
    b = np.array([p_g])
    c = np.matmul(a,b)
    log_pcpg = np.log2(c)
    
        #p(c,g) matrix, size is C*G
    aa = np.array([labels, predicted_labels])
    aa = aa.T
    unique_cgs = np.unique(aa, axis = 0, return_counts = True)
    bb = unique_cgs[1]
    partial_label_cluster = unique_cgs[0]
    
        #calculate missing elements in partial_label_cluster compared with full_label_cluster nad update the number of those elements in bb
    full_label_cluster = []
    for i in unique_labels[0]:
        for j in range(G):
            full_label_cluster.append([i,j])
    full_label_cluster = np.array(full_label_cluster)
    
    df_partial = pd.DataFrame(data = partial_label_cluster)
    df_full = pd.DataFrame(data = full_label_cluster)
    diff = pd.concat([df_full, df_partial]).drop_duplicates(keep=False)
    idx_of_missing = diff.index.values.tolist()
    for i in idx_of_missing:
        bb = np.insert(bb, i, 0)
    
    bb = np.reshape(bb, (C, G))   
    p_cg = bb/len(predicted_labels)
    p_cg = np.where(p_cg == 0, 1e-6, p_cg)
    log_p_cg = np.log2(p_cg)
    
    I_CG = np.sum(p_cg * (log_p_cg - log_pcpg))
    
        #denumerator
    H_C = entropy(p_c, base=2)
    H_G = entropy(p_g, base=2)
    
        #NMI
    NMI = I_CG/(H_C + H_G)
    # print('NMI: ',NMI)

    #---WC-SSD
    WC_SSD = np.sum(np.square(mindist))
    # print('WC-SSD: ',WC_SSD)
    
    #--- Silhoutte Coeffcient, need predicted_labels array
        #paste predicted clusters column to data_full
    data_with_cluster_label = np.c_[data_full, predicted_labels]
        #iterate through clusters
    S = 0
    for i in range(k):     
        cluster = data_with_cluster_label[data_with_cluster_label[:,4] == i]
        other_points_outof_cluster = data_with_cluster_label[data_with_cluster_label[:,4] != i]
        coords = cluster[:,[2,3]]
        other_points_outof_cluster = other_points_outof_cluster[:,[2,3]]
        
        
        for j in range(len(coords)):
            point = np.array([coords[j]])
            other_points_in_cluster = np.delete(coords, j, axis = 0)
            if other_points_in_cluster.size == 0:
                continue
            else:
                in_cluster_dist = spatial.distance.cdist(point, other_points_in_cluster, metric='euclidean')
                A = np.average(in_cluster_dist)
                out_cluster_dist = spatial.distance.cdist(point, other_points_outof_cluster, metric='euclidean')
                B = np.average(out_cluster_dist)
                S += (B - A)/max(A , B)
    S = S/len(data)
    # print('SC: ', S)
 
    
    return (NMI, WC_SSD, S, predicted_labels)
            
            
        
#-------------------main

#create three datasets
df = pd.read_csv('digits-embedding.csv',sep=',')
df_1 = df.to_numpy()
df_2 = df_1[ (df_1[:,1] == 2) | (df_1[:,1] == 4) | (df_1[:,1] == 6) | (df_1[:,1] == 7) ]
df_3 = df_1[ (df_1[:,1] == 6) | (df_1[:,1] == 7) ]
DATA = [df_1, df_2, df_3]

#Q2.2.1
K = [2, 4, 8, 16, 32]

for i in range(3):
    # print('i',i)
    WC = []
    SC = []
    for k in K:
        # print('k',k)
        NMI, WC_SSD, S, pred = kmeans(DATA[i], k)
        WC.append(WC_SSD)
        SC.append(S)
    
    #plot SC and WC-SSD against k
    plt.figure(figsize=(25, 10))
    plt.title('Silhoutte Coeffcient vs k ' +  'Dataset ' + str(i+1))
    plt.xlabel('k')
    plt.ylabel('Silhoutte Coeffcient')
    plt.plot(K,SC)
    plt.show()
    
    plt.figure(figsize=(25, 10))
    plt.title('WC-SSD vs k ' +  'Dataset ' + str(i+1))
    plt.xlabel('k')
    plt.ylabel('WC-SSD')
    plt.plot(K,WC)
    plt.show()
    

#Q2.2.3

seeds = np.random.randint(2147483647, size=10) 


for i in range(3):
    # print('i',i)
    WC = []
    WC_err = []
    SC = []
    SC_err = []   
    for k in K:
        # print('k',k)
        wc = []
        sc = []
        for seed in seeds:
            np.random.seed(seed)
            # print('seed',seed)
            NMI, WC_SSD, S, pred = kmeans(DATA[i], k)
            wc.append(WC_SSD)
            sc.append(S)
        WC.append(np.mean(wc))
        WC_err.append(np.std(wc))
        SC.append(np.mean(sc))
        SC_err.append(np.std(sc))
    
    
    
    #plot
    plt.figure(figsize=(25, 10))
    plt.title('Silhoutte Coeffcient vs k ' +  'Dataset ' + str(i+1))
    plt.xlabel('k')
    plt.ylabel('Silhoutte Coeffcient')
    plt.plot(K,SC)
    plt.errorbar(K,SC,yerr=SC_err,fmt='o',ecolor='r',color='b',elinewidth=2,capsize=4)
    plt.show()
    
    plt.figure(figsize=(25, 10))
    plt.title('WC-SSD vs k ' +  'Dataset ' + str(i+1))
    plt.xlabel('k')
    plt.ylabel('WC-SSD')
    plt.plot(K,WC)
    plt.errorbar(K,WC,yerr=WC_err,fmt='o',ecolor='r',color='b',elinewidth=2,capsize=4)
    plt.show()


            
        
#Q2.2.4   
#optimal K is 16,4,8 for dataset 1,2,3
K = [16,4,8]
for i , k in zip(range(3),K):
    NMI, WC_SSD, S, pred = kmeans(DATA[i], k)
    print('NMI of ' + 'Dataset ' + str(i+1) + ':', NMI)
    
    n = 1000
    df = DATA[i]
    random_indices = np.random.choice(len(df), size=n, replace=False)
    df = df[random_indices,:]
    data = df[:,2:]
    labels = pred[random_indices]

    #plot
  
    
    cmaps = ['#FFCCFF','#FFFF66','#FF99FF','#FF9933','#FF66FF',
             '#FF6666','#FF33FF','#FF3366','#CCFF33','#66FF33',
             '#6666FF','#6600FF','#3333FF','#3399FF','#333333',
             '#FFFF00']
    fig,ax = plt.subplots()
    
    for ii in range(n):
        color = int(labels[ii])
        plt.scatter(data[ii][0], data[ii][1], c = cmaps[color])
        
    patch = []
    for ii in range(k):
        patch.append( mpatches.Patch(color=cmaps[ii], label='cluster '+str(ii)))
        plt.legend(handles = patch)
    
    plt.title('1000 randomly selected examples in ' +  'Dataset ' + str(i+1))
    plt.xlabel('t-SNE first column')
    plt.ylabel('t-SNE second column')
    plt.show()
    
    
    
    

































    
