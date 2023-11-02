/** main - Hello World demo 
 * 
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/random/random.h>

#define PIN_THREADS (IS_ENABLED(CONFIG_SMP) && IS_ENABLED(CONFIG_SCHED_CPU_MASK))

/* size of stack area used by each thread */
#define STACKSIZE 1024

/* scheduling priority used by each thread */
#define PRIORITY 7

//extern struct k_sem duck1_sem;
//extern struct k_sem duck2_sem;
//extern struct k_sem goose_sem;
//
//extern struct k_thread threadDuck1_data;
//extern struct k_thread threadDuck2_data;
//extern struct k_thread threadGoose_data;
//
//extern struct k_thread_stack_t threadDuck1_stack_area;
//extern struct k_thread_stack_t threadDuck2_stack_area;
//extern struct k_thread_stack_t threadGoose_stack_area;

extern void threadDuck1();
extern void threadDuck2();
extern void threadGoose();

#include "duck1.h"
#include "duck2.h"
#include "goose.h"

/*
 * The hello world demo has two threads that utilize semaphores and sleeping
 * to take turns printing a greeting message at a controlled rate. The demo
 * shows both the static and dynamic approaches for spawning a thread; a real
 * world application would likely use the static approach for both threads.
 */


/*
 * @param my_name      thread identification string
 * @param my_sem       thread's own semaphore
 * @param other_sem    other thread's semaphore
 */
void threadKernel(int delay, struct k_sem* my_sem, struct k_sem* main_sem, char* selfStr);
