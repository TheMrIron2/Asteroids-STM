#include <stdio.h>

const uint16_t dg1[]= // dutch gold. to be removed
{
	0,0,16142,16142,16142,16142,16142,16142,16142,16142,0,0,0,0,0,16142,16142,16142,16142,16142,16142,0,0,0,0,0,16142,16142,16142,16142,16142,16142,16142,16142,0,0,0,0,16142,16142,16142,1994,1994,16142,16142,16142,0,0,0,0,16142,16142,16142,1994,16142,1994,16142,16142,0,0,0,0,16142,16142,16142,1994,16142,1994,16142,16142,0,0,0,0,16142,16142,16142,1994,16142,1994,16142,16142,0,0,0,0,16142,16142,16142,1994,1994,16142,16142,16142,0,0,0,0,16142,16142,16142,16142,16142,16142,16142,16142,0,0,0,0,16142,16142,16142,1994,1994,1994,16142,16142,0,0,0,0,16142,16142,16142,1994,16142,16142,16142,16142,0,0,0,0,16142,16142,16142,1994,16142,16142,16142,16142,0,0,0,0,16142,16142,16142,1994,16142,1994,16142,16142,0,0,0,0,16142,16142,16142,1994,1994,1994,16142,16142,0,0,0,0,0,16142,16142,16142,16142,16142,16142,0,0,0,0,0,0,16142,16142,16142,16142,16142,16142,0,0,0,
};

// Player sprites in 8 directions, manually rotated 45 degrees each.

const uint16_t player[]=
{
	0,0,0,0,0,0,0,36097,36097,0,0,0,0,0,0,0,0,0,0,0,0,0,0,60930,60930,0,0,0,0,0,0,0,0,0,0,0,0,0,0,53250,53250,0,0,0,0,0,0,0,0,0,0,0,0,0,52481,53763,53763,52481,0,0,0,0,0,0,0,0,0,0,0,0,61441,12355,12355,61441,0,0,0,0,0,0,0,0,0,0,0,52481,12802,3500,3500,12802,52481,0,0,0,0,0,0,0,0,0,0,52481,3946,3756,3756,3946,52481,0,0,0,0,0,0,0,0,0,0,61697,53090,3459,3459,53090,61697,0,0,0,0,0,0,0,0,0,44545,20738,60929,62724,62724,60929,20738,44545,0,0,0,0,0,0,0,11778,13316,21251,36354,54532,54532,36354,21251,13316,11778,0,0,0,0,0,36097,61954,62724,21251,36610,29443,29443,36610,21251,62724,61954,36097,0,0,0,0,52481,28929,62210,61441,36610,5380,5380,36610,61441,62210,28929,52481,0,0,0,0,0,44545,62722,12545,36610,21251,21251,36610,12545,62722,44545,0,0,0,0,0,0,35386,12354,61441,36610,21251,21251,36610,61441,12354,35386,0,0,0,0,0,0,35410,3963,35410,44082,45163,45163,44082,35410,3963,35410,0,0,0,0,0,0,0,0,0,0,35410,35410,0,0,0,0,0,0,0,
};

const uint16_t player_45[]=
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,36097,36097,0,0,0,0,0,0,0,0,0,0,0,0,0,20226,36354,36097,36097,0,0,0,0,0,0,0,0,0,0,61185,61186,36866,20226,36354,36097,0,0,0,0,0,0,0,0,52481,20481,61457,12835,37123,36866,20226,0,0,0,52481,36097,11778,20226,44545,45057,52818,28754,53123,12355,12835,61186,0,0,0,52481,52481,53250,53763,37891,45314,20522,36714,44708,28076,53123,61457,61185,0,0,0,0,12033,12546,62467,37635,37122,44802,29019,3467,44708,28754,20481,0,0,0,0,51770,28450,37890,4354,61698,3842,21508,5380,29019,36714,52818,52481,0,0,0,0,52579,4170,37138,12290,20482,45827,29700,21508,44802,20522,45057,0,0,0,0,0,3963,52835,20234,3842,62211,5380,45827,3842,37122,45314,44545,0,0,0,0,0,0,27458,44338,37411,21251,62211,20482,61698,37635,37891,20226,0,0,0,0,0,0,35410,52827,45411,37411,3842,12290,4354,62467,53763,11778,0,0,0,0,0,0,35410,35410,52827,44338,20234,37138,37890,12546,53250,36097,0,0,0,0,0,0,0,35410,35410,27458,52835,4170,28450,12033,52481,52481,0,0,0,0,0,0,0,0,0,0,3963,52579,51770,0,52481,0,0,0,0,0,0,
};

