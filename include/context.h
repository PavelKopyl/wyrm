/// \file
/// \brief Keep global data structures.
/// Provide symbols for all IR entities.
#ifndef CONTEXT_H
#define CONTEXT_H

#include "compatibility.h"
#include <unordered_map>
#include <unordered_set>

namespace wyrm {

class Module;
class Function;
struct SymReg;
using InternedStrings = std::unordered_set<std::string>;
using NameTableT = std::unordered_map<const void *, string_view>;
struct ModuleST {
  std::unordered_map<string_view, Function *> Functions;
  std::unordered_map<string_view, SymReg *> GlobalVariables;
};
using ModuleSymbolsT = std::unordered_map<Module *, ModuleST>;
using FunctionSymbolsT =
    std::unordered_map<Function *, std::unordered_set<string_view>>;

class WyrmContext {
public:
  const NameTableT &Names{NameTable};
  WyrmContext(const WyrmContext &) = delete;
  WyrmContext &operator=(WyrmContext) = delete;
  WyrmContext() {}
  friend class MIRBuilder;
  friend class Module;
  friend string_view internedName(std::string &&);

private:
  InternedStrings StringStorage{};
  NameTableT NameTable{};
  ModuleSymbolsT ModuleSymbols{};
  FunctionSymbolsT FunctionSymbols{};
};

inline WyrmContext GlobalContext{};
string_view internedName(std::string &&name);

} // namespace wyrm

#endif // CONTEXT_H
