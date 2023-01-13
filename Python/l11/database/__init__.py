from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import Table, Column, Integer, ForeignKey, String, DateTime, VARCHAR
from sqlalchemy import create_engine, MetaData
from sqlalchemy.orm import sessionmaker, validates, relationship

Base = declarative_base()

engine = create_engine("sqlite:///test.db", echo=True)
Session = sessionmaker(bind=engine)
session = Session()
