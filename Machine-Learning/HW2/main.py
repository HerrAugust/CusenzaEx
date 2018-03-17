import pandas
import string

from decisionTrees import decisionTrees
from holdoutMethod import holdoutMethod
from kFolds import kFolds


K_FOLD = False
header = ['letter', 'xbox', 'ybox', 'width', 'height', 'onpix', 'xbar', 'ybar', 'x2bar', 'y2bar', 'xybar', 'x2ybr', 'xy2br', 'x-ege', 'xegvy', 'y-ege', 'yegvx']
df = pandas.read_csv('Dataset/letter-recognition.data', names=header)
print('Dataset with {} entries'.format(df.__len__()))


# Pre-processing
mapping = {
    'A': 1,
    'B': 2
    #  etc.
}
i = 1
for letter in list(string.ascii_uppercase):
    mapping[letter] = i
    i = i + 1
df['letter'] = df['letter'].map(mapping)



# Compute models
# Classical way, i.e. divide dataset into training and test sets. 70% for train and 30% for test
holdoutMethod(df)
print('--------------------------')

# k-fold way with k=10
if K_FOLD:  # it is computationally expensive
    kFolds(df, k=10)
    print('--------------------------')

# Decision Trees
decisionTrees(df)
print('--------------------------')




# Stop console
input("Waiting for getting closed...")

