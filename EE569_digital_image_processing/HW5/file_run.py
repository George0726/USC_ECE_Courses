import os
# % Qirui Sun
# % USC ID: 1140685892
# % qiruisun@usc.edu
# % Submission Date: 4/14/2021

# experiment_hub = [ "python lenet.py --data_set cifar10 --save_path ./cifar10 --lr 0.001 --init he_normal --epoch 150 --schedule True --regularizer l2 --iters {} "]#,\
               # "python lenet.py --data_set cifar10 --save_path ./cifar10 --lr 0.001 --init he_normal --epoch 150 --regularizer l1 --iters {} ",\
               #  "python lenet.py --data_set cifar10 --save_path ./cifar10 --lr 0.001 --init random_normal --epoch 150 --regularizer l2 --iters {} ",\
               #  "python lenet.py --data_set cifar10 --save_path ./cifar10 --lr 0.05 --init he_normal --epoch 150 --regularizer l2 --iters {} ",\
               #  "python lenet.py --data_set cifar10 --save_path ./cifar10 --lr 0.05 --init he_normal --epoch 150 --schedule True --regularizer l2 --iters {} "
               # ]
# experiment_hub = [ "python lenet.py --data_set fashion_mnist --save_path ./fashion_mnist --lr 0.01 --init he_normal --schedule True --epoch 110 --iters {} "]
# for key in experiment_hub:
#     for i in range(5):
#         cmd = key.format(i+1)
#         os.system(cmd)
# "python lenet.py --data_set fashion_mnist --save_path ./fashion_mnist --lr 0.01 --init he_normal --schedule True --epoch 110 --iters {} "]
# "python lenet.py --data_set mnist --save_path ./mnist --lr 0.01 --init he_normal --epoch 80 --iters 2 "
# "python lenet.py --data_set fashion_mnist --save_path ./fashion_mnist --lr 0.01 --init he_normal --epoch 80 --iters {} "
# "python lenet.py --data_set cifar10 --save_path ./cifar10 --lr 0.001 --init he_normal --epoch 150 --regularizer None --iters {} "

# experiment_hub = ["python lenet.py --data_set mnist --save_path ./mnist --lr 0.01 --init random_normal --regularizer l2 --epoch 80 --iters {} ",\
#                     "python lenet.py --data_set mnist --save_path ./mnist --lr 0.01 --init he_normal --regularizer l1 --epoch 80 --iters {} ",\
#                     "python lenet.py --data_set mnist --save_path ./mnist --lr 0.01 --init he_normal --regularizer None --epoch 80 --iters {} ",\
#                     "python lenet.py --data_set mnist --save_path ./mnist --lr 0.005 --init he_normal --regularizer l2 --epoch 80 --iters {}  "]
# experiment_hub = ["python lenet.py --data_set fashion_mnist --save_path ./fashion_mnist --lr 0.01 --init random_normal --epoch 80 --iters {} ",\
#                     "python lenet.py --data_set fashion_mnist --save_path ./fashion_mnist --lr 0.01 --init he_normal --regularizer l1 --epoch 80 --iters {} ",\
#                     "python lenet.py --data_set fashion_mnist --save_path ./fashion_mnist --lr 0.01 --init he_normal --regularizer None --epoch 80 --iters {} ",\
#                     "python lenet.py --data_set fashion_mnist --save_path ./fashion_mnist --lr 0.05 --init he_normal --regularizer l2 --epoch 80 --iters {} "]


for i in range(5):
    cmd = "python inverse_lenet.py --iters {} ".format(i+1)
    os.system(cmd)