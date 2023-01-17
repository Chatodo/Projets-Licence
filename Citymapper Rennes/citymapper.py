import folium, io, json, sys, math
import psycopg2
from jinja2 import Template
from branca.element import Element
from PyQt5.QtWebEngineWidgets import QWebEngineView, QWebEnginePage
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
#Permet d'avoir l'heure de l'ordinateur
from datetime import datetime

#Variable global pour filter selon les choix
train = 1
bus = 1

class MainWindow(QMainWindow):
    #Initialisation de l'interface de la fenêtre
    def __init__(self):
        super().__init__()

        self.resize(1000, 1000)

        main = QWidget()
        self.setCentralWidget(main)
        main.setLayout(QVBoxLayout())
        main.setFocusPolicy(Qt.StrongFocus)

        self.tableWidget = QTableWidget()
        self.rows = []

        self.webView = myWebView()

        controls_panel = QHBoxLayout()
        controls_choix = QHBoxLayout()
        controls_heure = QHBoxLayout()
        mysplit = QSplitter(Qt.Vertical)
        mysplit.addWidget(self.tableWidget)
        mysplit.addWidget(self.webView)

        main.layout().addLayout(controls_panel)
        main.layout().addLayout(controls_choix)
        main.layout().addLayout(controls_heure)
        main.layout().addWidget(mysplit)

        _label = QLabel('From: ', self)
        _label.setFixedSize(30,20)
        self.from_box = QComboBox()
        self.from_box.setEditable(True)
        self.from_box.completer().setCompletionMode(QCompleter.PopupCompletion)
        self.from_box.setInsertPolicy(QComboBox.NoInsert)
        controls_panel.addWidget(_label)
        controls_panel.addWidget(self.from_box)

        _label = QLabel('  To: ', self)
        _label.setFixedSize(20,20)
        self.to_box = QComboBox()
        self.to_box.setEditable(True)
        self.to_box.completer().setCompletionMode(QCompleter.PopupCompletion)
        self.to_box.setInsertPolicy(QComboBox.NoInsert)
        controls_panel.addWidget(_label)
        controls_panel.addWidget(self.to_box)

        _label = QLabel('Hops: ', self)
        _label.setFixedSize(20,20)
        self.hop_box = QComboBox()
        self.hop_box.addItems( ['1', '2', '3'] )
        self.hop_box.setCurrentIndex( 2 )
        controls_panel.addWidget(_label)
        controls_panel.addWidget(self.hop_box)

        self.go_button = QPushButton("Go!")
        self.go_button.clicked.connect(self.button_Go)
        controls_panel.addWidget(self.go_button)

        self.clear_button = QPushButton("Clear")
        self.clear_button.clicked.connect(self.button_Clear)
        controls_panel.addWidget(self.clear_button)

        #Pour pouvoir filter les résultats
        controls_choix.setSpacing(0)
        self.bus = QCheckBox("Bus")
        self.bus.setChecked(True)
        controls_choix.addWidget(self.bus)
        self.metro = QCheckBox("Metro")
        self.metro.setChecked(True)
        controls_choix.addWidget(self.metro)
        controls_choix.addStretch(1)

        #Pour afficher les prochains horraires
        controls_heure.setSpacing(0)
        _label = QLabel('Prochain Depart pour : ', self)
        _label.setFixedSize(150,20)
        self.choix_stat = QComboBox()
        self.choix_stat.setEditable(True)
        self.choix_stat.completer().setCompletionMode(QCompleter.PopupCompletion)
        self.choix_stat.setInsertPolicy(QComboBox.NoInsert)
        controls_heure.addWidget(_label)
        controls_heure.addWidget(self.choix_stat)
        self.go_heure_button = QPushButton("Go!")
        self.go_heure_button.clicked.connect(self.button_go_horaire)
        controls_heure.addWidget(self.go_heure_button)

        self.maptype_box = QComboBox()
        self.maptype_box.addItems(self.webView.maptypes)
        self.maptype_box.currentIndexChanged.connect(self.webView.setMap)
        controls_panel.addWidget(self.maptype_box)

        self.connect_DB()

        self.startingpoint = True

        self.show()

    #Connexion à la base de données
    def connect_DB(self):
        self.conn = psycopg2.connect(database="", user="", host="10.11.11.22", password="")
        self.cursor = self.conn.cursor()
        #Requête pour sélectionner toutes les stations
        self.cursor.execute("""SELECT id, name FROM nodes ORDER BY name""")
        self.conn.commit()
        rows = self.cursor.fetchall()
        #Ajoute tous les noms de stations sur le from_box et le to_box
        for row in rows :
            self.from_box.addItem(str(row[1])+" Station "+str(row[0]))
            self.to_box.addItem(str(row[1])+" Station "+str(row[0]))
            self.choix_stat.addItem(str(row[1])+" Station "+str(row[0]))



    #Fonction qui se lance quand on clique sur le bouton go
    def button_Go(self):
        self.tableWidget.clearContents()
        #Récupère l'id de la station qui a été mis dans from_box
        _fromstation = str(self.from_box.currentText()).split(" ")[-1:][0]
        #Récupère l'id de la station qui a été mis dans to_box
        _tostation = str(self.to_box.currentText()).split(" ")[-1:][0]
        #Récupère le chiffre sélectionné dans hop_box
        _hops = int(self.hop_box.currentText())
        #Ajoute un marqueur sur la carte pour _fromstation
        self.cursor.execute(""f" SELECT lati,lon FROM nodes WHERE id = {_fromstation} """)
        self.conn.commit()
        fr = self.cursor.fetchall()
        self.webView.addMarker(fr[0][0], fr[0][1])
        #Ajoute un marqueur sur la carte pour _tostation
        self.cursor.execute(""f" SELECT lati,lon FROM nodes WHERE id = {_tostation} """)
        self.conn.commit()
        to = self.cursor.fetchall()
        self.webView.addMarker(to[0][0], to[0][1])

        self.rows = []
        #Exécute les requetes pour avoir les chemins entre deux stations en fonction du _hops
        if _hops >= 1 :
            self.cursor.execute(""f"\
            WITH transport_s(id_from,station_f,id_stop,station_s,name_line,temps) as(\
              SELECT id_from,n1.name,id_stop,n2.name,name_line,travel_time\
              FROM transport,nodes as n1,nodes as n2\
              WHERE id_from=n1.id and id_stop=n2.id)\
            SELECT a.station_f,a.name_line,b.station_s,(CONCAT(A.temps,'s')) as temps_tot\
            FROM transport_s as a, transport_s AS b\
            WHERE a.id_from = $${_fromstation}$$ AND b.id_stop = $${_tostation}$$ and a.name_line = b.name_line\
            ORDER BY temps_tot""")
            self.conn.commit()
            self.rows += self.cursor.fetchall()
        if _hops >= 2 :
            self.cursor.execute(""f"\
            WITH transport_s(id_from,station_f,id_stop,station_s,name_line,temps) as(\
              SELECT id_from,n1.name,id_stop,n2.name,name_line,travel_time\
              FROM transport,nodes as n1,nodes as n2\
              WHERE id_from=n1.id and id_stop=n2.id)\
            SELECT A.station_f, A.name_line, B.station_s, C.name_line, D.station_s, (CONCAT(A.temps + B.temps,'s')) as temps_tot\
            FROM transport_s as A, transport_s as B, transport_s as C, transport_s as D\
            WHERE A.id_from = $${_fromstation}$$ AND D.id_stop = $${_tostation}$$ AND A.name_line = B.name_line AND B.id_stop = C.id_from AND C.name_line = D.name_line AND A.name_line <> C.name_line AND A.id_stop <> B.id_from AND B.id_from <> D.id_stop\
            ORDER BY temps_tot;""")
            self.conn.commit()
            self.rows += self.cursor.fetchall()

        if _hops >= 3 :
            self.cursor.execute(""f"\
            WITH transport_s(id_from,station_f,id_stop,station_s,name_line,temps) as(\
            SELECT id_from,n1.name,id_stop,n2.name,name_line,travel_time\
            FROM transport,nodes as n1,nodes as n2\
            WHERE id_from=n1.id and id_stop=n2.id)\
            SELECT A.station_f, A.name_line, B2.station_s, B2.name_line, C2.station_s, C2.name_line, D.station_s, (CONCAT(A.temps + B2.temps + C2.temps,'s')) as temps_tot\
            FROM transport_s as A, transport_s as B1, transport_s as B2, transport_s as C1, transport_s as C2, transport_s as D\
            WHERE A.id_from = $${_fromstation}$$ AND D.id_stop = $${_tostation}$$ AND A.name_line = B1.name_line AND B1.id_stop = B2.id_from AND B2.name_line = C1.name_line AND C1.id_stop = C2.id_from AND C2.name_line = D.name_line AND A.name_line <> B2.name_line AND B2.name_line <> C2.name_line AND A.name_line <> C2.name_line AND A.id_from <> B1.id_stop AND B2.id_from <> C1.id_stop AND C2.id_from <> D.id_stop\
            ORDER BY temps_tot;""")
            self.conn.commit()
            self.rows += self.cursor.fetchall()

        if len(self.rows) == 0 :
            self.tableWidget.setRowCount(0)
            self.tableWidget.setColumnCount(0)
            return
        #Initialise un tableau
        numrows = len(self.rows)
        numcols = len(self.rows[-1])
        self.tableWidget.setRowCount(numrows)
        self.tableWidget.setColumnCount(numcols)
        #Remplissage du tableau avec les données
        i = 0
        for row in self.rows :
            j = 0
            check= False
            if len(row)== 4:
                if 'a' in row[1] and self.metro.isChecked():
                    check = True
                if 'a' not in row[1] and self.bus.isChecked():
                    check = True
            if len(row)== 6:
                if 'a' in row[1] and 'a' in row[3] and self.metro.isChecked():
                    check = True
                if 'a' not in row[1] and 'a' not in row[3] and self.bus.isChecked():
                    check = True
            if len(row)== 8:
                if 'a' in row[1] and 'a' in row[3] and 'a' in row[5] and self.metro.isChecked():
                    check = True
                if 'a' not in row[1] and 'a' not in row[3] and 'a' not in row[5] and self.bus.isChecked():
                    check = True
            if check:
                for col in row :
                    self.tableWidget.setItem(i, j, QTableWidgetItem(str(col)))
                    j = j + 1
            i = i + 1

        header = self.tableWidget.horizontalHeader()
        j = 0
        while j < numcols :
            header.setSectionResizeMode(j, QHeaderView.ResizeToContents)
            j = j+1

        self.update()

    #Fonction (qui ne marche pas) qui affiche les prochains départs de la station
    def button_go_horaire(self):
        self.tableWidget.clearContents()

        _fromstation = str(self.choix_stat.currentText()).split(" ")[-1:][0]
        self.cursor.execute(""f" SELECT lati,lon FROM nodes WHERE id = {_fromstation} """)
        self.conn.commit()
        fr = self.cursor.fetchall()
        self.webView.addMarker(fr[0][0], fr[0][1])
        _horaire_tmp = datetime.now()
        _horaire = _horaire_tmp.strftime("%HH%M")
        self.rows = []
        '''self.cursor.execute(""f"SELECT id_stop, arrive\
        FROM horaire NATURAL JOIN transport \
        WHERE id_from = $${_fromstation}$$ AND arrive > $${_horaire}$$;""")
        self.conn.commit()
        self.rows += self.cursor.fetchall()

        if len(self.rows) == 0 :
            self.tableWidget.setRowCount(0)
            self.tableWidget.setColumnCount(0)
            return
        numrows = len(self.rows)
        numcols = len(self.rows[-1])
        self.tableWidget.setRowCount(numrows)
        self.tableWidget.setColumnCount(numcols)

        i = 0
        #on veut afficher que les 10 resultats sinon c'est trop long
        for row in self.rows[10] :
            j = 0
            for col in row :
                self.tableWidget.setItem(i, j, QTableWidgetItem(str(col)))
                j = j + 1
            i = i + 1

        header = self.tableWidget.horizontalHeader()
        j = 0
        while j < numcols :
            header.setSectionResizeMode(j, QHeaderView.ResizeToContents)
            j = j+1

        self.update()

'''

    def button_Clear(self):
        self.webView.clearMap(self.maptype_box.currentIndex())
        self.startingpoint = True
        self.update()

    #Affiche la station la plus proche
    def mouseClick(self, lat, lng):
        self.webView.addPointMarker(lat, lng)

        print(f"Clicked on: latitude {lat}, longitude {lng}")
        self.cursor.execute(""f" WITH click (distance, nom)\
        AS (SELECT ( ABS(lati-{lat}) + ABS(lon+{abs(lng)}) ), name FROM nodes)\
        SELECT A.nom FROM click as A WHERE A.distance <=  (SELECT min(B.distance)\
        FROM click as B)""")
        self.conn.commit()

        rows = self.cursor.fetchall()
        #print('Closest STATION is: ', rows[0][0])
        #Comme notre tableau n'est pas de la même forme que celui du TP, Qt.MatchFixedString retourne toujours -1
        if self.startingpoint :
            self.from_box.setCurrentIndex(self.from_box.findText(rows[0][0], Qt.MatchStartsWith))
        else :
            self.to_box.setCurrentIndex(self.to_box.findText(rows[0][0], Qt.MatchStartsWith))
        self.startingpoint = not self.startingpoint



