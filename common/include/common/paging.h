#ifndef COMMON_PAGING_H
#define COMMON_PAGING_H

#include "common/common.h"
#include <stdint.h>
#include <stdbool.h>


#define MM_PAGE_SMALL_SIZE	4096
#define MM_PAGE_LARGE_SIZE  ( MM_PAGE_SMALL_SIZE * 512 )
#define MM_PAGE_HUGE_SIZE	( MM_PAGE_LARGE_SIZE * 512 )

#define MM_PAGE_SMALL_MASK  ( MM_PAGE_SMALL_SIZE - 1 )
#define MM_PAGE_LARGE_MASK  ( MM_PAGE_LARGE_SIZE - 1 )
#define MM_PAGE_HUGE_MASK   ( MM_PAGE_HUGE_SIZE  - 1 )

#define MM_PAGE_SMALL_SHIFT 12
#define MM_PAGE_LARGE_SHIFT 21
#define MM_PAGE_HUGE_SHIFT	30

#define MM_PAGE_SIZE  MM_PAGE_SMALL_SIZE
#define MM_PAGE_MASK  MM_PAGE_SMALL_MASK
#define MM_PAGE_SHIFT MM_PAGE_SMALL_SHIFT

#define MM_SIZE_TO_PAGE_SMALL( Size ) ( ( ( Size ) + MM_PAGE_SMALL_MASK ) >> MM_PAGE_SMALL_SHIFT )
#define MM_SIZE_TO_PAGE_LARGE( Size ) ( ( ( Size ) + MM_PAGE_LARGE_MASK ) >> MM_PAGE_LARGE_SHIFT )
#define MM_SIZE_TO_PAGE_HUGE(  Size ) ( ( ( Size ) + MM_PAGE_HUGE_MASK )  >> MM_PAGE_HUGE_SHIFT  )

#define MM_PAGES_SMALL_TO_SIZE( Pages ) ( ( Pages ) << MM_PAGE_SMALL_SHIFT )
#define MM_PAGES_LARGE_TO_SIZE( Pages ) ( ( Pages ) << MM_PAGE_LARGE_SHIFT )
#define MM_PAGES_HUGE_TO_SIZE(  Pages ) ( ( Pages ) << MM_PAGE_HUGE_SHIFT  ) 

#define MM_SIZE_TO_PAGE MM_SIZE_TO_PAGE_SMALL
#define MM_PAGES_TO_SIZE MM_PAGES_SMALL_TO_SIZE

#define MM_PAGE_SMALL_ALIGN_DOWN( Address ) ( ( ( Address ) >> MM_PAGE_SMALL_SHIFT ) << MM_PAGE_SMALL_SHIFT )
#define MM_PAGE_SMALL_ALIGN_UP( Address ) ( ( ( ( Address ) + MM_PAGE_SMALL_MASK ) >> MM_PAGE_SMALL_SHIFT ) << MM_PAGE_SMALL_SHIFT )

#define MM_PAGE_LARGE_ALIGN_DOWN( Address ) ( ( ( Address ) >> MM_PAGE_LARGE_SHIFT ) << MM_PAGE_LARGE_SHIFT )
#define MM_PAGE_LARGE_ALIGN_UP( Address ) ( ( ( ( Address ) + MM_PAGE_LARGE_MASK ) >> MM_PAGE_LARGE_SHIFT ) << MM_PAGE_LARGE_SHIFT )

#define MM_PAGE_HUGE_ALIGN_DOWN( Address ) ( ( ( Address ) >> MM_PAGE_HUGE_SHIFT ) << MM_PAGE_HUGE_SHIFT )
#define MM_PAGE_HUGE_ALIGN_UP( Address ) ( ( ( ( Address ) + MM_PAGE_HUGE_MASK ) >> MM_PAGE_HUGE_SHIFT ) << MM_PAGE_HUGE_SHIFT )

#define MM_PAGE_ALIGN_DOWN MM_PAGE_SMALL_ALIGN_DOWN
#define MM_PAGE_ALIGN_UP   MM_PAGE_SMALL_ALIGN_UP

