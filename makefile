EXE = vend
OBJ = vendingMachine.o main.o
C= g++
F= -Wall -g -MMD

$(EXE): $(OBJ)
	$(C) $(F) $(OBJ) -o $(EXE)

%.o: %.cpp
	$(C) $(F) -c $<

-include $(OBJ:.o=.d)

.PHONY: clean

clean:
	rm *.o
	rm *.d
