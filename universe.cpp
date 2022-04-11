#include "universe.h"

universe::universe()
{
    TotalTimePassed=0;
}
//-----------------------------------------------------
void universe::create(OvQt3DWindow *view,Qt3DCore::QEntity *rootEntity)
{
    this->view=view;
    this->rootEntity=rootEntity;
    // BackGround
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x00000)));

    Planets.Create(rootEntity);
    Player.Create(view->camera());
    Bullets.Create(rootEntity);

    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    lightEntity->addComponent(light);
    lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(Planets.Planet[0].Position);
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
void universe::render(float dt)
{
    TotalTimePassed+=dt;

    //float G=6.673e-11;
    Planets.Move(dt);
    Player.Move(view->Player_Controll,
                Player.GetDue(view->width(),view->Player_MouseX),Player.GetDue(view->height(),view->Player_MouseY),
                view->Player_Accelerate, dt);
    if(view->Player_Shoot==1)
    Bullets.Shoot(Player.Player.Position,Player.Player.ViewDir,Player.Player.Speed);
    Bullets.Move(dt);

    // set light according to "sun"
    lightTransform->setTranslation(Planets.Planet[0].Position);

    QVector3D V_distance=Planets.Planet[1].Position-Planets.Planet[2].Position;
    textMesh->setText(QString::number(V_distance.length()));
    //textMesh->setText(QString::number(view->Player_Accelerate ));
    //textMesh->setText(QString::number(y_due));
    //qDebug() << "ViewDir" << Player.ViewDir;
    //qDebug() << "UpDir" << Player.UpDir;

    //std::cout << "rendered";
}

