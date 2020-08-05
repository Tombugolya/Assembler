#include "first_iteration.h"

const Operation *operationPointer = NULL;
const Register *registerPointer = NULL;
int IC;
int DC;
int lineCount;
char label[MAX_LABEL_CHARS];
line_type type;
boolean errorsExist;
boolean isLabelFlag;
InstructionData instruction;
LabelChart *labelHead = NULL;
DeclarationCommands *declarationsHead = NULL;
Operand destinationOperand;
Operand originOperand;

void resetValues() {
    IC = INITIAL_IC_VALUE;
    DC = 0;
    lineCount = 0;
    errorsExist = False;
    memset(label, 0, sizeof label);
    type = 0;
    operationPointer = NULL;
    registerPointer = NULL;
    labelHead = NULL;
    declarationsHead = NULL;
}

void firstIteration(char *filename, FILE *file){
    resetValues();
    createTestFile(filename); /* Initializing our .test file */
    readFileLineByLineFirstTime(filename, file);
    updateLabelChartAddresses(&labelHead, IC);
    updateDeclarationCommandsAddresses(&declarationsHead, IC);
    writeICDC(filename, IC - INITIAL_IC_VALUE, DC);
    writeDeclarations(&declarationsHead, filename);
    if (errorsExist) {
        removeFiles(filename);
        return;
    } else
        secondIteration(filename, file, labelHead);
}

void readFileLineByLineFirstTime(char *filename, FILE *file) {
    char line[MAX_LINE_CHARS];
    char *token = NULL;
    while(fgets(line, sizeof(line), file)) {
        isLabelFlag = False;
        lineCount++;
        memset(label, 0, MAX_LABEL_CHARS); /* Clearing the line variable */
        token = strtok(line, DELIMITERS); /* Using strtok() to go token by token separated by the delimiters */
        while (token != NULL) {
            if (isLabel(token, True, True)) { /* If the line begins with a Label*/
                isLabelFlag = True;
            } else if (isComment(token)){ /* If the line is a comment*/
                token = NULL;
                break;
            } else if (isDeclaration(token)) { /* If the line is a declaration (excluding .entry which will be handled in secondIteration */
                isExtern() ? processExternLine(line) : processDeclarationLine(line);
                break;
            } else if (isInstruction(token, True)) /* Only thing that is left is that it could be an instruction */
                processInstructionLine(line, filename);
            token = strtok(NULL, DELIMITERS); /* Next token.. */
        }
    }
}

boolean isLabel(char *labelName, boolean toCheckColon, boolean report) {
    size_t len = strlen(labelName);

    if (isalpha(labelName[0]) && (toCheckColon ? labelName[len - 1] == LABEL_COLON_SIGN : True)) {

        if (toCheckColon) labelName[len-1] = '\0';

        if (len >= MAX_LABEL_CHARS) {
            return !(errorsExist = errorReport(LABEL_TOO_LONG, lineCount, labelName));
        } else if ( /* If the name matches a register / instruction operation or declaration operation name it should throw an error */
            isRegister(labelName, False) ||
            isInstruction(labelName, False) ||
            isValidDeclarationName(labelName)
        ) {
            return !(errorsExist = errorReport(RESERVED_NAME, lineCount, labelName));
        } else if (!isLabelFlag) {
            memcpy(label, labelName, (toCheckColon ? len - 1 : len));
            label[len] = '\0';
            return True;
        } else { /* If another label showed up in the same .entry / .extern this is not good, otherwise could happen in instruction lines */
            if (report)
                errorsExist = errorReport(TOO_MANY_LABELS, lineCount, labelName);
            else
                return True;
        }
    }
    return False;
}

boolean isDeclaration(char *declarationName) {
    if (declarationName[0] == DECLARATION_SIGN) { /* Sign of a declaration '.' */
        declarationName++;
        if (isValidDeclarationName(declarationName))
            return True;
        else /* Doesn't match any known declaration names*/
            errorsExist = errorReport(UNKNOWN_DECLARATION_COMMAND, lineCount, declarationName);
    }
    return False;
}

boolean isValidDeclarationName(char *declarationName) {
    if (strcmp(declarationName, "string") == 0)
        type = STRING; /* Assigns the global type variable to the correct line_type of the declaration line */
    else if (strcmp(declarationName, "data") == 0)
        type = DATA;
    else if (strcmp(declarationName, "entry") == 0)
        type = ENTRY;
    else if (strcmp(declarationName, "extern") == 0)
        type = EXTERN;
    else
        return False;
    return True;
}

