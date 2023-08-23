#include "AntiFunctionDecompile.hpp"
#include <llvm/Demangle/Demangle.h>
#include <llvm/IR/Constants.h>
#include <llvm/Transforms/Utils/BasicBlockUtils.h>
#include <llvm/IR/InlineAsm.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>


using namespace llvm;

PreservedAnalyses AntiFunctionDecompile::run(Function &F, FunctionAnalysisManager &FAM)
{
    // check if modified
    if (Run(F) == true)
    {
        PreservedAnalyses::none();
    }
    return PreservedAnalyses::all();
}

bool AntiFunctionDecompile::InsertAsmIntoBlock(Function &F)
{
    FunctionType *Ty = F.getFunctionType();

    for (BasicBlock &BB : F)
    {        
        outs() << "BasicBlock size : " << BB.size() << "\n";
        if (BB.size() <= 1)
        {
            return false;
        }
     
        // insert first non-PHI instruction in this block.
        BasicBlock::iterator IP = BB.getFirstInsertionPt();
        IRBuilder<> IRB(&(*IP));
        StringRef asmString = "b 0x4\n"
                              ".long 0xdeadbeef\n";

        InlineAsm *IA = InlineAsm::get(Ty, asmString, "", true, false, InlineAsm::AD_ATT);
        ArrayRef<Value *> Args = None;
        IRB.CreateCall(IA, Args);
    }
    return true;
}
bool AntiFunctionDecompile::InsertAsmIntoPrologue(Function &F)
{
    if (F.hasPrologueData())
    {
        return false;
    }
    
    IntegerType* int8Ty = Type::getInt8Ty(F.getContext());
    
    // only arm64
    /* 
    1E 00 00 10     ADR X30, 0x0
    DE 33 00 91     ADD X30, X30, 0xC
    C0 03 5F D6     RET
    */    

    StringRef obfusInst("\x1E\x00\x00\x10\xDE\x33\x00\x91\xC0\x03\x5F\xD6", 12);
    Constant* prologue = ConstantDataArray::getRaw(obfusInst, obfusInst.size(), int8Ty);
    F.setPrologueData(prologue);
    return true;
}

bool AntiFunctionDecompile::Run(Function &F)
{
    outs() << "Function Name : " << demangle(F.getName().str()) << '\n';
    // returns the number of non-debug IR instructions in this function.
    unsigned instCount = F.getInstructionCount();

    outs() << "inst count " << instCount << '\n'; 

    if (instCount == 0)
    {
        return false;
    }    
   
    bool success = false;
    success |= InsertAsmIntoPrologue(F); // Binary instructions can be inserted directly into the prologue.
    success |= InsertAsmIntoBlock(F);
    
    return success;
}
