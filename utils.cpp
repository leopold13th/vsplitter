#include <QString>
#include <stdio.h>

#include "utils.h"

QString secs2time(double pos)
{
    char buffer [32];
    int hours = pos / 3600;
    int minutes = int(pos / 60) % 60;
    double secs = pos - (hours*3600 + minutes*60);
    sprintf(buffer, "%02i:%02i:%02.2f", hours%60, minutes, secs);
    QString item(buffer);
    return item;
}
