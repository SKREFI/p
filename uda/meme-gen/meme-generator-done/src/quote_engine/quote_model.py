class QuoteModel:

    def __init__(self, body, author):
        self.body = body
        self.author = author

    def __repr__(self):
        return self.body + " - " + self.author

    def __str__(self):
        return self.body + " - " + self.author
