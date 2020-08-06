#ifndef ASSEMBLER_ERROR_REPORT_H
#define ASSEMBLER_ERROR_REPORT_H
#include <stdarg.h>
#include "../Common/common.h"

/* Errors codes that represent potential errors with the user inputted file */
typedef enum {
    NO_FILES,
    LABEL_TOO_LONG,
    UNKNOWN_DECLARATION_COMMAND,
    UNKNOWN_OPERATION_COMMAND,
    NO_QUOTATIONS,
    EXTERN_AFTER_LABEL,
    INVALID_LABEL,
    INVALID_NUMBER,
    NOT_COMMA_SEPARATED,
    TOO_MANY_ARGUMENTS,
    TOO_FEW_ARGUMENTS,
    INVALID_OPERAND_TYPE,
    INVALID_AS_FILE,
    FILE_NOT_FOUND,
    INVALID_MODE,
    RESERVED_NAME,
    NOT_UNIQUE_LABEL,
    NONEXISTENT_LABEL,
    EXTERNAL_DISTANCE_INVALID,
    INVALID_WHITESPACE
} error_code;

/*
 * Function that reports errors to the terminal based on user inputted files.
 * param err - error code specifying the issue
 * param lineNumber - specifies the line on the file where the error may have taken place
 * param ... - extra parameters that can be concatenated to the error output
 */
boolean errorReport(error_code err, int lineNumber, ...);

#endif //ASSEMBLER_ERROR_REPORT_H
