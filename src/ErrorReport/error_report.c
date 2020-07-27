#include "error_report.h"

boolean errorReport(error_code err, int lineNumber, ... ){
    va_list args;
    va_start(args, lineNumber);
    addressing_mode mode;
    switch (err) {
        case NO_FILES:
            fprintf(stderr, "Error: No files attached\n");
            break;
        case LABEL_TOO_LONG:
            fprintf(stderr, "Error in line.%d: Label name \"%s\" is too long, up to %d characters are allowed\n",
                    lineNumber,
                    va_arg(args, char*),
                    MAX_LABEL_CHARS - 1);
            break;
        case TOO_MANY_LABELS:
            fprintf(stderr,
                    "Error in line.%d: Unexpected appearance of an extra label \"%s\", only one label can appear per line\n",
                    lineNumber,
                    va_arg(args, char*));
            break;
        case UNKNOWN_DATA_COMMAND:
            fprintf(stderr, "Error in line.%d: Unknown data command \"%s\"\n", lineNumber,
                    va_arg(args, char*));
            break;
        case UNKNOWN_OPERATION_COMMAND:
            fprintf(stderr, "Error in line.%d: Unknown command \"%s\"\n", lineNumber,
                    va_arg(args, char*));
            break;
        case NO_QUOTATIONS:
            fprintf(stderr, "Error in line.%d: No opening and closing quotations in > %s  \n", lineNumber,
                    va_arg(args, char*));
            break;
        case EXTERN_AFTER_LABEL:
            fprintf(stderr, "Error in line.%d: Label needs to appear after \".extern\"\n", lineNumber);
            break;
        case NOT_VALID_LABEL:
            fprintf(stderr, "Error in line.%d: \"%s\" is not a valid label\n", lineNumber,
                    va_arg(args, char*));
            break;
        case NOT_VALID_NUMBER:
            fprintf(stderr, "Error in line.%d: \"%s\" is not a valid number\n", lineNumber,
                    va_arg(args, char*));
            break;
        case MISSING_COMMAS:
            fprintf(stderr, "Error in line.%d: Missing comma before \"%s\"\n", lineNumber,
                    va_arg(args, char*));
            break;
        case NOT_COMMA_SEPARATED:
            fprintf(stderr, "Error in line.%d: Not comma separated value\n", lineNumber);
            break;
        case TOO_MANY_ARGUMENTS:
            fprintf(stderr, "Error in line.%d: Too many arguments\n", lineNumber);
            break;
        case TOO_FEW_ARGUMENTS:
            fprintf(stderr, "Error in line.%d: Too few arguments\n", lineNumber);
            break;
        case INVALID_OPERAND_TYPE:
            mode = va_arg(args, addressing_mode);
            fprintf(stderr, "Error in line.%d: Operand addressing mode no. %d does not suit the criteria for command %s\n",
                    lineNumber, mode, va_arg(args, char *));
            break;
        default:
            fprintf(stderr, "UH OH! GENERAL ERROR, CREATE A CODE FOR THIS\n");
            break;
    }
    va_end(args);
    return True;
}
