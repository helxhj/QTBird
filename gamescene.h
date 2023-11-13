#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <QGraphicsScene>

class GameScene : public QGrahicsScene
{
    Q_OBJECT
public:
    // sceneRect场景的大小
    GameScene(QObject* parent,QRectF& sceneRect);
};

#endif // GAMESCENE_H
