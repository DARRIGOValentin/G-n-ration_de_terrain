#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "perlin.h"
#include <QDebug>
#include <time.h>


MyMesh::Color calcColor(MyMesh* _mesh, FaceHandle fh){

    //on va calculer la hauteur moyenne des 3 points de la face
    //pour ensuite déterminer sa couleur;
    float zs [3];
    int i = 0;
    for (MyMesh::FaceVertexIter curVert = _mesh->fv_iter(fh); curVert.is_valid(); curVert ++)
       {
           //qDebug() << "    vertID :" << (*curVert).idx();
            VertexHandle vh = *curVert;
            zs[i] = _mesh->point(vh)[2];
            i++;
            //if(_mesh->point(vh)[2] < -0.4f)
                //qDebug() << _mesh->point(vh)[2];
       }

    float somme = 0;
    for(int i = 0; i < 3; i++){
        somme += zs[i];
    }

    float d = somme/3.0f;


    if (d > 1.2f)  return MyMesh::Color(255, 255, 255);
    else if (d > 1.1f) return MyMesh::Color(200, 201, 176);
    else if (d > 0.9f) return MyMesh::Color(180, 181, 156);
    else if (d > 0.8f) return MyMesh::Color(135, 120, 110);
    else if (d > 0.6f) return MyMesh::Color(155, 60, 60);
    else if (d > 0.45f) return MyMesh::Color(0, 150, 0);
    else if (d > 0.3f) return MyMesh::Color(0, 175, 0);
    else if (d > 0.15f) return MyMesh::Color(0, 200, 0);
    else if (d > 0.0f) return MyMesh::Color(0, 100, 250);

    else if (d <= 0.0){

        //si au moins 1 des points de la faces
        //est audessus du niveau de la mer
        //alors la face est verte
        //sinon elle est bleu
        for(int i = 0; i < 3; i++){
            if (zs[i] > 0.0f) return MyMesh::Color(0, 200, 0);
        }

        return MyMesh::Color(0, 0, 220);
    }
}

MyMesh::Color calcColor_archipel(MyMesh* _mesh, FaceHandle fh)
{
    //fonction basée sur calcColor mais dont l'utilité est strictement réservée aux archipels

    float zs [3];
    int i = 0;
    for (MyMesh::FaceVertexIter curVert = _mesh->fv_iter(fh); curVert.is_valid(); curVert ++)
       {
           //qDebug() << "    vertID :" << (*curVert).idx();
            VertexHandle vh = *curVert;
            zs[i] = _mesh->point(vh)[2];
            i++;
            //if(_mesh->point(vh)[2] < -0.4f)
                //qDebug() << _mesh->point(vh)[2];
       }

    float somme = 0;
    for(int i = 0; i < 3; i++){
        somme += zs[i];
    }

    float d = somme/3.0f;


    if (d > 1.2f)  return MyMesh::Color(255, 255, 255);
    else if (d > 1.1f) return MyMesh::Color(200, 201, 176);
    else if (d > 0.9f) return MyMesh::Color(180, 181, 156);
    else if (d > 0.8f) return MyMesh::Color(135, 120, 110);
    else if (d > 0.6f) return MyMesh::Color(155, 60, 60);
    else if (d > 0.45f) return MyMesh::Color(0, 150, 0);
    else if (d > 0.3f) return MyMesh::Color(0, 175, 0);
    else if (d > 0.15f) return MyMesh::Color(0, 180, 0);
    else if (d > 0.10f) return MyMesh::Color(0, 200, 0);
    else if (d > 0.05f) return MyMesh::Color(247, 255 ,60);

    else if (d <= 0.5){

        //si au moins 1 des points de la faces
        //est audessus du niveau de la mer
        //alors la face est verte
        //sinon elle est bleu
        for(int i = 0; i < 3; i++){
            if (zs[i] > 0.0f) return MyMesh::Color(0, 200, 255);
        }

        return MyMesh::Color(0, 0, 250);
    }
}

