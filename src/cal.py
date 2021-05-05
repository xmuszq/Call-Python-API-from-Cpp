## to import self made function in python to c/cpp,
# make the current working directory into python path with command:
# export PYTHONPATH=$PYTHONPATH:/home/zhen/Projects/PyAPI4Cpp/call-python-from-cpp/src
## Does following work if we explicitly exposethe .py file to the cpp?
# include "C:/Python27/Lib/site-packages/numpy/core/include/numpy/arrayobject.h"


# the customed func. 
def add(i, j):
    c=i+j+i*j
    print('we are python, add() ', c)
    return c 


# the customed func. with a imported package
import math
def add_ceil(i, j):
    c=i+j+j*i
    print('from python . add_ceil()', c)
    c=math.ceil(c)
    return c



def str_process(s1, s2):
    s=s1+s2
    print('from python str_process()', s)
    return s

import numpy as np
def vector_process(v1):
    v1=np.asarray(v1)
    print('from python vector_process()', v1.shape, v1)
    return v1




import numpy as np
def img_process(img):
    img=np.asarray(img)
    print('from python img_process()')
    print('the shape of img ', img.shape)
    return img
    
def img_process_return_float(img):
    img=np.asarray(img).astype(float)
    img[0][0]=1.1233
    print('from python img_process()')
    print('the shape of img ', img.shape)
    return img


