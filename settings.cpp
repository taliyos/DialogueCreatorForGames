// settings.cpp
#include "settings.h"

Settings::Settings() {
    settings = new QSettings("OrganizationName", "AppName");
}

void Settings::saveSettings(const QString &key, const QVariant &value) {
    settings->setValue(key, value);
}

QVariant Settings::loadSettings(const QString &key, const QVariant &defaultValue) {
    return settings->value(key, defaultValue);
}
