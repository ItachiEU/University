from database import Base, Integer, Column, String, validates, ForeignKey, relationship, MetaData


class Producer(Base):
    __tablename__ = "producers"

    id = Column(Integer, primary_key=True)
    first_name = Column(String, nullable=False)
    last_name = Column(String, nullable=False)
    movies = relationship("Movie")

    @validates("last_name")
    def validate_last_name(self, key, value: str):
        assert value.istitle
        return value