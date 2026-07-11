#ifndef COMMON_STRING_H
#define COMMON_STRING_H

#include <stddef.h>
#include <stdint.h>

// TODO: Get optimised version of this. Probably with SIMD (AVX) - this is likely gonna mean assembly
// In the meantime this follows GCC's libitery memcmp implementation. I tested with godbolt. I could not beat this thing.
// Despite the same semantics, it was always slightly more optimised. a couple less instructions, less branches and less memory comparisons.
// This difference is tiny (probably below micro-optimisations) but thought it was interesting
int
memcmp(
    const void* Str1,
    const void* Str2,
    const size_t Size
);


// I have already got experience with this when I implemented my own sbrk from scratch 
// This I'm already aware of there is a memmove similar issue which is to do with tail and head copies.
// It is dependant on if the src and dst overlap and where.
// If Src is behind Dst ( src < dst ): copy backwards, 
// If Src is in front of Dst ( src > dst ): copy forwards
void
memcpy(
    void* Src,
    void* Dst,
    size_t Size
);

#endif // ! COMMON_STRING_H