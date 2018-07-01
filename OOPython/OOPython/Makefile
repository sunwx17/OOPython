SRCS = Analyzer.cpp Block.cpp Buildin.cpp Client.cpp Container.cpp Data.cpp Expression.cpp Function.cpp Varmap.cpp main.cpp
OBJS = ${SRCS:.cpp=.o}
CFLAGS = -O2 -Wall -std=c++11
CC = g++

all: main

main : ${OBJS}
	$(CC) ${CFLAGS} ${OBJS} -o main

.PHONY : clean
clean :
	-rm ${OBJS} *.d main

%.d : %.cpp
	${CC} -MM ${CFLAGS} $< > $@
	sed -i '1s/^/$@ /' $@
	
%.o: %.cpp
	${CC} -c ${CFLAGS} $<
	
-include ${SRCS:.cpp=.d}