#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QMainWindow>
#include "CLabel.h"
#include <QGridLayout>

namespace Ui {
class CMainWindow;
}
class CMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit CMainWindow(QWidget *parent = 0);
    ~CMainWindow();
    //初始化函数
    void initial();
    //反初始化函数
    void unInitial();

private:
    Ui::CMainWindow *	ui;
    CLabel *            m_curNullLab;       //当前空值标签
    CLabel *            m_curClickLab;      //当前点击标签
    QVector<CLabel *>   m_unuseLabVector;   //当前还未使用的标签容器
    QGridLayout *       m_layout;           //网格布局器

public slots:
    //标签值更新槽函数
    void labelUpdate();
};
#endif // CMAINWINDOW_H
