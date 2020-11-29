## The MemeEngine class

###### The class is responsible for:

* loading an image using Pillow (PIL)
* resizing the image so the width is at most 500px and the height is scaled proportionally
* add a quote body and a quote author to the image
* saving the manipulated image
* the class must implement this instance method signature which returns the path to the manipulated image make_meme(self, img_path, text, author, width=500) -> str

### Meme Engine Module

The Meme Engine Module is responsible for manipulating and drawing text onto images. It will reinforce your understanding of object-oriented thinking while demonstrating your skill using a more advanced third party library for image manipulation.

### How to Use this Module

```path = make_meme(img, quote.body, quote.author)```

`path` here will contain the path to generated image