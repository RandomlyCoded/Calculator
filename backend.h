#ifndef BACKEND_H
#define BACKEND_H

#include <QColor>
#include <QMap>
#include <QObject>

class QFile;
class QSettings;

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QString> availableFunctions READ availableFunctions CONSTANT FINAL)
    Q_PROPERTY(bool useAnsForPrimitive READ ansForPrimitive NOTIFY ansForPrimitiveChanged FINAL)

    Q_PROPERTY(QColor textColor READ settingTextColor WRITE setSettingTextColor NOTIFY settingTextColorChanged FINAL)
    Q_PROPERTY(QColor outlineColor READ settingOutlineColor WRITE setSettingOutlineColor NOTIFY settingOutlineColorChanged FINAL)
    Q_PROPERTY(QColor backgroundColor READ settingBackgroundColor WRITE setSettingBackgroundColor NOTIFY settingBackgroundColorChanged FINAL)

    Q_PROPERTY(bool bold READ settingBold WRITE setSettingBold NOTIFY settingBoldChanged FINAL)
    Q_PROPERTY(bool italic READ settingItalic WRITE setSettingItalic NOTIFY settingItalicChanged FINAL)
    Q_PROPERTY(QString fontName READ settingFontName WRITE setSettingFontName NOTIFY settingFontNameChanged FINAL)

    Q_PROPERTY(bool showPrimitiveOperations READ settingShowPrimitiveOperations WRITE setSettingShowPrimitiveOperations NOTIFY settingShowPrimitiveOperationsChanged FINAL)
    Q_PROPERTY(bool showComplexOperations READ settingShowComplexOperations WRITE setSettingShowComplexOperations NOTIFY settingShowComplexOperationsChanged FINAL)

public:
    explicit Backend(QObject *parent = nullptr);
    ~Backend();

    const QList<QString> availableFunctions() const { return m_functionNames.keys(); }

    bool ansForPrimitive() const { return m_useAnsForPrimitive; }

    const QColor settingTextColor() const;
    void setSettingTextColor(const QColor &newTextcolor);

    const QColor settingOutlineColor() const;
    void setSettingOutlineColor(const QColor &newOutlinecolor);

    const QColor settingBackgroundColor() const;
    void setSettingBackgroundColor(const QColor &newBackgroundcolor);

    bool settingBold() const;
    void setSettingBold(bool newBold);

    bool settingItalic() const;
    void setSettingItalic(bool newItalic);

    const QString settingFontName() const;
    void setSettingFontName(const QString &newFontName);

    bool settingShowPrimitiveOperations() const;
    void setSettingShowPrimitiveOperations(bool newShowPrimitiveOperations);

    bool settingShowComplexOperations() const;
    void setSettingShowComplexOperations(bool newShowComplexOperations);

public slots:
    double runFunc(QString name, double a = 0, double b = 1);

    double convert(QString text, double defaultV = 1);

    double runFormula(QString formula);

    void setA(double a);
    void setB(double b);

    void toggleAnsForPrimitive() { m_useAnsForPrimitive ^= 1; emit ansForPrimitiveChanged(); }

    void restoreDefaultSettings();

    QString generateConfirmText() { return "lol"; }

signals:
    void ansForPrimitiveChanged();

    void settingTextColorChanged();

    void settingOutlineColorChanged();

    void settingBackgroundColorChanged();

    void settingBoldChanged();

    void settingFontNameChanged();

    void settingItalicChanged();

    void settingShowPrimitiveOperationsChanged();

    void settingShowComplexOperationsChanged();

private:
    QMap<QString, QPair<double(*)(double, double), int>> m_functions;
    QMap<QString, QString> m_functionNames;

    double m_a = 0;
    double m_b = 1;
    double m_ans = 0;

    double parseArgument(QString arg);
    int argumentAmt(QString func);
    double internRunFunc(QString internName, double a, double b);
    bool m_useAnsForPrimitive = 0;

    QSettings *m_settings;
};

namespace CalculatorFunctions
{

using T = double;

T root(T a, T b);
T sqrt(T a, T b);
T pow(T a, T b);
T mult(T a, T b);
T div(T a, T b);
T add(T a, T b);
T sub(T a, T b);

T random(T min, T max);

T _or(T a, T b);
T _xor(T a, T b);
T _nor(T a, T b);
T _xnor(T a, T b);
T _and(T a, T b);
T _nand(T a, T b);
T _not(T a, T b);

} // namespace CalculatorFunctions

namespace CalcFunc = CalculatorFunctions;

#endif // BACKEND_H
