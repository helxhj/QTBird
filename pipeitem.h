#ifndef PIPEITEM_H
#define PIPEITEM_H

#include <QGraphicsObject>
#include <QGraphicsScene>
class PipeItem : public QGraphicsObject
{
    Q_OBJECT
public:
    PipeItem(QGraphicsScene* scene);
    ~PipeItem();

protected:
    // 重写绘图区域
    QRectF boundingRect()const;
    // 重写绘图事件
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    // 管道开始移动
    void startMove();
    // 创建管道的高度
    void createPipeHeight();

private:
    QGraphicsScene* m_scene;
    int m_upPipeHeight; // 上管道高度
    int m_downPipeHeight; // 下管道高度
};

#endif // PIPEITEM_H