const uint16_t player_90[]= // horizontal
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,52481,36097,0,0,0,0,0,0,0,0,0,0,0,35410,35386,44545,28929,61954,11778,0,0,0,0,0,0,0,0,0,0,3963,12354,62722,62210,62724,13316,44545,0,0,0,0,0,0,0,0,0,35410,61441,12545,61441,21251,21251,20738,61697,52481,52481,0,0,0,0,0,0,44082,36610,36610,36610,36610,36354,60929,53090,3946,12802,61441,52481,0,0,0,35410,45163,21251,21251,5380,29443,54532,62724,3459,3756,3500,12355,53763,53250,60930,36097,35410,45163,21251,21251,5380,29443,54532,62724,3459,3756,3500,12355,53763,53250,60930,36097,0,44082,36610,36610,36610,36610,36354,60929,53090,3946,12802,61441,52481,0,0,0,0,35410,61441,12545,61441,21251,21251,20738,61697,52481,52481,0,0,0,0,0,0,3963,12354,62722,62210,62724,13316,44545,0,0,0,0,0,0,0,0,0,35410,35386,44545,28929,61954,11778,0,0,0,0,0,0,0,0,0,0,0,0,0,52481,36097,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

const uint16_t player_135[]=
{
	0,0,0,0,0,3963,52579,51770,0,52481,0,0,0,0,0,0,0,0,35410,35410,27458,52835,4170,28450,12033,52481,52481,0,0,0,0,0,0,35410,35410,52827,44338,20234,37138,37890,12546,53250,36097,0,0,0,0,0,0,35410,52827,45411,37411,3842,12290,4354,62467,53763,11778,0,0,0,0,0,0,27458,44338,37411,21251,62211,20482,61698,37635,37891,20226,0,0,0,0,0,3963,52835,20234,3842,62211,5380,45827,3842,37122,45314,44545,0,0,0,0,0,52579,4170,37138,12290,20482,45827,29700,21508,44802,20522,45057,0,0,0,0,0,51770,28450,37890,4354,61698,3842,21508,5380,29019,36714,52818,52481,0,0,0,0,0,12033,12546,62467,37635,37122,44802,29019,3467,44708,28754,20481,0,0,0,0,52481,52481,53250,53763,37891,45314,20522,36714,44708,28076,53123,61457,61185,0,0,0,0,52481,36097,11778,20226,44545,45057,52818,28754,53123,12355,12835,61186,0,0,0,0,0,0,0,0,0,0,52481,20481,61457,12835,37123,36866,20226,0,0,0,0,0,0,0,0,0,0,0,61185,61186,36866,20226,36354,36097,0,0,0,0,0,0,0,0,0,0,0,0,20226,36354,36097,36097,0,0,0,0,0,0,0,0,0,0,0,0,0,36097,36097,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

const uint16_t player_180[]=
{
	0,0,0,0,0,0,0,35410,35410,0,0,0,0,0,0,0,0,0,0,35410,3963,35410,44082,45163,45163,44082,35410,3963,35410,0,0,0,0,0,0,35386,12354,61441,36610,21251,21251,36610,61441,12354,35386,0,0,0,0,0,0,44545,62722,12545,36610,21251,21251,36610,12545,62722,44545,0,0,0,0,0,52481,28929,62210,61441,36610,5380,5380,36610,61441,62210,28929,52481,0,0,0,0,36097,61954,62724,21251,36610,29443,29443,36610,21251,62724,61954,36097,0,0,0,0,0,11778,13316,21251,36354,54532,54532,36354,21251,13316,11778,0,0,0,0,0,0,0,44545,20738,60929,62724,62724,60929,20738,44545,0,0,0,0,0,0,0,0,0,61697,53090,3459,3459,53090,61697,0,0,0,0,0,0,0,0,0,0,52481,3946,3756,3756,3946,52481,0,0,0,0,0,0,0,0,0,0,52481,12802,3500,3500,12802,52481,0,0,0,0,0,0,0,0,0,0,0,61441,12355,12355,61441,0,0,0,0,0,0,0,0,0,0,0,0,52481,53763,53763,52481,0,0,0,0,0,0,0,0,0,0,0,0,0,53250,53250,0,0,0,0,0,0,0,0,0,0,0,0,0,0,60930,60930,0,0,0,0,0,0,0,0,0,0,0,0,0,0,36097,36097,0,0,0,0,0,0,0,
};

const uint16_t player_225[]=
{
	0,0,0,0,0,0,52481,0,51770,52579,3963,0,0,0,0,0,0,0,0,0,0,52481,52481,12033,28450,4170,52835,27458,35410,35410,0,0,0,0,0,0,0,36097,53250,12546,37890,37138,20234,44338,52827,35410,35410,0,0,0,0,0,0,11778,53763,62467,4354,12290,3842,37411,45411,52827,35410,0,0,0,0,0,0,20226,37891,37635,61698,20482,62211,21251,37411,44338,27458,0,0,0,0,0,0,44545,45314,37122,3842,45827,5380,62211,3842,20234,52835,3963,0,0,0,0,0,45057,20522,44802,21508,29700,45827,20482,12290,37138,4170,52579,0,0,0,0,52481,52818,36714,29019,5380,21508,3842,61698,4354,37890,28450,51770,0,0,0,0,20481,28754,44708,3467,29019,44802,37122,37635,62467,12546,12033,0,0,0,0,61185,61457,53123,28076,44708,36714,20522,45314,37891,53763,53250,52481,52481,0,0,0,61186,12835,12355,53123,28754,52818,45057,44545,20226,11778,36097,52481,0,0,0,20226,36866,37123,12835,61457,20481,52481,0,0,0,0,0,0,0,0,36097,36354,20226,36866,61186,61185,0,0,0,0,0,0,0,0,0,0,36097,36097,36354,20226,0,0,0,0,0,0,0,0,0,0,0,0,0,36097,36097,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

const uint16_t player_270[]=
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,36097,52481,0,0,0,0,0,0,0,0,0,0,0,0,0,11778,61954,28929,44545,35386,35410,0,0,0,0,0,0,0,0,0,44545,13316,62724,62210,62722,12354,3963,0,0,0,0,0,0,52481,52481,61697,20738,21251,21251,61441,12545,61441,35410,0,0,0,0,52481,61441,12802,3946,53090,60929,36354,36610,36610,36610,36610,44082,0,36097,60930,53250,53763,12355,3500,3756,3459,62724,54532,29443,5380,21251,21251,45163,35410,36097,60930,53250,53763,12355,3500,3756,3459,62724,54532,29443,5380,21251,21251,45163,35410,0,0,0,52481,61441,12802,3946,53090,60929,36354,36610,36610,36610,36610,44082,0,0,0,0,0,0,52481,52481,61697,20738,21251,21251,61441,12545,61441,35410,0,0,0,0,0,0,0,0,0,44545,13316,62724,62210,62722,12354,3963,0,0,0,0,0,0,0,0,0,0,11778,61954,28929,44545,35386,35410,0,0,0,0,0,0,0,0,0,0,0,36097,52481,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

const uint16_t player_315[]=
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,36097,36097,0,0,0,0,0,0,0,0,0,0,0,0,0,36097,36097,36354,20226,0,0,0,0,0,0,0,0,0,0,0,0,36097,36354,20226,36866,61186,61185,0,0,0,0,0,0,0,0,0,0,0,20226,36866,37123,12835,61457,20481,52481,0,0,0,0,0,0,0,0,0,0,61186,12835,12355,53123,28754,52818,45057,44545,20226,11778,36097,52481,0,0,0,0,61185,61457,53123,28076,44708,36714,20522,45314,37891,53763,53250,52481,52481,0,0,0,0,20481,28754,44708,3467,29019,44802,37122,37635,62467,12546,12033,0,0,0,0,0,52481,52818,36714,29019,5380,21508,3842,61698,4354,37890,28450,51770,0,0,0,0,0,45057,20522,44802,21508,29700,45827,20482,12290,37138,4170,52579,0,0,0,0,0,44545,45314,37122,3842,45827,5380,62211,3842,20234,52835,3963,0,0,0,0,0,20226,37891,37635,61698,20482,62211,21251,37411,44338,27458,0,0,0,0,0,0,11778,53763,62467,4354,12290,3842,37411,45411,52827,35410,0,0,0,0,0,0,36097,53250,12546,37890,37138,20234,44338,52827,35410,35410,0,0,0,0,0,0,52481,52481,12033,28450,4170,52835,27458,35410,35410,0,0,0,0,0,0,0,0,52481,0,51770,52579,3963,0,0,0,0,0,
};

// Asteroid visuals

const uint16_t asteroid[]=
{
	0,0,0,1304,1304,9504,26144,50720,50720,9504,0,0,0,0,0,0,0,0,42528,18729,43305,43041,10281,52017,27698,2866,26401,50720,9496,1304,0,0,0,42528,51497,35890,11578,60730,35898,52538,52794,52538,19506,35633,18209,10017,59168,0,0,34336,27177,44346,44602,10545,18729,11834,10801,36410,35377,2353,52017,2089,10017,9496,0,58912,18985,19770,3642,60730,11834,36410,3642,11578,52282,10025,35377,3122,59433,9504,0,1825,11057,60986,27442,28482,2866,51241,43569,20026,44866,60474,52274,44090,59953,9504,0,34593,27698,35890,44866,53058,44346,10025,9769,2866,36930,36674,3642,2866,11314,17952,1304,2089,35898,35898,28226,59953,53314,45387,37195,37195,29003,19250,11322,52282,60209,17696,34336,43305,35898,44346,27706,10025,35377,45387,37195,20290,53579,18217,27706,3122,43305,1304,9504,27441,52538,52538,11578,10025,35377,37195,45387,44610,29003,19770,27962,19770,26921,1304,34336,35369,11314,19506,53058,44610,36930,36410,4163,20290,3642,44866,19770,11578,43305,17952,1304,50720,27441,35890,19770,3642,19770,44346,11322,59176,26665,11834,11578,11314,19249,17696,0,1304,18473,35890,44346,44602,53058,3906,19770,11578,36154,60730,2609,27698,2345,9504,0,0,59168,26665,51761,52273,43825,52017,60474,3122,44081,52017,43825,51497,1825,1304,0,0,0,50720,1825,26401,51233,59689,19249,27177,35113,27177,10537,26401,9504,0,0,0,0,0,0,1304,1304,1304,26144,59168,1825,1825,42528,17952,0,0,
};

const uint16_t explode[]=
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15619,15619,0,0,0,0,0,0,0,0,0,0,15619,23811,0,15619,56588,56579,0,0,15619,15619,0,0,0,0,0,0,64770,7701,15619,7427,15885,32012,15619,40204,15893,15619,0,0,0,0,0,0,15619,40477,40220,15619,57247,48701,15619,15893,48396,15619,0,0,0,0,0,0,7427,24414,40903,48758,65519,49007,65439,32639,56578,15619,0,0,0,0,0,15619,48387,64772,8111,49111,57327,40911,57319,7982,23811,15619,15619,0,0,15619,7427,65045,32622,32695,49111,49111,65535,65535,49119,40911,24463,40469,64780,15619,0,15619,15619,56578,23811,24102,32671,65535,65535,65535,57327,16287,15877,15619,7426,15619,0,0,0,15619,15619,49007,49135,57327,40911,57335,40895,49095,40831,48396,0,0,0,0,0,23811,56862,8079,16231,56902,32703,57335,48990,48388,56902,40478,23810,0,0,0,23810,15902,40194,7427,7427,48387,57118,8119,40453,15619,15619,64770,15619,15619,0,0,15619,48386,0,15619,15619,15619,48387,15902,56578,15619,0,0,0,0,0,0,0,0,0,0,0,0,15619,56588,15619,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15619,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};