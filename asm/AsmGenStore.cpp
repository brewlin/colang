/**
 *@ClassName AsmGenStore
 *@Author brewlin
 *@Date 2020/10/13 0013 下午 2:25
 *@Version 1.0
 **/

#include "AsmGen.h"


static const char *argreg8 [] = {"%dil", "%sil", "%dl", "%cl", "%r8b", "%r9b"};
static const char *argreg16[] = {"%di", "%si", "%dx", "%cx", "%r8w", "%r9w"};
static const char *argreg32[] = {"%edi", "%esi", "%edx", "%ecx", "%r8d", "%r9d"};
static const char *argreg64[] = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};

/**
 *
 * @param r
 * @param offset
 * @param sz
 */
void AsmGen::store_gp(int r, int offset, int sz)
{
    switch (sz) {
        case 1:
            writeln("  mov %s, %d(%%rbp)", argreg8[r], offset);
            return;
        case 2:
            writeln("  mov %s, %d(%%rbp)", argreg16[r], offset);
            return;
        case 4:
            writeln("  mov %s, %d(%%rbp)", argreg32[r], offset);
            return;
        case 8:
            writeln("  mov %s, %d(%%rbp)", argreg64[r], offset);
            return;
        default:
            for (int i = 0; i < sz; i++) {
                writeln("  mov %s, %d(%%rbp)", argreg8[r], offset + i);
                writeln("  shr $8, %s", argreg64[r]);
            }
            return;
    }

}
