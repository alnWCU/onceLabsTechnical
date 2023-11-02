/** goose.c - Hello World demo 
 * 
 */

#include "main.h"
#include "goose.h"

K_THREAD_STACK_DEFINE(threadGoose_stack_area, STACKSIZE);

void threadGoose(struct k_sem* main_sem, void *unused2, void *unused3) {
	ARG_UNUSED(unused2);
	ARG_UNUSED(unused3);

    int delay = 3;
    threadKernel(delay, &goose_sem, main_sem, "goose");
}
