#pragma once

#include <cstdarg>
#include <cstring>
#include <memory>
#include <vector>
#include <string>
#include <functional>
#include <type_traits>
#include <utility>


namespace Colors
{
    struct AnsiColor
    {
        // ---- COLORS ----
        //          foreground background
        // black        30         40
        // red          31         41
        // green        32         42
        // yellow       33         43
        // blue         34         44
        // magenta      35         45
        // cyan         36         46
        // white        37         47
        enum Color
        {
            BLACK   = '0',
            RED     = '1',
            GREEN   = '2',
            YELLOW  = '3',
            BLUE    = '4',
            MAGENTA = '5',
            CYAN    = '6',
            WHITE   = '7'
        };

        // ---- MODIFIERS ----
        // reset             0  (everything back to normal)
        // bold/bright       1  (often a brighter shade of the same colour)
        // underline         4
        // inverse           7  (swap foreground and background colours)
        // bold/bright off  21
        // underline off    24
        // inverse off      27
        enum Modifier {
            NO_MODIFIER = '0',
            BOLD        = '1',
            UNDERLINE   = '4',
            INVERSE     = '7'
        };

        char data[8];

        explicit AnsiColor(const Color foreground, const Color background = BLACK, const Modifier modifier = NO_MODIFIER)
        {
            data[0] = '\033';
            data[1] = '[';
            data[2] = modifier;
            data[3] = ';';
            data[4] = '3';
            data[5] = foreground;
            data[6] = 'm';
            data[7] = '\0';
        }

        explicit AnsiColor(const char data[8])     { std::copy_n(data,       8, this->data); }
        explicit AnsiColor(const AnsiColor& color) { std::copy_n(color.data, 8, this->data); }

        AnsiColor& operator= (const char data[8])     { std::copy_n(data,       8, this->data); return *this; }
        AnsiColor& operator= (const AnsiColor& color) { std::copy_n(color.data, 8, this->data); return *this; }
    };


    const AnsiColor RED         ("\033[0;31m");
    const AnsiColor BOLD_RED    ("\033[1;31m");
    const AnsiColor BLUE        ("\033[0;34m");
    const AnsiColor BOLD_BLUE   ("\033[1;34m");
    const AnsiColor CYAN        ("\033[0;36m");
    const AnsiColor BOLD_CYAN   ("\033[1;36m");
    const AnsiColor GREEN       ("\033[0;32m");
    const AnsiColor BOLD_GREEN  ("\033[1;32m");
    const AnsiColor YELLOW      ("\033[0;33m");
    const AnsiColor BOLD_YELLOW ("\033[1;33m");
    const AnsiColor NORMAL      ("\033[0m\0\0\0");
};

using Colors::AnsiColor;

struct OutputColors
{
    AnsiColor failure;
    AnsiColor test;
    AnsiColor check;
    AnsiColor other;

    OutputColors(const AnsiColor& failure, const AnsiColor& test, const AnsiColor& check, const AnsiColor& other)
            : failure(failure), test(test), check(check), other(other) {}
};

static OutputColors default_colors = { Colors::RED, Colors::CYAN, Colors::GREEN, Colors::CYAN };



struct Options
{
    constexpr static unsigned char OUTPUT_NOTHING      = 0b00000000;
    constexpr static unsigned char OUTPUT_FAILURES     = 0b00000001;
    constexpr static unsigned char OUTPUT_TESTS        = 0b00000010;
    constexpr static unsigned char OUTPUT_CHECKS       = 0b00000100;
    constexpr static unsigned char OUTPUT_FINAL_RESULT = 0b00001000;
    constexpr static unsigned char OUTPUT_EVERYTHING   = OUTPUT_FAILURES | OUTPUT_TESTS | OUTPUT_CHECKS | OUTPUT_FINAL_RESULT;

    unsigned char flags = OUTPUT_EVERYTHING;
    FILE* file = stdout;
    OutputColors* color = &default_colors;
};


namespace details
{
    constexpr unsigned MAX_BUFFER_SIZE = 255;

    struct TestCase;
    static std::vector<TestCase*> test_cases;

    struct TestCase
    {
        using TestFunction = std::function<void(Options, const TestCase&, int&, int&)>;

        const char*  name;
        const char*  file;
        const int    line;
        const int    test_number;
        const TestFunction function;

        TestCase(
            const char*  name,
            const char*  file,
            const int    line,
            const int    test_number,
            TestFunction function
        ) noexcept
                : name(name), file(file), line(line), test_number(test_number), function(std::move(function))
        {
            test_cases.push_back(this);
        }
    };

    void Failure(const Options& options, const std::string& statement, const int line, const TestCase& test_info, int checks)
    {
        fprintf(options.file,
                "%s\t[Check %i failed]\n%s"
                "\t\tStatement: %s\n"
                "\t\tFile: %s\n"
                "\t\tLine: %i\n", options.color->failure.data, checks, Colors::NORMAL.data, statement.c_str(), test_info.file, line
        );
    }

