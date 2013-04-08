CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		mongotest.o

LIBS = -pthread -lmongoclient -lboost_thread-mt -lboost_filesystem -lboost_program_options -lboost_system

TARGET =	mongotest

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS) 

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
