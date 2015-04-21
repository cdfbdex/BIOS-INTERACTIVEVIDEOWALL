#ifndef IVW_MAINWINDOW_H
#define IVW_MAINWINDOW_H



#include <QMainWindow>
#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <Phonon/VideoWidget.h>
#include <Phonon/VideoPlayer.h>
#include <Phonon/Path.h>
#include <phonon/backendcapabilities.h>
#include <QList>
#include <QTableWidgetItem>
#include <QTime>
#include <QtMultimedia>
#include <QProcess>




#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>




namespace Ui {
    class IVW_mainWindow;
}

class IVW_mainWindow : public QMainWindow {
    Q_OBJECT
public:
    IVW_mainWindow(QWidget *parent = 0);
    ~IVW_mainWindow();

protected:
    void changeEvent(QEvent *e);
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private slots:
    void toolButton_CloseApp_Clicked();
    void toolButton_Open_Clicked();
    void toolButton_Stop_Clicked();
    void toolButton_DeleteTrack_Clicked();
    void toolButton_Next_Clicked();
    void toolButton_Prev_Clicked();
    void toolButton_PlayPause_Clicked();
    void toolButton_About_Clicked();
    void toolButton_AddFiles_Clicked();
    void toolButton_RemoveList_Clicked();
    void toolButton_UpTrack_Clicked();
    void toolButton_DownTrack_Clicked();
    void toolButton_FullScreen_Clicked();

    void tableWidget_itemDoubleClicked(QTableWidgetItem* item);
    void tableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

    void videoPlayer_stateChanged(Phonon::State newState, Phonon::State oldState);
    void videoPlayer_tick(qint64 time);
    void videoPlayer_totalTimeChanged(qint64 time);
    void videoPlayer_finished();

	// SEND INFORMATION TO INTERACTIVE APPLICATION
	void on_checkBox_AllVideo_stateChanged(int state);
	void toolButton_SendToInteractiveWall_Clicked();

	void On_FinishedProcess(int, QProcess::ExitStatus);

	void getInfoOfSelectedVideo();
	void pushButton_InitialRange_Clicked();
	void pushButton_EndRange_Clicked();


private:
    void ConnectSlots();
    void CreatePhononObjects();
    void LoadFilesInList(const QStringList& list, bool bClearTable = false);
    void ClearTable();
    void AddFilesToMediaSourceList(const QStringList& list);
    QStringList GetFilesWillPlay();

    void SetupPhononUI();

    bool hasVideo(const QString& fileName) const;
    void playNext();
    void ShowCurrentPlayingInTaskBar(const Phonon::MediaSource& source);
    void MarkPlayingItem(int index, bool bMark = true);
    void SetToolTipsForUI();    
    void SetEnabledForToolButtons();
	//void VRPN_CALLBACK handle_analog( void* userData, const vrpn_ANALOGCB a );

private:
    Ui::IVW_mainWindow *ui;
	//vrpn_Analog_Remote* vrpnAnalog;// = new vrpn_Analog_Remote(argv[1]);

    Phonon::SeekSlider *seekSlider_;    
    Phonon::VolumeSlider *volumeSlider_;
    QList<Phonon::MediaSource> list_sources_;

    Phonon::VideoPlayer *videoPlayer_;
    QTime displayTimeTotal_;


    int current_play_index_;
	int current_checkBox_state;				// 0 if is unchecked, 1 if is checked
	int current_selected_video;
	int ScaleFactor;						//Scale Factor for window height


	int initialRange;
	int endRange;


	int numberOfFrames;
	double fpsVideo;
	unsigned int actualFrame,actualTime;
	double maxTime;


	char* videoPath;

	QProcess* process;

	cv::VideoCapture videoFile;

};

#endif // IVW_mainWindow_H
