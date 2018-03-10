from sklearn import svm
from sklearn.cross_validation import train_test_split

def holdoutMethod(dataSet):
    """
    This is the holdout method. It is the most basic one, in which the dataset is split into 2. In this case, you take
    70% of samples for training and 30% for tests.
    :param dataSet: of type DataFrame
    """

    # Prepare the dataset
    # function train_test_split() splits the dataset into train and test sets. For each of them,
    # it also separates dependent and independent features (i.e., columns, attributes)
    X_train, X_test = train_test_split(dataSet, test_size=0.30)
    X_train = X_train.as_matrix()
    X_test = X_test.as_matrix()
    Y_train = X_train[:, 0:1]  # letter
    X_train = X_train[:, 1:16]
    Y_test = X_test[:, 0:1]  # letter
    X_test = X_test[:, 1:16]

    # fit a model. This is classification because the dependent variable - letter - is discrete (a integer number)
    lm = svm.SVC(gamma=0.001, C=100.)  # Support Vector Machine

    model = lm.fit(X_train, Y_train)
    predictions = lm.predict(X_test)
    print("Score of Holdout method: {}%".format(model.score(X_test, Y_test) * 100))