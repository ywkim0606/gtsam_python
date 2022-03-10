/*
 * MutexConstraint.cpp
 * @brief domain constraint
 * @date Feb 6, 2012
 * @author Yoonwoo Kim
 */

#include <gtsam/base/Testable.h>
#include <gtsam/discrete/DecisionTreeFactor.h>
#include <cpp/planning/MutexConstraint.h>

#include <boost/make_shared.hpp>
using namespace gtsam;
using namespace std;

namespace gtsam_example {

/* ************************************************************************* */
MutexConstraint::MutexConstraint(const DiscreteKeys& dkeys,
  const vector<size_t>& values) : DiscreteFactor(dkeys.indices()) {
  for (const DiscreteKey& dkey : dkeys) cardinalities_.insert(dkey);
  for (const size_t& value : values) values_.push_back(value);
}

/* ************************************************************************* */
void MutexConstraint::print(const std::string& s, const KeyFormatter& formatter) const {
  std::cout << s << "MutexConstraint on ";
  for (Key dkey : keys_) std::cout << formatter(dkey) << " ";
  std::cout << std::endl;
}

/* ************************************************************************* */
double MutexConstraint::operator()(const DiscreteValues& values) const {
  size_t count = 0;
  for (size_t i=0; i < values_.size(); i++) {
    size_t value = values.at(keys_[i]);  // get the value for that key
    if (value == values_[i]) count += 1.0;
    if (count > 1) return 0.0;
  }
  return 1.0;
}

/* ************************************************************************* */
DecisionTreeFactor MutexConstraint::toDecisionTreeFactor() const {
  DecisionTreeFactor converted;
  size_t nrKeys = keys_.size();
  for (size_t i = 0; i < nrKeys; i++) {
    SingleValueConstraint single(discreteKey(i), values_[i]);
    converted = converted * single.toDecisionTreeFactor();
  }
  return converted;
}

/* ************************************************************************* */
DecisionTreeFactor MutexConstraint::operator*(const DecisionTreeFactor& f) const {
  // TODO: can we do this more efficiently?
  return toDecisionTreeFactor() * f;
}

/* ************************************************************************* */
}  // namespace gtsam

