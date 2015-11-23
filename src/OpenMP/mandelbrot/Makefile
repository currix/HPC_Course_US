CFLAGS=-Wall
#OPTFLAGS=-O3 -ffast-math 
OPTFLAGS=-O3	
#OPTFLAGS=-Ofast
ARCH= -march=native
LDLIBS=-lrt
all:	mandelbrot mandelomp mandelomp_2 mandelomp_3 mandelomp_4
mandelomp:	mandelomp.c ppm_soa.o timing.o Makefile
	$(CC) $(CFLAGS) $(OPTFLAGS) $(ARCH) -fopenmp -o $@ $< $(LDLIBS) timing.o ppm_soa.o
mandelomp_1:	mandelomp_1.c ppm_soa.o timing.o Makefile
	$(CC) $(CFLAGS) $(OPTFLAGS) $(ARCH) -fopenmp -o $@ $< $(LDLIBS) timing.o ppm_soa.o
mandelomp_2:	mandelomp_2.c ppm_soa.o timing.o Makefile
	$(CC) $(CFLAGS) $(OPTFLAGS) $(ARCH) -fopenmp -o $@ $< $(LDLIBS) timing.o ppm_soa.o
mandelomp_3:	mandelomp_3.c ppm_soa.o timing.o Makefile
	$(CC) $(CFLAGS) $(OPTFLAGS) $(ARCH) -fopenmp -o $@ $< $(LDLIBS) timing.o ppm_soa.o
mandelomp_4:	mandelomp_4.c ppm_soa.o timing.o Makefile
	$(CC) $(CFLAGS) $(OPTFLAGS) $(ARCH) -fopenmp -o $@ $< $(LDLIBS) timing.o ppm_soa.o
mandelbrot:	mandelbrot.c timing.o ppm_soa.o Makefile
	$(CC) $(CFLAGS) $(OPTFLAGS) $(ARCH) -o $@ $< $(LDLIBS) timing.o ppm_soa.o
clean:
	rm -f *.o *.ppm *.exe mandelbrot  mandelomp mandelomp_1 mandelomp_2 mandelomp_3 mandelomp_4
