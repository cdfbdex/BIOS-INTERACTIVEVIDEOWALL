#include "IVW_mainWindow.h"
#include "ui_IVW_mainWindow.h"
#include <iostream>





#include <QtGui>


namespace
{
    const QString DEFAULT_LCDNUMBER_VALUE = "00:00:00  00:00:00";
	const QString DEFAULT_LCDNUMBER2_VALUE= " 000000    000000 ";
}


int numberOfFrames;



// On load of the window
IVW_mainWindow::IVW_mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IVW_mainWindow)
{
    ui->setupUi(this);
    SetToolTipsForUI();

    current_play_index_ = -1;
	current_comboBox_index = 0;
	initialRange = 0;
	endRange = 0;

	proceso = new QProcess(this);



    ui->toolButton_FullScreen->setVisible(false);

    CreatePhononObjects();
    SetupPhononUI();
    ConnectSlots();
    SetEnabledForToolButtons();

    ui->lcdNumber->display(DEFAULT_LCDNUMBER_VALUE);
	ui->lcdNumber_Frame->display(DEFAULT_LCDNUMBER2_VALUE);

	ui->lineEdit_InitialRange->setText("1801");
	ui->lineEdit_EndRange->setText("2000");

}

IVW_mainWindow::~IVW_mainWindow()
{
    delete ui;
}



void IVW_mainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}



void IVW_mainWindow::resizeEvent(QResizeEvent *event)
{
    if (ui->tableWidget->columnCount() > 0)
    {
        ui->tableWidget->setColumnWidth(0, this->width());
    }
}



void IVW_mainWindow::ConnectSlots()
{
    QObject::connect(ui->toolButton_CloseApp, SIGNAL(clicked()), this, SLOT(toolButton_CloseApp_Clicked()));
    QObject::connect(ui->toolButton_Open, SIGNAL(clicked()), this, SLOT(toolButton_Open_Clicked()));
    QObject::connect(ui->toolButton_Stop, SIGNAL(clicked()), this, SLOT(toolButton_Stop_Clicked()));
    QObject::connect(ui->toolButton_DeleteTrack, SIGNAL(clicked()), this, SLOT(toolButton_DeleteTrack_Clicked()));
    QObject::connect(ui->toolButton_Next, SIGNAL(clicked()), this, SLOT(toolButton_Next_Clicked()));
    QObject::connect(ui->toolButton_Prev, SIGNAL(clicked()), this, SLOT(toolButton_Prev_Clicked()));
    QObject::connect(ui->toolButton_PlayPause, SIGNAL(clicked()), this, SLOT(toolButton_PlayPause_Clicked()));
    QObject::connect(ui->toolButton_About, SIGNAL(clicked()), this, SLOT(toolButton_About_Clicked()));
    QObject::connect(ui->toolButton_AddFiles, SIGNAL(clicked()), this, SLOT(toolButton_AddFiles_Clicked()));
    QObject::connect(ui->toolButton_RemoveList, SIGNAL(clicked()), this, SLOT(toolButton_RemoveList_Clicked()));
    QObject::connect(ui->toolButton_UpTrack, SIGNAL(clicked()), this, SLOT(toolButton_UpTrack_Clicked()));
    QObject::connect(ui->toolButton_DownTrack, SIGNAL(clicked()), this, SLOT(toolButton_DownTrack_Clicked()));
    QObject::connect(ui->toolButton_FullScreen, SIGNAL(clicked()), this, SLOT(toolButton_FullScreen_Clicked()));
    QObject::connect(ui->tableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(tableWidget_itemDoubleClicked(QTableWidgetItem*)));    
    QObject::connect(ui->tableWidget, SIGNAL(currentItemChanged(QTableWidgetItem*,QTableWidgetItem*)), this, SLOT(tableWidget_currentItemChanged(QTableWidgetItem*,QTableWidgetItem*)));


    QObject::connect(this->videoPlayer_->mediaObject(), SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SLOT(videoPlayer_stateChanged(Phonon::State,Phonon::State)));
    QObject::connect(this->videoPlayer_->mediaObject(), SIGNAL(tick(qint64)), this, SLOT(videoPlayer_tick(qint64)));
    QObject::connect(this->videoPlayer_->mediaObject(), SIGNAL(totalTimeChanged(qint64)), this, SLOT(videoPlayer_totalTimeChanged(qint64)));
    QObject::connect(this->videoPlayer_, SIGNAL(finished()), this, SLOT(videoPlayer_finished()));    

	// SEND DATA TO VIDEO INTERACTIVE WALL
	//connect(ui->checkBox, SIGNAL(stateChanged(int)), this, SLOT(on_checkBox_stateChanged(int)));
	QObject::connect(ui->comboBox_SelectionType, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBox_SelectionType_Changed(int)));
	QObject::connect(ui->toolButton_SendToInteractiveWall, SIGNAL(clicked()), this, SLOT(toolButton_SendToInteractiveWall_Clicked()));

	QObject::connect(this->proceso, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(On_ProcesoTerminado(int, QProcess::ExitStatus)));
}