    void Success(const Options& options, int checks)
    {
        fprintf(options.file, "%s\t[check %i succeeded]\n%s", options.color->check.data, checks, Colors::NORMAL.data);
    }



    std::string ToString(const char      value)  { return std::to_string(value); }
    std::string ToString(const short     value)  { return std::to_string(value); }
    std::string ToString(const int       value)  { return std::to_string(value); }
    std::string ToString(const long      value)  { return std::to_string(value); }
    std::string ToString(const long long value)  { return std::to_string(value); }

    std::string ToString(const unsigned char      value)  { return std::to_string(value); }
    std::string ToString(const unsigned short     value)  { return std::to_string(value); }
    std::string ToString(const unsigned int       value)  { return std::to_string(value); }
    std::string ToString(const unsigned long      value)  { return std::to_string(value); }
    std::string ToString(const unsigned long long value)  { return std::to_string(value); }

    std::string ToString(const float  value) { return std::to_string(value); }
    std::string ToString(const double value) { return std::to_string(value); }

    std::string ToString(const char*  value) { return std::string(value); }

    template <typename Type>
    std::string ToString(const Type value [[gnu::unused]]) { return "?"; }



    template <typename ... Targs>
    std::string Format(const char* format, const Targs ... args)
    {
        char* statement = new char[MAX_BUFFER_SIZE];
        snprintf(statement, MAX_BUFFER_SIZE, format, ToString(args).c_str()...);

        return { statement };
    }

    std::tuple<int, int> RunTestCase(const details::TestCase& test, const Options& options)
    {
        int checks   = 0;
        int failures = 0;

        if ((options.flags & Options::OUTPUT_TESTS) == Options::OUTPUT_TESTS)
            fprintf(options.file, "%sStarting: %s\n%s", options.color->test.data, test.name, Colors::NORMAL.data);

        test.function(options, test, checks, failures);

        if ((options.flags & Options::OUTPUT_TESTS) == Options::OUTPUT_TESTS)
            fprintf(options.file, "%sCompleted %i out of %i\n%s", options.color->test.data, checks-failures, checks, Colors::NORMAL.data);

        return {checks, failures};
    }
}





// ---- PUBLIC FUNCTIONS/MACROS ----

#define Test(name)                                                                                                      \
void test_##name(Options options, const details::TestCase& __test_info, int& __checks, int& __failures);                \
details::TestCase test_info_##name(#name, __FILE__, __LINE__, __COUNTER__, test_##name);  /* NOLINT(cert-err58-cpp) */  \
void test_##name(                                                                                                       \
        [[gnu::unused]] Options options,                                                                                \
        [[gnu::unused]] const details::TestCase& __test_info,                                                           \
        [[gnu::unused]] int& __checks,                                                                                  \
        [[gnu::unused]] int& __failures                                                                                 \
)


#define Check(a, comparison, b)                                                                                         \
{                                                                                                                       \
    const auto value_a = a;  /* Must copy for rvalues of non pure function calls. */                                    \
    const auto value_b = b;  /* Must copy for rvalues of non pure function calls. */                                    \
                                                                                                                        \
    bool status = value_a comparison value_b;                                                                           \
                                                                                                                        \
    __checks   += 1;                                                                                                    \
    __failures += !status;                                                                                              \
                                                                                                                        \
    if ((options.flags & Options::OUTPUT_CHECKS) == Options::OUTPUT_CHECKS)                                             \
    {                                                                                                                   \
        if (status)                                                                                                     \
            details::Success(options, __checks);                                                                        \
        else                                                                                                            \
            details::Failure(options,                                                                                   \
                details::Format("%s " #comparison " %s \t (%s " #comparison " %s)", #a, #b, value_a, value_b),          \
                __LINE__, __test_info, __checks                                                                         \
                );                                                                                                      \
    }                                                                                                                   \
    else if ((options.flags & Options::OUTPUT_FAILURES) == Options::OUTPUT_FAILURES && !status)                         \
    {                                                                                                                   \
        details::Failure(options,                                                                                       \
            details::Format("%s " #comparison " %s \t (%s " #comparison " %s)", #a, #b, value_a, value_b),              \
            __LINE__, __test_info, __checks                                                                             \
        );                                                                                                              \
    }                                                                                                                   \
}


#define RunTest(name) details::RunTestCase(test_info_##name)
void RunAllTests(const Options& options = {})
{
    int checks   = 0;
    int failures = 0;

    int tests_run   = 0;
    int failed_test = 0;

    for (details::TestCase* test_case : details::test_cases)
    {
        auto result = details::RunTestCase(*test_case, options);
        checks   += std::get<0>(result);
        failures += std::get<1>(result);

        tests_run += 1;
        failed_test += failures > 0 ? 1 : 0;
    }

    if ((options.flags & Options::OUTPUT_FINAL_RESULT) == Options::OUTPUT_FINAL_RESULT)
        fprintf(
            options.file,
            "%s\nTESTS COMPLETED: Completed %i out of %i tests (%i out of %i checks).\n%s",
            options.color->other.data, tests_run-failed_test, tests_run, checks-failures, checks, Colors::NORMAL.data
        );
}
