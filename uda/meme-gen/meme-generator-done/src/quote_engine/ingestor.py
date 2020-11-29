from quote_engine import parse_txt, parse_docx, parse_pdf, parse_csv


class Ingestor:
    def parse(self, file):
        if file.endswith(".txt"):
            return parse_txt(file)
        elif file.endswith(".docx"):
            return parse_docx(file)
        elif file.endswith(".pdf"):
            return parse_pdf(file)
        elif file.endswith(".csv"):
            return parse_csv(file)
        else:
            print("Invalid File Format.")
