import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import matplotlib.patches as mpatches
import math
from scipy import spatial
from scipy import stats
from scipy.stats import entropy
from scipy.cluster.hierarchy import dendrogram, linkage, fcluster

np.random.seed(0)
max_ite = 50

#should input K and dataFilename here ---digits-embedding.csv
# dataFilename = input("input dataFilename:")
# K = int(input("input K:"))
dataFilename = 'digits-embedding.csv'


df = pd.read_csv(dataFilename,sep=',')
df_matrix = df.to_numpy()

#randomly sample 10 samples from each label
n_labels = 10
rand_idx = []

for i in range(n_labels):
    digit = df_matrix[df_matrix[:,1] == i]
    idx_array = digit[:,0]
    idx = np.random.choice(idx_array, 10, replace = False)
    rand_idx.extend(idx)
arr = np.array(rand_idx)
arr = arr.astype(int)
df_rand_100 = df_matrix[arr]




def hierarchical(data_full):
    #process data etc
    data = data_full[:,2:]
    labels = data_full[:,1]
    
    for met in ['single','complete','average']:
        #linage matrix
        Z = linkage(data, method = met)
        
        #plot dendrogram using different 
        plt.figure(figsize=(25, 10))
        plt.title('Hierarchical Clustering Dendrogram ' + met + ' linkage')
        plt.xlabel('sample index')
        plt.ylabel('distance')
        dendrogram(Z, leaf_rotation=90, leaf_font_size=8)
        plt.show()
        
        #different K
        K = [2, 4, 8, 16, 32]
        WC_SSDs = []
        SCs = []
        
        for k in K:
            predicted_labels = fcluster(Z, t = k, criterion='maxclust') - 1
            
            #---WC-SSD
                
            clusters = [[] for i in range(k)]
            centroid_coords = np.zeros((k,2))
            for i, item in enumerate(data_full):
                clusters[predicted_labels[i]].append(item)
            
            WC_SSD = 0
            for i in range(k):
                slic = clusters[i]
                slic = np.array(slic)
                if slic.size == 0:
                    print('!!!!!!!!', k)
                centroid_coords[i] = np.mean(slic[:,2:], axis=0)
                cent = np.array([centroid_coords[i]])
                points_coords = slic[:,2:]
                
                WC_SSD += np.sum(spatial.distance.cdist(cent, points_coords, metric='sqeuclidean'))
                
            WC_SSDs.append(WC_SSD)
            
            
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
                
                we = 1
                a = 1
            S = S/len(data)
            SCs.append(S)
        
            
        #plot SC and WC-SSD against k
        plt.figure(figsize=(25, 10))
        plt.title('Silhoutte Coeffcient vs k ' +  met + ' linkage')
        plt.xlabel('k')
        plt.ylabel('Silhoutte Coeffcient')
        plt.plot(K,SCs)
        plt.show()
        
        plt.figure(figsize=(25, 10))
        plt.title('WC-SSD vs k ' +  met + ' linkage')
        plt.xlabel('k')
        plt.ylabel('WC-SSD')
        plt.plot(K,WC_SSDs)
        plt.show()
        
        #determined optimal k to be 16 for all linkage
        k=16
        
        
        predicted_labels = fcluster(Z, t = k, criterion='maxclust') - 1
    
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
        for i in range(C):
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
        print(met + ' ' + 'NMI: ',NMI)
        
 
    
    return 0
            
            
        
#main
hierarchical(df_rand_100) 
            
        
    
    
    
