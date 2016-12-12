# -*- coding: utf-8 -*-
"""
Created on Tue Dec 13 01:18:30 2016

@author: Егор
"""

import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("output00.txt")
print('loaded')
plt.hist(data, bins=70)