"""
これは作ったグラフを画像として保存するプログラム
"""

import matplotlib.pyplot as plt
import numpy as np

infilename = 'data/RangeReferenceChirpExt.txt'
data = np.loadtxt(infilename)
if data is None:
    print('read data error...')

x1 = data[:, 0]
y1 = data[:, 1]


plt.plot(x1, y1, color = 'red', marker = 'None')
plt.savefig(infilename + '.png')

print('done.')

