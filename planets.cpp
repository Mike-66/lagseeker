#include "planets.hpp"

TPlanets::TPlanets()
{

}

//----------------------------------

void TPlanets::Create(Qt3DCore::QEntity *rootEntity)
{
    // Sphere
    Planet[0].Entity = new Qt3DCore::QEntity(rootEntity);
    Planet[0].Mesh = new Qt3DExtras::QSphereMesh;
    Planet[0].Mesh->setRadius(3);
    Planet[0].Mesh->setGenerateTangents(true);
    Planet[0].Material=new Qt3DExtras::QDiffuseSpecularMaterial();
    Planet[0].Material->setAmbient(QColor(0xffffff));
    Planet[0].Position=QVector3D(0.0f, 0.0f, 0.0f);
    Planet[0].Speed=QVector3D(0.0f, 0.0f, 0.0f);
    Planet[0].Mass=100000;
    Planet[0].Transform=new Qt3DCore::QTransform();
    Planet[0].Transform->setScale(1.0f);
    Planet[0].Transform->setTranslation(Planet[0].Position);

    Planet[1].Entity = new Qt3DCore::QEntity(rootEntity);
    Planet[1].Mesh = new Qt3DExtras::QSphereMesh;
    Planet[1].Mesh->setRadius(1.2);
    Planet[1].Mesh->setGenerateTangents(true);
    Planet[1].Material=new Qt3DExtras::QDiffuseSpecularMaterial();
    Planet[1].Material->setAmbient(QColor(0x000044));
    Planet[1].Position=QVector3D(-100.0f, 0.0f, 0.0f);
    Planet[1].Speed=QVector3D(0.0f, 31.675f, 0.0f);
    Planet[1].Speed=QVector3D(0.0f, 0.0f, 0.0f);
    Planet[1].Mass=1;
    Planet[1].Transform=new Qt3DCore::QTransform();
    Planet[1].Transform->setScale(1.0f);
    Planet[1].Transform->setTranslation(Planet[1].Position);

    /**/
    Planet[2].Entity = new Qt3DCore::QEntity(rootEntity);
    Planet[2].Mesh = new Qt3DExtras::QSphereMesh;
    Planet[2].Mesh->setRadius(0.3);
    Planet[2].Mesh->setGenerateTangents(true);
    Planet[2].Material=new Qt3DExtras::QDiffuseSpecularMaterial();
    Planet[2].Material->setAmbient(QColor(0x00ffff));
    Planet[2].Position=QVector3D(-100.0f, 0.0f, 0.0f);
    Planet[2].Speed=QVector3D(0.0f, 31.675f, 0.0f);

    QMatrix4x4 rot;
    rot.setToIdentity();
    rot.rotate(60, QVector3D(0.0f,0.0f,1.0f));
    Planet[2].Position=Planet[2].Position*rot;
    Planet[2].Speed=Planet[2].Speed*rot;

    Planet[2].Mass=0.001;
    Planet[2].Transform=new Qt3DCore::QTransform();
    Planet[2].Transform->setScale(1.0f);
    Planet[2].Transform->setTranslation(Planet[2].Position);
    /**/

    Planet[3].Entity = new Qt3DCore::QEntity(rootEntity);
    Planet[3].Mesh = new Qt3DExtras::QSphereMesh;
    Planet[3].Mesh->setRadius(0.3);
    Planet[3].Mesh->setGenerateTangents(true);
    Planet[3].Material=new Qt3DExtras::QDiffuseSpecularMaterial();
    Planet[3].Material->setAmbient(QColor(0x444444));
    Planet[3].Position=QVector3D(-3.0f, 0.0f, 0.0f)+Planet[1].Position;
    Planet[3].Speed=QVector3D(0.f, 0.5f, 0.0f)+Planet[1].Speed;
    Planet[3].Mass=0.01;
    Planet[3].Transform=new Qt3DCore::QTransform();
    Planet[3].Transform->setScale(1.0f);
    Planet[3].Transform->setTranslation(Planet[1].Position);

    for(int i=0;i<MAXPLANETS;i++)
    {
        //Planet[i].Material->setDiffuse(Planet[i].Material->ambient());
        Planet[i].Material->setShininess(10);
        Planet[i].Entity->addComponent(Planet[i].Mesh);
        Planet[i].Entity->addComponent(Planet[i].Material);
        Planet[i].Entity->addComponent(Planet[i].Transform);
    }
}

//------------------------------------------------------

void TPlanets::Move(float dt)
{
    float G=1.0f;
    QVector3D Force;

    //Calculate force on planet according to gravity and resulting acceleration
    for(int i=0;i<MAXPLANETS;i++)
    if (i!=0 && i!=2)
    {
        Force=QVector3D(0,0,0);
        for(int j=0;j<MAXPLANETS;j++)
        if (j!=i)
        if (j!=0 && j!=2)
        {
            QVector3D V_distance=Planet[j].Position-Planet[i].Position;
            float distance=V_distance.length();
            float distance_2=V_distance.lengthSquared();
            //Force+=G*Planet[i].Mass*Planet[j].Mass/distance_2*V_distance/qFabs(distance);
            //reduced Planet[i].Mass
            Force+=G*Planet[j].Mass/distance_2*V_distance/qFabs(distance);
        }
        //Planet[i].Acc=Force/Planet[i].Mass;
        //reduced Planet[i].Mass
        Planet[i].Acc=Force;
    }

    //Calculate and update positions
    for(int i=0;i<MAXPLANETS;i++)
    {
        Planet[i].Speed+=Planet[i].Acc*dt;
        Planet[i].Position+=Planet[i].Speed*dt;
        Planet[i].Transform->setTranslation(Planet[i].Position);
    }
}



