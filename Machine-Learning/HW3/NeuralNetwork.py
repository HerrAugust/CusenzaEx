import csv
import random

import pandas
import numpy
from sklearn import preprocessing
from sklearn.cross_validation import train_test_split
from sklearn.neural_network import MLPClassifier, MLPRegressor

import os.path


class NeuralNetwork:
    ################# Fields #######################
    # dataset_filename: string - path to dataset
    # header: list - header of the dataset
    # enumerable_columns: list - the enumerable columns

    # df: matrix - data set
    # training_set: matrix - training set
    # test_set: matrix - test set

    # TSnew_X: matrix - training set of TSnew (see documentation)
    # TSnew_Y: matrix - training set of TSnew (see documentation)
    # dim_random_subset: int - number of features to set to 0 (see documentation)
    # repeatSometimes: int - number of for cicles (see documentation)

    def __init__(self, repeatSometimes = 2, dim_random_subset = 2):
        # variables initialization
        self.enumerable_columns = []
        self.dataset_filename = ""
        self.header = []
        self.df = pandas.DataFrame()
        self.trainSet = pandas.DataFrame()
        self.testSet = pandas.DataFrame()
        self.TSnew_X = pandas.DataFrame()
        self.TSnew_Y = pandas.DataFrame()

        self.repeatSometimes = repeatSometimes
        self.dim_random_subset = dim_random_subset

        # This code really needs much time and therefore I save some computations
        if not os.path.isfile('trainSet{}-{}.csv'.format(repeatSometimes, dim_random_subset)):
            self.readDataset()
            self.discretization()
            self.preprocess()

            # creating TSnew
            self.createTrainingAndTestSet()
            self.createTSnew()

            # backup encoded sets
            self.writeCSV()
        else:
            self.readCSV()

        # training and test
        self.train()
        self.predict()


    def readDataset(self):
        print("DEB Read dataset")

        with open('header.txt') as f:
            self.header = f.read().split(',')
            print(self.header)
        with open('dataset.txt') as f:
            self.dataset_filename = f.read()
            print(self.dataset_filename)
        self.df = pandas.read_csv(self.dataset_filename, names=self.header)
        print('Dataset with {} entries'.format(self.df.__len__()))

############# Preprocessing ##########################
    # helper function (should not be called from other functions)
    def discretize(self, column):
        print("DEB Discretize column " + column)
        sorted_col = sorted(column)
        l = len(column)
        n = int(numpy.floor(l / 2))
        if l % 2 == 0:
            median_1 = numpy.median(sorted_col[0:n])
            median_2 = numpy.median(sorted_col[n:])
        else:
            median_1 = numpy.median(sorted_col[0:(n + 1)])
            median_2 = numpy.median(sorted_col[(n + 1):])
        iqr = median_2 - median_1
        h = 2 * iqr * (1 / numpy.cbrt(l))
        if h > 0:
            bins_number = numpy.ceil((column.max() - column.min()) / h)
            new_col, bins = pandas.cut(column, bins_number, labels=False, retbins=True, include_lowest=False)
        else:
           new_col = column
           bins = []
        return new_col, bins

    # helper function (should not be called from other functions)
    def normalize(column):
        print("DEB Normalize")
        h = abs(column.min())
        new_col = column + h
        return new_col

    def discretization(self):
        print("DEB Discretization")
        replacements = {}
        bins = {}
        for i in range(0, self.df.shape[1]):  # for each feature
            bins[i] = []
            col = self.df.as_matrix()[:, i]
            flag_str = False
            flag_float = False
            flag_negative = False

            for j in col:
                if type(j) is str: flag_str = True
                elif type(j) is float: flag_float = True
                elif type(j) is int and j < 0: flag_negative = True

            if flag_str:
                continue
            elif flag_negative:
                new_col = self.normalize(col)
                replacements[i] = new_col
                bins[i] = []
            elif flag_float:
                new_col, new_bins = self.discretize(col)
                replacements[i] = new_col
                bins[i] = new_bins
            for k, v in replacements.items():
                self.df.iloc[:, k] = v

    def preprocess(self, removeColumnsWithMissingValues = False):
        print("DEB Preprocessing")
        m = self.df.as_matrix()

        # it is possible to encode enumerable features and to remove missing values
        with open('enumerable_columns.txt') as f:  # e.g., self.enumerable_columns = [0, 5, 8]
            self.enumerable_columns = f.read()
            if self.enumerable_columns.__contains__(','):
                self.enumerable_columns = list(map(int, self.enumerable_columns.split(',')))
            else:
                self.enumerable_columns = [int(self.enumerable_columns)]
            print("enumerable columns are: " + str(self.enumerable_columns))
        le = preprocessing.LabelEncoder()
        for col in self.enumerable_columns:
            # if the column is enumerable
            self.df[self.header[col]] = le.fit_transform(self.df[self.header[col]])  #  A -> 0, B -> 1, ...

        #  remove cols with missing values (NaN), even though you risk to reduce too much the dataset
        if removeColumnsWithMissingValues:
            for i in range(0, m.shape[1]):
                if True in m[:, i]:
                    self.df = numpy.delete(self.df, 0, i)  # delete column


