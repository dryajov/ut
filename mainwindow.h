#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QClipboard>
#include <QColorDialog>
#include <QDateTime>
#include <QDesktopServices>
#include <QDesktopWidget>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QMenu>
#include <QMessageBox>
#include <QMouseEvent>
#include <QMovie>
#include <QNetworkAccessManager>
#include <QNetworkCookieJar>
#include <QNetworkDiskCache>
#include <QNetworkReply>
#include <QProcess>
#include <QProgressBar>
#include <QPropertyAnimation>
#include <QSettings>
#include <QSizePolicy>
#include <QStandardPaths>
#include <QTextCodec>
#include <QTimer>
#include <QWebElement>
#include <QWebFrame>
#include <QWebHistory>
#include <QWebView>
#include <QWidget>

#include "lyrics.h"
#include "paginator.h"
#include "radio.h"
#include "settings.h"
#include "store.h"
#include "videooption.h"
#include "youtube.h"
#include "download_widget.h"
#include "ui_settings.h"
#include "ui_track.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Q_INVOKABLE void addToQueue(QString id, QString title, QString artist, QString album, QString base64, QString dominantColor, QString songId, QString albumId, QString artistId);
    Q_INVOKABLE void clear_youtubeSearchTerm();
    Q_INVOKABLE void playLocalTrack(QVariant songId);
    Q_INVOKABLE void playSongById(QVariant songIdVar);
    Q_INVOKABLE void playRadioFromWeb(QVariant streamDetails);
    Q_INVOKABLE void saveRadioChannelToFavourite(QVariant channelInfo);
    Q_INVOKABLE void resultLoaded();
    Q_INVOKABLE void setSearchTermAndOpenYoutube(QVariant term);
    Q_INVOKABLE void setThemeColor(QString); //sets themeColor in mainWindow
    Q_INVOKABLE void showAjaxError();
    Q_INVOKABLE void web_watch_video(QVariant data);
    Q_INVOKABLE void playVideo(QString trackId);

    QString youtubeSearchTerm;
    bool saveTracksAfterBuffer;



protected slots:
    void closeEvent(QCloseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent *resizeEvent);

private slots:
    bool checkEngine();
    bool hasDeadTracks(QListWidget *queue);
    bool hasUnCachedTracks(QListWidget *queue);
    bool isNumericStr(const QString str);
    bool trackIsBeingProcessed(QString songId);
    QString getExpireTime(const QString urlStr);
    QString menuStyle();
    void add_colors_to_color_widget();
    void assignNextTrack(QListWidget *list, int index);
    void assignPreviousTrack(QListWidget *list, int index);
    void browse_youtube();
    void check_engine_updates();
    void clear_queue();
    void compare_versions(QString date, QString n_date);
    void customColor();
    void download_engine_clicked();
    void dynamicThemeChanged(bool enabled);
    void evoke_engine_check();
    void fillOliviaMetaList(QListWidget *list);
    void filterList(const QString &arg1, QListWidget *list);
    void get_engine_version_info();
    void getAudioStream(QString ytIds, QString songId);
    void getNowPlayingTrackId();
    void hideListItems(QListWidget *list);
    void init_app();
    void init_lyrics();
    void init_offline_storage();
    void init_radio();
    void init_settings();
    void init_webview();
    void init_videoOption();
    void installEventFilters();
    void listItemDoubleClicked(QListWidget *list, QListWidgetItem *item);
    void loadPlayerQueue();
    void loadSettings();
    void on_close_clicked();
    void on_filter_youtube_textChanged(const QString &arg1);
    void on_fullScreen_clicked();
    void on_maximize_clicked();
    void on_minimize_clicked();
    void on_play_pause_clicked();
    void on_radioSeekSlider_sliderMoved(int position);
    void on_radioVolumeSlider_valueChanged(int value);
    void on_right_list_2_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_right_list_2_itemClicked(QListWidgetItem *item);
    void on_right_list_2_itemDoubleClicked(QListWidgetItem *item);
    void on_settings_clicked();
    void on_stop_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_youtube_queue_options_clicked();
    void on_ytdlRefreshAll_clicked();
    void on_ytdlStopAll_clicked();
    void processYtdlQueue();
    void queue_currentItemChanged(QListWidget *queue, QListWidgetItem *current, QListWidgetItem *previous);
    void queueShowOption(QListWidget *queue);
    void radio_demuxer_cache_duration_changed(double, double radio_playerPosition);
    void radioDuration(int dur);
    void radioPosition(int pos);
    void radioStatus(QString);
    void recommendations();
    void reloadREquested(QString dataType, QString query);
    void restart_required();
    void saveTrack(QString format);
    void set_app_theme(QColor rgb);
    void setCountry(QString country);
    void setPlayerPosition(qint64 position);
    void setTrackItemNowPlaying();
    void setZoom(qreal);
    void showTrackOption();
    void slot_netwManagerFinished(QNetworkReply *reply);
    void trackItemClicked(QListWidget *listWidget, QListWidgetItem *item);
    void transparency_changed(int value); //from settings widget
    void webViewLoaded(bool loaded);
    void ytdlFinished(int code);
    void ytdlReadyRead();
    void zoomin();
    void zoomout();

    //return pain text version of text which contains html symbolic notations
    QString htmlToPlainText(QString html){
        QTextDocument text;
        text.setHtml(html.replace("\\\"","'"));
        return text.toPlainText();
    }


    void on_shuffle_toggled(bool checked);

    void on_hideDebug_clicked();

    void videoOptionDownloadRequested(QStringList metaData, QStringList formats);
    void init_downloadWidget();
    void getEnabledTracks(QListWidget*);


    void show_local_saved_videos();
    void update_stats_right_list_2();

    void on_actionFullscreen_triggered();

    void on_actionSettings_triggered();

    void on_actionDownloaded_Videos_triggered();

    void on_actionQuit_triggered();

    void on_actionHome_triggered();

private:
    Widget *downloadWidget;
    bool animationRunning = false;
    bool isLoadingResults;
    int currentResultPage;
    int left_panel_width;
    Lyrics *lyricsWidget;
    paginator *pagination_manager = nullptr;
    QFile *core_file;
    QList<qint64> processIdList;
    QList<QString> OliviaMetaList; //for search purpose
    QList<QStringList> ytdlQueue ;
    QPoint oldPos;
    QProcess * ytdlProcess = nullptr;
    qreal horizontalDpi;
    qreal zoom;
    QSettings settingsObj;
    QString core_local_date,core_remote_date;
    QString database;
    QString gotoAlbumId,gotoArtistId,recommendationSongId,youtubeVideoId;//jumper vars
    QString nowPlayingSongId;
    QString offsetstr;
    QString pageType;
    QString previous_eqArg;
    QString setting_path;
    QString themeColor = "4,42,59,0.2";
    QStringList color_list ;
    QStringList searchSuggestionList;
    QWidget *settingsWidget;
    radio *radio_manager = nullptr;
    settings *settUtils;
    store *store_manager = nullptr;
    Ui::MainWindow *ui;
    Ui::settings settingsUi;
    Ui::track track_ui;
    Youtube *youtube;
    VideoOption *videoOption = nullptr;
    QStringList shuffledPlayerQueue;

};

class SelectColorButton : public QPushButton
{
    Q_OBJECT
signals:
    void setCustomColor(QColor);

public:
    void setColor( const QColor& color );
    const QColor& getColor();

public slots:
    void updateColor();
    void changeColor();

private:
    QColor color;
};

#endif // MAINWINDOW_H
