# import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

# (1,1)
def es1c1(sigma):
    x = np.ones(10)
    best = x.copy()
    iter = 0
    while np.sum(x * x) > 0.005 and iter < 10000000:
        if iter % 100000 == 0:
            print('.', end='')
        iter += 1
        x += np.random.normal(0, sigma, 10)
        if np.sum(best * best) > np.sum(x * x):
            best = x.copy()
    print()
    return best

# (1+1)
def es1p1(sigma):
    x = np.ones(10)
    best = x.copy()
    iter = 0
    while np.sum(x * x) > 0.005 and iter < 10000000:
        if iter % 100000 == 0:
            print('.', end='')
        iter += 1
        y = x + np.random.normal(0, sigma, 10)
        if np.sum(best * best) > np.sum(y * y):
            best = y.copy()
        if np.sum(y * y) < np.sum(x * x):
            x = y.copy()
    print()
    return best

def run(es, fname):
    arr2d = []
    for _ in range(10):
        arr = []
        for sigma in [0.01, 0.1, 1.]:
            arr.append(es(sigma))
        arr2d.append(arr)
    df = pd.DataFrame(arr2d, columns=['0.01', '0.1', '1.0'])
    df.to_csv(fname)

run(es1p1, 'es1p1.csv')
run(es1c1, 'es1c1.csv')