void IVW_mainWindow::CreatePhononObjects()
{
    videoPlayer_ = new Phonon::VideoPlayer(Phonon::VideoCategory, this);
    videoPlayer_->videoWidget()->setVisible(false);
    videoPlayer_->mediaObject()->setTickInterval(1000);

    seekSlider_ = new Phonon::SeekSlider(this);
    seekSlider_->setMediaObject(videoPlayer_->mediaObject());

    volumeSlider_ = new Phonon::VolumeSlider(this);
    volumeSlider_->setAudioOutput(videoPlayer_->audioOutput());
    volumeSlider_->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
}




void IVW_mainWindow::SetupPhononUI()
{
    ui->gridLayout_3->addWidget(seekSlider_,0,0);
    ui->horizontalLayout_3->addWidget(volumeSlider_);
    ui->verticalLayout->addWidget(videoPlayer_);
}



void IVW_mainWindow::SetToolTipsForUI()
{
    ui->toolButton_About->setToolTip("About");
    ui->toolButton_AddFiles->setToolTip("Add files to playlist");
    ui->toolButton_CloseApp->setToolTip("Close");
    ui->toolButton_DeleteTrack->setToolTip("Delete selected files from the playlist");
    ui->toolButton_DownTrack->setToolTip("Move down current file in the playlist");
    ui->toolButton_Next->setToolTip("Play next file in the playlist");
    ui->toolButton_Open->setToolTip("Open files and create new playlist");
    ui->toolButton_PlayPause->setToolTip("Play/Pause");
    ui->toolButton_Prev->setToolTip("Play previous file in the playlist");
    ui->toolButton_RemoveList->setToolTip("Remove playlist");
    ui->toolButton_Stop->setToolTip("Stop");
    ui->toolButton_UpTrack->setToolTip("Move up current file in the playlist");
    ui->toolButton_FullScreen->setToolTip("Full Screen/Press Esc or mouse double click to exit from Full Screen Mode");
}





void IVW_mainWindow::toolButton_CloseApp_Clicked()
{
    this->close();
}






void IVW_mainWindow::SetEnabledForToolButtons()
{
    bool bEnabled = ui->tableWidget->rowCount() > 0;
    ui->toolButton_DeleteTrack->setEnabled(bEnabled);
    ui->toolButton_PlayPause->setEnabled(bEnabled);
    ui->toolButton_RemoveList->setEnabled(bEnabled);
    ui->toolButton_Stop->setEnabled(bEnabled);


    bEnabled = (ui->tableWidget->rowCount() > 1) && (ui->tableWidget->currentRow() < ui->tableWidget->rowCount() - 1);
    ui->toolButton_DownTrack->setEnabled(bEnabled);
    ui->toolButton_Next->setEnabled(bEnabled);


    bEnabled = (ui->tableWidget->rowCount() > 1) && (ui->tableWidget->currentRow() > 0);
    ui->toolButton_Prev->setEnabled(bEnabled);
    ui->toolButton_UpTrack->setEnabled(bEnabled);
}






