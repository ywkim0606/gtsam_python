/*
 * FrameConstraint.h
 * @brief FrameConstraint constraint
 * @date Mar 20, 2022
 * @author Yoonwoo Kim
 */

#pragma once

#include <gtsam/discrete/DiscreteFactor.h>
#include <gtsam/discrete/DiscreteValues.h>
#include <gtsam/discrete/DiscreteKey.h>
#include <cpp/planning/NullConstraint.h>

#include <boost/assign.hpp>
#include <boost/format.hpp>

using namespace std;
using namespace gtsam;
namespace gtsam_planner {

/**
 * Operator constraint: true if out of one or more OperatorConstraint is true.
 */
class FrameConstraint : public DiscreteFactor {
  vector<NullConstraint> factors_;  /// < all possible operators
  DiscreteKeys dkeys_;
  DiscreteKey dkey_;
  size_t cardinality_;

  public:

  /// Construct from factors.
  FrameConstraint(const DiscreteKey& dkey, const DiscreteKeys& dkeys,
    const vector<NullConstraint>& factors);

  // print
  void print(const std::string& s = "", const KeyFormatter& formatter =
                                            DefaultKeyFormatter) const override;

  /// equals
  bool equals(const DiscreteFactor& other, double tol) const override {
    if (!dynamic_cast<const FrameConstraint*>(&other))
      return false;
    else {
      const FrameConstraint& f(dynamic_cast<const FrameConstraint&>(other));
      if (cardinality_ == f.cardinality_) {
        for (size_t i = 0; i < factors_.size(); i++) {
          if (factors_[i].equals(f.factors_[i], 1e-9) == false) return false;
        }
        return true;
      }
      return false;
    }
  }

  /// Return the key associated with which operator to use.
  size_t operatorKey() const;

  /// Calculate value
  double operator()(const DiscreteValues& values) const override;

  /// Convert into a decisiontree
  DecisionTreeFactor toDecisionTreeFactor() const override;

  /// Convert into a decisiontree
  TableFactor toTableFactor() const override;

  /// Multiply into a decisiontree
  DecisionTreeFactor operator*(const DecisionTreeFactor& f) const override;

  /// Multiply into a decisiontree
  TableFactor operator*(const TableFactor& f) const override;  

  /// Render as markdown table.
  std::string markdown(const KeyFormatter& keyFormatter = DefaultKeyFormatter,
                       const Names& names = {}) const override {
    return (boost::format("`Constraint` on %1% variables\n") % (size())).str();
  }

  /// Render as html table.
  std::string html(const KeyFormatter& keyFormatter = DefaultKeyFormatter,
                   const Names& names = {}) const override {
    return (boost::format("<p>Constraint on %1% variables</p>") % (size())).str();
  }

};

}  // namespace gtsam_planner