#define MM_PAGE_SMALL_IS_ALIGNED( Address ) ( MM_PAGE_SMALL_ALIGN_DOWN( Address ) == Address )
#define MM_PAGE_LARGE_IS_ALIGNED( Address ) ( MM_PAGE_LARGE_ALIGN_DOWN( Address ) == Address )
#define MM_PAGE_HUGE_IS_ALIGNED(  Address ) ( MM_PAGE_HUGE_ALIGN_DOWN(  Address ) == Address )

#define MM_PAGE_IS_ALIGNED MM_PAGE_SMALL_IS_ALIGNED

#define MM_KERNEL_PML4_BASE 256

#define MM_CANONICAL_LOW_MASK  0x0000FFFFFFFFFFFFull
#define MM_CANONICAL_HIGH_MASK 0xFFFF000000000000ull
#define MM_CANONICAL_SIGN_BIT  (1ull << 47)

#define MM_PAGE_ENTRY_COUNT ( MM_PAGE_SIZE / sizeof( PVOID ) )

#define MM_PAGE_FLAG_PRESENT    ( 1ull << 0 )
#define MM_PAGE_FLAG_READ_WRITE ( 1ull << 1 )
#define MM_PAGE_FLAG_USER       ( 1ull << 2 )
#define MM_PAGE_FLAG_LARGE_PAGE ( 1ull << 7 )
#define MM_PAGE_FLAG_NO_EXECUTE ( 1ull << 63 )

#define MM_BYTES_TO_GB( Bytes ) (Bytes / ( 1024 * 1024 * 1024))
#define MM_BYTES_TO_MB( Bytes ) (Bytes / ( 1024 * 1024))

#define MM_GB_TO_BYTES( Gb ) (Gb * (1024 * 1024 * 1024))
#define MM_MB_TO_BYTES( Mb ) (Mb * (1024 * 1024))

typedef union _MM_VIRTUAL_ADDRESS
{
	uint64_t Value;

	struct
	{
		uint64_t Offset	  : 12;
		uint64_t PtIndex   : 9;
		uint64_t PdIndex   : 9;
		uint64_t PdptIndex : 9;
		uint64_t Pml4Index : 9;
		uint64_t Reserved  : 16;
	};

	struct
	{
		uint64_t Offset	  : 21;
		uint64_t PdIndex   : 9;
		uint64_t PdptIndex : 9;
		uint64_t Pml4Index : 9;
		uint64_t Reserved  : 16;

	} Large;

	struct
	{
		uint64_t Offset    : 30;
		uint64_t PdptIndex : 9;
		uint64_t Pml4Index : 9;
		uint64_t Reserved  : 16;

	} Huge;

} MM_VIRTUAL_ADDRESS, * PMM_VIRTUAL_ADDRESS;

static_assert(sizeof(MM_VIRTUAL_ADDRESS) == sizeof(uint64_t), "MM_VIRTUAL_ADDRESS Must be 8 bytes in size");

typedef union _MM_PHYSICAL_ADDRESS
{
	uint64_t Value;

	struct
	{
		uint64_t Offset : 12;
	};

	struct
	{
		uint64_t Offset : 21;

	} Large;

	struct
	{
		uint64_t Offset : 30;

	} Huge;

} MM_PHYSICAL_ADDRESS, * PMM_PHYSICAL_ADDRESS;

static_assert(sizeof(MM_PHYSICAL_ADDRESS) == sizeof(uint64_t), "MM_PHYSICAL_ADDRESS Must be 8 bytes in size");

