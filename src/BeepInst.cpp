/*
 *  BASS, a MIDI controled synthesizer for MSDOS systems using Adlib or 
 *  Soundblaster with MPU-401 UART compatible interfaces.
 *  Copyright (C) 2011  Kyle Delaney
 *
 *  This file is a part of BASS.
 *
 *  BASS is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  BASS is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  You may contact the author at <dr.kylstein@gmail.com>
 */
#include "BeepInst.hpp"
#include "Speaker.hpp"
const unsigned short int BeeperInstrument::_timingTable[2048] = {
	14868, 14342, 13818, 13296, 12776, 12257, 11741, 11226, 10713, 10202, 9693, 9186, 8681, 8177, 7675, 7175, 6677, 6181
, 5686, 5193, 4702, 4213, 3725, 3240, 2756, 2273, 1793, 1314, 837, 361, 65424, 64952, 64482, 64013, 63546, 63081, 62618, 
62156, 61696, 61237, 60780, 60325, 59872, 59420, 58969, 58521, 58074, 57628, 57184, 56742, 56301, 55862, 55425, 54989, 54555
, 54122, 53691, 53261, 52833, 52406, 51981, 51558, 51136, 50715, 50297, 49879, 49463, 49049, 48636, 48224, 47814, 47406, 
46999, 46593, 46189, 45787, 45386, 44986, 44588, 44191, 43795, 43401, 43009, 42618, 42228, 41840, 41453, 41067, 40683, 40300
, 39919, 39539, 39160, 38783, 38407, 38032, 37659, 37287, 36917, 36547, 36180, 35813, 35448, 35084, 34721, 34360, 34000, 
33641, 33284, 32928, 32573, 32219, 31867, 31516, 31166, 30818, 30471, 30125, 29780, 29436, 29094, 28753, 28413, 28075, 27737
, 27401, 27066, 26733, 26400, 26069, 25739, 25410, 25082, 24756, 24430, 24106, 23783, 23461, 23140, 22821, 22502, 22185, 
21869, 21554, 21240, 20928, 20616, 20305, 19996, 19688, 19381, 19075, 18770, 18466, 18163, 17862, 17561, 17262, 16963, 16666
, 16370, 16075, 15781, 15488, 15196, 14905, 14615, 14326, 14038, 13751, 13466, 13181, 12897, 12615, 12333, 12052, 11773, 
11494, 11217, 10940, 10664, 10390, 10116, 9844, 9572, 9301, 9032, 8763, 8495, 8228, 7963, 7698, 7434, 7171, 6909, 6648, 6388
, 6128, 5870, 5613, 5356, 5101, 4846, 4593, 4340, 4088, 3837, 3587, 3338, 3090, 2843, 2596, 2351, 2106, 1862, 1620, 1378, 
1136, 896, 657, 418, 180, 65480, 65244, 65009, 64774, 64541, 64308, 64077, 63846, 63616, 63386, 63158, 62930, 62704, 62478, 
62252, 62028, 61805, 61582, 61360, 61139, 60918, 60699, 60480, 60262, 60045, 59829, 59613, 59398, 59184, 58971, 58758, 58547
, 58336, 58125, 57916, 57707, 57499, 57292, 57086, 56880, 56675, 56471, 56267, 56064, 55862, 55661, 55461, 55261, 55062, 
54863, 54665, 54468, 54272, 54077, 53882, 53688, 53494, 53301, 53109, 52918, 52727, 52537, 52348, 52159, 51971, 51784, 51597
, 51411, 51226, 51041, 50858, 50674, 50492, 50310, 50128, 49948, 49768, 49588, 49410, 49232, 49054, 48877, 48701, 48526, 
48351, 48177, 48003, 47830, 47658, 47486, 47315, 47144, 46974, 46805, 46636, 46468, 46301, 46134, 45968, 45802, 45637, 45473
, 45309, 45146, 44983, 44821, 44659, 44498, 44338, 44178, 44019, 43860, 43702, 43545, 43388, 43232, 43076, 42920, 42766, 
42612, 42458, 42305, 42153, 42001, 41849, 41699, 41548, 41399, 41249, 41101, 40953, 40805, 40658, 40512, 40366, 40220, 40075
, 39931, 39787, 39643, 39501, 39358, 39216, 39075, 38934, 38794, 38654, 38515, 38376, 38238, 38100, 37963, 37826, 37690, 
37554, 37418, 37284, 37149, 37015, 36882, 36749, 36617, 36485, 36353, 36222, 36092, 35962, 35832, 35703, 35574, 35446, 35318
, 35191, 35064, 34938, 34812, 34686, 34561, 34437, 34313, 34189, 34066, 33943, 33821, 33699, 33578, 33457, 33336, 33216, 
33096, 32977, 32858, 32740, 32622, 32504, 32387, 32270, 32154, 32038, 31923, 31808, 31693, 31579, 31465, 31352, 31239, 31126
, 31014, 30902, 30791, 30680, 30569, 30459, 30349, 30240, 30131, 30022, 29914, 29806, 29699, 29592, 29485, 29379, 29273, 
29168, 29062, 28958, 28853, 28749, 28646, 28543, 28440, 28337, 28235, 28133, 28032, 27931, 27830, 27730, 27630, 27531, 27431
, 27332, 27234, 27136, 27038, 26941, 26844, 26747, 26650, 26554, 26459, 26363, 26268, 26174, 26079, 25985, 25892, 25798, 
25705, 25613, 25520, 25429, 25337, 25246, 25155, 25064, 24974, 24884, 24794, 24705, 24616, 24527, 24438, 24350, 24263, 24175
, 24088, 24001, 23915, 23829, 23743, 23657, 23572, 23487, 23402, 23318, 23234, 23150, 23067, 22984, 22901, 22818, 22736, 
22654, 22573, 22491, 22410, 22329, 22249, 22169, 22089, 22009, 21930, 21851, 21772, 21694, 21616, 21538, 21460, 21383, 21306
, 21229, 21152, 21076, 21000, 20924, 20849, 20774, 20699, 20624, 20550, 20476, 20402, 20329, 20256, 20183, 20110, 20037, 
19965, 19893, 19821, 19750, 19679, 19608, 19537, 19467, 19397, 19327, 19257, 19188, 19119, 19050, 18981, 18913, 18845, 18777
, 18709, 18642, 18574, 18507, 18441, 18374, 18308, 18242, 18176, 18111, 18046, 17981, 17916, 17851, 17787, 17723, 17659, 
17595, 17532, 17469, 17406, 17343, 17280, 17218, 17156, 17094, 17033, 16971, 16910, 16849, 16789, 16728, 16668, 16608, 16548
, 16488, 16429, 16370, 16311, 16252, 16193, 16135, 16077, 16019, 15961, 15904, 15846, 15789, 15732, 15676, 15619, 15563, 
15507, 15451, 15395, 15340, 15284, 15229, 15174, 15120, 15065, 15011, 14957, 14903, 14849, 14796, 14742, 14689, 14636, 14584
, 14531, 14479, 14426, 14374, 14323, 14271, 14220, 14168, 14117, 14066, 14016, 13965, 13915, 13865, 13815, 13765, 13715, 
13666, 13617, 13568, 13519, 13470, 13422, 13373, 13325, 13277, 13229, 13181, 13134, 13087, 13039, 12992, 12946, 12899, 12852
, 12806, 12760, 12714, 12668, 12623, 12577, 12532, 12487, 12442, 12397, 12352, 12308, 12263, 12219, 12175, 12131, 12087, 
12044, 12000, 11957, 11914, 11871, 11828, 11786, 11743, 11701, 11659, 11617, 11575, 11533, 11492, 11450, 11409, 11368, 11327
, 11286, 11245, 11205, 11164, 11124, 11084, 11044, 11004, 10965, 10925, 10886, 10847, 10808, 10769, 10730, 10691, 10653, 
10614, 10576, 10538, 10500, 10462, 10424, 10387, 10349, 10312, 10275, 10238, 10201, 10164, 10128, 10091, 10055, 10018, 9982,
 9946, 9910, 9875, 9839, 9804, 9768, 9733, 9698, 9663, 9628, 9594, 9559, 9525, 9490, 9456, 9422, 9388, 9354, 9321, 9287, 
9253, 9220, 9187, 9154, 9121, 9088, 9055, 9023, 8990, 8958, 8925, 8893, 8861, 8829, 8797, 8766, 8734, 8703, 8671, 8640, 8609
, 8578, 8547, 8516, 8485, 8455, 8424, 8394, 8364, 8334, 8304, 8274, 8244, 8214, 8185, 8155, 8126, 8096, 8067, 8038, 8009, 
7980, 7952, 7923, 7894, 7866, 7838, 7809, 7781, 7753, 7725, 7697, 7670, 7642, 7614, 7587, 7560, 7532, 7505, 7478, 7451, 7424
, 7398, 7371, 7344, 7318, 7292, 7265, 7239, 7213, 7187, 7161, 7135, 7110, 7084, 7058, 7033, 7008, 6982, 6957, 6932, 6907, 
6882, 6857, 6833, 6808, 6784, 6759, 6735, 6711, 6686, 6662, 6638, 6614, 6590, 6567, 6543, 6519, 6496, 6473, 6449, 6426, 6403
, 6380, 6357, 6334, 6311, 6288, 6266, 6243, 6221, 6198, 6176, 6154, 6131, 6109, 6087, 6065, 6043, 6022, 6000, 5978, 5957, 
5935, 5914, 5893, 5871, 5850, 5829, 5808, 5787, 5766, 5746, 5725, 5704, 5684, 5663, 5643, 5622, 5602, 5582, 5562, 5542, 5522
, 5502, 5482, 5462, 5443, 5423, 5404, 5384, 5365, 5345, 5326, 5307, 5288, 5269, 5250, 5231, 5212, 5193, 5174, 5156, 5137, 
5119, 5100, 5082, 5064, 5045, 5027, 5009, 4991, 4973, 4955, 4937, 4919, 4902, 4884, 4866, 4849, 4831, 4814, 4797, 4779, 4762
, 4745, 4728, 4711, 4694, 4677, 4660, 4643, 4626, 4610, 4593, 4577, 4560, 4544, 4527, 4511, 4495, 4479, 4462, 4446, 4430, 
4414, 4398, 4383, 4367, 4351, 4335, 4320, 4304, 4289, 4273, 4258, 4242, 4227, 4212, 4197, 4182, 4167, 4152, 4137, 4122, 4107
, 4092, 4077, 4063, 4048, 4033, 4019, 4004, 3990, 3976, 3961, 3947, 3933, 3919, 3904, 3890, 3876, 3862, 3848, 3835, 3821, 
3807, 3793, 3780, 3766, 3752, 3739, 3725, 3712, 3699, 3685, 3672, 3659, 3646, 3632, 3619, 3606, 3593, 3580, 3567, 3555, 3542
, 3529, 3516, 3504, 3491, 3478, 3466, 3453, 3441, 3428, 3416, 3404, 3392, 3379, 3367, 3355, 3343, 3331, 3319, 3307, 3295, 
3283, 3271, 3259, 3248, 3236, 3224, 3213, 3201, 3190, 3178, 3167, 3155, 3144, 3133, 3121, 3110, 3099, 3088, 3077, 3065, 3054
, 3043, 3032, 3021, 3011, 3000, 2989, 2978, 2967, 2957, 2946, 2935, 2925, 2914, 2904, 2893, 2883, 2873, 2862, 2852, 2842, 
2831, 2821, 2811, 2801, 2791, 2781, 2771, 2761, 2751, 2741, 2731, 2721, 2711, 2702, 2692, 2682, 2672, 2663, 2653, 2644, 2634
, 2625, 2615, 2606, 2596, 2587, 2578, 2568, 2559, 2550, 2541, 2532, 2522, 2513, 2504, 2495, 2486, 2477, 2468, 2459, 2451, 
2442, 2433, 2424, 2415, 2407, 2398, 2389, 2381, 2372, 2364, 2355, 2347, 2338, 2330, 2321, 2313, 2305, 2296, 2288, 2280, 2272
, 2263, 2255, 2247, 2239, 2231, 2223, 2215, 2207, 2199, 2191, 2183, 2175, 2167, 2160, 2152, 2144, 2136, 2129, 2121, 2113, 
2106, 2098, 2091, 2083, 2076, 2068, 2061, 2053, 2046, 2038, 2031, 2024, 2016, 2009, 2002, 1995, 1988, 1980, 1973, 1966, 1959
, 1952, 1945, 1938, 1931, 1924, 1917, 1910, 1903, 1896, 1890, 1883, 1876, 1869, 1862, 1856, 1849, 1842, 1836, 1829, 1823, 
1816, 1809, 1803, 1796, 1790, 1783, 1777, 1771, 1764, 1758, 1752, 1745, 1739, 1733, 1726, 1720, 1714, 1708, 1702, 1696, 1689
, 1683, 1677, 1671, 1665, 1659, 1653, 1647, 1641, 1635, 1629, 1624, 1618, 1612, 1606, 1600, 1595, 1589, 1583, 1577, 1572, 
1566, 1560, 1555, 1549, 1544, 1538, 1532, 1527, 1521, 1516, 1510, 1505, 1500, 1494, 1489, 1483, 1478, 1473, 1467, 1462, 1457
, 1452, 1446, 1441, 1436, 1431, 1426, 1421, 1415, 1410, 1405, 1400, 1395, 1390, 1385, 1380, 1375, 1370, 1365, 1360, 1355, 
1351, 1346, 1341, 1336, 1331, 1326, 1322, 1317, 1312, 1307, 1303, 1298, 1293, 1289, 1284, 1279, 1275, 1270, 1266, 1261, 1256
, 1252, 1247, 1243, 1238, 1234, 1229, 1225, 1221, 1216, 1212, 1207, 1203, 1199, 1194, 1190, 1186, 1182, 1177, 1173, 1169, 
1165, 1160, 1156, 1152, 1148, 1144, 1140, 1136, 1131, 1127, 1123, 1119, 1115, 1111, 1107, 1103, 1099, 1095, 1091, 1087, 1083
, 1080, 1076, 1072, 1068, 1064, 1060, 1056, 1053, 1049, 1045, 1041, 1038, 1034, 1030, 1026, 1023, 1019, 1015, 1012, 1008, 
1004, 1001, 997, 994, 990, 986, 983, 979, 976, 972, 969, 965, 962, 958, 955, 951, 948, 945, 941, 938, 934, 931, 928, 924, 
921, 918, 914, 911, 908, 904, 901, 898, 895, 891, 888, 885, 882, 879, 876, 872, 869, 866, 863, 860, 857, 854, 851, 848, 844,
 841, 838, 835, 832, 829, 826, 823, 820, 817, 814, 812, 809, 806, 803, 800, 797, 794, 791, 788, 786, 783, 780, 777, 774, 772
, 769, 766, 763, 760, 758, 755, 752, 750, 747, 744, 741, 739, 736, 733, 731, 728, 726, 723, 720, 718, 715, 713, 710, 707, 
705, 702, 700, 697, 695, 692, 690, 687, 685, 682, 680, 677, 675, 673, 670, 668, 665, 663, 661, 658, 656, 653, 651, 649, 646,
 644, 642, 639, 637, 635, 633, 630, 628, 626, 623, 621, 619, 617, 614, 612, 610, 608, 606, 603, 601, 599, 597, 595, 593, 591
, 588, 586, 584, 582, 580, 578, 576, 574, 572, 570, 568, 565, 563, 561, 559, 557, 555, 553, 551, 549, 547, 545, 543, 541, 
540, 538, 536, 534, 532, 530, 528, 526, 524, 522, 520, 519, 517, 515, 513, 511, 509, 507, 506, 504, 502, 500, 498, 497, 495,
 493, 491, 489, 488, 486, 484, 482, 481, 479, 477, 475, 474, 472, 470, 469, 467, 465, 464, 462, 460, 459, 457, 455, 454, 452
, 450, 449, 447, 445, 444, 442, 441, 439, 438, 436, 434, 433, 431, 430, 428, 427, 425, 424, 422, 420, 419, 417, 416, 414, 
413, 411, 410, 408, 407, 406, 404, 403, 401, 400, 398, 397, 395, 394, 393, 391, 390, 388, 387, 386, 384, 383, 381, 380, 379,
 377, 376, 375, 373, 372, 370, 369, 368, 366, 365, 364, 363, 361, 360, 359, 357, 356, 355, 353, 352, 351, 350, 348, 347, 346
, 345, 343, 342, 341, 340, 338, 337, 336, 335, 334, 332, 331, 330, 329, 328, 326, 325, 324, 323, 322, 321, 319, 318, 317, 
316, 315, 314, 313, 311, 310, 309, 308, 307, 306, 305, 304, 303, 301, 300, 299, 298, 297, 296, 295, 294, 293, 292, 291, 290,
 289, 288, 287, 286, 285, 284, 282, 281, 280, 279, 278, 277, 276, 275, 274, 273, 272, 271, 270, 270, 269, 268, 267, 266, 265
, 264, 263, 262, 261, 260, 259, 258, 257, 256, 255, 254, 253, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 244, 243, 
242, 241, 240, 239, 238, 237, 237, 236, 235, 234, 233, 232, 232, 231, 230, 229, 228, 227, 227, 226, 225, 224, 223, 222, 222,
 221, 220, 219, 219, 218, 217, 216, 215, 215, 214, 213, 212, 212, 211, 210, 209, 208, 208, 207, 206, 205, 205, 204, 203, 203
, 202, 201, 200, 200, 199, 198, 197, 197, 196, 195, 195, 194, 193, 193, 192, 191, 190, 190, 189, 188, 188, 187, 186, 186, 
185, 184, 184, 183, 182, 182, 181, 180, 180, 179, 178, 178, 177, 176, 176, 175, 175, 174, 173, 173, 172, 171, 171, 170, 170,
 169, 168, 168, 167, 167, 166, 165, 165, 164, 164, 163, 162, 162, 161, 161, 160, 159, 159, 158, 158, 157, 157, 156, 155, 155
, 154, 154, 153, 153, 152, 152, 151, 150, 150, 149, 149, 148, 148, 147, 147, 146, 146, 145, 145, 144, 144, 143, 143, 142, 
142, 141, 140, 140, 139, 139, 138, 138, 137, 137, 136, 136, 135, 135, 135, 134, 134, 133, 133, 132, 132, 131, 131, 130, 130,
 129, 129, 128, 128, 127, 127, 126, 126, 126, 125, 125, 124, 124, 123, 123, 122, 122, 122, 121, 121, 120, 120, 119, 119, 118
, 118, 118, 117, 117, 116, 116, 116, 115, 115, 114, 114, 113, 113, 113, 112, 112, 111, 111, 111, 110, 110, 109, 109, 109, 
108, 108, 107, 107, 107, 106, 106, 106, 105, 105, 104, 104, 104, 103, 103, 102, 102, 102, 101, 101, 101, 100, 100, 100, 99, 
99, 98, 98, 98, 97, 97, 97, 96, 96, 96, 95, 95, 95, 94, 94, 94, 93, 93, 93, 92, 92, 92, 91, 91, 91, 90, 90, 90
};
void BeeperInstrument::playNote(unsigned char note, unsigned char velocity) {
	_currentNote = note;
	_speaker->setTimer(_timingTable[( (_currentNote + 12) << 4) + (_currentBend >> 8)]);
	_speaker->connect();
}
void BeeperInstrument::stopNote(unsigned char note) {
	if(note == _currentNote) {
		_speaker->disconnect();
	}
}
void BeeperInstrument::pitchBend(signed int offset) {
	_currentBend = offset;
	_speaker->setTimer(_timingTable[( (_currentNote + 12) << 4) + (_currentBend >> 8)]);
}
void BeeperInstrument::pressureChangeNote(unsigned char note, unsigned char pressure) {
	return;
}
void BeeperInstrument::silence() {
	_speaker->disconnect();
}
void BeeperInstrument::update(int ticks) {
	_tremoloStep = _tremoloStep + ticks & 3;
	_speaker->setTimer(_timingTable[( (_currentNote + 12) << 4) + (_currentBend >> 8) + _tremoloStep - 1]);
}

BeeperInstrument::BeeperInstrument() {
	_speaker = new Speaker();
	_currentNote = _currentBend = _tremoloStep = 0;
}
BeeperInstrument::~BeeperInstrument() {
	delete _speaker;
}