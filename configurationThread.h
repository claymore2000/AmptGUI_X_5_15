/****************************************************************************
**
****************************************************************************/

#ifndef CONFIGURATIONTHREAD_H
#define CONFIGURATIONTHREAD_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QString>
#include <QFile>


class ConfigurationThread : public QThread
{
    Q_OBJECT

public:
    explicit ConfigurationThread(QObject *parent = nullptr);
    ~ConfigurationThread() override;

    void startConfigurationThreadInterface(int waitTimeout, QString & directoryPath);
    void stopConfigurationThreadOperation( void );

signals:
    void receiveConfigurationThreadError(const QString &s);
    void sendConfigurationThreadError(const QString s);
    void sendConfigurationThreadInfo(const QString s);
    void receiveConfigurationThreadExit();
    void publishSavedConfiguration(const QStringList &s);

public slots:
  void receiveConfigurationToSave(const QString & configuration);
  void handleTerminate( void );

private:
    void run() override;

    bool m_operational;
    QStringList m_configurationList;

    int m_waitTimeout = 0;
    QMutex m_mutex;
    QWaitCondition m_cond;
    QFile *m_configurationFile;
    QString m_configurationPathAndFileName;
    QString m_errorString;
};

#endif 
