#### Ingestors

An abstract base class, `IngestorInterface` defines two methods with the following class method signatures:

```python3
def can_ingest(cls, path) -> boolean
def parse(cls, path: str) -> List[QuoteModel]
```

Separate strategy objects realizes `IngestorInterface` for each file type (csv, docx, pdf, txt).

A final `Ingestor` class realizes the `IngestorInterface` abstract base class and encapsulates helper classes. It implements logic to select the appropriate helper for a given file based on filetype.

### Quote Engine Module

The Quote Engine Module is responsible for ingesting many types of files that contain quotes. A quote contains a body and an author (e.g. "this is a quote body" - Author). This module will be composed of many classes and demonstrate your understanding of complex inheritance, abstract classes, classmethods, strategy objects, and other fundamental programming principles. The responsibility of this module is to load and parse quotes from files.

### How to Use this Module

```
if IngestorInterface.can_ingest(file):
    quotes.extend(Ingestor().parse(file))
```
`quotes` here is a list that contain all the quotes loaded from different files. 