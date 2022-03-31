"""
GTSAM Copyright 2010-2019, Georgia Tech Research Corporation,
Atlanta, Georgia 30332-0415
All Rights Reserved

See LICENSE for the license information

MultiValueConstraint unit tests.
Author: Yoonwoo Kim
"""
import unittest

import numpy as np

import gtsam
from gtsam import DecisionTreeFactor, DiscreteValues, DiscreteKeys
import gtsam_planner
from gtsam_planner import MultiValueConstraint
from gtsam.utils.test_case import GtsamTestCase


class TestMultiValueConstraint(GtsamTestCase):
    """Tests for MultiValueConstraints which is basically multiple SingleValueConstraints"""

    def setUp(self):
        self.keys = DiscreteKeys()
        key_list = [(0, 2), (1, 2), (2, 4)]
        for key in key_list:
            self.keys.push_back(key)
        self.vals = [0, 1, 3]
        self.constraint = MultiValueConstraint(self.keys, self.vals)

    def test_operatorTrue(self):
        """Checks if factor returns 1.0 when variables have tentative values"""
        values = DiscreteValues()
        values[self.keys.at(0)[0]] = 0
        values[self.keys.at(1)[0]] = 1
        values[self.keys.at(2)[0]] = 3
        self.assertEqual(self.constraint(values), 1.0)
    
    def test_operatorFalse(self):
        """Checks if factor returns 1.0 when variables have tentative values"""
        values = DiscreteValues()
        values[self.keys.at(0)[0]] = 0
        values[self.keys.at(1)[0]] = 1
        values[self.keys.at(2)[0]] = 2
        self.assertEqual(self.constraint(values), 0.0)

    def test_toDecisionTree(self):
        """Tests if factor can be transformed to decision tree factor"""
        expected = self.constraint.toDecisionTreeFactor()
        self.assertIsInstance(expected, DecisionTreeFactor)
        self.gtsamAssertEquals(DecisionTreeFactor(self.keys, "0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0"), expected)


if __name__ == "__main__":
    unittest.main()
