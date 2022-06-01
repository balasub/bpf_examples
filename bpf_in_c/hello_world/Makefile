CLANG = clang

KERNEL_DIR = /usr/src/linux-source-5.4.0/linux-source-5.4.0
BPFTOOLS   = ${KERNEL_DIR}/samples/bpf
BPFLOADER  = $(BPFTOOLS)/bpf_load.c

CCINCLUDE   += -I${KERNEL_DIR}/tools/testing/selftests/bpf

LOADINCLUDE += -I${KERNEL_DIR}/samples/bpf
LOADINCLUDE += -I${KERNEL_DIR}/tools/lib
LOADINCLUDE += -I${KERNEL_DIR}/tools/perf
LOADINCLUDE += -I${KERNEL_DIR}/tools/include

LIBRARY_PATH = -L/usr/local/lib64

BPFSO = -lbpf

EXECUTABLE = load_bpf
BPFCODE    = hello_bpf

# Set -DHAVE_ATTR_TEST=0 for the kernel containing below patch:
# 06f84d1989b7 perf tools: Make usage of test_attr__* optional for perf-sys.h
#
# The patch was included in Linus's tree starting v5.5-rc1, but was also included
# in stable kernel branch linux-5.4.y. So it's hard to determine whether a kernel
# is affected based on the kernel version alone:
# - for a v5.4 kernel from Linus's tree, no;
# - for a v5.4 kernel from the stable tree (used by many distros), yes.
#
# So let's look at the actual kernel source code to decide.
#
# See more context at:
# https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=06f84d1989b7e58d56fa2e448664585749d41221
# https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=fce9501aec6bdda45ef3a5e365a5e0de7de7fe2d
CFLAGS += $(shell grep -q "define HAVE_ATTR_TEST 1" ${KERNEL_DIR}/tools/perf/perf-sys.h \
                  && echo "-DHAVE_ATTR_TEST=0")

.PHONY : clean $(CLANG) bpfload build

clean :
	rm -f *.o *.so $(EXECUTABLE)

build : ${BPFCODE.c} ${BPFLOADER}
	$(CLANG) -O2 -target bpf -c $(BPFCODE:=.c) $(CCINCLUDE) -o ${BPFCODE:=.o}

bpfload : build
	clang $(CFLAGS) -o $(EXECUTABLE) -lelf $(LOADINCLUDE) $(LIBRARY_PATH) $(BPFSO) \
        $(BPFLOADER) loader.c

$(EXECUTABLE) : bpfload

.DEFAULT_GOAL := $(EXECUTABLE)