############## MPL architecture #######################
    def createTrainingAndTestSet(self):
        print("DEB Create Training set. Using formula 80-20%")
        self.trainSet, self.testSet = train_test_split(self.df, test_size=0.20)

    # hearth of the algorithm!
    def createTSnew(self):
        print("DEB Create TS new")
        for i in range(0, self.trainSet.shape[0]):
            for j in range(0, self.repeatSometimes):
                # choose small random subset of features X_hat
                X_hat = [int(self.trainSet.shape[1] * random.random()) for i in range(0, self.dim_random_subset)]
                # insert into TSnew the sample: (x1...X_hat = 0 ... xk ; x1...xk)
                row = numpy.copy(self.trainSet.as_matrix()[i, :])
                for feature in X_hat:  # here you set the random features to 0. X_hat represents the indices of such features
                    row[feature] = 0
                self.TSnew_X = self.TSnew_X.append(pandas.DataFrame(row.reshape(-1, len(row))))  # append row to TSnew_X
                copy = numpy.copy(self.trainSet.as_matrix()[i, :])
                self.TSnew_Y = self.TSnew_Y.append(pandas.DataFrame(copy.reshape(-1, len(copy))))  # Y = x1...xk

############## Train & Predict ########################
    def train(self):
        print("DEB Training with TSnew")
        self.MLP = MLPRegressor(activation='relu', alpha=1e-05, batch_size='auto', beta_1=0.9,
                                 beta_2=0.999, early_stopping=False, epsilon=1e-08,
                                 hidden_layer_sizes=len(self.TSnew_Y.columns), learning_rate='constant',
                                 learning_rate_init=0.001, max_iter=200, momentum=0.9,
                                 nesterovs_momentum=True, power_t=0.5, random_state=1, shuffle=True,
                                 solver='lbfgs', tol=0.0001, validation_fraction=0.1, verbose=False,
                                 warm_start=False)
        self.MLP.fit(self.TSnew_X, self.TSnew_Y)

    def predict(self):
        print("DEB Test")

        testSetNew_X = pandas.DataFrame()
        testSetNew_Y = pandas.DataFrame()

        # preparing the test set - here you do the same as in function createTSnew:
        if not os.path.isfile('testSetNew_X{}-{}.csv'.format(self.repeatSometimes, self.dim_random_subset)):
            for i in range(0, self.testSet.shape[0]):
                # choose small random subset of features X_hat
                X_hat = [int(self.testSet.shape[1] * random.random()) for i in range(0, self.dim_random_subset)]
                # insert into TSnew the sample: (x1...X_hat = 0 ... xk ; x1...xk)
                row = numpy.copy(self.testSet.as_matrix()[i, :])
                for feature in X_hat:  # here you set the random features to 0. X_hat represents the indices of such features
                    row[feature] = 0
                testSetNew_X = testSetNew_X.append(pandas.DataFrame(row.reshape(-1, len(row))))
                copy = numpy.copy(self.testSet.as_matrix()[i, :])
                testSetNew_Y = testSetNew_Y.append(pandas.DataFrame(copy.reshape(-1, len(copy))))  # Y = x1...xk
            testSetNew_Y.to_csv('testSetNew_X{}-{}.csv'.format(self.repeatSometimes, self.dim_random_subset))
            testSetNew_Y.to_csv('testSetNew_Y{}-{}.csv'.format(self.repeatSometimes, self.dim_random_subset))
        else:  # if the needed DataFrames have already been calculated, simply load them from disk
            self.trainSet = self.trainSet.from_csv('testSetNew_X{}-{}.csv'.format(self.repeatSometimes, self.dim_random_subset))
            self.trainSet = self.trainSet.from_csv('testSetNew_Y{}-{}.csv'.format(self.repeatSometimes, self.dim_random_subset))

        # predictions
        self.MLP.predict(testSetNew_X)
        print("Score of method (repetitions={}, subset={}): {}%".format(self.repeatSometimes, self.dim_random_subset, self.MLP.score(testSetNew_X, testSetNew_Y) * 100))

########################## Helper functions ####################
    def writeCSV(self):
        print("DEB WriteCSV")
        self.trainSet.to_csv('trainSet{}-{}.csv'.format(self.repeatSometimes, self.dim_random_subset))
        self.testSet.to_csv('testSet{}-{}.csv'.format(self.repeatSometimes, self.dim_random_subset))
        self.TSnew_X.to_csv('TSnew_X{}-{}.csv'.format(self.repeatSometimes, self.dim_random_subset))
        self.TSnew_Y.to_csv('TSnew_Y{}-{}.csv'.format(self.repeatSometimes, self.dim_random_subset))

    def readCSV(self):
        print("DEB ReadCSV")
        self.trainSet = self.trainSet.from_csv('trainSet{}-{}.csv'.format(self.repeatSometimes, self.dim_random_subset))
        self.testSet = self.testSet.from_csv('testSet{}-{}.csv'.format(self.repeatSometimes, self.dim_random_subset))
        self.TSnew_X = self.TSnew_X.from_csv('TSnew_X{}-{}.csv'.format(self.repeatSometimes, self.dim_random_subset))
        self.TSnew_Y = self.TSnew_Y.from_csv('TSnew_Y{}-{}.csv'.format(self.repeatSometimes, self.dim_random_subset))

idx=1
for r in range(2, 14, 3):  # go 3 by 3
    for s in range(2, 14, 3):  # go 3 by 3
        print("----------------------- prove #{}, repeatSometimes={}, dim_random_subset={}".format(idx, r, s))
        idx = idx + 1
        NeuralNetwork(repeatSometimes=r, dim_random_subset=s)
