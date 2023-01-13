from fastapi import FastAPI
from server.routes import router

app = FastAPI()

app.include_router(router)


@app.get("/")
def root():
    return {"message": "Welcome to the database API!"}
