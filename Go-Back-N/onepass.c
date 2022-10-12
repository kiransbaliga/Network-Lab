/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
  FILE *f1, *f2, *f3, *f4, *f5, *f6;
  int lc, sa, i = 0, j = 0, m[10], pgmlen, len, k, len1, l = 0;
  char name[10], opnd[10], la[10], mne[10], s1[10], mne1[10], opnd1[10];
  char lcs[10], ms[10];
  char sym[10], symaddr[10], obj1[10], obj2[10], s2[10], q[10], s3[10];
  char s;

  f1 = fopen("input.txt", "r");
  f2 = fopen("optab.txt", "r");
  f3 = fopen("symtab.txt", "w+");
  f4 = fopen("symtab1.txt", "w+");
  f5 = fopen("output.txt", "w+");
  f6 = fopen("result.txt", "w+");
  fscanf(f1, "%s%s%s", la, mne, opnd);
  if (strcmp(mne, "START") == 0)
  {
    sa = atoi(opnd);
    strcpy(name, la);
    
    
    
    lc = sa;
  }
  strcpy(s1, "*");
  fscanf(f1, "%s%s%s", la, mne, opnd);
  while (strcmp(mne, "END") != 0)
  {
    if (strcmp(la, "-") == 0)
    {
      fscanf(f2, "%s%s", mne1, opnd1);
      while (!feof(f2))
      {
        if (strcmp(mne1, mne) == 0)
        {
          m[i] = lc + 1;
          fprintf(f3, "%s\t%s\n", opnd, s1);
          fprintf(f5, "%s\t0000\n", opnd1);
          lc = lc + 3;
          i = i + 1;
          break;
        }
        else
          fscanf(f2, "%s%s", mne1, opnd1);
      }
    }
    else
    {
      fseek(f3, SEEK_SET, 0);
      fscanf(f3, "%s%s", sym, symaddr);
      while (!feof(f3))
      {
        if (strcmp(sym, la) == 0)
        {

          fprintf(f4, "%s\t%06X\n", la, lc + 3096);

          fprintf(f5, "%06x\t%x\n", m[j++] + 3096, lc + 3096);
          i = i + 1;
          break;
        }
        else
          fscanf(f3, "%s%s", sym, symaddr);
      }
      if (strcmp(mne, "RESW") == 0)
        lc = lc + 3 * atoi(opnd);
      else if (strcmp(mne, "BYTE") == 0)
      {
        strcpy(s2, "-");
        len = strlen(opnd);
        lc = lc + len - 2;
        for (k = 2; k < len; k++)
        {
          q[l] = opnd[k];
          l = l + 1;
        }
        fprintf(f5, "%s\t%s\n", q, s2);
        break;
      }
      else if (strcmp(mne, "RESB") == 0)
        lc = lc + atoi(opnd);
      else if (strcmp(mne, "WORD") == 0)
      {
        strcpy(s3, "#");
        lc = lc + 3;
        fprintf(f5, "%s\t%s\n", opnd, s3);
        break;
      }
    }
    fseek(f2, SEEK_SET, 0);
    fscanf(f1, "%s%s%s", la, mne, opnd);
  }
  fseek(f5, SEEK_SET, 0);
  pgmlen = lc - sa;
  fprintf(f6, "H^%s^%06d^%06X\n", name, sa, pgmlen);
  fprintf(f6, "T^");
  fprintf(f6, "00%d^0%x", sa, pgmlen);
  fscanf(f5, "%s%s", obj1, obj2);
  while (!feof(f5))
  {
    if (strcmp(obj2, "0000") == 0)
      fprintf(f6, "^%s%s", obj1, obj2);
    else if (strcmp(obj2, "-") == 0)
    {
      fprintf(f6, "^");
      len1 = strlen(obj1);
      for (k = 0; k < len1; k++)
        fprintf(f6, "%d", obj1[k]);
    }
    else if (strcmp(obj2, "#") == 0)
    {
      fprintf(f6, "^");
      fprintf(f6, "%s", obj1);
    }
    fscanf(f5, "%s%s", obj1, obj2);
  }
  fseek(f5, SEEK_SET, 0);
  fscanf(f5, "%s%s", obj1, obj2);
  while (!feof(f5))
  {
    if (strcmp(obj2, "0000") != 0)
    {
      if (strcmp(obj2, "-") != 0)
      {
        if (strcmp(obj2, "#") != 0)
        {
          fprintf(f6, "\n");
          fprintf(f6, "T^%s^02^%s", obj1, obj2);
        }
      }
    }
    fscanf(f5, "%s%s", obj1, obj2);
  }
  fprintf(f6, "\nE^00%d", sa);

  fclose(f1);
  fclose(f2);
  fclose(f3);
  fclose(f4);
  fclose(f5);
  fclose(f6);

  FILE *symt;
  printf("\nsymtab..txt\n");
  printf("--------------\n");
  symt = fopen("symtab1.txt", "r");
  s = fgetc(symt);
  while (s != EOF)
  {
    printf("%c", s);
    s = fgetc(symt);
  }
  printf("\n");
  fclose(symt);

  FILE *res;
  printf("result.txt\n");
  printf("-----------\n");
  res = fopen("result.txt", "r");
  s = fgetc(res);
  while (s != EOF)
  {
    printf("%c", s);
    s = fgetc(res);
  }
  printf("\n\n");
  fclose(res);
}*/

