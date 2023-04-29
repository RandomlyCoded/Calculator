#ifndef BACKEND_H
#define BACKEND_H

#include <QColor>
#include <QMap>
#include <QObject>

class QFile;
class Settings;

class Backend : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<QString> availableFunctions READ availableFunctions CONSTANT FINAL)

public:
    explicit Backend(QObject *parent = nullptr);

    const QList<QString> availableFunctions() const { return m_functionNames.keys(); }

public slots:
    double runFunc(QString name, double a = 0, double b = 1);

    double convert(QString text, double defaultV = 1);

    double runFormula(QString formula);

    void setA(double a);
    void setB(double b);

    QString generateConfirmText();

    Settings *settings() { return m_settings; }

private:
    QMap<QString, QPair<double(*)(double, double), int>> m_functions;
    QMap<QString, QString> m_functionNames;

    double m_a = 0;
    double m_b = 1;
    double m_ans = 0;

    double parseArgument(QString arg);
    int argumentAmt(QString func);
    double internRunFunc(QString internName, double a, double b);

    Settings *m_settings;
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
