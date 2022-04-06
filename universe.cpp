#include "universe.h"

universe::universe()
{
    TotalTimePassed=0;
    CountBullets=0;
    NextBullet=0;
}
//-----------------------------------------------------
void universe::create(OvQt3DWindow *view,Qt3DCore::QEntity *rootEntity)
{
    this->view=view;
    this->rootEntity=rootEntity;
    // BackGround
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x00000)));

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

    // Camera
    Player.Entity = view->camera();
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

    for(int i=0;i<MAXBULLETS;i++)
    {
        Bullet_Create(Player.Position,rootEntity,i);
    }

    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    lightEntity->addComponent(light);
    lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(Planet[0].Position);
    lightEntity->addComponent(lightTransform);

    Qt3DCore::QEntity *text = new Qt3DCore::QEntity(rootEntity);
    Qt3DExtras::QPhongMaterial *textMaterial = new Qt3DExtras::QPhongMaterial();
    textMesh = new Qt3DExtras::QExtrudedTextMesh();

    Qt3DCore::QTransform *textTransform = new Qt3DCore::QTransform();
    QFont font("Chandas", 32, -1, false);
    textTransform->setTranslation(QVector3D(-250,180,0));
    textTransform->setScale(10.0f);
    textMesh->setDepth(.45f);
    textMesh->setFont(font);
    textMesh->setText("yo men digit");
    textMaterial->setAmbient(QColor(0xffffff));
    textMaterial->setDiffuse(QColor(0xffffff));
    text->addComponent(textMaterial);
    text->addComponent(textMesh);
    text->addComponent(textTransform);
}
//-----------------------------------------------------
void universe::Bullet_Create(QVector3D position, Qt3DCore::QEntity *rootEntity, int idx)
{
    Bullet[idx].Entity = new Qt3DCore::QEntity(rootEntity);
    Bullet[idx].Mesh = new Qt3DExtras::QCylinderMesh();
    //Bullet[idx].Mesh = new Qt3DExtras::QCylinderMesh();
    Bullet[idx].Mesh->setRadius(0.3);
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
    Bullet[idx].ShootTime=-1;
}
//-----------------------------------------------------
void universe::Bullet_Delete(int idx)
{
    //Bullet[idx].Entity = new Qt3DCore::QEntity(rootEntity);
    //Bullet[idx].Mesh = new Qt3DExtras::QSphereMesh();
    //Bullet[idx].Material=new Qt3DExtras::QDiffuseSpecularMaterial();
    //Bullet[idx].Transform=new Qt3DCore::QTransform();
    Bullet[idx].ShootTime=-1;
    Bullet[idx].Entity->removeComponent(Bullet[idx].Transform);
    Bullet[idx].Entity->removeComponent(Bullet[idx].Material);
    Bullet[idx].Entity->removeComponent(Bullet[idx].Mesh);
}
//-----------------------------------------------------
void universe::Bullet_Launch(double TimePassed)
{
    if (TimePassed > BULLET_INTERVALL)
    if ( Bullet[NextBullet].ShootTime < 0 )
    {
        Bullet[NextBullet].Entity->addComponent(Bullet[NextBullet].Mesh);
        Bullet[NextBullet].Entity->addComponent(Bullet[NextBullet].Material);
        Bullet[NextBullet].Entity->addComponent(Bullet[NextBullet].Transform);
        Bullet[NextBullet].Position=Player.Position;
        Bullet[NextBullet].Speed=Player.ViewDir*(Player.Speed+BULLET_SPEED);
        Bullet[NextBullet].ShootTime=TotalTimePassed;
        LastShootTime=TotalTimePassed;
        NextBullet++;
        if(NextBullet>=MAXBULLETS)
        NextBullet=0;

    }

}
//-----------------------------------------------------
void universe::render(float dt)
{
    TotalTimePassed+=dt;

    //float G=6.673e-11;
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

    //Calculate and update positions
    for(int i=0;i<MAXBULLETS;i++)
    if( Bullet[i].ShootTime>0)
    {
        Bullet[i].Position+=Bullet[i].Speed*dt;
        Bullet[i].Transform->setTranslation(Bullet[i].Position);
        if(  (TotalTimePassed-Bullet[i].ShootTime) > BULLET_LIFETIME)
        Bullet_Delete(i);
    }

    if(view->Player_Shoot==1)
    {
        Bullet_Launch(TotalTimePassed-LastShootTime);
        view->Player_Shoot=0;
    }

    // set light according to "sun"
    lightTransform->setTranslation(Planet[0].Position);

    //update Players movement, up and look angle
    int x_view_range=view->width();
    int y_view_range=view->height();
    int x_zero=x_view_range/2;
    int y_zero=y_view_range/2;
    float x_due= ( view->Player_MouseX-x_zero ) / float(x_zero);
    float y_due= ( view->Player_MouseY-y_zero ) / float(y_zero);

    if (view->Player_Controll==1)
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

    float sForce=view->Player_Accelerate/30.f;
    Player.Acc=sForce/Player.Mass;
    Player.Speed+=Player.Acc*dt;
    Player.ViewDir/=Player.ViewDir.length();
    Player.Position+=Player.ViewDir*Player.Speed*dt;
    Player.ViewCenter=Player.Position+100*Player.ViewDir;
    Player.Entity->setPosition(Player.Position);
    Player.Entity->setUpVector(Player.UpDir);
    Player.Entity->setViewCenter(Player.ViewCenter);

    QVector3D V_distance=Planet[1].Position-Planet[2].Position;
    textMesh->setText(QString::number(V_distance.length()));
    //textMesh->setText(QString::number(view->Player_Accelerate ));
    //textMesh->setText(QString::number(y_due));
    //qDebug() << "ViewDir" << Player.ViewDir;
    //qDebug() << "UpDir" << Player.UpDir;

    //std::cout << "rendered";
}

