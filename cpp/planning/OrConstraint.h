/*
 * OrConstraint.h
 * @brief OR constraint
 * @date Mar 20, 2022
 * @author Yoonwoo Kim
 */

#pragma once

#include <gtsam/discrete/DiscreteFactor.h>
#include <gtsam/discrete/DiscreteValues.h>
#include <gtsam/discrete/DiscreteKey.h>

#include <boost/assign.hpp>
#include <boost/format.hpp>

using namespace std;
using namespace gtsam;
namespace gtsam_planner {
/**
 * OR constraint: 
 */
class OrConstraint : public DiscreteFactor {
  
  vector<DecisionTreeFactor> dt_factors_;  /// < all possible operators
  vector<TableFactor> table_factors_; /// < all possible operators
  DiscreteKeys dkeys_;
  std::map<Key, size_t> cardinalities_;

 public:

  /// Construct from DecisionTreeFactors.
  OrConstraint(const vector<DecisionTreeFactor>& factors);

  /// Construct from TableFactors.
  OrConstraint(const vector<TableFactor>& factors);

  // print
  void print(const std::string& s = "", const KeyFormatter& formatter =
                                            DefaultKeyFormatter) const override;

  /// equals
  bool equals(const DiscreteFactor& other, double tol) const override {
    if (!dynamic_cast<const OrConstraint*>(&other))
      return false;
    else {
      const OrConstraint& f(static_cast<const OrConstraint&>(other));
      return cardinalities_.size() == f.cardinalities_.size() &&
              std::equal(cardinalities_.begin(), cardinalities_.end(),
                        f.cardinalities_.begin());
    }
  }

  /// Calculate value
  double operator()(const DiscreteValues& values) const override;

  /// Convert into a decisiontree
  DecisionTreeFactor toDecisionTreeFactor() const override;

  /// Convert into a TableFactor
  TableFactor toTableFactor() const override;

  /// Multiply into a decisiontree
  DecisionTreeFactor operator*(const DecisionTreeFactor& f) const override;

  /// Multiply into a TableFactor
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
