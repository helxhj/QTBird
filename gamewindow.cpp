#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "buttonitem.h"
#include <QFile>
#include <QGraphicsView>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>
#include <QStyleOption>
#include <QTimer>

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameWindow)
    , m_startGame(false)
{
    ui->setupUi(this);
    initControl();
    setWindowTitle("飞翔的小鸟");
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::paintEvent(QPaintEvent *)
{
    // 自定义paint事件
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);
}

void GameWindow::initControl()
{
    // 加载样式
    loadStyleSheet("GameWindow");
    // 获取当前窗体的矩形，
    // 因为是在当前窗口进行游戏，所以传入的矩形就是当前窗体
    QRectF gameRect = rect();
    // 初始化游戏场景
    m_scene = new GameScene(this,gameRect);
    // 游戏视图
    // 将场景添加到视图中
    QGraphicsView* view = new QGraphicsView(m_scene,this);
    view->setScene(m_scene); // 设置游戏场景
    // 视图没有边框，背景透明
    view->setStyleSheet("border:nonr;background:transparent;");
    // 设置缓存为背景模式
    view->setCacheMode(QGraphicsView::CacheBackground);
    startWelcome();
}

// 加载样式
void GameWindow::loadStyleSheet(const QString &sheetName)
{
    QFile file(":/BirdGame/Resources/qss/" + sheetName+".css");
    if(file.open(QFile::ReadOnly)){

        // 获取当前默认的样式
        QString strStyleSheet = this->styleSheet();
        // 读取文件所有内容
        strStyleSheet += file.readAll();
        // 设置样式
        this->setStyleSheet(strStyleSheet);
        file.close();
    }

}
// 启动欢迎
void GameWindow::startWelcome()
{
    // 道路

    // 管道

    // 小鸟
    m_birdItem = new BirdItem(m_scene);

    // 游戏装态检测
    m_checkGameStatusTimer = new QTimer(this);
    connect(m_checkGameStatusTimer,SIGNAL(timeout()),
            this,SLOT(onCheckGameStatus())); // 定时检测游戏状态是否是输了

    // 欢迎的字母  “飞吧，像风一样自由，无法挽留..."
    const int nLetters = 15;
    struct{
      char const* pix; // 字符 如 “飞”
      qreal initX,initY;    // 字符起始坐标
      qreal destX,destY;    // 字符结束坐标
    }letterData[nLetters] = {
    {"飞",-1000,-1000,250,100}, // -1000，-1000表示从这个坐标飞过来
    {"吧",-800,-1000,300,100},
    {",",-600,-1000,350,100},

    {"像",-400,-1000,150,160},
    {"风",1000,2000,200,160},
    {"一",800,2000,250,160},
    {"样",600,2000,300,160},
    {"自",400,2000,350,160},
    {"由",200,2000,400,160},
    {",",0,2000,450,160},

    {"无",0,2000,175,220},
    {"法",0,2000,225,220},
    {"挽",0,2000,275,220},
    {"留",0,2000,325,220},
    {"...",0,2000,375,220},
    };

    // 连续动画组
    QSequentialAnimationGroup* letterGroupMoving = new QSequentialAnimationGroup(this);
    // 并行动画组
    m_letterGroupFading  = new QParallelAnimationGroup(this);
    for(int i = 0;i < nLetters;i++){
        // 文本图形项
        QString htmlText = QString("<span style=\"font-family:'Berlin Sans FB';font-size:38px;font-weight:600;color:#194819;\">%1</span>")
                .arg(letterData[i].pix);
        QGraphicsTextItem* letter = new QGraphicsTextItem();
        letter->setHtml(htmlText);
        letter->setPos(letterData[i].initX,letterData[i].initY);

        // 文本项属性动画
        QPropertyAnimation* moveAnimation = new QPropertyAnimation(letter,"pos",letterGroupMoving);
        // 设置字符动画结束的位置
        moveAnimation->setEndValue(QPointF(letterData[i].destX,letterData[i].destY));
        moveAnimation->setDuration(200);
        moveAnimation->setEasingCurve(QEasingCurve::OutElastic);
        letterGroupMoving->addPause(50); // 暂停

        // 字符渐渐消失            opacity 透明度
        QPropertyAnimation* fadeAnimation = new QPropertyAnimation(letter,"opacity",m_letterGroupFading);
        fadeAnimation->setDuration(1000);
        fadeAnimation->setEndValue(0);// 透明度，0-1
        fadeAnimation->setEasingCurve(QEasingCurve::OutQuad);

        // 往场景中添加
        m_scene->addItem(letter);
    }

    // 启动策略，动画在停止后删除
    letterGroupMoving->start(QAbstractAnimation::DeleteWhenStopped);

    // 添加按钮图形项
    QPixmap pix = QPixmap(":/BirdGame/Resources/image/startButton.png");
    ButtonItem* btnItem = new ButtonItem(pix,m_scene);
    btnItem->setPos(QPoint(250,300));

    // 按钮渐渐消失动画
    QPropertyAnimation* fadeAnimation = new QPropertyAnimation(btnItem,"opacity",m_letterGroupFading);
    fadeAnimation->setDuration(600); // 动画时长600ms
    fadeAnimation->setEndValue(0);  // 结束值 opacity为0就完全透明
    fadeAnimation->setEasingCurve(QEasingCurve::OutQuart);

    // 按钮点击，游戏开始
    connect(btnItem,SIGNAL(clicked()),this,SLOT(onStartBtnClicked()));
    connect(fadeAnimation,&QPropertyAnimation::finished,
            [this](){
        m_startGame = true;
        m_checkGameStatusTimer->start(50);
        m_birdItem->flyLandfallAnimation(); // 往下边掉
    });
}

void GameWindow::GameOver()
{

}

void GameWindow::onStartBtnClicked()
{
    // 启动渐渐消失动画，动画结束后，自己删除
    m_letterGroupFading->start(QAbstractAnimation::DeleteWhenStopped);

}

void GameWindow::onCheckGameStatus()
{
    // 鸟儿和其他场景有冲突(碰撞)
    if(m_birdItem->checkIsCollided()){
        GameOver();
    }
}

