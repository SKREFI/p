import os
import random
import shutil

import requests
from flask import Flask, render_template, url_for, request

# @TODO Import your Ingestor and MemeEngine classes
from meme_generator import make_meme
from quote_engine import make_quote
from quote_engine.ingestor import Ingestor
from quote_engine.ingestor_interface import IngestorInterface

app = Flask(__name__)
app.static_folder = "./_data"


def setup():
    """ Load all resources """

    quote_files = ['./_data/DogQuotes/DogQuotesTXT.txt',
                   './_data/DogQuotes/DogQuotesDOCX.docx',
                   './_data/DogQuotes/DogQuotesPDF.pdf',
                   './_data/DogQuotes/DogQuotesCSV.csv']
    quotes = []

    for file in quote_files:
        if IngestorInterface.can_ingest(file):
            quotes.extend(Ingestor().parse(file))

    images = "./_data/photos/dog/"
    imgs = []
    for root, dirs, files in os.walk(images):
        imgs = [os.path.join(root, name) for name in files]

    return quotes, imgs


quotes, imgs = setup()


@app.route('/')
def meme_rand():
    """ Generate a random meme """

    img = random.choice(imgs)

    quote = random.choice(quotes)

    path = make_meme(img, quote.body, quote.author)
    path = url_for('static', filename="out/" + path)
    return render_template('meme.html', path=path)


@app.route('/create', methods=['GET'])
def meme_form():
    """ User input for meme information """
    return render_template('meme_form.html')


@app.route('/create', methods=['POST'])
def meme_post():
    """ Create a user defined meme """

    url = request.form['image_url']
    body = request.form['body']
    author = request.form['author']

    response = requests.get(url, stream=True)

    with open('img.png', 'wb') as out_file:
        shutil.copyfileobj(response.raw, out_file)
    del response

    path = make_meme("img.png", body, author)
    path = url_for('static', filename="out/" + path)
    os.remove("img.png")

    return render_template('meme.html', path=path)


if __name__ == "__main__":
    app.run()
