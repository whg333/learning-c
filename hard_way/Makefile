CFLAGS=-Wall -g -std=c99

# 使用通配符来获取所有以.c为后缀的源文件
SRCS = $(wildcard *.c)

# 生成对应的可执行文件名列表
BINS = $(patsubst %.c, %, $(SRCS))

# 默认目标：编译所有源文件并生成对应的可执行文件
all: $(BINS)

ex22_main: ex22.o

# 使用模式规则来编译每个源文件
#%: %.c
#	$(CC) $(CFLAGS) -o $@ $<

# 清理目标：删除所有生成的可执行文件
clean:
	rm -f $(BINS) *.o *.a *.so
