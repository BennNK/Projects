import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

df=pd.read_csv('dating-binned.csv',sep=',')
test_set = df.sample(frac = 0.2,  random_state = 47)
training_set = df.drop(test_set.index)

test_set.to_csv('testSet.csv', sep=',',  index=False)
training_set.to_csv('trainingSet.csv', sep=',',  index=False)