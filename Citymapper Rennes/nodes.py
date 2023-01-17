f = open("source/rennes/network_nodes.csv", 'r')
#On saute la 1er ligne car c'est pas les valeurs
next(f)
#Fichier de destination
r = open("source/database/nodes_data.sql",'w+')

#loop over each line of the input file
for line in f:
	#break line into an array of attributes separated by ';'
	r.write("INSERT INTO nodes VALUES(")
	items = line.rstrip("\n").split(";") 

	i = 0

	#loop over each attribute in the array items
	for item in items:

		#replace ' with '', for strings in postgreSQL
		item = item.replace("'", "''")

		if i < 3:
			r.write("\'%s \'," %item)
		else:
			r.write("\'%s\'" %item)
		#print the attribute position in array and its value
		i = i + 1
	r.write(");\n")

f.close()
r.close()