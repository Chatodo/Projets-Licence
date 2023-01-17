import csv

# importing the module
import csv
from datetime import datetime

# creating empty lists
temps_arr = []
temps_fin = []

# open the file in read mode
with open('citymapper/source/rennes/network_temporal_week.csv','r') as csv_file, open('citymapper/source/database/dateunix.csv','w') as output_file:
    csv_reader = csv.reader(csv_file,delimiter=';')
    next(csv_reader)
    print('Raven bg ')
    for line in csv_reader:
    	print(datetime.utcfromtimestamp(int(line[2])).strftime('%H:%M:%S'))
        print(datetime.utcfromtimestamp(int(line[3])).strftime('%H:%M:%S'))
#ts = int('')

# if you encounter a "year is out of range" error the timestamp
# may be in milliseconds, try `ts /= 1000` in that case
#print(datetime.utcfromtimestamp(ts).strftime('%H:%M:%S'))
