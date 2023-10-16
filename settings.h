#ifndef SETTINGS_H
#define SETTINGS_H
#include <QSettings>

class Settings {
public:
    Settings();
    void saveSettings(const QString &key, const QVariant &value);
    QVariant loadSettings(const QString &key, const QVariant &defaultValue = QVariant());

private:
    QSettings *settings;
};
#endif // SETTINGS_H