MyMesh::Color calcColor_foret(MyMesh* _mesh, FaceHandle fh)
{
    //fonction basée sur calcColor mais dont l'utilité est strictement réservée aux archipels

    float zs [3];
    int i = 0;
    for (MyMesh::FaceVertexIter curVert = _mesh->fv_iter(fh); curVert.is_valid(); curVert ++)
       {
           //qDebug() << "    vertID :" << (*curVert).idx();
            VertexHandle vh = *curVert;
            zs[i] = _mesh->point(vh)[2];
            i++;
            //if(_mesh->point(vh)[2] < -0.4f)
                //qDebug() << _mesh->point(vh)[2];
       }

    float somme = 0;
    for(int i = 0; i < 3; i++){
        somme += zs[i];
    }

    float d = somme/3.0f;


    if (d > 1.0f)  return MyMesh::Color(100, 100, 100);
    else if (d > 0.75f) return MyMesh::Color(0, 150, 0);
    else if (d > 0.50f) return MyMesh::Color(0, 175, 0);
    else if (d > 0.25f) return MyMesh::Color(0, 180, 0);
    else if (d > 0.1f) return MyMesh::Color(0, 200 ,0);

    else if (d <= 0.1){

        //si au moins 1 des points de la faces
        //est audessus du niveau de la mer
        //alors la face est verte
        //sinon elle est bleue
        for(int i = 0; i < 3; i++){
            if (zs[i] > 0.0f) return MyMesh::Color(0, 200, 255);
        }

        return MyMesh::Color(0, 0, 250);
    }
}

MyMesh::Color calcColor_plaines(MyMesh* _mesh, FaceHandle fh)
{
    //fonction basée sur calcColor mais dont l'utilité est strictement réservée aux archipels

    float zs [3];
    int i = 0;
    for (MyMesh::FaceVertexIter curVert = _mesh->fv_iter(fh); curVert.is_valid(); curVert ++)
       {
           //qDebug() << "    vertID :" << (*curVert).idx();
            VertexHandle vh = *curVert;
            zs[i] = _mesh->point(vh)[2];
            i++;
            //if(_mesh->point(vh)[2] < -0.4f)
                //qDebug() << _mesh->point(vh)[2];
       }

    float somme = 0;
    for(int i = 0; i < 3; i++){
        somme += zs[i];
    }

    float d = somme/3.0f;


    if (d > 0.45f)  return MyMesh::Color(0, 130, 0);
    else if (d > 0.40f) return MyMesh::Color(0, 150 ,0);
    else if (d > 0.40f) return MyMesh::Color(0, 180 ,0);
    else if (d > 0.30f) return MyMesh::Color(255, 255 ,0);
    else if (d > 0.1f) return MyMesh::Color(255, 215 ,0);

    else if (d <= 0.1){

        //si au moins 1 des points de la faces
        //est audessus du niveau de la mer
        //alors la face est verte
        //sinon elle est bleue
        for(int i = 0; i < 3; i++){
            if (zs[i] > 0.0f) return MyMesh::Color(0, 200, 255);
        }

        return MyMesh::Color(0, 0, 250);
    }
}



