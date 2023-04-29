#include "backend.h"
#include "settings.h"

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

    m_settings = new Settings(this);
}

namespace
{

QRandomGenerator *const rng = QRandomGenerator::global();

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

QString Backend::generateConfirmText()
{
    int len = rng->bounded(5, 10);
    QString conf = "";
    for(int i = 0; i < len; ++i) {
        bool upper = rng->bounded(2) - 1;
        if(upper)
            conf.append(QChar(rng->bounded('a', 'z')));
        else
            conf.append(QChar(rng->bounded('A', 'Z')));
    }
    return conf;
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

