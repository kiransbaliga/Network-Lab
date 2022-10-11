/*
Experiment No : 6
Aim           : Absolute loader
Name          : Aravind Jose
Class         : S5R
Roll No       : 10
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void main()
{
    FILE *fp;
    int i, addr1, l, j, staddr1;
    char name[10], name2[10], len[10], line[1000], name1[10], addr[10], rec[10], ch, staddr[10];
    fp = fopen("code.txt", "r");
    fscanf(fp, "%s", line);
    int count = 0, a = 0, b = 0, c = 0;
    for (i = 0; line[i] != '\0'; i++)
    {
        if (line[i] == '^')
        {
            count++;
            continue;
        }
        if (count == 1)
        {
            name1[a] = line[i];
            a++;
        }
        else if (count == 2)
        {
            name2[b] = line[i];
            b++;
        }
        else if (count == 3)
        {
            len[c] = line[i];
            c++;
        }
    }

    name1[a] = '\0';
    name2[b] = '\0';
    len[c] = '\0';
    printf("%s\t", name1);
    printf("Starting Add : %s\t", name2);
    printf("Length : %s\n\n", len);
    do
    {
        fscanf(fp, "%s", line);
        if (line[0] == 'T')
        {
            count = 0;
            a = 0;
            for (i = 0; line[i] != '\0'; i++)
            {
                if (line[i] == '^')
                {
                    count++;
                    continue;

                }
                else if (count == 1)
                {
                    staddr[a] = line[i];
                    a++;
                }
                else if (count == 3)
                {
                    break;
                }
            }
            staddr[a] = '\0';
            staddr1 = strtol(staddr, NULL, 16);

            while (line[i] != '\0')
            {
                if (line[i] != '^')
                {
                    int aa, bb;
                    aa = line[i];
                    bb = line[i + 1];
                    aa -= 48;
                    bb -= 48;
                    if (aa > 10)
                    {
                        aa -= 7;
                    }
                    if (bb > 10)
                    {
                        bb -= 7;
                    }
                    int cc = aa * 16 + bb;

                    printf("00%X \t %c%c\n",staddr1, line[i], line[i + 1]);
                    staddr1++;
                    i = i + 2;
                }
                else
                    i++;
            }
        }
        else if (line[0] = 'E')
        {
            break;
        }
    } while (!feof(fp));
}
/*
OUTPUT
------

INPUT.TXT
---------
H^COPY^001000^00107A
T^001000^1E^141033^482039^001036^281030^301015^482061^3C1003^00102A^0C1039^00102D
T^00101E^15^0C1036^482061^081033^4C0000^454F46^000003^000000
T^001047^1E^041030^001030^E0205D^30203F^D8205D^281030^302057^549039^2C205E^38203F
T^001077^1C^101036^4C0000^000000^001000^041030^E02079^302064^509039^DC2079^2C1036
E^001000


COPY    Starting Add : 001000   Length : 00107A

001000   14
001001   10
001002   33
001003   48
001004   20
001005   39
001006   00
001007   10
001008   36
001009   28
00100A   10
00100B   30
00100C   30
00100D   10
00100E   15
00100F   48
001010   20
001011   61
001012   3C
001013   10
001014   03
001015   00
001016   10
001017   2A
001018   0C
001019   10
00101A   39
00101B   00
00101C   10
00101D   2D
00101E   0C
00101F   10
001020   36
001021   48
001022   20
001023   61
001024   08
001025   10
001026   33
001027   4C
001028   00
001029   00
00102A   45
00102B   4F
00102C   46
00102D   00
00102E   00
00102F   03
001030   00
001031   00
001032   00
001047   04
001048   10
001049   30
00104A   00
00104B   10
00104C   30
00104D   E0
00104E   20
00104F   5D
001050   30
001051   20
001052   3F
001053   D8
001054   20
001055   5D
001056   28
001057   10
001058   30
001059   30
00105A   20
00105B   57
00105C   54
00105D   90
00105E   39
00105F   2C
001060   20
001061   5E
001062   38
001063   20
001064   3F
001077   10
001078   10
001079   36
00107A   4C
00107B   00
00107C   00
00107D   00
00107E   00
00107F   00
001080   00
001081   10
001082   00
001083   04
001084   10
001085   30
001086   E0
001087   20
001088   79
001089   30
00108A   20
00108B   64
00108C   50
00108D   90
00108E   39
00108F   DC
001090   20
001091   79
001092   2C
001093   10
001094   36

*/
