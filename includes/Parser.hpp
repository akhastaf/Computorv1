#ifndef PARSER_HPP
#define PARSER_HPP

#include <map>
#include <vector>
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include "Tokenizer.hpp"

namespace ft
{
    class Parser
    {
        private:
            typedef struct token Token;
            Tokenizer _tokenizer;
            Token _lookahead;
            Token _eat(std::string const &token_type) 
            {
                Token t = _lookahead;
                try
                {
                    if (t.type == "NULL")
                        throw ("Unexpected end of input, expected : " + token_type);
                    if (t.type != token_type)
                        throw ("Unexpected token : " + t.type + ", expected : " + token_type);
                    _lookahead = _tokenizer.get_next_token();
                }
                catch (std::string& e)
                {
                    std::cerr << e << std::endl;
                    exit(1);
                }
                return t;
            }
        public:
            Parser(std::string const &text) : _tokenizer(text)
            {
                try
                {
                    _lookahead = _tokenizer.get_next_token();
                }
                catch (std::string& e)
                {
                    std::cerr << e << std::endl;
                    exit(1);
                }
            }
            ~Parser() {};
            std::map<int, double>   parsing() 
            {
                std::map<int, double> coefficients;
                std::pair<int, double> coefficient;
                
                // Parse left side of equation
                do
                {
                    coefficient = TermLeft();
                    std::map<int, double>::iterator it = coefficients.find(coefficient.first);
                    if (it != coefficients.end())
                        it->second += coefficient.second;
                    else
                        coefficients.insert(coefficient);
                } while (_lookahead.type == "NUMBER");

                _eat("=");

                // Parse right side of equation
                do
                {
                    coefficient = TermRight();
                    std::map<int, double>::iterator it = coefficients.find(coefficient.first);
                    if (it != coefficients.end())
                        it->second += coefficient.second;
                    else
                        coefficients.insert(coefficient);
                } while (_lookahead.type == "NUMBER");

                return coefficients;
            }
            std::pair<int, double> TermLeft()
            {
                std::pair<int, double> coefficient;
                try 
                {
                    coefficient.second = Coefficients();
                    if (_lookahead.type != "*") {
                        coefficient.first = 0;
                    } else {
                        _eat("*");
                        _eat("X");
                        _eat("^");
                        coefficient.first = Power();
                    }
                }
                catch (std::string& e)
                {
                    std::cerr << e << std::endl;
                    exit(1);
                }
                return coefficient;
            }
            std::pair<int, double> TermRight()
            {
                std::pair<int, double> coefficient;
                try 
                {
                    coefficient.second = -1 * Coefficients();
                    if (_lookahead.type != "*") {
                        coefficient.first = 0;
                    } else {
                        _eat("*");
                        _eat("X");
                        _eat("^");
                        coefficient.first = Power();
                    }
                }
                catch (std::string& e)
                {
                    std::cerr << e << std::endl;
                    exit(1);
                }
                return coefficient;
            }
            double Coefficients()
            {
                std::string s = _eat("NUMBER").value;
                
                // Remove leading and trailing spaces
                s.erase(0, s.find_first_not_of(" \t\n\r\f\v"));
                s.erase(s.find_last_not_of(" \t\n\r\f\v") + 1);
                
                // Optional: remove spaces in the middle too
                s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
                return std::stod(s);
            }
            int Power() 
            {
                std::string s = _eat("NUMBER").value;
                
                // Remove leading and trailing spaces
                s.erase(0, s.find_first_not_of(" \t\n\r\f\v"));
                s.erase(s.find_last_not_of(" \t\n\r\f\v") + 1);
                
                // Optional: remove spaces in the middle too
                s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
                return std::stoi(s);
            }
    };
}
#endif