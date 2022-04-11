#ifndef PLANETS_HPP
#define PLANETS_HPP

#include "config.hpp"

//------------------------------------------
struct s_Planet {
    Qt3DCore::QEntity *Entity;
    Qt3DExtras::QSphereMesh *Mesh;
    Qt3DExtras::QDiffuseSpecularMaterial *Material;
    Qt3DCore::QTransform *Transform;
    QVector3D Position;
    QVector3D Speed;
    QVector3D Acc;
    float     Mass;
};

class TPlanets
{
//    Q_OBJECT
private:
protected:
public:
    s_Planet Planet[MAXPLANETS];
    TPlanets();

    void Create(Qt3DCore::QEntity *rootEntity);
    void Move(float dt);
};

#endif // PLANETS_HPP
