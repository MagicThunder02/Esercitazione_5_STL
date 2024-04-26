#include "PolygonalMesh.hpp"

namespace PolygonalLibrary {

bool checkEdgesLength(PolygonalMesh& mesh) {
    for (unsigned int e = 0; e < 2; e++)
    {
        cout << "Edge id:" << e << endl;
        const unsigned int origin = mesh.Cell1DVertices[e][0];
        const unsigned int end = mesh.Cell1DVertices[e][1];

        const double originX = mesh.Cell0DCoordinates[origin][0];
        const double originY = mesh.Cell0DCoordinates[origin][1];

        const double endX = mesh.Cell0DCoordinates[end][0];
        const double endY = mesh.Cell0DCoordinates[end][1];

        cout << "originX: " << originX << endl;
        cout << "originY: " << originY << endl << endl;

        cout << "endX: " << endX << endl;
        cout << "endY: " << endY << endl << endl;
    }

    return true;
}
}
