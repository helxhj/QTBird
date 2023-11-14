#include "pipeitem.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QDebug>

#define PIPE_WIDTH 60  // 管道宽度

PipeItem::PipeItem(QGraphicsScene* scene)
    :m_scene(scene)
{
    // 游戏场景中添加管道
    scene->addItem(this);
    createPipeHeight();
    startMove();
}

PipeItem::~PipeItem()
{

}

QRectF PipeItem::boundingRect() const
{
    return QRectF(m_scene->width(),0,PIPE_WIDTH,m_scene->height());
}

// 重写绘图事件
void PipeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawImage(QRectF(m_scene->width(),0,
                             PIPE_WIDTH,m_upPipeHeight),
                      QImage(":/BirdGame/Resources/image/tubeup.png"));

    painter->drawImage(QRectF(m_scene->width(),m_scene->height()- 60 - m_downPipeHeight,
                             PIPE_WIDTH,m_downPipeHeight),
                      QImage(":/BirdGame/Resources/image/tubedown.png"));
}

void PipeItem::startMove()
{
    // 移动的动画
    QPropertyAnimation* moveAnimation = new QPropertyAnimation(this,"pos");
    moveAnimation->setLoopCount(-1); // 一直循环
    moveAnimation->setDuration(3000); // 动画时长 3s
    moveAnimation->setStartValue(QPoint(0,pos().y()));
    moveAnimation->setEndValue(QPoint(0-m_scene->width()-PIPE_WIDTH,pos().y()));
    moveAnimation->start();
}

// 创建管道高度
void PipeItem::createPipeHeight()
{
    // 改进，上下管道都为随机
    // 上管道高度
    m_upPipeHeight = qrand() % 100 + 80;
    m_downPipeHeight = m_scene->height() - m_upPipeHeight - 178;
}
