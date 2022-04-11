#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "config.hpp"
#include "ovqt3dwindow.h"

#include "planets.hpp"
#include "player.hpp"
#include "bullets.hpp"

//------------------------------------------
class universe: public QObject
{
public:
    universe();

    Qt3DRender::QMaterial *material;
    Qt3DCore::QTransform *lightTransform;
    Qt3DExtras::QExtrudedTextMesh *textMesh;

    OvQt3DWindow *view;
    Qt3DCore::QEntity *rootEntity;

    TPlanets Planets;
    TPlayer Player;
    TBullets Bullets;

    double TotalTimePassed;

    void create(OvQt3DWindow *view,Qt3DCore::QEntity *rootEntity);

public slots:
    void render(float dt);
};

#endif // UNIVERSE_H
