CXXFLAGS += -Wall -Werror -std=c++11

APP_NAME = goodApp
SOURCES = \
    src/IIoHandler.cpp \
    src/IIoDispatcher.cpp \
    src/IoDispatcherSelect.cpp \
    src/NamedPipeToStdout.cpp \
    src/main.cpp
OBJS_APP = $(SOURCES:.cpp=.o)

all: $(APP_NAME) badApp 

$(APP_NAME): $(OBJS_APP)
	$(CXX) $(CXXFLAGS) $(OBJS_APP) -o $@

.c.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

badApp: src/bad-main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(OBJS_APP) $(APP_NAME) badApp

.PHONY: clean
