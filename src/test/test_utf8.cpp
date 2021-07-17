/*
 * This file is a part of the Kithare programming language source code.
 * The source code for Kithare programming language is distributed under the MIT license.
 * Copyright (C) 2021 Kithare Organization
 */

#include <kithare/test.hpp>
#include <kithare/utf8.hpp>


using namespace kh;

#define KH_TEST_U32STRING U"\x42\x63\xf6\xf3\u4242\u6363\U00010000"
#define KH_TEST_U8STRING "\x42\x63\xc3\xb6\xc3\xb3\xe4\x89\x82\xe6\x8d\xa3\xf0\x90\x80\x80"

static std::vector<std::string>* errors_ptr;

static void utf8EncodeTest() {
    try {
        KH_TEST_ASSERT(encodeUtf8(KH_TEST_U32STRING) == KH_TEST_U8STRING);
    }
    catch (...) {
        errors_ptr->push_back("An exception was thrown in ");
        goto error;
    }

    return;
error:
    errors_ptr->back() += "utf8EncodeTest";
}

static void utf8DecodeTest() {
    try {
        KH_TEST_ASSERT(decodeUtf8(KH_TEST_U8STRING) == KH_TEST_U32STRING);
    }
    catch (...) {
        errors_ptr->push_back("An exception was thrown in ");
        goto error;
    }

    return;
error:
    errors_ptr->back() += "utf8DecodeTest";
}

void kh_test::utf8Test(std::vector<std::string>& errors) {
    errors_ptr = &errors;
    utf8EncodeTest();
    utf8DecodeTest();
}
