import pandas

from quote_engine.ingestor_interface import IngestorInterface


class CsvIngestor(IngestorInterface):

    def parse(self, file):
        from quote_engine import QuoteModel
        lines = self.get_text(file)
        list = []
        for line in lines:
            quote = line.rsplit("-", 1)
            list.append(QuoteModel(quote[0].strip(), quote[1].strip()))
        return list

    def get_text(self, file):
        df = pandas.read_csv(file, sep=",", header=0)
        list = []
        for index, row in df.iterrows():
            list.append(row['body'] + "-" + row['author'])
        return list
