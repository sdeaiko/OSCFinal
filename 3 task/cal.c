#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");

static int num1 = 0;
module_param(num1, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(num1, "The first number");

static int num2 = 0;
module_param(num2, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(num2, "The second number");

static char *op = "+";
module_param(op, charp, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(op, "The operator (+, -, *, /)");

static int result = 0;

static int cal_init(void)
{
    switch (*op) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 == 0) {
                printk(KERN_ALERT "Division by zero\n");
                return -EINVAL;
            }
            result = num1 / num2;
            break;
        default:
            printk(KERN_ALERT "Invalid operator: %s\n", op);
            return -EINVAL;
    }

    printk(KERN_ALERT "Result: %d\n", result);

    return 0;
}

static void cal_exit(void)
{
    printk(KERN_ALERT "Calculator module unloaded\n");
}

module_init(cal_init);
module_exit(cal_exit);
