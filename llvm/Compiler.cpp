/**
 *@ClassName Compiler
 *@Author brewlin
 *@Date 2020/9/10 0010 下午 3:33
 *@Version 1.0
 **/
#include "Compiler.h"
#include "Runtime.h"
#include "Parser.h"
#include "Value.h"



Compiler::Compiler(const std::string &filename)
{
	rt = new Runtime("main");
	p = new Parser(filename,rt);
    //初始化类型转换表 用于指示那些可以进行类型转换
    addCast(getVarType(rt,"int"),   getVarType(rt,"float"), llvm::CastInst::SIToFP);
    addCast(getVarType(rt,"int"),   getVarType(rt,"double"), llvm::CastInst::SIToFP);
    addCast(getVarType(rt,"bool"),  getVarType(rt,"double"), llvm::CastInst::SIToFP);
    addCast(getVarType(rt,"float"), getVarType(rt,"double"), llvm::CastInst::FPExt);
    addCast(getVarType(rt,"float"), getVarType(rt,"int"), llvm::CastInst::FPToSI);
    addCast(getVarType(rt,"double"),getVarType(rt,"int"), llvm::CastInst::FPToSI);
//    addCast(intTy, intTy, llvm::CastInst::SExt);
}
Compiler::~Compiler()
{
    delete  p;
    delete rt;
}
void Compiler::printIR()
{
    //这里表示IR 中间代码表示已经生成完毕
    llvm::legacy::PassManager passManager;
    passManager.add(createPrintModulePass(llvm::outs()));
    passManager.run(*(rt->llvmModule.get()));
}
/**
 * 程序启动api
 */
void Compiler::execute()
{
    //词法解析 语法解析
    this->p->parse();

    this->ctx.push_back(new Context);

    //注册struct类型
    registerStruct();

    //遍历函数表 将所有的 函数注册到里面去
    registerFunc();


    //判断有没有main函数 有就不用解析下面的了
    if(!this->rt->getFunc("main"))
        registerDefaultMain();
    return;
}


void Compiler::bin(const string& filename){
    // Initialize the target registry etc.
    llvm::InitializeAllTargetInfos();
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmParsers();
    llvm::InitializeAllAsmPrinters();

    auto targetTriple = llvm::sys::getDefaultTargetTriple();
    rt->llvmModule->setTargetTriple(targetTriple);

    std::string error;
    auto Target = llvm::TargetRegistry::lookupTarget(targetTriple, error);

    if( !Target ){
        llvm::errs() << error;
        return;
    }

    auto CPU = "generic";
    auto features = "";

    llvm::TargetOptions opt;
    auto RM = llvm::Optional<llvm::Reloc::Model>();
    auto theTargetMachine = Target->createTargetMachine(targetTriple, CPU, features, opt, RM);

    rt->llvmModule->setDataLayout(theTargetMachine->createDataLayout());
    rt->llvmModule->setTargetTriple(targetTriple);

    std::error_code EC;
    llvm::raw_fd_ostream dest(filename.c_str(), EC, llvm::sys::fs::F_None);
//    raw_fd_ostream dest(filename.c_str(), EC, sys::fs::F_None);
//    formatted_raw_ostream formattedRawOstream(dest);

    llvm::legacy::PassManager pass;
    auto fileType = llvm::TargetMachine::CGFT_ObjectFile;
//    auto fileType = llvm::TargetMachine::CGFT_AssemblyFile;

    if( theTargetMachine->addPassesToEmitFile(pass, dest,fileType) ){
        llvm::errs() << "theTargetMachine can't emit a file of this type";
        return;
    }

    pass.run(*rt->llvmModule.get());
    dest.flush();

    llvm::outs() << "Object code wrote to " << filename.c_str() << "\n";
    llvm::outs() << "start to ld " << filename.c_str() << " -o main \n";


    system("clang++ main.o -o main");
    return;
}