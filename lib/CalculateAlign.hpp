#include <cstdint>
#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/PassManager.h>
#include <llvm/Support/raw_ostream.h>
#include <vector>

namespace CalculateAlign {
class CalculateAlignAnalysis : public llvm::AnalysisInfoMixin<CalculateAlignAnalysis> {

public:
  struct MemberAlignment final {
    uint32_t size;
    uint32_t alignment;
  };
  using Result = std::vector<MemberAlignment>;

  Result run(llvm::Module &module, llvm::ModuleAnalysisManager &mam);
  static llvm::AnalysisKey Key;
};

class CalculateAlignAnalysisPass : public llvm::PassInfoMixin<CalculateAlignAnalysisPass> {
public:
  llvm::PreservedAnalyses run(llvm::Module &module, llvm::ModuleAnalysisManager &mam);
};

} // namespace CalculateAlign