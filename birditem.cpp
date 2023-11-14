#include "birditem.h"
#include <QPainter>
#include <QKeyEvent>
#include <QPoint>
#include <QTimer>
#define FLY_BIRD_SIZE 45

// scene游戏主场景，就是 gamescene这个主场景
BirdItem::BirdItem(QGraphicsScene* scene)
    :
      m_IsLandFall(true),
      m_isRaise(true)
{
    m_curFlyStatus = 0;

    // 添加图形项,就是这个小鸟项
    // 将当前的小鸟对象添加到游戏场景中去
    scene->addItem(this);

    // 初始化计时器,定时刷新小鸟
    m_birdReFreshTimer = new QTimer(this);
    connect(m_birdReFreshTimer,SIGNAL(timeout())
            ,this,SLOT(onRefreshBird()));
    m_birdReFreshTimer->start(10);

    // 通过设置小鸟位置属性值，达到动画效果
    m_flyAnimation = new QPropertyAnimation(this,"pos");

    connect(m_flyAnimation,SIGNAL(finished())
            ,this,SLOT(onFlyRaiseAnimationFinished()));
}

BirdItem::~BirdItem()
{

}

// 重写绘图区域
QRectF BirdItem::boundingRect() const
{
    // 左上角位置，   宽 、 高
    return QRectF(60,FLY_BIRD_SIZE*5,FLY_BIRD_SIZE,FLY_BIRD_SIZE);
}
// 小鸟上升动画
void BirdItem::flyRaiseAnimation()
{
    if(m_isRaise){
        m_isRaise = false;
        m_flyAnimation->stop(); // 将原来的动画结束，不管是什么动作

        int nMove = pos().y();  // 鸟儿移动的y值

        // 整个窗体中心为坐标原点，往上走就是负的
        // 算一下为什么是180
        if(nMove > -180){
            // 动画时长
            m_flyAnimation->setDuration(300);
            // 小鸟每次上升一个小鸟的高度
            m_flyAnimation->setEndValue(QPoint(this->pos().x(),this->pos().y()-FLY_BIRD_SIZE));
        }else{
            // 小鸟飞到了顶上
            m_flyAnimation->setDuration(300);
            m_flyAnimation->setEndValue(pos());
        }
        // 动画运动的曲线（规律）
        // QEasingCurve::Linear线性
        m_flyAnimation->setEasingCurve(QEasingCurve::InQuad);
        m_flyAnimation->start();
        // 动画结束，让其下落

    }
}
// 下降动画
void BirdItem::flyLandfallAnimation()
{
    if(m_IsLandFall){
        // m_IsLandFall = false;
        m_flyAnimation->stop();

        m_flyAnimation->setDuration(300);
        // 每次下降一个小鸟高度
        m_flyAnimation->setEndValue(QPoint(pos().x(),pos().y() + FLY_BIRD_SIZE));
        m_flyAnimation->setEasingCurve(QEasingCurve::InQuad);
        m_flyAnimation->start();

    }
}

bool BirdItem::checkIsCollided()
{
    // collidingItems与当前游戏项“冲突”(碰撞)的所有项
    if(collidingItems().isEmpty()){
        return false; // 没有碰上
    }else{
        return true;
    }
}

void BirdItem::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *, QWidget *)
{
    if(m_curFlyStatus < 10){ // 翅膀往上
        m_curFlyStatus++;
        painter->drawImage(boundingRect(),QImage(":/BirdGame/Resources/image/bird1.png"));
    }else if(m_curFlyStatus < 20){ // 翅膀居中
        m_curFlyStatus++;
        painter->drawImage(boundingRect(),QImage(":/BirdGame/Resources/image/bird2.png"));
    }else if(m_curFlyStatus < 30){ // 翅膀往下
        m_curFlyStatus++;
        painter->drawImage(boundingRect(),QImage(":/BirdGame/Resources/image/bird3.png"));
    }else{
        m_curFlyStatus = 0;
    }
}

void BirdItem::keyPressEvent(QKeyEvent *event)
{
    // 空格键
    if(event->key() == Qt::Key_Space){
        m_isRaise = true;
        flyRaiseAnimation();
    }
}

void BirdItem::onRefreshBird()
{
    // 触发重绘事件，达到刷新图片
    update();
}

void BirdItem::onFlyRaiseAnimationFinished()
{
    m_IsLandFall = true;
    // 执行下降标志
    flyLandfallAnimation();
}
