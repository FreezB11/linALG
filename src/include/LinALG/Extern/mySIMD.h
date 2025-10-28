/// @file: mySIMD.h
/// @brief Central SIMD include header using SIMDe
///
/// This header auto-detects platform SIMD support
/// (AVX2 → AVX → SSE2 → Scalar fallback)
/// and includes the appropriate SIMDe intrinsics.

#pragma once

// Detect SIMD support
#if defined(__AVX2__)
  #define USE_SIMDE_AVX2
  #include "simde/simde/x86/avx2.h"
#elif defined(__AVX__)
  #define USE_SIMDE_AVX
  #include "simde/simde/x86/avx.h"
#elif defined(__SSE2__)
  #define USE_SIMDE_SSE2
  #include "simde/simde/x86/sse2.h"
#elif defined(__SSE__)
  #define USE_SIMDE_SSE
  #include "simde/simde/x86/sse.h"
#else
  #define USE_SCALAR_FALLBACK
#endif

// Optional: include AES if you need crypto ops
#if defined(__AES__)
  #include "simde/simde/x86/aes.h"
#endif
