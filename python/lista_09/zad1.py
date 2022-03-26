from sqlalchemy import create_engine
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import relationship
from sqlalchemy.orm.session import Session, sessionmaker
from sqlalchemy.sql.schema import Column, ForeignKey
from sqlalchemy.sql.sqltypes import Integer, String

Base = declarative_base()

class Book(Base):
  __tablename__ = 'Book'

  id = Column(Integer, primary_key=True)
  title = Column(String(100), nullable=False)
  author = Column(String(100), nullable=False)
  year = Column(Integer, nullable=False)
  borrower = Column(Integer, ForeignKey('Person.id'))
  

class Person(Base):
  __tablename__ = 'Person'

  id = Column(Integer, primary_key=True)
  name = Column(String(50), nullable=False)
  email = Column(String(100), nullable=False)
  books = relationship('Book')

engine = create_engine('sqlite:///movies.db')
Base.metadata.create_all(engine)

Session = sessionmaker(bind=engine)
session = Session()

def add_person(name, email):
  person = Person(name=name, email=email)

  session.add(person)
  session.commit()

def add_book(title, author, year):
  book = Book(title=title, author=author, year=year)

  session.add(book)
  session.commit()

def borrow_book(person_id, book_id):
  book = session.query(Book).get(book_id)
  person = session.query(Person).get(person_id)

  if not book or not person:
    return False

  if book.borrower != None:
    return False

  person.books.append(book)
  session.add(person)
  session.commit()

  return True
  
def return_book(person_id, book_id):
  book = session.query(Book).get(book_id)
  person = session.query(Person).get(person_id)

  if not book or not person:
    return False

  if book.borrower != person.id:
    return False

  book.borrower = None
  person.books = [book for book in person.books if book.id != book_id]
  session.add(person)
  session.commit()

  return True
