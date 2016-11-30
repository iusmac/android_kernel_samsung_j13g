/*
 *
 * Zinitix bt432 touch driver
 *
 * Copyright (C) 2013 Samsung Electronics Co.Ltd
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 */


#ifndef _LINUX_BT432_TS_H
#define _LINUX_BT432_TS_H

#define TS_DRVIER_VERSION	"1.0.18_1"

#define BT432_TS_DEVICE		"bt432_ts"

#define zinitix_debug_msg(fmt, args...) \
	do { \
		if (m_ts_debug_mode) \
			printk(KERN_INFO "bt432_ts[%-18s:%5d] " fmt, \
					__func__, __LINE__, ## args); \
	} while (0);

#define zinitix_printk(fmt, args...) \
	do { \
		printk(KERN_INFO "bt432_ts[%-18s:%5d] " fmt, \
				__func__, __LINE__, ## args); \
	} while (0);

struct bt432_ts_platform_data {
	u32	gpio_int;
	u32	gpio_ldo_en;
	int     (*tsp_power)(struct bt432_ts_info *info, int on);
	u32	x_resolution;
	u32	y_resolution;
	u32	page_size;
	u32	orientation;
	u32		tsp_supply_type;
};

extern struct class *sec_class;

/* SPEC V0.2 */
static const u16 dnd_v_diff[18][10] = {
	{4370,	4750,	4600,	4680,	4610,	4600,	4560,	4620,	4550,	4820},
	{2300,	2730,	2580,	2670,	2590,	2600,	2570,	2650,	2620,	2920},
	{2350,	3020,	2710,	2770,	2720,	2730,	2690,	2730,	2700,	3080},
	{2510,	2150,	2130,	2120,	2130,	2130,	2160,	2120,	2110,	2340},
	{2130,	2430,	2390,	2400,	2390,	2390,	2360,	2400,	2380,	2840},
	{2730,	2350,	2260,	2250,	2270,	2240,	2280,	2230,	2250,	2360},
	{2330,	2160,	2300,	2300,	2290,	2310,	2280,	2310,	2310,	2870},
	{2880,	2440,	2260,	2290,	2290,	2270,	2290,	2260,	2270,	2470},
	{2570,	2110,	2260,	2240,	2250,	2250,	2230,	2240,	2240,	2940},
	{3200,	2470,	2330,	2340,	2360,	2350,	2360,	2330,	2340,	2620},
	{2870,	2100,	2230,	2210,	2210,	2210,	2200,	2210,	2200,	3150},
	{4920,	3150,	3020,	3040,	3030,	3070,	3030,	3020,	3030,	2590},
	{4250,	2350,	2510,	2490,	2500,	2500,	2490,	2490,	2510,	4120},
	{2350,	5610,	5650,	5640,	5650,	4810,	5570,	5530,	5330,	4920},
	{4220,	2830,	2780,	2810,	2780,	2840,	2790,	2800,	2810,	2470},
	{2710,	2070,	2090,	2090,	2070,	2330,	2050,	2050,	2060,	2860},
	{4940,	4580,	4570,	4580,	4600,	4640,	4680,	4650,	4670,	4280},
	{0,	0,	0,	0,	6520,	0,	0,	6410,	0,	0}
};

static const u16 dnd_h_diff[19][9] = {
	{2040,	2100,	2060,	2110,	2060,	2080,	2030,	2160,	2330},
	{2360,	2190,	2060,	2050,	2070,	2080,	2080,	2230,	2060},
	{2080,	2080,	2060,	2100,	2070,	2060,	2040,	2200,	2360},
	{2610,	2350,	2030,	2070,	2070,	2060,	2030,	2220,	2030},
	{2050,	2110,	2030,	2070,	2070,	2050,	2040,	2230,	2420},
	{2520,	2140,	2030,	2060,	2060,	2050,	2040,	2250,	2050},
	{2130,	2210,	2030,	2080,	2090,	2050,	2040,	2230,	2560},
	{2590,	2090,	2030,	2060,	2070,	2060,	2030,	2270,	2060},
	{2150,	2230,	2030,	2060,	2080,	2050,	2040,	2260,	2680},
	{2770,	2080,	2030,	2070,	2080,	2050,	2030,	2250,	2050},
	{2040,	2180,	2030,	2080,	2100,	2050,	2050,	2250,	2920},
	{2990,	2070,	2030,	2080,	2090,	2060,	2040,	2260,	2060},
	{2780,	2170,	2040,	2080,	2060,	2070,	2050,	2250,	3580},
	{3820,	2050,	2030,	2080,	2050,	2090,	2050,	2230,	2060},
	{4140,	2080,	2030,	2070,	2800,	2850,	2030,	2060,	2460},
	{2750,	2070,	2030,	2090,	2740,	2800,	2030,	2070,	3730},
	{3500,	2080,	2040,	2110,	3110,	3090,	2030,	2090,	2840},
	{3130,	2100,	2040,	2110,	3070,	3130,	2040,	2080,	3230},
	{0,	0,	0,	0,	0,	0,	0,	2130,	0}
};

static const u16 pdnd_max[19][10] = {
	{15666,	15694,	15730,	15671,	15835,	15799,	15814,	15806,	15734,	15426},
	{18131,	18604,	18391,	18416,	18447,	18379,	18474,	18477,	18377,	18283},
	{17756,	17721,	17741,	17647,	17818,	17757,	17798,	17778,	17642,	17322},
	{18139,	18653,	18471,	18423,	18517,	18455,	18495,	18487,	18383,	18387},
	{18613,	18552,	18582,	18522,	18649,	18546,	18624,	18576,	18434,	18045},
	{18448,	18982,	18950,	18978,	19008,	18936,	18943,	18967,	18785,	18852},
	{19197,	19274,	19241,	19186,	19253,	19175,	19198,	19172,	19028,	18478},
	{18678,	19240,	19320,	19282,	19316,	19237,	19278,	19239,	18960,	19151},
	{19691,	19912,	19672,	19734,	19748,	19668,	19691,	19641,	19468,	18871},
	{18982,	19702,	19760,	19788,	19793,	19735,	19722,	19721,	19578,	19573},
	{20325,	20382,	20259,	20263,	20326,	20246,	20264,	20193,	20026,	19205},
	{19457,	20448,	20453,	20472,	20572,	20461,	20454,	20416,	20175,	20267},
	{22391,	21646,	21502,	21533,	21610,	21552,	21496,	21454,	21262,	19727},
	{20170,	21991,	22028,	22021,	22164,	22074,	22002,	21962,	21779,	21816},
	{20436,	18386,	18428,	18439,	18460,	19262,	18454,	18452,	18498,	18952},
	{18289,	17607,	17682,	17655,	17713,	18445,	17690,	17708,	17764,	19404},
	{19058,	17620,	17691,	17682,	17738,	18797,	17788,	17783,	17876,	18675},
	{16017,	14925,	14994,	14993,	15059,	16104,	15019,	15057,	15107,	16292},
	{0,	0,	0,	0,	18074,	0,	0,	17900,	0,	0}
};

static const u16 pdnd_min[19][10] = {
	{6390,	6418,	6454,	6395,	6559,	6523,	6538,	6530,	6458,	6150},
	{8855,	9328,	9115,	9140,	9171,	9103,	9198,	9201,	9101,	9007},
	{8480,	8445,	8465,	8371,	8542,	8481,	8522,	8502,	8366,	8046},
	{8863,	9377,	9195,	9147,	9241,	9179,	9219,	9211,	9107,	9111},
	{9337,	9276,	9306,	9246,	9373,	9270,	9348,	9300,	9158,	8769},
	{9172,	9706,	9674,	9702,	9732,	9660,	9667,	9691,	9509,	9576},
	{9921,	9998,	9965,	9910,	9977,	9899,	9922,	9896,	9752,	9202},
	{9402,	9964,	10044,	10006,	10040,	9961,	10002,	9963,	9684,	9875},
	{10415,	10636,	10396,	10458,	10472,	10392,	10415,	10365,	10192,	9595},
	{9706,	10426,	10484,	10512,	10517,	10459,	10446,	10445,	10302,	10297},
	{11049,	11106,	10983,	10987,	11050,	10970,	10988,	10917,	10750,	9929},
	{10181,	11172,	11177,	11196,	11296,	11185,	11178,	11140,	10899,	10991},
	{13115,	12370,	12226,	12257,	12334,	12276,	12220,	12178,	11986,	10451},
	{10894,	12715,	12752,	12745,	12888,	12798,	12726,	12686,	12503,	12540},
	{11160,	9110,	9152,	9163,	9184,	9986,	9178,	9176,	9222,	9676},
	{9013,	8331,	8406,	8379,	8437,	9169,	8414,	8432,	8488,	10128},
	{9782,	8344,	8415,	8406,	8462,	9521,	8512,	8507,	8600,	9399},
	{6741,	5649,	5718,	5717,	5783,	6828,	5743,	5781,	5831,	7016},
	{0,	0,	0,	0,	9732,	0,	0,	9638,	0,	0}
};

static const u16 (*hfdnd_max)[10], (*hfdnd_min)[10];

static const u16 assy_hfdnd_max[19][10] = {
	{13241,	13181,	12990,	12938,	13181,	13036,	13131,	13143,	12989,	12699},
	{15091,	15340,	15062,	15045,	15223,	14990,	15158,	15174,	14994,	15002},
	{14588,	14458,	14295,	14225,	14430,	14166,	14416,	14372,	14171,	13876},
	{14460,	15050,	14604,	14570,	14706,	14394,	14689,	14660,	14464,	14502},
	{14554,	14482,	14342,	14323,	14451,	14067,	14468,	14389,	14111,	13716},
	{13882,	14350,	14177,	14178,	14265,	13863,	14271,	14220,	13932,	14036},
	{14231,	14274,	14029,	13994,	14118,	13631,	14127,	14054,	13736,	13116},
	{13256,	13912,	13783,	13758,	13920,	13318,	13854,	13802,	13459,	13526},
	{13797,	13849,	13559,	13559,	13652,	13019,	13629,	13549,	13232,	12322},
	{12420,	13398,	13306,	13262,	13381,	12685,	13349,	13263,	12955,	12966},
	{13632,	13526,	13275,	13279,	13423,	12581,	13360,	13271,	12916,	11560},
	{11665,	13146,	13027,	13035,	13163,	12283,	13099,	12987,	12683,	12756},
	{14554,	13511,	13304,	13263,	13368,	12366,	13319,	13197,	12839,	10705},
	{10913,	13343,	13280,	13285,	13355,	12292,	13291,	13186,	12821,	13127},
	{15245,	12497,	12323,	12340,	12510,	11676,	12538,	12466,	12328,	12461},
	{12547,	11978,	11856,	11838,	12050,	11223,	12042,	11997,	11893,	13993},
	{12811,	11016,	10838,	10823,	11075,	10432,	11116,	11070,	10958,	11851},
	{11076,	9792,	9638,	9618,	9843,	9410,	9834,	9812,	9709,	11176},
	{0,	0,	0,	0,	11123,	0,	0,	11111,	0,	0}
};

static const u16 assy_hfdnd_min[19][10] = {
	{6865,	6805,	6614,	6562,	6805,	6660,	6755,	6767,	6613,	6323},
	{8715,	8964,	8686,	8669,	8847,	8614,	8782,	8798,	8618,	8626},
	{8212,	8082,	7919,	7849,	8054,	7790,	8040,	7996,	7795,	7500},
	{8084,	8674,	8228,	8194,	8330,	8018,	8313,	8284,	8088,	8126},
	{8178,	8106,	7966,	7947,	8075,	7691,	8092,	8013,	7735,	7340},
	{7506,	7974,	7801,	7802,	7889,	7487,	7895,	7844,	7556,	7660},
	{7855,	7898,	7653,	7618,	7742,	7255,	7751,	7678,	7360,	6740},
	{6880,	7536,	7407,	7382,	7544,	6942,	7478,	7426,	7083,	7150},
	{7421,	7473,	7183,	7183,	7276,	6643,	7253,	7173,	6856,	5946},
	{6044,	7022,	6930,	6886,	7005,	6309,	6973,	6887,	6579,	6590},
	{7256,	7150,	6899,	6903,	7047,	6205,	6984,	6895,	6540,	5184},
	{5289,	6770,	6651,	6659,	6787,	5907,	6723,	6611,	6307,	6380},
	{8178,	7135,	6928,	6887,	6992,	5990,	6943,	6821,	6463,	4329},
	{4537,	6967,	6904,	6909,	6979,	5916,	6915,	6810,	6445,	6751},
	{8869,	6121,	5947,	5964,	6134,	5300,	6162,	6090,	5952,	6085},
	{6171,	5602,	5480,	5462,	5674,	4847,	5666,	5621,	5517,	7617},
	{6435,	4640,	4462,	4447,	4699,	4056,	4740,	4694,	4582,	5475},
	{4700,	3416,	3262,	3242,	3467,	3034,	3458,	3436,	3333,	4800},
	{0,	0,	0,	0,	4747,	0,	0,	4735,	0,	0}
};

static const u16 tsp_hfdnd_max[19][10] = {
	{13799,	13779,	13755,	13784,	13790,	13676,	13850,	13903,	13732,	13547},
	{15621,	15848,	15764,	15874,	15855,	15635,	15793,	15898,	15687,	15766},
	{15203,	15173,	15155,	15201,	15214,	14976,	15217,	15239,	15063,	14778},
	{15224,	15688,	15474,	15585,	15566,	15256,	15527,	15593,	15381,	15461},
	{15284,	15321,	15269,	15366,	15422,	15030,	15353,	15360,	15148,	14702},
	{14596,	15217,	15124,	15246,	15287,	14849,	15147,	15182,	14980,	15037},
	{14979,	15253,	14964,	15115,	15180,	14660,	15074,	15031,	14845,	14180},
	{14022,	14865,	14788,	14884,	14997,	14383,	14847,	14841,	14622,	14676},
	{14610,	15088,	14584,	14680,	14711,	14114,	14717,	14666,	14456,	13462},
	{13274,	14439,	14362,	14440,	14564,	13809,	14437,	14444,	14228,	14318},
	{14485,	14801,	14389,	14479,	14635,	13734,	14493,	14525,	14274,	12730},
	{12511,	14292,	14238,	14285,	14394,	13432,	14274,	14294,	14066,	14253},
	{15149,	14625,	14520,	14610,	14651,	13636,	14603,	14681,	14433,	11937},
	{11855,	14648,	14650,	14652,	14740,	13576,	14636,	14682,	14472,	14922},
	{16913,	13645,	13549,	13639,	13634,	12599,	13464,	13645,	13607,	13887},
	{13747,	13098,	12971,	13126,	13125,	12098,	13115,	13083,	13072,	16074},
	{14120,	12010,	11878,	11922,	11948,	11101,	11985,	11997,	12036,	13268},
	{12279,	10723,	10611,	10614,	10610,	9994,	10631,	10621,	10655,	12640},
	{0,	0,	0,	0,	10498,	0,	0,	10483,	0,	0}
};

static const u16 tsp_hfdnd_min[19][10] = {
	{6609,	6589,	6565,	6594,	6600,	6486,	6660,	6713,	6542,	6357},
	{8431,	8658,	8574,	8684,	8665,	8445,	8603,	8708,	8497,	8576},
	{8013,	7983,	7965,	8011,	8024,	7786,	8027,	8049,	7873,	7588},
	{8034,	8498,	8284,	8395,	8376,	8066,	8337,	8403,	8191,	8271},
	{8094,	8131,	8079,	8176,	8232,	7840,	8163,	8170,	7958,	7512},
	{7406,	8027,	7934,	8056,	8097,	7659,	7957,	7992,	7790,	7847},
	{7789,	8063,	7774,	7925,	7990,	7470,	7884,	7841,	7655,	6990},
	{6832,	7675,	7598,	7694,	7807,	7193,	7657,	7651,	7432,	7486},
	{7420,	7898,	7394,	7490,	7521,	6924,	7527,	7476,	7266,	6272},
	{6084,	7249,	7172,	7250,	7374,	6619,	7247,	7254,	7038,	7128},
	{7295,	7611,	7199,	7289,	7445,	6544,	7303,	7335,	7084,	5540},
	{5321,	7102,	7048,	7095,	7204,	6242,	7084,	7104,	6876,	7063},
	{7959,	7435,	7330,	7420,	7461,	6446,	7413,	7491,	7243,	4747},
	{4665,	7458,	7460,	7462,	7550,	6386,	7446,	7492,	7282,	7732},
	{9723,	6455,	6359,	6449,	6444,	5409,	6274,	6455,	6417,	6697},
	{6557,	5908,	5781,	5936,	5935,	4908,	5925,	5893,	5882,	8884},
	{6930,	4820,	4688,	4732,	4758,	3911,	4795,	4807,	4846,	6078},
	{5089,	3533,	3421,	3424,	3420,	2804,	3441,	3431,	3465,	5450},
	{0,	0,	0,	0,	3308,	0,	0,	3293,	0,	0}
};

#endif /* LINUX_BT531_TS_H */