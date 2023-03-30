import numpy as np
import numpy.random
import sys

n = int(input())
arr = np.random.rand(n)
print(n)
print('\n'.join([str(a) for a in arr]))

print(f'média: {np.mean(arr):0.9f}', f'var: {np.var(arr):0.9f}', file=sys.stderr)
