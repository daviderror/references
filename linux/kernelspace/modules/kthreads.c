#include <linux/kernel.h>
#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/kthread.h>
#include <linux/slab.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Drakonof");
MODULE_DESCRIPTION("A thread demo");
MODULE_VERSION("0.01");

// если параметр доживет то его можно почитать: sudo cat /sys/module/kthreads/parameters/thread_cnt тк S_IRUSR | S_IRGRP | S_IROTH позволяют это.
// __initdata разрешает удаления этой переменной из памяти после ее использования в инициализауции.
static unsigned long __initdata thread_cnt = 0; 

// Подобный макрос должен быть записан для каждого предусмотренного параметра и 
// должен последовательно определять: имя (параметра и переменной);тип значения этого параметра;
// права доступа (к параметру, отображаемому как путевое имя в системе /sys).
module_param(thread_cnt, ulong, S_IRUSR | S_IRGRP | S_IROTH);

// Описание параметра
MODULE_PARM_DESC(thread_cnt, "Parameter to the thread");     

static struct task_struct *p_thread_hnd = NULL;


static int thread_func(void *p_data) 
{
    set_current_state(TASK_UNINTERRUPTIBLE);

    typeof(thread_cnt) *p_par = p_data; // получает значение thread_cnt из памяти
    pr_info("kthreads: Thread started with param %lld\n", (long long int) *p_par);

    kfree(p_par); // удаляет p_par и parama из thread_init
    
    while (!kthread_should_stop()) {
       // переключение планировщика на другую задачу, нужно просто для иммитации работы цикла
       schedule();
    }

    pr_info("kthreads: Thread stoped\n");
    
    return 0;
}


static int __init thread_init( void ) 
{ 
    pr_info("kthreads: %s\n", module_name(THIS_MODULE));
    // тк поток запускается на много позже чем создается переменная, то thread_cnt может уже не существовать
    // поэтому её значения копируются в память (со слов автора урока). ЧТО ЭТО ЗНАЧИТ ХЗ, НУЖНО РАЗОБРАТЬСЯ
   
    typeof(thread_cnt) *p_param = kmalloc(sizeof(*p_param), GFP_KERNEL);
    *p_param = thread_cnt;
    p_thread_hnd = kthread_run(&thread_func, p_param, "kthreads: %s-thread-%d", module_name(THIS_MODULE), 0);
    
    if (IS_ERR(p_thread_hnd)) {
        pr_err("kthreads: A thread creation error -%s\n",
                 PTR_ERR(p_thread_hnd) == -ENOMEM ? "ENOMEM" : "EINTR");

        p_thread_hnd = NULL;
    }

    return 0; 
} 


static void __exit thread_exit( void ) 
{ 
       char thread_name [TASK_COMM_LEN] = {};

    if (NULL == p_thread_hnd) {
        pr_err("kthreads: error!");
    }

    get_task_comm(thread_name, p_thread_hnd);
    pr_info("kthreads: Thread %s was stoped\n", thread_name);
    kthread_stop(p_thread_hnd);

    pr_info("kthreads: Goodbye, kernel!\n");
} 

module_init(thread_init);  
module_exit(thread_exit);