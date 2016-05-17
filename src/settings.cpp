//Public Domain License

#include "settings.h"
#include <utils/environment.h>
#include <QSettings>

static const char groupC[] = "SaveAllTheTime";
static const char intervalC[] = "Interval";

namespace SaveAllTheTime {

bool Settings::equals(const Settings &rhs) const
{
    return interval == rhs.interval;
}

void Settings::toSettings(QSettings *settings) const
{
    settings->beginGroup(QLatin1String(groupC));
    settings->setValue(QLatin1String(intervalC), interval);
    settings->endGroup();
}

void Settings::fromSettings(const QSettings *settings)
{
    const QString rootKey = QLatin1String(groupC) + QLatin1Char('/');
    interval = settings->value(rootKey + QLatin1String(intervalC), 1).toInt();
}

} // namespace