void MainWindow::create_field()
{
    MyMesh mesha;

    if(method != "Par slider"){
        mise_a_jour_variables();
    }
    vector<vector<QVector3D>> terrain  = genereTerrain(10, 10, 15, octaves, persistence, lacunarity);

    int cols =terrain[0].size();
    int rows = terrain.size();

    //on va ajouter les points du terrain
    //dans un tableau de VertexHandle sommets
    vector<MyMesh::VertexHandle> sommets;
    vector<float> xs, ys, zs;
    float z_min = 0;
    float z_max = -5000;

    vector<MyMesh::VertexHandle> line;
    for(int i = 0, n = terrain[0].size(); i < n; i++){
        line.clear();
        for(int j = 0, m = terrain.size(); j < m; j++){
            float x = terrain[i][j][0];
            float y = terrain[i][j][1];
            float z = terrain[i][j][2];
            sommets.push_back(mesha.add_vertex(MyMesh::Point(x, y, z)));
            if(z < z_min){
                z_min = z;
            }
            if(z > z_max){
                z_max = z;
            }
        }
    }
    qDebug() << "z_min = " << z_min;
    qDebug() << "z_max = " << z_max;

    if(paysage != "Archipel"){
        for (MyMesh::VertexIter curVert = mesha.vertices_begin(); curVert != mesha.vertices_end(); curVert++){
            mesha.set_point((*curVert), MyMesh::Point(mesha.point(*curVert)[0], mesha.point(*curVert)[1], mesha.point(*curVert)[2] + abs(z_min)));
        }
    }
    else{
        for (MyMesh::VertexIter curVert = mesha.vertices_begin(); curVert != mesha.vertices_end(); curVert++){
            mesha.set_point((*curVert), MyMesh::Point(mesha.point(*curVert)[0], mesha.point(*curVert)[1], mesha.point(*curVert)[2]));
        }
    }

    //à partir du tableau de vertexHandle sommets
    //on  construit les faces
    vector<MyMesh::VertexHandle> uneNouvelleFace;
    for(int y = 0; y < rows-1; y++){
            for(int x = 0; x < cols-1; x++){

                int p0 = y * rows + x;
                int p1 = p0 + 1;
                int p2 = p0 + rows;
                int p3 = p2 + 1;

                uneNouvelleFace.clear();
                uneNouvelleFace.push_back(sommets[p0]);
                uneNouvelleFace.push_back(sommets[p1]);
                uneNouvelleFace.push_back(sommets[p2]);
                mesha.add_face(uneNouvelleFace);

                uneNouvelleFace.clear();
                uneNouvelleFace.push_back(sommets[p3]);
                uneNouvelleFace.push_back(sommets[p2]);
                uneNouvelleFace.push_back(sommets[p1]);
                mesha.add_face(uneNouvelleFace);

            }
    }

    /*if(paysage == "Archipel"){
        //on ajoute 2 faces au mesh pour faire l'eau
        float size = 5;

        MyMesh::VertexHandle eau1 = mesh.add_vertex(MyMesh::Point(-size, -size, 0));
        MyMesh::VertexHandle eau2 = mesh.add_vertex(MyMesh::Point(-size,  size, 0));
        MyMesh::VertexHandle eau3 = mesh.add_vertex(MyMesh::Point( size,  size, 0));
        MyMesh::VertexHandle eau4 = mesh.add_vertex(MyMesh::Point( size, -size, 0));

        uneNouvelleFace.clear();
        uneNouvelleFace.push_back(eau1);
        uneNouvelleFace.push_back(eau4);
        uneNouvelleFace.push_back(eau2);
        mesh.add_face(uneNouvelleFace);

        uneNouvelleFace.clear();
        uneNouvelleFace.push_back(eau4);
        uneNouvelleFace.push_back(eau3);
        uneNouvelleFace.push_back(eau2);
        mesh.add_face(uneNouvelleFace);
    }*/

    // on détermine la couleur de toutes les faces
    if(paysage == "Archipel"){
        for (MyMesh::FaceIter curFace = mesha.faces_begin(); curFace != mesha.faces_end(); curFace++)
        {
            FaceHandle fh = *curFace;
            mesha.set_color(fh,calcColor_archipel(&mesha, fh));
        }
        for (MyMesh::VertexIter curVert = mesha.vertices_begin(); curVert != mesha.vertices_end(); curVert++){
            if(mesha.point(*curVert)[2] < 0){
                mesha.set_point((*curVert), MyMesh::Point(mesha.point(*curVert)[0], mesha.point(*curVert)[1], 0));
            }
        }
    }
    else if(paysage == "Forêt"){
        for (MyMesh::FaceIter curFace = mesha.faces_begin(); curFace != mesha.faces_end(); curFace++)
        {
            FaceHandle fh = *curFace;
            mesha.set_color(fh,calcColor_foret(&mesha, fh));
        }
        for (MyMesh::VertexIter curVert = mesha.vertices_begin(); curVert != mesha.vertices_end(); curVert++){
            if(mesha.point(*curVert)[2] < 0){
                mesha.set_point((*curVert), MyMesh::Point(mesha.point(*curVert)[0], mesha.point(*curVert)[1], 0));
            }
        }
    }
    else if(paysage == "Plaines"){
        for (MyMesh::FaceIter curFace = mesha.faces_begin(); curFace != mesha.faces_end(); curFace++)
        {
            FaceHandle fh = *curFace;
            mesha.set_color(fh,calcColor_plaines(&mesha, fh));
        }
        for (MyMesh::VertexIter curVert = mesha.vertices_begin(); curVert != mesha.vertices_end(); curVert++){
            if(mesha.point(*curVert)[2] < 0){
                mesha.set_point((*curVert), MyMesh::Point(mesha.point(*curVert)[0], mesha.point(*curVert)[1], 0));
            }
        }
    }
    else{
        for (MyMesh::FaceIter curFace = mesha.faces_begin(); curFace != mesha.faces_end(); curFace++)
        {
            FaceHandle fh = *curFace;
            mesha.set_color(fh,calcColor(&mesha, fh));
        }
    }
    mesh = mesha;
    displayMesh(&mesh);
    method = "Par critère";
}

