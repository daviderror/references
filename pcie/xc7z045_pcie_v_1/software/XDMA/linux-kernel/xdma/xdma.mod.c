#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xf7e1912f, "module_layout" },
	{ 0x2d3385d3, "system_wq" },
	{ 0xe248a9fc, "dma_map_sg_attrs" },
	{ 0x2065c5ab, "kmem_cache_destroy" },
	{ 0x25b6229f, "cdev_del" },
	{ 0xc35ee9f4, "kmalloc_caches" },
	{ 0xeb233a45, "__kmalloc" },
	{ 0x6e2fffdd, "cdev_init" },
	{ 0xe0f7c8db, "put_devmap_managed_page" },
	{ 0x83fc2f4f, "pci_write_config_word" },
	{ 0xd6ee688f, "vmalloc" },
	{ 0x3c95ebab, "pci_read_config_byte" },
	{ 0x46cf10eb, "cachemode2protval" },
	{ 0x2e7284b1, "dma_unmap_sg_attrs" },
	{ 0x4a580305, "dma_set_mask" },
	{ 0x4bd8c37b, "pcie_set_readrq" },
	{ 0x5367b4b4, "boot_cpu_data" },
	{ 0x393fc8de, "pci_disable_device" },
	{ 0xa253a9, "pci_disable_msix" },
	{ 0xffec9af5, "set_page_dirty_lock" },
	{ 0x837b7b09, "__dynamic_pr_debug" },
	{ 0xad34e79f, "device_destroy" },
	{ 0x4d503c6, "kobject_set_name" },
	{ 0x6729d3df, "__get_user_4" },
	{ 0x87b8798d, "sg_next" },
	{ 0x984bd0c1, "pci_release_regions" },
	{ 0x3a3a02cd, "pcie_capability_clear_and_set_word" },
	{ 0x409bcb62, "mutex_unlock" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x999e8297, "vfree" },
	{ 0xc1ca7541, "dma_free_attrs" },
	{ 0x7a2af7b4, "cpu_number" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0x75128ab, "pv_ops" },
	{ 0xfbe8a50, "dma_set_coherent_mask" },
	{ 0x85b1fcd0, "kthread_create_on_node" },
	{ 0x15ba50a6, "jiffies" },
	{ 0xc5e4a5d1, "cpumask_next" },
	{ 0x82862cb3, "kthread_bind" },
	{ 0xd9a5ea54, "__init_waitqueue_head" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0x17de3d5, "nr_cpu_ids" },
	{ 0xa6bf81a6, "pci_set_master" },
	{ 0x426b48f8, "pci_alloc_irq_vectors_affinity" },
	{ 0xfb578fc5, "memset" },
	{ 0x5d80fd88, "pci_restore_state" },
	{ 0x944f654, "pci_iounmap" },
	{ 0xd35cce70, "_raw_spin_unlock_irqrestore" },
	{ 0x977f511b, "__mutex_init" },
	{ 0xc5850110, "printk" },
	{ 0xfef216eb, "_raw_spin_trylock" },
	{ 0x585cfa4d, "kthread_stop" },
	{ 0xe1537255, "__list_del_entry_valid" },
	{ 0x5a5a2271, "__cpu_online_mask" },
	{ 0xae1e48b5, "pci_aer_clear_nonfatal_status" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0x63e7e055, "pci_read_config_word" },
	{ 0xd1880ecd, "dma_alloc_attrs" },
	{ 0x9f13157d, "kmem_cache_free" },
	{ 0x2ab7989d, "mutex_lock" },
	{ 0x854d40cc, "finish_swait" },
	{ 0x78b4028b, "device_create" },
	{ 0x92d5838e, "request_threaded_irq" },
	{ 0x6091797f, "synchronize_rcu" },
	{ 0x395c2799, "pci_enable_msi" },
	{ 0x68f31cbd, "__list_add_valid" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0x7455a7ab, "pci_find_capability" },
	{ 0x3460f6a5, "cdev_add" },
	{ 0x3a2f6702, "sg_alloc_table" },
	{ 0xe63c2d24, "kmem_cache_alloc" },
	{ 0xb601be4c, "__x86_indirect_thunk_rdx" },
	{ 0x618911fc, "numa_node" },
	{ 0xb2fd5ceb, "__put_user_4" },
	{ 0xc959d152, "__stack_chk_fail" },
	{ 0x9cb986f2, "vmalloc_base" },
	{ 0x1000e51, "schedule" },
	{ 0x8ddd8aad, "schedule_timeout" },
	{ 0x1d24c881, "___ratelimit" },
	{ 0x3ec2f5c2, "prepare_to_swait_event" },
	{ 0x2ea2c95c, "__x86_indirect_thunk_rax" },
	{ 0xeb15bd43, "wake_up_process" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0xf61b4ec7, "pci_unregister_driver" },
	{ 0xc84ed42, "kmem_cache_alloc_trace" },
	{ 0xba8fbd64, "_raw_spin_lock" },
	{ 0xb19a5453, "__per_cpu_offset" },
	{ 0x34db050b, "_raw_spin_lock_irqsave" },
	{ 0xe48b3a32, "kmem_cache_create" },
	{ 0x664ce1a8, "pci_irq_vector" },
	{ 0x3eeb2322, "__wake_up" },
	{ 0xb3f7646e, "kthread_should_stop" },
	{ 0x8c26d495, "prepare_to_wait_event" },
	{ 0x37a0cba, "kfree" },
	{ 0x2048e1f4, "remap_pfn_range" },
	{ 0x2d7ae524, "pci_request_regions" },
	{ 0x6df1aaf1, "kernel_sigaction" },
	{ 0xd3e848ea, "pci_disable_msi" },
	{ 0xdec0b570, "__pci_register_driver" },
	{ 0x4636828d, "class_destroy" },
	{ 0x92540fbf, "finish_wait" },
	{ 0x608741b5, "__init_swait_queue_head" },
	{ 0x7f5b4fe4, "sg_free_table" },
	{ 0xc5b6f236, "queue_work_on" },
	{ 0x656e4a6e, "snprintf" },
	{ 0xea16eea6, "pci_iomap" },
	{ 0x67c9f91c, "pci_enable_device_mem" },
	{ 0x7f02188f, "__msecs_to_jiffies" },
	{ 0x4a453f53, "iowrite32" },
	{ 0x94e05cb1, "pci_enable_device" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0x5abf98c2, "param_ops_uint" },
	{ 0x9bc087d1, "__class_create" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xaec89a32, "__put_page" },
	{ 0xa78af5f3, "ioread32" },
	{ 0x5e4d3730, "get_user_pages_fast" },
	{ 0xc80ab559, "swake_up_one" },
	{ 0xc1514a3b, "free_irq" },
	{ 0x8c2990d8, "pci_save_state" },
	{ 0xe914e41e, "strcpy" },
	{ 0x587f22d7, "devmap_managed_key" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("pci:v000010EEd00009048sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00009044sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00009042sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00009041sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd0000903Fsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00009038sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00009028sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00009018sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00009034sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00009024sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00009014sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00009032sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00009022sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00009012sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00009031sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00009021sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00009011sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00008011sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00008012sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00008014sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00008018sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00008021sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00008022sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00008024sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00008028sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00008031sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00008032sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00008034sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00008038sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00007011sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00007012sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00007014sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00007018sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00007021sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00007022sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00007024sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00007028sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00007031sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00007032sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00007034sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00007038sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00006828sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00006830sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00006928sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00006930sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00006A28sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00006A30sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00006D30sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00004808sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00004828sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00004908sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00004A28sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00004B28sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010EEd00002808sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001D0Fd0000F000sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001D0Fd0000F001sv*sd*bc*sc*i*");

MODULE_INFO(srcversion, "755B8C84314FF43EE2506DC");
