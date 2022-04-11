#include "bullets.hpp"

TBullets::TBullets()
{
    CountBullets=0;
    NextBullet=0;
    LastShootTimePassed=0;
}
//-------------------------------------------------------
void TBullets::Create(Qt3DCore::QEntity *rootEntity)
{
    for (int idx=0;idx<MAXBULLETS;idx++)
    {
        QVector3D position=QVector3D(0.0f, 0.0f, 0.0f);
        Bullet[idx].Entity = new Qt3DCore::QEntity(rootEntity);
        Bullet[idx].Mesh = new Qt3DExtras::QCylinderMesh();
        //Bullet[idx].Mesh = new Qt3DExtras::QCylinderMesh();
        Bullet[idx].Mesh->setRadius(0.1);
        Bullet[idx].Mesh->setLength(0.3);
        //Bullet[idx].Mesh->setRings(5);
        //Bullet[idx].Mesh->setSlices(5);
        Bullet[idx].Material=new Qt3DExtras::QDiffuseSpecularMaterial();
        Bullet[idx].Material->setAmbient(QColor(0xffffff));
        Bullet[idx].Position=position;
        Bullet[idx].Speed=QVector3D(0.0f, 0.0f, 0.0f);
        Bullet[idx].Transform=new Qt3DCore::QTransform();
        Bullet[idx].Transform->setScale(1.0f);
        Bullet[idx].Transform->setTranslation(Bullet[idx].Position);
        Bullet[idx].Entity->addComponent(Bullet[idx].Mesh);
        Bullet[idx].Entity->addComponent(Bullet[idx].Material);
        Bullet[idx].Entity->addComponent(Bullet[idx].Transform);
        Bullet[idx].Age=BULLET_AGE_FREE;
    }
}
//-------------------------------------------------------
void TBullets::Move(float dt)
{
    for(int i=0;i<MAXBULLETS;i++)
    if( Bullet[i].Age>BULLET_AGE_SEPARATOR)
    {
        Bullet[i].Age+=dt;
        Bullet[i].Position+=Bullet[i].Speed*dt;
        Bullet[i].Transform->setTranslation(Bullet[i].Position);
        if(  Bullet[i].Age > BULLET_LIFETIME)
        Delete(i);
    }
    LastShootTimePassed+=dt;
}
//-------------------------------------------------------
void TBullets::Shoot(QVector3D position,QVector3D direction,float speed)
{
    if (LastShootTimePassed <  BULLET_INTERVALL)
    return;
    LastShootTimePassed=0;
    if (Bullet[NextBullet].Age >= BULLET_AGE_SEPARATOR )
    return;
    Bullet[NextBullet].Entity->addComponent(Bullet[NextBullet].Mesh);
    Bullet[NextBullet].Entity->addComponent(Bullet[NextBullet].Material);
    Bullet[NextBullet].Entity->addComponent(Bullet[NextBullet].Transform);
    Bullet[NextBullet].Position=position;
    Bullet[NextBullet].Speed=direction*(speed+BULLET_SPEED);
    Bullet[NextBullet].Age=BULLET_AGE_RUNNING;
    NextBullet++;
    if(NextBullet>=MAXBULLETS)
    NextBullet=0;
}
//-------------------------------------------------------
void TBullets::Delete(int idx)
{
    //Bullet[idx].Entity = new Qt3DCore::QEntity(rootEntity);
    //Bullet[idx].Mesh = new Qt3DExtras::QSphereMesh();
    //Bullet[idx].Material=new Qt3DExtras::QDiffuseSpecularMaterial();
    //Bullet[idx].Transform=new Qt3DCore::QTransform();
    Bullet[idx].Age=BULLET_AGE_FREE;
    Bullet[idx].Entity->removeComponent(Bullet[idx].Transform);
    Bullet[idx].Entity->removeComponent(Bullet[idx].Material);
    Bullet[idx].Entity->removeComponent(Bullet[idx].Mesh);
}
//-------------------------------------------------------
