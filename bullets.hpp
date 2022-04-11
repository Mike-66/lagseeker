#ifndef TBULLETS_HPP
#define TBULLETS_HPP

#include "config.hpp"

//------------------------------------------
struct s_Bullet {
    Qt3DCore::QEntity *Entity;
    Qt3DExtras::QCylinderMesh *Mesh;
    Qt3DExtras::QDiffuseSpecularMaterial *Material;
    Qt3DCore::QTransform *Transform;
    QVector3D Position;
    QVector3D Speed;
    float     Age;
};
//------------------------------------------

class TBullets
{
public:
    TBullets();

    unsigned CountBullets;
    double   LastShootTimePassed;
    int      NextBullet;
    s_Bullet Bullet[MAXBULLETS] ;
    void Create(Qt3DCore::QEntity *rootEntity);
    void Move(float dt);
    void Shoot(QVector3D position,QVector3D direction,float speed);
    void Delete(int idx);

};

#endif // TBULLETS_HPP
