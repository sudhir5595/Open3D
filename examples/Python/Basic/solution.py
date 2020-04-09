#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Apr  7 08:40:43 2020

@author: sudhir
"""
import sys
import numpy as np
import open3d as o3d

a = str(sys.argv[1])
mesh = o3d.io.read_triangle_mesh(a)
#print(mesh)
vertices1 = np.asarray(mesh.vertices)
triangles1 = np.asarray(mesh.triangles)

colors1 = np.asarray(mesh.vertex_colors)

from collections import defaultdict 
  
# This class represents a directed graph 
# using adjacency list representation 
class Graph: 
  
    # Constructor 
    def __init__(self): 
  
        # default dictionary to store graph 
        self.graph = defaultdict(list) 
  
    # function to add an edge to graph 
    def addEdge(self,u,v): 
        self.graph[u].append(v)
        self.graph[v].append(u)
  
    # Function to print a BFS of graph 
    def BFS(self, source, colors1, visited, result):
        
        currentResult = []
        # Create a queue for BFS 
        queue = [] 
        # Mark the source node as  
        # visited and enqueue it 
        queue.append(source) 
        visited[source] = True
        currentResult.append(source)
  
        while queue: 
            # Dequeue a vertex from  
            # queue and print it 
            node = queue.pop(0)

            for i in self.graph[node]:
                out = 0
                if(colors1[node,0] == colors1[i,0] and colors1[node,1] == colors1[i,1] and colors1[node,2] == colors1[i,2]):
                    out = 1
                if(visited[i] == False and out == 1):
                    visited[i] = True
                    queue.append(i)
                    currentResult.append(i)
                                 
        currentResult.sort()
        result.append(currentResult)




def identically_colored_connected_components(vertices1, triangles1, colors1):
    # Mark all the vertices as not visited 
    visited = [False] * (len(vertices1)) 
    result = [[]]
    # Create a graph given in  the above diagram 
    g = Graph()
    for i in range(len(triangles1)):
        g.addEdge(triangles1[i,0],triangles1[i,1])
        g.addEdge(triangles1[i,1],triangles1[i,2])
        g.addEdge(triangles1[i,0],triangles1[i,2])

    for i in range(len(vertices1)):
        if(visited[i] == False):
            g.BFS(i, colors1, visited, result)

    result.sort()
    result = result[1:len(result)]
    return result


connected_components = [[]]

connected_components = identically_colored_connected_components(vertices1, triangles1, colors1)
#Print the result
for i in connected_components:
    print(*i)
#Write text file
with open('results.txt', 'w') as f:
    for item in connected_components:
        for i in item:
            f.write(str(i) + " ")
        f.write("\n")
