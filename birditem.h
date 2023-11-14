#ifndef BIRDITEM_H
#define BIRDITEM_H

#include <QGraphicsObject>
#include <QPropertyAnimation>
#include <QGraphicsScene>
// QGraphicsObject图形项对象
// 游戏中的鸟儿对象（图形项），自定义图形项时，需要重写paint，boundingRect
//
class BirdItem : public QGraphicsObject
{
    Q_OBJECT
public:
    BirdItem(QGraphicsScene* scene);
    ~BirdItem();
public:
    // 返回你的图形所在的矩形，比如鸟儿所在的矩形
    QRectF boundingRect()const;// 重写绘图区域

    void flyRaiseAnimation();   // 上升动画
    void flyLandfallAnimation();    // 下降动画
    bool checkIsCollided(); // 碰撞检测
private:
    // 重写绘图事件
    void paint(QPainter* ,const QStyleOptionGraphicsItem*,QWidget*);
    // 重写键盘事件，空格控制小鸟
    void keyPressEvent(QKeyEvent* event);

private slots:
    void onRefreshBird();       // 定时刷新小鸟
    void onFlyRaiseAnimationFinished(); // 上升动画结束

private:
    bool m_IsLandFall;  // 下降标志
    bool m_isRaise;     // 上升标志
    int m_curFlyStatus; // 当前飞行状态
    QGraphicsScene* m_scene;    // 所在场景
    QTimer* m_birdReFreshTimer; // 刷新小鸟的计时器
    QPropertyAnimation* m_flyAnimation; // 飞行动画
};

#endif // BIRDITEM_H
