CC = g++ -g
exe_file = run_wizard

$(exe_file): run_wizard.o catalog.o
	$(CC) run_wizard.o catalog.o -o $(exe_file)

run_wizard.o: run_wizard.cpp
	$(CC) -c run_wizard.cpp

catalog.o: catalog.cpp catalog.hpp
	$(CC) -c catalog.cpp

clean: 
	rm -rf *.o $(exe_file)
