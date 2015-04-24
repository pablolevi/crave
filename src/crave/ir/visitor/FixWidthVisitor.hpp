#pragma once

#include "../Node.hpp"
#include "NodeVisitor.hpp"

#include <boost/intrusive_ptr.hpp>

#include <stack>
#include <utility>

namespace crave {

class FixWidthVisitor : NodeVisitor {

  typedef boost::intrusive_ptr<Node> result_type;
  typedef std::pair<result_type, int> stack_entry;

 public:
  FixWidthVisitor() : NodeVisitor(), exprStack_() {}

 private:
  virtual void visitNode(Node const&);
  virtual void visitTerminal(Terminal const&);
  virtual void visitUnaryExpr(UnaryExpression const&);
  virtual void visitUnaryOpr(UnaryOperator const&);
  virtual void visitBinaryExpr(BinaryExpression const&);
  virtual void visitBinaryOpr(BinaryOperator const&);
  virtual void visitTernaryExpr(TernaryExpression const&);
  virtual void visitPlaceholder(Placeholder const&);
  virtual void visitVariableExpr(VariableExpr const&);
  virtual void visitConstant(Constant const&);
  virtual void visitVectorExpr(VectorExpr const&);
  virtual void visitNotOpr(NotOpr const&);
  virtual void visitNegOpr(NegOpr const&);
  virtual void visitComplementOpr(ComplementOpr const&);
  virtual void visitInside(Inside const&);
  virtual void visitExtendExpr(ExtendExpression const&);
  virtual void visitAndOpr(AndOpr const&);
  virtual void visitOrOpr(OrOpr const&);
  virtual void visitLogicalAndOpr(LogicalAndOpr const&);
  virtual void visitLogicalOrOpr(LogicalOrOpr const&);
  virtual void visitXorOpr(XorOpr const&);
  virtual void visitEqualOpr(EqualOpr const&);
  virtual void visitNotEqualOpr(NotEqualOpr const&);
  virtual void visitLessOpr(LessOpr const&);
  virtual void visitLessEqualOpr(LessEqualOpr const&);
  virtual void visitGreaterOpr(GreaterOpr const&);
  virtual void visitGreaterEqualOpr(GreaterEqualOpr const&);
  virtual void visitPlusOpr(PlusOpr const&);
  virtual void visitMinusOpr(MinusOpr const&);
  virtual void visitMultipliesOpr(MultipliesOpr const&);
  virtual void visitDevideOpr(DevideOpr const&);
  virtual void visitModuloOpr(ModuloOpr const&);
  virtual void visitShiftLeftOpr(ShiftLeftOpr const&);
  virtual void visitShiftRightOpr(ShiftRightOpr const&);
  virtual void visitVectorAccess(VectorAccess const&);
  virtual void visitIfThenElse(IfThenElse const&);
  virtual void visitForEach(ForEach const&);
  virtual void visitUnique(Unique const&);
  virtual void visitBitslice(Bitslice const&);
  void pop(stack_entry&);
  void pop2(stack_entry&, stack_entry&);
  void pop3(stack_entry&, stack_entry&, stack_entry&);
  void evalBinExpr(BinaryExpression const&, stack_entry&, stack_entry&, bool);
  void evalTernExpr(TernaryExpression const&, stack_entry&, stack_entry&,
                    stack_entry&);

 public:
  result_type fixWidth(Node const& expr) {

    expr.visit(*this);
    stack_entry entry;
    pop(entry);

    return entry.first;
  }

 private:
  std::stack<stack_entry> exprStack_;
};

inline void FixWidthVisitor::pop(stack_entry& fst) {
  assert(exprStack_.size() >= 1);
  fst = exprStack_.top();
  exprStack_.pop();
}
inline void FixWidthVisitor::pop2(stack_entry& fst, stack_entry& snd) {
  assert(exprStack_.size() >= 2);
  fst = exprStack_.top();
  exprStack_.pop();
  snd = exprStack_.top();
  exprStack_.pop();
}
inline void FixWidthVisitor::pop3(stack_entry& fst, stack_entry& snd,
                                  stack_entry& trd) {
  assert(exprStack_.size() >= 3);
  fst = exprStack_.top();
  exprStack_.pop();
  snd = exprStack_.top();
  exprStack_.pop();
  trd = exprStack_.top();
  exprStack_.pop();
}
inline void FixWidthVisitor::evalBinExpr(BinaryExpression const& bin,
                                         stack_entry& fst, stack_entry& snd,
                                         bool fixWidth = true) {
  visitBinaryExpr(bin);
  pop2(snd, fst);
  if (!fixWidth) return;
  if (fst.second < snd.second) {
    unsigned int diff = snd.second - fst.second;
    fst.first = result_type(new ExtendExpression(fst.first.get(), diff));
    fst.second = snd.second;
  } else if (fst.second > snd.second) {
    unsigned int diff = fst.second - snd.second;
    snd.first = result_type(new ExtendExpression(snd.first.get(), diff));
    snd.second = fst.second;
  }
}
inline void FixWidthVisitor::evalTernExpr(TernaryExpression const& tern,
                                          stack_entry& fst, stack_entry& snd,
                                          stack_entry& trd) {
  visitTernaryExpr(tern);
  pop3(trd, snd, fst);
}

}  // end namespace crave
