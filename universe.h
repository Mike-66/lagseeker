#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <QObject>

#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QCameraLens>
#include <Qt3DRender/QPointLight>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QAspectEngine>
#include <Qt3DLogic/qframeaction.h>

#include <Qt3DInput/QInputAspect>

#include <Qt3DRender/QRenderAspect>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QDiffuseSpecularMaterial>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QTorusMesh>

#include <Qt3DExtras/QExtrudedTextMesh>
#include <QtMath>

#include "ovqt3dwindow.h"


#define MAXPLANETS         4
#define MAXBULLETS       150
#define BULLET_INTERVALL 0.1
#define BULLET_LIFETIME   10
#define BULLET_SPEED     250

//------------------------------------------
struct s_Sphere {
    Qt3DCore::QEntity *Entity;
    Qt3DExtras::QSphereMesh *Mesh;
    Qt3DExtras::QDiffuseSpecularMaterial *Material;
    Qt3DCore::QTransform *Transform;
    QVector3D Position;
    QVector3D Speed;
    QVector3D Acc;
    float     Mass;

};
//------------------------------------------
struct s_Player {
    Qt3DRender::QCamera *Entity;
    QVector3D Position;
    float Speed;
    float Acc;
    QVector3D ViewDir;
    QVector3D UpDir;
    QVector3D ViewCenter;
    float     Mass;
};
//------------------------------------------
struct s_Bullet {
    Qt3DCore::QEntity *Entity;
    Qt3DExtras::QCylinderMesh *Mesh;
    Qt3DExtras::QDiffuseSpecularMaterial *Material;
    Qt3DCore::QTransform *Transform;
    QVector3D Position;
    QVector3D Speed;
    double    ShootTime;
};
//------------------------------------------
class universe: public QObject
{
public:
    universe();

    // Material
    Qt3DRender::QMaterial *material;
    // Sphere
    s_Sphere Planet[MAXPLANETS];
    s_Player Player;
    Qt3DCore::QTransform *lightTransform;
    Qt3DExtras::QExtrudedTextMesh *textMesh;

    OvQt3DWindow *view;
    Qt3DCore::QEntity *rootEntity;

    double TotalTimePassed;

    unsigned CountBullets;
    double   LastShootTime;
    int      NextBullet;
    s_Bullet Bullet[MAXBULLETS] ;
    void Bullet_Create(QVector3D position, Qt3DCore::QEntity *rootEntity, int idx);
    void Bullet_Launch(double TotalTimePassed);
    void Bullet_Delete(int idx);

    void create(OvQt3DWindow *view,Qt3DCore::QEntity *rootEntity);

public slots:
    void render(float dt);
};

#endif // UNIVERSE_H
