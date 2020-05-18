"""
    * FloydWarshall.py
    *
    * Implementation of Floyd Warshall Algorithm
    *
    *Execution python FloydWarshall.py (filename)
    *Right now reads file without the V or F's and needs the vertex and faces at the top of the file
    +LAST EDIT November 28st!!
    *NO LIBS.
    *
    """
import math
from collections import defaultdict
from random import random

# This is equivalent to what the default dict does
#graph = {}
#for i in range(numNodes):
#    graph[i] = []

def readGraphFromFile():
    graph = defaultdict(list)
    
    filename = "block.obj"
    file = open(filename, 'r')
    
    # for each line in the file
    for line in file.read().split('\n'):
        # skip over comment lines, blank lines
        if not line or line[0] == '#':
            pass
    
        # face line
        # check if line is one we care about
        elif line[0] == 'f':
            data = line.split()
            if len(data) != 4:
                continue
            #f, s1, s2, s3 = data
            
            v1 = int(data[1])
            v2 = int(data[2])
            v3 = int(data[3])
            
            edges = [(v1, v2), (v1, v3), (v2, v3), (v2, v1), (v3, v1), (v3, v2)]
            for u, v in edges:
                # generate a random weight in the range 0-100
                #random.randint(0, 100)
                # generate a random weight in the range 0-1
                weight = random()
                # make a tuple to vertex and weight
                edge = (v, weight)
                # append to edge list for the starting vertex
                graph[u].append(edge)

                    # undirected graph so also need an edge going the other way
                    # same or different random weight?
                    
                    # keep track of these for GUI version
                    # vertex line
                    elif line[0] == 'v':
                        pass
                            
                            return graph


def floyd_warshall(graph):
    V = len(graph)+1
    
    #let dist be a |V| × |V| array of minimum distances initialized to ∞ (infinity)
    dist = [[math.inf for i in range(V)] for j in range(V)]
    
    # let next be a |V| × |V| array of vertex indices initialized to null
    next = [[None for i in range(V)] for j in range(V)]
    
    #for each edge (u,v)
    for u in graph:
        for v, weight in graph[u]:
            dist[u][v] = weight
            next[u][v] = v

#for each vertex v
for v in graph:
    dist[v][v] =0
    next[v][v] = v
    #for k from 1 to |V| // standard Floyd-Warshall implementation
    for k in range(V):
        #for i from 1 to |V|
        for i in range (V):
            #for j from 1 to |V|
            for j in range (V):
                if dist[i][j] > dist[i][k] + dist[k][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]
                    next[i][j] = next[i][k]

return dist, next




#procedure Path(u, v)
def getPath(next, u, v):
    if not next[u][v]:
        return []
            path = [u]
            while u != v:
                u = next[u][v]
                path.append(u)
                    return path




def main():
    graph = readGraphFromFile()
    
    dist, next = floyd_warshall(graph)
    
    # u, v = input("Enter two nodes").split()
    
    print(getPath(next, 3, 5))

main()