void IVW_mainWindow::LoadFilesInList(const QStringList& list, bool bClearTable)
{
    if (bClearTable)
    {
        ClearTable();
    }

    if (ui->tableWidget->columnCount() == 0)
    {
        ui->tableWidget->insertColumn(0);
    }

    int size = list.size();
    int currentRow = ui->tableWidget->rowCount();

    for (int i = 0; i < size; ++i)
    {
        ui->tableWidget->insertRow(currentRow);

        QTableWidgetItem *item = new QTableWidgetItem();
        item->setText(QFileInfo(list[i]).fileName());
        item->setIcon(QFileIconProvider().icon(QFileInfo(list[i])));
        ui->tableWidget->setItem(currentRow, 0, item);

        ++currentRow;
    }

    ui->tableWidget->setColumnWidth(0, this->width());
}





void IVW_mainWindow::AddFilesToMediaSourceList(const QStringList& list)
{
    int count_files = list.size();
    for (int i = 0; i < count_files; ++i)
    {
        Phonon::MediaSource source(list[i]);
        list_sources_.append(source);
    }
}



QStringList IVW_mainWindow::GetFilesWillPlay()
{
    return QFileDialog::getOpenFileNames(this, QString("Open music and video files"), QDesktopServices::storageLocation(QDesktopServices::MusicLocation), QString("Media files (*.mp3 *.wav *.wma *.avi *.wmv);;Any files (*)"));
}




bool IVW_mainWindow::hasVideo(const QString& fileName) const
{
    QFileInfo fi(fileName);

    QString extens = fi.completeSuffix();

    extens = extens.toLower();

    if (extens == "avi" || extens == "wmv" || extens == "vob")
        return true;

    return false;
}





void IVW_mainWindow::videoPlayer_totalTimeChanged(qint64 time)
{
    displayTimeTotal_.setHMS(time / (60000*60), (time / 60000) % 60, (time / 1000) % 60);
    ui->lcdNumber->display("00:00:00" + QString("  ") + displayTimeTotal_.toString("hh:mm:ss"));
	
	/*TODO:*/
	//ui->lcdNumber_Frame->display(QString(" 000000    %d ").arg(numberOfFrames));
}



void IVW_mainWindow::videoPlayer_finished()
{
    videoPlayer_->stop();
    videoPlayer_->videoWidget()->setFullScreen(false);
    releaseKeyboard();
    releaseMouse();
    MarkPlayingItem(current_play_index_, false);
    videoPlayer_->videoWidget()->setVisible(false);
    ui->tableWidget->setVisible(true);

    if (current_play_index_ >= ui->tableWidget->rowCount() - 1)
        return;

    ui->tableWidget->setCurrentItem(ui->tableWidget->item(current_play_index_ + 1, 0));

    playNext();

    MarkPlayingItem(current_play_index_);
}








void IVW_mainWindow::videoPlayer_tick(qint64 time)
{
    QTime displayTime(time / (60000*60), (time / 60000) % 60, (time / 1000) % 60);
    ui->lcdNumber->display(displayTime.toString("hh:mm:ss") + QString("  ") + displayTimeTotal_.toString("hh:mm:ss"));
	//std::cout<<"Hola"<<std::endl;
}





void IVW_mainWindow::videoPlayer_stateChanged(Phonon::State newState, Phonon::State oldState)
{
    switch (newState)
    {
        case Phonon::ErrorState:
            if (videoPlayer_->mediaObject()->errorType() == Phonon::FatalError)
            {
                QMessageBox::warning(this, tr("Fatal Error"),
                videoPlayer_->mediaObject()->errorString());
            }
            else
            {
                QMessageBox::warning(this, tr("Error"),
                videoPlayer_->mediaObject()->errorString());
            }
            break;

        case Phonon::PlayingState:
            ui->toolButton_PlayPause->setIcon(QIcon(":Images/pause.png"));
            ShowCurrentPlayingInTaskBar(list_sources_[current_play_index_]);
            if (videoPlayer_->mediaObject()->hasVideo())
            {
                ui->toolButton_FullScreen->setVisible(true);
            }
            else
            {
                ui->toolButton_FullScreen->setVisible(false);
            }
            break;

        case Phonon::StoppedState:
            ui->lcdNumber->display(DEFAULT_LCDNUMBER_VALUE);
			ui->lcdNumber_Frame->display(DEFAULT_LCDNUMBER2_VALUE);
            ui->toolButton_PlayPause->setIcon(QIcon(":Images/play.png"));

            videoPlayer_->videoWidget()->setVisible(false);
            ui->tableWidget->setVisible(true);            
            statusBar()->showMessage("");

            ui->toolButton_FullScreen->setVisible(false);
            break;

        case Phonon::PausedState:
            ui->toolButton_PlayPause->setIcon(QIcon(":Images/play.png"));
            break;

        case Phonon::BufferingState:
            break;

        default:
            break;
    }

}












