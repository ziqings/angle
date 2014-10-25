//
// Copyright (c) 2014 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#include "common/angleutils.h"

#include <stdio.h>
#include <vector>

int FormatStringIntoVector(const char *fmt, va_list vararg, std::vector<char>* buffer)
{
    // Attempt to just print to the current buffer
    int len = vsnprintf(&(buffer->front()), buffer->size(), fmt, vararg);
    if (len < 0 || static_cast<size_t>(len) >= buffer->size())
    {
        // Buffer was not large enough, calculate the required size and resize the buffer
        len = vsnprintf(NULL, 0, fmt, vararg);
        buffer->resize(len + 1);

        // Print again
        len = vsnprintf(&(buffer->front()), buffer->size(), fmt, vararg);
    }
    return len;
}

std::string FormatString(const char *fmt, va_list vararg)
{
    static std::vector<char> buffer(512);

    int len = FormatStringIntoVector(fmt, vararg, &buffer);

    return std::string(&buffer[0], len);
}

std::string FormatString(const char *fmt, ...)
{
    va_list vararg;
    va_start(vararg, fmt);
    std::string result = FormatString(fmt, vararg);
    va_end(vararg);
    return result;
}
