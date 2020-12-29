import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

df=pd.read_csv('dating.csv',sep=',')



df_male = df[df['gender'] == 1]
df_female = df[df['gender'] == 0]

df_male_mean = []
df_female_mean = []

col = df_male.loc[: , 'attractive_important':'shared_interests_important']
df_male_mean = col.mean(axis=0)
col = df_female.loc[: , 'attractive_important':'shared_interests_important']
df_female_mean = col.mean(axis=0)


#plot
label = ['attractive_important','sincere_important','intelligence_important','funny_important','ambition_important','shared_interests_important']
label_loc= np.arange(len(label))

fig, bar_plot = plt.subplots()

plot_male = bar_plot.bar(label_loc + 0.125, df_male_mean, 0.25, color= 'green', label = 'male')
plot_female = bar_plot.bar(label_loc-0.125, df_female_mean, 0.25, color= 'red', label = 'female')
bar_plot.set_xticks(label_loc)
bar_plot.set_ylabel('Mean of dfferent attributes', fontsize = 14)
bar_plot.set_xticklabels(label, fontsize = 14, ha='center')
plt.legend(loc=[1, 0], prop={'size': 24})

