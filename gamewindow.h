#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QParallelAnimationGroup>
#include "gamescene.h"
#include "birditem.h"
QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

protected:
    // 重写绘图事件
    void paintEvent(QPaintEvent* event);

private:
    void initControl();     // 初始化控件
    // 加载样式
    void loadStyleSheet(const QString& sheetName);
    // 启动欢迎
    void startWelcome();
private:
    Ui::GameWindow *ui;
    GameScene* m_scene;     // 游戏场景
    BirdItem* m_birdItem;   // 鸟儿对象
    bool m_startGame;       // 游戏开始标志
    // 渐渐消失 动画组
    QParallelAnimationGroup* m_letterGroupFading;

};
#endif // GAMEWINDOW_H
