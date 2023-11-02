/** main.c - Hello World demo 
 * 
 */

#include "main.h"
#include "duck2.h"

K_THREAD_STACK_DEFINE(threadDuck2_stack_area, STACKSIZE);
struct k_thread threadDuck2_data;

void threadDuck2(struct k_sem* main_sem, void *unused2, void *unused3) {
	ARG_UNUSED(unused2);
	ARG_UNUSED(unused3);

    int delay = 2;
    threadKernel(delay, &duck2_sem, main_sem, "duck");
}
