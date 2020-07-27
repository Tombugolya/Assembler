#include "decode.h"

void decodeInstruction(int opCode, line_type type, addressing_mode first, ...) {
    if (type == CODE) {
        InstructionCode test;
        test.opCode = opCode;
        test.originAddress = 0;
        test.originOperand = 0;
        test.destAddress = 0;
        test.destOperand = 0;
        test.function = 0;
        test.absolute = 0;
        test.relocatable = 0;
        test.external = 0;
        writeHexadecimal(test, "filename");
    } else if ( type == STRING ) {
        DataCode test;
    } else { /* type == DATA { */
        OperandCode test;
    }
}

void writeHexadecimal(InstructionCode bitField, char * filename) {
    /* Write on a file */
    printf("%d\t%d\t%d\n%d\t%d\t%d\n%d\t%d\t%d\n%x\n\n",
        bitField.opCode,
        bitField.originAddress,
        bitField.originOperand,
        bitField.destAddress,
        bitField.destOperand,
        bitField.function,
        bitField.absolute,
        bitField.relocatable,
        bitField.external,
        bitField
    );
}
