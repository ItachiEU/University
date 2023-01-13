from database import session, create_engine, Base, sessionmaker, engine
import database.api.functions as api
from argparse import ArgumentParser


if __name__ == '__main__':
    parser = ArgumentParser('Movies database managment')
    parser.add_argument(dest='database_name', choices=[
                        'movies', 'directors', 'operators', 'producers'], help="Choose which table you want to perform action on.")
    parser.add_argument('--add', dest='add', metavar='col_1 ... col_n', nargs='*', required=False,
                        help='Add a row in the selected table.')
    parser.add_argument('--delete', dest='delete', metavar='id', type=int, required=False,
                        help='Delete a row in the selected table.')
    parser.add_argument('--update', dest='update', metavar='col_1 ... col_n',  nargs='*', required=False,
                        help='Update a column in the selected table')
    parser.add_argument('--show', dest='show',
                        required=False, help="Show contents of the selected table.", action='store_true')

    args = parser.parse_args()
    if (args.add is None and args.delete is None and args.update is None and args.show is None) \
            or sum([1 for x in [args.add, args.delete, args.show, args.update] if x]) > 1:
        raise RuntimeError("Exactly one action has to be selected.")

    Base.metadata.create_all(engine)

    if args.add:
        if args.database_name == 'movies':
            api.add_movie(*args.add)
        if args.database_name == 'directors':
            api.add_director(*args.add)
        if args.database_name == 'operators':
            api.add_operator(*args.add)
        if args.database_name == 'producers':
            api.add_producer(*args.add)

    if args.delete:
        if args.database_name == 'movies':
            api.delete_movie(args.delete)
        if args.database_name == 'directors':
            api.delete_director(args.delete)
        if args.database_name == 'operators':
            api.delete_operator(args.delete)
        if args.database_name == 'producers':
            api.delete_producer(args.delete)

    if args.update:
        if args.database_name == 'movies':
            api.update_movie(*args.update)
        if args.database_name == 'directors':
            api.update_director(*args.update)
        if args.database_name == 'operators':
            api.update_operator(*args.update)
        if args.database_name == 'producers':
            api.update_producer(*args.update)

    if args.show:
        print(api.show(args.database_name))

    session.close()
