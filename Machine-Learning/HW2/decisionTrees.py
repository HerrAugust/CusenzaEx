from numpy import transpose
from sklearn import tree
from sklearn.cross_validation import train_test_split
from sklearn.metrics import accuracy_score


def decisionTrees(dataSet):
    """
    Classification via Decision Trees method. I use here the proportions 70-30% for training and test sets
    :param dataSet: of type DataFrame
    """
    X_train, X_test = train_test_split(dataSet, test_size=0.30)
    X_train = X_train.as_matrix()
    X_test = X_test.as_matrix()
    Y_train = X_train[:, 0:1]  # letter
    X_train = X_train[:, 1:16]
    Y_test = X_test[:, 0:1]  # letter
    X_test = X_test[:, 1:16]

    clf = tree.DecisionTreeClassifier(criterion='gini', splitter='best')
    clf.fit(X_train, Y_train)
    Y_predicted = clf.predict(X_test)
    print("Decision Tree - accuracy with Gini index: {}%", accuracy_score(Y_test, Y_predicted)*100)
