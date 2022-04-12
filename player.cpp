#include "player.hpp"

TPlayer::TPlayer()
{

}
//-------------------------------------------------
void TPlayer::Create(Qt3DRender::QCamera *camera)
{
    Player.Entity = camera;
    Player.Position=(QVector3D(0.0f, 0.0f, 500.0f));
    Player.Speed=0;
    Player.Acc=0;
    Player.ViewDir=(QVector3D(0.0f, 0.0f, 0.0f))-Player.Position;
    Player.ViewDir/=Player.ViewDir.length();
    Player.ViewCenter=Player.Position+100*Player.ViewDir;
    Player.UpDir=QVector3D(0, 1.0f, 0.0f);
    Player.Mass=0.001;
    Player.Entity->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
    Player.Entity->setPosition(Player.Position);
    Player.Entity->setUpVector(Player.UpDir);
    Player.Entity->setViewCenter(Player.ViewCenter);

    Gun_Muzzle_Idx=0;
    Gun_Muzzle[0]=QVector3D(1.f,1.f,0);
    QMatrix4x4 rot;
    rot.setToIdentity();
    float rotangle=360.f/GUN_MUZZLES;
    for(int i=1;i<GUN_MUZZLES;i++)
    {
        rot.rotate(rotangle, QVector3D(0.f,0.f,1.f));
        Gun_Muzzle[i]=Gun_Muzzle[0]*rot;
    }
}
//-------------------------------------------------
float TPlayer::GetDue(int range, int position)
{
    int x_zero=range/2;
    return(float ( position-x_zero ) / float(x_zero));
}
//-------------------------------------------------
void TPlayer::Shoot(void)
{

}
//-------------------------------------------------
void TPlayer::Move(int controll,float x_due, float y_due, int accellerate, float dt)
{

    float rotangle;
    /*
    if (controll==1)
    {
        QMatrix4x4 rot;
        QVector3D V_normal=QVector3D::normal(Player.ViewDir,Player.UpDir);
        rotangle=90.*x_due*dt;
        rot.setToIdentity();
        rot.rotate(rotangle, Player.UpDir);
        Player.ViewDir=Player.ViewDir*rot;
        for(int i=0;i<GUN_MUZZLES;i++)
        Gun_Muzzle[i]=Gun_Muzzle[i]*rot;
        rotangle=90.*y_due*dt;
        rot.setToIdentity();
        rot.rotate(rotangle, V_normal);
        Player.UpDir=Player.UpDir*rot;
        Player.ViewDir=Player.ViewDir*rot;
        for(int i=0;i<GUN_MUZZLES;i++)
        Gun_Muzzle[i]=Gun_Muzzle[i]*rot;

    }
    */

    if (controll==1)
    {
        QMatrix4x4 rot;
        QVector3D V_normal=QVector3D::normal(Player.ViewDir,Player.UpDir);
        rotangle=-90.*x_due*dt;
        rot.setToIdentity();
        rot.rotate(rotangle, Player.ViewDir);
        Player.UpDir=Player.UpDir*rot;
        for(int i=0;i<GUN_MUZZLES;i++)
        Gun_Muzzle[i]=Gun_Muzzle[i]*rot;
        rotangle=90.*y_due*dt;
        rot.setToIdentity();
        rot.rotate(rotangle, V_normal);
        Player.UpDir=Player.UpDir*rot;
        Player.ViewDir=Player.ViewDir*rot;
        for(int i=0;i<GUN_MUZZLES;i++)
        Gun_Muzzle[i]=Gun_Muzzle[i]*rot;

    }

    float sForce=accellerate/30.f;
    Player.Acc=sForce/Player.Mass;
    Player.Speed+=Player.Acc*dt;
    Player.ViewDir/=Player.ViewDir.length();
    Player.Position+=Player.ViewDir*Player.Speed*dt;
    Player.ViewCenter=Player.Position+100*Player.ViewDir;
    Player.Entity->setPosition(Player.Position);
    Player.Entity->setUpVector(Player.UpDir);
    Player.Entity->setViewCenter(Player.ViewCenter);
}
//-------------------------------------------------
