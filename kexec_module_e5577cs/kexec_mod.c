/*
 * kexec.c - kexec system call
 * Copyright (C) 2002-2004 Eric Biederman  <ebiederm@xmission.com>
 *
 * This source code is licensed under the GNU General Public License,
 * Version 2.  See the file COPYING for more details.
 */

#include <linux/capability.h>
#include <linux/mm.h>
#include <linux/file.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/kexec.h>
#include <linux/mutex.h>
#include <linux/list.h>
#include <linux/highmem.h>
#include <linux/syscalls.h>
#include <linux/reboot.h>
#include <linux/ioport.h>
#include <linux/hardirq.h>
#include <linux/elf.h>
#include <linux/elfcore.h>
#include <linux/utsname.h>
#include <linux/numa.h>
#include <linux/suspend.h>
#include <linux/device.h>
#include <linux/freezer.h>
#include <linux/pm.h>
#include <linux/cpu.h>
#include <linux/console.h>
#include <linux/vmalloc.h>
#include <linux/swap.h>
#include <linux/syscore_ops.h>
#include <linux/kallsyms.h>

#include <asm/page.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <asm/sections.h>
//#include <asm/smp.h>

#include <linux/module.h>

#include "kexec_mod.h"

MODULE_LICENSE("GPL");

static int __init kexec_module_init(void) {
    unsigned long (*sym_kallsyms_lookup_name)(const char *name) = (void *)kallsyms_lookup_name;
    sym_machine_shutdown = (void *)sym_kallsyms_lookup_name("machine_shutdown");
    sym_kernel_restart_prepare = (void *)sym_kallsyms_lookup_name("kernel_restart_prepare");
    sym_insert_resource = (void *)sym_kallsyms_lookup_name("insert_resource");
    sym_soft_restart = (void *)sym_kallsyms_lookup_name("soft_restart");
    irq_to_desc = (void *)sym_kallsyms_lookup_name("irq_to_desc");
    /*sym_panic_on_oops = (void *)sym_kallsyms_lookup_name("panic_on_oops");
    void (*sym_smp_send_stop)(void) = (void *)sym_kallsyms_lookup_name("smp_send_stop");
    void (*sym_preempt_disable)(void) = (void *)sym_kallsyms_lookup_name("preempt_disable");
    void (*sym_spm_mtcmos_ctrl_cpu1)(int, int) = (void *)sym_kallsyms_lookup_name("spm_mtcmos_ctrl_cpu1");
    void (*sym_spm_mtcmos_ctrl_cpu2)(int, int) = (void *)sym_kallsyms_lookup_name("spm_mtcmos_ctrl_cpu2");
    void (*sym_spm_mtcmos_ctrl_cpu3)(int, int) = (void *)sym_kallsyms_lookup_name("spm_mtcmos_ctrl_cpu3");
    void (*sym_migrate_to_reboot_cpu)(void) = (void *)sym_kallsyms_lookup_name("migrate_to_reboot_cpu");
	void (*sym_cpu_hotplug_enable)(void) = (void *)sym_kallsyms_lookup_name("cpu_hotplug_enable");*/

	ksysfs_init();

//	root@android:/ # echo 0 > /proc/sys/kernel/dmesg_restrict
//	root@android:/ # echo 0 > /proc/sys/kernel/kptr_restrict
//	root@android:/ # cat /proc/kallsyms | grep sys_call_table
//	c000e0a8 T sys_call_table
	syscall_table = (void **)0xc00111e8;

	//_sys_call_page = virt_to_page(&syscall_table);
	/////set_memory_rw((long unsigned int)syscall_table, 1);

	/* Set kexec_load() syscall. */
	syscall_table[__NR_kexec_load] = kexec_load;

	/* Swap reboot() syscall and store original */
	original_reboot = syscall_table[__NR_reboot];
	syscall_table[__NR_reboot] = reboot;

	/* crash_notes_memory_init */
	/* Allocate memory for saving cpu registers. */
	crash_notes_memory_init();

	crash_save_vmcoreinfo_init();

	return 0;
}

module_init(kexec_module_init)
