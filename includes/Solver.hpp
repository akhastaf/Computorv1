#ifndef SOLVER_HPP
# define SOLVER_HPP

#include <map>
#include <iostream>

namespace ft {
    class Solver
    {
    private:
        std::map<int, double> coefficients;
        double a;
        double b;
        double c;
        int degree;
    public:
        Solver(std::map<int, double> coefficients) : coefficients(coefficients) {
            std::map<int, double>::iterator ait = coefficients.find(2);
            std::map<int, double>::iterator bit = coefficients.find(1);
            std::map<int, double>::iterator cit = coefficients.find(0);

            a = ait == coefficients.end() ? 0 : ait->second;
            b = bit == coefficients.end() ? 0 : bit->second;
            c = cit == coefficients.end() ? 0 : cit->second;

            std::map<int, double>::const_reverse_iterator last = coefficients.rbegin();
            degree = last->first;
        }

        ~Solver() {}

        void printDegree() {
            std::cout << "Polynomial degree: " << degree << std::endl;
        }

        void printReducedForm() {
            std::map<int, double>::const_iterator it = coefficients.begin();
            bool isFirst = true;
            
            if (coefficients.empty())
                return;

            std::cout << "Reduced form: ";
            
            for (; it != coefficients.end(); ++it)
            {
                if (isFirst)
                {
                    if (it->second < 0)
                        std::cout << "- ";
                    isFirst = false;
                }
                else
                    std::cout << (it->second < 0 ? " - " : " + ");

                double absCoeff = fabs(it->second);
                std::cout << absCoeff;

                if (it->first >= 0)
                {
                    std::cout << " * X";
                    std::cout << "^" << it->first;
                }
            }
            std::cout << " = 0" << std::endl;
        }

        void solve() {
            if (degree > 2) {
                std::cout << "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
                return;
            }
            if (a == 0) {
                if (b == 0) {
                    if (c == 0) {
                        std::cout << "All real numbers are solutions !" << std::endl;
                    } else {
                        std::cout << "No solution !" << std::endl;
                    }
                } else {
                    std::cout << "The solution is:" << std::endl;
                    std::cout << (-c / b) << std::endl;
                }
                return;
            }
            double delta = ((b * b) - (4 * a * c));
            if (delta == 0) {
                std::cout << "The solution is:" << std::endl;
                std::cout << (-b / (2 * a)) << std::endl;
            } else if (delta > 0) {
                std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
                std::cout << ((-b - std::sqrt(delta)) / (2 * a)) << std::endl;
                std::cout << ((-b + std::sqrt(delta)) / (2 * a)) << std::endl;
            } else {
                double realPart = (b * -1) / (2 * a);
                double imaginaryPart = std::sqrt(-delta) / (2 * a);
                std::cout << "Discriminant is strictly negative, the two complex solutions are:" << std::endl;
                std::cout << realPart <<  " + " << imaginaryPart << " * i" << std::endl;
            }
        }
    };
}

#endif