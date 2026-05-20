#ifndef ARCH_X64_SERIAL_H
#define ARCH_X64_SERIAL_H

#include <stdint.h>
#include "common/status_codes.h"
#include "common/common.h"

#define MAX_SERIAL_PORTS ((uint16_t)~0u)

GLOBAL_STATUS 
SerialWrite(
    uint16_t Port,
    uint8_t  Data
);

GLOBAL_STATUS 
SerialWriteEx(
    uint16_t Port,
    uint64_t Size,
    uint8_t* Data
);

GLOBAL_STATUS 
SerialRead(
    uint16_t Port,
    uint8_t* Data
);

GLOBAL_STATUS 
SerialReadEx(
    uint16_t Port,
    uint64_t Size,
    uint8_t* Data
);



#endif // !ARCH_X64_SERIAL_H