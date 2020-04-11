#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Apr 10 09:06:18 2020

@author: sudhir
"""

import open3d as o3d
import numpy as np
import time
import pytest
import os

ref_vertices = np.array([[10, 10, 0],[20, 10, 0],[0, 0, 0],[10, 0, 0],[20, 0, 0],[10, -10, 0],[20, -10, 0]]);

ref_vertex_colors = np.array([[1, 0, 0],[0, 1, 0],[0, 0, 1],[1, 0, 0],[0, 1, 0],[1, 0, 0],[1, 0, 0]])

ref_triangles = np.array([[0, 2, 3],  [0, 1, 3], [1, 3, 4], [2, 3, 5], [3, 5, 6],[3, 4, 6]])

mesh = o3d.geometry.TriangleMesh()
mesh.vertices = o3d.utility.Vector3dVector(ref_vertices)
mesh.triangles = o3d.utility.Vector3iVector(ref_triangles)
mesh.vertex_colors = o3d.utility.Vector3dVector(ref_vertex_colors)

#Output Result to be expected
gt_connected_components = [[0, 3, 5, 6], [1,4], [2]]

def test_identically_colored_connected_components():
    connected_components = mesh.identically_colored_connected_components()
    np.testing.assert_equal(connected_components, gt_connected_components)
    
    
 
    
    