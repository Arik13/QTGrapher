#include "mainwindow.h"
#include <iostream>
#include <QApplication>
#include <function.h>
#include "parser.h"
#include "glm/glm.hpp"

int main(int argc, char *argv[]) {
    std::string es = "(a*b-b*d)/(b*c-a*d)";
    std::string fs = "(b*c-d*d)/(b*c-a*d)";
    std::string gs = "(a*a-b*c)/(a*d-b*c)";
    std::string hs = "(a*c-c*d)/(a*d-b*c)";
    Function* e = parseFunction(es);
    Function* f = parseFunction(fs);
    Function* g = parseFunction(gs);
    Function* h = parseFunction(hs);
    char vars[] = {'a', 'b', 'c', 'd'};
    float vals[] = {23, 1, 0, -9};
    glm::mat2x2 m(vals[0], vals[1], vals[2], vals[3]);
    glm::mat2x2 mrotate(
                    e->evaluate(vars, vals, 4),
                    f->evaluate(vars, vals, 4),
                    g->evaluate(vars, vals, 4),
                    h->evaluate(vars, vals, 4)
                );
    glm::mat2x2 mccrotate = mrotate * m;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            std::cout << m[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << " * " << std::endl;
    for (int i = 0; i < mrotate.length(); i++) {
        for (int j = 0; j < mrotate[0].length(); j++) {
            std::cout << mrotate[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << " = " << std::endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            std::cout << mccrotate[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    //return a.exec();
}
