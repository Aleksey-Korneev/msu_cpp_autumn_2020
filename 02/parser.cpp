#include "parser.hpp"

bool TokenParser::IsDigitToken(const std::string& token) const
{
    return std::all_of(token.begin(), token.end(), isdigit);
}

void TokenParser::TokenizeInput()
{
    const std::string delimiters = " \t\n";
    size_t start = text.find_first_not_of(delimiters);
    size_t end = text.find_first_of(delimiters, start);
    while(end != std::string::npos) {
        tokens.push_back(text.substr(start, end - start));
        start = text.find_first_not_of(delimiters, end);
        end = text.find_first_of(delimiters, start);
    }
    if (text.length() > start) {
        tokens.push_back(text.substr(start, text.length() - start));
    }
}

TokenParser::TokenParser(const std::string& input_text) :
        text(input_text),
        tokens({}),
        start_callback([]{}),
        end_callback([]{}),
        digit_callback([](int){}),
        string_callback([](const std::string&){})
{
}

TokenParser::~TokenParser()
{
}

void TokenParser::SetStartCallback(const StartEndCallback& callback)
{
    start_callback = callback;
}

void TokenParser::SetEndCallback(const StartEndCallback& callback)
{
    end_callback = callback;
}

void TokenParser::SetDigitTokenCallback(const DigitTokenCallback& callback)
{
    digit_callback = callback;
}

void TokenParser::SetStringTokenCallback(const StringTokenCallback& callback)
{
    string_callback = callback;
}

void TokenParser::Parse()
{
    start_callback();

    TokenizeInput();
    for (const std::string& token : tokens) {
        if (IsDigitToken(token)) { 
            digit_callback(std::stoi(token));
        } else {
            string_callback(token);
        }
    }

    end_callback();
}

const std::vector<std::string>& TokenParser::GetTokens() const
{
    return tokens;
}
