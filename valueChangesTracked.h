#ifndef VALUECHANGESTRACKED_H
#define VALUECHANGESTRACKED_H

#include <QWidget>
#include <QObject>
#include <QString>
#include <QDebug>

class valueChangesTracked : public QWidget
{
    Q_OBJECT

signals:

    void publishCommand(const QString command);

public:
    valueChangesTracked( void );
    virtual ~valueChangesTracked( void );

    bool getIgnoreSignals( void );
    void setIgnoreSignals( bool s );
	
    virtual void sendAllChangedValues( void );
    virtual void resetAllTrackedValues ( void ); // bool s = false );

protected:
	bool ignoreSignals;


};

#endif // VALUECHANGESTRACKED__H
