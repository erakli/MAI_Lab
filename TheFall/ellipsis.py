# -*- coding: utf-8 -*-
"""
Created on Sun Dec 11 15:44:26 2016

@author: Егор
"""

from __future__ import division
import numpy as np
from sympy import sqrt, symbols, pprint
from sympy.plotting import plot
from scipy.stats import chi2

m_vec = np.loadtxt("m_vec.txt", delimiter="\t")
K_matrix = np.loadtxt("K_matrix.txt", delimiter="\t")

K_sqrt = np.sqrt(K_matrix)
r = K_matrix[1, 0] / (K_sqrt[0, 0] * K_sqrt[1, 1])

m1, m2 = m_vec[0], m_vec[1]
K1, K2 = K_matrix[0, 0], K_matrix[1, 1]
K1_sqrt, K2_sqrt = K_sqrt[0, 0], K_sqrt[1, 1]

x, y = symbols('x, y', real = True)
chi2_alpha = chi2.ppf(0.95, 2)

y = ((sqrt(-K1 * K2 * (r**2 - 1) * (chi2_alpha * K1 - (m1 - x)**2)) +
      K1_sqrt * K2_sqrt * r * (x - m1) + K1 * m2) / K1) 

print(y)
plot(y, (x, 1, 10))