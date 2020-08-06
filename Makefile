OBJS	= main.o src/UtilFunctions/functions.o src/LinkedListOfDataCommands/declaration_commands.o src/LabelChart/label_chart.o src/FirstIteration/first_iteration.o src/ErrorReport/error_report.o src/Decode/decode.o src/Common/consts.o
SOURCE	= main.c src/UtilFunctions/functions.c src/LinkedListOfDataCommands/declaration_commands.c src/LabelChart/label_chart.c src/FirstIteration/first_iteration.c src/ErrorReport/error_report.c src/Decode/decode.c src/Common/consts.c
HEADER	= main.h src/UtilFunctions/functions.h src/LinkedListOfDataCommands/declaration_commands.h src/LabelChart/label_chart.h src/FirstIteration/first_iteration.h src/ErrorReport/error_report.h src/Decode/decode.h src/Common/common.h
OUT	= compiler
CC	 = gcc
FLAGS	 = -g -Wall -ansi -pedantic

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c 

src/UtilFunctions/functions.o: src/UtilFunctions/functions.c
	$(CC) $(FLAGS) src/UtilFunctions/functions.c 

src/LinkedListOfDataCommands/declaration_commands.o: src/LinkedListOfDataCommands/declaration_commands.c
	$(CC) $(FLAGS) src/LinkedListOfDataCommands/declaration_commands.c 

src/LabelChart/label_chart.o: src/LabelChart/label_chart.c
	$(CC) $(FLAGS) src/LabelChart/label_chart.c 

src/FirstIteration/first_iteration.o: src/FirstIteration/first_iteration.c
	$(CC) $(FLAGS) src/FirstIteration/first_iteration.c 

src/ErrorReport/error_report.o: src/ErrorReport/error_report.c
	$(CC) $(FLAGS) src/ErrorReport/error_report.c 

src/Decode/decode.o: src/Decode/decode.c
	$(CC) $(FLAGS) src/Decode/decode.c 

src/Common/consts.o: src/Common/consts.c
	$(CC) $(FLAGS) src/Common/consts.c 


clean:
	rm -f $(OBJS) $(OUT)