typedef union _MM_PTE_DESCRIPTOR
{
    uint64_t Value;

    //
    // Intel SDM Volume 3
    // Table 5-20. Format of a Page-Table Entry that Maps a 4-KByte Page
    //
    struct
    {
        uint64_t Present          : 1;   // [0]
        uint64_t Writable         : 1;   // [1]
        uint64_t UserSupervisor   : 1;   // [2]
        uint64_t PageWriteThrough : 1;   // [3]
        uint64_t PageCacheDisable : 1;   // [4]
        uint64_t Accessed         : 1;   // [5]
        uint64_t Dirty            : 1;   // [6]
        uint64_t PAT              : 1;   // [7]
        uint64_t Global           : 1;   // [8]
        uint64_t Ignored1         : 2;   // [10:9]
        uint64_t HLATRestart      : 1;   // [11]
        uint64_t PageFrameNumber  : 36;  // [47:12]
        uint64_t Reserved0        : 4;   // [51:48]
        uint64_t Ignored2         : 7;   // [58:52]
        uint64_t ProtectionKey    : 4;   // [62:59]
        uint64_t NoExecute        : 1;   // [63]
    };

    //
    // Intel SDM Volume 3
    // Table 5-18. Format of a Page-Directory Entry that Maps a 2-MByte Page
    //
    struct
    {
        uint64_t Present          : 1;   // [0]
        uint64_t Writable         : 1;   // [1]
        uint64_t UserSupervisor   : 1;   // [2]
        uint64_t PageWriteThrough : 1;   // [3]
        uint64_t PageCacheDisable : 1;   // [4]
        uint64_t Accessed         : 1;   // [5]
        uint64_t Dirty            : 1;   // [6]
        uint64_t LargePage        : 1;   // [7]
        uint64_t Global           : 1;   // [8]
        uint64_t Ignored1         : 2;   // [10:9]
        uint64_t HLATRestart      : 1;   // [11]
        uint64_t PAT              : 1;   // [12]
        uint64_t Reserved0        : 8;   // [20:13]
        uint64_t PageFrameNumber  : 31;  // [51:21]
        uint64_t Reserved1        : 1;   // [52]
        uint64_t Ignored2         : 6;   // [58:53]
        uint64_t ProtectionKey    : 4;   // [62:59]
        uint64_t NoExecute        : 1;   // [63]

    } Large;

    //
    // Intel SDM Volume 3
    // Table 5-16. Format of a Page-Directory-Pointer-Table Entry (PDPTE) that Maps a 1-GByte Page
    //
    struct
    {
        uint64_t Present          : 1;   // [0]
        uint64_t Writable         : 1;   // [1]
        uint64_t UserSupervisor   : 1;   // [2]
        uint64_t PageWriteThrough : 1;   // [3]
        uint64_t PageCacheDisable : 1;   // [4]
        uint64_t Accessed         : 1;   // [5]
        uint64_t Dirty            : 1;   // [6]
        uint64_t HugePage         : 1;   // [7]
        uint64_t Global           : 1;   // [8]
        uint64_t Ignored1         : 2;   // [10:9]
        uint64_t HLATRestart      : 1;   // [11]
        uint64_t PAT              : 1;   // [12]
        uint64_t Reserved0        : 17;  // [29:13]
        uint64_t PageFrameNumber  : 22;  // [51:30]
        uint64_t Reserved1        : 1;   // [52]
        uint64_t Ignored2         : 6;   // [58:53]
        uint64_t ProtectionKey    : 4;   // [62:59]
        uint64_t NoExecute        : 1;   // [63]

    } Huge;

    union
    {
        struct
        {
            uint64_t Readable        : 1;   // [0]
            uint64_t Writable        : 1;   // [1]
            uint64_t Executable      : 1;   // [2]
            uint64_t MemoryType      : 3;   // [5:3]
            uint64_t IgnorePAT       : 1;   // [6]
            uint64_t Reserved0       : 1;   // [7]
            uint64_t Accessed        : 1;   // [8]
            uint64_t Dirty           : 1;   // [9]
            uint64_t UserExecute     : 1;   // [10]
            uint64_t Reserved1       : 1;   // [11]
            uint64_t PageFrameNumber : 36;  // [47:12]
            uint64_t Reserved2       : 15;  // [62:48]
            uint64_t SupressVE       : 1;   // [63]
        };

        struct
        {
            uint64_t Readable        : 1;   // [0]
            uint64_t Writable        : 1;   // [1]
            uint64_t Executable      : 1;   // [2]
            uint64_t MemoryType      : 3;   // [5:3]
            uint64_t IgnorePAT       : 1;   // [6]
            uint64_t LargePage       : 1;   // [7]
            uint64_t Accessed        : 1;   // [8]
            uint64_t Dirty           : 1;   // [9]
            uint64_t UserExecute     : 1;   // [10]
            uint64_t Reserved1       : 10;  // [20:11]
            uint64_t PageFrameNumber : 27;  // [47:21]
            uint64_t Reserved2       : 15;  // [62:48]
            uint64_t SupressVE       : 1;   // [63]

        } Large;

        struct
        {
            uint64_t Readable        : 1;   // [0]
            uint64_t Writable        : 1;   // [1]
            uint64_t Executable      : 1;   // [2]
            uint64_t MemoryType      : 3;   // [5:3]
            uint64_t IgnorePAT       : 1;   // [6]
            uint64_t LargePage       : 1;   // [7]
            uint64_t Accessed        : 1;   // [8]
            uint64_t Dirty           : 1;   // [9]
            uint64_t UserExecute     : 1;   // [10]
            uint64_t Reserved1       : 19;  // [29:11]
            uint64_t PageFrameNumber : 18;  // [47:30]
            uint64_t Reserved2       : 15;  // [62:48]
            uint64_t SupressVE       : 1;   // [63]

        } Huge;

    } Extended;

} MM_PTE_DESCRIPTOR, * PMM_PTE_DESCRIPTOR;

