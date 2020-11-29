from abc import ABC, abstractmethod


class IngestorInterface(ABC):

    @classmethod
    def can_ingest(cls, file):
        if (file.endswith(".txt") or file.endswith(".docx")
                or file.endswith(".pdf") or file.endswith(".csv")):
            return True
        else:
            raise Exception("Invalid File Format.")

    @abstractmethod
    def parse(self, file):
        pass
