#!/usr/bin/python
#
#
import numpy as np
import time
#
###########################################################
def exact_val(a_val, Iterat, N_val, vb_vec):
    #
    return a_val**Iterat*np.linspace(0,N_val-1,N_val)*0.25 + vb_vec*(a**Iterat-1)/(a-1)
###########################################################
#
N1 = 64
Iter = 100000000
a = 1.0 + 1.0e-8
FLOP = (Iter*2.0)*N1
#
# Initialize va and vb
va = np.linspace(0,N1-1,N1)/4
vb = np.linspace(0,N1-1,N1)
#
count = 0
#
start = time.clock() # Start Timing
#
while (count<Iter):
    va = va*a+vb
    count += 1
#
end = time.clock()
#
time_elapsed =  end - start
#
exact_value = exact_val(a, Iter, N1, vb)
error = np.abs(va[1:] - exact_value[1:])/exact_value[1:]
#
np.set_printoptions(precision=10)
#print repr(va[1:])
#print repr(exact_value[1:])
print repr(error)
print "%.6e"  % (FLOP/time_elapsed)
print "%.6e"  % (1.0/time_elapsed)
#
