#include "test.hpp"
#include "parser.hpp"
#include <cassert>
#include <ctime>

//An empty string
void Test1()
{
    std::cout << __func__ << std::endl;
    TokenParser parser(std::string{});
    parser.Parse();

    const std::vector<std::string> tokens{};
    assert(parser.GetTokens() == tokens);
}

//A string containing both numbers and strings
void Test2()
{
    std::cout << __func__ << std::endl;
    TokenParser parser("        \nText 123 ExtraText 2 af x3vb 009a");
    parser.SetStartCallback([]{ std::cout << "Start parsing" << std::endl; });
    parser.SetEndCallback([]{ std::cout << "End parsing" << std::endl; });
    parser.SetDigitTokenCallback([](int token){
            std::cout << "Found a number: " << token << std::endl; });
    parser.SetStringTokenCallback([](const std::string& token){
            std::cout << "Found a string: " << token << std::endl; });
    parser.Parse();

    const std::vector<std::string> tokens =
            { "Text", "123", "ExtraText", "2", "af", "x3vb", "009a" };
    assert(parser.GetTokens() == tokens);
}

//Only numbers
void Test3()
{
    int errors_cnt = 0;
    std::cout << __func__ << std::endl;
    TokenParser parser("\t\n   0 \t9\n\n 1\t0 9\n\n\t\n9 0002 26\n    \t");
    parser.SetStartCallback([&parser]{
            std::cout << "Object \'parser\' at " << &parser << std::endl; });
    parser.SetDigitTokenCallback([](int){
            static int cnt = 0;
            std::cout << ++cnt << " tokens found so far" << std::endl; });
    parser.SetStringTokenCallback([&errors_cnt](std::string){
            std::cout << "Error! No strings should have been found!"
            << std::endl;
            ++errors_cnt; });
    parser.SetEndCallback([&parser]{
            std::cout << "All in all found "
            << parser.GetTokens().size() << " tokens" << std::endl; });
    parser.Parse();
    const std::vector<std::string> tokens =
            { "0", "9", "1", "0", "9", "9", "0002", "26" };
    assert(parser.GetTokens() == tokens);
    assert(!errors_cnt); //Found a string token
}

//Only strings
void Test4()
{
    int errors_cnt = 0;
    std::cout << __func__ << std::endl;
    TokenParser parser("\t\n \tThis is\nan\toriginal\n\t\\ttext\n\t ! ");
    clock_t time_start = 0;
    parser.SetStartCallback([&time_start]{
            std::cout << "The function's running time will be calculated" << std::endl ;
            time_start = clock(); });
    parser.SetDigitTokenCallback([&errors_cnt](int){
            std::cout << "Error! No numbers should have been found!" << std::endl;
            ++errors_cnt; });
    parser.SetStringTokenCallback([](const std::string& token){
            static std::vector<std::string> strings;
            strings.push_back(token);
            std::cout << "All strings found so far: ";
            for (const std::string& str : strings) {
                std::cout << str << ' ';
            }
            std::cout << std::endl; });
    parser.SetEndCallback([&time_start]{
            std::cout << "Parsing took " << std::fixed <<
            static_cast<double>(clock() - time_start) / CLOCKS_PER_SEC
            << " seconds" << std::endl; });
    parser.Parse();
    const std::vector<std::string> tokens =
            { "This", "is", "an", "original", "\\ttext", "!" };
    assert(parser.GetTokens() == tokens);
    assert(!errors_cnt); //Found a digit token
}

void RunTests()
{
    const std::vector<std::function<void()>> tests =
            { Test1, Test2, Test3, Test4 };
    for (const std::function<void()>& test : tests) {
        test();
        std::cout << std::endl;
    }
}

int main()
{
    RunTests();
    std::cout << "All tests passed." << std::endl;
    return 0;
}
