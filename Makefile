all: assembler
OBJ_LOC = ./Objects/
OBJS = assembler $(OBJ_LOC)main.o $(OBJ_LOC)first_iteration.o $(OBJ_LOC)second_iteration.o $(OBJ_LOC)label_chart.o $(OBJ_LOC)declaration_commands.o $(OBJ_LOC)functions.o $(OBJ_LOC)error_report.o $(OBJ_LOC)decode.o $(OBJ_LOC)consts.o
CC = gcc
FLAGS = -ansi -pedantic -Wall
assembler: $(OBJ_LOC)main.o $(OBJ_LOC)first_iteration.o $(OBJ_LOC)second_iteration.o $(OBJ_LOC)label_chart.o $(OBJ_LOC)declaration_commands.o $(OBJ_LOC)functions.o $(OBJ_LOC)error_report.o $(OBJ_LOC)decode.o $(OBJ_LOC)consts.o
	gcc -o $(OBJS)

$(OBJ_LOC)main.o: main.c main.h
	$(CC) $(FLAGS) -o $@ -c main.c

$(OBJ_LOC)first_iteration.o: ./src/FirstIteration/first_iteration.c ./src/FirstIteration/first_iteration.h
	$(CC) $(FLAGS) -o $@ -c ./src/FirstIteration/first_iteration.c

$(OBJ_LOC)second_iteration.o: ./src/SecondIteration/second_iteration.c ./src/SecondIteration/second_iteration.h
	$(CC) $(FLAGS) -o $@ -c ./src/SecondIteration/second_iteration.c

$(OBJ_LOC)label_chart.o: ./src/LabelChart/label_chart.c ./src/LabelChart/label_chart.h
	$(CC) $(FLAGS) -o $@ -c ./src/LabelChart/label_chart.c

$(OBJ_LOC)declaration_commands.o: ./src/LinkedListOfDataCommands/declaration_commands.c ./src/LinkedListOfDataCommands/declaration_commands.h
	$(CC) $(FLAGS) -o $@ -c ./src/LinkedListOfDataCommands/declaration_commands.c

$(OBJ_LOC)functions.o: ./src/UtilFunctions/functions.c ./src/UtilFunctions/functions.h
	$(CC) $(FLAGS) -o $@ -c ./src/UtilFunctions/functions.c

$(OBJ_LOC)error_report.o: ./src/ErrorReport/error_report.c ./src/ErrorReport/error_report.h
	$(CC) $(FLAGS) -o $@ -c ./src/ErrorReport/error_report.c

$(OBJ_LOC)decode.o: ./src/Decode/decode.c ./src/Decode/decode.h
	$(CC) $(FLAGS) -o $@ -c ./src/Decode/decode.c

$(OBJ_LOC)consts.o: ./src/Common/consts.c ./src/Common/common.h
	$(CC) $(FLAGS) -o $@ -c ./src/Common/consts.c

clean:
	rm -f $(OBJS)
