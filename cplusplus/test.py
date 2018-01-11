from Bp import *

mybp = Bp(2, 3, 1)

inputs1 = doubleArray(2)
inputs1[0] = 0
inputs1[1] = 0

    [0, 0], 
    [0, 1],
    [1, 0],
    [1, 1]

targets= [
    [1],
    [0],
    [0],
    [1]
    ]
    
for i in range(10000):
    mybp.error_total = 0.0
    mybp.train([0,0], [1])
    mybp.train([0,1], [0])
    mybp.train([1,0], [0])
    mybp.train([1,1], [1])
        
    if i % 1000 == 0:
        print("error_total = %.5f" % mybp.error_total)

mybp.test_result([0,0], [1])
mybp.test_result([0,1], [0])
mybp.test_result([1,0], [0])
mybp.test_result([1,1], [1])