class myWebView (QWebEngineView):
    def __init__(self):
        super().__init__()

        self.maptypes = ["OpenStreetMap", "Stamen Terrain", "stamentoner", "cartodbpositron"]
        self.setMap(0)


    def add_customjs(self, map_object):
        my_js = f"""{map_object.get_name()}.on("click",
                 function (e) {{
                    var data = `{{"coordinates": ${{JSON.stringify(e.latlng)}}}}`;
                    console.log(data)}}); """
        e = Element(my_js)
        html = map_object.get_root()
        html.script.get_root().render()
        html.script._children[e.get_name()] = e

        return map_object


    def handleClick(self, msg):
        data = json.loads(msg)
        lat = data['coordinates']['lat']
        lng = data['coordinates']['lng']


        window.mouseClick(lat, lng)


    def addSegment(self, lat1, lng1, lat2, lng2):
        js = Template(
        """
        L.polyline(
            [ [{{latitude1}}, {{longitude1}}], [{{latitude2}}, {{longitude2}}] ], {
                "color": "red",
                "opacity": 1.0,
                "weight": 4,
                "line_cap": "butt"
            }
        ).addTo({{map}});
        """
        ).render(map=self.mymap.get_name(), latitude1=lat1, longitude1=lng1, latitude2=lat2, longitude2=lng2 )

        self.page().runJavaScript(js)


    def addMarker(self, lat, lng):
        js = Template(
        """
        L.marker([{{latitude}}, {{longitude}}] ).addTo({{map}});
        L.circleMarker(
            [{{latitude}}, {{longitude}}], {
                "bubblingMouseEvents": true,
                "color": "#3388ff",
                "popup": "hello",
                "dashArray": null,
                "dashOffset": null,
                "fill": false,
                "fillColor": "#3388ff",
                "fillOpacity": 0.2,
                "fillRule": "evenodd",
                "lineCap": "round",
                "lineJoin": "round",
                "opacity": 1.0,
                "radius": 2,
                "stroke": true,
                "weight": 5
            }
        ).addTo({{map}});
        """
        ).render(map=self.mymap.get_name(), latitude=lat, longitude=lng)
        self.page().runJavaScript(js)


    def addPointMarker(self, lat, lng):
        js = Template(
        """
        L.circleMarker(
            [{{latitude}}, {{longitude}}], {
                "bubblingMouseEvents": true,
                "color": 'green',
                "popup": "hello",
                "dashArray": null,
                "dashOffset": null,
                "fill": false,
                "fillColor": 'green',
                "fillOpacity": 0.2,
                "fillRule": "evenodd",
                "lineCap": "round",
                "lineJoin": "round",
                "opacity": 1.0,
                "radius": 2,
                "stroke": true,
                "weight": 5
            }
        ).addTo({{map}});
        """
        ).render(map=self.mymap.get_name(), latitude=lat, longitude=lng)
        self.page().runJavaScript(js)


    def setMap (self, i):
        self.mymap = folium.Map(location=[48.1172, -1.6777], tiles=self.maptypes[i], zoom_start=12, prefer_canvas=True)

        self.mymap = self.add_customjs(self.mymap)

        page = WebEnginePage(self)
        self.setPage(page)

        data = io.BytesIO()
        self.mymap.save(data, close_file=False)

        self.setHtml(data.getvalue().decode())

    def clearMap(self, index):
        self.setMap(index)



class WebEnginePage(QWebEnginePage):
    def __init__(self, parent):
        super().__init__(parent)
        self.parent = parent

    def javaScriptConsoleMessage(self, level, msg, line, sourceID):
        #print(msg)
        if 'coordinates' in msg:
            self.parent.handleClick(msg)




if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())
