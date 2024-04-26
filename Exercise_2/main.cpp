#include "PolygonalMesh.hpp"
#include "Utils.hpp"
#include <iostream>

using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;

int main()
{
    PolygonalMesh mesh;

    string filepath = "PolygonalMesh";

    if(!ImportMesh(filepath,
                    mesh))
    {
        return 1;
    }

    // Execute some tests

    checkEdgesLength(mesh);

    return 0;
}

