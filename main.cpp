#include <iostream>
#include <limits>
#include <iomanip>
#include <string>

#include <QCoreApplication>
#include <QString>

#include "MathExpressionHandler/MathExpHandler.hpp"

void helper();
void tests();
bool test(QString formula, double expect);

int main(int argc, char *argv[])
{
    std::setlocale(0, NULL);
    helper();
    tests();

    std::string expression;
    MathExpHandler handler;
    bool isExit = false;
    char choose = 'y';

    while(!isExit)
    {
        expression.clear();

        std::cout << "Please, enter math expression: ";
        std::getline(std::cin, expression);

        if(expression.empty()) { std::cout << "\nError: empty expression" << std::endl; break; }
        handler.setFormatString(QString::fromStdString(expression));
        handler.processing();
        std::cout << std::setprecision(3) << std::fixed;
        std::cout << "Result: " << handler.getFinally() << std::endl;

        std::cout << "Repeat? (y/n) "; std::cin >> choose;
        isExit = choose == 'y' ? isExit : true;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return 0;
}

//использую свой тест, потому что лень маятся с тестами от гтестами
void tests()
{
    std::cout << "~~~~~~~~~~~ TESTS START ~~~~~~~~~~~" << std::endl;

    int iJustif = 0,
        iTest = 0;

    iJustif += test("2 + 2", 4); ++iTest;

    iJustif += test("(5-7)/2", -1); ++iTest;

    iJustif += test("10/3", 3.333); ++iTest;

    iJustif += test("~1.1111+(10-2)/3", 1.555); ++iTest;

    iJustif += test("2*((11+1)/(9-3))", 4); ++iTest;

    iJustif += test("2*[(11+1)/(9-3)]", 4); ++iTest;

    std::cout << "~~~~~~~~~~~ TESTS END ~~~~~~~~~~~" << std::endl;
    std::cout << "Percent true expessions: " << iJustif * 100 / (iTest) << "%\n" << std::endl;

}

bool test(QString formula, double expect)
{
    auto is_equal = [](double x, double y) -> bool {
        return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
    };

    MathExpHandler testHandler;
    std::string isOk = " ...is OK";
    std::string isBad = " ...is BAD";
    bool justif = false;

    testHandler.setFormatString(formula);
    testHandler.processing();
    justif = is_equal(testHandler.getFinally(), expect);
    isBad += " | Diff = " + std::to_string(testHandler.getFinally() - expect);
    std::cout << std::setprecision(3) << std::fixed;
    std::cout << testHandler.formatString().toStdString() << " = " << testHandler.getFinally()
              << (justif ? isOk : isBad) << std::endl;

    return justif;
}

void helper()
{
    char showListOpt = 'n';
    std::cout << "CREATED BY ILYA SERGIN\n"
                 "Если вы хотите использовать математические функции, то необходим\n"
                 "их специальный вызов, который выглядит следующим образом: \n"
                 "$function #arg, если вместо #arg у вас стоит математическое \n"
                 "выражение, то его следует обрамлять скобками, пример: \n"
                 "1. $sqrt 256 (если аргумент не подвыражение) \n"
                 "1. $sqrt(256) \n"
                 "2. $sqrt(10 * 256)\n"
                 "Для ввода отриц. значений, вместо знака минус необходимо ставить знак ~ (тильда)\n"
                 "Показать полный список операций? (y/n) ";
                 std::cin >> showListOpt; std::cout << std::endl;

                 std::cin.clear();
                 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if(showListOpt != 'y') return;

    std::cout << "Для вызова мат. функций необходимо перед названием поставить знак $!\n"
                 "Полный список операций для математических выражений: \n"
                 "1.  sqrt ~ квадратный корень\n"
                 "2.  abs ~ абсолютное значение\n"
                 "3.  sin ~ синус\n"
                 "4.  arcsin ~ арксинус\n"
                 "5.  cos ~ косинус\n"
                 "6.  arccos ~ арккосинус\n"
                 "7.  log ~ логарифм\n"
                 "8.  dlog ~ десятичный логарифм\n"
                 "9.  exp ~ вычисление экспоненты\n"
                 "10. ceil ~ округление до наибольшего\n"
                 "11. floor ~ округление до наименьшего\n" << std::endl;
}
