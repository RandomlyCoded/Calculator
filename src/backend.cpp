#include "backend.h"

#include <QDebug>
#include <QFile>
#include <QRandomGenerator>
#include <QSettings>

#define NAME_A(f) {QString(#f) + "(a)", #f}
#define NAME(f) {QString(#f) + "(a, b)", #f}

Backend::Backend(QObject *parent)
    : QObject{parent}
{
    m_functions = {
        {"sqrt", {CalcFunc::sqrt,  1}},
        {"root", {CalcFunc::root,  2}},
        {"pow",  {CalcFunc::pow,   2}},
        {"mult", {CalcFunc::mult,  2}},
        {"div",  {CalcFunc::div,   2}},
        {"add",  {CalcFunc::add,   2}},
        {"sub",  {CalcFunc::sub,   2}},

        {"rng",  {CalcFunc::random,2}},
        {"random",{CalcFunc::random, 2}},

        {"or",   {CalcFunc::_or,   2}},
        {"nor",  {CalcFunc::_nor,  2}},
        {"xor",  {CalcFunc::_xor,  2}},
        {"xnor", {CalcFunc::_xnor, 2}},
        {"and",  {CalcFunc::_and,  2}},
        {"nand", {CalcFunc::_nand, 2}},
        {"not",  {CalcFunc::_not,  1}},
    };

    m_functionNames = {
        NAME_A(sqrt),
        NAME  (root),
        NAME  (pow),
        NAME  (mult),
        NAME  (div),
        NAME  (add),
        NAME  (sub),

        {"random(min, max)", "rng"},

        NAME  (or),
        NAME  (nor),
        NAME  (xor),
        NAME  (xnor),
        NAME  (and),
        NAME  (nand),
        NAME_A(not),
    };

    m_settings = new QSettings("settings.ini", QSettings::IniFormat, this);
    if(Q_UNLIKELY(m_settings->value("color/text", "existance").toString() == "existance"))
        restoreDefaultSettings();
}



Backend::~Backend()
{
}

 /********************************************
 * Settings functions                        *
 ********************************************/

const QColor Backend::settingTextColor() const
{
    return m_settings->value("color/text").value<QColor>();
}

void Backend::setSettingTextColor(const QColor &newTextcolor)
{
    m_settings->setValue("color/text", newTextcolor);
    emit settingTextColorChanged();
}

const QColor Backend::settingOutlineColor() const
{
    return m_settings->value("color/outline").value<QColor>();
}

void Backend::setSettingOutlineColor(const QColor &newOutlinecolor)
{
    m_settings->setValue("color/outline", newOutlinecolor);
    emit settingOutlineColorChanged();
}

const QColor Backend::settingBackgroundColor() const
{
    return m_settings->value("color/background").value<QColor>();
}

void Backend::setSettingBackgroundColor(const QColor &newBackgroundcolor)
{
    m_settings->setValue("color/background", newBackgroundcolor);
    emit settingBackgroundColorChanged();
}

bool Backend::settingBold() const
{
    return m_settings->value("font/bold").toBool();
}

void Backend::setSettingBold(bool newBold)
{
    m_settings->setValue("font/bold", newBold);
    emit settingBoldChanged();
}

bool Backend::settingItalic() const
{
    return m_settings->value("font/italic").toBool();
}

void Backend::setSettingItalic(bool newItalic)
{
    m_settings->setValue("font/italic", newItalic);
    emit settingItalicChanged();
}

const QString Backend::settingFontName() const
{
    return m_settings->value("font/name").toString();
}

void Backend::setSettingFontName(const QString &newFontName)
{
    m_settings->setValue("font/name", newFontName);
    emit settingFontNameChanged();
}

bool Backend::settingShowPrimitiveOperations() const
{
    return m_settings->value("display/primitive").toBool();
}

void Backend::setSettingShowPrimitiveOperations(bool newShowPrimitiveOperations)
{
    m_settings->setValue("display/primitive", newShowPrimitiveOperations);
    emit settingShowPrimitiveOperationsChanged();
}

bool Backend::settingShowComplexOperations() const
{
    return m_settings->value("display/complex").toBool();
}

void Backend::setSettingShowComplexOperations(bool newShowComplexOperations)
{
    m_settings->setValue("display/complex", newShowComplexOperations);
    emit settingShowComplexOperationsChanged();
}

void Backend::restoreDefaultSettings()
{
    setSettingTextColor({0, 0, 0});
    setSettingBackgroundColor({255, 255, 255});
    setSettingOutlineColor({0x2d, 0x2d, 0x2d});

    setSettingBold(false);
    setSettingItalic(false);
    setSettingFontName("Source Code Pro");

    setSettingShowComplexOperations(true);
    setSettingShowPrimitiveOperations(true);
}

 /****************************************************
 * all these random functions used by the calculator *
 ****************************************************/

