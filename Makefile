TARGET = batstat

EXEC_PATH = /usr/bin
CONFIG_DIR = /etc/batstat
UNIT_DIR =/etc/systemd/system
DATA_DIR =/var/log/batstat

SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c,obj/%.o,$(SRCS))

all:  install | $(TARGET)

$(TARGET): $(OBJS) 
	gcc -o $(TARGET) $(OBJS)

obj/%.o: src/%.c | obj
	gcc -c $< -o $@

# Ensure obj directory exists
obj:
	mkdir -p obj

install:
	install -Dm755 data/config.conf $(DESTDIR)$(CONFIG_DIR)/config.conf
	mkdir -p $(DESTDIR)$(DATA_DIR)
	install -Dm755 data/batstat.service $(DESTDIR)$(UNIT_DIR)/batstat.service
	install -Dm755 $(TARGET) $(DESTDIR)$(EXEC_PATH)/$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)