// permet d'initialiser les couleurs et les épaisseurs des élements du maillage
void MainWindow::resetAllColorsAndThickness(MyMesh* _mesh)
{
    for (MyMesh::VertexIter curVert = _mesh->vertices_begin(); curVert != _mesh->vertices_end(); curVert++)
    {
        _mesh->data(*curVert).thickness = 1;
        _mesh->set_color(*curVert, MyMesh::Color(0, 0, 0));
    }

    for (MyMesh::FaceIter curFace = _mesh->faces_begin(); curFace != _mesh->faces_end(); curFace++)
    {
        _mesh->set_color(*curFace, MyMesh::Color(150, 150, 150));
    }

    for (MyMesh::EdgeIter curEdge = _mesh->edges_begin(); curEdge != _mesh->edges_end(); curEdge++)
    {
        _mesh->data(*curEdge).thickness = 1;
        _mesh->set_color(*curEdge, MyMesh::Color(0, 0, 0));
    }
}

// charge un objet MyMesh dans l'environnement OpenGL
void MainWindow::displayMesh(MyMesh* _mesh, bool isTemperatureMap, float mapRange)
{
    GLuint* triIndiceArray = new GLuint[_mesh->n_faces() * 3];
    GLfloat* triCols = new GLfloat[_mesh->n_faces() * 3 * 3];
    GLfloat* triVerts = new GLfloat[_mesh->n_faces() * 3 * 3];

    int i = 0;

    if(isTemperatureMap)
    {
        QVector<float> values;

        if(mapRange == -1)
        {
            for (MyMesh::VertexIter curVert = _mesh->vertices_begin(); curVert != _mesh->vertices_end(); curVert++)
                values.append(fabs(_mesh->data(*curVert).value));
            qSort(values);
            mapRange = values.at(values.size()*0.8);
            qDebug() << "mapRange" << mapRange;
        }

        float range = mapRange;
        MyMesh::ConstFaceIter fIt(_mesh->faces_begin()), fEnd(_mesh->faces_end());
        MyMesh::ConstFaceVertexIter fvIt;

        for (; fIt!=fEnd; ++fIt)
        {
            fvIt = _mesh->cfv_iter(*fIt);
            if(_mesh->data(*fvIt).value > 0){triCols[3*i+0] = 255; triCols[3*i+1] = 255 - std::min((_mesh->data(*fvIt).value/range) * 255.0, 255.0); triCols[3*i+2] = 255 - std::min((_mesh->data(*fvIt).value/range) * 255.0, 255.0);}
            else{triCols[3*i+2] = 255; triCols[3*i+1] = 255 - std::min((-_mesh->data(*fvIt).value/range) * 255.0, 255.0); triCols[3*i+0] = 255 - std::min((-_mesh->data(*fvIt).value/range) * 255.0, 255.0);}
            triVerts[3*i+0] = _mesh->point(*fvIt)[0]; triVerts[3*i+1] = _mesh->point(*fvIt)[1]; triVerts[3*i+2] = _mesh->point(*fvIt)[2];
            triIndiceArray[i] = i;

            i++; ++fvIt;
            if(_mesh->data(*fvIt).value > 0){triCols[3*i+0] = 255; triCols[3*i+1] = 255 - std::min((_mesh->data(*fvIt).value/range) * 255.0, 255.0); triCols[3*i+2] = 255 - std::min((_mesh->data(*fvIt).value/range) * 255.0, 255.0);}
            else{triCols[3*i+2] = 255; triCols[3*i+1] = 255 - std::min((-_mesh->data(*fvIt).value/range) * 255.0, 255.0); triCols[3*i+0] = 255 - std::min((-_mesh->data(*fvIt).value/range) * 255.0, 255.0);}
            triVerts[3*i+0] = _mesh->point(*fvIt)[0]; triVerts[3*i+1] = _mesh->point(*fvIt)[1]; triVerts[3*i+2] = _mesh->point(*fvIt)[2];
            triIndiceArray[i] = i;

            i++; ++fvIt;
            if(_mesh->data(*fvIt).value > 0){triCols[3*i+0] = 255; triCols[3*i+1] = 255 - std::min((_mesh->data(*fvIt).value/range) * 255.0, 255.0); triCols[3*i+2] = 255 - std::min((_mesh->data(*fvIt).value/range) * 255.0, 255.0);}
            else{triCols[3*i+2] = 255; triCols[3*i+1] = 255 - std::min((-_mesh->data(*fvIt).value/range) * 255.0, 255.0); triCols[3*i+0] = 255 - std::min((-_mesh->data(*fvIt).value/range) * 255.0, 255.0);}
            triVerts[3*i+0] = _mesh->point(*fvIt)[0]; triVerts[3*i+1] = _mesh->point(*fvIt)[1]; triVerts[3*i+2] = _mesh->point(*fvIt)[2];
            triIndiceArray[i] = i;

            i++;
        }
    }
    else
    {
        MyMesh::ConstFaceIter fIt(_mesh->faces_begin()), fEnd(_mesh->faces_end());
        MyMesh::ConstFaceVertexIter fvIt;
        for (; fIt!=fEnd; ++fIt)
        {
            fvIt = _mesh->cfv_iter(*fIt);
            triCols[3*i+0] = _mesh->color(*fIt)[0]; triCols[3*i+1] = _mesh->color(*fIt)[1]; triCols[3*i+2] = _mesh->color(*fIt)[2];
            triVerts[3*i+0] = _mesh->point(*fvIt)[0]; triVerts[3*i+1] = _mesh->point(*fvIt)[1]; triVerts[3*i+2] = _mesh->point(*fvIt)[2];
            triIndiceArray[i] = i;

            i++; ++fvIt;
            triCols[3*i+0] = _mesh->color(*fIt)[0]; triCols[3*i+1] = _mesh->color(*fIt)[1]; triCols[3*i+2] = _mesh->color(*fIt)[2];
            triVerts[3*i+0] = _mesh->point(*fvIt)[0]; triVerts[3*i+1] = _mesh->point(*fvIt)[1]; triVerts[3*i+2] = _mesh->point(*fvIt)[2];
            triIndiceArray[i] = i;

            i++; ++fvIt;
            triCols[3*i+0] = _mesh->color(*fIt)[0]; triCols[3*i+1] = _mesh->color(*fIt)[1]; triCols[3*i+2] = _mesh->color(*fIt)[2];
            triVerts[3*i+0] = _mesh->point(*fvIt)[0]; triVerts[3*i+1] = _mesh->point(*fvIt)[1]; triVerts[3*i+2] = _mesh->point(*fvIt)[2];
            triIndiceArray[i] = i;

            i++;
        }
    }


    ui->displayWidget->loadMesh(triVerts, triCols, _mesh->n_faces() * 3 * 3, triIndiceArray, _mesh->n_faces() * 3);

    delete[] triIndiceArray;
    delete[] triCols;
    delete[] triVerts;

    GLuint* linesIndiceArray = new GLuint[_mesh->n_edges() * 2];
    GLfloat* linesCols = new GLfloat[_mesh->n_edges() * 2 * 3];
    GLfloat* linesVerts = new GLfloat[_mesh->n_edges() * 2 * 3];

    i = 0;
    QHash<float, QList<int> > edgesIDbyThickness;
    for (MyMesh::EdgeIter eit = _mesh->edges_begin(); eit != _mesh->edges_end(); ++eit)
    {
        float t = _mesh->data(*eit).thickness;
        if(t > 0)
        {
            if(!edgesIDbyThickness.contains(t))
                edgesIDbyThickness[t] = QList<int>();
            edgesIDbyThickness[t].append((*eit).idx());
        }
    }
    QHashIterator<float, QList<int> > it(edgesIDbyThickness);
    QList<QPair<float, int> > edgeSizes;
    while (it.hasNext())
    {
        it.next();

        for(int e = 0; e < it.value().size(); e++)
        {
            int eidx = it.value().at(e);

            MyMesh::VertexHandle vh1 = _mesh->to_vertex_handle(_mesh->halfedge_handle(_mesh->edge_handle(eidx), 0));
            linesVerts[3*i+0] = _mesh->point(vh1)[0];
            linesVerts[3*i+1] = _mesh->point(vh1)[1];
            linesVerts[3*i+2] = _mesh->point(vh1)[2];
            linesCols[3*i+0] = _mesh->color(_mesh->edge_handle(eidx))[0];
            linesCols[3*i+1] = _mesh->color(_mesh->edge_handle(eidx))[1];
            linesCols[3*i+2] = _mesh->color(_mesh->edge_handle(eidx))[2];
            linesIndiceArray[i] = i;
            i++;

            MyMesh::VertexHandle vh2 = _mesh->from_vertex_handle(_mesh->halfedge_handle(_mesh->edge_handle(eidx), 0));
            linesVerts[3*i+0] = _mesh->point(vh2)[0];
            linesVerts[3*i+1] = _mesh->point(vh2)[1];
            linesVerts[3*i+2] = _mesh->point(vh2)[2];
            linesCols[3*i+0] = _mesh->color(_mesh->edge_handle(eidx))[0];
            linesCols[3*i+1] = _mesh->color(_mesh->edge_handle(eidx))[1];
            linesCols[3*i+2] = _mesh->color(_mesh->edge_handle(eidx))[2];
            linesIndiceArray[i] = i;
            i++;
        }
        edgeSizes.append(qMakePair(it.key(), it.value().size()));
    }

    ui->displayWidget->loadLines(linesVerts, linesCols, i * 3, linesIndiceArray, i, edgeSizes);

    delete[] linesIndiceArray;
    delete[] linesCols;
    delete[] linesVerts;

    GLuint* pointsIndiceArray = new GLuint[_mesh->n_vertices()];
    GLfloat* pointsCols = new GLfloat[_mesh->n_vertices() * 3];
    GLfloat* pointsVerts = new GLfloat[_mesh->n_vertices() * 3];

    i = 0;
    QHash<float, QList<int> > vertsIDbyThickness;
    for (MyMesh::VertexIter vit = _mesh->vertices_begin(); vit != _mesh->vertices_end(); ++vit)
    {
        float t = _mesh->data(*vit).thickness;
        if(t > 0)
        {
            if(!vertsIDbyThickness.contains(t))
                vertsIDbyThickness[t] = QList<int>();
            vertsIDbyThickness[t].append((*vit).idx());
        }
    }
    QHashIterator<float, QList<int> > vitt(vertsIDbyThickness);
    QList<QPair<float, int> > vertsSizes;

    while (vitt.hasNext())
    {
        vitt.next();

        for(int v = 0; v < vitt.value().size(); v++)
        {
            int vidx = vitt.value().at(v);

            pointsVerts[3*i+0] = _mesh->point(_mesh->vertex_handle(vidx))[0];
            pointsVerts[3*i+1] = _mesh->point(_mesh->vertex_handle(vidx))[1];
            pointsVerts[3*i+2] = _mesh->point(_mesh->vertex_handle(vidx))[2];
            pointsCols[3*i+0] = _mesh->color(_mesh->vertex_handle(vidx))[0];
            pointsCols[3*i+1] = _mesh->color(_mesh->vertex_handle(vidx))[1];
            pointsCols[3*i+2] = _mesh->color(_mesh->vertex_handle(vidx))[2];
            pointsIndiceArray[i] = i;
            i++;
        }
        vertsSizes.append(qMakePair(vitt.key(), vitt.value().size()));
    }

    ui->displayWidget->loadPoints(pointsVerts, pointsCols, i * 3, pointsIndiceArray, i, vertsSizes);

    delete[] pointsIndiceArray;
    delete[] pointsCols;
    delete[] pointsVerts;
}

