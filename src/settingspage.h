//Public Domain License

#pragma once

#include "ui_settingspage.h"

#include <coreplugin/dialogs/ioptionspage.h>

#include <QStringList>
#include <QSharedPointer>
#include <QPointer>

namespace SaveAllTheTime {

class Settings;

class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget *parent = 0);

    void setSettings(const Settings &);
    Settings settings();

private:
    Internal::Ui::SettingsPage m_ui;
};

class SettingsPage : public Core::IOptionsPage
{
    Q_OBJECT

public:
    explicit SettingsPage(const QSharedPointer<Settings> &settings);
    ~SettingsPage() override;

    QWidget *widget() override;
    void apply() override;
    void finish() override {}

signals:
    void applied();

private:
    const QSharedPointer<Settings> m_settings;

    QPointer<SettingsWidget> m_widget;
};

} // namespace
