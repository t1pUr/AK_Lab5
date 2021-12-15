#include <linux/init.h>
#include <linux/module.h>
#include <linux/ktime.h>
#include<linux/slab.h>

MODULE_AUTHOR(”Timur Gereihanov <simplex1135@gmail.com>”);
MODULE_DESCRIPTION(”Lab5 AK”);
MODULE_LICENSE(”Dual BSD/GPL”);


 uint hello_world_count = 1;
 module_param(hello_world_count, uint, 0660);
 MODULE_PARM_DESC(hello_world_count, ”Number of ’hello world’s to print”);

 struct hello_data {
 struct list_head tlist;
 ktime_t time;
 };

 LIST_HEAD(head_node);

 static int __init hello_init(void)
 {
 int i;

 printk(KERN_INFO ”Loading module hello...\n”);

 if (hello_world_count == 0) {
 printk(KERN_WARNING ”Warning: hello_world_count is zero\n”);
 } else if (hello_world_count >= 5 && hello_world_count <= 10) {
 printk(KERN_WARNING ”Warning: hello_world_count is between 5 and 10\n”);
 } else if (hello_world_count > 10) {
 printk(KERN_ERR ”Error: hello_world_count is out of range\n”);
 return -EINVAL;
 }

 for (i = 0; i < hello_world_count; i++) {
 struct hello_data *new_node = NULL;

 new_node = kmalloc(sizeof(struct hello_data), GFP_KERNEL);
 new_node->time = ktime_get();
 INIT_LIST_HEAD(&new_node->tlist);
 list_add_tail(&new_node->tlist, &head_node);

 printk(KERN_INFO ”Hello, world!\n”);
 }
 return 0;
 }

 static void __exit hello_exit(void)
 {
 int count = 0;
 struct hello_data *c, *temp_node;

 list_for_each_entry_safe(c, temp_node, &head_node, tlist) {
 printk(KERN_INFO ”Node %d ktime = %lld\n”, count++,


 ktime_to_ns(c->time));
 list_del(&c->tlist);
 kfree(c);
 }
 printk(KERN_INFO ”Module unloaded\n”);
 }

 module_init(hello_init);
 module_exit(hello_exit);
