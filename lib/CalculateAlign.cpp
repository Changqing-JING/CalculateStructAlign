#include "CalculateAlign.hpp"
#include <cassert>
#include <cstdint>
#include <iostream>
#include <llvm/IR/DataLayout.h>

namespace CalculateAlign {
llvm::AnalysisKey CalculateAlignAnalysis::Key;

CalculateAlignAnalysis::Result CalculateAlignAnalysis::run(llvm::Module &module, llvm::ModuleAnalysisManager &mam) {
  static_cast<void>(mam);
  CalculateAlignAnalysis::Result res;
  llvm::DataLayout const layout(&module);

  // module.dump();
  std::vector<llvm::StructType *> const structTypesList = module.getIdentifiedStructTypes();

  for (llvm::StructType const *const structType : structTypesList) {

    uint32_t const elementsCount = structType->getNumElements();
    for (uint32_t i = 0; i < elementsCount; i++) {
      llvm::Type *const elementType = structType->getStructElementType(i);
      elementType->dump();

      uint32_t const elementBitSize = elementType->getScalarSizeInBits();
      assert((elementBitSize % 8U) == 0);

      uint32_t const elementByteSize = elementBitSize / 8U;

      uint32_t const elementAlignment = layout.getABITypeAlignment(elementType);

      res.push_back({elementByteSize, elementAlignment});

      std::cout << "Element size " << elementByteSize << " align " << elementAlignment << std::endl;
    }
  }

  return res;
}

llvm::PreservedAnalyses CalculateAlignAnalysisPass::run(llvm::Module &module, llvm::ModuleAnalysisManager &mam) {
  CalculateAlignAnalysis::Result const res = mam.getResult<CalculateAlignAnalysis>(module);
  static_cast<void>(res);
  return llvm::PreservedAnalyses::all();
}

} // namespace CalculateAlign