void MainWindow::mise_a_jour_variables(){
    if(ui->comboBox->currentText() == "Montagnes"){
        octaves = rand()%3+6;
        persistence = ((float)rand()/RAND_MAX)*0.3;
        lacunarity = ((float)rand()/RAND_MAX)*2.0+3.0;
        altitude = 2.0;
    }
    if(ui->comboBox->currentText() == "Plaines"){
        octaves = rand()%2+2;
        persistence = ((float)rand()/RAND_MAX)+1.0;
        lacunarity = ((float)rand()/RAND_MAX)*0.2+0.1;
        altitude = 2.0;
    }
    if(ui->comboBox->currentText() == "Archipel"){
        octaves = rand()%2+2;
        persistence = ((float)rand()/RAND_MAX)+1.0;
        lacunarity = ((float)rand()/RAND_MAX)*0.2+0.1;
        altitude = 2.0;
    }
    if(ui->comboBox->currentText() == "Forêt"){
        octaves = rand()%2+2;
        persistence = ((float)rand()/RAND_MAX)+2.0;
        lacunarity = ((float)rand()/RAND_MAX)*0.5+1.0;
        altitude = 2.0;
    }
    paysage = ui->comboBox->currentText();
    ui->valeur_octaves->setText(QString::number(octaves));
    ui->valeur_persistence->setText(QString::number(persistence));
    ui->valeur_lacunarity->setText(QString::number(lacunarity));


}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    srand(time(nullptr));
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//------------------------------------ I H M -------------------------------------------

