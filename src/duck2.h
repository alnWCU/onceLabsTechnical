
K_SEM_DEFINE(duck2_sem, 0, 1);	/* starts as "not available" */

//extern struct k_thread_stack_t threadDuck2_stack_area;
//extern struct k_thread threadDuck2_data;

void threadDuck2(struct k_sem* main_sem, void *unused2, void *unused3);
