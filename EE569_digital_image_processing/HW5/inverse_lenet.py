# % Qirui Sun
# % USC ID: 1140685892
# % qiruisun@usc.edu
# % Submission Date: 4/14/2021
from tensorflow.keras.layers import Flatten, MaxPooling2D, Conv2D, Input, Dense
from tensorflow.keras.models import Model
from tensorflow.keras.utils import to_categorical
from tensorflow.keras.datasets import mnist
from tensorflow.keras.regularizers import l1, l2
from tensorflow.keras import optimizers
import os
import pickle
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--save_path', default='./inverse_mnist', type=str)
parser.add_argument('--batch_size', default=128,type =int)
parser.add_argument('--init',type = str, choices=['random_normal','he_normal'],default='he_normal')
parser.add_argument('--lr',type = float,default=0.01)
parser.add_argument('--epoch',type = int,default=100)
parser.add_argument('--kernel_regularizer',type=float, default=0.001)
parser.add_argument('--regularizer',type = str, default='l2',choices = ['None','l1','l2'])
parser.add_argument('--iters',type = int, default=-1)


(x_train, y_train), (x_test, y_test) = mnist.load_data()
x_train = x_train.reshape(-1, 28, 28, 1)
x_test = x_test.reshape(-1, 28, 28, 1)
y_train = to_categorical(y_train, 10)
y_test = to_categorical(y_test, 10)
x_train = x_train.astype('float32') / 255.0
x_test = x_test.astype('float32') / 255.0
x_test_ori = x_test
x_test = 1 - x_test


def LeNet_5_Modified(lr, initilization,regularizer):
    x_input = Input(shape=(28,28,1))
    X_reverse = 1 - x_input
    X_transform = X_reverse*x_input
    x_cov1 = Conv2D(6, (5, 5), kernel_initializer=initilization, kernel_regularizer=regularizer, activation='relu')(X_transform)
    x_pool1 = MaxPooling2D()(x_cov1)
    x_cov2 = Conv2D(16, (5, 5), kernel_initializer=initilization, kernel_regularizer=regularizer, activation='relu')(x_pool1)
    x_pool2 = MaxPooling2D()(x_cov2)
    x_flatten = Flatten()(x_pool2)
    x_dense1 = Dense(120, kernel_initializer=initilization, kernel_regularizer=regularizer, activation='relu')(x_flatten)
    x_dense2 = Dense(84, kernel_initializer=initilization, kernel_regularizer=regularizer, activation='relu')(x_dense1)
    x_output = Dense(10, kernel_initializer=initilization, kernel_regularizer=regularizer, activation='softmax')(x_dense2)

    model = Model(inputs=x_input, outputs=x_output)
    sgd = optimizers.SGD(lr=lr, momentum=0.9, nesterov=True, decay=1e-6)
    model.compile(loss='categorical_crossentropy', optimizer=sgd, metrics=['accuracy'])
    return model


if __name__ == '__main__':
    args = parser.parse_args()
    if os.path.exists(args.save_path) == False:
        os.mkdir(args.save_path)
    if args.regularizer == 'l1':
        regularizer = l1(args.kernel_regularizer)
    elif args.regularizer == 'l2':
        regularizer = l2(args.kernel_regularizer)
    else:
        regularizer = None

    model = LeNet_5_Modified(args.lr,args.init,regularizer)
    model.summary()
    document = model.fit(x_train, y_train,
                                   batch_size=args.batch_size,
                                   epochs=args.epoch,
                                   validation_data=(x_test, y_test)
                                   )
    save_file = os.path.join(args.save_path + '/lr_{}_init_{}_epoch_{}_{}_{}_testAcc_{}_run{}.pickle')
    results = model.evaluate(x_test_ori, y_test)

    with open("file.txt", 'a') as f:
        for s in results:
            f.write(str(s) + '\n')

    with open(save_file.format(args.lr, args.init, args.epoch, args.regularizer, args.kernel_regularizer,
                               document.history.get('val_accuracy')[-1], args.iters), 'wb') as file_pi:
        pickle.dump(document.history, file_pi)