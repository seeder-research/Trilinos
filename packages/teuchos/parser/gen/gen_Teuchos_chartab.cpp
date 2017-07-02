#include <cctype>
#include <climits>
#include <iostream>
#include <fstream>
#include <cassert>

int main() {
  int chartab[CHAR_MAX + 1];
  char inv_chartab[CHAR_MAX + 1];
  int n = 0;
  for (int i = 0; i <= CHAR_MAX; ++i) chartab[i] = -1;
  for (int i = 0; i <= CHAR_MAX; ++i) {
    switch (char(i)) {
      /* not using std::isspace, so we'll be dropping support for
         form feed and vertical tab. */
      case ' ':
      case '\t':
      case '\n':
      case '\r':
        chartab[i] = n;
        inv_chartab[n] = char(i);
        ++n;
    }
  }
  for (int i = 0; i <= CHAR_MAX; ++i) {
    if (std::islower(i)) {
      chartab[i] = n;
      inv_chartab[n] = char(i);
      ++n;
    }
  }
  for (int i = 0; i <= CHAR_MAX; ++i) {
    if (std::isupper(i)) {
      chartab[i] = n;
      inv_chartab[n] = char(i);
      ++n;
    }
  }
  for (int i = 0; i <= CHAR_MAX; ++i) {
    if (std::isdigit(i)) {
      chartab[i] = n;
      inv_chartab[n] = char(i);
      ++n;
    }
  }
  for (int i = 0; i <= CHAR_MAX; ++i) {
    if (std::ispunct(i)) {
      chartab[i] = n;
      inv_chartab[n] = char(i);
      ++n;
    }
  }
  std::ofstream chartab_hpp("Teuchos_chartab.hpp");
  chartab_hpp << "/* This file was auto-generated by\n";
  chartab_hpp << "   gen_Teuchos_chartab */\n";
  chartab_hpp << "\n";
  chartab_hpp << "#ifndef TEUCHOS_CHARTAB_HPP\n";
  chartab_hpp << "#define TEUCHOS_CHARTAB_HPP\n";
  chartab_hpp << "\n";
  chartab_hpp << "namespace Teuchos {\n";
  chartab_hpp << "\n";
  chartab_hpp << "enum { NCHARS = " << n << " };\n";
  chartab_hpp << "\n";
  chartab_hpp << "extern int const chartab[" << (CHAR_MAX + 1) << "];\n";
  chartab_hpp << "extern char const inv_chartab[NCHARS];\n";
  chartab_hpp << "\n";
  chartab_hpp << "}  // end namespace Teuchos\n";
  chartab_hpp << "\n";
  chartab_hpp << "#endif\n";
  chartab_hpp.close();
  std::ofstream chartab_cpp("Teuchos_chartab.cpp");
  chartab_cpp << "/* This file was auto-generated by\n";
  chartab_cpp << "   gen_Teuchos_chartab */\n";
  chartab_cpp << "\n";
  chartab_cpp << "#include \"Teuchos_chartab.hpp\"\n";
  chartab_cpp << "\n";
  chartab_cpp << "namespace Teuchos {\n";
  chartab_cpp << "\n";
  chartab_cpp << "int const chartab[" << (CHAR_MAX + 1) << "] = {\n";
  for (int i = 0; i <= CHAR_MAX; ++i) {
    chartab_cpp << "  " << chartab[i];
    if (i != CHAR_MAX) chartab_cpp << ',';
    chartab_cpp << '\n';
  }
  chartab_cpp << "};\n";
  chartab_cpp << "\n";
  chartab_cpp << "char const inv_chartab[NCHARS] = {\n";
  for (int i = 0; i < n; ++i) {
    chartab_cpp << "  \'";
    if (inv_chartab[i] == '\\') chartab_cpp << "\\\\";
    else if (inv_chartab[i] == '\'') chartab_cpp << "\\\'";
    else if (std::isprint(inv_chartab[i])) chartab_cpp << inv_chartab[i];
    else if (inv_chartab[i] == '\t') chartab_cpp << "\\t";
    else if (inv_chartab[i] == '\n') chartab_cpp << "\\n";
    else if (inv_chartab[i] == '\r') chartab_cpp << "\\r";
    else assert(false);
    chartab_cpp << '\'';
    if (i != n - 1) chartab_cpp << ',';
    chartab_cpp << '\n';
  }
  chartab_cpp << "};\n";
  chartab_cpp << "\n";
  chartab_cpp << "}  // end namespace Teuchos\n";
  chartab_cpp.close();
}
