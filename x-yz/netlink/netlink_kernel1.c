#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/init.h>
#include <linux/ip.h>
#include <linux/types.h>
#include <linux/sched.h>
#include <net/sock.h>
#include <linux/netlink.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Koorey King");

struct sock *nl_sk = NULL;
static void nl_data_ready (struct sock *sk, int len)
{
    struct sk_buff *skb;
    struct nlmsghdr *nlh = NULL;

    while((skb = skb_dequeue(&sk->sk_receive_queue)) != NULL)
    {
          nlh = (struct nlmsghdr *)skb->data;
          printk("%s: received netlink message payload: %s \n", __FUNCTION__, (char*)NLMSG_DATA(nlh));
          kfree_skb(skb);
    }
    printk("recvied finished!\n");
}

static int __init myinit_module()
{
    printk("my netlink in\n");
    /* API changed */
    nl_sk = netlink_kernel_create(NETLINK_TEST,0,nl_data_ready,THIS_MODULE);
    return 0;
}

static void __exit mycleanup_module()
{
    printk("my netlink out!\n");
    sock_release(nl_sk->sk_socket);
}

module_init(myinit_module);
module_exit(mycleanup_module);
