from quote_engine import QuoteModel
from quote_engine.ingestor_interface import IngestorInterface


class TextIngestor(IngestorInterface):

    def parse(self, file):
        lines = self.get_text(file)
        list = []
        for line in lines:
            quote = line.rsplit("-", 1)
            list.append(QuoteModel(quote[0].strip(), quote[1].strip()))
        return list
    def get_text(self, file):
        file = open(file, encoding='utf-8-sig')
        lines = file.readlines()
        return lines