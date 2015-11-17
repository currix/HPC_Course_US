/* see http://blog.regehr.org/archives/330 */

typedef unsigned long long ticks;

static __inline__ ticks ticks_start (void) {
  unsigned cycles_low, cycles_high;
  asm volatile ("CPUID\n\t"
		"RDTSC\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
		"%rax", "%rbx", "%rcx", "%rdx");
  return ((ticks)cycles_high << 32) | cycles_low;
}

static __inline__ ticks ticks_stop (void) {
  unsigned cycles_low, cycles_high;
  asm volatile("RDTSCP\n\t"
	       "mov %%edx, %0\n\t"
	       "mov %%eax, %1\n\t"
	       "CPUID\n\t": "=r" (cycles_high), "=r" (cycles_low):: "%rax",
	       "%rbx", "%rcx", "%rdx");
  return ((ticks)cycles_high << 32) | cycles_low;
}
