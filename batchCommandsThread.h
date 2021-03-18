/****************************************************************************
**
****************************************************************************/

#ifndef BATCHCOMMANDSTHREAD_H
#define BATCHCOMMANDSTHREAD_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QVector>


class BatchCommandsThread : public QThread
{
    Q_OBJECT

public:
    explicit BatchCommandsThread(QObject *parent = nullptr);
    ~BatchCommandsThread() override;

    void startBatchCommandsThreadInterface(int waitTimeout);
    void stopBatchCommandsThreadOperation( void );

signals:
    void publishBatchCommandsThreadError(const QString s);
    void publishBatchCommandsFileValidated(bool);
    void publishBatchCommandsFileOperationBegun( void );
    void publishBatchCommandsFileOperationEnded( void );
    void publishBatchCommandToGateway(const QString currentCommand);
    void publishBatchCommandStatus(const QString status);

public slots:
    void handlePublishBatchFileToValidate(const QString fileName);
    void handlePublishBatchFileStartStop( void );
    void handlePublishTerminate( void );
    void handlePublishCurrentActiveMAC(const QString currentActiveMAC);

 private:
    void run() override;

    bool m_operational;
    bool m_running;
    bool m_validated;

    QString m_currentActiveMAC;

    QString m_batchCommandsFileName;
    QFile *m_batchCommandsFile;
    QTextStream *m_batchCommandsStream;

    unsigned int m_numberOfBatchCommandLoopsToDo;
    unsigned int m_numberOfBatchCommandLoopsSoFar;
    unsigned int m_currentIndexIntoBatchCommandsVector;
    
    int m_waitTimeout = 0;
    QMutex m_mutex;
    QWaitCondition m_cond;
    QVector<QString> m_batchCommands;

    bool validateBatchFile(const QString fileName);
};

#endif 
