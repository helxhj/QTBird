#include "buttonitem.h"

#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
ButtonItem::ButtonItem(const QPixmap& pix,QGraphicsScene* scene)
    :m_pix(pix)
{
    scene->addItem(this);
    // 鼠标变成手的形状
    setCursor(QCursor(Qt::PointingHandCursor)); // 设置光标
}
// 重写按钮图形项绘图区域
ButtonItem::~ButtonItem()
{

}

QRectF ButtonItem::boundingRect()const
{
    return QRectF(QPointF(0,0),m_pix.size());
}

void ButtonItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        emit clicked();
    }
}

void ButtonItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0,0,m_pix);
}
