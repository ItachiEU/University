from database import Base, Integer, Column, String, validates, ForeignKey, MetaData


class Movie(Base):
    __tablename__ = "movies"

    id = Column(Integer, primary_key=True)
    title = Column(String, nullable=False)
    production_year = Column(Integer, nullable=False)
    director_id = Column(Integer, ForeignKey("directors.id"), nullable=False)
    producer_id = Column(Integer, ForeignKey("producers.id"), nullable=False)
    operator_id = Column(Integer, ForeignKey("operators.id"), nullable=False)

    @validates("production_year")
    def validate_year(self, key, value: str):
        assert 0 < int(value) < 3000
        return value
