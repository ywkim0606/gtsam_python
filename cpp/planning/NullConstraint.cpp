/*
 * NullConstraint.cpp
 * @brief NullConstraint constraint
 * @date Mar 20, 2022
 * @author Yoonwoo Kim
 */

#include <gtsam/base/Testable.h>
#include <gtsam/discrete/DecisionTreeFactor.h>
#include <gtsam/discrete/TableFactor.h>
#include <cpp/planning/NullConstraint.h>
#include <cpp/planning/BinarySameConstraint.h>

#include <boost/make_shared.hpp>
using namespace gtsam;
using namespace std;

namespace gtsam_planner {

/* ************************************************************************* */
NullConstraint::NullConstraint(const DiscreteKeys& dkeys)
  : DiscreteFactor(dkeys.indices()) {
  dkeys_ = dkeys;
  for (const DiscreteKey& dkey : dkeys) cardinalities_.insert(dkey);
  for (size_t i = 0; i < dkeys.size(); i++) {
    if (i < dkeys.size()/2) dkeys_t_.push_back(dkeys[i]);
    else dkeys_tp_.push_back(dkeys[i]);
  }
}

/* ************************************************************************* */
void NullConstraint::print(const string& s, const KeyFormatter& formatter) const {
  cout << s << "NullConstraint on ";
  for (Key dkey : keys_) cout << formatter(dkey) << " ";
  cout << endl;
}

/* ************************************************************************* */
DiscreteKeys NullConstraint::discreteKeys() const {
  return dkeys_;
}

/* ************************************************************************* */
double NullConstraint::operator()(const DiscreteValues& values) const {
  for (size_t i = 0; i < dkeys_t_.size(); i++) {
    if ((values.count(dkeys_t_[i].first) != 0) && (values.count(dkeys_tp_[i].first) != 0)) {
      if (values.at(dkeys_t_[i].first) != values.at(dkeys_tp_[i].first)) return 0.0;
    }
  }
  return 1.0;
}

/* ************************************************************************* */
DecisionTreeFactor NullConstraint::toDecisionTreeFactor() const {
  DecisionTreeFactor converted;
  size_t nrKeys = dkeys_.size();
  for (size_t i=0; i<dkeys_t_.size(); i++) {
    BinarySameConstraint bsame(dkeys_t_[i], dkeys_tp_[i]);
    converted = converted * bsame.toDecisionTreeFactor();
  }
  return converted;
}

/* ************************************************************************* */
TableFactor NullConstraint::toTableFactor() const {
  TableFactor converted;
  size_t nrKeys = dkeys_.size();
  for (size_t i=0; i<dkeys_t_.size(); i++) {
    BinarySameConstraint bsame(dkeys_t_[i], dkeys_tp_[i]);
    converted = converted * bsame.toTableFactor();
  }
  return converted;
}

/* ************************************************************************* */
DecisionTreeFactor NullConstraint::operator*(const DecisionTreeFactor& f) const {
  // TODO: can we do this more efficiently?
  return toDecisionTreeFactor() * f;
}

/* ************************************************************************* */
TableFactor NullConstraint::operator*(const TableFactor& f) const {
  return toTableFactor() * f;
}

}  // namespace gtsam_planner
