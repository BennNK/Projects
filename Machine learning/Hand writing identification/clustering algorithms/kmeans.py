import numpy as np

import pandas as pd

from scipy import spatial

from scipy.stats import entropy

np.random.seed(0)
max_ite = 50

#should input K and dataFilename here ---digits-embedding.csv
dataFilename = input("input dataFilename:")
K = int(input("input K:"))

df = pd.read_csv(dataFilename,sep=',')
df_matrix = df.to_numpy()


# def getDistance(point1, point2):
#     diff = np.subtract(point1, point2)  
#     return np.linalg.norm(diff)


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
    print('NMI: ',NMI)

    #---WC-SSD
    WC_SSD = np.sum(np.square(mindist))
    print('WC-SSD: ',WC_SSD)
    
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
    print('SC: ', S)
 
    
    return 0
            
            
        
#main
kmeans(df_matrix, K) 
            
        
    
    
    
