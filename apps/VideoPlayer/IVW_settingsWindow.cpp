#include "IVW_settingsWindow.h"
#include "ui_IVW_settingsWindow.h"

#include <QtGui>

// On load of the window
IVW_settingsWindow::IVW_settingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IVW_settingsWindow)
{
    ui->setupUi(this);
	ConnectSlots();

	// Variables initialization
	model = new QStandardItemModel(0, 2, this);

	ui->tableView_data->setModel(model);
	ReadDataFromFile();
}

IVW_settingsWindow::~IVW_settingsWindow()
{
    delete ui;
}

// Slot connection
void IVW_settingsWindow::ConnectSlots()
{
	QObject::connect(ui->pushButtonAdd, SIGNAL(clicked()), this, SLOT(pushButtonAdd_Click()));
	QObject::connect(ui->pushButtonDelete, SIGNAL(clicked()), this, SLOT(pushButtonDelete_Click()));
	QObject::connect(ui->pushButtonClear, SIGNAL(clicked()), this, SLOT(pushButtonClear_Click()));
	QObject::connect(ui->pushButtonClose, SIGNAL(clicked()), this, SLOT(pushButtonClose_Click()));
}


// SLOT DEFINITION
void IVW_settingsWindow::ReadDataFromFile()
{
	/// Read File to fill data in model
	QFile file("KinectOrder.txt");
	if (!file.open(QIODevice::ReadOnly))
	{
		//If file was not open, create it.
		WriteDataOnFile();

		//If file is still not open, show error
		if (!file.open(QIODevice::ReadOnly))
		{
			QMessageBox::information(0, "Error reading file.", file.errorString());
			return;
		}
	}

	// Read each line of the file and show it in the tableView
	QTextStream inFile(&file);
	while (!inFile.atEnd())
	{
		QString line = inFile.readLine();
		QStringList fields = line.split(" ");

		QList<QStandardItem*> newRow;
		for (int i = 0; i<2; i++)
		{
			QStandardItem* itm = new QStandardItem(QString(fields.at(i)));
			newRow.append(itm);
		}
		// Append read data in the matrix
		model->appendRow(newRow);
	}
	file.close();
}


void IVW_settingsWindow::WriteDataOnFile()
{
	/// WriteFile with data contained in model
	QFile file("KinectOrder.txt");
	if (!file.open(QIODevice::WriteOnly))
	{
		// Show error message if file was not open properly
		QMessageBox::information(0, "Error writing file.", file.errorString());
		return;
	}

	// Write tableView data into a file separated by white space in each row
	QString dataRow;
	for (int row = 0; row < model->rowCount(); row++)
	{
		dataRow = model->item(row, 0)->text() + " " + model->item(row, 1)->text();
		QTextStream out(&file);
		out << dataRow << endl;
	}
	file.close();
}

void IVW_settingsWindow::pushButtonAdd_Click()
{
	// Function to add data to the model and write it in the file
	int data1 = ui->spinBox_firstImage->value();
	int data2 = ui->spinBox_secondImage->value();
	
	int maxKinect = 10;

	// Verify proper input of data
	if (data1 < 1 || data2 < 1 || data1 >maxKinect || data2 > maxKinect)
	{
		QMessageBox msgBox;
		msgBox.setText(QString().sprintf("The values must be between 1 and %d.",maxKinect));
		msgBox.exec();
	}
	else
	{
		// Append row to model
		QList<QStandardItem*> newRow;
		newRow.append(new QStandardItem(QString::number(data1)));
		newRow.append(new QStandardItem(QString::number(data2)));
		model->appendRow(newRow);

		WriteDataOnFile();
	}
	
}

void IVW_settingsWindow::pushButtonDelete_Click()
{
	// Function to delete the selected row in model
	int selectedRow = ui->tableView_data->currentIndex().row();
	bool removed = model->removeRow(selectedRow);

	// If removal of row was successful, write data
	if (removed)
	{
		WriteDataOnFile();
	}
	else
	{
		// Show error message
		QMessageBox msgBox;
		msgBox.setWindowTitle("Error");
		msgBox.setText("Error removing selected row.");
		msgBox.exec();
	}
}

void IVW_settingsWindow::pushButtonClear_Click()
{
	// Delete all rows in model
	while (model->rowCount() > 0)
	{
		model->removeRow(0);
	}
	WriteDataOnFile();
}

void IVW_settingsWindow::pushButtonClose_Click()
{
	WriteDataOnFile();
	this->close();
}

