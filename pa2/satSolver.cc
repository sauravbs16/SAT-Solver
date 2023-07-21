#include <memory>
#include "satSolver.h"
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Dimacs.h"
#include "minisat/core/Solver.h"


bool satCallingMiniSat(unsigned int numVar, std::vector<std::vector<int>> &cnf) {
  // your code starts here
  std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
  
  Minisat::vec<Minisat::Lit> literal;
  Minisat::vec<Minisat::Lit> clause;

  Minisat::Lit l1, l2, l3, l4;

  for(int i=0;i<numVar;i++)
  {
    l1 = Minisat::mkLit(solver->newVar());
    literal.push(l1);
  }
  for(int j=0;j<cnf.size();j++)
  {
    for(int k=0;k<cnf[j].size();k++)
    {
      l1 = literal[abs(cnf[j][k])-1];
      if(cnf[j][k]<0)
      {
        clause.push(~l1);
      }
      else{
        clause.push(l1);
      }
    }
    solver->addClause(clause);
    clause.clear();
  }
  bool res = solver->solve();
  solver.reset(new Minisat::Solver());
  return res;
}
