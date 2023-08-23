#pragma once
#include <llvm/IR/PassManager.h>

using namespace llvm;

class AntiFunctionDecompile : public PassInfoMixin<AntiFunctionDecompile>
{
public: 
    PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM);
private:
    bool Run(Function &F);
    bool InsertAsmIntoPrologue(Function &F);
    bool InsertAsmIntoBlock(Function &F);
};
