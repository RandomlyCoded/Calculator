#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class QSettings;

class Settings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(QColor outlineColor READ outlineColor WRITE setOutlineColor NOTIFY outlineColorChanged)

    Q_PROPERTY(bool bold READ bold WRITE setBold NOTIFY boldChanged)
    Q_PROPERTY(bool italic READ italic WRITE setItalic NOTIFY italicChanged)
    Q_PROPERTY(QString fontName READ fontName WRITE setFontName NOTIFY fontNameChanged)

    Q_PROPERTY(bool showPrimitiveOperations READ showPrimitiveOperations WRITE setShowPrimitiveOperations NOTIFY showPrimitiveOperationsChanged)
    Q_PROPERTY(bool showComplexOperations READ showComplexOperations WRITE setShowComplexOperations NOTIFY showComplexOperationsChanged)

    Q_PROPERTY(bool useAnsInPrimitive READ useAnsInPrimitive WRITE setUseAnsInPrimitive NOTIFY useAnsInPrimitiveChanged)

public:
    explicit Settings(QObject *parent = nullptr);

    QColor backgroundColor();
    void setBackgroundColor(QColor newBackgroundColor);

    QColor textColor();
    void setTextColor(QColor newTextColor);

    QColor outlineColor();
    void setOutlineColor(QColor newOutlineColor);


    bool bold();
    void setBold(bool newBold);

    bool italic();
    void setItalic(bool newItalic);

    QString fontName();
    void setFontName(QString newFontName);


    bool showPrimitiveOperations();
    void setShowPrimitiveOperations(bool newShow);

    bool showComplexOperations();
    void setShowComplexOperations(bool newShow);

    bool useAnsInPrimitive();
    void setUseAnsInPrimitive(bool newUse);

public slots:
    void restoreDefaultSettings();

signals:
    void textColorChanged();
    void backgroundColorChanged();
    void outlineColorChanged();

    void italicChanged();
    void boldChanged();
    void fontNameChanged();

    void showPrimitiveOperationsChanged();
    void showComplexOperationsChanged();

    void useAnsInPrimitiveChanged();

private:
    QSettings *const m_settings;
};

#endif // SETTINGS_H
