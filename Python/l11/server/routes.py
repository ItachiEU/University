from fastapi import APIRouter
from enum import Enum
from pydantic import BaseModel

from database.api.functions import add_director, add_movie, add_operator, add_producer, delete_director, delete_movie, delete_operator, delete_producer, show


router = APIRouter(
    prefix="/api",
    tags=["database_calls"],
    responses={404: {"description": "Not found"}},
)


class TableName(str, Enum):
    movies = "movies"
    directors = "directors"
    operators = "operators"
    producers = "producers"


class Movie(BaseModel):
    id: int
    title: str
    production_year: int
    director_id: int
    producer_id: int
    operator_id: int


class Person(BaseModel):
    id: int
    first_name: str
    last_name: str


@router.post('/movie')
def post_movie(movie: Movie):
    add_movie(movie.id, movie.title, movie.production_year,
              movie.director_id, movie.producer_id, movie.operator_id)
    return {"message": f"Added {movie} to the database"}


@router.post('/director')
def post_director(director: Person):
    add_director(director.id, director.first_name, director.last_name)
    return {"message": f"Added {director} to the database"}


@router.post('/operator')
def post_operator(operator: Person):
    add_operator(operator.id, operator.first_name, operator.last_name)
    return {"message": f"Added {operator} to the database"}


@router.post('/producer')
def post_producer(producer: Person):
    add_producer(producer.id, producer.first_name, producer.last_name)
    return {"message": f"Added {producer} to the database"}


@router.delete('/movie/{movie_id}')
def del_movie(movie_id: int):
    delete_movie(movie_id)
    return {"message": f"Deleted movie {movie_id} from the database"}


@router.delete('/director/{director_id}')
def del_director(director_id: int):
    delete_director(director_id)
    return {"message": f"Deleted director {director_id} from the database"}


@router.delete('/operator/{operator_id}')
def del_operator(operator_id: int):
    delete_operator(operator_id)
    return {"message": f"Deleted operator {operator_id} from the database"}


@router.delete('/producer/{producer_id}')
def del_producer(producer_id: int):
    delete_producer(producer_id)
    return {"message": f"Deleted producer {producer_id} from the database"}


@router.get('/show/{table_name}')
def show_table_contents(table_name: TableName):
    return show(table_name.value).to_json(orient="records")
