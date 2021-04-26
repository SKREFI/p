import cv2
import tensorflow as tf
import numpy as np
import os
import sys

IMG_SIZE = 32


class Image:
    def __init__(self, name, array, label=-1):
        self.name = name
        self.array = array
        self.label = label

    def __repr__(self):
        return f"{self.name},{self.label}"


def prepare_image(filepath):
    img_array = cv2.imread(filepath)
    new_array = cv2.resize(img_array, (IMG_SIZE, IMG_SIZE))
    return new_array.reshape(-1, IMG_SIZE, IMG_SIZE, 3)


def load_images(text_file):
    image_names = []
    with open(text_file, "r") as file:
        for line in file:
            image_names.append(line.strip())
    images = []
    for name in image_names:
        images.append(Image(name, prepare_image(os.path.join("test/", name))))
    return images


# run me with: python3 saved_model
if __name__ == "__main__":
    # load the data and the model
    images = load_images("test.txt")
    model = tf.keras.models.load_model(sys.argv[1])

    with open("results.txt", "w") as file:
        file.write("id,label\n")  # first line, csv style
        for i in range(len(images)):
            file.write(f"{images[i].name},{np.argmax([model.predict(images[i].array)], axis=-1)[0][0]}\n")
