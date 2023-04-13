#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>

#include "CalculateAlign.hpp"

void registerModuleAnalyses(llvm::ModuleAnalysisManager &MAM) {
  MAM.registerPass([] {
    return CalculateAlign::CalculateAlignAnalysis();
  });
}

bool registerModulePipeline(llvm::StringRef Name, llvm::ModulePassManager &MPM, llvm::ArrayRef<llvm::PassBuilder::PipelineElement>) {
  if (Name == "calculate-align") {
    MPM.addPass(CalculateAlign::CalculateAlignAnalysisPass());
    return true;
  }
  return false;
}

llvm::PassPluginLibraryInfo getAddConstPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "CalculateAlign", LLVM_VERSION_STRING, [](llvm::PassBuilder &PB) {
            PB.registerAnalysisRegistrationCallback(registerModuleAnalyses);
            PB.registerPipelineParsingCallback(registerModulePipeline);
          }};
}

extern "C" LLVM_ATTRIBUTE_WEAK llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return getAddConstPluginInfo();
}