void IVW_mainWindow::toolButton_Open_Clicked()
{
    QStringList files = GetFilesWillPlay();

    if (files.isEmpty())
        return;

    list_sources_.clear();
    AddFilesToMediaSourceList(files);
    LoadFilesInList(files, true);

    if (ui->tableWidget->currentRow() < 0)
    {
        ui->tableWidget->setCurrentItem(ui->tableWidget->item(0, 0));        
    }    

    videoPlayer_->mediaObject()->setCurrentSource(list_sources_[ui->tableWidget->currentRow()]);

    current_play_index_ = ui->tableWidget->currentRow();

    SetEnabledForToolButtons();
}



void IVW_mainWindow::ClearTable()
{
    ui->tableWidget->clear();

    int row_count = ui->tableWidget->rowCount();
    int column_count = ui->tableWidget->columnCount();

    for (int i = 0; i < row_count; ++i)
    {
        ui->tableWidget->removeRow(0);
    }

    for (int i = 0; i < column_count; ++i)
    {
        ui->tableWidget->removeColumn(0);
    }

}



void IVW_mainWindow::toolButton_RemoveList_Clicked()
{
    toolButton_Stop_Clicked();
    ClearTable();
    list_sources_.clear();

    SetEnabledForToolButtons();

    current_play_index_ = -1;
}




void IVW_mainWindow::toolButton_AddFiles_Clicked()
{
    QStringList files = GetFilesWillPlay();

    if (files.isEmpty())
        return;

    AddFilesToMediaSourceList(files);
    LoadFilesInList(files);

    if (ui->tableWidget->currentRow() < 0)
    {
        ui->tableWidget->setCurrentItem(ui->tableWidget->item(0, 0));        
    }


    if (!videoPlayer_->isPlaying())
    {
        videoPlayer_->mediaObject()->setCurrentSource(list_sources_[ui->tableWidget->currentRow()]);
    }
    else
    {
        ShowCurrentPlayingInTaskBar(list_sources_[current_play_index_]);
    }

    if (current_play_index_ == -1)
    {
        current_play_index_ = ui->tableWidget->currentRow();
    }


    SetEnabledForToolButtons();
}





void IVW_mainWindow::toolButton_DeleteTrack_Clicked()
{
    if (ui->tableWidget->rowCount() == 0)
        return;

    QList<QTableWidgetItem*> listSelectedItems = ui->tableWidget->selectedItems();
    int count_items = listSelectedItems.count();    
    if (count_items == 0)
        return;
    int row = listSelectedItems[0]->row();

    if (current_play_index_  >= row && current_play_index_ < row + count_items)
    {
       toolButton_Stop_Clicked();
    }

    for (int i = 0; i < count_items; ++i)
    {
        ui->tableWidget->removeRow(row);
        list_sources_.removeAt(row);
    }

    SetEnabledForToolButtons();

    if (ui->tableWidget->rowCount() == 0)
    {
        current_play_index_ = -1;
    }

}


void IVW_mainWindow::toolButton_UpTrack_Clicked()
{
    int current_row = ui->tableWidget->currentRow();
    if (current_row <= 0)
        return;

    QTableWidgetItem* item_up  = ui->tableWidget->takeItem(current_row, 0);
    QTableWidgetItem* item_down  = ui->tableWidget->takeItem(current_row - 1, 0);
    ui->tableWidget->setItem(current_row - 1, 0, item_up);
    ui->tableWidget->setItem(current_row, 0, item_down);

    bool wasPlaying = videoPlayer_->isPlaying() || videoPlayer_->isPaused();

    if (wasPlaying)
    {
        if (current_play_index_ == current_row)
        {
            --current_play_index_;
        }
        else
        {
            if (current_play_index_ == current_row - 1)
            {
                current_play_index_ = current_row;
            }
        }
    }

    list_sources_.swap(current_row, current_row - 1);
    ui->tableWidget->setCurrentItem(ui->tableWidget->item(current_row - 1, 0));
}




