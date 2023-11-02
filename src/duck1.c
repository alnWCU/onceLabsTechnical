/** main.c - Hello World demo 
 * 
 */

#include "main.h"
#include "duck1.h"

K_THREAD_STACK_DEFINE(threadDuck1_stack_area, STACKSIZE);
struct k_thread threadDuck1_data;

void threadDuck1(struct k_sem* main_sem, void *unused2, void *unused3) {
	ARG_UNUSED(unused2);
	ARG_UNUSED(unused3);

    int delay = 1;
    threadKernel(delay, &duck1_sem, main_sem, "duck");
}
