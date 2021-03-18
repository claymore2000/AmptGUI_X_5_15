
#include "valueChangesTracked.h"

valueChangesTracked::valueChangesTracked( void )
{
    ignoreSignals = true;
}

valueChangesTracked::~valueChangesTracked( void )
{

}

bool valueChangesTracked::getIgnoreSignals( void )
{
    return ignoreSignals;
}

void valueChangesTracked::setIgnoreSignals( bool s )
{
    // qDebug() << Q_FUNC_INFO << " setting to " << QString::number(s);
    ignoreSignals = s;

}
	
void valueChangesTracked::sendAllChangedValues( void )
{

}

void valueChangesTracked::resetAllTrackedValues( void ) // bool s)
{

}
