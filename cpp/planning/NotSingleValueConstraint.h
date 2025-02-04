/*
 * NotSingleValueConstraint.h
 * @brief NotSingleValueConstraint constraint
 * @date Mar 20, 2022
 * @author Yoonwoo Kim
 */

#pragma once

#include <gtsam/discrete/DiscreteFactor.h>
#include <gtsam/discrete/DiscreteValues.h>
#include <gtsam/discrete/DiscreteKey.h>

#include <boost/assign.hpp>
#include <boost/format.hpp>

using namespace gtsam;
namespace gtsam_planner {

/**
 * NotSingleValue constraint: ensures a variable does not take on a certain value.
 */
class NotSingleValueConstraint : public DiscreteFactor {
  size_t cardinality_;  /// < Number of values
  size_t value_;        ///<  allowed value

  DiscreteKey discreteKey() const {
    return DiscreteKey(keys_[0], cardinality_);
  }

 public:

  /// Construct from key, cardinality, and given value.
  NotSingleValueConstraint(Key key, size_t n, size_t value)
      : DiscreteFactor(boost::assign::cref_list_of<1>(key)),
        cardinality_(n), value_(value) {}

  /// Construct from DiscreteKey and given value.
  NotSingleValueConstraint(const DiscreteKey& dkey, size_t value)
      : DiscreteFactor(boost::assign::cref_list_of<1>(dkey.first)),
        cardinality_(dkey.second), value_(value) {}

  // print
  void print(const std::string& s = "", const KeyFormatter& formatter =
                                            DefaultKeyFormatter) const override;

  /// equals
  bool equals(const DiscreteFactor& other, double tol) const override {
    if (!dynamic_cast<const NotSingleValueConstraint*>(&other))
      return false;
    else {
      const NotSingleValueConstraint& f(static_cast<const NotSingleValueConstraint&>(other));
      return (cardinality_ == f.cardinality_) && (value_ == f.value_);
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
