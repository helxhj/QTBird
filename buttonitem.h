#ifndef BUTTONITEM_H
#define BUTTONITEM_H
// 自定义图形项时，需要重写paint，boundingRect
#include <QGraphicsObject>
#include <QGraphicsScene>
class ButtonItem : public QGraphicsObject
{
    Q_OBJECT
public:
    ButtonItem(const QPixmap& pix,QGraphicsScene* scene);
    ~ButtonItem();

public:
    // 矩形区域
    QRectF boundingRect() const;

private:
    // 鼠标按下事件
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    void paint(QPainter* ,const QStyleOptionGraphicsItem*,QWidget*);

signals:
    void clicked(); // 点击信号

private:
    QPixmap m_pix;
};

#endif // BUTTONITEM_H
