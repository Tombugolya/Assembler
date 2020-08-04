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
            fprintf(stderr,"Error in line.%d: Unexpected appearance of an extra label \"%s\", only one label can appear per line\n",
                    lineNumber,
                    va_arg(args, char*));
            break;
        case UNKNOWN_DECLARATION_COMMAND:
            fprintf(stderr, "Error in line.%d: Unknown data command \"%s\"\n",
                    lineNumber,
                    va_arg(args, char*));
            break;
        case UNKNOWN_OPERATION_COMMAND:
            fprintf(stderr, "Error in line.%d: Unknown command \"%s\"\n",
                    lineNumber,
                    va_arg(args, char*));
            break;
        case NO_QUOTATIONS:
            fprintf(stderr, "Error in line.%d: quotations are not covering the entire string > %s  \n",
                    lineNumber,
                    va_arg(args, char*));
            break;
        case EXTERN_AFTER_LABEL:
            fprintf(stderr, "Error in line.%d: Label needs to appear after \".extern\"\n",
                    lineNumber);
            break;
        case INVALID_LABEL:
            fprintf(stderr, "Error in line.%d: \"%s\" is not a valid label\n",
                    lineNumber,
                    va_arg(args, char*));
            break;
        case INVALID_NUMBER:
            fprintf(stderr, "Error in line.%d: \"%s\" is not a valid number\n",
                    lineNumber,
                    va_arg(args, char*));
            break;
        case MISSING_COMMAS:
            fprintf(stderr, "Error in line.%d: Missing comma before \"%s\"\n",
                    lineNumber,
                    va_arg(args, char*));
            break;
        case NOT_COMMA_SEPARATED:
            fprintf(stderr, "Error in line.%d: Not comma separated value\n",
                    lineNumber);
            break;
        case TOO_MANY_ARGUMENTS:
            fprintf(stderr, "Error in line.%d: Too many arguments\n",
                    lineNumber);
            break;
        case TOO_FEW_ARGUMENTS:
            fprintf(stderr, "Error in line.%d: Too few arguments\n",
                    lineNumber);
            break;
        case INVALID_OPERAND_TYPE:
            mode = va_arg(args, addressing_mode);
            fprintf(stderr, "Error in line.%d: Operand addressing mode no. %d does not suit the criteria for command %s\n",
                    lineNumber, mode, va_arg(args, char *));
            break;
        case INVALID_AS_FILE:
            fprintf(stderr, "Error: \"%s\" is not an .as file\n", va_arg(args, char *));
            break;
        case FILE_NOT_FOUND:
            fprintf(stderr, "Error: Cannot locate file \"%s\"\n", va_arg(args, char *));
            break;
        case INVALID_MODE:
            fprintf(stderr, "Error in line.%d: \"%s\" does not match any valid addressing mode\n",
                    lineNumber, va_arg(args, char *));
            break;
        case RESERVED_NAME:
            fprintf(stderr, "Error in line.%d: \"%s\" is a reserved name and cannot be used\n",
                    lineNumber, va_arg(args, char *));
            break;
        case NOT_UNIQUE_LABEL:
            fprintf(stderr, "Error: Label with the name \"%s\" is already used \n",
                    va_arg(args, char *));
            break;
        case NONEXISTENT_LABEL:
            fprintf(stderr, "Error: Label with the name \"%s\" does not exist \n",
                    va_arg(args, char *));
            break;
        case EXTERNAL_DISTANCE_INVALID:
            fprintf(stderr, "Error: Label with the name \"%s\" is external so it's distance cannot be calculated \n",
                    va_arg(args, char *));
            break;
        default:
            fprintf(stderr, "UH OH! You forgot to put the break!\n");
            break;
    }
    va_end(args);
    return True;
}
