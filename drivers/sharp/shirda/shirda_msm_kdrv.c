/* drivers/sharp/shirda/shirda_msm_kdrv.c (sharp IrDA driver)
 *
 * Copyright (C) 2011 - 2015 SHARP CORPORATION All rights reserved.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/clk.h>
#include <linux/wakelock.h>
#include <linux/spinlock.h>
#include <linux/hrtimer.h>
#include <linux/delay.h>
#include <asm/io.h>


#include <linux/gpio.h>

#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>

#include <linux/moduleparam.h>

#include SHIRDA_CONFIG_H

#include "sharp/irda_kdrv_api.h"

#define	SHIRDA_DRIVER_NAME	SHIRDA_DEVFILE_NAME
#include "shirda_kdrv.h"







#define	SHIRDA_KERNEL_DRIVER_VERSION	"1.54.00"
#define	SHIRDA_KERNEL_DRIVER_NAME	SHIRDA_DEVFILE_NAME
#define	SHIRDA_KERNEL_DRIVER_NAME2	SHIRDA_DEVFILE_NAME2
#define	SHIRDA_KERNEL_DRIVER_NAME3	SHIRDA_DEVFILE_NAME3

#define SHIRDA_CORE_CLK_FREQ	(7372800)

#define	SHIRDA_GPIO_HIGH	(1)
#define	SHIRDA_GPIO_LOW		(0)
#define	SHIRDA_GPIO_IDLE	(0)
#define	SHIRDA_SD_SHUTDOWN	(1)
#define	SHIRDA_SD_ACTIVE	(0)

#define	SHIRDA_WAIT_MODESEQ	(200*1000)
#define	SHIRDA_MODESEQ_SDACTIME	(1)
#define	SHIRDA_MODESEQ_WAITTXD	(400*1000)

#define	SHIRDA_LEDRCMODE_WAIT	(1*1000)
#define	SHIRDA_LEDRCMODE_ST1	(1)
#define	SHIRDA_LEDRCMODE_ST2	(1)
#define	SHIRDA_LEDRCMODE_ST3	(10)
#define	SHIRDA_LEDRCMODE_ST4	(10*1000)


#define	SHIRDA_UART_DM_IRDA    (GSBIREG_BASE + UART_DM_REGISTER + UART_DM_IRDA)


#define	MEDIUM_RATE_EN		(0x0010)
#define	IRDA_LOOPBACK		(0x0008)
#define	INVERT_IRDA_TX		(0x0004)
#define	INVERT_IRDA_RX		(0x0002)
#define	IRDA_EN			(0x0001)


static int shirda_open(struct inode *inode, struct file *fp);
static int shirda_release(struct inode *inode, struct file *fp);
static int shirda_driver_init(struct platform_device *pdev);
static int shirda_driver_remove(struct platform_device *pdev);

static int shirda2_open(struct inode *inode, struct file *fp);
static int shirda2_release(struct inode *inode, struct file *fp);
static int shirda3_open(struct inode *inode, struct file *fp);
static int shirda3_release(struct inode *inode, struct file *fp);
#ifdef	SHIRDA_QUALCOMM_PERFLOCK
static int shirda_cpufreq_callback(struct notifier_block *nb,
					unsigned long event, void *data);
#endif


typedef enum {
	SHIRDA_GSBI_NORMAL,
	SHIRDA_GSBI_INVERT,
	SHIRDA_GSBI_IRDA,
	SHIRDA_GSBI_IRDA_MIR,
} shirda_gsbi_mode;

typedef enum {
	SHIRDA_LED_SIR_FUNC,
	SHIRDA_LED_FIR_FUNC,
	SHIRDA_LED_RC_START_FUNC,
	SHIRDA_LED_RC_END_FUNC,
} shirda_led_function;

typedef enum {
	SHIRDA_STATE_INIT,
	SHIRDA_STATE_IDLE,
	SHIRDA_STATE_READY,
	SHIRDA_STATE_OPEN,
	SHIRDA_STATE_OPEN2,
	SHIRDA_STATE_OPEN3,
	SHIRDA_STATE_ERROR
} shirda_main_state;

static shirda_main_state shirda_state = SHIRDA_STATE_INIT;

typedef enum {
	SHIRDA_GPIO_MODE_IDLE,
	SHIRDA_GPIO_MODE_ACTIVE,
	SHIRDA_GPIO_MODE_ACTIVE2,
	SHIRDA_GPIO_MODE_MAX
} shirda_gpio_mode;

static void shirda_gpio_free(void);
static int shirda_gpios_enable(shirda_gpio_mode mode);



static int shirda_gpio_init(void);
#include	"shirda_msm_gpio.c"

struct platform_device *shirda_device = NULL;
static struct platform_driver shirda_driver = {
	.remove = shirda_driver_remove,
	.driver = {
		.name  = SHIRDA_KERNEL_DRIVER_NAME,
		.owner = THIS_MODULE,
	},
};

static struct file_operations shirda_ops = {
	.owner		= THIS_MODULE,
	.open		= shirda_open,
	.release	= shirda_release,
};

static struct miscdevice shirda_misc = {
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= SHIRDA_KERNEL_DRIVER_NAME,
	.fops	= &shirda_ops,
};

static struct file_operations shirda2_ops = {
	.owner		= THIS_MODULE,
	.open		= shirda2_open,
	.release	= shirda2_release,
};

static struct miscdevice shirda2_misc = {
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= SHIRDA_KERNEL_DRIVER_NAME2,
	.fops	= &shirda2_ops,
};

static struct file_operations shirda3_ops = {
	.owner		= THIS_MODULE,
	.open		= shirda3_open,
	.release	= shirda3_release,
};

static struct miscdevice shirda3_misc = {
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= SHIRDA_KERNEL_DRIVER_NAME3,
	.fops	= &shirda3_ops,
};



static spinlock_t shirda_lock;
#define	SHIRDA_WLOCK_SUSPEND_NAME "shirda_suspend_lock"
static struct wake_lock shirda_wlock_suspend;










static void shirda_led_set_sir(void)
{
	struct timespec wait_time;
	unsigned long lock_flag;

	wait_time.tv_sec  = 0;
	wait_time.tv_nsec = SHIRDA_WAIT_MODESEQ;
	hrtimer_nanosleep(&wait_time, NULL, HRTIMER_MODE_REL, CLOCK_MONOTONIC);

	spin_lock_irqsave(&shirda_lock, lock_flag);

	gpio_set_value(SHIRDA_GPIO_SD, SHIRDA_SD_SHUTDOWN);
	udelay(SHIRDA_MODESEQ_SDACTIME);
	gpio_set_value(SHIRDA_GPIO_SD, SHIRDA_SD_ACTIVE);

	spin_unlock_irqrestore(&shirda_lock, lock_flag);

	wait_time.tv_sec  = 0;
	wait_time.tv_nsec = SHIRDA_MODESEQ_WAITTXD;
	hrtimer_nanosleep(&wait_time, NULL, HRTIMER_MODE_REL, CLOCK_MONOTONIC);

	return;
}

static void shirda_led_set_rc(void)
{
	struct timespec wait_time;
	unsigned long lock_flag;

	wait_time.tv_sec  = 0;
	wait_time.tv_nsec = SHIRDA_LEDRCMODE_WAIT;
	hrtimer_nanosleep(&wait_time, NULL, HRTIMER_MODE_REL, CLOCK_MONOTONIC);

	spin_lock_irqsave(&shirda_lock, lock_flag);

	gpio_set_value(SHIRDA_GPIO_SD, SHIRDA_SD_SHUTDOWN);

	udelay(SHIRDA_LEDRCMODE_ST1);
	gpio_set_value(SHIRDA_GPIO_TXD, 1);

	udelay(SHIRDA_LEDRCMODE_ST2);
	gpio_set_value(SHIRDA_GPIO_TXD, 0);

	udelay(SHIRDA_LEDRCMODE_ST3);
	gpio_set_value(SHIRDA_GPIO_SD, SHIRDA_SD_ACTIVE);

	spin_unlock_irqrestore(&shirda_lock, lock_flag);

	wait_time.tv_sec  = 0;
	wait_time.tv_nsec = SHIRDA_LEDRCMODE_ST4;
	hrtimer_nanosleep(&wait_time, NULL, HRTIMER_MODE_REL, CLOCK_MONOTONIC);

	return;
}

static int shirda_gpio_set_irda_enable(shirda_led_function func)
{
	int ret = 0;


	gpio_set_value(SHIRDA_GPIO_SD, SHIRDA_SD_ACTIVE);

	switch (func) {
	case SHIRDA_LED_SIR_FUNC:
		shirda_led_set_sir();

		ret = shirda_gpios_enable(SHIRDA_GPIO_MODE_ACTIVE);
		if (ret != 0) {
			IRDALOG_FATAL("gpios_enable() fail errno = %d\n", ret);
		}
		break;
	case SHIRDA_LED_RC_START_FUNC:
		shirda_led_set_rc();

		ret = shirda_gpios_enable(SHIRDA_GPIO_MODE_ACTIVE2);
		if (ret != 0) {
			IRDALOG_FATAL("gpios_enable() fail errno = %d\n", ret);
		}
		break;
	case SHIRDA_LED_RC_END_FUNC:
	default:
		IRDALOG_FATAL("Internal error! shirda_led_function = %d\n",
									func);
		ret = -EIO;
		break;
	}


	IRDALOG_INFO("include config file %s \n", SHIRDA_CONFIG_H);

	return ret;
}

static int shirda_gpio_set_irda_disable(shirda_led_function func)
{
	int ret = 0;


	ret = shirda_gpios_enable(SHIRDA_GPIO_MODE_IDLE);
	if (ret != 0) {
		IRDALOG_FATAL("gpios_enable() fail errno = %d\n", ret);
	}

	switch (func) {
	case SHIRDA_LED_SIR_FUNC:
		break;
	case SHIRDA_LED_RC_END_FUNC:
		shirda_led_set_sir();
		break;
	default:
		IRDALOG_FATAL("Internal error! shirda_led_function = %d\n",
									func);
		ret = -EIO;
		break;
	}

	gpio_set_value(SHIRDA_GPIO_SD, SHIRDA_SD_SHUTDOWN);

	return ret;
}

struct shirda_clk_table {
	struct clk	*clk;
	struct clk	*pclk;
};
static struct shirda_clk_table	shirda_clk = {
	.clk	= NULL,
	.pclk	= NULL,
};






static int shirda_clk_enable(void)
{
	int	ret;


	shirda_clk.clk = clk_get_sys(SHIRDA_UART_CLK_NAME, "core_clk");
	if (unlikely(IS_ERR(shirda_clk.clk))) {
		IRDALOG_FATAL("The core_clk address error\n");
		return -EIO;
	} else {
		ret = clk_set_rate(shirda_clk.clk, SHIRDA_CORE_CLK_FREQ);
		if (ret != 0) {
			IRDALOG_FATAL("core_clk set rate error %d\n", ret);
			goto	clk_error;
		}
		ret = clk_prepare_enable(shirda_clk.clk);
		if (ret != 0) {
			IRDALOG_FATAL("core_clk enable error %d\n", ret);
			goto	clk_error;
		}
	}

	shirda_clk.pclk = clk_get_sys(SHIRDA_UART_CLK_NAME, "iface_clk");
	if (!(IS_ERR(shirda_clk.pclk))) {
		ret = clk_prepare_enable(shirda_clk.pclk);
		if (ret != 0) {
			IRDALOG_FATAL("iface_clk enable error %d\n", ret);
			goto	clk_error_disable;
		}
	} else {
		IRDALOG_FATAL("The iface_clk address error\n");
		goto	clk_error_disable;
	}

	return 0;

clk_error_disable:
	clk_disable_unprepare(shirda_clk.clk);
clk_error:
	clk_put(shirda_clk.clk);
	return -EIO;
}









static void shirda_clk_disable(void)
{

	shirda_clk.clk = clk_get_sys(SHIRDA_UART_CLK_NAME, "core_clk");
	if (!(IS_ERR(shirda_clk.clk))) {
		clk_disable_unprepare(shirda_clk.clk);
		clk_put(shirda_clk.clk);
	} else {
		IRDALOG_FATAL("The core_clk(%s) address get error\n",
							SHIRDA_UART_CLK_NAME);
	}

	shirda_clk.pclk = clk_get_sys(SHIRDA_UART_CLK_NAME, "iface_clk");
	if (!(IS_ERR(shirda_clk.pclk))) {
		clk_disable_unprepare(shirda_clk.pclk);
		clk_put(shirda_clk.pclk);
	} else {
		IRDALOG_FATAL("The iface_clk(%s) address get error\n",
							SHIRDA_UART_CLK_NAME);
	}

	return;
}
































static int shirda_set_uartdm_irda_enable(shirda_gsbi_mode mode)
{
	unsigned long	lock_flag;
	void __iomem	*gsbi_irda = ioremap_nocache(SHIRDA_UART_DM_IRDA, 4);
	int		ret = 0;

	ret = shirda_clk_enable();
	if (ret != 0) {
		IRDALOG_FATAL("Fatal error! can't enable clk.\n");
		goto uartdm_irda_ena_err;
	}

	spin_lock_irqsave(&shirda_lock, lock_flag);

	switch (mode) {
	case SHIRDA_GSBI_NORMAL:
		writel_relaxed((INVERT_IRDA_RX), gsbi_irda);
		mb();
		break;
	case SHIRDA_GSBI_INVERT:
		writel_relaxed((INVERT_IRDA_RX | INVERT_IRDA_TX), gsbi_irda);
		mb();
		break;
	case SHIRDA_GSBI_IRDA:
		writel_relaxed((INVERT_IRDA_RX | IRDA_EN), gsbi_irda);
		mb();
		break;
	case SHIRDA_GSBI_IRDA_MIR:
		writel_relaxed((INVERT_IRDA_RX | IRDA_EN | MEDIUM_RATE_EN),
								 gsbi_irda);
		mb();
		break;
	default:
		IRDALOG_FATAL("Internal error! shirda_gsbi_mode = %d\n", mode);
		ret = -EIO;
		break;
	}

	spin_unlock_irqrestore(&shirda_lock, lock_flag);

	shirda_clk_disable();

uartdm_irda_ena_err:

	if (gsbi_irda != NULL)	iounmap(gsbi_irda);

	return ret;
}

static void shirda_set_uartdm_irda_disable(void)
{
	unsigned long lock_flag;
	void __iomem *gsbi_irda = ioremap_nocache(SHIRDA_UART_DM_IRDA, 4);


	if (shirda_clk_enable() != 0) {
		IRDALOG_FATAL("Fatal error! can't enable clk.\n");
		goto uartdm_irda_dis_err;
	}

	spin_lock_irqsave(&shirda_lock, lock_flag);

	writel_relaxed((INVERT_IRDA_RX), gsbi_irda);
	mb();

	spin_unlock_irqrestore(&shirda_lock, lock_flag);

	shirda_clk_disable();

uartdm_irda_dis_err:
	if (gsbi_irda != NULL)	iounmap(gsbi_irda);
}

static int shirda_open(struct inode *inode, struct file *fp)
{
	int ret = 0;


	switch (shirda_state) {
	case SHIRDA_STATE_IDLE:
	case SHIRDA_STATE_READY:
		ret = shirda_set_uartdm_irda_enable(SHIRDA_GSBI_IRDA);
		if (ret != 0) {
			IRDALOG_ERROR("IrDA setting was not completed.\n");
		} else {
			ret = shirda_gpio_set_irda_enable(SHIRDA_LED_SIR_FUNC);
		}
		break;
	case SHIRDA_STATE_OPEN2:
	case SHIRDA_STATE_OPEN3:
		IRDALOG_INFO("Already using by IrDA. state = %d\n",
								shirda_state);
		return -EBUSY;
	default:
		IRDALOG_ERROR("open error. state = %d\n", shirda_state);
		return -EPERM;
	}

	if (ret == 0) {
		wake_lock(&shirda_wlock_suspend);
	}


	if (ret != 0) {
		shirda_set_uartdm_irda_disable();
	} else {
		shirda_state = SHIRDA_STATE_OPEN;
	}

	return ret;
}

static int shirda_release(struct inode *inode, struct file *fp)
{
	int ret = 0;


	if (shirda_state != SHIRDA_STATE_OPEN) {
		IRDALOG_ERROR("close error. state = %d\n", shirda_state);
		ret = -EPERM;
	} else {
		ret = shirda_gpio_set_irda_disable(SHIRDA_LED_SIR_FUNC);
		if (ret == 0) {
			shirda_state = SHIRDA_STATE_READY;
			wake_unlock(&shirda_wlock_suspend);
		} else {
			IRDALOG_FATAL("irda disable fatal error.\n");
			shirda_state = SHIRDA_STATE_ERROR;
			shirda_gpio_free();
		}
		shirda_set_uartdm_irda_disable();
	}
	return ret;
}

static int shirda2_open(struct inode *inode, struct file *fp)
{
	int ret = 0;


	switch (shirda_state) {
	case SHIRDA_STATE_IDLE:
	case SHIRDA_STATE_READY:
		ret = shirda_set_uartdm_irda_enable(SHIRDA_GSBI_IRDA);
		if (ret != 0) {
			IRDALOG_ERROR("IrDA setting was not completed.\n");
		} else {
			ret = shirda_gpio_set_irda_enable(
						SHIRDA_LED_RC_START_FUNC);
		}
		break;
	case SHIRDA_STATE_OPEN:
	case SHIRDA_STATE_OPEN3:
		IRDALOG_INFO("Already using by IrDA. state = %d\n",
								shirda_state);
		return -EBUSY;
	default:
		IRDALOG_ERROR("open error. state = %d\n", shirda_state);
		return -EPERM;
	}

	if (ret == 0) {
		wake_lock(&shirda_wlock_suspend);
		IRDALOG_INFO("wake_lock_suspend\n");
	}


	if (ret != 0) {
		shirda_gpio_set_irda_disable(SHIRDA_LED_RC_END_FUNC);
		shirda_set_uartdm_irda_disable();
	} else {
		shirda_state = SHIRDA_STATE_OPEN2;



	}

	return ret;
}

static int shirda2_release(struct inode *inode, struct file *fp)
{
	int ret = 0;


	if (shirda_state != SHIRDA_STATE_OPEN2) {
		IRDALOG_ERROR("close error. state = %d\n", shirda_state);
		ret = -EPERM;
	} else {
		ret = shirda_gpio_set_irda_disable(SHIRDA_LED_RC_END_FUNC);
		if (ret == 0) {
			shirda_state = SHIRDA_STATE_READY;
			wake_unlock(&shirda_wlock_suspend);
			IRDALOG_INFO("wake_unlock_suspend\n");
		} else {
			IRDALOG_FATAL("irda disable fatal error.\n");
			shirda_state = SHIRDA_STATE_ERROR;
			shirda_gpio_free();
		}
		shirda_set_uartdm_irda_disable();
	}


	return ret;
}

static int shirda3_open(struct inode *inode, struct file *fp)
{
	int ret = 0;


	switch (shirda_state) {
	case SHIRDA_STATE_IDLE:
	case SHIRDA_STATE_READY:
		ret = shirda_set_uartdm_irda_enable(SHIRDA_GSBI_IRDA_MIR);
		if (ret != 0) {
			IRDALOG_ERROR("IrDA setting was not completed.\n");
		} else {
			ret = shirda_gpio_set_irda_enable(
						SHIRDA_LED_RC_START_FUNC);
		}
		break;
	case SHIRDA_STATE_OPEN:
	case SHIRDA_STATE_OPEN2:
		IRDALOG_INFO("Already using by IrDA. state = %d\n",
								shirda_state);
		return -EBUSY;
	default:
		IRDALOG_ERROR("open error. state = %d\n", shirda_state);
		return -EPERM;
	}

	if (ret == 0) {
		wake_lock(&shirda_wlock_suspend);
		IRDALOG_INFO("wake_lock_suspend\n");
	}


	if (ret != 0) {
		shirda_gpio_set_irda_disable(SHIRDA_LED_RC_END_FUNC);
		shirda_set_uartdm_irda_disable();
	} else {
		shirda_state = SHIRDA_STATE_OPEN3;



	}

	return ret;
}

static int shirda3_release(struct inode *inode, struct file *fp)
{
	int ret = 0;


	if (shirda_state != SHIRDA_STATE_OPEN3) {
		IRDALOG_ERROR("close error. state = %d\n", shirda_state);
		ret = -EPERM;
	} else {
		ret = shirda_gpio_set_irda_disable(SHIRDA_LED_RC_END_FUNC);
		if (ret == 0) {
			shirda_state = SHIRDA_STATE_READY;
			wake_unlock(&shirda_wlock_suspend);
			IRDALOG_INFO("wake_unlock_suspend\n");
		} else {
			IRDALOG_FATAL("irda disable fatal error.\n");
			shirda_state = SHIRDA_STATE_ERROR;
			shirda_gpio_free();
		}
		shirda_set_uartdm_irda_disable();
	}
	return ret;
}





static char* node =  SHIRDA_BLSP_NODE;
module_param( node, charp, S_IRUGO );
MODULE_PARM_DESC( node, "BLSP node name of tty device");

static int shirda_driver_init(struct platform_device *pdev)
{
	int ret = 0;


	if (shirda_state != SHIRDA_STATE_INIT &&
		shirda_state != SHIRDA_STATE_ERROR) {
		IRDALOG_ERROR("already initialized  Now state: %d\n",
								shirda_state);
		return ret;
	}


	ret = shirda_gpio_init();
	if (ret != 0) {
		IRDALOG_FATAL("gpio initialization failed. errno = %d\n", ret);
		shirda_state = SHIRDA_STATE_ERROR;
		return ret;
	}

	spin_lock_init(&shirda_lock);

	if (shirda_set_uartdm_irda_enable(SHIRDA_GSBI_NORMAL) == 0) {
		shirda_state = SHIRDA_STATE_READY;
	} else {
		IRDALOG_ERROR("IrDA setting was not completed.\n");
		shirda_state = SHIRDA_STATE_IDLE;
	}

	misc_register(&shirda_misc);

	misc_register(&shirda2_misc);
	misc_register(&shirda3_misc);


	wake_lock_init(&shirda_wlock_suspend, WAKE_LOCK_SUSPEND,
						SHIRDA_WLOCK_SUSPEND_NAME);

	return ret;
}

static int shirda_driver_remove(struct platform_device *pdev)
{


	shirda_gpio_free();

	wake_lock_destroy(&shirda_wlock_suspend);

	misc_deregister(&shirda_misc);

	misc_deregister(&shirda2_misc);
	misc_deregister(&shirda3_misc);


	return 0;
}

static int __init shirda_module_init(void)
{
	int ret = 0;


	shirda_device = platform_device_alloc(
				(const char *)SHIRDA_KERNEL_DRIVER_NAME,
							(unsigned int) -1);
	if (shirda_device == NULL) {
		IRDALOG_FATAL("platform_device_alloc() failed\n");
		return -ENODEV;
	}

	ret = platform_device_add(shirda_device);
	if (ret != 0) {
		platform_device_put(shirda_device);
		IRDALOG_FATAL("platform_device_add() failed errno = %d\n",
								 ret);
	} else {
		ret = platform_driver_probe(&shirda_driver,
							shirda_driver_init);
		if (ret != 0) {
			platform_device_unregister(shirda_device);
			IRDALOG_FATAL(
				"platform_driver_probe() failed errno = %d\n",
								ret);
		}
	}


	return ret;
}

static void __exit shirda_module_exit(void)
{

	platform_driver_unregister(&shirda_driver);
	platform_device_unregister(shirda_device);
}

module_init(shirda_module_init);
module_exit(shirda_module_exit);

MODULE_DESCRIPTION("msm IrDA driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("SHARP CORPORATION");
MODULE_VERSION(SHIRDA_KERNEL_DRIVER_VERSION);
