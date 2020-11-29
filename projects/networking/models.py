class Source():
    def __init__(self, **d):
        self.id = d.get('id')
        self.name = d.get('name')

    def __repr__(self):
        return f'Source {self.id} --> {self.name}'


class Articles():
    def __init__(self, **d):
        self.source = Source(**d.get('source'))
        self.author = d.get('author')
        self.title = d.get('title')
        self.url = d.get('url')
        self.urlToImage = d.get('urlToImage')


class Response():
    def __init__(self, **d):
        self.status = d.get('status')
        self.totalResults = d.get('totalResults')
        self.articles = [Articles(**x) for x in d.get('articles')]
