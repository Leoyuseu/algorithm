#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/init.h>
#include <linux/ip.h>
#include <linux/types.h>
#include <linux/sched.h>
#include <net/sock.h>
#include <net/netlink.h> 
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Koorey King");

struct sock *nl_sk = NULL;
static struct task_struct *mythread = NULL; //内核线程对象

//向用户空间发送消息的接口
void sendnlmsg(char *message/*,int dstPID*/)
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

    // 设置Netlink的控制块里的相关信息
    NETLINK_CB(skb).pid = 0; // 消息发送者的id标识，如果是内核发的则置0
    NETLINK_CB(skb).dst_group = 5; //多播组号为5，但置成0好像也可以。

    message[slen] = '\0';
    memcpy(NLMSG_DATA(nlh), message, slen+1);

    //通过netlink_unicast()将消息发送用户空间由dstPID所指定了进程号的进程
    //netlink_unicast(nl_sk,skb,dstPID,0);
    netlink_broadcast(nl_sk, skb, 0,5, GFP_KERNEL); //发送多播消息到多播组5，这里我故意没有用1之类的“常见”值，目的就是为了证明我们上面提到的多播组号和多播组号掩码之间的对应关系
    printk("send OK!\n");
    return;
}

//每隔1秒钟发送一条“I am from kernel!”消息，共发10个报文
static int sending_thread(void *data)
{
     int i = 10;
     struct completion cmpl;
     while(i--){
            init_completion(&cmpl);
            wait_for_completion_timeout(&cmpl, 1 * HZ);
            sendnlmsg("I am from kernel!");
     }
     printk("sending thread exited!");
     return 0;
}

static int __init myinit_module()
{
    printk("my netlink in\n");
    nl_sk = netlink_kernel_create(NETLINK_TEST,0,NULL,THIS_MODULE);

    if(!nl_sk){
        printk(KERN_ERR "my_net_link: create netlink socket error.\n");
        return 1;
    }

    printk("my netlink: create netlink socket ok.\n");
    mythread = kthread_run(sending_thread,NULL,"thread_sender");
    return 0;
}

static void __exit mycleanup_module()
{
    if(nl_sk != NULL){
        sock_release(nl_sk->sk_socket);
}
printk("my netlink out!\n");
}

module_init(myinit_module);
module_exit(mycleanup_module);
