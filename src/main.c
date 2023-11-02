/**
 * main.c
 */

#include "main.h"

K_SEM_DEFINE(mainThread_sem, 0, 1);

K_THREAD_STACK_DEFINE(mainThread_stack_area, STACKSIZE);
static struct k_thread mainThread_data;

void threadKernel(int delay, struct k_sem* my_sem, struct k_sem* main_sem, char* selfStr) {
	//struct k_thread *current_thread;
	while (1) {
		k_sem_take(my_sem, K_FOREVER);

        uint32_t timeout = sys_rand32_get();
        k_msleep(delay * 1000 + (1000 * (timeout / (double) INT_MAX)));

        printk("%s\n", selfStr);
		k_sem_give(main_sem);
	}
}

void mainThreadKernel() {
    while (1) {
        k_sem_take(&mainThread_sem, K_FOREVER);
        k_sem_give(&duck1_sem);
        k_sem_take(&duck2_sem, K_FOREVER);
        k_sem_take(&mainThread_sem, K_FOREVER);
        k_sem_give(&duck2_sem);
        k_sem_take(&goose_sem, K_FOREVER);
        k_sem_take(&mainThread_sem, K_FOREVER);
        k_sem_give(&goose_sem);
        k_sem_take(&duck1_sem, K_FOREVER);
    }
}

int main(void) {
    // spawn main thread
	k_thread_create(&mainThread_data, mainThread_stack_area,
			K_THREAD_STACK_SIZEOF(mainThread_stack_area),
			mainThreadKernel, NULL, NULL, NULL,
			PRIORITY, 0, K_FOREVER);
	k_thread_name_set(&mainThread_data, "main_thread");
#if PIN_THREADS
	if (arch_num_cpus() > 3) {
		k_thread_cpu_pin(&mainThread_data, 0);
	}
#endif

	k_thread_create(&threadDuck1_data, threadDuck1_stack_area,
			K_THREAD_STACK_SIZEOF(threadDuck1_stack_area),
			threadDuck1, &mainThread_sem, NULL, NULL,
			PRIORITY, 0, K_FOREVER);
	k_thread_name_set(&threadDuck1_data, "Duck1_thread");
#if PIN_THREADS
	if (arch_num_cpus() > 3) {
		k_thread_cpu_pin(&threadDuck1_data, 1);
	}
#endif

	k_thread_create(&threadDuck2_data, threadDuck2_stack_area,
			K_THREAD_STACK_SIZEOF(threadDuck2_stack_area),
			threadDuck2, &mainThread_sem, NULL, NULL,
			PRIORITY, 0, K_FOREVER);
	k_thread_name_set(&threadDuck2_data, "Duck2_thread");
#if PIN_THREADS
	if (arch_num_cpus() > 3) {
		k_thread_cpu_pin(&threadDuck2_data, 2);
	}
#endif

	k_thread_create(&threadGoose_data, threadGoose_stack_area,
			K_THREAD_STACK_SIZEOF(threadGoose_stack_area),
			threadGoose, &mainThread_sem, NULL, NULL,
			PRIORITY, 0, K_FOREVER);
	k_thread_name_set(&threadGoose_data, "Goose_thread");
#if PIN_THREADS
	if (arch_num_cpus() > 3) {
		k_thread_cpu_pin(&threadGoose_data, 3);
	}
#endif

	k_thread_start(&threadDuck1_data);
	k_thread_start(&threadDuck2_data);
	k_thread_start(&threadGoose_data);
	k_thread_start(&mainThread_data);
	return 0;
}
