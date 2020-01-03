#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/list.h>

static LIST_HEAD(birthday_list);

struct birthday {
   int day;
   int month;
   int year;
   struct list_head list;
};

void set_person(int day, int month, int year, struct birthday *person){
   person->day = day;
   person->month = month;
   person->year = year;
   INIT_LIST_HEAD(&person->list);
   list_add_tail(&person->list, &birthday_list);
}

int simple_init(void){
   struct birthday *person;
   struct birthday *ptr;

   person = kmalloc(sizeof(*person)*5, GFP_KERNEL);
   set_person(2,8,1995,person);
   person++;
   set_person(4,10,1990,person);
   person++;
   set_person(1,10,1998,person);
   person++;
   set_person(1,1,1990,person);
   person++;
   set_person(28,7,1992,person);
   
   list_for_each_entry(ptr, &birthday_list, list) {
      printk(KERN_INFO "day: %d\n",ptr->day);
      printk(KERN_INFO "month: %d\n",ptr->month);
      printk(KERN_INFO "year: %d\n",ptr->year);
   }

   return 0;
}

void simple_exit(void){
   struct birthday *ptr, *next;
   list_for_each_entry_safe(ptr, next, &birthday_list, list){
      list_del(&ptr->list);
      kfree(ptr);
   }
   printk(KERN_INFO "birthday removed\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Birthday Module");
MODULE_AUTHOR("SGG");
