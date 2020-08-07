all: assembler

OBJS = assembler main.o first_iteration.o second_iteration.o label_chart.o declaration_commands.o functions.o error_report.o decode.o consts.o
OUT = assembler

assembler: main.o first_iteration.o second_iteration.o label_chart.o declaration_commands.o functions.o error_report.o decode.o consts.o
	gcc -o $(OBJS)

main.o: main.c main.h
	gcc -ansi -pedantic -Wall -c main.c

first_iteration.o: ./src/FirstIteration/first_iteration.c ./src/FirstIteration/first_iteration.h
	gcc -ansi -pedantic -Wall -c ./src/FirstIteration/first_iteration.c

second_iteration.o: ./src/SecondIteration/second_iteration.c ./src/SecondIteration/second_iteration.h
	gcc -ansi -pedantic -Wall -c ./src/SecondIteration/second_iteration.c

label_chart.o: ./src/LabelChart/label_chart.c ./src/LabelChart/label_chart.h
	gcc -ansi -pedantic -Wall -c ./src/LabelChart/label_chart.c

declaration_commands.o: ./src/LinkedListOfDataCommands/declaration_commands.c ./src/LinkedListOfDataCommands/declaration_commands.h
	gcc -ansi -pedantic -Wall -c ./src/LinkedListOfDataCommands/declaration_commands.c

functions.o: ./src/UtilFunctions/functions.c ./src/UtilFunctions/functions.h
	gcc -ansi -pedantic -Wall -c ./src/UtilFunctions/functions.c

error_report.o: ./src/ErrorReport/error_report.c ./src/ErrorReport/error_report.h
	gcc -ansi -pedantic -Wall -c ./src/ErrorReport/error_report.c

decode.o: ./src/Decode/decode.c ./src/Decode/decode.h
	gcc -ansi -pedantic -Wall -c ./src/Decode/decode.c

consts.o: ./src/Common/consts.c ./src/Common/common.h
	gcc -ansi -pedantic -Wall -c ./src/Common/consts.c

clean:
	rm -f $(OBJS) $(OUT)
