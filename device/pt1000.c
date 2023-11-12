#include "pt1000.h"
#include "log.h"

#define ARRAY_SZ(x)     (sizeof(x)/sizeof(x[0]))


const static U32 pt1000[1692] = {
    803063,
    803460,803857,804254,804651,805048,805445,805842,806239,806604,807033,
    807430,807827,808224,808621,809018,809415,809812,810209,810606,811003,
    811400,811796,812193,812590,812987,813383,813780,814177,814573,814970,
    815367,815763,816160,816557,816954,817350,817747,818144,818540,818937,
    819334,819730,820127,820523,820920,821316,821713,822109,822506,822902,
    823298,823695,824091,824487,824884,825280,825676,826072,826469,826865,
    827261,827658,828054,828450,828847,829243,829639,830035,830432,830828,
    831224,831620,832016,832412,832809,833205,833601,833997,834393,834789,
    835185,835581,835977,836373,836769,837164,837560,837956,838352,838748,
    839144,839540,839936,840332,840728,841123,841519,841915,842311,842707,
    843103,843498,843894,844290,844686,845081,845477,845873,846268,846664,
    847060,847455,847851,848246,848642,849037,849433,849828,850224,850619,
    851015,851410,851806,852201,852597,852992,853388,853783,854179,854573,
    854968,855364,855759,856154,856550,856945,857340,857735,858131,858526,
    858921,859316,859712,860107,860502,860897,861292,861688,862082,862478,
    862873,863268,863663,864058,864453,864848,865243,865638,866033,866428,
    866823,867218,867613,868008,868403,868797,869192,869587,869982,870377,
    870772,871166,871561,871956,872351,872746,873141,873535,873930,874325,
    874720,875114,875509,875904,876299,876693,877088,877483,877877,878272,
    878667,879061,879456,879850,880245,880639,881034,881428,881823,882217,
    882611,883006,883400,883795,884189,884583,884978,885372,885766,886161,
    886555,886949,887344,887738,888132,888526,888920,889315,889709,890103,
    890497,890891,891285,891679,892074,892468,892862,893256,893650,894044,
    894438,894832,895226,895620,896015,896409,896803,897197,897591,897985,
    898379,898773,899166,899560,899954,900348,900742,901135,901529,901923,
    902317,902711,903104,903498,903892,904286,904680,905073,905467,905861,
    906255,906648,907042,907436,907830,908223,908617,909011,909404,909798,
    910192,910585,910979,911372,911766,912159,912553,912946,913340,913733,
    914126,914520,914913,915306,915700,916093,916486,916879,917273,917666,
    918059,918453,918846,919239,919633,920026,920419,920812,921206,921599,
    921992,922385,922779,923172,923565,923958,924351,924745,925138,925531,
    925924,926317,926710,927103,927496,927888,928281,928674,929067,929460,
    929853,930246,930639,931032,931425,931818,932211,932604,932997,933390,
    933783,934175,934568,934961,935354,935746,936139,936532,936924,937317,
    937710,938102,938495,938888,939281,939673,940066,940459,940851,941244,
    941637,942029,942422,942814,943207,943600,943992,944385,944777,945170,
    945562,945955,946347,946740,947132,947524,947917,948309,948702,949094,
    949486,949878,950271,950663,951055,951447,951839,952232,952624,953016,
    953408,953800,954193,954585,954977,955369,955761,956154,956546,956938,
    957330,957722,958114,958506,958899,959291,959683,960075,960467,960859,
    961251,961643,962035,962427,962819,963211,963603,963995,964387,964779,
    965171,965563,965954,966346,966738,967130,967522,967913,968305,968697,
    969089,969480,969872,970264,970656,971047,971439,971831,972222,972614,
    973006,973397,973789,974180,974572,974963,975355,975746,976138,976529,
    976921,977313,977704,978096,978487,978879,979270,979662,980053,980444,
    980835,981227,981618,982010,982401,982793,983184,983575,983967,984358,
    984749,985140,985532,985923,986314,986705,987096,987488,987879,988270,
    988661,989052,989443,989834,990226,990617,991008,991399,991790,992181,
    992572,992963,993354,993745,994136,994527,994918,995309,995700,996091,
    
    1000000,1000391,1000782,1001172,1001563,1001954,1002345,1002736,1003126,1003517,    //0
    1003908,1004298,1004689,1005080,1005470,1005861,1006252,1006642,1007033,1007424,
    1007814,1008205,1008595,1008986,1009377,1009767,1010158,1010548,1010939,1011329,
    1011720,1012110,1012501,1012891,1013282,1013672,1014062,1014453,1014843,1015234,
    1015624,1016014,1016405,1016795,1017185,1017576,1017966,1018356,1018747,1019137,
    1019527,1019917,1020308,1020698,1021088,1021478,1021868,1022259,1022649,1023039,
    1023429,1023819,1024209,1024599,1024989,1025380,1025770,1026160,1026550,1026940,
    1027330,1027720,1028110,1028500,1028890,1029280,1029670,1030060,1030450,1030840,
    1031229,1031619,1032009,1032399,1032789,1033179,1033569,1033958,1034348,1034738,
    1035128,1035518,1035907,1036297,1036687,1037077,1037466,1037856,1038246,1038636,
    1039025,1039415,1039805,1040194,1040584,1040973,1041363,1041753,1042142,1042532,
    1042921,1043311,1043701,1044090,1044480,1044869,1045259,1045648,1046038,1046427,
    1046816,1047206,1047595,1047985,1048374,1048764,1049153,1049542,1049932,1050321,
    1050710,1051099,1051489,1051878,1052268,1052657,1053046,1053435,1053825,1054214,
    1054603,1054992,1055381,1055771,1056160,1056549,1056938,1057327,1057716,1058105,
    1058495,1058884,1059273,1059662,1060051,1060440,1060829,1061218,1061607,1061996,
    1062385,1062774,1063163,1063552,1063941,1064330,1064719,1065108,1065496,1065885,
    1066274,1066663,1067052,1067441,1067830,1068218,1068607,1068996,1069385,1069774,
    1070162,1070551,1070940,1071328,1071717,1072106,1072495,1072883,1073272,1073661,
    1074049,1074438,1074826,1075215,1075604,1075992,1076381,1076769,1077158,1077546,
    1077935,1078324,1078712,1079101,1079489,1079877,1080266,1080654,1081043,1081431,
    1081820,1082208,1082596,1082985,1083373,1083762,1084150,1084538,1084926,1085315,
    1085703,1086091,1086480,1086868,1087256,1087644,1088033,1088421,1088809,1089197,
    1089585,1089974,1090362,1090750,1091138,1091526,1091914,1092302,1092690,1093078,
    1093467,1093855,1094243,1094631,1095019,1095407,1095795,1096183,1096571,1096959,
    1097347,1097734,1098122,1098510,1098898,1099286,1099674,1100062,1100450,1100838,
    1101225,1101613,1102001,1102389,1102777,1103164,1103552,1103940,1104328,1104715,
    1105103,1105491,1105879,1106266,1106654,1107042,1107429,1107817,1108204,1108592,
    1108980,1109367,1109755,1110142,1110530,1110917,1111305,1111693,1112080,1112468,
    1112855,1113242,1113630,1114017,1114405,1114792,1115180,1115567,1115954,1116342,
    1116729,1117117,1117504,1117891,1118279,1118666,1119053,1119441,1119828,1120215,
    1120602,1120990,1121377,1121764,1122151,1122538,1122926,1123313,1123700,1124087,
    1124474,1124861,1125248,1125636,1126023,1126410,1126797,1127184,1127571,1127958,
    1128345,1128732,1129119,1130127,1129893,1130280,1130667,1131054,1131441,1131828,
    1132215,1132602,1132988,1133375,1133762,1134149,1134536,1134923,1135309,1135696,
    1136083,1136470,1136857,1137243,1137630,1138017,1138404,1138790,1139177,1139564,
    1139950,1140337,1140724,1141110,1141497,1141884,1142270,1142657,1143043,1143430,
    1143817,1144203,1144590,1144976,1145363,1145749,1146136,1146522,1146909,1147295,
    1147681,1148068,1148454,1148841,1149227,1149614,1150000,1150386,1150773,1151159,
    1151545,1151932,1152318,1152704,1153091,1153477,1153863,1154249,1154636,1155022,
    1155408,1155794,1156180,1156567,1156953,1157339,1157725,1158111,1158497,1158883,
    1159270,1159656,1160042,1160428,1160814,1161200,1161586,1161972,1162358,1162744,
    1163130,1163516,1163902,1164288,1164674,1165060,1165446,1165831,1166217,1166603,
    1166989,1167375,1167761,1168147,1168532,1168918,1169304,1169690,1170076,1170461,
    1170847,1171233,1171619,1172004,1172390,1172776,1173161,1173547,1173933,1174318,
    1174704,1175090,1175475,1175861,1176247,1176632,1177018,1177403,1177789,1178174,
    1178560,1178945,1179331,1179716,1180102,1180487,1180873,1181258,1181644,1182029,
    1182414,1182800,1183185,1183571,1183956,1184341,1184727,1185112,1185597,1185883,
    1186268,1186653,1187038,1187424,1187809,1188194,1188579,1188965,1189350,1189735,
    1190120,1190505,1190890,1191276,1191661,1192046,1192431,1192816,1193201,1193586,
    1193971,1194356,1194741,1195126,1195511,1195896,1196281,1196666,1197051,1197436,
    1197821,1198206,1198591,1198976,1199361,1199746,1200131,1200516,1200900,1201285,
    1201670,1202055,1202440,1202824,1203209,1203594,1203979,1204364,1204748,1205133,
    1205518,1205902,1206287,1206672,1207056,1207441,1207826,1208210,1208595,1208980,
    1209364,1209749,1210133,1210518,1210902,1211287,1211672,1212056,1212441,1212825,
    1213210,1213594,1213978,1214363,1214747,1215120,1215516,1215901,1216285,1216669,
    1217054,1217438,1217822,1218207,1218591,1218975,1219360,1219744,1220128,1220513,
    1220897,1221281,1221665,1222049,1222434,1222818,1223202,1223586,1223970,1224355,
    1224739,1225123,1225507,1225891,1226275,1226659,1227043,1227427,1227811,1228195,
    1228579,1228963,1229347,1229731,1230115,1230499,1230883,1231267,1231651,1232035,
    1232419,1232803,1233187,1233571,1233955,1234338,1234722,1235106,1235490,1235874,
    1236257,1236641,1237025,1237409,1237792,1238176,1238560,1238944,1239327,1239711,
    1240095,1240478,1240862,1241246,1241629,1242030,1242396,1242780,1243164,1243547,
    1243931,1244314,1244698,1245081,1245465,1245848,1246232,1246615,1246999,1247382,
    1247766,1248149,1248533,1248916,1249299,1249683,1250066,1250450,1250833,1251216,
    1251600,1251983,1252366,1252749,1253133,1253516,1253899,1254283,1254666,1255049,
    1255432,1255815,1256199,1256582,1256965,1257348,1257731,1258114,1258497,1258881,
    1259264,1259647,1260030,1260413,1260796,1261179,1261562,1261945,1262328,1262711,
    1263094,1263477,1263860,1264243,1264626,1265009,1265392,1265775,1266157,1266540,
    1266923,1267306,1267689,1268072,1268455,1268837,1269220,1269603,1269986,1270368,
    1270751,1271134,1271517,1271899,1272282,1272665,1273048,1273430,1273813,1274195,
    1274578,1274691,1274803,1274916,1275029,1275141,1275254,1275366,1275479,1275591,
    1278404,1278786,1279169,1279551,1279934,1280316,1280699,1281081,1281464,1281846,
    1282228,1282611,1282993,1283376,1283758,1284140,1284523,1284905,1285287,1285670,
    1286052,1286434,1286816,1287199,1287581,1287963,1288345,1288728,1289110,1289492,
    1289874,1290256,1290638,1291021,1291403,1291785,1292167,1292549,1292931,1293313,
    1293695,1294077,1294459,1294841,1295223,1295605,1295987,1296369,1296751,1297133,
    1297515,1297897,1298279,1298661,1299043,1299425,1299807,1300188,1300570,1300952,
    1301334,1301716,1302098,1302479,1302861,1303243,1303625,1304006,1304388,1304770,
    1305152,1305533,1305915,1306297,1306678,1307060,1307442,1307823,1308205,1308586,
    1308968,1309350,1309731,1310113,1310494,1310876,1311270,1311639,1312020,1312402,
    1312783,1313165,1313546,1313928,1314309,1314691,1315072,1315453,1315835,1316216,
    1316597,1316979,1317360,1317742,1318123,1318504,1318885,1319267,1319648,1320029,
    1320411,1320792,1321173,1321554,1321935,1322316,1322697,1323079,1323460,1323841,
    1324222,1324603,1324985,1325366,1325747,1326128,1326509,1326890,1327271,1327652,
    1328033,1328414,1328795,1329176,1329557,1329938,1330319,1330700,1331081,1331462,
    1331843,1332224,1332604,1332985,1333366,1333747,1334128,1334509,1334889,1335270,
    1335651,1336032,1336413,1336793,1337174,1337555,1337935,1338316,1338697,1339078,
    1339458,1335839,1332220,1328600,1324981,1321361,1317742,1314123,1310503,1306884,
    1343264,1343645,1344025,1344406,1344786,1345167,1345570,1345928,1346308,1346689,
    1347069,1347450,1347830,1348211,1348591,1348971,1349352,1349732,1350112,1350493,
    1350873,1351253,1351634,1352014,1352394,1352774,1353155,1353535,1353915,1354295,
    1354676,1355056,1355436,1355816,1356196,1356577,1356957,1357337,1357717,1358097,
    1358477,1358857,1359237,1359617,1359997,1360377,1360757,1361137,1361517,1361897,
    1362277,1362657,1363037,1363417,1363797,1364177,1364557,1364937,1365317,1365697,
    1366077,1366456,1366836,1367216,1367596,1367976,1368355,1368735,1369115,1369495,
    1369875,1370254,1370634,1371014,1371393,1371773,1372153,1372532,1372912,1373292,
    1373671,1374051,1374431,1374810,1375190,1375569,1375949,1376329,1376708,1377088,
    1377467,1377847,1378226,1378606,1378985,1379365,1379744,1380123,1380503,1380882,
    1381262,1381641,1382020,1382400,1382779,1383158,1383538,1383917,1384296,1384676,        //99
    
    1385055,1388847,1392638,1396428,1400217,1404005,1407791,1411576,1415360,1419143,
    1422925,1426706,1430485,1434264,1438041,1441817,1445592,1449366,1453138,1456910,
    1460680,1464449,1468217,1471984,1475750,1479514,1483277,1487040,1490801,1494561,
    1498319,1502077,1505833,1509589,1513343,1517096,1520847,1524598,1528381,1532139,
    1535843,1539589,1543334,1547078,1550820,1554562,1558302,1562041,1565779,1569516,
    1573251,1576986,1580719,1584451,1588182,1591912,1595641,1599368,1603094,1606820,
    1610544,1614267,1617989,1621709,1625429,1629147,1632864,1636580,1640295,1644009,
    1647721,1651433,1655143,1658852,1662560,1666267,1669972,1673677,1677380,1681082,
    1684783,1688483,1692181,1695879,1699575,1703271,1706965,1710658,1714349,1718040,
    1721729,1725418,1729105,1732791,1736475,1740159,1743842,1747523,1751203,1754882,
    1758560,1762237,1765912,1769587,1773260,1776932,1780603,1784273,1787941,1791610,
    1795275,1798940,1802604,1806267,1809929,1813590,1817249,1820907,1824564,1828220,
    1831875,1835529,1839181,1842832,1846483,1850132,1853779,1857426,1861072,1864716,
    1868359,1872001,1875642,1879282,1882921,1886558,1890194,1893830,1897463,1901096,
    1904728,1908359,1911988,1915616,1919243,1922869,1926494,1930117,1933740,1937361,
    1940981,1944600,1948218,1951835,1955450,1959065,1962678,1966290,1969901,1973510,
    1977119,1980726,1984333,1987938,1991542,1995145,1998746,2002347,2005946,2009544,
    2013141,2016737,2020332,2023925,2027518,2031109,2034699,2038288,2041876,2045463,
    2049048,2052632,2056215,2059798,2063378,2066958,2070537,2074114,2077690,2081265,
    2084839,2088412,2091984,2095554,2099123,2102692,2106259,2109824,2113389,2116953,
    2120515,
};

