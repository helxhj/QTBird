#ifndef ROADITEM_H
#define ROADITEM_H

#include <QGraphicsObject>
#include <QGraphicsScene>
// 道路图形项
class RoadItem : public QGraphicsObject
{
    Q_OBJECT
public:
    RoadItem(QGraphicsScene* scene);
    ~RoadItem();
public:
    // 重写图形项的绘图区域
    QRectF boundingRect()const;

private:
    // 重写图形项的绘图
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // 马路移动
    void startMove();
private:
    QGraphicsScene* m_scene;
};

#endif // ROADITEM_H
