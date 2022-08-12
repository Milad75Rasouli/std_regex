/*
DESCRIPTION: The ways to parse a text with regex in C++.
 Author: Milad Rasouli
*/
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <memory.h>



class Regex
{
public:

    /* Delete all waste things that compiler likes to make them.
       There are so many ways to do it. It's one of them. */
    Regex() = delete;
    ~Regex() = delete;
    Regex(const Regex&) = delete;
    Regex(Regex&&) = delete;
    Regex& operator= (const Regex&) = delete;
    Regex& operator= (Regex&&) = delete;

    /* Regex methodes */

    /* cregex_iterator(...) */
    static auto regex_identify_1(const char* text, int length,const char* pattern)->
            std::unique_ptr<std::cmatch>
    {
        std::regex rgx{pattern};
        auto group_being = std::cregex_iterator(text, (text + length), rgx);
        auto group_end = std::cregex_iterator();
        if (std::distance(group_being,group_end) <= 0)
            return nullptr;
        return std::move(std::make_unique<std::cmatch>(std::move(*group_being)));
    }
    
    /* sregex_iterator(...) */
    static auto regex_identify_2(const std::string& text,
        const std::string& pattern)->std::unique_ptr<std::smatch> {

        std::regex rgx{ pattern };
        auto group_being = std::sregex_iterator(text.cbegin(), text.cend(), rgx);
        auto group_end = std::sregex_iterator();
        if (std::distance(group_being, group_end) <= 0)
            return nullptr;

        return std::move(std::make_unique<std::smatch>(std::move(*group_being)));
    }

    /* std::regex_match(...) */
    static auto regex_identify_3(const std::string& text,
        const std::string& pattern)->std::unique_ptr<std::smatch> {

        std::regex rgx{ pattern };
        std::smatch result{};
        if (std::regex_match(text, result, rgx))
        {
            return std::move(std::make_unique<std::smatch>(result));
        }
        return nullptr;
    }

    /* std::regex_search(...) */
    static auto regex_identify_4(const std::string& text,
        const std::string& pattern)->std::unique_ptr<std::smatch> {

        std::regex rgx{ pattern };
        std::smatch result{};
        if (std::regex_search(text, result, rgx))
        {
            return std::move(std::make_unique<std::smatch>(result));
        }
        return nullptr;
    }

    /* std::regex_replace(...) */
    static auto regex_replace(const std::string& text,
        const std::string& pattern,const std::string& rplc)->std::unique_ptr<std::string> {
        try {
            std::regex rgx{ pattern };
            auto result = std::regex_replace(text, rgx, rplc);
            return std::move(std::make_unique<std::string>(std::move(result)));
        }
        catch (const std::regex_error& e) {
            throw e.what();
        }
    }

};


int main() {

    /* ===== Method 1 ===== */
    std::cout << "Method 1\n";
    /* Here, our subject is what is among the '[' and ']'. Which is IP.*/
    char text_1[]{ "Here we have an IP: >>>[192.168.1.41]<<<" };
    /* Before parsing, you must know what is the format of the text. */
    char pattern_1[]{R"(\[(\d+)\.(\d+).(\d+).(\d+)\])" };
    /* To obtain size of the text */
    auto size_ = strlen(text_1);
    auto&& result_1 = Regex::regex_identify_1(text_1, size_, pattern_1);
    if (result_1 != nullptr)
    {
        /* show datas in console */
        //std::cout << result_1->str(1) << "\n"; // You can also use this to show
        std::copy(result_1->begin(), result_1->end(), std::ostream_iterator<std::string>(std::cout, "   "));
    }


    /* ===== Method 2 ===== */
    std::cout << "\nMethod 2\n";
    /* Here, our subject is what is among the '[' and ']'. Which is IP.*/
    std::string text_2{ "Here we have an IP: >>>[192.168.1.11]<<<" };
    /* Before parsing, you must know what is the format of the text. */
    std::string pattern_2{ R"(\[(\d+)\.(\d+).(\d+).(\d+)\])" };

    auto&& result_2 = Regex::regex_identify_2(text_2, pattern_2);
    if (result_2 != nullptr)
    {
        /* show datas in console */
        //std::cout << result_2->str(1) << "\n"; // You can also use this to show
        std::copy(result_2->begin(), result_2->end(), std::ostream_iterator<std::string>(std::cout, "   "));
    }


    /* ===== Method 3 =====*/
    std::cout << "\nMethod 3\n";
    /* Here, our subject is what is among the '[' and ']'. Which is IP.*/
    /* NOTICE:
       For this case , there is an exception. the regex_match() cannt recognize complex text like
       this: 'Here we have an IP: >>>[192.168.1.31]<<<' even this one: '-[192.168.1.11]-' */
    std::string text_3{ "[192.168.1.31]" };
    /* Before parsing, you must know what is the format of the text. */
    std::string pattern_3{ R"(\[(\d+)\.(\d+).(\d+).(\d+)\])" };
    auto&& result_3 = Regex::regex_identify_3(text_3, pattern_3);
    if (result_3 != nullptr)
    {
        /* show datas in console */
        //std::cout << result_3->str(1) << "\n"; // You can also use this to show
        std::copy(result_3->begin(), result_3->end(), std::ostream_iterator<std::string>(std::cout, "   "));
    }

    /* ===== Method 4 =====*/
    std::cout << "\nMethod 4\n";
    /* Here, our subject is what is among the '[' and ']'. Which is IP.*/
    std::string text_4{ "[192.168.1.101]" };
    /* Before parsing, you must know what is the format of the text. */
    std::string pattern_4{ R"(\[(\d+)\.(\d+).(\d+).(\d+)\])" };
    auto&& result_4 = Regex::regex_identify_4(text_4, pattern_4);
    if (result_4 != nullptr)
    {
        /* show datas in console */
        //std::cout << result_4->str(1) << "\n"; // You can also use this to show
        std::copy(result_4->begin(), result_4->end(), std::ostream_iterator<std::string>(std::cout, "   "));
    }


    /* ===== Replace =====*/
    std::cout << "\nReplace\n";
    /* Here, our subject is what is among the '[' and ']'. Which is IP.*/
    /* NOTICE:
       For this case , there is an exception. the regex_match() cannt recognize complex text like
       this: 'Here we have an IP: >>>[192.168.1.11]<<<' even this one: '>[192.168.1.11]<' */
    std::string text_r{ "Here we have an IP: >>>[192.168.1.11]<<<" };
    /* Before parsing, you must know what is the format of the text. */
    std::string pattern_r{ R"(\w+\s)" };
    auto&& result_r = Regex::regex_replace(text_r, pattern_r, "[$&]");
    std::cout << *result_r;



    return EXIT_SUCCESS;
}

