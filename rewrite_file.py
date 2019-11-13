import random

line = ''
datalines = []

with open("fb-wosn-friends.edges", 'r') as f:
    line = f.read()
    for l in line.split('\n'):
        datalines.append(l.split()[:2])

def toStr(arr):
    s = "_".join([str(x) for x in arr])
    return s


with open("datafile.txt", 'w') as fout:
    edges = set()
    for el in datalines[1:-1]:
        arr = [int(x) for x in el]
        if toStr(arr) not in edges:
            weight = str(random.randint(1, 10))
            fout.write(" ".join([str(x) for x in arr[:2]])+' '+weight+'\n')

        edges.add(toStr(arr))
