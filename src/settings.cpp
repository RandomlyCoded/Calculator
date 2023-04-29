#include "settings.h"

#include <QColor>
#include <QSettings>

Settings::Settings(QObject *parent)
    : QObject{parent}
    , m_settings{new QSettings{"settings.ini", QSettings::IniFormat, this}}
{
    if(m_settings->allKeys().isEmpty())
        restoreDefaultSettings();
}

QColor Settings::backgroundColor()
{
    return m_settings->value("color/background").value<QColor>();
}

void Settings::setBackgroundColor(QColor newBackgroundColor)
{
    m_settings->setValue("color/background", newBackgroundColor.name());
    emit backgroundColorChanged();
}

QColor Settings::textColor()
{
    return m_settings->value("color/text").value<QColor>();
}

void Settings::setTextColor(QColor newTextColor)
{
    m_settings->setValue("color/text", newTextColor.name());
    emit textColorChanged();
}

QColor Settings::outlineColor()
{
    return m_settings->value("color/outline").value<QColor>();
}

void Settings::setOutlineColor(QColor newOutlineColor)
{
    m_settings->setValue("color/outline", newOutlineColor.name());
    emit outlineColorChanged();
}

bool Settings::bold()
{
    return m_settings->value("font/bold").toBool();
}

void Settings::setBold(bool newBold)
{
    m_settings->setValue("font/bold", newBold);
    emit boldChanged();
}

bool Settings::italic()
{
    return m_settings->value("font/italic").toBool();
}

void Settings::setItalic(bool newItalic)
{
    m_settings->setValue("font/italic", newItalic);
    emit italicChanged();
}

QString Settings::fontName()
{
    return m_settings->value("font/name").toString();
}

void Settings::setFontName(QString newFontName)
{
    m_settings->setValue("font/name", newFontName);
    emit fontNameChanged();
}

bool Settings::showPrimitiveOperations()
{
    return m_settings->value("display/primitive").toBool();
}

void Settings::setShowPrimitiveOperations(bool newShow)
{
    m_settings->setValue("display/primitive", newShow);
    emit showPrimitiveOperationsChanged();
}

bool Settings::showComplexOperations()
{
    return m_settings->value("display/complex").toBool();
}

void Settings::setShowComplexOperations(bool newShow)
{
    m_settings->setValue("display/complex", newShow);
    emit showComplexOperationsChanged();
}

bool Settings::useAnsInPrimitive()
{
    return m_settings->value("misc/useAnsInPrimitive").toBool();
}

void Settings::setUseAnsInPrimitive(bool newUse)
{
    m_settings->setValue("misc/useAnsInPrimitive", newUse);
    emit useAnsInPrimitiveChanged();
}

void Settings::restoreDefaultSettings()
{
    setTextColor({0, 0, 0});
    setBackgroundColor({255, 255, 255});
    setOutlineColor({0x2d, 0x2d, 0x2d});

    setBold(false);
    setItalic(false);
    setFontName("Source Code Pro");

    setShowComplexOperations(true);
    setShowPrimitiveOperations(true);

    setUseAnsInPrimitive(false);
}
