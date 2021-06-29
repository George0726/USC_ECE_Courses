# % Qirui Sun
# % USC ID: 1140685892
# % qiruisun@usc.edu
# % Submission Date: 4/14/2021
from tensorflow.keras import optimizers,callbacks
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Conv2D, MaxPooling2D, Dense, Flatten
from tensorflow.keras.datasets import mnist,cifar10,fashion_mnist
from tensorflow.keras.utils import to_categorical
import argparse
import os
import pickle
import matplotlib.pyplot as plt
from tensorflow.keras.regularizers import l1, l2

parser = argparse.ArgumentParser()
parser.add_argument('--save_path', default='./log', type=str)
parser.add_argument('--batch_size', default=128,type =int)
parser.add_argument('--data_set',type = str, choices=['mnist','fashion_mnist','cifar10','inverse_mnist'],default='mnist')
parser.add_argument('--init',type = str, choices=['random_normal','he_normal'],default='random_normal')
parser.add_argument('--lr',type = float,default=0.1)
parser.add_argument('--epoch',type = int,default=100)
parser.add_argument('--is_plot',type = bool,default=False)
parser.add_argument('--kernel_regularizer',type=float, default=0.001)
parser.add_argument('--regularizer',type = str, default='l2',choices = ['None','l1','l2'])
parser.add_argument('--iters',type = int, default=-1)
parser.add_argument('--schedule',type=bool, default=False)
# schedule1
# def schedule(epoch, lr):
#     if epoch < 120:
#         return lr
#     elif epoch < 140:
#         return 0.5 * lr
#     else:
#         return 0.1 * lr

# schedule2
def schedule(epoch, lr):
    if epoch < 140:# 100
        return lr
    else:
        return 0.5 * lr


def Lenet5(input_size,lr, initilization,regularizer):

    model = Sequential()
    model.add(Conv2D(6, (5, 5), padding='valid', activation='relu', kernel_initializer=initilization, kernel_regularizer=regularizer,input_shape=(input_size[0], input_size[1], input_size[2])))
    model.add(MaxPooling2D((2, 2), strides=(2, 2)))
    model.add(Conv2D(16, (5, 5), padding='valid', activation='relu', kernel_initializer=initilization, kernel_regularizer=regularizer))
    model.add(MaxPooling2D((2, 2), strides=(2, 2)))
    model.add(Flatten())
    model.add(Dense(120, activation='relu', kernel_initializer=initilization, kernel_regularizer=regularizer))
    model.add(Dense(84, activation='relu', kernel_initializer=initilization, kernel_regularizer=regularizer))
    model.add(Dense(10, activation='softmax', kernel_initializer=initilization, kernel_regularizer=regularizer))
    sgd = optimizers.SGD(lr=lr, momentum=0.9, nesterov=True, decay=1e-6)
    model.compile(loss='categorical_crossentropy', optimizer=sgd, metrics=['accuracy'])
    return model

def data_prepare(type):

    if type == 'mnist':
        (x_train, y_train), (x_test, y_test) = mnist.load_data()
        x_train = x_train.reshape(-1, 28, 28, 1)
        x_test = x_test.reshape(-1, 28, 28, 1)
        y_train = to_categorical(y_train, 10)
        y_test = to_categorical(y_test, 10)
        x_train = x_train.astype('float32') / 255.0
        x_test = x_test.astype('float32') / 255.0
        return (x_train, y_train), (x_test, y_test), [28,28,1]

    if type == 'fashion_mnist':
        (x_train, y_train), (x_test, y_test) = fashion_mnist.load_data()
        x_train = x_train.reshape(-1, 28, 28, 1)
        x_test = x_test.reshape(-1, 28, 28, 1)
        y_train = to_categorical(y_train, 10)
        y_test = to_categorical(y_test, 10)
        x_train = x_train.astype('float32') / 255.0
        x_test = x_test.astype('float32') / 255.0

        return (x_train, y_train), (x_test, y_test), [28,28,1]

    if type == 'cifar10':
        (x_train, y_train), (x_test, y_test) = cifar10.load_data()
        x_train = x_train.reshape(-1, 32, 32, 3)
        x_test = x_test.reshape(-1, 32, 32, 3)
        y_train = to_categorical(y_train, 10)
        y_test = to_categorical(y_test, 10)
        x_train = x_train.astype('float32') / 255.0
        x_test = x_test.astype('float32') / 255.0

        return (x_train, y_train), (x_test, y_test), [32,32,3]

    if type == 'inverse_mnist':
        (x_train, y_train), (x_test, y_test) = mnist.load_data()
        x_train = x_train.reshape(-1, 28, 28, 1)
        x_test = x_test.reshape(-1, 28, 28, 1)
        y_train = to_categorical(y_train, 10)
        y_test = to_categorical(y_test, 10)
        x_train = x_train.astype('float32') / 255.0
        x_test = 1.0 - x_test.astype('float32') / 255.0
        return (x_train, y_train), (x_test, y_test), [28, 28, 1]
    print('dataset error')


if __name__ == '__main__':
    args = parser.parse_args()
    if os.path.exists(args.save_path) == False:
        os.mkdir(args.save_path)

    (x_train, y_train), (x_test, y_test), input_size=data_prepare(args.data_set)
    if args.regularizer == 'l1':
        regularizer = l1(args.kernel_regularizer)
    elif args.regularizer == 'l2':
        regularizer = l2(args.kernel_regularizer)
    else:
        regularizer = None
    model = Lenet5(input_size,args.lr,args.init,regularizer)
    model.summary()
    # training
    if args.schedule ==False:
        document = model.fit(x_train, y_train, batch_size=args.batch_size, epochs=args.epoch, validation_data=(x_test, y_test), shuffle=True)
        save_file = os.path.join(args.save_path + '/dataset_{}_lr_{}_init_{}_epoch_{}_{}_{}_testAcc_{}_run{}.pickle')
        with open(save_file.format(args.data_set,args.lr,args.init,args.epoch,args.regularizer,args.kernel_regularizer,document.history.get('val_accuracy')[-1],args.iters), 'wb') as file_pi:
            pickle.dump(document.history, file_pi)
    else:
        lr_scheduler = callbacks.LearningRateScheduler(schedule)
        document = model.fit(x_train, y_train, batch_size=args.batch_size, epochs=args.epoch, callbacks=[lr_scheduler], validation_data=(x_test, y_test), shuffle=True)
        save_file = os.path.join(args.save_path + '/dataset_{}_lr_{}_init_{}_epoch_{}_{}_{}_schedule2_testAcc_{}_run{}.pickle')
        with open(save_file.format(args.data_set,args.lr,args.init,args.epoch,args.regularizer,args.kernel_regularizer,document.history.get('val_accuracy')[-1],args.iters), 'wb') as file_pi:
            pickle.dump(document.history, file_pi)

    if args.is_plot:
        train_acc = document.history['accuracy']
        test_acc = document.history['val_accuracy']
        epoch = range(1,1+args.epoch)
        fig_name = 'dataset_{}_lr_{}_init_{}_epoch_{}_l2_{}'.format(args.data_set,args.lr,args.init,args.epoch,args.kernel_regularizer)
        plt.plot(epoch,train_acc, 'rs-', label='training accuracy')
        plt.plot(epoch, test_acc, 'b*-', label='test accuracy')
        plt.legend()
        plt.xlabel('Epoch')
        plt.ylabel('Accuracy')
        plt.title(fig_name)
        plt.savefig(os.path.join(args.save_path+'/'+fig_name+'.jpg'))
