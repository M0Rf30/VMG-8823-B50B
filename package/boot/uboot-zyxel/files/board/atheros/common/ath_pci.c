/*****************************************************************************/
/*! file ath_pci.c
** /brief PCI support for Atheros boards
**
** This provides the support code required for PCI support on the AP91/93
** board in the U-Boot environment. This board is a Python based system
** with a Merlin WLAN interface. This file also contains the support
** for initialization of the Merlin radios on the PCi bus, required for
** pre-configuration for use by Linux.
**
** Copyright (c) 2008 Atheros Communications Inc. All rights reserved.
**
*/

#include <common.h>
#include <command.h>
#include <asm/mipsregs.h>
#include <asm/addrspace.h>
#include <config.h>
#include <version.h>
#include <pci.h>
#include <atheros.h>

/*
** PCI controller "hose" value
*/

static struct pci_controller hose;

static int ath_local_read_config(int where, int size, uint32_t *value);
static int ath_local_write_config(int where, int size, uint32_t value);

static int
ath_local_read_config(int where, int size, uint32_t *value)
{
	*value = ath_reg_rd(ATH_PCI_CRP + where);
	return 0;
}

static int
ath_local_write_config(int where, int size, uint32_t value)
{
	ath_reg_wr((ATH_PCI_CRP + where),value);
	return 0;
}

static int
ath_pci_read_config(struct pci_controller *hose,
			pci_dev_t dev, int where, uint32_t *value)
{
	*value = ath_reg_rd(ATH_PCI_DEV_CFGBASE + where);
	return 0;
}

static int
ath_pci_write_config(struct pci_controller *hose,
			pci_dev_t dev, int where, uint32_t value)
{
	ath_reg_wr((ATH_PCI_DEV_CFGBASE + where), value);
	return 0;
}

static int
ath_local_read_config_rc2(int where, int size, uint32_t *value)
{
	*value = ath_reg_rd(0x18250000 + where);
	return 0;
}

static int
ath_local_write_config_rc2(int where, int size, uint32_t value)
{
	ath_reg_wr((0x18250000 + where),value);
	return 0;
}

static int
ath_pci_read_config_rc2(struct pci_controller *hose,
			pci_dev_t dev, int where, uint32_t *value)
{
	*value = ath_reg_rd(0xb6000000 + where);
	return 0;
}

static int
ath_pci_write_config_rc2(struct pci_controller *hose,
			pci_dev_t dev, int where, uint32_t value)
{
	ath_reg_wr((0xb6000000 + where), value);
	return 0;
}

/*
** We will use the ART configuration information stored in flash to initialize
** these devices as required.
*/

#ifdef CONFIG_PCI_CONFIG_DATA_IN_OTP
#define plat_dev_init()
#else
void plat_dev_init(void)
{
	u32	val;
	u32	addr;
	u32	BaseAddr = 0x10000000;
	u32	CalAddr = WLANCAL;
	volatile u16 *calData;

	/*
	 * Copy the device ID from Flash to device config space.
	 */

	calData = (u16 *)CalAddr;

#ifndef CONFIG_PCI_CONFIG_DATA_IN_OTP
	if (calData[0] != 0xa55a && calData[0] != 0x5aa5)
	{
#ifndef COMPRESSED_UBOOT
		prmsg("BOARD IS NOT CALIBRATED!!!\n");
#endif
		return;
	}
#else
	return;
#endif
	/*
	** Need to setup the PCI device to access the internal registers
	*/
	if ((is_ar7241() || is_ar7242()))
		ath_pci_write_config(&hose, NULL, 0x10, 0x1000ffff);
	else
		ath_pci_write_config(&hose, NULL, 0x10, 0xffff);

	ath_pci_write_config(&hose, NULL, 0x04, 0x6);

	ath_pci_write_config_rc2(&hose, NULL, 0x10, 0xffff);

	ath_pci_write_config_rc2(&hose, NULL, 0x04, 0x6);
	/*
	** Set pointer to first reg address
	*/

	calData += ATH_ART_PCICFG_OFFSET;

	while(*calData != 0xffff)
	{
		u16 cd;

		cd = *calData++;
		addr = BaseAddr + cd;
		val = *calData++;
		val |= (*calData++) << 16;

		ath_reg_wr_nf(addr,val);
		udelay(100);
	}

	return;
}
#endif

