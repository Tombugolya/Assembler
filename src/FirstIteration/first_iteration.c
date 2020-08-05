#include "first_iteration.h"

const Operation *commandPointer = NULL;
const Register *registerPointer = NULL;
int IC;
int DC;
int lineCount;
char label[MAX_LABEL_CHARS];
line_type type;
boolean errorsExist;
boolean isLabelFlag;
InstructionData instruction;
Label *labelHead = NULL;
DeclarationCommands *declarationsHead = NULL;
Operand destinationOperand;
Operand originOperand;

void resetValues() {
    IC = 100;
    DC = 0;
    lineCount = 0;
    errorsExist = False;
    memset(label, 0, sizeof label);
    type = 0;
    commandPointer = NULL;
    registerPointer = NULL;
    labelHead = NULL;
    declarationsHead = NULL;
}

void firstIteration(char *filename, FILE *file){
    resetValues();
    createTestFile(filename);
    readFileLineByLineFirstTime(filename, file);
    updateLabelChart(&labelHead, IC);
    updateDeclarationCommands(&declarationsHead, IC);
    writeICDC(filename, IC-100, DC);
    writeData(&declarationsHead, filename);
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
        memset(label, 0, MAX_LABEL_CHARS);
        token = strtok(line, delimiters);
        while(token != NULL) {
            if (isLabel(token, True, True))
                isLabelFlag = True;
            else if (isComment(token)){
                token = NULL;
                break;
            }
            else if (isDeclaration(token)) {
                isExtern() ? processExternLine(line) : processDeclarationLine(line);
                break;
            }
            else if (isInstruction(token, True))
                processInstructionLine(line, filename);
            token = strtok(NULL, delimiters);
        }
    }
}

boolean isLabel(char *labelName, boolean toCheckColon, boolean report) {
    size_t len = strlen(labelName);
    if (isalpha(labelName[0]) && (toCheckColon ? labelName[len - 1] == ':' : True)) {
        if (toCheckColon) labelName[len-1] = '\0';
        if (len >= MAX_LABEL_CHARS)
            return !(errorsExist = errorReport(LABEL_TOO_LONG, lineCount, labelName));
        else if (isRegister(labelName, False) || isInstruction(labelName, False) || isValidDeclarationName(labelName))
            return !(errorsExist = errorReport(RESERVED_NAME, lineCount, labelName));
        else if (!isLabelFlag) {
            memcpy(label, labelName, (toCheckColon ? len - 1 : len));
            label[len] = '\0';
            return True;
        }
        else {
            if (report)
                errorsExist = errorReport(TOO_MANY_LABELS, lineCount, labelName);
            else
                return True;
        }
    }
    return False;
}

boolean isDeclaration(char *declarationName) {
    size_t len = strlen(declarationName);
    char *name = NULL;
    name = (char *) malloc(len - 1);
    strncpy(name, declarationName + 1, len - 1);
    name[len - 1] = '\0';
    if (declarationName[0] == '.') {
        if (isValidDeclarationName(name))
            return True;
        else
            errorsExist = errorReport(UNKNOWN_DECLARATION_COMMAND, lineCount, declarationName);
    }
    return False;
}

boolean isInstruction(char *commandName, boolean report) {
    int i;
    for (i=0; i < OPERATION_NUM ; i++) {
        if (strcmp(commandName, OPERATIONS[i].name) == 0 ) {
            commandPointer = &OPERATIONS[i];
            return True;
        }
    }
    if (report) errorsExist = errorReport(UNKNOWN_OPERATION_COMMAND, lineCount, commandName);
    return False;
}

boolean isRegister(char *regis, boolean assign) {
    int i;
    for (i=0 ; i < REGISTER_NUM ; i++) {
        if (strcmp(regis, REGISTERS[i].name) == 0) {
            if (assign) registerPointer = &REGISTERS[i];
            return True;
        }
    }
    return False;
}

boolean isComment(const char *commentSymbol) {
    if (commentSymbol[0] == ';')
        return True;
    return False;
}

boolean isExtern() {
    boolean bool = type == EXTERN ? True : False;
    return bool;
}

boolean isValidDeclarationName(char *declarationName) {
    if (strcmp(declarationName, "string") == 0)
        type = STRING;
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
    char *stringContent = NULL;
    int i;
    arguments = strtok(NULL, "\n");
    arguments = trimWhiteSpace(arguments);
    if (arguments[0] == '"' && arguments[len = (strlen(arguments) - 1)] == '"') {
        stringContent = malloc(len);
        strncpy(stringContent, arguments + 1, len - 1);
        stringContent[len - 1] = '\0';
        for (i=0 ; i < strlen(stringContent) ; i++)
            addToDeclarationCommands(&declarationsHead, DC++, STRING, stringContent[i]);
        addToDeclarationCommands(&declarationsHead, DC++, STRING, '\0');
    } else {
        errorsExist = errorReport(NO_QUOTATIONS, lineCount, arguments);
    }
}