static_assert(sizeof(MM_PTE_DESCRIPTOR) == sizeof(uint64_t), "MM_PTE_DESCRIPTOR Must be 8 bytes in size");

typedef union _MM_PAGING_BASE_DESCRIPTOR
{
    uint64_t Value;

    struct
    {
        uint64_t Reserved1             : 3;
        uint64_t PageLevelWriteThrough : 1;
        uint64_t PageLevelCacheDisable : 1;
        uint64_t Reserved2             : 7;
        uint64_t PageFrameNumber       : 36;
        uint64_t Reserved3             : 16;
    };

    struct
    {
        uint64_t Pcid            : 12; 
        uint64_t PageFrameNumber : 36; 
        uint64_t Reserved1       : 16; 
    } Pcide;

} MM_PAGING_BASE_DESCRIPTOR, * PMM_PAGING_BASE_DESCRIPTOR;

static_assert(sizeof(MM_PAGING_BASE_DESCRIPTOR) == sizeof(uint64_t), "MM_PAGING_BASE_DESCRIPTOR Must be 8 bytes");

__inline__
bool
MmIsAddressCanonical(
    _In_ uint64_t Value
)
{
    if (Value & MM_CANONICAL_SIGN_BIT)
    {
        return ((Value >> 48ull) == 0xFFFFull);
    }

    return ((Value >> 48ull) == 0x0000ull);
}

__inline__
uint64_t
MmMakeAddressCanonical(
    _In_ uint64_t Value
)
{
    if (Value & MM_CANONICAL_SIGN_BIT)
    {
        Value |= MM_CANONICAL_HIGH_MASK;
    }

    return Value;
}

__inline__
uint64_t
MmMakeAddressNotCanonical(
    _In_ uint64_t Value
)
{
    return Value & MM_CANONICAL_LOW_MASK;
}

__inline__
uint64_t
MmMakeVirtualAddress(
    _In_ uint64_t Pml4Index,
    _In_ uint64_t PdptIndex,
    _In_ uint64_t PdIndex,
    _In_ uint64_t PtIndex,
    _In_ uint64_t Offset
)
{
    MM_VIRTUAL_ADDRESS VirtualAddress = { 0 };

    VirtualAddress.Pml4Index = Pml4Index;
    VirtualAddress.PdptIndex = PdptIndex;
    VirtualAddress.PdIndex = PdIndex;
    VirtualAddress.PtIndex = PtIndex;
    VirtualAddress.Offset = Offset;

    return MmMakeAddressCanonical(VirtualAddress.Value);
}

__inline__
uint64_t
MmMakeLargeVirtualAddress(
    _In_ uint64_t Pml4Index,
    _In_ uint64_t PdptIndex,
    _In_ uint64_t PdIndex,
    _In_ uint64_t Offset
)
{
    MM_VIRTUAL_ADDRESS VirtualAddress = { 0 };

    VirtualAddress.Large.Pml4Index = Pml4Index;
    VirtualAddress.Large.PdptIndex = PdptIndex;
    VirtualAddress.Large.PdIndex = PdIndex;
    VirtualAddress.Large.Offset = Offset;

    return MmMakeAddressCanonical(VirtualAddress.Value);
}

