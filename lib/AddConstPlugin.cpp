#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>

#include "CalculateAlign.hpp"

static inline void registerModuleAnalyses(llvm::ModuleAnalysisManager &MAM) {
  MAM.registerPass([] {
    return CalculateAlign::CalculateAlignAnalysis();
  });
}

static void inline addPassToMPM(llvm::ModulePassManager &MPM) {
  MPM.addPass(CalculateAlign::CalculateAlignAnalysisPass());
}

static inline bool registerModulePipeline(llvm::StringRef Name, llvm::ModulePassManager &MPM, llvm::ArrayRef<llvm::PassBuilder::PipelineElement>) {
  if (Name == "calculate-align") {
    addPassToMPM(MPM);
    return true;
  }
  return false;
}

static inline bool earlySimplificationCallback(llvm::ModulePassManager &MPM, llvm::OptimizationLevel level) {
  static_cast<void>(level);
  addPassToMPM(MPM);
  return true;
}

static inline llvm::PassPluginLibraryInfo getAddConstPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "CalculateAlign", LLVM_VERSION_STRING, [](llvm::PassBuilder &PB) {
            PB.registerPipelineEarlySimplificationEPCallback(earlySimplificationCallback);
            PB.registerAnalysisRegistrationCallback(registerModuleAnalyses);
            PB.registerPipelineParsingCallback(registerModulePipeline);
          }};
}

extern "C" LLVM_ATTRIBUTE_WEAK llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return getAddConstPluginInfo();
}