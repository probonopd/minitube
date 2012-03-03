#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <phonon/audiooutput.h>
#include <phonon/volumeslider.h>
#include <phonon/mediaobject.h>
#include <phonon/seekslider.h>
#include "View.h"
#include "SearchView.h"
#include "MediaView.h"
#include "AboutView.h"
#include "downloadview.h"

class SearchLineEdit;
class UpdateChecker;

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    static MainWindow* instance();
    MainWindow();
    ~MainWindow();
    Phonon::SeekSlider* getSeekSlider() { return seekSlider; }
    void readSettings();
    void writeSettings();

public slots:
    void showMedia(SearchParams *params);
    void messageReceived(const QString &message);
    void quit();

protected:
    void changeEvent(QEvent *);
    void closeEvent(QCloseEvent *);
    bool eventFilter(QObject *obj, QEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void resizeEvent(QResizeEvent *);

private slots:
    void checkForUpdate();
    void gotNewVersion(QString version);
    void goBack();
    void showSearch();
    void visitSite();
    void donate();
    void about();
    void fullscreen();
    void updateUIForFullscreen();
    void compactView(bool enable);
    void stop();
    void stateChanged(Phonon::State newState, Phonon::State oldState);
    void searchFocus();
    void tick(qint64 time);
    void totalTimeChanged(qint64 time);
    void setDefinitionMode(QString definitionName);
    void toggleDefinitionMode();
    void clearRecentKeywords();

    // volume shortcuts
    void volumeUp();
    void volumeDown();
    void volumeMute();
    void volumeChanged(qreal newVolume);
    void volumeMutedChanged(bool muted);

    // fullscreen toolbar
    void showFullscreenToolbar(bool show);
    void showFullscreenPlaylist(bool show);

    void setManualPlay(bool enabled);
    void updateDownloadMessage(QString);
    void downloadsFinished();
    void toggleDownloads(bool show);

    void startToolbarSearch(QString query);
    void floatOnTop(bool);
    void showActionInStatusBar(QAction*, bool show);
    void showStopAfterThisInStatusBar(bool show);

private:
    void initPhonon();
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void showWidget(QWidget*);
    static QString formatTime(qint64 time);
    bool confirmQuit();

    UpdateChecker *updateChecker;

    // view mechanism
    QStackedWidget *views;
    QStack<QWidget*> *history;

    // view widgets
    SearchView *searchView;
    MediaView *mediaView;
    QWidget *aboutView;
    QWidget *downloadView;

    // actions
    QAction *addGadgetAct;
    QAction *backAct;
    QAction *quitAct;
    QAction *siteAct;
    QAction *donateAct;
    QAction *aboutAct;
    QAction *searchFocusAct;

    // media actions
    QAction *skipBackwardAct;
    QAction *skipAct;
    QAction *pauseAct;
    QAction *stopAct;
    QAction *fullscreenAct;
    QAction *compactViewAct;
    QAction *webPageAct;
    QAction *copyPageAct;
    QAction *copyLinkAct;
    QAction *volumeUpAct;
    QAction *volumeDownAct;
    QAction *volumeMuteAct;
    QAction *findVideoPartsAct;

    // playlist actions
    QAction *removeAct;
    QAction *moveDownAct;
    QAction *moveUpAct;
    QAction *fetchMoreAct;
    QAction *clearAct;

    // menus
    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *playlistMenu;
    QMenu *helpMenu;

    // toolbar
    QToolBar *mainToolBar;
    SearchLineEdit *toolbarSearch;
    QToolBar *statusToolBar;

    // phonon
    Phonon::SeekSlider *seekSlider;
    Phonon::VolumeSlider *volumeSlider;
    Phonon::MediaObject *mediaObject;
    Phonon::AudioOutput *audioOutput;
    QLabel *currentTime;
    QLabel *totalTime;

    bool m_fullscreen;
    bool m_maximized;

};

#endif
