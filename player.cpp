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
}
//-------------------------------------------------
float TPlayer::GetDue(int range, int position)
{
    int x_zero=range/2;
    return(float ( position-x_zero ) / float(x_zero));
}
//-------------------------------------------------
void TPlayer::Move(int controll,float x_due, float y_due, int accellerate, float dt)
{
    if (controll==1)
    {
        QMatrix4x4 rot;
        QVector3D V_normal=QVector3D::normal(Player.ViewDir,Player.UpDir);
        rot.setToIdentity();
        rot.rotate(90.*x_due*dt, Player.UpDir);
        Player.ViewDir=Player.ViewDir*rot;
        rot.setToIdentity();
        rot.rotate(90.*y_due*dt, V_normal);
        Player.UpDir=Player.UpDir*rot;
        Player.ViewDir=Player.ViewDir*rot;
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
