#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
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

private:
    Ui::GameWindow *ui;
    GameScene* m_scene;     // 游戏场景
    BirdItem* m_birdItem;   // 鸟儿对象

};
#endif // GAMEWINDOW_H
