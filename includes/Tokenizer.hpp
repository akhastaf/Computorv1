#ifndef TOLENIZER_HPP
#define TOLENIZER_HPP

#include <map>
#include <vector>
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include<ctype.h>

namespace ft {

    std::string::iterator number_literal(std::string::iterator it, std::string::iterator end)
    {
        if (it != end && (*it == '+' || *it == '-')) {
            ++it;
        }
        while (it != end && isspace(*it))
            it++;
        if (it == end || !std::isdigit(*it))
            return it;
        
        while (it != end && std::isdigit(*it))
            ++it;
        
        if (it != end && *it == '.') {
            ++it;
            if (it == end || !std::isdigit(*it))
                return it;
            
            while (it != end && std::isdigit(*it))
                ++it;
        }
        return it;
    }
    std::string::iterator white_spaces(std::string::iterator it, std::string::iterator end)
    {
        while (it != end && isspace(*it))
            it++;
        return it;
    }
    std::string::iterator multiplication(std::string::iterator it, std::string::iterator end)
    {
        if (it != end && *it == '*')
            it++;
        return it;
    }
    std::string::iterator equal(std::string::iterator it, std::string::iterator end) 
    {
        if (it != end && *it == '=')
            it++;
        return it;
    }
    std::string::iterator power(std::string::iterator it, std::string::iterator end)
    {
        if (it != end && *it == '^')
            it++;
        return it;
    }
    std::string::iterator variable(std::string::iterator it, std::string::iterator end)
    {
        if (it != end && (*it == 'X' || *it == 'x'))
            it++;
        return it;
    }
    
    struct token
    {
        std::string type;
        std::string value;
    };
    class Tokenizer
    {
        private:
            std::string _text;
            std::string::iterator _cursor;
            std::vector<std::pair<std::string, std::string::iterator (*)(std::string::iterator, std::string::iterator)> > _specs;
            bool _has_more_tokens() { return (_cursor != _text.end()); }
        public:
            typedef struct token Token;
            Tokenizer(std::string text) : _text(text), _cursor(_text.begin()) 
            {
                _specs.push_back(std::make_pair("null", white_spaces));
                _specs.push_back(std::make_pair("^", power));
                _specs.push_back(std::make_pair("*", multiplication));
                _specs.push_back(std::make_pair("=", equal));
                _specs.push_back(std::make_pair("X", variable));
                _specs.push_back(std::make_pair("NUMBER", number_literal));
            }
            ~Tokenizer() {}
            Token get_next_token()
            {
                Token t;
                std::string::iterator match;
                if (!_has_more_tokens())
                {
                    t.type = "NULL";
                    return t;
                }
                for (size_t i = 0; i < _specs.size(); i++)
                {
                    match = (_specs[i].second)(_cursor, _text.end());
                    if (match == _cursor)
                        continue;
                    if (_specs[i].first == "null")
                    {
                        _cursor = match;
                        return get_next_token();
                    }
                    t.type = _specs[i].first;
                    t.value = std::string(_cursor, match);
                    _cursor = match;
                    if (t.type == "STRING" && (t.value[0] == '\'' || t.value[0] == '"'))
                        t.value = t.value.substr(1, t.value.length() - 2);
                    return t;
                }
                    throw ("undefinde token " + std::string(_cursor, _cursor + 1));
                return t;
            }
    };  
}

#endif