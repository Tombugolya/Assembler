#include "decode.h"

void decode_to_binary(int opCode, line_type type, addressing_modes first, ...) {
    if (type == CODE) {
        machineOperation test;
        test.opCode = opCode;
        test.originAddress = 0;
        test.originOperand = 0;
        test.destAddress = 0;
        test.destOperand = 0;
        test.function = 0;
        test.absolute = 0;
        test.relocatable = 0;
        test.external = 0;

        write_hexadecimal(test, "filename");
    } else if ( type == STRING ) {
        machineData test;
    } else { /* type == DATA { */

    }

}

void write_hexadecimal(machineOperation bitField, char * filename) {
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