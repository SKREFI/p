import cv2
import numpy as np
import os
import sys
import tensorflow as tf
import random
from sklearn.model_selection import train_test_split

EPOCHS = 3
IMG_WIDTH = 32
IMG_HEIGHT = 32
NUM_CATEGORIES = 9
TEST_SIZE = 0.4

def main():
    # Check command-line arguments
    if len(sys.argv) not in [2, 3]:
        # ok __name__ is going to be __main__ but in case you're runnig this from some other file :D
        sys.exit(f"Usage: python {__name__}.py data_directory [model.h5]")

    # Get image arrays and labels for all image files
    images, labels = load_data(sys.argv[1])

    # Split data into training and testing sets
    labels = tf.keras.utils.to_categorical(labels)
    x_train, x_test, y_train, y_test = train_test_split(np.array(images), np.array(labels), test_size=TEST_SIZE)


    print(x_train[0].shape)
    exit()
    # Get a compiled neural network
    model = get_model()

    # Fit model on training data
    model.fit(x_train, y_train, epochs=EPOCHS)

    # Evaluate neural network performance
    model.evaluate(x_test, y_test, verbose=2)

    # Save model to file       indexi     0           1          2
    if len(sys.argv) == 3:  # python3 FISIERUL.py data_file savemodel
        filename = sys.argv[2]
        model.save(filename)
        print(f"Model saved to {filename}.")


def load_data(data_dir):
    """
    Load image data from directory `data_dir`.

    Assume `data_dir` has one directory named after each category, numbered
    0 through NUM_CATEGORIES - 1. Inside each category directory will be some
    number of image files.

    Return tuple `(images, labels)`. `images` should be a list of all
    of the images in the data directory, where each image is formatted as a
    numpy ndarray with dimensions IMG_WIDTH x IMG_HEIGHT x 3. `labels` should
    be a list of integer labels, representing the categories for each of the
    corresponding `images`.
    """
    imagelist = []
    labellist = []
    count = 0
    listofimages = []
    with open(os.path.join(data_dir, "train.txt"), "r") as a_file:
        for line in a_file:
            stripped_line = line.strip()
            a = stripped_line.split(",")
            listofimages.append(a)
    for ims in listofimages:
        image_dir = os.path.join(data_dir, "train")
        imagelist.append(cv2.resize(cv2.imread(os.path.join(image_dir, ims[0])), (IMG_WIDTH, IMG_HEIGHT)))
        labellist.append(ims[1])
    # for image_path in os.listdir(data_dir):
    # image_dir=os.path.join(data_dir,image_path)
    # for image in os.listdir(image_dir):
    # imagelist.append(cv2.resize(cv2.imread(os.path.join(image_dir,image)),(IMG_WIDTH,IMG_HEIGHT)))
    # labellist.append(count)
    # count += 1
    return (imagelist, labellist)


def get_model():
    """
    Returns a compiled convolutional neural network model. Assume that the
    `input_shape` of the first layer is `(IMG_WIDTH, IMG_HEIGHT, 3)`.
    The output layer should have `NUM_CATEGORIES` units, one for each category.
    """


    model = tf.keras.models.Sequential([  
        tf.keras.layers.Conv2D(32, (3, 3), activation="relu", input_shape=(IMG_WIDTH,IMG_HEIGHT,3)),
        tf.keras.layers.MaxPooling2D(pool_size=(2, 2)),         
        tf.keras.layers.Conv2D(32, (3, 3), activation="relu"),
        tf.keras.layers.MaxPooling2D(pool_size=(2, 2)),
        tf.keras.layers.Flatten(),
        tf.keras.layers.Dense(128, activation="relu"),
        tf.keras.layers.Dropout(0.5),
        tf.keras.layers.Dense(NUM_CATEGORIES, activation="softmax")
    ])

    
    model.compile(
    optimizer="adam",
    loss="categorical_crossentropy",
    metrics=["accuracy"]
    )
    return model

# run with
#  clear; python3 -u "c:\Users\SKREFI\Documents\Chestii\p\facultate\an II\ia\kaggle\main.py" . .\saved_model\
if __name__ == "__main__":
    main()