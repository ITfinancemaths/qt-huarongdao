#include "CMainWindow.h"
#include "ui_CMainWindow.h"
#include <QTime>
//此处的宏定义代表当前标签的行列，如当前为4，则ui有 4*4 个标签
#define MAX 4

CMainWindow::CMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(nullptr)
    , m_layout(nullptr)
{}

CMainWindow::~CMainWindow() {}

void CMainWindow::initial()
{
    if(nullptr == ui) {
        ui = new Ui::CMainWindow;
        ui->setupUi(this);
        //网格布局器指针
        m_layout = new QGridLayout;
        //new一个label为保留位置，并连接信号槽
        m_curNullLab = new CLabel;
        connect(m_curNullLab, &CLabel::clicked, this, &CMainWindow::labelUpdate);

        int range = MAX * MAX;
        for(int index = 1; index != range; ++index) {
            //循环创建label，并设置其文本和连接信号槽
            CLabel *curLab = new CLabel;
            curLab->setText(QString::number(index));
            connect(curLab, &CLabel::clicked, this, &CMainWindow::labelUpdate);
            //将label添加到还未使用label的数组中
            m_unuseLabVector.append(curLab);
        }

        qsrand (QTime(0, 0, 0).secsTo(QTime::currentTime()));
        for(int index = 0; index != range - 1; ++index) {
            //循环获取当前未使用label数组的大小，并使用随机数取出数组中的幸运儿，并将其添加到布局器中
            int size = m_unuseLabVector.size();
            CLabel *curLab = m_unuseLabVector.takeAt(qrand() % size);
            m_layout->addWidget(curLab, index / MAX, index % MAX);
        }
        //将保留位置添加到布局器最后一格中（右下角）
        m_layout->addWidget(m_curNullLab, MAX - 1, MAX - 1);
        //将布局器设置到ui中，并设置ui的背景颜色，使其视觉上有网格效果
        ui->centralWidget->setLayout(m_layout);
        ui->centralWidget->setStyleSheet("background-color: skyblue");
    }
}

void CMainWindow::unInitial()
{
    if(nullptr != m_layout) {
        //循环获取布局器中的Item
        QLayoutItem *child;
        while (child = m_layout->takeAt(0)) {
            //获取Item中的widget指针，将其父类置空，并释放及置空
            QWidget *widget = child->widget();
            widget->setParent(nullptr);
            delete widget;
            widget = nullptr;
            //将Item指针释放并置空
            delete child;
            child = nullptr;
        }
        delete m_layout;
        m_layout = nullptr;
    }

    if(nullptr != ui) {
        delete ui;
        ui = nullptr;
    }
}

void CMainWindow::labelUpdate()
{
    //获取信号发送者的指针对象
    m_curClickLab = dynamic_cast<CLabel *>(sender());
    QString text = m_curClickLab->text();
    //获取对应控件在布局器中的位置，方便判断
    int clickIndex = m_layout->indexOf(m_curClickLab);
    int nullIndex = m_layout->indexOf(m_curNullLab);
    //当前点击label与空label位置不同且其与空label相邻时更新标签值
    if(clickIndex != nullIndex && (clickIndex + MAX == nullIndex || clickIndex - MAX == nullIndex
                                  || clickIndex + 1 == nullIndex || clickIndex - 1 == nullIndex))
    {
        //更新标签值，并将空标签指针设置为当前点击的标签
        m_curClickLab->setText("");
        m_curNullLab->setText(text);
        m_curNullLab = m_curClickLab;
    }
}
