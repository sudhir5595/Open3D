import sys
import numpy as np
import open3d as o3d

a = str(sys.argv[1])
mesh = o3d.io.read_triangle_mesh(a)

connected_components = mesh.identically_colored_connected_components()
#Print the result
for i in connected_components:
    print(*i)
#Write text file
with open('results.txt', 'w') as f:
    for item in connected_components:
        for i in item:
            f.write(str(i) + " ")
        f.write("\n")
