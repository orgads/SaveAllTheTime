//Public Domain License

#pragma once

#include <QString>

QT_FORWARD_DECLARE_CLASS(QSettings)

namespace SaveAllTheTime {

class Settings {
public:
    //Export.
    void toSettings(QSettings *s) const;
    //Import.
    void fromSettings(const QSettings *s);
    bool equals(const Settings &s) const;

    int interval = 1;
};

inline bool operator==(const Settings &s1, const Settings &s2) { return s1.equals(s2); }
inline bool operator!=(const Settings &s1, const Settings &s2) { return !s1.equals(s2); }

} // namespace
