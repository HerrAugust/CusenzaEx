'''
Requires Python 3

@author: Github - HerrAugust
Note of the author: this code is given as is, without guarantees. It has been written only to
understand some concepts and not with distribution aims in mind!

Exercise #1: Given a vector V with N elements and a matrix NxN that
contains numbers and ? somewhere, find a possible candidate for all the ?s.
'''
import collections
from math import sqrt
from random import randint

# Functions:
# determines fibonacci number after n
def fibonacci_after(n):
    return ((1 + sqrt(5)) ** n - (1 - sqrt(5)) ** n) / (2 ** n * sqrt(5))  # source: https://stackoverflow.com/questions/494594/how-to-write-the-fibonacci-sequence

# determines the prime number after n. Source: https://gist.github.com/ldong/808d5403c5e3b19f2f05
def prime_after(n):
    return find_prime_in_range(n, 2 * n)

# helper function of prime_after()
def find_prime_in_range(a, b):
    for p in range(a, b):
        for i in range(2, p):
            if p % i == 0:
                break
        else:
            return p
    return None

# determine if n is a perfect square
def isSquare(n):
    return n > 0 and sqrt(n) % 1 == 0

# determine if n is a prime number; ref. https://stackoverflow.com/questions/4114167/checking-if-a-number-is-a-prime-number-in-python
def isPrime(n):
    return all(n % i for i in range(2, n))

# determine if n is a number of a Fibonacci Series; ref. https://stackoverflow.com/questions/40639509/jschecking-if-number-belongs-to-fibonacci-sequencewithout-loop
def isFib(n):
    return n > 0 and isSquare(5 * (n * n) - 4) or isSquare(isSquare(5 * (n * n) + 4))

# prints a matrix
def print_matrix(matrix):
    s = [[str(e) for e in row] for row in matrix]
    lens = [max(map(len, col)) for col in zip(*s)]
    fmt = '\t'.join('{{:{}}}'.format(x) for x in lens)
    table = [fmt.format(*row) for row in s]
    print('\n'.join(table))

# Main:
V = []
M = []
M_prime =[]
n = -1 # elements in the matrix

# Reading matrix and vector
fname = 'input.txt'
f = open(fname,'r')
for line in f.readlines():
    if line.startswith('V'):
        line = line.replace('V=(', '')
        line = line.replace(')', '')
        V = [int(s) for s in line.split(' ')]
print('read V='+str(V))

f.seek(0,0)
n = len(V)
M = n*[n*[-1]]
row = 0
for line in f.readlines():
    if line.startswith('M'):
        line = line.replace('M=(', '')
        line = line.replace(')', '')
        line = line.replace('?','-1') # otherwise I could not create a matrix of integer
        for l in line.split('; '):
            M[row] = [int(s) for s in l.split(' ')]
            row = row + 1
f.close()
print('read M=')
print_matrix(M)

# Different Prediction Models are presented here. In some of them there is no
# learning (random), and in some others there is. Following possibilities for ? are:
#     1. Random choice;
#     2. Frequency-based algorithm;
#     3. Finding clues using the vector V

# 1. A random prediction
M_prime = [[-1]*n for i in range(n)]
for i in range(n):
    for j in range(n):
        M_prime[i][j] = M[i][j]
        if M[i][j] == -1:
            randomnum = V[randint(0, len(V) - 1)]
            M_prime[i][j] = randomnum
print("M' with random prediction: ")
print_matrix(M_prime)

# 2. Frequency-based algorithm:
# Order V by frequence. Example: V = (1 1 2 1) => V = (1 2)
counts = collections.Counter(V)
V_frequencies = sorted(V, key=counts.get, reverse=True)
i = 1
while i < len(V_frequencies):
    if V_frequencies[i-1] == V_frequencies[i]:
        V_frequencies.remove(i)
        i -= 1
    i += 1

# Insert numbers into matrix using V as a circular array
counter = 0
M_prime = [[-1]*n for i in range(n)]
for i in range(n):
    for j in range(n):
        M_prime[i][j] = M[i][j]
        if M[i][j] == -1:
            M_prime[i][j] = V_frequencies[counter]
            counter += 1
            if counter == len(V_frequencies):
                counter = 0
print("\nM' with frequency-based algorithm: ")
print_matrix(M_prime)

# 3. Finding clues using the vector V
M_prime = y = [[-1]*n for i in range(n)]
clue = 'None'  # if none => random

# check if V is a part of Fibonacci Series
previous_prime = isPrime(V[0])
clue = 'Fib'
for i in range(n):
    if not isFib(V[i]):
        clue = 'None'
        break

# check if V is made up of prime numbers
clue = 'Primes'
for i in range(n):
    if not isPrime(V[i]):
        clue = 'None'
        break

# check if adjacent items have the same difference
clue = 'SameDiff'
diff = V[1] - V[0]
for i in range(2, n):
    if V[i] - V[i-1] != diff:
        clue = 'None'
        break

if clue == 'Fib':
    for i in range(n):
        for j in range(n):
            M_prime[i][j] = M[i][j]
            if M[i][j] == -1:
                fib = 1
                if j > 0:
                    fib = fibonacci_after(M[i][j-1])
                M_prime[i][j] = fib
elif clue == 'Primes':
    for i in range(n):
        for j in range(n):
            M_prime[i][j] = M[i][j]
            if M[i][j] == -1:
                prime = 1
                if j > 0:
                    prime = prime_after(M[i][j - 1])
                M_prime[i][j] = prime
elif clue == 'SameDiff':
    for i in range(n):
        for j in range(n):
            M_prime[i][j] = M[i][j]
            if M[i][j] == -1:
                this_num = -1  # the number that we will set in this location
                if j > 0:
                    this_num = M_prime[i][j-1] + diff
                else:
                    this_num = M[i][j+1] - diff
                M_prime[i][j] = this_num
else:  # random numbers
    for i in range(n):
        for j in range(n):
            M_prime[i][j] = M[i][j]
            if M[i][j] == -1:
                randomnum = V[randint(0, len(V) - 1)]
                M_prime[i][j] = randomnum
print('\nClue: ' + clue)
print("\nM' finding clues using the vector V: ")
print_matrix(M_prime)
