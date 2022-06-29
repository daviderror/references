obj-m += hello_world.o
obj-m += kthreads.o
obj-m += work_queue.o

# It is not good practis for kernel
CFLAGS_work_queue.o += -std=gnu99

# Do not print "Entering directory" on recursive make call if not verbose
MAKEFLAGS += $(if $(value V),,--no-print-directory)

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

tidy:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

hello_world:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) hello_world.ko

kthreads:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) kthreads.ko

work_queue:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) work_queue.ko

# we link original clean to target named tidy
clean:
	-rm -rf .tmp_versions
	-rm -f modules.order .modules.order.cmd Module.symvers .Module.symvers.cmd
	-rm -f $(obj-m) $(obj-m:.o=.mod) $(obj-m:.o=.mod.o) $(obj-m:.o=.mod.c) .$(obj-m:.o=.mod.cmd)
	-rm -f $(addsuffix .cmd,$(addprefix .,$(obj-m)))
	-rm -f $(addsuffix .cmd,$(addprefix .,$(obj-m:.o=.ko)))
	-rm -f $(addsuffix .cmd,$(addprefix .,$(obj-m:.o=.mod.o)))