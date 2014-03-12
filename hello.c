#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>

int foo()
{
	return 3;
}

main()
{
	int x, i;
	void* page;

	x = foo();
	printf("foo returned: %d\n", x);
	printf("Before\n");
	for (i = 0; i < 15; i++) {
		printf("%p: %02x\n", &((uint8_t*)foo)[i], ((uint8_t*)foo)[i]);
	}
	page = (void*)((uint64_t)foo & ~(getpagesize()-1));
	if(mprotect(page, getpagesize(), PROT_WRITE|PROT_READ|PROT_EXEC)) {
		perror("mprotect");
	}
	((uint8_t*)foo)[5] = 42;
	printf("After\n");
	for (i = 0; i < 15; i++) {
		printf("%p: %02x\n", &((uint8_t*)foo)[i], ((uint8_t*)foo)[i]);
	}
	x = foo();
	printf("foo returned: %d\n", x);
}
