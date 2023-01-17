import csv
#Ouverture des fichiers
with open('source/rennes/network_combined.csv','r') as csv_file, open('source/rennes/nom_ligne.csv','r') as route_file, open('source/database/transport_data.sql','w') as output_file:
    #Lecture des fichiers
    csv_reader = csv.reader(csv_file,delimiter=';')
    dict_reader = csv.reader(route_file,delimiter=';')
    #Dictionnaire qui a pour clé les identifiant des routes et pour valeurs les lignes de bus ou de métro
    d={}
    for line in dict_reader:
        d[line[0]]=line[1]
    #Saut de la première ligne qui sont les noms des colonnes
    next(csv_reader)
    print('loading')
    #Boucle qui écrit dans le fichier output_file tous les INSERT et si une ligne a plusieurs routes, la boucle les sépare en plusieurs lignes
    for line in csv_reader:
        line[3]=str(round(float(line[3])))
        route= line[5]
        tab=[route.split(",")[i].split(":")[0] for i in range(len(route.split(",")))]
        for i in tab:
            line[4]=d[i]
            stringLine= str(line[:-2])
            output_file.write("INSERT INTO transport VALUES ("+ stringLine[1:-1] +");\n")
    print('done')
