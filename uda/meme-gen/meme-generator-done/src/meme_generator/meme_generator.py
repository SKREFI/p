import os
from datetime import datetime

from PIL import Image, ImageDraw, ImageFont


font_file = "/meme_generator/novae-regular.ttf"
out_file = "_data/out/"

class MemeGenerator:

    def generate(self, img, body, author, width=500):
        image = Image.open(img)
        draw = ImageDraw.Draw(image)

        font = ImageFont.truetype(os.getcwd() + font_file, 18)

        draw.text((16, 300), body.strip() + " - " + author.strip(), (255, 255, 255), font=font)
        path = str(datetime.now()) + ".jpg"
        if not os.path.exists(out_file):
            os.makedirs(out_file)
        image.save(out_file + path)
        return path