/******************************************************************************/
/*!
** \brief pci host initialization
**
** Sets up the PCI controller on the host. For AR7240 this may not be necessary,
** but this function is required for board support.
**
** We want a 1:1 mapping between PCI and DDR for inbound and outbound.
** The PCI<---AHB decoding works as follows:
**
** 8 registers in the DDR unit provide software configurable 32 bit offsets
** for each of the eight 16MB PCI windows in the 128MB. The offsets will be
** added to any address in the 16MB segment before being sent to the PCI unit.
**
** Essentially for any AHB address generated by the CPU,
** 1. the MSB four bits are stripped off, [31:28],
** 2. Bit 27 is used to decide between the lower 128Mb (PCI) or the rest of
**    the AHB space
** 3. Bits 26:24 are used to access one of the 8 window registers and are
**    masked off.
** 4. If it is a PCI address, then the WINDOW offset in the WINDOW register
**    corresponding to the next 3 bits (bit 26:24) is ADDED to the address,
**    to generate the address to PCI unit.
**
**     eg. CPU address = 0x100000ff
**         window 0 offset = 0x10000000
**         This points to lowermost 16MB window in PCI space.
**         So the resulting address would be 0x000000ff+0x10000000
**         = 0x100000ff
**
**         eg2. CPU address = 0x120000ff
**         WINDOW 2 offset = 0x12000000
**         resulting address would be 0x000000ff+0x12000000
**                         = 0x120000ff
**
** There is no translation for inbound access (PCI device as a master)
**
**  \return N/A
*/

#ifdef  COMPRESSED_UBOOT
#	define PCI_INIT_RET_TYPE	int
#	define PCI_INIT_RETURN		return 0
#else
#	define PCI_INIT_RET_TYPE	void
#	define PCI_INIT_RETURN		return
#endif

PCI_INIT_RET_TYPE
pci_init_board (void)
{
#ifdef CONFIG_ATH_EMULATION
	prmsg("--- Skipping %s for emulation\n", __func__);
#else
	uint32_t cmd;

	if (is_drqfn()) {
		/*
		 * Dont enable PCIe in DRQFN package as it has some issues
		 * related to PCIe
		 */
		PCI_INIT_RETURN;
	}

	// common for rc1 and rc2
	ath_reg_wr_nf(PCIE_PLL_DITHER_DIV_MAX_ADDRESS,
		PCIE_PLL_DITHER_DIV_MAX_EN_DITHER_SET(0x1) |
		PCIE_PLL_DITHER_DIV_MAX_USE_MAX_SET(0x1) |
		PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_INT_SET(0x14) |
		PCIE_PLL_DITHER_DIV_MAX_DIV_MAX_FRAC_SET(0x3ff));

	ath_reg_wr_nf(PCIE_PLL_DITHER_DIV_MIN_ADDRESS,
		PCIE_PLL_DITHER_DIV_MIN_DIV_MIN_INT_SET(0x14));

	ath_reg_wr_nf(PCIE_PLL_CONFIG_ADDRESS,
		PCIE_PLL_CONFIG_REFDIV_SET(1) |
		PCIE_PLL_CONFIG_BYPASS_SET(1) |
		PCIE_PLL_CONFIG_PLLPWD_SET(1));
	udelay(10000);

	ath_reg_rmw_clear(PCIE_PLL_CONFIG_ADDRESS, PCIE_PLL_CONFIG_PLLPWD_SET(1));
	udelay(1000);
	ath_reg_rmw_clear(PCIE_PLL_CONFIG_ADDRESS, PCIE_PLL_CONFIG_BYPASS_SET(1));
	udelay(1000);

	if (!(ath_reg_rd(RST_BOOTSTRAP_ADDRESS) & RST_BOOTSTRAP_PCIE_RC_EP_SELECT_MASK)) {
		pci_rc2_init_board();
		return;
	}

	ath_reg_rmw_set(RST_RESET_ADDRESS, RST_RESET_PCIE_PHY_RESET_SET(1));
	udelay(10000);

	ath_reg_rmw_set(RST_RESET_ADDRESS, RST_RESET_PCIE_RESET_SET(1));
	udelay(10000);

	ath_reg_rmw_clear(RST_MISC2_ADDRESS, RST_MISC2_PERSTN_RCPHY_SET(1));
	udelay(10000);

	ath_reg_wr_nf(PCIE_RESET_ADDRESS, 0);	// Put endpoint in reset
	udelay(100000);

	ath_reg_rmw_set(RST_MISC2_ADDRESS, RST_MISC2_PERSTN_RCPHY_SET(1));
	udelay(10000);

	ath_reg_rmw_clear(RST_RESET_ADDRESS, RST_RESET_PCIE_PHY_RESET_SET(1));
	udelay(10000);

	ath_reg_rmw_clear(RST_RESET_ADDRESS, RST_RESET_PCIE_RESET_SET(1));
	udelay(10000);

	ath_reg_wr_nf(PCIE_APP_ADDRESS, PCIE_APP_PCIE_BAR_MSN_SET(1) |
					PCIE_APP_CFG_BE_SET(0xf) |
					PCIE_APP_SLV_RESP_ERR_MAP_SET(0x3f) |
					PCIE_APP_LTSSM_ENABLE_SET(1));

	cmd = PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER | PCI_COMMAND_INVALIDATE |
		PCI_COMMAND_PARITY | PCI_COMMAND_SERR | PCI_COMMAND_FAST_BACK;

	ath_local_write_config(PCI_COMMAND, 4, cmd);
	ath_local_write_config(0x20, 4, 0x1ff01000);
	ath_local_write_config(0x24, 4, 0x1ff01000);

	ath_reg_wr_nf(PCIE_RESET_ADDRESS, 4);	// Pull endpoint out of reset
	udelay(100000);

	/*
	 * Check if the WLAN PCI-E H/W is present, If the
	 * WLAN H/W is not present, skip the PCI platform
	 * initialization code and return
	 */
	if (((ath_reg_rd(PCIE_RESET_ADDRESS)) & 0x1) == 0x0) {
		prmsg("*** Warning *** : PCIe WLAN Module not found !!!\n");
	}

	pci_rc2_init_board();

#if !defined(COMPRESSED_UBOOT) && !defined(CONFIG_ATH_SKIP_REGISTER_PCI_API)
	/*
	 * Now, configure for u-boot tools
	 */

	hose.first_busno = 0;
	hose.last_busno = 0xff;

	/* System space */
	pci_set_region(	&hose.regions[0],
			0x80000000,
			0x00000000,
			32 * 1024 * 1024,
			PCI_REGION_MEM | PCI_REGION_SYS_MEMORY);

	/* PCI memory space */
	pci_set_region(	&hose.regions[1],
			0x10000000,
			0x10000000,
			128 * 1024 * 1024,
			PCI_REGION_MEM);

	hose.region_count = 2;

	pci_register_hose(&hose);

	pci_set_ops(	&hose,
			pci_hose_read_config_byte_via_dword,
			pci_hose_read_config_word_via_dword,
			ath_pci_read_config,
			pci_hose_write_config_byte_via_dword,
			pci_hose_write_config_word_via_dword,
			ath_pci_write_config);
#endif
	plat_dev_init();
#endif /* CONFIG_ATH_EMULATION */

	PCI_INIT_RETURN;
}

