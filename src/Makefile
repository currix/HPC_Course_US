#USE_DOUBLE = 1

# optimization settings 
OPT=-O3 -ftree-vectorize -ffast-math -funroll-loops
#OPT=-O3 -funroll-loops  
#OPT=-O3
#INFO=-fopt-info-vec-missed -fopt-info-vec-optimized
#INFO=-fopt-info-vec-optimized
INFO=-fopt-info-all

# MP settings
MPFLAGS=-fopenmp

## SCALE and MANDEL can be passed as command line args
#ifndef SCALE
#SCALE = scale1
#endif

TYPE_DEF = -DPREC=DP 
ifdef USE_SIMPLE
TYPE_DEF = -DPREC=SP 
endif

# this should require little changes
ARCH=-march=native
FC=gfortran
FPP=cpp
FFLAGS=$(ARCH)
LDFLAGS=-lm
OPTFFLAGS=$(OPT) $(ARCH)
OPTFFLAGS1="\"$(OPT) $(ARCH)\""

all: iteratef teamcake_CPB test_vectorize

.FORCE:	

test_vectorize:	test_vectorize.f90 Makefile
	$(FC) $(OPT) $(ARCH) $(INFO) $(LDFLAGS) -o $@ $<

teamcake_CPB:	teamcake_CPB.f90 Makefile .FORCE teamcake_CPB.lst
	$(FC) $(OPTFLAGS) $(INFO) $(LDFLAGS) $(MPFLAGS) -o $@ $<

teamcake_CPB.lst:	teamcake_CPB.f90 Makefile
	$(FC) -c -g -Wa,-a,-ad $(OPTFFLAGS) $(INFO) $(MPFLAGS) $< > $@

iteratef:	iterate.f90 scale.f90 Makefile .FORCE  scale.lst
	$(FPP) -std=c89 $(TYPE_DEF) -DFLAGS=$(OPTFFLAGS1) $< > /tmp/$<
	$(FPP) -std=c89 $(TYPE_DEF) -DFLAGS=$(OPTFFLAGS1) scale.f90 > /tmp/scale.f90
	$(FC) $(OPTFFLAGS) $(LDFLAGS) $(INFO) -o $@ /tmp/scale.f90 /tmp/$<

scale.lst:	iterate.f90 scale.f90 Makefile
	$(FPP) -std=c89 $(TYPE_DEF) -DFLAGS=$(OPTFFLAGS1) $< > /tmp/$<
	$(FPP) -std=c89 $(TYPE_DEF) -DFLAGS=$(OPTFFLAGS1) scale.f90 > /tmp/scale.f90
	$(FC) -c -g -Wa,-a,-ad $(OPTFFLAGS) /tmp/scale.f90 /tmp/$< > $@

clean:	
	rm -f *.o *.s *.exe *.lst *.ppm iteratef test_vectorize teamcake_CPB
