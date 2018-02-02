import Bp

if __name__ == '__main__':
    mybp = Bp.Bp(2, 6, 1)

    input1 = Bp.doubleArray(2)
    target1 = Bp.doubleArray(1)
    input1[0] = 0
    input1[1] = 0
    target1[0] = 1

    input2 = Bp.doubleArray(2)
    target2 = Bp.doubleArray(1)
    input2[0] = 0
    input2[1] = 1
    target2[0] = 0

    input3 = Bp.doubleArray(2)
    target3 = Bp.doubleArray(1)
    input3[0] = 1
    input3[1] = 0
    target3[0] = 0

    input4 = Bp.doubleArray(2)
    target4 = Bp.doubleArray(1)
    input4[0] = 1
    input4[1] = 1
    target4[0] = 1

    for i in range(100000):
        mybp.error_total = 0.0
        mybp.train(input1, target1)
        mybp.train(input2, target2)
        mybp.train(input3, target3)
        mybp.train(input4, target4)
        if i % 1000 == 0:
            print("error_total = %.5f " % mybp.error_total)

    mybp.test_result(input1)
    mybp.test_result(input2)
    mybp.test_result(input3)
    mybp.test_result(input4)

    # mybp.print_weights()

