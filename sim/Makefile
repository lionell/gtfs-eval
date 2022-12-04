all: run

run: main.cc evaluator.o schedule.o time.o csv.o
	@g++ -o run evaluator.o schedule.o time.o csv.o main.cc

schedule.o: schedule.cc schedule.h
	@g++ -c schedule.cc

evaluator.o: evaluator.cc evaluator.h
	@g++ -c evaluator.cc

time.o: time.cc time.h
	@g++ -c time.cc

csv.o: csv.cc csv.h
	@g++ -c csv.cc

clean:
	@rm -rf *.o run
