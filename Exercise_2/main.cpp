#include "PolygonalMesh.hpp"
#include "Utils.hpp"
#include <iostream>

using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;

int main()
{
    // setto la tolleranza dall'utente oppure uso la epsilon di macchina
    double tol;
    cout << "Inserire tolleranza per il controllo sugli errori: "<< endl;
    cin >> tol;
    double  tol2 = max(10*numeric_limits<double>::epsilon(), tol);
    cout << "Tolleranza: "<< tol2 << endl;

    PolygonalMesh mesh;

    string filepath = "PolygonalMesh";

    if(!ImportMesh(filepath,
                    mesh))
    {
        return 1;
    }

    // Execute some tests
    checkEdgesDimension(mesh, tol);

    checkAreasDimension(mesh, tol);

    return 0;
}