namespace CalculatorFunctions
{

T random(T min, T max)
{
    return QRandomGenerator::global()->generateDouble() * (max - min) + min;
}

T root(T a, T b)
{
    return pow(a, 1/b);
}

T sqrt(T a, T b)
{
    using std::sqrt;
    return sqrt(a);
}

T pow(T a, T b)
{
    using std::pow;
    return pow(a, b);
}

T mult(T a, T b)
{
    return a * b;
}

T div(T a, T b)
{
    return a/b;
}

T add(T a, T b)
{
    return a + b;
}

T sub(T a, T b)
{
    return a - b;
}

// bit functions
T _or(T a, T b)
{
    int res = (*(int*)&a | *(int*)&b);
    return *(double*)&res;
}

T _xor(T a, T b)
{
    int res = (*(int*)&a ^ *(int*)&b);
    return *(double*)&res;
}

T _nor(T a, T b)
{
    int res = ~(*(int*)&a | *(int*)&b);
    return *(double*)&res;
}

T _xnor(T a, T b)
{
    int res = ~(*(int*)&a ^ *(int*)&b);
    return *(double*)&res;
}

T _and(T a, T b)
{
    int res = (*(int*)&a & *(int*)&b);
    return *(double*)&res;
}

T _nand(T a, T b)
{
    int res = ~(*(int*)&a & *(int*)&b);
    return *(double*)&res;
}

T _not(T a, T b)
{
    int res = ~(*(int*)&a);
    return *(double*)&res;
}

} // namespace CalculatorFunctions

namespace
{

inline double fakeFunc(double, double) { return -1; }

} // namespace

double Backend::runFunc(QString name, double a, double b)
{
    QString internName = m_functionNames.value(name, "-invalid-");
    if(internName == "-invalid-") {
        qWarning() << "invalid function" << name;
        return qQNaN();
    }
    double result = internRunFunc(internName, a, b);
    if(m_useAnsForPrimitive)
        m_ans = result;

    return result;
}

double Backend::convert(QString text, double defaultV)
{
    bool success = true;
    double data = text.toDouble(&success);
    if(!success)
        return defaultV;

    if(qIsNaN(data))
        return defaultV;

    return data;
}

double Backend::runFormula(QString formula)
{
    formula.remove(" ");
    formula.remove("\n");
    formula.remove("\t");
    formula.remove(";");
    qInfo() << "parsing" << formula;
    return parseArgument(formula);
}

void Backend::setA(double a)
{
    m_a = a;
    qInfo() << "a is now" << a;
}

void Backend::setB(double b)
{
    m_b = b;
    qInfo() << "b is now" << b;
}

double Backend::parseArgument(QString arg)
{
    QString firstData;
    int idx = 0;
    for(auto c: arg) {
        if(c == '(' || c == ',')
            break;
        firstData += c;
        ++idx;
    }

    bool isNumber;
    double maybeNumber = firstData.toDouble(&isNumber);
    if(isNumber)
        return maybeNumber;

    if(firstData.toLower() == "a")
        return m_a;
    if(firstData.toLower() == "b")
        return m_b;
    if(firstData.toLower() == "ans")
        return m_ans;

    QString func = firstData;

    arg.remove(0, idx);

    if(arg.isEmpty())
        return qQNaN();

    arg.remove(0, arg.indexOf('(') + 1);
    int endParenthesis = arg.lastIndexOf(')');
    if(endParenthesis == -1)
        return qQNaN();
    arg.remove(endParenthesis, 1);

    QString _argA;

    int childIdx = 0;
    for(auto c: arg) {
        if(c == '(')
            ++childIdx;
        if(c == ')')
            --childIdx;
        if(childIdx == 0 && c == ',')
            break;
        _argA += c;
    }

    arg.remove(0, _argA.length() + 1);
    QString _argB = arg;

    qInfo() << func << _argA << _argB;

    double argA = parseArgument(_argA);
    double argB = parseArgument(_argB);

    if(qIsNaN(argA) || qIsNaN(argB))
        return qQNaN();

    return internRunFunc(func.toLower(), argA, argB);
}

int Backend::argumentAmt(QString func)
{
    return m_functions[func].second;
}

double Backend::internRunFunc(QString internName, double a, double b)
{
    auto func = m_functions.value(internName, {fakeFunc, -1});

    double ret = qQNaN();
    if(Q_LIKELY(func.second > 0))
        ret = func.first(a, b);

    else
        qWarning() << "!!! unknown function name" << internName;

    return ret;
}
