OBJECTS = Main.o Term.o Autocomplete.o
HEADERS = Term.h Autocomplete.h
AutocompleteProg: $(OBJECTS)
	g++ $^ -o AutocompleteProg
%.o: %.cpp $(HEADERS)
	g++ -c $< -o $@
clean:
	rm -i *.o AutocompleteProg