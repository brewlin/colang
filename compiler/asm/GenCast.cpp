/**
 *@ClassName AsmGenReg
 *@Author brewlin
 *@Date 2021/7/6 0016 上午 9:01
 *@Version 1.0
 **/

#include "AsmGen.h"
#include "../internal/Internal.h"

#include <unordered_map>
using namespace std;

enum BaseType{ I8, I16, I32, I64, U8, U16, U32, U64};

unordered_map<Token,int> types = {
	{KW_I8,I8}, {KW_I16,I16}, {KW_I32,I32}, {KW_I64,I64},
  {KW_U8,U8}, {KW_U16,U16}, {KW_U32,U32}, {KW_U64,U64}
};


// The table for type casts
static char i32i8[] = "movsbl %al, %eax";
static char i32u8[] = "movzbl %al, %eax";
static char i32i16[] = "movswl %ax, %eax";
static char i32u16[] = "movzwl %ax, %eax";
static char i32i64[] = "movsxd %eax, %rax";
static char u32i64[] = "mov %eax, %eax";

static char *cast_table[][8] = {
  // i8   i16     i32     i64     u8     u16     u32     u64    
  {NULL,  NULL,   NULL,   i32i64, i32u8, i32u16, NULL,   i32i64 }, // i8
  {i32i8, NULL,   NULL,   i32i64, i32u8, i32u16, NULL,   i32i64 }, // i16
  {i32i8, i32i16, NULL,   i32i64, i32u8, i32u16, NULL,   i32i64 }, // i32
  {i32i8, i32i16, NULL,   NULL,   i32u8, i32u16, NULL,   NULL,  }, // i64

  {i32i8, NULL,   NULL,   i32i64, NULL,  NULL,   NULL,   i32i64 }, // u8
  {i32i8, i32i16, NULL,   i32i64, i32u8, NULL,   NULL,   i32i64 }, // u16
  {i32i8, i32i16, NULL,   u32i64, i32u8, i32u16, NULL,   u32i64 }, // u32
  {i32i8, i32i16, NULL,   NULL,   i32u8, i32u16, NULL,   NULL   }, // u64
};

void AsmGen::Cast(Token from ,Token to) {
  int f = types[from];
  int t = types[to];
  if (cast_table[f][t]){
    writeln("  %s", cast_table[f][t]);
  }
}