void IVW_mainWindow::toolButton_DownTrack_Clicked()
{
    int current_row = ui->tableWidget->currentRow();
    if (current_row < 0 || current_row >= ui->tableWidget->rowCount() - 1)
        return;

    QTableWidgetItem* item_down  = ui->tableWidget->takeItem(current_row, 0);
    QTableWidgetItem* item_up  = ui->tableWidget->takeItem(current_row + 1, 0);

    ui->tableWidget->setItem(current_row + 1, 0, item_down);
    ui->tableWidget->setItem(current_row, 0, item_up);

    bool wasPlaying = videoPlayer_->isPlaying() || videoPlayer_->isPaused();

    if (wasPlaying)
    {
        if (current_play_index_ == current_row)
        {
            ++current_play_index_;
        }
        else
        {
            if (current_play_index_ == current_row + 1)
            {
                current_play_index_ = current_row;
            }
        }

    }


    list_sources_.swap(current_row, current_row + 1);
    ui->tableWidget->setCurrentItem(ui->tableWidget->item(current_row + 1, 0));
}


void IVW_mainWindow::toolButton_Stop_Clicked()
{    
    videoPlayer_->stop();

    if (videoPlayer_->videoWidget()->isVisible())
    {
        videoPlayer_->videoWidget()->setVisible(false);
        ui->tableWidget->setVisible(true);
        ui->tableWidget->setCurrentItem(ui->tableWidget->item(current_play_index_, 0));
    }

    MarkPlayingItem(current_play_index_, false);

    SetEnabledForToolButtons();
}



void IVW_mainWindow::toolButton_Next_Clicked()
{
    bool wasPlaying = videoPlayer_->isPlaying() || videoPlayer_->isPaused();

    if (wasPlaying)
    {
        videoPlayer_->stop();
        MarkPlayingItem(current_play_index_, false);
        videoPlayer_->videoWidget()->setVisible(false);
        ui->tableWidget->setVisible(true);
        ++current_play_index_;
        ui->tableWidget->setCurrentItem(ui->tableWidget->item(current_play_index_, 0));
        playNext();
        MarkPlayingItem(current_play_index_);
    }
    else
    {
        ui->tableWidget->setCurrentItem(ui->tableWidget->item(ui->tableWidget->currentRow() + 1, 0));
    }



}

void IVW_mainWindow::toolButton_Prev_Clicked()
{
    bool wasPlaying = videoPlayer_->isPlaying() || videoPlayer_->isPaused();

    if (wasPlaying)
    {
        videoPlayer_->stop();
        MarkPlayingItem(current_play_index_, false);
        videoPlayer_->videoWidget()->setVisible(false);
        ui->tableWidget->setVisible(true);
        --current_play_index_;
        ui->tableWidget->setCurrentItem(ui->tableWidget->item(current_play_index_, 0));
        playNext();
        MarkPlayingItem(current_play_index_);
    }
    else
    {
       ui->tableWidget->setCurrentItem(ui->tableWidget->item(ui->tableWidget->currentRow() - 1, 0));
    }
}






void IVW_mainWindow::playNext()
{
    current_play_index_ = ui->tableWidget->currentRow();

    if (hasVideo(list_sources_[current_play_index_].fileName()))
    {
        ui->tableWidget->setVisible(false);
        videoPlayer_->videoWidget()->setVisible(true);        
    }
    else
    {
        videoPlayer_->videoWidget()->setVisible(false);
        ui->tableWidget->setVisible(true);
    }

    if (!videoPlayer_->isPaused())
    {
        videoPlayer_->play(list_sources_[current_play_index_].fileName());
    }
}