__inline__
uint64_t
MmMakeHugeVirtualAddress(
    _In_ uint64_t Pml4Index,
    _In_ uint64_t PdptIndex,
    _In_ uint64_t Offset
)
{
    MM_VIRTUAL_ADDRESS VirtualAddress = { 0 };

    VirtualAddress.Huge.Pml4Index = Pml4Index;
    VirtualAddress.Huge.PdptIndex = PdptIndex;
    VirtualAddress.Huge.Offset = Offset;

    return MmMakeAddressCanonical(VirtualAddress.Value);
}

__inline__
uint64_t
__MmR_xProtection(
    void
)
{
    MM_PTE_DESCRIPTOR Protection = { 0 };
    Protection.Present   = true;
    Protection.Writable  = false;
    Protection.NoExecute = false;
    return Protection.Value;
};

__inline__
uint64_t
__MmRw_Protection(
    void
)
{
    MM_PTE_DESCRIPTOR Protection = { 0 };
    Protection.Present   = true;
    Protection.Writable  = true;
    Protection.NoExecute = true;
    return Protection.Value;
};

__inline__
uint64_t
__MmR__Protection(
    void
)
{
    MM_PTE_DESCRIPTOR Protection = { 0 };
    Protection.Present   = true;
    Protection.Writable  = false;
    Protection.NoExecute = true;
    return Protection.Value;
};

__inline__
uint64_t
__MmRwxProtection(
    void
)
{
    MM_PTE_DESCRIPTOR Protection = { 0 };
    Protection.Present   = true;
    Protection.Writable  = true;
    Protection.NoExecute = false;
    return Protection.Value;
};

#define MmReadExecuteProtection      \
(                                    \
    MM_PAGE_FLAG_PRESENT             \
)                                    
                                     
#define MmReadWriteProtection        \
(                                    \
    MM_PAGE_FLAG_PRESENT    |        \
    MM_PAGE_FLAG_READ_WRITE |        \
    MM_PAGE_FLAG_NO_EXECUTE          \
)

#define MmReadOnlyProtection         \
(                                    \
    MM_PAGE_FLAG_PRESENT    |        \
    MM_PAGE_FLAG_NO_EXECUTE          \
)

#define MmReadWriteExecuteProtection \
(                                    \
    MM_PAGE_FLAG_PRESENT    |        \
    MM_PAGE_FLAG_READ_WRITE          \
)                             

__inline__
uint64_t
__MmStrongCacheDisablePolicy(
    void
)
{
    MM_PTE_DESCRIPTOR Protection = { 0 };
    Protection.PageWriteThrough = true;
    Protection.PageCacheDisable = true;
    return Protection.Value;
};

__inline__
uint64_t
__MmCacheDisablePolicy(
    void
)
{
    MM_PTE_DESCRIPTOR Protection = { 0 };
    Protection.PageWriteThrough = false;
    Protection.PageCacheDisable = true;
    return Protection.Value;
};

__inline__
uint64_t
__MmWritebackPolicy(
    void
)
{
    MM_PTE_DESCRIPTOR Protection = { 0 };
    Protection.PageWriteThrough = false;
    Protection.PageCacheDisable = false;
    return Protection.Value;
};

// Strong cacheability meaning MTRRs cannot override this. UC.
#define MmStrongUncacheablePagePolicy \
(                                     \
    __MmStrongCacheDisablePolicy()    \
)

// MTRRs can override this cacheability from UC- to WC (Write-Combining).
#define MmWeakUncacheablePagePolicy   \
(                                     \
    __MmCacheDisablePolicy()          \
)    

#define MmWritebackPagePolicy         \
(                                     \
    __MmWritebackPolicy()             \
)                                     

__inline__
bool
MmMakePageStrongUncacheable(
    PMM_PTE_DESCRIPTOR Page
)
{
    if (!Page)
    {
        return false;
    }

    Page->Value |= MmStrongUncacheablePagePolicy;

    return true;
}

__inline__
bool
MmMakePageWeakUncacheable(
    PMM_PTE_DESCRIPTOR Page
)
{
    if (!Page)
    {
        return false;
    }

    Page->Value |= MmWeakUncacheablePagePolicy;

    return true;
}

__inline__
bool
MmMakePageWriteback(
    PMM_PTE_DESCRIPTOR Page
)
{
    if (!Page)
    {
        return false;
    }

    Page->Value |= MmWritebackPagePolicy;

    return true;
}

#endif // !ARCHX64_PAGING_H