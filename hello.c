#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include <linux/ktime.h>
#include <linux/slab.h>

MODULE_AUTHOR("Timur Gereihanov <simplex1135@gmail.com>");
MODULE_DESCRIPTION("Lab5 AK");
MODULE_LICENSE("Dual BSD/GPL");

static uint howmany = 1;

module_param(howmany, uint, 0444);
MODULE_PARM_DESC(howmany, "Number of prints");

struct my_struct {
    struct list_head tlist;
    ktime_t time;
};

static LIST_HEAD(my_list_head);

static int __init hello_init(void)
{

    if (howmany == 0) {
		pr_warn("The parameter is 0");
    } else if (howmany >= 5 && howmany <= 10) {
		pr_warn("The parameter is in [5; 10]");
    } else if (howmany > 10) {
		pr_err("The parameter is > 10)");
		return -EINVAL;
    }

    int i;
	for (i = 0; i < howmany; i++) {

		struct my_struct *ms = NULL;

		ms = kmalloc(sizeof(struct my_struct), GFP_KERNEL);
		ms->time = ktime_get();
		list_add_tail(&ms->tlist, &my_list_head);

		pr_info("Hello, world!\n");
    }

    return 0;
}

static void __exit hello_exit(void)
{
    int count = 0;
    struct my_struct *t, *tmp;

    if (ZERO_OR_NULL_PTR(&my_list_head))
    	return 0;

    list_for_each_entry_safe(t, tmp, &my_list_head, tlist) {
		pr_info("i: %d; ktime = %lld\n", count++, ktime_to_ns(t->time));
		list_del(&t->tlist);
		kfree(t);
    }
    pr_info("Module unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);
