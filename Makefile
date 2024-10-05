CXX=g++
CXXFLAGS=-Wall -Werror

REDIS_SRCS = src/redis_main.cpp
REDIS_OBJS = $(REDIS_SRCS:.cpp=.o)

CLIENT_SRCS = src/client_main.cpp
CLIENT_OBJS = $(CLIENT_SRCS:.cpp=.o)

REDIS_TARGET = redis_main
CLIENT_TARGET = client_main

all: redis client

redis: $(REDIS_TARGET)

client: $(CLIENT_TARGET)

# Rule to build the redis executable
$(REDIS_TARGET): $(REDIS_OBJS)
	$(CXX) $(CXXFLAGS) $(REDIS_OBJS) -o $(REDIS_TARGET)

# Rule to build the client executable
$(CLIENT_TARGET): $(CLIENT_OBJS)
	$(CXX) $(CXXFLAGS) $(CLIENT_OBJS) -o $(CLIENT_TARGET)

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(REDIS_OBJS) $(REDIS_TARGET) $(CLIENT_OBJS) $(CLIENT_TARGET)