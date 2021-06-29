import numpy as np
from tensorflow.keras.datasets import mnist,fashion_mnist
from skimage.util import view_as_windows
from pixelhop import Pixelhop
from skimage.measure import block_reduce
import xgboost as xgb
import warnings, gc
import time
import argparse
from sklearn.metrics import accuracy_score
import os

parser = argparse.ArgumentParser()
parser.add_argument('--data_set',type = str, choices=['mnist','fashion_mnist'],default='mnist')
parser.add_argument('--is_resume', default='', type=str)
parser.add_argument('--th2',default=0.005,type=float)
# parser.add_argument('--cw',default= False,type=bool)

np.random.seed(1)

# Preprocess
N_Train_Reduced = 10000    # 10000
N_Train_Full = 60000     # 50000
N_Test = 10000            # 10000

BS = 10000 # batch size


def shuffle_data(X, y):
    shuffle_idx = np.random.permutation(y.size)
    X = X[shuffle_idx]
    y = y[shuffle_idx]
    return X, y


def select_balanced_subset(images, labels, use_num_images):
    '''
    select equal number of images from each classes
    '''
    num_total, H, W, C = images.shape
    num_class = np.unique(labels).size
    num_per_class = int(use_num_images / num_class)

    # Shuffle
    images, labels = shuffle_data(images, labels)

    selected_images = np.zeros((use_num_images, H, W, C))
    selected_labels = np.zeros(use_num_images)

    for i in range(num_class):
        selected_images[i * num_per_class:(i + 1) * num_per_class] = images[labels == i][:num_per_class]
        selected_labels[i * num_per_class:(i + 1) * num_per_class] = np.ones((num_per_class)) * i

    # Shuffle again
    selected_images, selected_labels = shuffle_data(selected_images, selected_labels)

    return selected_images, selected_labels

def Shrink(X, shrinkArg):
    #---- max pooling----
    pool = shrinkArg['pool']
    # TODO: fill in the rest of max pooling
    X = block_reduce(X, block_size=(1, pool, pool, 1), func=np.max)

    #---- neighborhood construction
    win = shrinkArg['win']
    stride = shrinkArg['stride']
    pad = shrinkArg['pad']
    ch = X.shape[-1]
    # TODO: fill in the rest of neighborhood construction

    if pad>0:
        X = np.pad(X,((0,0),(pad,pad),(pad,pad),(0,0)),'reflect')
    X = view_as_windows(X, (1, win, win, ch), (1, stride, stride, ch))

    return X.reshape(X.shape[0],X.shape[1],X.shape[2],-1)

# example callback function for how to concate features from different hops
def Concat(X, concatArg):
    return X

def get_feat(X, num_layers=3):
    output = p2.transform_singleHop(X,layer=0)
    if num_layers>1:
        for i in range(num_layers-1):
            output = p2.transform_singleHop(output, layer=i+1)
    return output


