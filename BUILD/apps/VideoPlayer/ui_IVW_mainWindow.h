/********************************************************************************
** Form generated from reading UI file 'IVW_mainWindow.ui'
**
** Created: Tue 19. May 16:44:43 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IVW_MAINWINDOW_H
#define UI_IVW_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTableWidget>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IVW_mainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *toolButton_Open;
    QToolButton *toolButton_RemoveList;
    QToolButton *toolButton_AddFiles;
    QToolButton *toolButton_DeleteTrack;
    QToolButton *toolButton_UpTrack;
    QToolButton *toolButton_DownTrack;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *toolButton_Stop;
    QToolButton *toolButton_Prev;
    QToolButton *toolButton_PlayPause;
    QToolButton *toolButton_Next;
    QToolButton *toolButton_FullScreen;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *toolButton_UserGuide;
    QToolButton *toolButton_About;
    QToolButton *toolButton_CloseApp;
    QTableWidget *tableWidget;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_5;
    QFrame *line;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QLCDNumber *lcdNumber;
    QLabel *label_2;
    QLCDNumber *lcdNumber_Frame;
    QLabel *label;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_SendToWall;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_6;
    QToolButton *toolButton_SendToInteractiveWall;
    QSpacerItem *horizontalSpacer_7;
    QToolButton *toolButton_Settings;
    QGridLayout *gridLayout_2;
    QCheckBox *checkBox_AllVideo;
    QComboBox *comboBox_ScaleHeight;
    QLabel *label_6;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_EndRange;
    QLabel *label_EndRange;
    QLineEdit *lineEdit_InitialRange;
    QLabel *label_InitialRange;
    QPushButton *pushButton_InitialRange;
    QPushButton *pushButton_EndRange;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *IVW_mainWindow)
    {
        if (IVW_mainWindow->objectName().isEmpty())
            IVW_mainWindow->setObjectName(QString::fromUtf8("IVW_mainWindow"));
        IVW_mainWindow->resize(596, 488);
        centralWidget = new QWidget(IVW_mainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_4 = new QGridLayout(centralWidget);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, -1, 1);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        toolButton_Open = new QToolButton(centralWidget);
        toolButton_Open->setObjectName(QString::fromUtf8("toolButton_Open"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Images/fileopen.png"), QSize(), QIcon::Normal, QIcon::On);
        toolButton_Open->setIcon(icon);
        toolButton_Open->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(toolButton_Open);

        toolButton_RemoveList = new QToolButton(centralWidget);
        toolButton_RemoveList->setObjectName(QString::fromUtf8("toolButton_RemoveList"));
        toolButton_RemoveList->setEnabled(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Images/delete.png"), QSize(), QIcon::Normal, QIcon::On);
        toolButton_RemoveList->setIcon(icon1);
        toolButton_RemoveList->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(toolButton_RemoveList);

        toolButton_AddFiles = new QToolButton(centralWidget);
        toolButton_AddFiles->setObjectName(QString::fromUtf8("toolButton_AddFiles"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Images/list-add.png"), QSize(), QIcon::Normal, QIcon::On);
        toolButton_AddFiles->setIcon(icon2);
        toolButton_AddFiles->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(toolButton_AddFiles);

        toolButton_DeleteTrack = new QToolButton(centralWidget);
        toolButton_DeleteTrack->setObjectName(QString::fromUtf8("toolButton_DeleteTrack"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Images/list-remove.png"), QSize(), QIcon::Normal, QIcon::On);
        toolButton_DeleteTrack->setIcon(icon3);
        toolButton_DeleteTrack->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(toolButton_DeleteTrack);

        toolButton_UpTrack = new QToolButton(centralWidget);
        toolButton_UpTrack->setObjectName(QString::fromUtf8("toolButton_UpTrack"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Images/up.png"), QSize(), QIcon::Normal, QIcon::On);
        toolButton_UpTrack->setIcon(icon4);
        toolButton_UpTrack->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(toolButton_UpTrack);

        toolButton_DownTrack = new QToolButton(centralWidget);
        toolButton_DownTrack->setObjectName(QString::fromUtf8("toolButton_DownTrack"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Images/down.png"), QSize(), QIcon::Normal, QIcon::On);
        toolButton_DownTrack->setIcon(icon5);
        toolButton_DownTrack->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(toolButton_DownTrack);

        horizontalSpacer_2 = new QSpacerItem(188, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        toolButton_Stop = new QToolButton(centralWidget);
        toolButton_Stop->setObjectName(QString::fromUtf8("toolButton_Stop"));
        toolButton_Stop->setMinimumSize(QSize(0, 0));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Images/stop.png"), QSize(), QIcon::Normal, QIcon::On);
        toolButton_Stop->setIcon(icon6);
        toolButton_Stop->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(toolButton_Stop);

        toolButton_Prev = new QToolButton(centralWidget);
        toolButton_Prev->setObjectName(QString::fromUtf8("toolButton_Prev"));
        toolButton_Prev->setMinimumSize(QSize(0, 0));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Images/prev.png"), QSize(), QIcon::Normal, QIcon::On);
        toolButton_Prev->setIcon(icon7);
        toolButton_Prev->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(toolButton_Prev);

        toolButton_PlayPause = new QToolButton(centralWidget);
        toolButton_PlayPause->setObjectName(QString::fromUtf8("toolButton_PlayPause"));
        toolButton_PlayPause->setMinimumSize(QSize(0, 0));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Images/play.png"), QSize(), QIcon::Normal, QIcon::On);
        toolButton_PlayPause->setIcon(icon8);
        toolButton_PlayPause->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(toolButton_PlayPause);

        toolButton_Next = new QToolButton(centralWidget);
        toolButton_Next->setObjectName(QString::fromUtf8("toolButton_Next"));
        toolButton_Next->setMinimumSize(QSize(0, 0));
        toolButton_Next->setBaseSize(QSize(40, 40));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/Images/NextMenuButtonIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon9.addFile(QString::fromUtf8(":/Images/next.png"), QSize(), QIcon::Normal, QIcon::On);
        toolButton_Next->setIcon(icon9);
        toolButton_Next->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(toolButton_Next);

        toolButton_FullScreen = new QToolButton(centralWidget);
        toolButton_FullScreen->setObjectName(QString::fromUtf8("toolButton_FullScreen"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/Images/auto_layout.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_FullScreen->setIcon(icon10);
        toolButton_FullScreen->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(toolButton_FullScreen);

        horizontalSpacer_3 = new QSpacerItem(198, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        toolButton_UserGuide = new QToolButton(centralWidget);
        toolButton_UserGuide->setObjectName(QString::fromUtf8("toolButton_UserGuide"));
        toolButton_UserGuide->setLayoutDirection(Qt::LeftToRight);
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/Images/userManual.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_UserGuide->setIcon(icon11);
        toolButton_UserGuide->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(toolButton_UserGuide);

        toolButton_About = new QToolButton(centralWidget);
        toolButton_About->setObjectName(QString::fromUtf8("toolButton_About"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/Images/fileinfo-32.png"), QSize(), QIcon::Normal, QIcon::On);
        toolButton_About->setIcon(icon12);
        toolButton_About->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(toolButton_About);

        toolButton_CloseApp = new QToolButton(centralWidget);
        toolButton_CloseApp->setObjectName(QString::fromUtf8("toolButton_CloseApp"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/Images/exit.png"), QSize(), QIcon::Normal, QIcon::On);
        toolButton_CloseApp->setIcon(icon13);
        toolButton_CloseApp->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(toolButton_CloseApp);


        verticalLayout->addLayout(horizontalLayout_2);

        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setEnabled(true);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setDragEnabled(false);
        tableWidget->setDragDropMode(QAbstractItemView::NoDragDrop);
        tableWidget->setDefaultDropAction(Qt::IgnoreAction);
        tableWidget->setColumnCount(1);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(tableWidget);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_5);


        gridLayout_4->addLayout(verticalLayout, 0, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_5->addWidget(line);


        gridLayout_4->addLayout(horizontalLayout_5, 7, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 0, 2, 1, 1);

        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(5);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lcdNumber->sizePolicy().hasHeightForWidth());
        lcdNumber->setSizePolicy(sizePolicy);
        lcdNumber->setMinimumSize(QSize(200, 0));
        lcdNumber->setSmallDecimalPoint(true);
        lcdNumber->setNumDigits(20);
        lcdNumber->setSegmentStyle(QLCDNumber::Flat);
        lcdNumber->setProperty("value", QVariant(0));

        gridLayout_3->addWidget(lcdNumber, 0, 4, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 0, 3, 1, 1);

        lcdNumber_Frame = new QLCDNumber(centralWidget);
        lcdNumber_Frame->setObjectName(QString::fromUtf8("lcdNumber_Frame"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lcdNumber_Frame->sizePolicy().hasHeightForWidth());
        lcdNumber_Frame->setSizePolicy(sizePolicy1);
        lcdNumber_Frame->setMinimumSize(QSize(200, 0));
        lcdNumber_Frame->setSmallDecimalPoint(true);
        lcdNumber_Frame->setDigitCount(20);
        lcdNumber_Frame->setSegmentStyle(QLCDNumber::Flat);

        gridLayout_3->addWidget(lcdNumber_Frame, 1, 4, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 1, 3, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_SendToWall = new QLabel(centralWidget);
        label_SendToWall->setObjectName(QString::fromUtf8("label_SendToWall"));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label_SendToWall->setFont(font);

        horizontalLayout_4->addWidget(label_SendToWall);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);


        gridLayout_4->addLayout(horizontalLayout_4, 8, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(498, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        gridLayout_4->addLayout(horizontalLayout_3, 5, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        toolButton_SendToInteractiveWall = new QToolButton(centralWidget);
        toolButton_SendToInteractiveWall->setObjectName(QString::fromUtf8("toolButton_SendToInteractiveWall"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/Images/sendVideo.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_SendToInteractiveWall->setIcon(icon14);
        toolButton_SendToInteractiveWall->setIconSize(QSize(70, 30));
        toolButton_SendToInteractiveWall->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout_6->addWidget(toolButton_SendToInteractiveWall);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);

        toolButton_Settings = new QToolButton(centralWidget);
        toolButton_Settings->setObjectName(QString::fromUtf8("toolButton_Settings"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/Images/wrench73.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_Settings->setIcon(icon15);
        toolButton_Settings->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout_6->addWidget(toolButton_Settings);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        checkBox_AllVideo = new QCheckBox(centralWidget);
        checkBox_AllVideo->setObjectName(QString::fromUtf8("checkBox_AllVideo"));

        gridLayout_2->addWidget(checkBox_AllVideo, 1, 1, 1, 2);

        comboBox_ScaleHeight = new QComboBox(centralWidget);
        comboBox_ScaleHeight->setObjectName(QString::fromUtf8("comboBox_ScaleHeight"));

        gridLayout_2->addWidget(comboBox_ScaleHeight, 0, 2, 1, 2);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 0, 0, 1, 2);


        horizontalLayout_6->addLayout(gridLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lineEdit_EndRange = new QLineEdit(centralWidget);
        lineEdit_EndRange->setObjectName(QString::fromUtf8("lineEdit_EndRange"));

        gridLayout->addWidget(lineEdit_EndRange, 0, 3, 1, 1);

        label_EndRange = new QLabel(centralWidget);
        label_EndRange->setObjectName(QString::fromUtf8("label_EndRange"));

        gridLayout->addWidget(label_EndRange, 0, 2, 1, 1);

        lineEdit_InitialRange = new QLineEdit(centralWidget);
        lineEdit_InitialRange->setObjectName(QString::fromUtf8("lineEdit_InitialRange"));

        gridLayout->addWidget(lineEdit_InitialRange, 0, 1, 1, 1);

        label_InitialRange = new QLabel(centralWidget);
        label_InitialRange->setObjectName(QString::fromUtf8("label_InitialRange"));

        gridLayout->addWidget(label_InitialRange, 0, 0, 1, 1);

        pushButton_InitialRange = new QPushButton(centralWidget);
        pushButton_InitialRange->setObjectName(QString::fromUtf8("pushButton_InitialRange"));

        gridLayout->addWidget(pushButton_InitialRange, 1, 1, 1, 1);

        pushButton_EndRange = new QPushButton(centralWidget);
        pushButton_EndRange->setObjectName(QString::fromUtf8("pushButton_EndRange"));

        gridLayout->addWidget(pushButton_EndRange, 1, 3, 1, 1);


        horizontalLayout_6->addLayout(gridLayout);


        gridLayout_4->addLayout(horizontalLayout_6, 9, 0, 1, 1);

        IVW_mainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(IVW_mainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        IVW_mainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(toolButton_Open, toolButton_RemoveList);
        QWidget::setTabOrder(toolButton_RemoveList, toolButton_AddFiles);
        QWidget::setTabOrder(toolButton_AddFiles, toolButton_DeleteTrack);
        QWidget::setTabOrder(toolButton_DeleteTrack, toolButton_UpTrack);
        QWidget::setTabOrder(toolButton_UpTrack, toolButton_DownTrack);
        QWidget::setTabOrder(toolButton_DownTrack, toolButton_Stop);
        QWidget::setTabOrder(toolButton_Stop, toolButton_Prev);
        QWidget::setTabOrder(toolButton_Prev, toolButton_PlayPause);
        QWidget::setTabOrder(toolButton_PlayPause, toolButton_Next);
        QWidget::setTabOrder(toolButton_Next, toolButton_FullScreen);
        QWidget::setTabOrder(toolButton_FullScreen, toolButton_About);
        QWidget::setTabOrder(toolButton_About, toolButton_CloseApp);
        QWidget::setTabOrder(toolButton_CloseApp, tableWidget);
        QWidget::setTabOrder(tableWidget, toolButton_SendToInteractiveWall);
        QWidget::setTabOrder(toolButton_SendToInteractiveWall, checkBox_AllVideo);
        QWidget::setTabOrder(checkBox_AllVideo, comboBox_ScaleHeight);
        QWidget::setTabOrder(comboBox_ScaleHeight, lineEdit_InitialRange);
        QWidget::setTabOrder(lineEdit_InitialRange, lineEdit_EndRange);
        QWidget::setTabOrder(lineEdit_EndRange, pushButton_InitialRange);
        QWidget::setTabOrder(pushButton_InitialRange, pushButton_EndRange);

        retranslateUi(IVW_mainWindow);

        QMetaObject::connectSlotsByName(IVW_mainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *IVW_mainWindow)
    {
        IVW_mainWindow->setWindowTitle(QApplication::translate("IVW_mainWindow", "Interactive Video Wall", 0, QApplication::UnicodeUTF8));
        toolButton_Open->setText(QApplication::translate("IVW_mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_RemoveList->setText(QApplication::translate("IVW_mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_AddFiles->setText(QApplication::translate("IVW_mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_DeleteTrack->setText(QApplication::translate("IVW_mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_UpTrack->setText(QApplication::translate("IVW_mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_DownTrack->setText(QApplication::translate("IVW_mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_Stop->setText(QApplication::translate("IVW_mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_Prev->setText(QApplication::translate("IVW_mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_PlayPause->setText(QApplication::translate("IVW_mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_Next->setText(QApplication::translate("IVW_mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_FullScreen->setText(QApplication::translate("IVW_mainWindow", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButton_UserGuide->setToolTip(QApplication::translate("IVW_mainWindow", "Open user manual (Spanish)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_UserGuide->setText(QApplication::translate("IVW_mainWindow", "User Manual", 0, QApplication::UnicodeUTF8));
        toolButton_About->setText(QApplication::translate("IVW_mainWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_CloseApp->setText(QApplication::translate("IVW_mainWindow", "...", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("IVW_mainWindow", "Time:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("IVW_mainWindow", "Frame:", 0, QApplication::UnicodeUTF8));
        label_SendToWall->setText(QApplication::translate("IVW_mainWindow", "LAUNCH TO INTERACTIVE VIDEO WALL", 0, QApplication::UnicodeUTF8));
        toolButton_SendToInteractiveWall->setText(QApplication::translate("IVW_mainWindow", "Launch", 0, QApplication::UnicodeUTF8));
        toolButton_Settings->setText(QApplication::translate("IVW_mainWindow", "Settings", 0, QApplication::UnicodeUTF8));
        checkBox_AllVideo->setText(QApplication::translate("IVW_mainWindow", "Load all frames", 0, QApplication::UnicodeUTF8));
        comboBox_ScaleHeight->clear();
        comboBox_ScaleHeight->insertItems(0, QStringList()
         << QApplication::translate("IVW_mainWindow", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("IVW_mainWindow", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("IVW_mainWindow", "3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("IVW_mainWindow", "4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("IVW_mainWindow", "5", 0, QApplication::UnicodeUTF8)
        );
        label_6->setText(QApplication::translate("IVW_mainWindow", "Scale Height:", 0, QApplication::UnicodeUTF8));
        label_EndRange->setText(QApplication::translate("IVW_mainWindow", "End:", 0, QApplication::UnicodeUTF8));
        label_InitialRange->setText(QApplication::translate("IVW_mainWindow", "Initial:", 0, QApplication::UnicodeUTF8));
        pushButton_InitialRange->setText(QApplication::translate("IVW_mainWindow", "Set actual position", 0, QApplication::UnicodeUTF8));
        pushButton_EndRange->setText(QApplication::translate("IVW_mainWindow", "Set actual position", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class IVW_mainWindow: public Ui_IVW_mainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IVW_MAINWINDOW_H
