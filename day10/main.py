from pathlib import Path
from itertools import product
import numpy as np
import sys
import tqdm
from sympy import solve
from sympy import symbols
import string
from functools import reduce

inp = sys.stdin.read().strip()
lines = inp.splitlines()

def to_list(inp):
    return list(map(int, inp[1:-1].split(',')))

def calc(e, t) -> float | None:
    o = {k:v.subs(t) for k,v in e.items()} | t
    if any(v < 0 for v in o.values()):
        return None
    return float(sum(o.values()))

syms = symbols(" ".join(string.ascii_lowercase), integer=True)

s = 0
for l in tqdm.tqdm(lines):
    _, *btns, jolt = l.split()
    jolt = np.array(list(map(int, jolt[1:-1].split(','))))
    btns = list(map(to_list, btns))

    a = np.zeros((len(jolt), len(btns)))
    for i, j in enumerate(jolt):
        for k, b in enumerate(btns):
            if i in b:
                a[i][k] = 1

    equs = [sum(v*s for v,s in zip(row, syms))-j for row,j in zip(a, jolt)]
    res = solve(equs, *syms)

    free = tuple(reduce(set.union, (v.free_symbols for v in res.values()), set()))
    best = None
    # print(len(free))
    print(res, free)
    if len(free) == 0:
        s += sum(res.values())
        continue

    elif len(free) == 1:
        valid1 = [i for i in range(best or sum(jolt)) if calc(res, {free[0]:i}) is not None]
        for v1 in valid1:
            su = calc(res, {free[0]:v1})

            if su is not None and int(su) == su and (best is None or su < best):
                best = int(su)


    elif len(free) == 2:
        valid1 = [i for i in range(best or sum(jolt)) if calc(res, {free[0]:i}) is not None]
        valid2 = [i for i in range(best or sum(jolt)) if calc(res, {free[1]:i}) is not None]

        for v1 in valid1:
            for v2 in valid2:
                su = calc(res, {free[0]:v1, free[1]: v2})
                if su is not None and int(su) == su and (best is None or su < best):
                    best = int(su)

    elif len(free) == 3:
        valid1 = [i for i in range(best or sum(jolt)) if calc(res, {free[0]:i}) is not None]
        valid2 = [i for i in range(best or sum(jolt)) if calc(res, {free[1]:i}) is not None]
        valid3 = [i for i in range(best or sum(jolt)) if calc(res, {free[2]:i}) is not None]

        for v1 in valid1:
            for v2 in valid2:
                for v3 in valid3:
                    su = calc(res, {free[0]:v1, free[1]: v2, free[2]: v3})
                    if su is not None and int(su) == su and (best is None or su < best):
                        best = int(su)
    else:
        print("PANIC")

    s += best
# 53523 too high
print(s)

