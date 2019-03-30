#include <linux/init.h>
#include <linux/ip.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/tcp.h>

MODULE_LICENSE("GPL");

static struct nf_hook_ops hook_ops;

static unsigned int hook_func(void* priv, struct sk_buff *skb, const struct nf_hook_state* state)
{
    struct iphdr *ip_header = (struct iphdr *)skb_network_header(skb);
    struct tcphdr *tcp_header;
    unsigned int dest, source;
    if (ip_header->protocol == 6) //TCP protocol
    {
        tcp_header= (struct tcphdr *)((__u32 *)ip_header+ ip_header->ihl);
        dest = ntohs(tcp_header->dest);
        source = ntohs(tcp_header->source);
        if(dest == 22)
        {
            printk("TCP Source Port: %u, Dest Port: %u\n", source, dest);
        }
    }
    return NF_ACCEPT; //accept the packet
}

static int __init myfilter_init(void)
{
    int retval;

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
    printk("Unregistered the net hook.\n");
}

/* Register module functions */
module_init(myfilter_init);
module_exit(myfilter_exit);
