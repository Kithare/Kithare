/*
 * This file is a part of the Kithare programming language source code.
 * The source code for Kithare programming language is distributed under the MIT license.
 * Copyright (C) 2021 Kithare Organization
 */

#include <vector>

#ifdef _WIN32
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <codecvt>
#endif

#include <kithare/file.hpp>
#include <kithare/parser.hpp>
#include <kithare/string.hpp>
#include <kithare/test.hpp>
#include <kithare/utf8.hpp>


static std::vector<std::u32string> args;
static bool help = false, show_tokens = false, show_ast = false, show_timer = false, silent = false,
            test_mode = false;
static std::vector<std::u32string> excess_args;

static void handleArgs() {
    for (std::u32string& _arg : args) {
        std::u32string arg;

        /* Indicates that it is a flag argument (which starts with `-`. `--`, or `/`) */
        if (_arg.size() > 1 && _arg[0] == '-' && _arg[1] == '-')
            arg = std::u32string(_arg.begin() + 2, _arg.end());
        else if (_arg.size() > 0 && (_arg[0] == '-' || _arg[0] == '/'))
            arg = std::u32string(_arg.begin() + 1, _arg.end());
        /* Excess arguments */
        else {
            excess_args.push_back(_arg);
            continue;
        }

        /* Sets the booleans of the specified flags */
        if (arg == U"h" || arg == U"help")
            help = true;
        else if (arg == U"tokens")
            show_tokens = true;
        else if (arg == U"ast")
            show_ast = true;
        else if (arg == U"t" || arg == U"timer")
            show_timer = true;
        else if (arg == U"test")
            test_mode = true;
        else {
            if (!silent)
                std::cout << "Unrecognized flag argument: " << kh::encodeUtf8(arg) << '\n';
            std::exit(1);
        }
    }
}

static int execute() {
    int code = 0;

    if (help && !silent) {
        std::cout << "TODO\n";
    }

    /* Unittest */
    if (test_mode) {
        std::vector<std::u32string> errors;
        kh_test::utf8Test(errors);
        kh_test::lexerTest(errors);
        kh_test::parserTest(errors);
        if (!silent) {
            std::cout << "Unit-test: " << errors.size() << " error(s)\n";
            for (const std::u32string& error : errors)
                std::cout << kh::encodeUtf8(error) << '\n';
        }

        std::exit(errors.size());
    }

    /* Compilation */
    if (!excess_args.empty()) {
        std::u32string source;

        try {
            source = kh::readFile(excess_args[0]);
        }
        catch (kh::Exception& exc) {
            if (!silent)
                std::cerr << kh::encodeUtf8(exc.format()) << '\n';
            std::exit(1);
        }

        kh::Parser parser(source);

        parser.lex();
        if (show_timer && !silent)
            std::cout << "Finished lexing in " << parser.lex_time << "s\n";
        if (!parser.lex_exceptions.empty()) {
            if (!silent)
                for (kh::LexException& exc : parser.lex_exceptions)
                    std::cout << "LexException: " << kh::encodeUtf8(exc.format()) << '\n';
            code += parser.lex_exceptions.size();
        }
        if (show_tokens && !silent) {
            std::cout << "tokens:\n";
            for (kh::Token& token : parser.tokens)
                std::cout << '\t' << kh::encodeUtf8(kh::repr(token)) << '\n';
        }

        parser.parse();
        if (show_timer && !silent)
            std::cout << "Finished parsing in " << parser.parse_time << "s\n";
        if (!parser.parse_exceptions.empty()) {
            if (!silent)
                for (kh::ParseException& exc : parser.parse_exceptions)
                    std::cout << "ParseException: " << kh::encodeUtf8(exc.format()) << '\n';
            code += parser.parse_exceptions.size();
        }
        if (show_ast && !code && parser.ast && !silent)
            std::cout << kh::encodeUtf8(kh::repr(*parser.ast)) << '\n';
    }

    return code;
}

/* Entry point of the Kithare CI program */
#ifdef _WIN32
int wmain(const int argc, wchar_t* argv[])
#else
int main(const int argc, char* argv[])
#endif
{
    /* Sets the locale to using UTF-8 */
    std::setlocale(LC_ALL, "en_US.utf8");
#ifdef _WIN32
    /* Sets up std::wcout and std::wcin on Windows */
    std::locale _utf8_locale(std::locale(), new std::codecvt_utf8_utf16<wchar_t>);
    std::wcout.imbue(_utf8_locale);
    std::wcin.imbue(_utf8_locale);
#endif

    args.reserve(argc - 1);

    /* Ignore the first argument */
    for (int arg = 1; arg < argc; arg++)
#ifdef _WIN32
        args.push_back(kh::repr(std::wstring(argv[arg])));
#else
        args.push_back(kh::decodeUtf8(std::string(argv[arg])));
#endif

    handleArgs();
    return execute();
}