void MainWindow::on_pushButton_generer_clicked()
{
    create_field();
}

void MainWindow::on_lacunaritySlider_sliderReleased()
{
    ui->valeur_lacunarity->setText(QString::number(ui->lacunaritySlider->value()/10.0));
    lacunarity = ui->lacunaritySlider->value()/10.0;
    method = "Par slider";
    create_field();
}

void MainWindow::on_octavesSlider_sliderReleased()
{
    ui->valeur_octaves->setText(QString::number(ui->octavesSlider->value()));
    octaves = ui->octavesSlider->value();
    method = "Par slider";
    create_field();
}

void MainWindow::on_persistenceSlider_sliderReleased()
{
    ui->valeur_persistence->setText(QString::number(ui->persistenceSlider->value()/10.0));
    persistence = ui->persistenceSlider->value()/10.0;
    method = "Par slider";
    create_field();
}

// exemple pour charger un fichier .obj
void MainWindow::on_pushButton_chargement_clicked()
{
    // fenêtre de sélection des fichiers
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Mesh"), "", tr("Mesh Files (*.obj)"));

    // chargement du fichier .obj dans la variable globale "mesh"
    OpenMesh::IO::read_mesh(mesh, fileName.toUtf8().constData());

    mesh.update_normals();

    // initialisation des couleurs et épaisseurs (sommets et arêtes) du mesh
    resetAllColorsAndThickness(&mesh);

    // on affiche le maillage
    displayMesh(&mesh);
}

void MainWindow::on_pushButton_aretes_clicked()
{
    if(aretes_activated == false){
        for (MyMesh::EdgeIter curEdge = mesh.edges_begin(); curEdge != mesh.edges_end(); curEdge++)
        {
            EdgeHandle eh = *curEdge;
            mesh.set_color(eh, MyMesh::Color(150, 150, 150));
            mesh.data(eh).thickness = 0.5;
        }
        aretes_activated = true;
    }
    else{
        for (MyMesh::EdgeIter curEdge = mesh.edges_begin(); curEdge != mesh.edges_end(); curEdge++)
        {
            EdgeHandle eh = *curEdge;
            mesh.set_color(eh, MyMesh::Color(150, 150, 150));
            mesh.data(eh).thickness = 0.0;
        }
        aretes_activated = false;
    }
    displayMesh(&mesh);
}
