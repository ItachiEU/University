import datetime
import pprint as pp

from typing import DefaultDict
from collections import defaultdict

start_date = datetime.date(1601, 1, 1)
end_date = datetime.date(2000, 12, 31)
delta = datetime.timedelta(days=1)

week_days = ["Monday", "Tuesday", "Wednesday",
             "Thursday", "Friday", "Saturday", "Sunday"]

day_counter = defaultdict(int)

while start_date <= end_date:
    if start_date.day == 13:
        day_counter[week_days[start_date.weekday()]] += 1
    start_date += delta

pp.pprint(day_counter)
