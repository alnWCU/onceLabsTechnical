
K_SEM_DEFINE(duck1_sem, 1, 1);	/* starts as "available" */

//extern struct k_thread_stack_t threadDuck1_stack_area;
//extern struct k_thread threadDuck1_data;

void threadDuck1(struct k_sem* main_sem, void *unused2, void *unused3);
