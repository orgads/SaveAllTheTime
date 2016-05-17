//Public Domain License

#include "settingspage.h"
#include "settings.h"
#include "saveallthetimeconstants.h"

#include <coreplugin/icore.h>

#include <QTextStream>
#include <QCoreApplication>

namespace SaveAllTheTime {

SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent)
{
    m_ui.setupUi(this);
}

void SettingsWidget::setSettings(const Settings &settings)
{
    m_ui.intervalSpinBox->setValue(settings.interval);
}

Settings SettingsWidget::settings()
{
    Settings rc;
    rc.interval = m_ui.intervalSpinBox->value();
    return rc;
}

SettingsPage::SettingsPage(const QSharedPointer<Settings> &settings) :
    m_settings( settings ),
    m_widget( nullptr )
{
    setId("A.SaveAllTheTime.General");
    setDisplayName(tr("General"));
    setCategory(Constants::SAVEALLTHETIME_SETTINGS_CATEGORY);
    setDisplayCategory(QCoreApplication::translate("SaveAllTheTime",
                       Constants::SAVEALLTHETIME_SETTINGS_TR_CATEGORY));
    setCategoryIcon(QLatin1String(Constants::SETTINGS_CATEGORY_SAVEALLTHETIME_ICON));
}

SettingsPage::~SettingsPage()
{
}

QWidget *SettingsPage::widget()
{
    if ( !m_widget )
    {
        m_widget = new SettingsWidget();
        m_widget->setSettings( *m_settings );
    }
    return m_widget;
}

void SettingsPage::apply()
{
    if (!m_widget)
    {
      // page was never shown
        return;
    }

    const Settings newSettings = m_widget->settings();
    if (newSettings != *m_settings)
    {
        *m_settings = newSettings;
        m_settings->toSettings( Core::ICore::settings() );
    }

    emit applied();
}

} // namespace
