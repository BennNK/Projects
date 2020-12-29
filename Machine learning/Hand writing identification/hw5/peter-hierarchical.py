import numpy as np
import os
import scipy
import pandas as pd
import random
import matplotlib.pyplot as plt
import sys
import math
from scipy.cluster.hierarchy import dendrogram, linkage

FIG_DIR = "./figures/hierarchical"

class Agglomerative():
    def __init__(self, full_data, data, labels, seed=0):
        np.random.seed(seed)
        self.full_data = np.matrix(full_data)
        self.data = np.matrix(data)
        self.labels = labels.to_numpy().flatten()
        
        # print(self.labels)
        
    def sample_data(self):
        # find the indices of our sampled data
        total_choices = None
        for i in range(10):
            inds = np.where(self.labels == i)[0]
            
            choices = np.random.choice(inds, 10, replace=False)
            
            # print(inds)
            # print(choices)
            
            if i == 0:
                total_choices = np.copy(choices)
            else:
                total_choices = np.append(total_choices, choices)
            
            # break
        print(total_choices)
        
        # reduce our data to the 100 points
        self.full_data = self.full_data[total_choices.astype(int), :]
        self.data = self.data[total_choices.astype(int), :]
        self.labels = self.labels[total_choices.astype(int)]
        
    def performClustering(self, linkage_type):
        Z = linkage(self.data, linkage_type)
        fig = plt.figure(figsize=(25, 10))
        dn = dendrogram(Z)
        # plt.show()
        plt.title(linkage_type + " linkage")
        plt.savefig(os.path.join(FIG_DIR, linkage_type))
        
    def allClustering(self):
        linkage_types = ['single', 'complete', 'average']
        
        for linkage_type in linkage_types:
            self.performClustering(linkage_type)
        
        

filename = 'digits-embedding.csv'
# k = int(args[2])

yelp = pd.read_csv(filename, delimiter=",",index_col = None, header=None, engine = "python")
yelp.columns = ['ind1', 'ind2', 'ind3', 'ind4']
data = yelp[['ind3','ind4']]
labels = yelp[['ind2']]

ag = Agglomerative(yelp, data, labels)
ag.sample_data()
ag.allClustering()
# ag.performClustering('single')
# print(yelp)
# km = k_means(data, labels, yelp,k,0)
# km.fit()
# print("WC-SSE: "+ str(km.SSEn))
# print("SC: "+ str(km.S_c))
# print("NMI: " + str(km.NMI))
    
# if __name__ == "__main__":
#     main(sys.argv)
        
    
        