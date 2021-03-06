#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "config.hpp"

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
class TPlayer
{
public:
    TPlayer();
    s_Player Player;

    QVector3D Gun_Muzzle[GUN_MUZZLES];
    int       Gun_Muzzle_Idx;

    void Create(Qt3DRender::QCamera *camera);
    float GetDue(int range, int position);
    void Shoot(void);
    void Move(int controll,float x_due, float y_due, int accellerate, float dt);

};
//------------------------------------------
#endif // PLAYER_HPP
