#include <stdint.h>
#include <stdio.h>
#include <climits>
#include "trim.hpp"

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    FuzzedDataProvider provider(data, size);
    std::string s = provider.ConsumeRandomLengthString();

    mapnik::util::rtrim(s);

    return 0;
}
