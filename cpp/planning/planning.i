namespace gtsam_planner {
#include <gtsam/discrete/DecisionTreeFactor.h>
#include <gtsam/discrete/TableFactor.h>

#include <cpp/planning/SingleValueConstraint.h>
virtual class SingleValueConstraint : gtsam::DiscreteFactor {
  SingleValueConstraint(gtsam::Key key, size_t n, size_t value);
  SingleValueConstraint(const gtsam::DiscreteKey& dkey, size_t value);
  void print(const string s="",
            const gtsam::KeyFormatter& formatter = 
              gtsam::DefaultKeyFormatter) const;
  bool equals(const gtsam::DiscreteFactor& other, double tol) const;
  double operator()(const gtsam::DiscreteValues& values) const;
  gtsam::DecisionTreeFactor toDecisionTreeFactor() const;
  gtsam::TableFactor toTableFactor() const;
};

#include <cpp/planning/NotSingleValueConstraint.h>
// #include <gtsam/discrete/DecisionTreeFactor.h>
virtual class NotSingleValueConstraint : gtsam::DiscreteFactor {
  NotSingleValueConstraint(gtsam::Key key, size_t n, size_t value);
  NotSingleValueConstraint(const gtsam::DiscreteKey& dkey, size_t value);
  void print(const string s="",
            const gtsam::KeyFormatter& formatter = 
              gtsam::DefaultKeyFormatter) const;
  bool equals(const gtsam::DiscreteFactor& other, double tol) const;
  double operator()(const gtsam::DiscreteValues& values) const;
  gtsam::DecisionTreeFactor toDecisionTreeFactor() const;
  gtsam::TableFactor toTableFactor() const;
};

#include <cpp/planning/MultiValueConstraint.h>
virtual class MultiValueConstraint : gtsam::DiscreteFactor {
  MultiValueConstraint(const gtsam::DiscreteKeys& dkey, const std::vector<size_t>& values);
  void print(const string s="",
          const gtsam::KeyFormatter& formatter = 
            gtsam::DefaultKeyFormatter) const;
  bool equals(const gtsam::DiscreteFactor& other, double tol) const;
  gtsam::DiscreteKeys discreteKeys() const;
  double operator()(const gtsam::DiscreteValues& values) const;
  gtsam::DecisionTreeFactor toDecisionTreeFactor() const;
  gtsam::TableFactor toTableFactor() const;
};

#include <cpp/planning/OrConstraint.h>
virtual class OrConstraint : gtsam::DiscreteFactor {
  OrConstraint(const std::vector<gtsam::DecisionTreeFactor>& factors);
  void print(const string s="",
          const gtsam::KeyFormatter& formatter = 
            gtsam::DefaultKeyFormatter) const;
  bool equals(const gtsam::DiscreteFactor& other, double tol) const;
  double operator()(const gtsam::DiscreteValues& values) const;
  gtsam::DecisionTreeFactor toDecisionTreeFactor() const;
  gtsam::TableFactor toTableFactor() const;
};

#include <cpp/planning/MutexConstraint.h>
virtual class MutexConstraint : gtsam::DiscreteFactor {
  MutexConstraint(const gtsam::DiscreteKeys& dkey, const std::vector<size_t>& values);
  void print(const string s="",
          const gtsam::KeyFormatter& formatter = 
            gtsam::DefaultKeyFormatter) const;
  bool equals(const gtsam::DiscreteFactor& other, double tol) const;
  double operator()(const gtsam::DiscreteValues& values) const;
  gtsam::DecisionTreeFactor toDecisionTreeFactor() const;
  gtsam::TableFactor toTableFactor() const;
};

// #include <cpp/planning/MutexAddConstraint.h>
// virtual class MutexAddConstraint : gtsam::DiscreteFactor {
//   MutexAddConstraint(const gtsam::DiscreteKey& dkey,
//     const gtsam::DiscreteKeys& dkeys, const std::vector<size_t>& values);
//   void print(const string s="",
//           const gtsam::KeyFormatter& formatter = 
//             gtsam::DefaultKeyFormatter) const;
//   bool equals(const gtsam::DiscreteFactor& other, double tol) const;
//   double operator()(const gtsam::DiscreteValues& values) const;
//   gtsam::DecisionTreeFactor toDecisionTreeFactor() const;
// };

#include <cpp/planning/BinarySameConstraint.h>
virtual class BinarySameConstraint : gtsam::DiscreteFactor {
  BinarySameConstraint();
  BinarySameConstraint(const gtsam::DiscreteKey& key1, const gtsam::DiscreteKey& key2);
  void print(const string s="",
          const gtsam::KeyFormatter& formatter = 
            gtsam::DefaultKeyFormatter) const;
  bool equals(const gtsam::DiscreteFactor& other, double tol) const;
  double operator()(const gtsam::DiscreteValues& values) const;
  gtsam::DecisionTreeFactor toDecisionTreeFactor() const;
  gtsam::TableFactor toTableFactor() const;
  gtsam::TableFactor toTableFactor() const;
};

#include <cpp/planning/NullConstraint.h>
virtual class NullConstraint : gtsam::DiscreteFactor {
  NullConstraint(const gtsam::DiscreteKeys& dkeys);
  gtsam::DiscreteKeys discreteKeys() const;
  void print(const string s="",
          const gtsam::KeyFormatter& formatter = 
            gtsam::DefaultKeyFormatter) const;
  bool equals(const gtsam::DiscreteFactor& other, double tol) const;
  double operator()(const gtsam::DiscreteValues& values) const;
  gtsam::DecisionTreeFactor toDecisionTreeFactor() const;
  gtsam::TableFactor toTableFactor() const;
};

// #include <cpp/planning/OperatorChooseConstraint.h>
// virtual class OperatorChooseConstraint : gtsam::DiscreteFactor {
//   OperatorChooseConstraint(const std::vector<gtsam_planner::MultiValueConstraint>& factors,
//     std::size_t which_op);
//   void print(const string s="",
//           const gtsam::KeyFormatter& formatter = 
//             gtsam::DefaultKeyFormatter) const;
//   bool equals(const gtsam::DiscreteFactor& other, double tol) const;
//   double operator()(const gtsam::DiscreteValues& values) const;
//   gtsam::DecisionTreeFactor toDecisionTreeFactor() const;
// };

// #include <cpp/planning/OperatorAddConstraint.h>
// virtual class OperatorAddConstraint : gtsam::DiscreteFactor {
//   OperatorAddConstraint(const gtsam::DiscreteKey& dkey, const gtsam::DiscreteKeys& dkeys,
//     const std::vector<gtsam_planner::MultiValueConstraint>& factors,
//     const std::vector<gtsam_planner::NullConstraint>& null_factors);
//   void print(const string s="",
//           const gtsam::KeyFormatter& formatter = 
//             gtsam::DefaultKeyFormatter) const;
//   double operatorKey() const;
//   bool equals(const gtsam::DiscreteFactor& other, double tol) const;
//   double operator()(const gtsam::DiscreteValues& values) const;
//   gtsam::DecisionTreeFactor toDecisionTreeFactor() const;
// };

// #include <cpp/planning/OperatorConstraint.h>
// virtual class OperatorConstraint : gtsam::DiscreteFactor {
//   OperatorConstraint(const gtsam::DiscreteKeys& multi_keys, const std::vector<size_t>& values,
//     const gtsam::DiscreteKeys& null_keys, const gtsam::DiscreteKeys& dkeys);
//   void print(const string s="",
//           const gtsam::KeyFormatter& formatter = 
//             gtsam::DefaultKeyFormatter) const;
//   bool equals(const gtsam::DiscreteFactor& other, double tol) const;
//   gtsam::DiscreteKeys discreteKeys() const;
//   double operator()(const gtsam::DiscreteValues& values) const;
//   gtsam::DecisionTreeFactor toDecisionTreeFactor() const;
// };

#include <cpp/planning/OperatorOrConstraint.h>
virtual class OperatorOrConstraint : gtsam::DiscreteFactor {
  OperatorOrConstraint(const gtsam::DiscreteKey& dkey, const gtsam::DiscreteKeys& dkeys,
    const std::vector<gtsam_planner::MultiValueConstraint>& factors);
  void print(const string s="",
          const gtsam::KeyFormatter& formatter = 
            gtsam::DefaultKeyFormatter) const;
  bool equals(const gtsam::DiscreteFactor& other, double tol) const;
  double operatorKey() const;
  double operator()(const gtsam::DiscreteValues& values) const;
  gtsam::DecisionTreeFactor toDecisionTreeFactor() const;
  gtsam::TableFactor toTableFactor() const;
};

#include <cpp/planning/FrameConstraint.h>
virtual class FrameConstraint : gtsam::DiscreteFactor {
  FrameConstraint(const gtsam::DiscreteKey& dkey, const gtsam::DiscreteKeys& dkeys,
    const std::vector<gtsam_planner::NullConstraint>& null_factors);
  void print(const string s="",
          const gtsam::KeyFormatter& formatter = 
            gtsam::DefaultKeyFormatter) const;
  double operatorKey() const;
  bool equals(const gtsam::DiscreteFactor& other, double tol) const;
  double operator()(const gtsam::DiscreteValues& values) const;
  gtsam::DecisionTreeFactor toDecisionTreeFactor() const;
  gtsam::TableFactor toTableFactor() const;
};

// #include <cpp/planning/ValidVariablesConstraint.h>
// virtual class ValidVariablesConstraint : gtsam::DiscreteFactor {
//   ValidVariablesConstraint(const gtsam_planner::BinarySameConstraint b_factor,
//     const std::vector<gtsam_planner::MultiValueConstraint>& m_factors, const gtsam::DiscreteKeys dkeys);
//   void print(const string s="",
//           const gtsam::KeyFormatter& formatter = 
//             gtsam::DefaultKeyFormatter) const;
//   bool equals(const gtsam::DiscreteFactor& other, double tol) const;
//   double operator()(const gtsam::DiscreteValues& values) const;
//   gtsam::DecisionTreeFactor toDecisionTreeFactor() const;
// };

}
