/**
 *@ClassName CompilerStruct
 *@Author brewlin
 *@Date 2020/9/27 0027 下午 3:39
 *@Version 1.0
 **/
#include "Compiler.h"
#include "Log.h"

/**
 * 声明结构体
 */
void Compiler::registerStruct()
{
    Debug("start regist structs");
    for(auto v : rt->structs){
        Struct *s = v.second;
        Debug("regist struct name:%s\n",s->name.c_str());
        declarationStruct(rt,ctx,s);
    }
}
/**
 *
 * @param rt
 * @param ctx
 * @param s
 */
void Compiler::declarationStruct(Runtime *rt, std::deque<Context *> ctx, Struct *s)
{
    Debug("declaration struct:%s",s->name.c_str());
    //声明成员变量 类型都是 void*
    std::vector<llvm::Type*> memberTypes;

    //定义结构体
    auto structType = llvm::StructType::create(rt->llvmContext, s->name);
    rt->structTypes[s->name] = structType;
    for(int i = 0; i < s->members.size(); i ++){
        memberTypes.push_back(getVarType(rt,"int"));
    }
    //声明成员函数
    for(int i = 0; i < s->funcs.size(); i ++){
        Function* f = s->funcs[i];
        //创建函数指针
        memberTypes.push_back(getFuncPtr(rt,f));
        declarationFunc(rt,ctx,f);
    }
    //声明成员 类型为  函数指针
    structType->setBody(memberTypes);
}

/**
 * 获取结构体的成员变量
 * @param rt
 * @param ctx
 * @param varname
 * @param membername
 * @return
 */
 llvm::Value* Compiler::getStructMember(Runtime *rt, std::deque<Context *> ctx, std::string varname,
                                        std::string membername)
{
     Debug("get struct memeber var:%s member:%s",varname.c_str(),membername.c_str());
    llvm::Value* varPtr = getVar(ctx,varname);
    auto structPtr      = rt->builder.CreateLoad(varPtr, "structPtr");
    Debug("struct name:%s type:%s",varname.c_str(),Compiler::getTypeStr(structPtr).c_str());
    structPtr->setAlignment(4);

    if( !structPtr->getType()->isStructTy() ){
        Error("The variable is not struct");
    }

    std::string structName = structPtr->getType()->getStructName().str();
    Struct* s = rt->structs[structName];
    int index = 0;
    for (int i = 0; i < s->members.size(); ++i)
        if(s->members[i] == membername)
            index = i;

    Debug("struct member index:%d",index);
    std::vector<llvm::Value*> indices;
    indices.push_back(llvm::ConstantInt::get(getVarType(rt,"int"), 0, false));
    indices.push_back(llvm::ConstantInt::get(getVarType(rt,"int"), (uint64_t)index, false));
    auto ptr = rt->builder.CreateInBoundsGEP(varPtr, indices, "memberPtr");
    return ptr;
//    return rt->builder.CreateLoad(ptr);
}

/**
 * 初始化结构体 赋值成员函数
 * @param obj
 * @param name
 */
void Compiler::initStruct(Runtime* rt,llvm::Value *obj, Struct* s)
{
    //如果没有成员函数则不需要进行初始化
    if(s->funcs.size() == 0)
        return;
    auto varPtr = obj;
//    auto structPtr = context.builder.CreateLoad(varPtr, "structPtr");
//    auto underlyingStruct = context.builder.CreateLoad(load);
//    structPtr->setAlignment(4);
    auto structPtr = rt->builder.CreateLoad(varPtr, "structPtr");
    if( !structPtr->getType()->isStructTy() ){
        parse_err("The variable is not struct");
    }

    string structName = structPtr->getType()->getStructName().str();

    //获取成员函数对应的索引
    int msize = s->members.size();
    int fsize = s->funcs.size();


    for (int i = 0; i < fsize; ++i) {

        Function* fi = s->funcs[i];
        llvm::Function* f = rt->funcTypes[fi->name];
        std::vector<llvm::Value*> indices;
    //    auto index = ;
        indices.push_back(llvm::ConstantInt::get(getVarType(rt,"int"), 0, false));
        indices.push_back(llvm::ConstantInt::get(getVarType(rt,"int"), (uint64_t)(msize+i), false));

        auto ptr = rt->builder.CreateInBoundsGEP(varPtr, indices, "structMemberPtr");

        rt->builder.CreateStore(f, ptr);
    }

}