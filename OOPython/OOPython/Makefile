SRCS = Analyzer.cpp Block.cpp Buildin.cpp Client.cpp Container.cpp Data.cpp Expression.cpp Function.cpp Varmap.cpp main.cpp
OBJS = ${SRCS:.cpp=.o}
CFLAGS = -O2 -std=c++11
CC = g++

all: python

python : ${OBJS}
	$(CC) ${CFLAGS} ${OBJS} -o python

.PHONY : clean
clean :
	-rm ${OBJS} *.d python

%.d : %.cpp
	${CC} -MM ${CFLAGS} $< > $@
	sed -i '1s/^/$@ /' $@
	
%.o: %.cpp
	${CC} -c ${CFLAGS} $<
	
-include ${SRCS:.cpp=.d}