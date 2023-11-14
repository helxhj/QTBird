#include "roaditem.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QDebug>
// 马路的高度
 // const int ROAD_ITEM_HEIGHT = 64;
#define ROAD_ITEM_HEIGHT 64
RoadItem::RoadItem(QGraphicsScene* scene)
    : m_scene(scene)
{
    // 将当前道路图形项对象添加到游戏场景中去
    scene->addItem(this);
    // 让其开始移动
    startMove();
}

RoadItem::~RoadItem()
{

}

// 重写矩形绘图区域
QRectF RoadItem::boundingRect() const
{
    // 584*448
    // 384*64
    return QRectF(0,m_scene->height() - ROAD_ITEM_HEIGHT,
                 2*m_scene->width(),ROAD_ITEM_HEIGHT);
}

// 重写绘图事件
void RoadItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // 画前后两段马路
    painter->drawImage(QRectF(0,m_scene->height() - ROAD_ITEM_HEIGHT,
                              m_scene->width(),ROAD_ITEM_HEIGHT),
                       QImage(":/BirdGame/Resources/image/road.png"));
    painter->drawImage(QRectF(m_scene->width(),m_scene->height() - ROAD_ITEM_HEIGHT,
                              m_scene->width(),ROAD_ITEM_HEIGHT),
                      QImage(":/BirdGame/Resources/image/road.png"));

}

void RoadItem::startMove()
{
    QPropertyAnimation* moveAnimation = new QPropertyAnimation(this,"pos");
    // -1 为无限循环  0不启动
    moveAnimation->setLoopCount(-1); // 设置循环计数
    moveAnimation->setDuration(6000); // 动画时长为6s
    // 动画启动值（位置初始值）
    moveAnimation->setStartValue(QPoint(0,pos().y()));
    moveAnimation->setEndValue(QPoint(0-m_scene->width(),pos().y()));
    moveAnimation->setEasingCurve(QEasingCurve::Linear);
    moveAnimation->start();
}
