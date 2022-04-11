#include "ovqt3dwindow.h"

OvQt3DWindow::OvQt3DWindow(QGuiApplication *app): Qt3DExtras::Qt3DWindow()
{
    this->app=app;
    number=0;
    Player_Controll=0;
    Player_Accelerate=0;
    Player_MouseX=0;
    Player_MouseY=0;
}
//-----------------------------------------------------------------
void OvQt3DWindow::keyPressEvent(QKeyEvent *event)
{

    std::cout<< ++number <<" PRESSED " << event->key() << std::endl;

    switch (event->key())
    {
        case Qt::Key_Escape:
            if ( windowState() == Qt::WindowFullScreen )
                setWindowState(Windowstate_Old);
            else
                app->quit();
        break;
        case Qt::Key_F:
            if ( windowState() != Qt::WindowFullScreen )
            {
                Windowstate_Old=windowState();
                setWindowState(Qt::WindowFullScreen);
            }
        break;
        case Qt::Key_C:Player_Controll=1;break;
        case Qt::Key_W:Player_Accelerate=1;break;
        case Qt::Key_S:Player_Accelerate=-1;break;
        case Qt::Key_Space:Player_Shoot=1;break;

    }
}
//-----------------------------------------------------------------
void OvQt3DWindow::keyReleaseEvent(QKeyEvent *event)
{
    std::cout<< ++number <<" RELEASED " << event->key() << std::endl;

    switch (event->key())
    {
        case Qt::Key_W:Player_Accelerate=0;break;
        case Qt::Key_S:Player_Accelerate=0;break;
        case Qt::Key_Space:Player_Shoot=0;break;
    }
}
//-----------------------------------------------------------------
void OvQt3DWindow::mouseMoveEvent(QMouseEvent* event)
{
    Player_MouseX=event->pos().x();
    Player_MouseY=event->pos().y();
}
//-----------------------------------------------------------------
