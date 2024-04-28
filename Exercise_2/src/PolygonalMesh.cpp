#include "PolygonalMesh.hpp"
#include <cmath>

using namespace std;

namespace PolygonalLibrary {

    void checkEdgesDimension(PolygonalMesh& mesh, double tol) {
        for (unsigned int e = 0; e < mesh.NumberCell1D; e++)
        {

            const unsigned int origin = mesh.Cell1DVertices[e][0];
            const unsigned int end = mesh.Cell1DVertices[e][1];

            const double originX = mesh.Cell0DCoordinates[origin][0];
            const double originY = mesh.Cell0DCoordinates[origin][1];

            const double endX = mesh.Cell0DCoordinates[end][0];
            const double endY = mesh.Cell0DCoordinates[end][1];

            //cout << "originX: " << originX << endl;
            //cout << "originY: " << originY << endl << endl;

            //cout << "endX: " << endX << endl;
            //cout << "endY: " << endY << endl << endl;

            double distance = sqrt(pow((originX-endX),2) + pow((originY-endY),2));
            if (distance < tol) {
                cout << "Edge " << e << " has lenght less than tollerance " << endl;
            }

        }

        cout << "All lengths of the edges have been checked" << endl;
        return;
    }

    void checkAreasDimension(PolygonalMesh& mesh, double tol) {
        // la tolleranza deve essere in proporzione a quella dell'area di un triangolo
        tol = max(pow(tol,2)*sqrt(3)/4, tol);

        for (unsigned int p = 0; p < mesh.NumberCell2D; p++)
        {

            vector<unsigned int> vertices = mesh.Cell2DVertices[p];
            unsigned int verticesNumber = vertices.size();

            // cout << "vertices: " << verticesNumber << endl;

            double area = 0;

            for (unsigned int i = 0; i < verticesNumber-1; i++) {
                unsigned int pointIndex = vertices[i];
                unsigned int nextPointIndex = vertices[i+1];

                double x = mesh.Cell0DCoordinates[pointIndex][0];
                double y = mesh.Cell0DCoordinates[pointIndex][1];

                double nextX = mesh.Cell0DCoordinates[nextPointIndex][0];
                double nextY = mesh.Cell0DCoordinates[nextPointIndex][1];

                area += x*nextY + nextX*y;
            }

            area = area / 2;
            // cout << area << endl;

            if (area < tol) {
                cout << "Polygon " << p << " has area: " << area << " less than tollerance " << endl;
                for (unsigned int i: vertices)
                    cout << i << ' ';
                cout << endl;
            }

        }

        cout << "All areas of the polygon have been checked" << endl;
        return;
    }
}
