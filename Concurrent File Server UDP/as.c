
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct qwe
{
    char a[100];
} arr[100];
struct wer
{
    int len;
    int ind;
} leng[100];
void main()
{
    FILE *fint, *optab, *flen, *fsym, *fout;
    int op1[10], txtlen, txtlen1, i, j = 0, len;
    char abc[10] = {'0', '0', '0', '0'}, add[5], adress_symtab[5], opcode_optab[5], start[10], temp[30], line[20], label[20], opcode_ip[10], operand_ip[10], symbol_symtab[10], mnemonic_optab[10];
    fint = fopen("input.txt", "r");
    flen = fopen("length.txt", "r");
    optab = fopen("optab.txt", "r");
    fsym = fopen("symbol.txt", "r");
    fout = fopen("output.txt", "w");
    leng[0].ind = 0;
    leng[0].len = 0;
    fscanf(fint, "%s%s%s%s", add, label, opcode_ip, operand_ip);
    if (strcmp(opcode_ip, "START") == 0)
    {
        strcpy(start, operand_ip);
        fscanf(flen, "%d", &len);
    }
    fprintf(fout, "H^%s^%s^%d", label, start, len);
    fscanf(fint, "%s%s%s%s", add, label, opcode_ip, operand_ip);
    int co = 0, leng_counter = 1, arr_counter = 0;
    while (strcmp(opcode_ip, "END") != 0)
    {
        fscanf(optab, "%s%s", mnemonic_optab, opcode_optab);
        while (!feof(optab)) // search optab for opcode
        {
            if (strcmp(opcode_ip, mnemonic_optab) == 0)
            {
                while (!feof(fsym)) // search symtab for operand
                {
                    fscanf(fsym, "%s%s", adress_symtab, symbol_symtab);
                    if (strcmp(operand_ip, symbol_symtab) == 0)
                    {
                        strcpy(arr[arr_counter].a, opcode_optab);
                        strcat(arr[arr_counter++].a, adress_symtab);
                        co += strlen(opcode_optab);
                        co += strlen(adress_symtab);
                        if (co >= 60) // max size of txt record is 60
                        {
                            leng[leng_counter].ind = arr_counter - 1;
                            leng[leng_counter++].len = co - strlen(opcode_optab) - strlen(adress_symtab);
                            co = strlen(opcode_optab) + strlen(adress_symtab);
                        }
                        break;
                    }
                }
                fseek(fsym, SEEK_SET, 0);
                break;
            }
            else
            {
                fscanf(optab, "%s%s", mnemonic_optab, opcode_optab);
            }
        }
        fseek(optab, SEEK_SET, 0);
        if ((strcmp(opcode_ip, "BYTE") == 0) || (strcmp(opcode_ip, "WORD") == 0))
        {
            if (strcmp(opcode_ip, "WORD") == 0)
            {
                // strcpy(abc, "00000");
                char zerocount[6 - strlen(operand_ip)];
                for (int i = 0; i < 6 - strlen(operand_ip); i++)
                {
                    zerocount[i] = '0';
                }
                strcpy(arr[arr_counter++].a, strcat(zerocount, operand_ip));
                co += 6;
                if (co >= 60)
                {
                    leng[leng_counter].ind = arr_counter - 1;
                    leng[leng_counter++].len = co - 6;
                    co = 6;
                }
                // fprintf(fout, "00000%s^", operand);
            }
            else
            {
                len = strlen(operand_ip);
                int ascii_operand[100], ascii_counter = 0;
                char str[100];
                for (i = 2; i < len - 1; i++)
                {
                    ascii_operand[ascii_counter++] = (int)operand_ip[i];
                }
                int index = 0;
                for (i = 0; i < ascii_counter; i++)
                    index += sprintf(&str[index], "%d", ascii_operand[i]);
                strcpy(arr[arr_counter++].a, str);
                co += strlen(str);
                if (co >= 60)
                {
                    leng[leng_counter].ind = arr_counter - 1;
                    leng[leng_counter++].len = co - strlen(str);
                    co = strlen(str);
                }
            }
        }
        fscanf(fint, "%s%s%s%s", add, label, opcode_ip, operand_ip);
    }
    if (co < 60)
    {
        leng[leng_counter].ind = arr_counter;
        leng[leng_counter++].len = co;
    }
    fprintf(fout, "\n");
    int a = strtol(start, NULL, 16);
    for (int i = 0; i < leng_counter - 1; i++)
    {
        a = a + leng[i].len / 2;
        fprintf(fout, "T^%02X^", a);
        fprintf(fout, "%X^", leng[i + 1].len / 2);
        for (int j = leng[i].ind; j < leng[i + 1].ind; j++)
        {
            fprintf(fout, "%s^", arr[j].a);
        }
        fprintf(fout, "\n");
    }
    fprintf(fout, "E^00%s", start);
    fclose(fint);
    fclose(optab);
    fclose(fsym);
    fclose(flen);
    fclose(fout);
}
/*
Input:

-	CODE	START	1000
1000	-	LDA	ALPHA
1003	-	ADD	INCR
1006	-	SUB	ONE
1009	-	STA	BETA
100C	ALPHA	WORD	1
100F	INCR	RESW	1
1012	ONE	WORD	1
1015	BETA	RESW	1
-	-	END	-

SYMTAB:

100C    ALPHA
100F    INCR
1012    ONE
1015    BETA
*/
