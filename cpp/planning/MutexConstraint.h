/*
 * MutexConstraint.h
 * @brief Mutually exclusive constraint
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
 * Mutex constraint: Mutually exclusive constraint.
 * i.e (A, B, [1, 2]) variable A and B can take
 * 1 and 2 each but should not take them at the same time.
 */
class MutexConstraint : public DiscreteFactor {
  std::vector<size_t> values_;

  std::map<Key, size_t> cardinalities_;

  DiscreteKey discreteKey(size_t i) const {
    Key j = keys_[i];
    return DiscreteKey(j, cardinalities_.at(j));
  }

 public:

  /// Construct from keys, and mutually exclusive values.
  MutexConstraint(const DiscreteKeys& dkeys,
                    const std::vector<size_t>& values);

  // print
  void print(const std::string& s = "", const KeyFormatter& formatter =
                                            DefaultKeyFormatter) const override;

  /// equals
  bool equals(const DiscreteFactor& other, double tol) const override {
    if (!dynamic_cast<const MutexConstraint*>(&other))
      return false;
    else {
      const MutexConstraint& f(static_cast<const MutexConstraint&>(other));
      return cardinalities_.size() == f.cardinalities_.size() &&
              std::equal(cardinalities_.begin(), cardinalities_.end(),
                        f.cardinalities_.begin()) &&
              std::equal (values_.begin(), values_.end(), f.values_.begin());
    }
  }

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