void
pci_rc2_init_board (void)
{
	uint32_t	cmd;

	ath_reg_rmw_set(RST_RESET2_ADDRESS, RST_RESET2_PCIE2_PHY_RESET_SET(1));
	udelay(10000);

	ath_reg_rmw_set(RST_RESET2_ADDRESS, RST_RESET2_PCIE2_RESET_SET(1));
	udelay(10000);

	ath_reg_rmw_clear(RST_MISC2_ADDRESS, RST_MISC2_PERSTN_RCPHY2_SET(1));
	udelay(10000);

	ath_reg_wr_nf(PCIE2_RESET_ADDRESS, 0);	// Put endpoint in reset
	udelay(100000);

	ath_reg_rmw_set(RST_MISC2_ADDRESS, RST_MISC2_PERSTN_RCPHY2_SET(1));
	udelay(10000);

	ath_reg_rmw_clear(RST_RESET2_ADDRESS, RST_RESET_PCIE_PHY_RESET_SET(1));
	udelay(10000);

	ath_reg_rmw_clear(RST_RESET2_ADDRESS, RST_RESET_PCIE_RESET_SET(1));
	udelay(10000);

	ath_reg_wr_nf(PCIE2_APP_ADDRESS, PCIE2_APP_PCIE2_BAR_MSN_SET(1) |
					PCIE2_APP_CFG_BE_SET(0xf) |
					PCIE2_APP_SLV_RESP_ERR_MAP_SET(0x3f) |
					PCIE2_APP_LTSSM_ENABLE_SET(1));

	cmd = PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER | PCI_COMMAND_INVALIDATE |
		PCI_COMMAND_PARITY | PCI_COMMAND_SERR | PCI_COMMAND_FAST_BACK;

	ath_local_write_config_rc2(PCI_COMMAND, 4, cmd);
	ath_local_write_config_rc2(0x20, 4, 0x1ff01000);
	ath_local_write_config_rc2(0x24, 4, 0x1ff01000);

	ath_reg_wr_nf(PCIE2_RESET_ADDRESS, 4);	// Pull endpoint out of reset
	udelay(100000);

	/*
	 * Check if the WLAN PCI-E H/W is present, If the
	 * WLAN H/W is not present, skip the PCI platform
	 * initialization code and return
	 */
	if (((ath_reg_rd(PCIE2_RESET_ADDRESS)) & 0x1) == 0x0) {
		prmsg("*** Warning *** : PCIe WLAN Module not found !!!\n");
		return;
	}
}

void pci_init(void)
{
	pci_init_board();
}

