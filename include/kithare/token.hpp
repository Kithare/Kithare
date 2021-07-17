/*
 * This file is a part of the Kithare programming language source code.
 * The source code for Kithare programming language is distributed under the MIT license.
 * Copyright (C) 2021 Kithare Organization
 */

#pragma once

#include <kithare/string.hpp>


namespace kh {
    struct Token;
    struct TokenValue;
    enum class Operator;
    enum class Symbol;
    enum class TokenType;

    std::u32string strfy(const Token& token, bool show_token_type = false);
    std::u32string strfy(TokenType type);
    std::u32string strfy(Operator op);
    std::u32string strfy(Symbol sym);

    enum class Operator {
        ADD,
        SUB,
        MUL,
        DIV,
        MOD,
        POW,

        IADD,
        ISUB,
        IMUL,
        IDIV,
        IMOD,
        IPOW,

        INCREMENT,
        DECREMENT,

        EQUAL,
        NOT_EQUAL,
        LESS,
        MORE,
        LESS_EQUAL,
        MORE_EQUAL,

        BIT_AND,
        BIT_OR,
        BIT_NOT,
        BIT_LSHIFT,
        BIT_RSHIFT,
        AND,
        OR,
        NOT,

        ASSIGN,
        SIZEOF,
        ADDRESS
    };

    enum class Symbol {
        SEMICOLON,
        DOT,
        COMMA,
        COLON,

        PARENTHESES_OPEN,
        PARENTHESES_CLOSE,
        CURLY_OPEN,
        CURLY_CLOSE,
        SQUARE_OPEN,
        SQUARE_CLOSE
    };

    enum class TokenType {
        IDENTIFIER,
        OPERATOR,
        SYMBOL,
        CHARACTER,
        STRING,
        BUFFER,
        UINTEGER,
        INTEGER,
        FLOATING,
        IMAGINARY
    };

    struct TokenValue {
        union {
            Operator operator_type;
            Symbol symbol_type;

            uint64_t uinteger;
            int64_t integer;
            char32_t character;

            double floating;
            double imaginary;
        };

        std::u32string string;

        std::string identifier;
        std::string buffer;
    };

    struct Token {
        size_t column;
        size_t line;
        size_t index;
        size_t length;
        TokenType type;
        TokenValue value;

        Token();
        Token(size_t _index, size_t _end, TokenType _type, const TokenValue& _value);
    };
}
