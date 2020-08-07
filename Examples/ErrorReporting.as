; Comma errors and warnings

Label1: .extern Label2
.extern xdHH :
.string "Str
.data  1, -2,+3 , 4 ,5 6,
HI: .string "Good String"
    .string "Extra Character after quotations";
    .string Whoops missed quotation"
HI: .string "Non unique label"
ColonFarAway : .string "hi2"
mov r1 r2

; Comments Comments Comments!

; Wrong operands
mov hi, #1
LABEL3: mov &hi, #1
LABEL4: clr
mov r1, r2, r3
bne r2
mov 2, 3
clr #-2, 2

; Labels
VERYVERYVERYVERYVERYVERYVERYVERYVERYLONGLABEL: stop
123HI: stop
string: stop