boolean isInstruction(char *commandName, boolean report) {
    int i;
    for (i = 0; i < OPERATION_NUM ; i++) {
        if (strcmp(commandName, OPERATIONS[i].name) == 0 ) { /* Matched a known operation name */
            operationPointer = &OPERATIONS[i]; /* operationPointer to point at the relevant Operation to access it's data */
            return True;
        }
    }
    if (report) /* We don't want to report this error in case a label matched one of the operation names, otherwise we do */
        errorsExist = errorReport(UNKNOWN_OPERATION_COMMAND, lineCount, commandName);
    return False;
}

boolean isRegister(char *regis, boolean assign) {
    int i;
    for (i = 0 ; i < REGISTER_NUM ; i++) {
        if (strcmp(regis, REGISTERS[i].name) == 0) { /* Matched a known register name */
            if (assign) /* We don't want to assign in case a label matches one of the register names, otherwise we do */
                registerPointer = &REGISTERS[i]; /* registerPointer to point at the relevant register to access it's data */
            return True;
        }
    }
    return False;
}

boolean isComment(const char *commentSign) {
    if (commentSign[0] == COMMENT_SIGN) /* Sign of a comment ';' */
        return True;
    return False;
}

boolean isExtern() {
    boolean bool = type == EXTERN ? True : False; /* If the type variable matches the EXTERN value */
    return bool;
}

void processDeclarationLine(char *arguments) {
    if (isLabelFlag && isUniqueLabel(&labelHead, label, True))
        addToLabelChart(&labelHead, label, DC, type, False, False);

    switch (type) {
        case STRING:
            processString(arguments);
            break;
        case DATA:
            processData(arguments);
            break;
        case ENTRY:
        default:
            break;
    }
}

void processString(char *arguments) {
    size_t len;
    int i;
    arguments = strtok(NULL, "\n");  /* Next token without the comma, space or tab delimiter, because we are expecting one "string" argument */
    arguments = trimWhiteSpace(arguments);
    len = strlen(arguments) - 1;

    if (arguments[0] == '"' && arguments[len] == '"') { /* A string needs to be surrounded by quotations */
        arguments++;
        arguments[len - 1] = '\0';
        for (i = 0 ; i < strlen(arguments) ; i++)
            addToDeclarationCommands(&declarationsHead, DC++, STRING, arguments[i]); /* Valid char adding to the DeclarationCommands for later parsing */
        addToDeclarationCommands(&declarationsHead, DC++, STRING, '\0'); /* Null terminator */
    } else {
        errorsExist = errorReport(NO_QUOTATIONS, lineCount, arguments);
    }
}

void processData(char *arguments) {
    int num;
    char *endPtr = NULL;
    arguments = strtok(NULL, ",\n"); /* Next token with comma or new line, since we are expecting 1 or more "#num" arguments */

    while (arguments != NULL) {
        if (isValidNumber(arguments)) {
            num = strtol(arguments, &endPtr, 10); /* Convert to decimal int with strtol() */
            addToDeclarationCommands(&declarationsHead, DC, DATA, num); /* Adding to the DeclarationCommands */
            DC++;
        }
        arguments = strtok(NULL, ",\n"); /* Next token.. */
    }
}

void processExternLine(char *arguments) {
    if (isLabelFlag) {
        errorsExist = errorReport(EXTERN_AFTER_LABEL, lineCount, arguments);
        return;
    }

    arguments = strtok(NULL, DELIMITERS);
    if (isLabel(arguments, False, True)) {
        isUniqueLabel(&labelHead, arguments, False) ? /* If it's a unique label -- add it, otherwise update the label with a value of 0 to the address */
            addToLabelChart(&labelHead, arguments, 0, DATA, False, True) :
            updateLabelAddress(&labelHead, label, 0);
    } else
        errorsExist = errorReport(INVALID_LABEL, lineCount, arguments);
}

void processInstructionLine(char *arguments, char *filename) {
    instruction = EMPTY_INSTRUCTION;    /* Setting these 3 to their empty state */
    destinationOperand = EMPTY_OPERAND;
    originOperand = EMPTY_OPERAND;

    if (isLabelFlag && isUniqueLabel(&labelHead, label, True))
        addToLabelChart(&labelHead, label, IC, INSTRUCTION, False, False);

    assignInstructionValues();

    if (operationPointer -> operands > 0) { /* 1 or 2 operands for this relevant operation */
        if (isValidOperand(arguments, operationPointer -> operands)) {
            writeInstruction(instruction, filename);
            handleOperands(filename);
        }
    } else  /* No operands */
        writeInstruction(instruction, filename);
}

void handleOperands(char *filename) {
    if (originOperand.active) /* If the operand is active - either reserve a line or write it depending on the reserve flag */
        originOperand.reserve ? reserveOperand(originOperand, filename) : writeOperand(originOperand, filename);

    if (destinationOperand.active)
        destinationOperand.reserve ? reserveOperand(destinationOperand, filename) : writeOperand(destinationOperand, filename);
}

