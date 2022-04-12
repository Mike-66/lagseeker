#ifndef CONFIG_HPP
#define CONFIG_HPP

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

#define MAXPLANETS            4
#define MAXBULLETS          500
#define BULLET_INTERVALL      0.2
#define BULLET_AGE_FREE      -1.0f
#define BULLET_AGE_SEPARATOR -0.1f
#define BULLET_AGE_RUNNING    0.0f
#define BULLET_LIFETIME      10
#define BULLET_SPEED        100
#define GUN_MUZZLES           4

#endif // CONFIG_HPP
