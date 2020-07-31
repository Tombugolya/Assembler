#ifndef ASSEMBLER_ERROR_REPORT_H
#define ASSEMBLER_ERROR_REPORT_H
#include <stdarg.h>
#include "../Common/common.h"

#define MAX_LABEL_CHARS 32  /* ':'  + '\0' */

typedef enum {
    False, True
} boolean;

typedef enum {
    NO_FILES,
    LABEL_TOO_LONG,
    TOO_MANY_LABELS,
    UNKNOWN_DATA_COMMAND,
    UNKNOWN_OPERATION_COMMAND,
    NO_QUOTATIONS,
    EXTERN_AFTER_LABEL,
    INVALID_LABEL,
    INVALID_NUMBER,
    MISSING_COMMAS,
    NOT_COMMA_SEPARATED,
    TOO_MANY_ARGUMENTS,
    TOO_FEW_ARGUMENTS,
    INVALID_OPERAND_TYPE,
    INVALID_AS_FILE,
    FILE_NOT_FOUND,
    EMPTY_NUMBER
} error_code;

boolean errorReport(error_code, int, ...);
#endif //ASSEMBLER_ERROR_REPORT_H
