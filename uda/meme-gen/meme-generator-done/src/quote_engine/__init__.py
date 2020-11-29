from quote_engine.ingestors.csv_ingestor import CsvIngestor
from quote_engine.ingestors.docx_ingestor import DocxIngestor
from quote_engine.ingestors.pdf_ingestor import PdfIngestor
from quote_engine.quote_model import QuoteModel
from quote_engine.ingestors.text_ingestor import TextIngestor


def make_quote(body, author):
    return QuoteModel(body, author)

def parse_txt(file):
    return TextIngestor().parse(file)


def parse_docx(file):
    return DocxIngestor().parse(file)


def parse_pdf(file):
    return PdfIngestor().parse(file)


def parse_csv(file):
    return CsvIngestor().parse(file)
