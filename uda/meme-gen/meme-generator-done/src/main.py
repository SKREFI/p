import argparse
import os
import random
from PIL import Image

from src.meme_generator import make_meme
from src.quote_engine.ingestor import Ingestor
from src.quote_engine.ingestor_interface import IngestorInterface
from src.quote_engine.quote_model import QuoteModel


def generate_meme(path=None, body=None, author=None):
    """ Generate a meme given an path and a quote """

    if path is None:
        images = "./_data/photos/dog/"
        imgs = []
        for root, dirs, files in os.walk(images):
            imgs = [os.path.join(root, name) for name in files]

        img = random.choice(imgs)

    else:
        img = path
    print(img)
    if body is None:
        quote_files = ['./_data/DogQuotes/DogQuotesTXT.txt',
                       './_data/DogQuotes/DogQuotesDOCX.docx',
                       './_data/DogQuotes/DogQuotesPDF.pdf',
                       './_data/DogQuotes/DogQuotesCSV.csv']
        quotes = []

        for file in quote_files:
            if (IngestorInterface.can_ingest(file)):
                quotes.extend(Ingestor().parse(file))

        quote = random.choice(quotes)

    else:
        if author is None:
            raise Exception('Author Required if Body is Used')
        quote = QuoteModel(body, author)

    path = make_meme(img, quote.body, quote.author)
    path = os.getcwd() + "/_data/out/" + path
    image = Image.open(path)
    image.show()
    return path, quote.body, quote.author


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Meme Argument Parser')
    parser.add_argument("--path")
    parser.add_argument("--body")
    parser.add_argument("--author")
    args = parser.parse_args()

    print(generate_meme(args.path, args.body, args.author))
