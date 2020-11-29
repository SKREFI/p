import docx

from quote_engine.ingestor_interface import IngestorInterface


class DocxIngestor(IngestorInterface):

    def parse(self, file):
        from quote_engine import QuoteModel
        lines = self.get_text(file).split("\n")
        list = []
        for line in lines:
            quote = line.rsplit("-", 1)
            list.append(QuoteModel(quote[0].strip(), quote[1].strip()))
        return list

    def get_text(self, file):
        doc = docx.Document(file)
        full_text = []
        for para in doc.paragraphs:
            if (para.text != ""):
                full_text.append(para.text)
        return '\n'.join(full_text)
