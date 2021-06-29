import os
th2 = [0.001,0.002,0.005,0.01,0.015]
data_set = ['mnist','fashion_mnist']
for data in data_set:
        for thres in th2:
                cmd = "python main_pixelhop.py --data_set {} --th2 {} ".format(data,thres)
                print(cmd)
                os.system(cmd)

                cmd = "python main_pixelhop++.py --data_set {}  --th2 {} ".format(data,thres)
                print(cmd)
                os.system(cmd)
    # for key in th1:
    #     cmd = "python main.py --data_set {} --th1 {}".format(data,key)
    #     os.system(cmd)

