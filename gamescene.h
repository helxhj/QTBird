#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <QGraphicsScene>
#include <QRectF>
// 游戏场景
class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    // sceneRect场景的大小
    GameScene(QObject* parent,const QRectF& sceneRect);
};

#endif // GAMESCENE_H
