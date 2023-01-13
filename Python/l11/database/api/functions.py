from database.definitions import Movie, Director, Operator, Producer
from database import session, engine
import pandas as pd


def add_movie(id: int, title: str, production_year: int, director_id: int, producer_id: int, operator_id: int) -> None:
    movie = Movie(id=id, title=title, production_year=production_year, director_id=director_id,
                  producer_id=producer_id, operator_id=operator_id)
    session.add(movie)
    session.commit()


def add_director(id: int, first_name: str, last_name: str):
    director = Director(id=id, first_name=first_name,
                        last_name=last_name)
    session.add(director)
    session.commit()


def add_operator(id: int, first_name: str, last_name: str):
    operator = Operator(id=id, first_name=first_name, last_name=last_name)
    session.add(operator)
    session.commit()


def add_producer(id: int, first_name: str, last_name: str):
    producer = Producer(id=id, first_name=first_name, last_name=last_name)
    session.add(producer)
    session.commit()


def delete_movie(id: int):
    movie = session.query(Movie).filter(Movie.id == id).scalar()
    if movie:
        session.delete(movie)
        session.commit()


def delete_director(id: int):
    director = session.query(Director).filter(Director.id == id).scalar()
    if director:
        session.delete(director)
        session.commit()


def delete_operator(id: int):
    operator = session.query(Operator).filter(Operator.id == id).scalar()
    if operator:
        session.delete(operator)
        session.commit()


def delete_producer(id: int):
    producer = session.query(Producer).filter(Producer.id == id).scalar()
    if producer:
        session.delete(producer)
        session.commit()


# Na update nie starczyło mi czasu
def update_operator():
    pass


def update_producer():
    pass


def update_movie():
    pass


def update_director():
    pass


def show(table_name: str) -> pd.DataFrame:
    return pd.read_sql_table(table_name=table_name, con=engine)
