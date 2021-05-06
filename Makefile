CFLAGS = -mavx2 --std=c++98 -O0 -Wall -m32

VERIFY ?= 0
COMMON_SRCS := MatrixMN.cpp main.cpp
EXECUTABLE := sse

sse : $(COMMON_SRCS)
	$(CC) $(CFLAGS) -DVERIFY=$(VERIFY) -D$@ -o $@ main.cpp

clean:
	$(RM) $(EXECUTABLE)