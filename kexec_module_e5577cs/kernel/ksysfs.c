/*
 * kernel/ksysfs.c - sysfs attributes in /sys/kernel, which
 * 		     are not related to any other subsystem
 *
 * Copyright (C) 2004 Kay Sievers <kay.sievers@vrfy.org>
 * 
 * This file is release under the GPLv2
 *
 */

#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/export.h>
#include <linux/init.h>
#include <linux/kexec.h>
#include <linux/profile.h>
#include <linux/stat.h>
#include <linux/sched.h>
#include <linux/capability.h>

#define KERNEL_ATTR_RO(_name) \
static struct kobj_attribute _name##_attr = __ATTR_RO(_name)

#define KERNEL_ATTR_RW(_name) \
static struct kobj_attribute _name##_attr = \
	__ATTR(_name, 0644, _name##_show, _name##_store)
#ifdef CONFIG_KEXEC
static ssize_t kexec_loaded_show(struct kobject *kobj,
				 struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", !!kexec_image);
}
KERNEL_ATTR_RO(kexec_loaded);

static ssize_t kexec_crash_loaded_show(struct kobject *kobj,
				       struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", !!kexec_crash_image);
}
KERNEL_ATTR_RO(kexec_crash_loaded);

static ssize_t kexec_crash_size_show(struct kobject *kobj,
				       struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%zu\n", crash_get_memory_size());
}
static ssize_t kexec_crash_size_store(struct kobject *kobj,
				   struct kobj_attribute *attr,
				   const char *buf, size_t count)
{
	unsigned long cnt;
	int ret;

	if (strict_strtoul(buf, 0, &cnt))
		return -EINVAL;

	ret = crash_shrink_memory(cnt);
	return ret < 0 ? ret : count;
}
KERNEL_ATTR_RW(kexec_crash_size);

static ssize_t vmcoreinfo_show(struct kobject *kobj,
			       struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%lx %x\n",
		       paddr_vmcoreinfo_note(),
		       (unsigned int)vmcoreinfo_max_size);
}
KERNEL_ATTR_RO(vmcoreinfo);

#endif /* CONFIG_KEXEC */

static struct kobject *kernel_kobj_kexec;

static struct attribute * kernel_attrs[] = {
#ifdef CONFIG_KEXEC
	&kexec_loaded_attr.attr,
	&kexec_crash_loaded_attr.attr,
	&kexec_crash_size_attr.attr,
	&vmcoreinfo_attr.attr,
#endif
	NULL
};

static struct attribute_group kernel_attr_group = {
	.attrs = kernel_attrs,
};

asmlinkage int __init ksysfs_init(void)
{
	int error;

	kernel_kobj_kexec = kobject_get(kernel_kobj);
	if (!kernel_kobj_kexec) {
		error = -ENOMEM;
		goto exit;
	}
	error = sysfs_create_group(kernel_kobj, &kernel_attr_group);
	if (error)
		goto kset_exit;

	printk("KExec: Created sysfs entries!\n");
	return 0;

group_exit:
	sysfs_remove_group(kernel_kobj, &kernel_attr_group);
kset_exit:
	//kobject_put(kernel_kobj);
exit:

	printk("KExec: Failed to create sysfs entries!\n");

	return error;
}

//core_initcall(ksysfs_init);
