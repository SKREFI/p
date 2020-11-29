
from subprocess import Popen, PIPE

from quote_engine.ingestor_interface import IngestorInterface

class PdfIngestor(IngestorInterface):

    def parse(self, file):
        from quote_engine import QuoteModel
        lines = self.get_text(file)
        list = []
        for line in lines:
            quote = line.rsplit("-", 1)
            list.append(QuoteModel(quote[0].strip(), quote[1].strip()))
        return list

    def get_text(self, file):
        with open(file, "rb") as f:
            text = Popen(['pdftotext', file, '-'], stdout=PIPE).communicate()[0]
            list = text.decode().strip().split('\n')
        return list