void IVW_mainWindow::toolButton_PlayPause_Clicked()
{
    if (videoPlayer_->isPlaying())
    {        
        videoPlayer_->pause();
    }
    else
    {
        if (!videoPlayer_->isPaused())
        {
            current_play_index_ = ui->tableWidget->currentRow();

            if (hasVideo(list_sources_[current_play_index_].fileName()))
            {
                ui->tableWidget->setVisible(false);                
                videoPlayer_->videoWidget()->setVisible(true);
            }
            else
            {               
                videoPlayer_->videoWidget()->setVisible(false);
                ui->tableWidget->setVisible(true);
            }

            videoPlayer_->play(list_sources_[current_play_index_]);
        }
        else
        {
            videoPlayer_->play();
        }

        MarkPlayingItem(current_play_index_);
    }
}




void IVW_mainWindow::ShowCurrentPlayingInTaskBar(const Phonon::MediaSource& source)
{
    statusBar()->showMessage("Now playing: " + QFileInfo(source.fileName()).fileName());
}






void IVW_mainWindow::toolButton_About_Clicked()
{
    QMessageBox::information(this, tr("About Qt Media Player"),
                                   tr("The Qt Media Player is very simple media player."
                                      "This player uses Qt Phonon multimedia library."));
}




void IVW_mainWindow::tableWidget_itemDoubleClicked(QTableWidgetItem* item)
{
    if (videoPlayer_->isPlaying() || videoPlayer_->isPaused())
    {
        toolButton_Stop_Clicked();
        MarkPlayingItem(current_play_index_, false);
    }

    playNext();
    MarkPlayingItem(current_play_index_);
}






void IVW_mainWindow::tableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    if (current == 0)
        return;

    int index = current->row();

    if (index == 0)
    {
        ui->toolButton_UpTrack->setEnabled(false);
    }
    else
    {
        ui->toolButton_UpTrack->setEnabled(true);
    }


    if (index == ui->tableWidget->rowCount() - 1)
    {
        ui->toolButton_DownTrack->setEnabled(false);
    }
    else
    {
        ui->toolButton_DownTrack->setEnabled(true);
    }


    bool wasPlaying = videoPlayer_->isPlaying() || videoPlayer_->isPaused();

    if (wasPlaying)
    {
        index = current_play_index_;
    }


    if (index == 0)
    {
        ui->toolButton_Prev->setEnabled(false);        
    }
    else
    {
        ui->toolButton_Prev->setEnabled(true);        
    }


    if (index == ui->tableWidget->rowCount() - 1)
    {        
        ui->toolButton_Next->setEnabled(false);
    }
    else
    {        
        ui->toolButton_Next->setEnabled(true);
    }



	// Process previous information of the selected item
	QString file = list_sources_.at(ui->tableWidget->currentRow()).fileName();
	const char* filePath = file.toLocal8Bit().constData();


	/**/
	QMessageBox msgBox;

	if (!videoFile.isOpened())
	{
		videoFile = cv::VideoCapture(filePath);
		numberOfFrames = int(videoFile.get(CV_CAP_PROP_FRAME_COUNT));
	}
	else
	{
		videoFile.release();
		videoFile = cv::VideoCapture(filePath);
		numberOfFrames = videoFile.get(CV_CAP_PROP_FRAME_COUNT);
	}

	

	//QMessageBox msgBox;
	msgBox.setText(QString().sprintf("Number of frames = %d", numberOfFrames));
	msgBox.exec();


}





void IVW_mainWindow::MarkPlayingItem(int index, bool bMark)
{
    QTableWidgetItem* item = ui->tableWidget->item(index, 0);
    if (item == 0)
        return;

    if (bMark)
    {
        item->setBackgroundColor(QColor(Qt::lightGray));
        item->setForeground(QBrush(Qt::blue));
    }
    else
    {
        item->setBackgroundColor(QColor(Qt::white));
        item->setForeground(QBrush(Qt::black));
    }
}



void IVW_mainWindow::toolButton_FullScreen_Clicked()
{
    if (videoPlayer_->isPlaying() && videoPlayer_->mediaObject()->hasVideo())
    {
        grabKeyboard();
        grabMouse();
        videoPlayer_->videoWidget()->setFullScreen(true);
    }
}



