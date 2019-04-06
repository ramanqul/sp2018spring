#include <linux/init.h>
#include <linux/ip.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/tcp.h>

MODULE_LICENSE("GPL");

static struct nf_hook_ops hook_ops;
struct packet_info {
   u16 port_s;
   u16 port_d;
};

struct tasklet_struct my_t;

static unsigned int hook_func(void* priv, struct sk_buff *skb, const struct nf_hook_state* state)
{
    struct iphdr *ip_header = (struct iphdr *)skb_network_header(skb);
    struct tcphdr *tcp_header;
    struct packet_info data;

    if (ip_header->protocol == 6) //TCP protocol
    {
        tcp_header= (struct tcphdr *)((__u32 *)ip_header+ ip_header->ihl);

	data.port_d = ntohs(tcp_header->dest);
        data.port_s = ntohs(tcp_header->source);
	my_t.data = &data;

	tasklet_schedule(&my_t);
    }

    return NF_ACCEPT; //accept the packet
}

void tasklet_func(unsigned long data) {
   struct packet_info *mydata = (struct packet_info *) &data;
   printk(KERN_INFO "port dest: %hu, port source: %hu", mydata->port_d, mydata->port_s);
}

static int __init myfilter_init(void)
{
    int retval;
   
    tasklet_init(&my_t, tasklet_func, 0);

    hook_ops.hook = hook_func;
    hook_ops.hooknum = NF_INET_LOCAL_IN;
    hook_ops.pf = PF_INET;
    hook_ops.priority = NF_IP_PRI_FIRST;
    retval = nf_register_net_hook(&init_net, &hook_ops);
    printk("nf_register_net_hook returned %d\n", retval);

    return retval;
}

static void __exit myfilter_exit(void)
{
    nf_unregister_net_hook(&init_net, &hook_ops);
    tasklet_kill(&my_t);
    printk("Unregistered the net hook.\n");
}

/* Register module functions */
module_init(myfilter_init);
module_exit(myfilter_exit);
