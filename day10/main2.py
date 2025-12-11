from pathlib import Path
from itertools import product
import numpy as np
import sys
import tqdm
from sympy import solve
from sympy import symbols
import string
from functools import reduce
from scipy.optimize import linprog

inp = sys.stdin.read().strip()
lines = inp.splitlines()

def to_list(inp):
    return list(map(int, inp[1:-1].split(',')))

syms = symbols(" ".join(string.ascii_lowercase), integer=True)

s = 0
for l in lines:
    tqdm.tqdm.write(l)
    _, *btns, jolt = l.split()
    jolt = np.array(list(map(int, jolt[1:-1].split(','))))
    btns = list(map(to_list, btns))

    a = np.zeros((len(jolt), len(btns)), dtype=int)
    for i, j in enumerate(jolt):
        for k, b in enumerate(btns):
            if i in b:
                a[i][k] = 1

    res = linprog([1]*len(btns), A_eq=a, b_eq=jolt, bounds=[(0, sum(jolt))]*len(btns), method="highs", integrality=1)
    s += int(sum(res.x))
    print(res.x)
    print(np.dot(a, res.x), jolt)
    # assert np.all(np.dot(a, res.x) == jolt)
# 53523 too high
# 21771 too low
print(s)

