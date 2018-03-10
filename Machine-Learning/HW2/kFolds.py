from sklearn import svm
from sklearn.model_selection import KFold
import numpy


def kFolds(dataSet, k = 10):
    """
    This is the k-fold method
    :param dataSet: of type DataFrame
    :param k: number of subsets to choose
    """
    df_mx = dataSet.as_matrix()
    X = df_mx[:, 1:16]
    Y = df_mx[:, 0:1]

    lm = svm.SVC(gamma=0.001, C=100.)  # Support Vector Machine
    kf = KFold(n_splits=10)  # Define the split - into 10 folds
    i = 0
    accuracies = numpy.zeros(kf.get_n_splits(X))
    for train_index, test_index in kf.split(X):
        print("{}. TRAIN: {} TEST: {}".format(i+1, train_index, test_index))
        X_train, X_test = X[train_index], X[test_index]
        Y_train, Y_test = Y[train_index], Y[test_index]
        # train using X_Train
        model = lm.fit(X_train, Y_train)
        # evaluate against X_Test
        predictions = lm.predict(X_test)
        # save accuracy
        accuracies[i] = model.score(X_test, Y_test)
        i = i + 1

    # find mean accuracy over all rounds
    print("Average accuracy of K-Folds (k={}): {}%".format(numpy.mean(accuracies) * 100, k))
