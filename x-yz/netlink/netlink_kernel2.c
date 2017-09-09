#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/init.h>
#include <linux/ip.h>
#include <linux/types.h>
#include <linux/sched.h>
#include <net/sock.h>
#include <linux/netlink.h> /*该文头文件里包含了linux/netlink.h，因为我们要用到net/netlink.h中的某些API函数，nlmsg_pug()*/

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Koorey King");

struct sock *nl_sk = NULL;
//向用户空间发送消息的接口
void sendnlmsg(char *message,int dstPID)
{
    struct sk_buff *skb;
    struct nlmsghdr *nlh;
    int len = NLMSG_SPACE(MAX_MSGSIZE);
    int slen = 0;

    if(!message || !nl_sk){
        return;
    }

    // 为新的 sk_buffer申请空间
    skb = alloc_skb(len, GFP_KERNEL);
    if(!skb){
        printk(KERN_ERR "my_net_link: alloc_skb Error./n");
        return;
    }

    slen = strlen(message)+1;

    //用nlmsg_put()来设置netlink消息头部
    nlh = nlmsg_put(skb, 0, 0, 0, MAX_MSGSIZE, 0);

    // 设置Netlink的控制块
    NETLINK_CB(skb).pid = 0; // 消息发送者的id标识，如果是内核发的则置0
    NETLINK_CB(skb).dst_group = 0; //如果目的组为内核或某一进程，该字段也置0

    message[slen] = '\0';
    memcpy(NLMSG_DATA(nlh), message, slen+1);

    //通过netlink_unicast()将消息发送用户空间由dstPID所指定了进程号的进程
    netlink_unicast(nl_sk,skb,dstPID,0);
    printk("send OK!\n");
    return;
}

static void nl_data_ready (struct sock *sk, int len)
{
    struct sk_buff *skb;
    struct nlmsghdr *nlh = NULL;

    while((skb = skb_dequeue(&sk->sk_receive_queue)) != NULL)
    {
        nlh = (struct nlmsghdr *)skb->data;
        printk("%s: received netlink message payload: %s \n", __FUNCTION__, (char*)NLMSG_DATA(nlh));
        kfree_skb(skb);
        sendnlmsg("I see you",nlh->nlmsg_pid); //发送者的进程ID我们已经将其存储在了netlink消息头部里的nlmsg_pid字段里，所以这里可以拿来用。
    }
    printk("recvied finished!\n");
}

static int __init myinit_module()
{
    printk("my netlink in\n");
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
