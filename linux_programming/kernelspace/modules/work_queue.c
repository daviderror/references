#include <linux/kernel.h>
#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/jiffies.h> 
//#include <linux/kthread.h>
#include <linux/slab.h>
//#include <linux/sched.h>
#include <linux/workqueue.h> 

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Drakonof");
MODULE_DESCRIPTION("A fig_kmod aka work_queue demo");
MODULE_VERSION("0.01");

// Входные параметры модуля:

// если параметр доживет, что вряд ли для __initdata, то его можно почитать: sudo cat /sys/module/kthreads/parameters/fim_num тк S_IRUSR | S_IRGRP | S_IROTH позволяют это.
// __initdata разрешает удаления этой переменной из памяти после ее использования в инициализауции.
static unsigned long fib_num = 10; 

// Подобный макрос должен быть записан для каждого предусмотренного параметра и 
// должен последовательно определять: имя (параметра и переменной);тип значения этого параметра;
// права доступа (к параметру, отображаемому как путевое имя в системе /sys).
module_param(fib_num, ulong, S_IRUSR | S_IRGRP | S_IROTH);

// Описание параметра
MODULE_PARM_DESC(fib_num, "Ntf fibonacci number to calculate");

static unsigned long __initdata max_iter = 1;
module_param(max_iter, ulong, S_IRUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(max_iter, "Max number iteration within loop");

struct  fib_state {
	unsigned long last [2];
	unsigned long cur;
	unsigned long target;
	unsigned long max_iter_num;
};

struct my_work {
    struct work_struct work;
    struct fib_state *p_state;
};


// правильный вариант алокации и делокации
struct mod_allocs {
    u32 my_work : 1;
    u32 my_work_work : 1;
    u32 my_work_state : 1;
};

enum {
    INIT_RET_ERROR = 1
};

#define err_except(cond, label, message, ...) \
    do { bool tmp = (cond); \
        if (!(tmp)) \
        { \
                pr_err(#cond " failed: " message " \n", ##__VA_ARGS__); \
                goto label; \
        } \
    } while (0)

static struct mod_allocs mod_all = {};

static struct my_work *p_wrk = NULL;

static void mod_dealloc(void) {
    if (true == mod_all.my_work_state) {
        pr_info("fib_kmod: dealloc state");
        kfree(p_wrk->p_state);
    }

    if (true == mod_all.my_work) {
        pr_info("fib_kmod: dealloc work");
        kfree(p_wrk);
    }
}

static bool fib_init(struct fib_state *p_state, unsigned long target_cnt, unsigned long max_iter) {
     if ((NULL == p_state) || (0 == target_cnt) || (0 == max_iter)) {
         return false;
     }

     *p_state = (struct fib_state) {
     	.last = {0, 1},
     	.cur = 0,
     	.target = target_cnt,
     	.max_iter_num = max_iter
     };

     pr_info("fib_kmod: fib_init");

     return true;
}

static unsigned long fib_result(struct fib_state *p_state) {

	return p_state->last[0];
}

static bool fib_iter(struct fib_state *p_state) {
    for (unsigned long i = 0; i < p_state->max_iter_num; i++) {
        if (p_state->cur == p_state->target) {
        	return true;
        }

        unsigned long tmp = p_state->last[1];
        p_state->last[1] = p_state->last[0] + p_state->last[1];
        p_state->last[0] = tmp;

        p_state->cur++;
    }

    return false;
}

void my_work_func(struct work_struct *w) {
    pr_info("fib_kmod: work run @ %lu", jiffies);

    // получить данные из queue
    struct my_work *wr = container_of(w, struct my_work, work);
    
    if(!fib_iter(wr->p_state)) {
        schedule_work(w);
    }
    
}



static int __init fib_kmod_init( void ) { 
    pr_info("fib_kmod: init run @ %lu", jiffies);

    pr_info("fib_kmod: parameters fib_num: %lu, max_iter: %lu\n", fib_num, max_iter);

    err_except((0 != max_iter) && (fib_num >= 0), init_error, "max_iter and fib_num error\n" );

    err_except(NULL != (p_wrk = kmalloc(sizeof (*p_wrk), GFP_KERNEL)), init_error, "p_wrk alloc error\n");
         
    
    pr_info("fib_kmod: alloc work");
    mod_all.my_work = true;
    

    err_except(NULL != (p_wrk->p_state = kmalloc(sizeof (*p_wrk->p_state ), GFP_KERNEL)), init_error, "state alloc error\n");

    pr_info("fib_kmod: alloc state");
    mod_all.my_work_state = true;
    
    err_except(fib_init(p_wrk->p_state, fib_num, max_iter), init_error, "fib_init error\n");

    INIT_WORK(&p_wrk->work, &my_work_func);
    schedule_work(&p_wrk->work);

    return 0; 
 
    init_error:
        mod_dealloc();
        return INIT_RET_ERROR;
}

static void __exit fib_kmod_exit( void ) { 

    flush_scheduled_work(); 
    pr_notice("fib_kmod: fibonacci result(%lu %lu)", p_wrk->p_state->cur, fib_result(p_wrk->p_state));
    mod_dealloc();
} 

module_init(fib_kmod_init);  
module_exit(fib_kmod_exit);