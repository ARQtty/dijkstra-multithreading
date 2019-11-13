with open("datafile.txt", 'r') as fin:
    numE, numV = [int(x) for x in fin.readline().split()]
    adj_list = [[] for x in range(numV)]

    for line in fin:
        fromm, to, weight = [int(x)-1 for x in line.split()]
        # print(fromm, to)
        weight += 1
        adj_list[fromm].append((to, weight))
        adj_list[to].append((fromm, weight))
