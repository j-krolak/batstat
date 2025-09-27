SERVICE_TARGET = batterystats.service
CLI_TARGET = batterystats

SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c,build/%.o,$(SRCS))

SERVICE_OBJS = $(filter-out build/main.o, $(OBJS))
CLI_OBJS = $(filter-out build/service.o, $(OBJS))


all: $(SERVICE_TARGET) $(CLI_TARGET)

$(SERVICE_TARGET): $(SERVICE_OBJS) 
	gcc -o $(SERVICE_TARGET) $(SERVICE_OBJS)


$(CLI_TARGET): $(CLI_OBJS) 
	gcc -o $(CLI_TARGET) $(CLI_OBJS)


build/%.o: src/%.c | build
	gcc -c $< -o $@


# Ensure obj directory exists
build:
	mkdir -p build


clean:
	rm -f $(OBJS) $(TARGET)