void processData(char *arguments) {
    int num;
    char *endPtr = NULL;
    char *saveContent = NULL;
    arguments = strtok(NULL, ",\n");
    while (arguments != NULL) {
        saveContent = malloc(strlen(arguments));
        strcpy(saveContent, arguments);
        saveContent[strlen(saveContent)] = '\0';
        if (isValidNumber(saveContent)) {
            num = strtol(saveContent, &endPtr, 10);
            addToDeclarationCommands(&declarationsHead, DC, DATA, num);
            DC++;
        }
        arguments = strtok(NULL, ",\n");
    }
}

void processExternLine(char *arguments) {
    if (isLabelFlag) {
        errorsExist = errorReport(EXTERN_AFTER_LABEL, lineCount, arguments);
        return;
    }
    arguments = strtok(NULL, delimiters);
    if (isLabel(arguments, False, True))
        isUniqueLabel(&labelHead, arguments, False) ? addToLabelChart(&labelHead, arguments, 0, DATA, False, True) : updateLabelAddress(
                &labelHead, label, 0);
    else
        errorsExist = errorReport(INVALID_LABEL, lineCount, arguments);
}

void processInstructionLine(char *arguments, char *filename) {
    instruction = EmptyInstruction;
    destinationOperand = EmptyOperand;
    originOperand = EmptyOperand;
    if (isLabelFlag && isUniqueLabel(&labelHead, label, True))
        addToLabelChart(&labelHead, label, IC, INSTRUCTION, False, False);
    assignInstructionValues();
    if (commandPointer -> operands > 0) {
        if (isValidOperand(arguments, commandPointer -> operands)) {
            decodeInstruction(instruction, filename);
            handleOperands(filename);
        }
    }
    else { /* No operands */
        decodeInstruction(instruction, filename);
    }
}

void handleOperands(char *filename) {
    if (destinationOperand.active)
        destinationOperand.reserve ? reserveOperand(destinationOperand, filename) : writeOperand(destinationOperand, filename);
    if (originOperand.active)
        originOperand.reserve ? reserveOperand(originOperand, filename) : writeOperand(originOperand, filename);
}

/*TODO: Potentially you might want to change all of the 'filename' parameters to be the file, instead of opening and closing it every function call*/
boolean isValidOperand(char *operand, int maxParamNum) {
    int operandNum = 0;
    char *pt = NULL;
    addressing_mode operandMode;
    Operand *pointer;
    operand = strtok(NULL, ",\n");
    while (operand != NULL) {
        operandNum++;
        if (operandNum > maxParamNum)
            return !(errorsExist = errorReport(TOO_MANY_ARGUMENTS, lineCount));
        operand = trimWhiteSpace(operand);
        pt = strpbrk(operand, " \t");
        if (pt != NULL)
            return !(errorsExist = errorReport(NOT_COMMA_SEPARATED, lineCount));
        if ((operandMode = getOperandAddressingMode(operand)) == ERROR)
            return False;
        if (!isValidAddressingMode(operandMode, operandNum))
            return !(errorsExist = errorReport(INVALID_OPERAND_TYPE, lineCount, operandMode, commandPointer->name));
        if (ORIGIN) pointer = &originOperand;
        else if (DESTINATION) pointer = &destinationOperand;
        switch (operandMode){
            case IMMEDIATE:
                operand++;
                assignOperandValues(pointer, False, operand);
                break;
            case INDIRECT:
            case DIRECT:
                assignOperandValues(pointer, True, operand);
                break;
            case REGISTER:
                if (ORIGIN) instruction.regisOrigin = registerPointer->value;
                else if (DESTINATION) instruction.regisDest = registerPointer->value;
                break;
            default:
                return False;
        }
        operand = strtok(NULL, ",\n");
    }
    if (operandNum < maxParamNum)
        return !(errorsExist = errorReport(TOO_FEW_ARGUMENTS, lineCount));
    return True;
}

boolean isValidNumber(char *number){
    int i;
    boolean isValidParam = True;
    number = trimWhiteSpace(number);
    for(i=0; i < strlen(number) ; i++) {
        if (i==0 && (number[i] == '-' || number[i] == '+'))
            isValidParam = True;
        else if (number[i] != ' ' && number[i] != '\t' && !isdigit(number[i]))
            return !(errorsExist = errorReport(INVALID_NUMBER, lineCount, number));
    }
    return isValidParam;
}

boolean isValidAddressingMode(addressing_mode mode, int operandNum){
    int i;
    const addressing_mode *modes = NULL;
    if (ORIGIN)
        modes = commandPointer -> modesOrigin;
    else if (DESTINATION)
        modes = commandPointer -> modesDest;

    for (i = 0; i < MAX_APPLICABLE_MODES; i++) {
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
    if (operand[0] == '#'){
        operand++;
        if (isValidNumber(operand))
            return IMMEDIATE;
    } else if (isRegister(operand, True)) {
        return REGISTER;
    } else if (operand[0] == '&') {
        operand++;
        if (isLabel(operand, False, False))
            return INDIRECT;
    } else if (isLabel(operand, False, False))
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

void assignInstructionValues() {
    instruction.address = IC++;
    instruction.opCode = commandPointer -> opCode;
    instruction.function = commandPointer -> function;
}