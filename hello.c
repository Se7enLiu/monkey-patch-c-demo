#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>

int bar()
{
	return 42;
}

int foo()
{
	return 3;
}

void monkey_patch(void* old_function, void* new_function)
{
	void* page;

	page = (void*)((uint64_t)old_function & ~(getpagesize()-1));
	if(mprotect(page, getpagesize(), PROT_WRITE|PROT_READ|PROT_EXEC)) {
		perror("mprotect");
	}
	((uint8_t*)old_function)[0] = 0xeb; /* jmp */
	/*
	 * Number of bytes to jump relative to the eip which is 2 bytes past
	 * the address of this instruction. Cannot jump more than 128 bytes.
	 */
	((uint8_t*)old_function)[1] = new_function - old_function - 2;
}

main()
{
	int x, i;

	x = foo();
	printf("foo returned: %d\n", x);
	monkey_patch(foo, bar);
	x = foo();
	printf("foo returned: %d\n", x);
}
