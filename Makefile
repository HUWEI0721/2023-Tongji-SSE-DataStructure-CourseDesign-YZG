# 获取所有子目录
SUBDIRS = $(wildcard */.)

# 默认目标
all: $(SUBDIRS)

# 调用每个子目录的Makefile
$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: all $(SUBDIRS)

