#include "amptgui_x.h"
#include <QApplication>
#include <QDateTime>

#include "amptbuildtime.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AmptGUI_X w;
    QString AmptGUI_X_WindowTitle("AmptGUI_X   Version : ");
    QString formatIt("yyyy_MM_dd hh:mm:ss");
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    AmptGUI_X_WindowTitle +=  APP_VERSION;
    AmptGUI_X_WindowTitle += "   Build Time : " + BUILDV;
    AmptGUI_X_WindowTitle += "   Time Started : " + CurrentDateTime;

    w.setWindowTitle(AmptGUI_X_WindowTitle);
    w.show();
    // w.showFullScreen(); // w.show()

    return a.exec();
}