ithokke thettalle........
ingane okke copy adikka


Ayinu nee ethada ******* ?

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void main()
{
    char opcode[10], operand[10], label[10], mnemonic[10], code[10];
    int locctr, start, length;

    FILE *input, *optab, *symbol, *output;

    input = fopen("input.txt", "r");
    optab = fopen("optab.txt", "r");
    symbol = fopen("symbol.txt", "w");
    output = fopen("output.txt", "w");

    fscanf(input, "%s\t%s\t%s", label, opcode, operand);

    if (strcmp(opcode, "START") == 0)
    {
        start = strtol(operand, NULL, 16);
        locctr = start;
        fprintf(output, "\t%s\t%s\t%s\n", label, opcode, operand);
    }
    else
    {
        locctr = 0;
    }
    fscanf(input, "%s\t%s\t%s", label, opcode, operand);
    while (strcmp(opcode, "END") != 0)
    {
        fprintf(output, "%X\t", locctr);
        if (strcmp(label, "-") != 0)
        {
            fprintf(symbol, "%s\t%X\n", label, locctr);
            if (strcmp(opcode, "WORD") == 0)
            {
                locctr += 3;
            }
            else if (strcmp(opcode, "RESW") == 0)
            {
                locctr += (3 * (atoi(operand)));
            }
            else if (strcmp(opcode, "RESB") == 0)
            {
                locctr += atoi(operand);
            }
            else if (strcmp(opcode, "BYTE") == 0)
            {
                locctr += strlen(operand) - 2;
            }
        }
        else
        {
            fscanf(optab, "%s\t%s", code, mnemonic);
            fseek(optab, SEEK_SET, 0);
            while (strcmp(code, "END") != 0)
            {
                if (strcmp(opcode, code) == 0)
                {
                    locctr += 3;
                    break;
			//podaaaaa naari
                }
                fscanf(optab, "%s\t%s", code, mnemonic);
            }
        }
        fprintf(output, "%s\t%s\t%s\t\n", label, opcode, operand);
        fscanf(input, "%s\t%s\t%s", label, opcode, operand);
    }
    fprintf(output, "\t%s\t%s\t%s\n", label, opcode, operand);
    length = locctr - start;
    printf("The length of code: %x\n", length);
    fclose(input);
    fclose(optab);
    fclose(symbol);
    fclose(output);
}
/*
INPUT.TXT

CODE	START	1000
-	LDA	ALPHA
-	ADD	INCR
-	SUB	ONE
-	STA	BETA
ALPHA	WORD	1
INCR	RESW	1
ONE	WORD	1
BETA	RESW	1
-	END	-

OPTAB.TXT
START	-
LDA	00
ADD	18
SUB	1C
STA	0C
END	-

OUTPUT.TXT

	CODE	START	1000
1000	-	LDA	ALPHA
1003	-	ADD	INCR
1006	-	SUB	ONE
1009	-	STA	BETA
100C	ALPHA	WORD	1
100F	INCR	RESW	1
1012	ONE	WORD	1
1015	BETA	RESW	1
	-	END	-

SYMTAB.TXT

ALPHA	100C
INCR	100F
ONE	1012
BETA	1015


*/

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
