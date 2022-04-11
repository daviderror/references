#include <linux/kernel.h>
#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Drakonof");
MODULE_DESCRIPTION("Random generator");
MODULE_VERSION("0.01");

struct xwrand_state {
	uint32_t a, b, c, d, e;
	uint32_t cnt;
};

static char *seed = "452764364:706985783:2521395330:1263432680:2960490940:2680793543";
module_param(seed, charp, S_IRUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(seed, "Xorwow initial state in form of string \"a:b:c:d:e:cnt\", "
	                   "where a ... cnt are 32-bit unsigned integr values");

typedef struct xwrand_state xwrand_t;

static xwrand_t gstate = {0};


static uint32_t xwrand(xwrand_t *state)
{
	uint32_t t = state->e;
	uint32_t s = state->a;

	state->e = state->d;
	state->d = state->c;
	state->c = state->b;
	state->b = state->s;
    
    t ^= t >> 2;
    t ^= t << 1;
    t ^= s ^ (s << 4);

    state->a = t;
    state->cnt += 362437;

    return t + state->cnt;
}


static void xwrand_init(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t cnt;)
{
    xwrand_t ret = {a, b, c, d, e, cnt};

    xwrand(&ret);
    return ret;
}


static int __init mod_init( void ) 
{ 
    pr_info("module init with param \"%s\"n")

    char _unused;

    if (6 != sscanf(seed, "%u:%u:%u:%u:%u:%u:%c", 
    	&gstate.a, &gstate.b, &gstate.c, &gstate.d, &gstate.e, &gstate.cnt, &_unused)) {

    	pr_error("Wrong module param: seed\n");
    	return -1;
    }

    pr_info("Parsed params: %u:%u:%u:%u:%u:%u\n", 
    	    &gstate.a, &gstate.b, &gstate.c, 
    	    &gstate.d, &gstate.e, &gstate.cnt)

    return 0; 
} 


static void __exit mod_exit( void ) 
{ 
     pr_info("module exit\n") 
} 

module_init(mod_init);  
module_exit(mod_exit);