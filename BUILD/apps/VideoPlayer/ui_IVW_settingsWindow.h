/********************************************************************************
** Form generated from reading UI file 'IVW_settingsWindow.ui'
**
** Created: Tue 19. May 16:44:43 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IVW_SETTINGSWINDOW_H
#define UI_IVW_SETTINGSWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_IVW_settingsWindow
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QSpinBox *spinBox_secondImage;
    QPushButton *pushButtonAdd;
    QSpinBox *spinBox_firstImage;
    QLabel *label_2;
    QLabel *label;
    QPushButton *pushButtonDelete;
    QPushButton *pushButtonClear;
    QTableView *tableView_data;
    QSpacerItem *verticalSpacer;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *IVW_settingsWindow)
    {
        if (IVW_settingsWindow->objectName().isEmpty())
            IVW_settingsWindow->setObjectName(QString::fromUtf8("IVW_settingsWindow"));
        IVW_settingsWindow->resize(419, 324);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Images/VideoWall_icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        IVW_settingsWindow->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(IVW_settingsWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        spinBox_secondImage = new QSpinBox(IVW_settingsWindow);
        spinBox_secondImage->setObjectName(QString::fromUtf8("spinBox_secondImage"));

        gridLayout->addWidget(spinBox_secondImage, 1, 3, 1, 1);

        pushButtonAdd = new QPushButton(IVW_settingsWindow);
        pushButtonAdd->setObjectName(QString::fromUtf8("pushButtonAdd"));

        gridLayout->addWidget(pushButtonAdd, 4, 0, 1, 1);

        spinBox_firstImage = new QSpinBox(IVW_settingsWindow);
        spinBox_firstImage->setObjectName(QString::fromUtf8("spinBox_firstImage"));

        gridLayout->addWidget(spinBox_firstImage, 1, 1, 1, 1);

        label_2 = new QLabel(IVW_settingsWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 2, 1, 1);

        label = new QLabel(IVW_settingsWindow);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        pushButtonDelete = new QPushButton(IVW_settingsWindow);
        pushButtonDelete->setObjectName(QString::fromUtf8("pushButtonDelete"));

        gridLayout->addWidget(pushButtonDelete, 4, 1, 1, 1);

        pushButtonClear = new QPushButton(IVW_settingsWindow);
        pushButtonClear->setObjectName(QString::fromUtf8("pushButtonClear"));

        gridLayout->addWidget(pushButtonClear, 4, 3, 1, 1);

        tableView_data = new QTableView(IVW_settingsWindow);
        tableView_data->setObjectName(QString::fromUtf8("tableView_data"));

        gridLayout->addWidget(tableView_data, 3, 0, 1, 4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 3, 1, 1);

        label_3 = new QLabel(IVW_settingsWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 2, 0, 1, 4, Qt::AlignHCenter);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonClose = new QPushButton(IVW_settingsWindow);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));

        horizontalLayout->addWidget(pushButtonClose);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(IVW_settingsWindow);

        QMetaObject::connectSlotsByName(IVW_settingsWindow);
    } // setupUi

    void retranslateUi(QDialog *IVW_settingsWindow)
    {
        IVW_settingsWindow->setWindowTitle(QApplication::translate("IVW_settingsWindow", "Settings - Interactive Video Wall", 0, QApplication::UnicodeUTF8));
        pushButtonAdd->setText(QApplication::translate("IVW_settingsWindow", "Add row", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("IVW_settingsWindow", "<html><head/><body><p align=\"center\">with Kinect</p></body></html>", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("IVW_settingsWindow", "<html><head/><body><p align=\"center\">Swap Kinect</p></body></html>", 0, QApplication::UnicodeUTF8));
        pushButtonDelete->setText(QApplication::translate("IVW_settingsWindow", "Delete row", 0, QApplication::UnicodeUTF8));
        pushButtonClear->setText(QApplication::translate("IVW_settingsWindow", "Clear table", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_3->setToolTip(QApplication::translate("IVW_settingsWindow", "If invalid data is given, there will be an error in application launch.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_3->setText(QApplication::translate("IVW_settingsWindow", "Fill data according to the number of connected kinects.", 0, QApplication::UnicodeUTF8));
        pushButtonClose->setText(QApplication::translate("IVW_settingsWindow", "Close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class IVW_settingsWindow: public Ui_IVW_settingsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IVW_SETTINGSWINDOW_H
