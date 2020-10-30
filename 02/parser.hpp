#pragma once

#include <iostream>
#include <sstream>
#include <functional>
#include <algorithm>
#include <vector>

class TokenParser
{
    std::string text;
    std::vector<std::string> tokens;

    using StartEndCallback = std::function<void()>;
    using DigitTokenCallback = std::function<void(int token)>;
    using StringTokenCallback = std::function<void(const std::string& token)>;

    StartEndCallback start_callback, end_callback;
    DigitTokenCallback digit_callback;
    StringTokenCallback string_callback;

    bool IsDigitToken(const std::string& token) const;
    void TokenizeInput();

public:
    explicit TokenParser(const std::string& input_text);
    ~TokenParser();

    void SetStartCallback(const StartEndCallback& callback);
    void SetEndCallback(const StartEndCallback& callback);
    void SetDigitTokenCallback(const DigitTokenCallback& callback);
    void SetStringTokenCallback(const StringTokenCallback& callback);

    const std::vector<std::string>& GetTokens() const;
    void Parse();
};
