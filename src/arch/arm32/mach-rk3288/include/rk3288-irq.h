#ifndef __RK3288_IRQ_H__
#define __RK3288_IRQ_H__

#ifdef __cplusplus
extern "C" {
#endif

#define RK3288_IRQ_HYPERVISOR_TIMER			(26)
#define RK3288_IRQ_VIRTUAL_TIMER			(27)
#define RK3288_IRQ_SECURE_PHYSICAL_TIMER	(29)
#define RK3288_IRQ_NONSECURE_PHYSICAL_TIMER	(30)

#define RK3288_IRQ_DMAC_BUS0				(32)
#define RK3288_IRQ_DMAC_BUS1				(33)
#define RK3288_IRQ_DMAC_PERI0				(34)
#define RK3288_IRQ_DMAC_PERI1				(35)
#define RK3288_IRQ_UPCTL0					(36)
#define RK3288_IRQ_UPCTL1					(37)
#define RK3288_IRQ_GPU_IRQJOB				(38)
#define RK3288_IRQ_GPU_IRQMMU				(39)
#define RK3288_IRQ_GPU_IRQGPU				(40)
#define RK3288_IRQ_VIDEO_ENCODER			(41)
#define RK3288_IRQ_VIDEO_DEECODER			(42)
#define RK3288_IRQ_VIDEO_MMU				(43)
#define RK3288_IRQ_HEVC						(44)
#define RK3288_IRQ_VIP						(45)
#define RK3288_IRQ_ISP						(46)
#define RK3288_IRQ_VOP_BIG					(47)
#define RK3288_IRQ_VOP_LIT					(48)
#define RK3288_IRQ_IEP						(49)
#define RK3288_IRQ_RGA						(50)
#define RK3288_IRQ_DSI0						(51)
#define RK3288_IRQ_DSI1						(52)
#define RK3288_IRQ_CSI0						(53)
#define RK3288_IRQ_CSI1						(54)
#define RK3288_IRQ_USBOTG					(55)
#define RK3288_IRQ_USBHOST0_EHCI			(56)
#define RK3288_IRQ_USBHOST1					(57)
#define RK3288_IRQ_HSIC						(58)
#define RK3288_IRQ_GMAC						(59)
#define RK3288_IRQ_GMAC_PMT					(60)
#define RK3288_IRQ_GPS						(61)
#define RK3288_IRQ_GPS_TIMER				(62)
#define RK3288_IRQ_TSI						(63)
#define RK3288_IRQ_SDMMC					(64)
#define RK3288_IRQ_SDIO0					(65)
#define RK3288_IRQ_SDIO1					(66)
#define RK3288_IRQ_EMMC						(67)
#define RK3288_IRQ_SARADC					(68)
#define RK3288_IRQ_TSADC					(69)
#define RK3288_IRQ_NANDC0					(70)
#define RK3288_IRQ_PERIMMU					(71)
#define RK3288_IRQ_NANDC1					(72)
#define RK3288_IRQ_USBHOST0_OHCI			(73)
#define RK3288_IRQ_TPS						(74)
#define RK3288_IRQ_SCR						(75)
#define RK3288_IRQ_SPI0						(76)
#define RK3288_IRQ_SPI1						(77)
#define RK3288_IRQ_SPI2						(78)
#define RK3288_IRQ_PS2C						(79)
#define RK3288_IRQ_CRYPTO					(80)
#define RK3288_IRQ_HOST_PULSE0				(81)
#define RK3288_IRQ_HOST_PULSE1				(82)
#define RK3288_IRQ_HOST0					(83)
#define RK3288_IRQ_HOST1					(84)
#define RK3288_IRQ_I2S						(85)
#define RK3288_IRQ_SPDIF					(86)
#define RK3288_IRQ_UART_BT					(87)
#define RK3288_IRQ_UART_BB					(88)
#define RK3288_IRQ_UART_DBG					(89)
#define RK3288_IRQ_UART_GPS					(90)
#define RK3288_IRQ_UART_EXP					(91)
#define RK3288_IRQ_I2C_PMU					(92)
#define RK3288_IRQ_I2C_AUDIO				(93)
#define RK3288_IRQ_I2C_SENSOR				(94)
#define RK3288_IRQ_I2C_CAM					(95)
#define RK3288_IRQ_I2C_TP					(96)
#define RK3288_IRQ_I2C_HDMI					(97)
#define RK3288_IRQ_TIMER6CH0				(98)
#define RK3288_IRQ_TIMER6CH1				(99)
#define RK3288_IRQ_TIMER6CH2				(100)
#define RK3288_IRQ_TIMER6CH3				(101)
#define RK3288_IRQ_TIMER6CH4				(102)
#define RK3288_IRQ_TIMER6CH5				(103)
#define RK3288_IRQ_TIMER2CH0				(104)
#define RK3288_IRQ_TIMER2CH1				(105)
#define RK3288_IRQ_PWM0						(106)
#define RK3288_IRQ_PWM1						(107)
#define RK3288_IRQ_PWM2						(108)
#define RK3288_IRQ_PWM3						(109)
#define RK3288_IRQ_RKPWM					(110)
#define RK3288_IRQ_WDT						(111)
#define RK3288_IRQ_PMU						(112)
#define RK3288_IRQ_GPIO0					(113)
#define RK3288_IRQ_GPIO1					(114)
#define RK3288_IRQ_GPIO2					(115)
#define RK3288_IRQ_GPIO3					(116)
#define RK3288_IRQ_GPIO4					(117)
#define RK3288_IRQ_GPIO5					(118)
#define RK3288_IRQ_GPIO6					(119)
#define RK3288_IRQ_GPIO7					(120)
#define RK3288_IRQ_GPIO8					(121)
#define RK3288_IRQ_AHB_ARBITER0				(122)
#define RK3288_IRQ_AHB_ARBITER1				(123)
#define RK3288_IRQ_AHB_ARBITER2				(124)
#define RK3288_IRQ_USBOTG_ID				(125)
#define RK3288_IRQ_USBOTG_BVALID			(126)
#define RK3288_IRQ_USBOTG_LINESTATE			(127)
#define RK3288_IRQ_USBHOST0_LINESTATE		(128)
#define RK3288_IRQ_USBHOST1_LINESTATE		(129)
#define RK3288_IRQ_USBOTG_EDP				(130)
#define RK3288_IRQ_SDMMC_DETECT				(131)
#define RK3288_IRQ_SDIO0_DETECT				(132)
#define RK3288_IRQ_SDIO1_DETECT				(133)
#define RK3288_IRQ_HDMI_WAKEUP				(134)
#define RK3288_IRQ_HDMI						(135)
#define RK3288_IRQ_CCP						(136)
#define RK3288_IRQ_CCS						(137)
#define RK3288_IRQ_SDMMC_DETECT_DUAL_EDGE	(138)
#define RK3288_IRQ_GPIO_B3_DUAL_EDGE		(139)
#define RK3288_IRQ_GPIO_C6_DUAL_EDGE		(140)
#define RK3288_IRQ_GPIO_A2_DUAL_EDGE		(141)
#define RK3288_IRQ_EDP_HDMI					(142)
#define RK3288_IRQ_HEVC_MMU					(143)

#define RK3288_IRQ_PMUIRQ0					(186)
#define RK3288_IRQ_PMUIRQ1					(187)
#define RK3288_IRQ_PMUIRQ2					(188)
#define RK3288_IRQ_PMUIRQ3					(189)

#define RK3288_IRQ_GPIO0_A0					(192)
#define RK3288_IRQ_GPIO0_A1					(193)
#define RK3288_IRQ_GPIO0_A2					(194)
#define RK3288_IRQ_GPIO0_A3					(195)
#define RK3288_IRQ_GPIO0_A4					(196)
#define RK3288_IRQ_GPIO0_A5					(197)
#define RK3288_IRQ_GPIO0_A6					(198)
#define RK3288_IRQ_GPIO0_A7					(199)
#define RK3288_IRQ_GPIO0_B0					(200)
#define RK3288_IRQ_GPIO0_B1					(201)
#define RK3288_IRQ_GPIO0_B2					(202)
#define RK3288_IRQ_GPIO0_B3					(203)
#define RK3288_IRQ_GPIO0_B4					(204)
#define RK3288_IRQ_GPIO0_B5					(205)
#define RK3288_IRQ_GPIO0_B6					(206)
#define RK3288_IRQ_GPIO0_B7					(207)
#define RK3288_IRQ_GPIO0_C0					(208)
#define RK3288_IRQ_GPIO0_C1					(209)
#define RK3288_IRQ_GPIO0_C2					(210)

#define RK3288_IRQ_GPIO1_D0					(248)
#define RK3288_IRQ_GPIO1_D1					(249)
#define RK3288_IRQ_GPIO1_D2					(250)
#define RK3288_IRQ_GPIO1_D3					(251)

#define RK3288_IRQ_GPIO2_A0					(256)
#define RK3288_IRQ_GPIO2_A1					(257)
#define RK3288_IRQ_GPIO2_A2					(258)
#define RK3288_IRQ_GPIO2_A3					(259)
#define RK3288_IRQ_GPIO2_A4					(260)
#define RK3288_IRQ_GPIO2_A5					(261)
#define RK3288_IRQ_GPIO2_A6					(262)
#define RK3288_IRQ_GPIO2_A7					(263)
#define RK3288_IRQ_GPIO2_B0					(264)
#define RK3288_IRQ_GPIO2_B1					(265)
#define RK3288_IRQ_GPIO2_B2					(266)
#define RK3288_IRQ_GPIO2_B3					(267)
#define RK3288_IRQ_GPIO2_B4					(268)
#define RK3288_IRQ_GPIO2_B5					(269)
#define RK3288_IRQ_GPIO2_B6					(270)
#define RK3288_IRQ_GPIO2_B7					(271)
#define RK3288_IRQ_GPIO2_C0					(272)
#define RK3288_IRQ_GPIO2_C1					(273)

#define RK3288_IRQ_GPIO3_A0					(288)
#define RK3288_IRQ_GPIO3_A1					(289)
#define RK3288_IRQ_GPIO3_A2					(290)
#define RK3288_IRQ_GPIO3_A3					(291)
#define RK3288_IRQ_GPIO3_A4					(292)
#define RK3288_IRQ_GPIO3_A5					(293)
#define RK3288_IRQ_GPIO3_A6					(294)
#define RK3288_IRQ_GPIO3_A7					(295)
#define RK3288_IRQ_GPIO3_B0					(296)
#define RK3288_IRQ_GPIO3_B1					(297)
#define RK3288_IRQ_GPIO3_B2					(298)
#define RK3288_IRQ_GPIO3_B3					(299)
#define RK3288_IRQ_GPIO3_B4					(300)
#define RK3288_IRQ_GPIO3_B5					(301)
#define RK3288_IRQ_GPIO3_B6					(302)
#define RK3288_IRQ_GPIO3_B7					(303)
#define RK3288_IRQ_GPIO3_C0					(304)
#define RK3288_IRQ_GPIO3_C1					(305)
#define RK3288_IRQ_GPIO3_C2					(306)
#define RK3288_IRQ_GPIO3_C3					(307)
#define RK3288_IRQ_GPIO3_C4					(308)
#define RK3288_IRQ_GPIO3_C5					(309)
#define RK3288_IRQ_GPIO3_C6					(310)
#define RK3288_IRQ_GPIO3_C7					(311)
#define RK3288_IRQ_GPIO3_D0					(312)
#define RK3288_IRQ_GPIO3_D1					(313)
#define RK3288_IRQ_GPIO3_D2					(314)
#define RK3288_IRQ_GPIO3_D3					(315)
#define RK3288_IRQ_GPIO3_D4					(316)
#define RK3288_IRQ_GPIO3_D5					(317)
#define RK3288_IRQ_GPIO3_D6					(318)
#define RK3288_IRQ_GPIO3_D7					(319)

#define RK3288_IRQ_GPIO4_A0					(320)
#define RK3288_IRQ_GPIO4_A1					(321)
#define RK3288_IRQ_GPIO4_A2					(322)
#define RK3288_IRQ_GPIO4_A3					(323)
#define RK3288_IRQ_GPIO4_A4					(324)
#define RK3288_IRQ_GPIO4_A5					(325)
#define RK3288_IRQ_GPIO4_A6					(326)
#define RK3288_IRQ_GPIO4_A7					(327)
#define RK3288_IRQ_GPIO4_B0					(328)
#define RK3288_IRQ_GPIO4_B1					(329)
#define RK3288_IRQ_GPIO4_B2					(330)
#define RK3288_IRQ_GPIO4_B3					(331)
#define RK3288_IRQ_GPIO4_B4					(332)
#define RK3288_IRQ_GPIO4_B5					(333)
#define RK3288_IRQ_GPIO4_B6					(334)
#define RK3288_IRQ_GPIO4_B7					(335)
#define RK3288_IRQ_GPIO4_C0					(336)
#define RK3288_IRQ_GPIO4_C1					(337)
#define RK3288_IRQ_GPIO4_C2					(338)
#define RK3288_IRQ_GPIO4_C3					(339)
#define RK3288_IRQ_GPIO4_C4					(340)
#define RK3288_IRQ_GPIO4_C5					(341)
#define RK3288_IRQ_GPIO4_C6					(342)
#define RK3288_IRQ_GPIO4_C7					(343)
#define RK3288_IRQ_GPIO4_D0					(344)
#define RK3288_IRQ_GPIO4_D1					(345)
#define RK3288_IRQ_GPIO4_D2					(346)
#define RK3288_IRQ_GPIO4_D3					(347)
#define RK3288_IRQ_GPIO4_D4					(348)
#define RK3288_IRQ_GPIO4_D5					(349)
#define RK3288_IRQ_GPIO4_D6					(350)
#define RK3288_IRQ_GPIO4_D7					(351)

#define RK3288_IRQ_GPIO5_B0					(360)
#define RK3288_IRQ_GPIO5_B1					(361)
#define RK3288_IRQ_GPIO5_B2					(362)
#define RK3288_IRQ_GPIO5_B3					(363)
#define RK3288_IRQ_GPIO5_B4					(364)
#define RK3288_IRQ_GPIO5_B5					(365)
#define RK3288_IRQ_GPIO5_B6					(366)
#define RK3288_IRQ_GPIO5_B7					(367)
#define RK3288_IRQ_GPIO5_C0					(368)
#define RK3288_IRQ_GPIO5_C1					(369)
#define RK3288_IRQ_GPIO5_C2					(370)
#define RK3288_IRQ_GPIO5_C3					(371)

#define RK3288_IRQ_GPIO6_A0					(384)
#define RK3288_IRQ_GPIO6_A1					(385)
#define RK3288_IRQ_GPIO6_A2					(386)
#define RK3288_IRQ_GPIO6_A3					(387)
#define RK3288_IRQ_GPIO6_A4					(388)
#define RK3288_IRQ_GPIO6_A5					(389)
#define RK3288_IRQ_GPIO6_A6					(390)
#define RK3288_IRQ_GPIO6_A7					(391)
#define RK3288_IRQ_GPIO6_B0					(392)
#define RK3288_IRQ_GPIO6_B1					(393)
#define RK3288_IRQ_GPIO6_B2					(394)
#define RK3288_IRQ_GPIO6_B3					(395)
#define RK3288_IRQ_GPIO6_C0					(400)
#define RK3288_IRQ_GPIO6_C1					(401)
#define RK3288_IRQ_GPIO6_C2					(402)
#define RK3288_IRQ_GPIO6_C3					(403)
#define RK3288_IRQ_GPIO6_C4					(404)
#define RK3288_IRQ_GPIO6_C5					(405)
#define RK3288_IRQ_GPIO6_C6					(406)

#define RK3288_IRQ_GPIO7_A0					(416)
#define RK3288_IRQ_GPIO7_A1					(417)
#define RK3288_IRQ_GPIO7_A2					(418)
#define RK3288_IRQ_GPIO7_A3					(419)
#define RK3288_IRQ_GPIO7_A4					(420)
#define RK3288_IRQ_GPIO7_A5					(421)
#define RK3288_IRQ_GPIO7_A6					(422)
#define RK3288_IRQ_GPIO7_A7					(423)
#define RK3288_IRQ_GPIO7_B0					(424)
#define RK3288_IRQ_GPIO7_B1					(425)
#define RK3288_IRQ_GPIO7_B2					(426)
#define RK3288_IRQ_GPIO7_B3					(427)
#define RK3288_IRQ_GPIO7_B4					(428)
#define RK3288_IRQ_GPIO7_B5					(429)
#define RK3288_IRQ_GPIO7_B6					(430)
#define RK3288_IRQ_GPIO7_B7					(431)
#define RK3288_IRQ_GPIO7_C0					(432)
#define RK3288_IRQ_GPIO7_C1					(433)
#define RK3288_IRQ_GPIO7_C2					(434)
#define RK3288_IRQ_GPIO7_C3					(435)
#define RK3288_IRQ_GPIO7_C4					(436)
#define RK3288_IRQ_GPIO7_C5					(437)
#define RK3288_IRQ_GPIO7_C6					(438)
#define RK3288_IRQ_GPIO7_C7					(439)

#define RK3288_IRQ_GPIO8_A0					(448)
#define RK3288_IRQ_GPIO8_A1					(449)
#define RK3288_IRQ_GPIO8_A2					(450)
#define RK3288_IRQ_GPIO8_A3					(451)
#define RK3288_IRQ_GPIO8_A4					(452)
#define RK3288_IRQ_GPIO8_A5					(453)
#define RK3288_IRQ_GPIO8_A6					(454)
#define RK3288_IRQ_GPIO8_A7					(455)
#define RK3288_IRQ_GPIO8_B0					(456)
#define RK3288_IRQ_GPIO8_B1					(457)

#ifdef __cplusplus
}
#endif

#endif /* __RK3288_IRQ_H__ */