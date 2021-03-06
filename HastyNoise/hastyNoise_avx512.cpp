// hastyNoise_avx512.cpp
//
// MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#ifdef hastyNoise_avx512_EXPORTS
#define hastyNoise_EXPORTS
#endif

#include "hastyNoise.h"

#include "simd_constants.inl"

namespace HastyNoise
{
namespace details
{

template<typename Float, typename Int>
struct Constants<Float, Int, SIMDType::AVX512>:ConstantsBase<Float, Int>
{
    static Float numf_X_GRAD;
    static Float numf_Y_GRAD;
    static Float numf_Z_GRAD;
};

template<typename Float, typename Int>
Float Constants<Float, Int, SIMDType::AVX512>::numf_X_GRAD;
template<typename Float, typename Int>
Float Constants<Float, Int, SIMDType::AVX512>::numf_Y_GRAD;
template<typename Float, typename Int>
Float Constants<Float, Int, SIMDType::AVX512>::numf_Z_GRAD;

}
}

#include "internal_none.inl"
#include "internal_avx512.inl"
#include "hastyNoise_internal.h"

#include "simd_init.inl"

namespace HastyNoise
{
namespace details
{

template<>
struct InitSIMDValues<SIMDType::AVX512>:InitSIMDValuesBase<SIMDType::AVX512>
{
    typedef Constants<typename SIMD<SIMDType::AVX512>::Float, typename SIMD<SIMDType::AVX512>::Int, SIMDType::AVX512> _Constants;

    static void _()
    {
        if(_Constants::valueSet)
            return;

        _Constants::numf_X_GRAD=_mm512_set_ps(0, -1, 0, 1, 0, 0, 0, 0, -1, 1, -1, 1, -1, 1, -1, 1);
        _Constants::numf_Y_GRAD=_mm512_set_ps(-1, 1, -1, 1, -1, 1, -1, 1, 0, 0, 0, 0, -1, -1, 1, 1);
        _Constants::numf_Z_GRAD=_mm512_set_ps(-1, 0, 1, 0, -1, -1, 1, 1, -1, -1, 1, 1, 0, 0, 0, 0);

        InitSIMDValuesBase<SIMDType::AVX512>::init<_Constants>();
    }
};

}
}
#include "hastyNoise_internal.inl"

namespace HastyNoise
{
namespace details
{

template<>
struct GradCoord<SIMDType::AVX512>
{
    static typename SIMD<SIMDType::AVX512>::Float VECTORCALL _(typename SIMD<SIMDType::AVX512>::Int seed, typename SIMD<SIMDType::AVX512>::Int xi, typename SIMD<SIMDType::AVX512>::Int yi, typename SIMD<SIMDType::AVX512>::Int zi, typename SIMD<SIMDType::AVX512>::Float x, typename SIMD<SIMDType::AVX512>::Float y, typename SIMD<SIMDType::AVX512>::Float z)
    {
        typedef Constants<SIMD<SIMDType::AVX512>::Float, SIMD<SIMDType::AVX512>::Int, SIMDType::AVX512> Constant;
        typename SIMD<SIMDType::AVX512>::Int hash=Hash<SIMDType::AVX512>(seed, xi, yi, zi);

        typename SIMD<SIMDType::AVX512>::Float xGrad=SIMD<SIMDType::AVX512>::permute(Constant::numf_X_GRAD, hash);
        typename SIMD<SIMDType::AVX512>::Float yGrad=SIMD<SIMDType::AVX512>::permute(Constant::numf_Y_GRAD, hash);
        typename SIMD<SIMDType::AVX512>::Float zGrad=SIMD<SIMDType::AVX512>::permute(Constant::numf_Z_GRAD, hash);

        return SIMD<SIMDType::AVX512>::mulAdd(x, xGrad, SIMD<SIMDType::AVX512>::mulAdd(y, yGrad, SIMD<SIMDType::AVX512>::mulf(z, zGrad)));
    }
};

template class HASTYNOISE_EXPORT NoiseSIMD<SIMDType::AVX512>;
//template struct Constants<typename SIMD<SIMDType::AVX512>::Float, typename SIMD<SIMDType::AVX512>::Int, SIMDType::AVX512>;

}//namespace details
}//namespace HastyNoise

