# specify architecture specific settings here 
ARCH=-march=native 
#OPT=-O3 -ftree-vectorize -ffast-math -ftree-vectorizer-verbose=2
OPT=-O1 -Wall
#INFO=-fopt-info-vec-missed
# CC = icc
CC = gcc
CFLAGS=-std=gnu99 $(OPT) $(ARCH)

all: test_util test_ppm1 test_ppm2 test_ppm3

test_util:      test_util.c sysinfo.c timing.c Makefile
	$(CC) $(CFLAGS) -o test_util test_util.c sysinfo.c timing.c

test_ppm1:	test_ppm1.c ppm.o Makefile
	$(CC) $(CFLAGS) $< ppm.o -o $@

test_ppm2:	test_ppm2.c ppm_aos.o Makefile
	$(CC) $(CFLAGS) $< ppm_aos.o -o $@

test_ppm3:	test_ppm3.c ppm_soa.o Makefile
	$(CC) $(CFLAGS) $< ppm_soa.o -o $@

clean:	
	rm -f *.o *.exe *.ppm test_util test_ppm1 test_ppm2 test_ppm3

