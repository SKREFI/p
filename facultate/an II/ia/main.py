# import the shit
import numpy as np
import matplotlib.pyplot as plt
from sklearn.naive_bayes import MultinomialNB

# gether the data from the files
train_images = np.loadtxt("lab2data/train_images.txt")
train_labels = np.loadtxt("lab2data/train_labels.txt").astype(int)
test_images = np.loadtxt("lab2data/test_images.txt")
test_labels = np.loadtxt("lab2data/test_labels.txt").astype(int)


class KNNClassifier:
    def __init__(self, train_images, train_labels):
        self.train_images = train_images
        self.train_labels = train_labels

    def classify_image(self, test_image, num_neighbors=15, metric="l2"):
        if metric == "l2":
            # train_images - test_image = weights
            distances = np.sum((train_images - test_image) ** 2, axis=-1)
        elif metric == "l1":
            distances = np.sum(np.abs(train_images - test_image), axis=-1)

        sorted_indexes = np.argsort(distances)
        print("Sorted indexes:", sorted_indexes)

        top_neighbors = self.train_labels[sorted_indexes[:num_neighbors]]
        print("Top neighbors:", top_neighbors)

        class_counts = np.bincount(top_neighbors)
        print("Class counts:", class_counts)

        return np.argmax(class_counts)


clf = KNNClassifier(train_images, train_labels)
print("Predicted class:", clf.classify_image(train_images[0]))

exit()

predictions = []
for test_image in test_images:
    pred_label = clf.classify_image(test_image)
    predictions.append(pred_label)

pred_labels = np.array(predictions)

np.savetxt("predictii_3nn_l2_mnist.txt", pred_labels)

correct_count = np.sum(pred_labels == test_labels)
total_count = len(test_labels)

accuracy = correct_count / total_count

print(f"Accuracy: {accuracy * 100}%")

ks = [1, 3, 5, 7, 9]


def compute_accuracy(metric):
    accuracies = []

    for k in ks:
        correct_count = 0
        for test_image, test_label in zip(test_images, test_labels):
            pred_label = clf.classify_image(test_image, num_neighbors=k, metric=metric)
            if pred_label == test_label:
                correct_count += 1

        accuracy = correct_count / len(test_images)

        accuracies.append(accuracy)

    np.savetxt(f"acuratete_{metric}.txt", np.array(accuracies))


compute_accuracy("l2")
compute_accuracy("l1")

l2_accs = np.loadtxt("acuratete_l2.txt")
l1_accs = np.loadtxt("acuratete_l1.txt")

plt.plot(l2_accs, label="L2")
plt.plot(l1_accs, label="L1")

plt.show()

print("Done")
