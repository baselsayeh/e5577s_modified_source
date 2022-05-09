#ifndef __KEXEC_MOD_H__
#define __KEXEC_MOD_H__

asmlinkage int ksysfs_init(void);
asmlinkage int crash_notes_memory_init(void);
asmlinkage int crash_save_vmcoreinfo_init(void);
asmlinkage long kexec_load(unsigned long entry, unsigned long nr_segments,
		struct kexec_segment __user * segments, unsigned long flags);
asmlinkage long reboot(int magic1, int magic2, unsigned int cmd,
		void __user * arg);


/* Syscall table */
void **syscall_table;

/* original and new reboot syscall */
asmlinkage long (*original_reboot)(int magic1, int magic2, unsigned int cmd, void __user *arg);
asmlinkage long reboot(int magic1, int magic2, unsigned int cmd, void __user *arg);

//other functions
void log_buf_kexec_setup(void);

void (*sym_machine_shutdown)(void);
int (*sym_insert_resource)(struct resource *parent, struct resource *new);
//void (*insert_resource)(void);
void (*sym_soft_restart)(unsigned long addr);
struct irq_desc *(*irq_to_desc)(unsigned int irq);
//int *sym_panic_on_oops;
void (*sym_kernel_restart_prepare)(char *cmd);

//struct irq_desc *irq_to_desc(unsigned int irq);

#endif