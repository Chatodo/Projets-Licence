import csv
#Ouverture des fichiers
with open('source/rennes/network_temporal_day.csv','r') as csv_file, open('source/database/horaire_data.sql','w') as output_file:
    #Lecture du .csv
    csv_reader = csv.reader(csv_file,delimiter=';')
    #Saut de la première ligne qui sont les noms des colonnes
    next(csv_reader)
    print('loading')
    #Boucle qui écrit dans le fichier output_file tous les INSERT
    for line in csv_reader:
        stringLine = str(line)
        output_file.write("INSERT INTO horaire VALUES ("+ stringLine[1:-1] +");\n")
    print('done')
