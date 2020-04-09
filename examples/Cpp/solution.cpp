// #include "Open3D/Geometry/TriangleMesh.h"
#include <iostream>
#include <set> 
#include <queue> 
#include <memory>
#include <thread>
#include <Open3D/Open3D.h>

using namespace std;


void bfs(int source, std::vector<std::unordered_set<int>> &graph, std::vector<Eigen::Matrix<double, 3, 1> >& colors1, std::vector<bool>& visited, std::vector<std::vector<int>>& result){
    vector<int> currentResult;
    queue<int> Q;
    Q.push(source);
    visited[source] = true;
    currentResult.push_back(source);
    while(!Q.empty()){
        int node = Q.front();
        Q.pop();
        for(auto it= graph[node].begin(); it != graph[node].end(); it++){
            if(!visited[*it] and colors1[node]==colors1[*it]){
                visited[*it] = true;
                Q.push(*it);
                currentResult.push_back(*it);
            }
        }
    }
    sort(currentResult.begin(), currentResult.end());
    result.push_back(currentResult);
}



std::vector < std::vector <int> > IdenticallyColoredConnectedComponents(std::vector<Eigen::Matrix<double, 3, 1> > &vertices1, std::vector<Eigen::Matrix<int, 3, 1> > &triangle1, std::vector<Eigen::Matrix<double, 3, 1> > &colors1){
  
    std::vector <bool> visited(vertices1.size(), false);
    std::vector < std::vector <int> > result; // Result array
    std:: vector<unordered_set<int>> graph(vertices1.size());
    for(int i=0; i<triangle1.size(); i++){
        graph[triangle1[i][0]].insert(triangle1[i][1]);
        graph[triangle1[i][0]].insert(triangle1[i][2]);
        graph[triangle1[i][1]].insert(triangle1[i][0]);
        graph[triangle1[i][1]].insert(triangle1[i][2]);
        graph[triangle1[i][2]].insert(triangle1[i][0]);
        graph[triangle1[i][2]].insert(triangle1[i][1]);
    }
    for(int i = 0; i<vertices1.size(); i++){
        if(visited[i] == false){
            //Call BFS
            bfs(i, graph, colors1, visited, result);
    // std::cout << mesh_ptr->vertices_.size();
        }
    }
    return result;
}


int main(int argc, char *argv[]){
using namespace open3d;
utility::SetVerbosityLevel(utility::VerbosityLevel::Debug);
// Read the triangular mesh
std::string option(argv[1]);
auto mesh_ptr = std::make_shared<geometry::TriangleMesh>();
if (io::ReadTriangleMesh(argv[1], *mesh_ptr)) {
            utility::LogInfo("Successfully read {}\n", argv[1]);
    }
    else {
        utility::LogWarning("Failed to read {}\n\n", argv[1]);
        return 1;
    }
    // mesh_ptr->ComputeVertexNormals();

    std::vector<Eigen::Matrix<double, 3, 1> > vertices1;
    std::vector<Eigen::Matrix<int, 3, 1> > triangle1;
    std::vector<Eigen::Matrix<double, 3, 1> > colors1;
    vertices1 = mesh_ptr->vertices_;
    triangle1 = mesh_ptr->triangles_;
    colors1 = mesh_ptr->vertex_colors_;

    std::vector < std::vector <int> > connected_components; // Result array

    connected_components = IdenticallyColoredConnectedComponents(vertices1, triangle1, colors1);
    
    // std::cout << "result print" << endl;
    sort(connected_components.begin(),connected_components.end());
    for(int i = 0; i<connected_components.size(); i++){
        for(int j = 0; j<connected_components[i].size(); j++){
            std::cout << connected_components[i][j] << " ";
        }
    std::cout << endl; 
    }
    std::freopen("results.txt","w",stdout);
    
    for(int i = 0; i<connected_components.size(); i++){
        for(int j = 0; j<connected_components[i].size(); j++){
            std::cout << connected_components[i][j] << " ";
        }
        std::cout << endl; 
    }
    fclose (stdout);
}