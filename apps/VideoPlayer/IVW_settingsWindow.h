#ifndef IVW_SETTINGSWINDOW_H
#define IVW_SETTINGSWINDOW_H



#include <QDialog>
#include <QtCore>
#include <QtGui>


namespace Ui {
    class IVW_settingsWindow;
}

class IVW_settingsWindow : public QDialog {
    Q_OBJECT

public:
    IVW_settingsWindow(QWidget *parent = 0);
    ~IVW_settingsWindow();

private slots:
	void ReadDataFromFile();
	void WriteDataOnFile();
	void pushButtonAdd_Click();
	void pushButtonClear_Click();
	void pushButtonDelete_Click();
	void pushButtonClose_Click();
	
private:
	void ConnectSlots();

private:
    Ui::IVW_settingsWindow *ui;
	QStandardItemModel *model;
    
};

#endif // IVW_settingsWindow_H
