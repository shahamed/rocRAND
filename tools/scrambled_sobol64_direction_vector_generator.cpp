// Copyright (c) 2022 Advanced Micro Devices, Inc. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "../library/include/rocrand/rocrand_sobol64_precomputed.h"
#include <fstream>
#include <iomanip>
#include <cstdint>
#include <iostream>
#include <string>

using namespace std;

constexpr const char* preamble
    = R"(// Copyright (c) 2022 Advanced Micro Devices, Inc. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

// Auto-generated file. Do not edit!
// Generated by tools/scrambled_sobol64_direction_vector_generator

#include "rocrand/rocrandapi.h"

)";

template<typename DirectionVectorType>
void write_matrices(std::ofstream&       fout,
                    const std::string    name,
                    DirectionVectorType* directions,
                    int32_t              n,
                    int32_t              bits,
                    uint32_t             offset)
{
    const char* dim_sym
        = (sizeof(DirectionVectorType) == 4) ? "SCRAMBLED_SOBOL32_N" : "SCRAMBLED_SOBOL64_N";
    fout << preamble << "// clang-format off\n"
         << "#define " << dim_sym << " " << n << "\nextern ROCRANDAPI const "
         << ((sizeof(DirectionVectorType) == 4) ? "unsigned int " : "unsigned long long int ")
         << name << "[" << dim_sym << "] =\n{";
    for(int k = 0; k < n; k++)
    {
        if(k % bits == 0)
            fout << std::endl << "    ";
        fout << "0x";
        fout << std::hex << std::setw(sizeof(DirectionVectorType) * 2) << std::setfill('0')
             << directions[k] + offset << ", ";
    }
    fout << "\n};\n";
}

int main(int argc, char const* argv[])
{
    if(argc != 3 || std::string(argv[1]) == "--help")
    {
        std::cout << "Usage:" << std::endl;
        std::cout << "  ./scrambled_sobol64_direction_vector_generator "
                     "../../library/include/rocrand/rocrand_scrambled_sobol32_precomputed.h "
                     "../../library/src/rocrand_scrambled_sobol32_precomputed.cpp"
                  << std::endl;
        return -1;
    }

    const std::string header_path(argv[1]);
    const std::string source_path(argv[2]);

    std::ofstream header_out(header_path, std::ios_base::out | std::ios_base::trunc);
    std::ofstream source_out(source_path, std::ios_base::out | std::ios_base::trunc);

    constexpr const char* symbol = "rocrand_h_scrambled_sobol64_direction_vectors";

    header_out << preamble << "#ifndef ROCRAND_SCRAMBLED_SOBOL64_PRECOMPUTED_H_\n"
               << "#define ROCRAND_SCRAMBLED_SOBOL64_PRECOMPUTED_H_\n"
               << "\n"
               << "#ifndef SCRAMBLED_SOBOL_DIM\n"
               << "    #define SCRAMBLED_SOBOL_DIM " << SOBOL_DIM << "\n"
               << "#endif\n"
               << "#define SCRAMBLED_SOBOL64_N " << SOBOL64_N << "\n"
               << "\n"
               << "extern ROCRANDAPI const unsigned long long\n"
               << "    " << symbol << "[SCRAMBLED_SOBOL64_N];\n"
               << "\n"
               << "#endif // ROCRAND_SCRAMBLED_SOBOL64_PRECOMPUTED_H_\n";

    write_matrices(source_out, symbol, rocrand_h_sobol64_direction_vectors, SOBOL64_N, 64, 1280000);

    return 0;
}