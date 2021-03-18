#ifndef OUTPUTLOGGERTHREAD_H
#define OUTPUTLOGGERTHREAD_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QString>
#include <QFile>
#include <QTextStream>


class outputLoggerThread : public QThread
{
    Q_OBJECT

public:
    explicit outputLoggerThread(QObject *parent = nullptr);
    ~outputLoggerThread() override;

    void startLoggerThreadInterface(int waitTimeout);
    void stopLoggerThreadOperation( void );

signals:
    void publishOutputLoggerThreadError(const QString s);
    void publishOutputLoggerReady( void );
    void publishOutputLoggerExit();
    void receiveOutputLoggerThreadExit();
    void publishCSVFileOpenFailed(const QString s);
    void publishRawFileOpenFailed(const QString s);

public slots:
    void handleStartOutputRawFile(const QString data);
    void handleStartOutputCSVFile(const QString data);
    void handleRawDataToLog(const QString data);
    void handleOTADataForCSV(const QString sn, const QString data);
    void handleStopOutputFiles(void);
    void handleTerminate( void );

private:
    void run() override;

    bool m_operational;
    QStringList m_rawDataToLogList;
    QStringList m_csvDataToLogList;

    int m_waitTimeout = 0;
    QMutex m_mutex;
    QMutex m_rawMutex;
    QMutex m_csvMutex;
    QWaitCondition m_cond;
    bool m_readyForRawData;
    QFile *m_rawLoggerFile;
    QTextStream *m_rawLoggerStream;
    bool m_readyForCSVData;
    bool m_writtenCSVHeaderLine;
    QFile *m_csvLoggerFile;
    QTextStream *m_csvLoggerStream;
};


#endif // OUTPUTLOGGERTHREAD_H
