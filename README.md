# FastNoise SIMD
FastNoise SIMD is the SIMD implementation of my noise library [FastNoise](https://github.com/Auburns/FastNoise). It aims to provide faster performance through the use of intrinsic(SIMD) CPU functions. Vectorisation of the code allows noise functions to process data in sets of 4 or 8 increasing performance by 300-400%.

After releasing FastNoise I got in contact with the author of [FastNoise SIMD](https://github.com/jackmott/FastNoise-SIMD) (naming is coincidence) and was inspired to work with SIMD functions myself. Through his code and discussions with him I created my implementation with even more optimisation thanks to the removal of lookup tables. 

Runtime detection of highest supported instruction set ensures the fastest possible performance with only 1 compile needed. If no support is found it will fallback to standard types (float/int).

##Features

- Value Noise 3D
- Gradient (Perlin) Noise 3D
- Simplex Noise 3D
- Multiple fractal options for all of the above
- White Noise 3D

##Supported Instruction Sets
- AVX2 - FMA3
- SSE4.1
- SSE2

##Wiki
[Getting Started](https://github.com/Auburns/FastNoiseSIMD/wiki)

More documentation coming soon.

#FastNoise SIMD Preview

I have written a compact testing application for all the features included in FastNoiseSIMD with a visual representation. I use this for development purposes and testing noise settings used in terrain generation. The fastest supported instruction set is also reported.

Download links can be found in the [Releases Section](https://github.com/Auburns/FastNoiseSIMD/releases).

![FastNoise SIMD Preview](http://i.imgur.com/p4kHh7P.png)

#Performance Comparisons
Using default noise settings on FastNoise SIMD and matching those settings across the other libraries where possible.

Timing are averages of time taken for 1 million iterations on a single thread.

- CPU: i7 4790k @ 4.0Ghz
- Compiler: MSVC v120 x64

| Noise Type       | FastNoise SIMD - AVX2 | FastNoise SIMD - SSE4.1 | FastNoise SIMD - SSE2 | FastNoise SIMD - Fallback | FastNoise | LibNoise | ANL    |
|------------------|-----------------------|-------------------------|-----------------------|---------------------------|-----------|----------|--------|
| Value            | 4.48                  | 9.28                    | 11.62                 | 25.55                     | 16.09     | 26.22    | 103.14 |
| Value Fractal    | 13.49                 | 27.32                   | 34.62                 | 81.43                     | 54.93     |          | 316.39 |
| Gradient         | 7.17                  | 15.06                   | 18.67                 | 92.42                     | 25.00     | 30.80    | 107.00 |
| Gradient Fractal | 23.55                 | 46.80                   | 58.66                 | 321.28                    | 82.26     | 112.72   | 332.47 |
| Simplex          | 7.16                  | 13.92                   | 15.11                 | 94.04                     | 31.42     |          | 44.23  |
| Simplex Fractal  | 22.12                 | 43.36                   | 45.20                 | 292.07                    | 106.80    |          | 167.67 |
| White Noise      | 0.56                  | 0.94                    | 1.50                  | 2.36                      | 3.01      |          |        |

Measurements are in ms
