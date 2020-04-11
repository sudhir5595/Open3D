// #include "Open3D/Geometry/TriangleMesh.h"
#include <iostream>
#include <set> 
#include <queue> 
#include <memory>
#include <thread>
#include <Open3D/Open3D.h>

using namespace open3d;


int main(int argc, char *argv[]){

utility::SetVerbosityLevel(utility::VerbosityLevel::Debug);
// Read the triangular mesh
std::string option(argv[1]);
auto mesh = std::make_shared<geometry::TriangleMesh>();
if (io::ReadTriangleMesh(argv[1], *mesh)) {
            utility::LogInfo("Successfully read {}\n", argv[1]);
    }
    else {
        utility::LogWarning("Failed to read {}\n\n", argv[1]);
        return 1;
    }
    
    std::vector < std::vector <int> > connected_components; // Result array

    connected_components = mesh->IdenticallyColoredConnectedComponents();
    
    //  "print the result"
    
    sort(connected_components.begin(),connected_components.end());
    for(int i = 0; i<int(connected_components.size()); i++){
        for(int j = 0; j<int(connected_components[i].size()); j++){
            std::cout << connected_components[i][j] << " ";
        }
    std::cout << std::endl; 
    }

    // Save the result in .txt form
    std::freopen("results.txt","w",stdout);
    
    for(int i = 0; i<int(connected_components.size()); i++){
        for(int j = 0; j<int(connected_components[i].size()); j++){
            std::cout << connected_components[i][j] << " ";
        }
        std::cout << std::endl; 
    }
    fclose (stdout);
}