boolean isValidOperand(char *operand, int maxParamNum) {
    int operandNum = 0;
    char *whitespacePointer = NULL; /* For checking proper comma separation */
    addressing_mode operandMode;
    Operand *pointer;
    operand = strtok(NULL, ",\n"); /* Next token since we are expecting a few that are comma separated */
    while (operand != NULL) {
        operandNum++;
        if (operandNum > maxParamNum)
            return !(errorsExist = errorReport(TOO_MANY_ARGUMENTS, lineCount));

        operand = trimWhiteSpace(operand);

        whitespacePointer = strpbrk(operand, " \t");
        if (whitespacePointer != NULL)
            return !(errorsExist = errorReport(NOT_COMMA_SEPARATED, lineCount));

        if ((operandMode = getOperandAddressingMode(operand)) == ERROR) /* Doesn't match any known addressing mode*/
            return False;

        if (!isValidAddressingMode(operandMode, operandNum)) /* Is the addressing mode relevant for this type of operand (dest / origin)? */
            return !(errorsExist = errorReport(INVALID_OPERAND_TYPE, lineCount, operandMode, operationPointer->name));

        if (ORIGIN) pointer = &originOperand;
        else if (DESTINATION) pointer = &destinationOperand;

        switch (operandMode){
            case IMMEDIATE: /* We can assign the values immediately, no need to reserve */
                operand++; /* Stepping forward because of the "#" */
                assignOperandValues(pointer, False, operand);
                break;
            case INDIRECT:
            case DIRECT: /* The label addresses may not be known at this point so we have to reserve*/
                assignOperandValues(pointer, True, operand);
                break;
            case REGISTER: /* Registers can be assigned within the instruction line, point to the relevant operand type*/
                if (ORIGIN) instruction.regisOrigin = registerPointer->value;
                else if (DESTINATION) instruction.regisDest = registerPointer->value;
                break;
            default:
                return False;
        }

        operand = strtok(NULL, ",\n"); /* Next token.. */
    }

    if (operandNum < maxParamNum)
        return !(errorsExist = errorReport(TOO_FEW_ARGUMENTS, lineCount));

    return True;
}

boolean isValidNumber(char *number){
    int i;
    boolean isValidParam = True;
    number = trimWhiteSpace(number);
    for (i = 0; i < strlen(number) ; i++) {
        if (i == 0 && (number[i] == '-' || number[i] == '+')) /* These are exceptions for the 0 index only  */
            isValidParam = True;
        else if (number[i] != ' ' && number[i] != '\t' && !isdigit(number[i])) /* If it's not a digit, a space or a tab */
            return !(errorsExist = errorReport(INVALID_NUMBER, lineCount, number));
    }

    return isValidParam;
}

boolean isValidAddressingMode(addressing_mode mode, int operandNum){
    int i;
    const addressing_mode *modes = NULL;

    if (ORIGIN) /* Checks if we are on the Origin operand now or the Destination */
        modes = operationPointer -> modesOrigin; /* Assign the relevant modes from our operationPointer to a modes variable */
    else if (DESTINATION)
        modes = operationPointer -> modesDest;

    for (i = 0; i < MAX_APPLICABLE_MODES; i++) { /* Checks if there is a match between our operand addressing mode and the ones that are acceptable */
        if (mode == modes[i]) {
            if (ORIGIN)
                instruction.originMode = modes[i];
            else if (DESTINATION)
                instruction.destMode = modes[i];
            return True;
        }
    }
    return False;
}

addressing_mode getOperandAddressingMode(char *operand) {
    operand = trimWhiteSpace(operand);

    if (operand[0] == NUMBER_SIGN){ /* Sign for an immediate value*/
        operand++;
        if (isValidNumber(operand))
            return IMMEDIATE;
    } else if (isRegister(operand, True)) {
        return REGISTER;
    } else if (operand[0] == DISTANCE_SIGN) { /* Sign for a distance calculating value (indirect) */
        operand++;
        if (isLabel(operand, False, False))
            return INDIRECT;
    } else if (isLabel(operand, False, False)) /* Just a label without the colon */
        return DIRECT;
    else
        errorsExist = errorReport(INVALID_MODE, lineCount, operand);

    return ERROR;
}

void assignOperandValues(Operand *operand, boolean reserve, char *value) {
    (*operand).active = True;
    (*operand).value = value;
    (*operand).reserve = reserve;
    (*operand).address = IC++;
}

void assignInstructionValues() { /* Assigning initial data to the decoder based on the operation we are pointing */
    instruction.address = IC++;
    instruction.opCode = operationPointer -> opCode;
    instruction.function = operationPointer -> function;
}