if __name__ == "__main__":
    args = parser.parse_args()
    warnings.filterwarnings("ignore")
    # ---------- Load MNIST data or fashion_MNIST and split ----------
    if args.data_set == "mnist":
        (x_train, y_train), (x_test,y_test) = mnist.load_data()
        print("mnist dataset!")
    else:
        (x_train,y_train),(x_test,y_test) = fashion_mnist.load_data()
        print("fashion-mnist dataset!")

    # -----------Data Preprocessing-----------
    x_train = np.asarray(x_train,dtype='float32')[:,:,:,np.newaxis]
    x_test = np.asarray(x_test,dtype='float32')[:,:,:,np.newaxis]
    y_train = np.asarray(y_train,dtype='int')
    y_test = np.asarray(y_test,dtype='int')

    # if use only 10000 images train pixelhop
    x_train_reduced, y_train_reduced = select_balanced_subset(x_train, y_train, use_num_images=N_Train_Reduced)

    x_train_reduced /= 255.0

    x_train /= 255.0
    x_test /= 255.0

    # -----------Module 1: set PixelHop parameters-----------
    t0 = time.time()
    # TODO: fill in this part
    shrinkArgs = [{'func':Shrink,'win':5,'stride':1,'pad':2,'pool':1},
                  {'func':Shrink,'win':5,'stride':1,'pad':0,'pool':2},
                  {'func':Shrink,'win':5,'stride':1,'pad':0,'pool':2}]

    SaabArgs = [{'num_AC_kernels': -1, 'needBias': False,'cw': False},
                {'num_AC_kernels': -1, 'needBias': True, 'cw': True},
                {'num_AC_kernels': -1, 'needBias': True, 'cw': True}]

    concatArg = {'func':Concat}

    print("parameter setting!")
    # -----------Module 1: Train PixelHop -----------
    # TODO: fill in this part
    p2 = Pixelhop(depth=3,TH1=0.001,TH2=args.th2,SaabArgs=SaabArgs,shrinkArgs = shrinkArgs,concatArg=concatArg)
    p2.fit(x_train_reduced)

    # p2.save( "./phckpt/ckpt/dataset_{}_TH2_{}_".format(args.data_set,args.th2))

    t_module1 = time.time()
    print(t_module1-t0)
    print("-----------------------Module 1 done--------------------------------------")

    # --------- Module 2: get only Hop 3 feature for both training set and testing set -----------
    # you can get feature "batch wise" and concatenate them if your memory is restricted
    # TODO: fill in this part
    split_train_arr = []

    for i in range(6):
        temp = get_feat(x_train[i*BS:(i+1)*BS,:,:,:])
        split_train_arr.append(temp)

    train_hop3_feats = np.concatenate((split_train_arr[0],split_train_arr[1],split_train_arr[2],split_train_arr[3],split_train_arr[4],split_train_arr[5]),axis=0)

    # train_hop3_feats = get_feat(x_train)
    test_hop3_feats = get_feat(x_test)

    print(train_hop3_feats.shape,test_hop3_feats.shape)

    print("----------------------transform for total training and test set--------------------")

    # --------- Module 2: standardization
    STD = np.std(train_hop3_feats,axis=0, keepdims=1)
    train_hop3_feats = train_hop3_feats/STD
    test_hop3_feats = test_hop3_feats/STD

    train_hop3_feats = np.squeeze(train_hop3_feats)
    test_hop3_feats = np.squeeze(test_hop3_feats)


    # save_feature = "./phckpt/dataset_{}_TH2_{}_.npz".format(args.data_set,args.th2)

    print("---------------------standardize extracted features-----------------")
    t_module2 = time.time()

    #---------- Module 3: Train XGBoost classifier on hop3 feature ---------

    # tr_acc = [] # change some parameters to see whether final accuracy changes
    # te_acc = []

    clf = xgb.XGBClassifier(n_jobs=-1,
                        objective='multi:softprob',
                        # tree_method='gpu_hist', gpu_id=None,
                        max_depth=6,n_estimators=100,
                        min_child_weight=5,gamma=5,
                        subsample=0.8,learning_rate=0.1,
                        nthread=8,colsample_bytree=1.0)

    clf.fit(train_hop3_feats,y_train)
    y_train_pred = clf.predict(train_hop3_feats)
    y_test_pred = clf.predict(test_hop3_feats)

    t_module3 = time.time()

    test_feature_1 = get_feat(x_test[:10,:,:,:],1)

    test_feature_2 = get_feat(x_test[:10,:,:,:],2)

    with open('record.txt', 'a') as f:
        f.write("\npixelhop++ dataset: {};TH2: {};---\n".format(args.data_set,args.th2))
        f.write("---training accuracy: {}; test accuracy: {}---\n".format(accuracy_score(y_train, y_train_pred),accuracy_score(y_test, y_test_pred)))
        f.write("---running time---module1: {}s ; module2:{}s ; module3:{}s\n".format(t_module1-t0,t_module2-t_module1,t_module3-t_module2))
        f.write("feature size: hop1 {} ; hop2 {}; hop3 {}\n".format(test_feature_1.shape,test_feature_2.shape,train_hop3_feats.shape))
    # with open('{}_train_acc.txt'.format(args.data_set), 'a') as f:
    #     f.write("{}---{}\n".format(args.th2,accuracy_score(y_train, y_train_pred)))
    # with open('{}_test_acc.txt'.format(args.data_set), 'a') as f:
    #     f.write("{}---{}\n".format(args.th2,accuracy_score(y_test, y_test_pred)))
    # print("train accuracy", accuracy_score(y_train, y_train_pred))
    # print("train accuracy", accuracy_score(y_train, y_train_pred))
    # print("test accuracy", accuracy_score(y_test, y_test_pred))

    # TODO: fill in the rest and report accuracy


    #
    # np.savez(save_feature,train_feature = train_hop3_feats, train_label = y_train, test_feature = test_hop3_feats, test_label = y_test, test_feature_0 = test_feature_0,test_feature_1 = test_feature_1, test_feature_2 = test_feature_2 )
    # print("feature saved!")


