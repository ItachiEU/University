# databse handling source: https://www.postgresqltutorial.com/postgresql-python/connect/?fbclid=IwAR2gP6JF8jr-p4iCpue58ayJ4hKOXMl327oKwoVrDbAmxkX5IbzduqtSrj4

import psycopg2
from configparser import ConfigParser
import sys
import argparse
import json


class DB:
    def __init__(self):
        self.cur = None
        self.conn = None

    def initData(self):
        try:
            self.cur.execute(open("init.sql", "r").read())
            print('{"status":"OK"}')
        except (Exception, psycopg2.DatabaseError) as error:
            print(error)

    def commit(self):
        self.cur.execute("COMMIT;")

    def flight(self, params):
        id = params["id"]
        segments = []  # (airport, takeoff_time, landing_time)
        n = len(params["airports"])
        for i in range(n):
            seg = params["airports"][i]
            if i == 0:
                segments.append((seg["airport"], seg["takeoff_time"], None))
            elif i == n - 1:
                segments.append((seg["airport"], None, seg["landing_time"]))
            else:
                segments.append(
                    (seg["airport"], seg["takeoff_time"], seg["landing_time"]))
        n = len(segments)
        for i in range(1, n):
            try:
                self.cur.execute(
                    f"INSERT INTO Segment (flight_id, takeoff_airport_id, landing_airport_id, takeoff_time, landing_time) VALUES ({id}, '{segments[i-1][0]}', '{segments[i][0]}', '{segments[i-1][1]}'::timestamp, '{segments[i][2]}'::timestamp);")
                self.commit()
            except (Exception, psycopg2.DatabaseError) as error:
                print(error)
        print('{"status":"OK"}')

    def list_flights(self, params):
        id = params["id"]
        try:
            self.cur.execute(
                f"SELECT list_flights({id});")
            out = self.cur.fetchall()
            temp = dict()
            temp["data"] = []
            for line in out:
                line = line[0].split(',')
                line[0] = line[0][1:]
                line[-1] = line[-1].replace('"', '')
                line[-1] = line[-1][:-1]
                temp["data"].append(
                    {"rid": line[0], "from": line[1], "to": line[2], "takeoff_time": line[3]})

            temp = json.dumps(temp)
            temp = temp[0] + '"status":"OK",' + temp[1:]
            temp = json.loads(temp)
            print(json.dumps(temp, indent=4))

        except (Exception, psycopg2.DatabaseError) as error:
            print(error)

    def list_cities(self, params):
        id = params["id"]
        dist = params["dist"]
        try:
            self.cur.execute(
                f"SELECT list_cities({id}, {dist});")
            out = self.cur.fetchall()
            temp = dict()
            temp["data"] = []
            for line in out:
                line = line[0].replace('"', '')
                line = line.split(',')
                line[0] = line[0][1:]
                line[-1] = line[-1][:-1]
                temp["data"].append(
                    {"name": line[0], "prov": line[1], "country": line[2]})

            temp = json.dumps(temp)
            temp = temp[0] + '"status":"OK",' + temp[1:]
            temp = json.loads(temp)
            print(json.dumps(temp, indent=4, ensure_ascii=False))

        except (Exception, psycopg2.DatabaseError) as error:
            print(error)

    def list_airport(self, params):
        airport_id = params["iatacode"]
        n = params["n"]
        try:
            self.cur.execute(
                f"SELECT DISTINCT flight_id, takeoff_time FROM segment WHERE takeoff_airport_id='{airport_id}' ORDER BY takeoff_time DESC, flight_id ASC LIMIT {n};")

            out = self.cur.fetchall()
            temp = dict()
            temp["data"] = []
            for line in out:
                temp["data"].append(
                    {"iatacode": str(line[0]), "takeoff_time": str(line[1])})

            temp = json.dumps(temp)
            temp = temp[0] + '"status":"OK",' + temp[1:]
            temp = json.loads(temp)
            print(json.dumps(temp, indent=4, ensure_ascii=False))
        except (Exception, psycopg2.DatabaseError) as error:
            print(error)

    def list_city(self, params):  # TO DO
        name, prov, country, n, dist = params["name"], params["prov"], params["country"], params["n"], params["dist"]
        try:
            self.cur.execute(
                f"SELECT list_city('{name}', '{prov}', '{country}', {n}, {dist});")

            out = self.cur.fetchall()
            temp = dict()
            temp["data"] = []
            for line in out:
                line = line[0].replace('"', '')
                line = line.split(',')
                line[0] = line[0][1:]
                line[-1] = line[-1][:-1]
                temp["data"].append(
                    {"rid": str(line[0]), "mdist": str(line[1])})

            temp = json.dumps(temp)
            temp = temp[0] + '"status":"OK",' + temp[1:]
            temp = json.loads(temp)
            print(json.dumps(temp, indent=4, ensure_ascii=False))
        except (Exception, psycopg2.DatabaseError) as error:
            print(error)

    def config(self, filename='database.ini', section='postgresql'):
        # create a parser
        parser = ConfigParser()
        # read config file
        parser.read(filename)
        # get section, default to postgresql
        db = {}
        if parser.has_section(section):
            params = parser.items(section)
            for param in params:
                db[param[0]] = param[1]
        else:
            raise Exception(
                'Section {0} not found in the {1} file'.format(section, filename))
        return db

    def connect(self):
        """ Connect to the PostgreSQL database server """
        self.conn = None
        try:
            params = self.config()

            print('Connecting to the PostgreSQL database...')
            self.conn = psycopg2.connect(**params)
            self.cur = self.conn.cursor()

        except (Exception, psycopg2.DatabaseError) as error:
            print(error)

    def disconnect(self):
        if self.conn is not None:
            self.cur.close()
            self.conn.close()
            print('Database connection closed.')


def main():
    db = DB()
    db.connect()

    parser = argparse.ArgumentParser(description='init parse')
    parser.add_argument('--init', action='store_true')
    args = parser.parse_args()

    if args.init:
        # init db
        db.initData()
        db.disconnect()
        return 0

    for line in sys.stdin.readlines():
        js = json.loads(line)
        function = js["function"]
        params = js["params"]

        if function == "flight":
            db.flight(params)
        if function == "list_flights":
            db.list_flights(params)
        if function == "list_cities":
            db.list_cities(params)
        if function == "list_airport":
            db.list_airport(params)
        if function == "list_city":
            db.list_city(params)

    db.disconnect()


if __name__ == '__main__':
    main()
