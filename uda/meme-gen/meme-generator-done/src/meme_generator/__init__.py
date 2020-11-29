from meme_generator.meme_generator import MemeGenerator


def make_meme(img_path, body, author, width=500):
    return MemeGenerator().generate(img_path, body, author, width)