//根据索引获取温度
static F32 get_temp(int idx)
{
    F32 t;
    //-50~99:    (50+99)*10+1     step: 0.1
    //100~300    20*10+1          step: 1.0
    
    if(idx<=1490) {
        t = -50+idx*0.1f;
    }
    else {
        t = 100+idx*1.0f;
    }
    
    return t;
}

//volt to resistance
static F32 v_to_r(F32 v)
{
     F32 r,x;
    
    /*
        分压电阻为6.8k，运放倍数为1.5M/200k=7.5，根据分压公式计算
        3.3*(r/(r+6800)-820/(820+6800))*7.5=v
    */
    x = v/(7.5f*3.3f) + (820*1.0f)/(820+6800);
    r = (x*6800)/(1-x);
    
    return r;
}

int pt1000_temp(F32 v, F32 *t)
{
    U32 *pt=(U32*)pt1000;
    U32 r=v_to_r(v)*1000;
    int l,h,x,idx,sz=ARRAY_SZ(pt1000);
    
    if(r<pt[0] || r>pt[sz-1]) {
        LOGE("___ wrong r\n");
        return -1;
    }
    
    LOGD("___ pt1000, v: %.3fmv, r: %d\n", v, r);
    l=0; h=sz-1;
    while(l<=h) {
        x = (l+h)/2;
        if(r>=pt[x]) {
            if(x>=h) {
                idx = h;
                break;
            }
            else {
                if(r<=pt[x+1]) {
                    idx = (r>(pt[x]+pt[x+1])/2)?(x+1):x;
                        break;
                }
                else {
                    l = x; 
                }
            }
        }
        else {
            if(x<=l) {
                idx = l;
                break;
            }
            else {
                if(r>=pt[x-1]) {
                    idx = (r>(pt[x]+pt[x-1])/2)?x:(x-1);
                    break;
                }
                else {
                    h = x;
                }
            }
        }
    }
    
    if(t) *t = get_temp(idx);
    
    return 0;
}


