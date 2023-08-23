#include <llvm/IR/PassManager.h>
#include <llvm/Passes/OptimizationLevel.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>

#include "AntiFunctionDecompile/AntiFunctionDecompile.hpp"

using namespace llvm;

extern "C" PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK llvmGetPassPluginInfo()
{   
    // Register LLVM passes
    return
    {
        LLVM_PLUGIN_API_VERSION, "CodetronikPass", "v1.0.0", [](PassBuilder &PB)
        {
            PB.registerPipelineStartEPCallback(
                [](ModulePassManager &MPM, OptimizationLevel level)
                {
                }
            );
            PB.registerScalarOptimizerLateEPCallback(
                [](FunctionPassManager &FPM, OptimizationLevel level)
                {
                    // todo : Need to change to cli option
                    FPM.addPass(AntiFunctionDecompile());
                }
            );
        }
    };
}
