#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

namespace PolygonalLibrary {
bool ImportMesh(const string& filepath,
                PolygonalMesh& mesh)
{

    if(!ImportCell0Ds(filepath + "/Cell0Ds.csv",
                       mesh))
    {
        return false;
    }
    else
    {
        /*cout << "Cell0D marker:" << endl;
        for(auto it = mesh.Cell0DMarkers.begin(); it != mesh.Cell0DMarkers.end(); it++)
        {
            cout << "key:\t" << it -> first << "\t values:";
            for(const unsigned int id : it -> second)
                cout << "\t" << id;

            cout << endl;
        }*/
    }

    if(!ImportCell1Ds(filepath + "/Cell1Ds.csv",
                       mesh))
    {
        return false;
    }
    else
    {
        /* cout << "Cell1D marker:" << endl;
        for(auto it = mesh.Cell1DMarkers.begin(); it != mesh.Cell1DMarkers.end(); it++)
        {
            cout << "key:\t" << it -> first << "\t values:";
            for(const unsigned int id : it -> second)
                cout << "\t" << id;

            cout << endl;
        }*/
    }

    if(!ImportCell2Ds(filepath + "/Cell2Ds.csv",
                       mesh))
    {
        return false;
    }

    return true;

}
// ***************************************************************************
bool ImportCell0Ds(const string &filename,
                   PolygonalMesh& mesh)
{

    ifstream file;
    file.open(filename);


    if(file.fail()){
       return false;
    }

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    listLines.pop_front();

    mesh.NumberCell0D = listLines.size();

    if (mesh.NumberCell0D == 0)
    {
        cerr << "There is no cell 0D" << endl;
        return false;
    }

    mesh.Cell0DId.reserve(mesh.NumberCell0D);
    mesh.Cell0DCoordinates.reserve(mesh.NumberCell0D);

    for (string& line : listLines)
    {
        std::replace(line.begin(), line.end(), ';', ' ');
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        Vector2d coord;

        converter >>  id >> marker >> coord(0) >> coord(1);

        mesh.Cell0DId.push_back(id);
        mesh.Cell0DCoordinates.push_back(coord);

        if( marker != 0)
        {
            //            if (mesh.Cell0DMarkers.find(marker) == mesh.Cell0DMarkers.end())
            //                mesh.Cell0DMarkers.insert({marker, {id}});
            //            else
            //                mesh.Cell0DMarkers[marker].push_back(id);


            auto ret = mesh.Cell0DMarkers.insert({marker, {id}});
            if(!ret.second)
                (ret.first)->second.push_back(id);
        }

    }
    file.close();
    return true;
}
// ***************************************************************************
bool ImportCell1Ds(const string &filename,
                   PolygonalMesh& mesh)
{

    ifstream file;
    file.open(filename);

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    listLines.pop_front();

    mesh.NumberCell1D = listLines.size();

    if (mesh.NumberCell1D == 0)
    {
        cerr << "There is no cell 1D" << endl;
        return false;
    }

    mesh.Cell1DId.reserve(mesh.NumberCell1D);
    mesh.Cell1DVertices.reserve(mesh.NumberCell1D);

    for (string& line : listLines)
    {
        std::replace(line.begin(), line.end(), ';', ' ');
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        Vector2i vertices;

        converter >>  id >> marker >> vertices(0) >> vertices(1);

        mesh.Cell1DId.push_back(id);
        mesh.Cell1DVertices.push_back(vertices);

        if( marker != 0)
        {
            //            if (mesh.Cell1DMarkers.find(marker) == mesh.Cell1DMarkers.end())
            //                mesh.Cell1DMarkers.insert({marker, {id}});
            //            else
            //                mesh.Cell1DMarkers[marker].push_back(id);


            auto ret = mesh.Cell1DMarkers.insert({marker, {id}});
            if(!ret.second)
                (ret.first)->second.push_back(id);
        }
    }

    file.close();

    return true;
}
// ***************************************************************************
bool ImportCell2Ds(const string &filename,
                  PolygonalMesh& mesh)
{

    ifstream file;
    file.open(filename);

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    listLines.pop_front();

    mesh.NumberCell2D = listLines.size();

    if (mesh.NumberCell2D == 0)
    {
        cerr << "There is no cell 2D" << endl;
        return false;
    }

    mesh.Cell2DId.reserve(mesh.NumberCell2D);
    mesh.Cell2DVertices.reserve(mesh.NumberCell2D);
    mesh.Cell2DEdges.reserve(mesh.NumberCell2D);

    for (string& line : listLines)
    {
        std::replace(line.begin(), line.end(), ';', ' ');
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        unsigned int NumVertices;
        unsigned int NumEdges;
        vector<unsigned int> vertices;
        vector<unsigned int> edges;

        converter >>  id;
        converter >> marker;
        converter >>  NumVertices;

        //vertices.reserve(NumVertices);

        for(unsigned int i = 0; i < NumVertices; i++){
            unsigned int tmp;
            converter>>tmp;
            vertices.push_back(tmp);
            //converter >> vertices[i];
            //cout << vertices[i] << endl;
        }

        cerr << vertices[0] << endl;
        converter >> NumEdges;
        //edges.reserve(NumEdges);
        for(unsigned int i = 0; i < NumEdges; i++){
            unsigned int tmp;
            converter>>tmp;
            edges.push_back(tmp);
            //converter >> edges[i];
        }

        mesh.Cell2DId.push_back(id);
        mesh.Cell2DMarkers.insert({marker, {id}});
        for(unsigned int i=0; i<mesh.NumberCell2D; i++){
            for(unsigned int k=0;k<vertices.size();k++){
                mesh.Cell2DVertices[i].push_back(vertices[k]);
            }
        }
        //mesh.Cell2DVertices.push_back(vertices);
        mesh.Cell2DEdges.push_back(edges);

    }
    file.close();
    return true;
}

}