void IVW_mainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    videoPlayer_->videoWidget()->setFullScreen(false);
    releaseKeyboard();
    releaseMouse();
}



void IVW_mainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Escape:
            videoPlayer_->videoWidget()->setFullScreen(false);
            releaseMouse();
            releaseKeyboard();
            break;

        default:
            break;
    }
}



// SLOTS TO SEND INFORMATION TO INTERACTIVE WALL APPLICATION
void IVW_mainWindow::on_checkBox_AllVideo_stateChanged(int state)
{
	if (state)
	{
		ui->label_InitialRange->setEnabled(false);
		ui->lineEdit_InitialRange->setEnabled(false);
		ui->label_EndRange->setEnabled(false);
		ui->lineEdit_EndRange->setEnabled(false);
		ui->pushButton_InitialRange->setEnabled(false);
		ui->pushButton_EndRange->setEnabled(false);
		ui->comboBox_SelectionType->setEnabled(false);
		ui->label_6->setEnabled(false);
	}
	else
	{
		ui->label_InitialRange->setEnabled(true);
		ui->lineEdit_InitialRange->setEnabled(true);
		ui->label_EndRange->setEnabled(true);
		ui->lineEdit_EndRange->setEnabled(true);
		ui->pushButton_InitialRange->setEnabled(true);
		ui->pushButton_EndRange->setEnabled(true);
		ui->comboBox_SelectionType->setEnabled(true);
		ui->label_6->setEnabled(true);
	}	
}


void IVW_mainWindow::comboBox_SelectionType_Changed(int index)
{
	current_comboBox_index = index;

	QMessageBox msgBox;
	msgBox.setText(QString().sprintf("Valor = %d", index));
	msgBox.exec();
}


void IVW_mainWindow::toolButton_SendToInteractiveWall_Clicked()
{
	initialRange = ui->lineEdit_InitialRange->text().toInt();
	endRange = ui->lineEdit_EndRange->text().toInt();

	// Get filePath from the selected video.

	if (list_sources_.isEmpty())
	{
		QMessageBox msgBox;
		msgBox.setText(QString().sprintf("Please load a video."));
		msgBox.exec();
		return;
	}
	else
	{
		QString file = list_sources_.at(ui->tableWidget->currentRow()).fileName();
		const char* filePath = file.toLocal8Bit().constData();
		//std::cout << "Ruta archivo: " << fileTexto << std::endl;
		//std::cout << "Initial Range: " << initialRange << std::endl;
		//std::cout << "End Range: " << endRange << std::endl;

		





		char *comando = new char[300];
		sprintf(comando, "InteractiveWallNKinect.exe %s %d %d", filePath, initialRange, endRange);

		proceso->startDetached(comando);

		//QMessageBox msgBox1;
		//msgBox1.setText(QString().sprintf("Valor Inicial= %d \nValor Final= %d",initialRange,endRange));
		//msgBox1.exec();

		//QMessageBox msgBox;
		//msgBox.setText(file);
		//msgBox.exec();
	}
}

void IVW_mainWindow::On_ProcesoTerminado(int, QProcess::ExitStatus)
{
	QMessageBox msgBox;
	msgBox.setText(QString().sprintf("Process has been finished."));
	msgBox.exec();
}





/*TODO: OBTENER RUTA DEL ARCHIVO ESPECIFICADO*/
// CAMBIAR ORDEN DE TABULACION .UI
// CREAR CALCULO DE FRAMES PROCESANDO EL VIDEO CON OPENCV VIDEOCAPTURE

//QTableWidgetItem* item = ui->tableWidget->item(ui->tableWidget->currentRow(), 0);

//Phonon::MediaSource pp = list_sources_.at(ui->tableWidget->currentRow());
//QMessageBox msgBox;
////msgBox.setText(QString().sprintf("Valor = %d", ui->tableWidget->currentRow()));
//QString file = pp.fileName();
//msgBox.setText(file);
//msgBox.exec();



//Phonon::MediaSource pp = list_sources_.at(ui->tableWidget->currentRow());
//QString file = pp.fileName();

//const char* fileTexto = file.toLocal8Bit().constData();
//std::cout << fileTexto;