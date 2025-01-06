#include "./includes/Parser.hpp"
#include "./includes/Solver.hpp"



int main(int argc, char *argv[]) {
    try {
        if (argc != 2)
            throw ("Invalid number of arguments");
        
        ft::Parser parser = ft::Parser(argv[1]);
        ft::Solver solver(parser.parsing());

        solver.printReducedForm();
        solver.printDegree();
        solver.solve();
    }
    catch(const std::string e) {
        std::cerr << e << std::endl;
        return 1;
    }
}