#include <stdio.h>

#include <mt_dtype.h>
#include <mt_net.h>
#include <mt_line.h>
#include <mt_station.h>

net *create_net();
station *prompt_station(line *l, char *append);
line *prompt_line(net *n, char *append);

int main() {
	int i, j; // auxiliar vars

	station *s;
	line *l;
	link *hl;

	net *metro = create_net();

	int o;
	line *lp, *ld;
	station *sp, *sd;
	
	while(1) {
		printf("\nRED DEL METRO DE LA CIDUAD DE MEXICO\n");

		printf(" 1. Planear recorrido\n");
		printf(" 2. Salir\n");
		printf("\nTu opcion: ");
		scanf("%d", &o);

		switch(o) {
			case 1:
				lp = prompt_line(metro, " de partida");
				sp = prompt_station(lp, " de partida");
				ld = prompt_line(metro, " de destino");
				sd = prompt_station(ld, " de destino");
				dijk_make(metro, sp);
				dijk_print_path(sd);
				break;
			case 2:
				return 0;
		}
	}
	return 0;
}

/**
 * Asks the user to choose a line from net
 */
line *prompt_line(net *n, char *append) {
	int o;
	line *li;
	
	while(1) {
		printf("\nSelecciona la linea%s\n", append);

		net_print_lines(n);

		printf("\nTu opcion: ");
		scanf("%d", &o);

		if(li = net_get_line(n, o)) return li;
	}
}

/**
 * Asks the user to choose a station from line
 */
station *prompt_station(line *l, char *append) {
	int o;
	station *st;
	
	while(1) {
		printf("\nSelecciona la estacion%s\n", append);

		line_print(l);

		printf("\nTu opcion: ");
		scanf("%d", &o);

		if(st = line_get_station(l, o)) return st;
	}
}

/**
 * Constructs a net representing the Metro de la Ciudad de Mexico
 */
net *create_net() {
	net *n; 

	char *stations[] = {
		"Observatorio",					/* 0 */
		"Tacubaya",
		"Juanacatlan",
		"Chapultepec",
		"Sevilla",
		"Insurgentes",					/* 5 */
		"Cuauhtemoc",
		"Balderas",
		"Salto del Agua",
		"Isabel la Catolica",			
		"Pino Suarez",					/* 10 */
		"Merced",
		"Candelaria",
		"San Lazaro",
		"Moctezuma",
		"Balbuena",						/* 15 */
		"Boulevard Puerto Aereo",
		"Gomez Farias",
		"Zaragoza",
		"Pantitlan",					
		"Cuatro Caminos",				/* 20 */
		"Panteones",
		"Tacuba",
		"Cuitlahuac",
		"Popotla",
		"Colegio Militar",				/* 25 */
		"Normal",
		"San Cosme",
		"Revolucion",
		"Hidalgo",
		"Bellas Artes",					/* 30 */
		"Allende",
		"Zocalo",
		"San Antonio Abad",
		"Chabacano",
		"Viaducto",						/* 35 */
		"Xola",
		"Villa de Cortes",
		"Nativitas",
		"Portales",
		"Ermita",						/* 40 */
		"General Anaya",
		"Tasquena",
		"Indios Verdes",
		"Deportivo 18 de Mayo",
		"Potrero",						/* 45 */
		"La Raza",
		"Tlatelolco",
		"Guerrero",
		"Juarez",
		"Ninos Heroes",					/* 50 */
		"Hospital General",
		"Centro Medico",
		"Etiopia",
		"Eugenia",
		"Division del Norte",			/* 55 */
		"Zapata",
		"Coyoacan",
		"Viveros",
		"Miguel Angel de Quevedo",
		"Copilco",						/* 60 */
		"Universidad",
		"Martín Carrera",
		"Talismán",
		"Bondojito",
		"Consulado",					/* 65 */
		"Canal del Norte",
		"Morelos",
		"Fray Servando",
		"Jamaica",
		"Santa Anita",					/* 70 */
		"Hangares",
		"Terminal Aérea",
		"Oceania",
		"Aragón",
		"Eduardo Molina",				/* 75 */
		"Valle Gomez",
		"Misterios",
		"Autobuses Norte",
		"Instituto del Petróleo",
		"Politecnico",					/* 80 */
		"El Rosario",
		"Tezozómoc",
		"Azcapotzalco",
		"Ferrería",
		"Norte 45",						/* 85 */
		"Vallejo",
		"Lindavista",
		"La Villa-Basílica",
		"Aquiles Serdán",
		"Camarones",					/* 90 */
		"Refinería",
		"San Joaquín",
		"Polanco",
		"Auditorio",
		"Constituyentes",				/* 95 */
		"San Pedro de los Pinos",
		"San Antonio",
		"Mixcoac",
		"Barranca del Muerto",
		"Garibaldi", 					/* 100 */
		"San Juan de Letrán",
		"Doctores",
		"Obrera",
		"La Viga",
		"Coyuya",						/* 105 */
		"Iztacalco",
		"Apatlaco",
		"Aculco",
		"Escuadrón 201",
		"Atlalilco",					/* 110 */
		"Iztapalapa",
		"Cerro de la Estrella",
		"UAM-I",
		"Constitución de 1917",
		"Patriotismo",					/* 115 */
		"Chilpancingo",
		"Lázaro Cárdenas",
		"Mixiuhca",
		"Velódromo",
		"Ciudad Deportiva",				/* 120 */
		"Puebla",
		"Agricola Oriental",
		"Canal de San Juan",
		"Tepalcates",
		"Guelatao",						/* 125 */
		"Peñon Viejo",
		"Acatitla",
		"Santa Marta",
		"Los Reyes",
		"La Paz",						/* 130 */
		"Ciudad Azteca",
		"Plaza Aragón",
		"Olimpica",
		"Ecatepec",
		"Múzquiz",						/* 135 */
		"Río de los Remedios",
		"Impulsora",
		"Nezahualcóyotl",
		"Villa de Aragón",
		"Bosque de Aragón",				/* 140 */
		"Deportivo Oceanía",
		"Romero Rubio",
		"R. Flores Magón",
		"Tepito",
		"Lagunilla",					/* 145 */
		"Buenavista"
	};

	int l_1[] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
		17, 18, 19
	};
	int l_2[] = {
		20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 10, 33, 34,
		35, 36, 37, 38, 39, 40, 41, 42
	};
	int l_3[] = {
		43, 44, 45, 46, 47, 48, 29, 49, 7, 50, 51, 52, 53, 54, 55, 56, 57, 58,
		59, 60, 61
	};
	int l_4[] = { 62, 63, 64, 65, 66, 67, 12, 68, 69, 70 };
	int l_5[] = { 19, 71, 72, 73, 74, 75, 65, 76, 77, 46, 78, 79, 80 };
	int l_6[] = { 81, 82, 83, 84, 85, 86, 79, 87, 44, 88, 62 };
	int l_7[] = { 81, 89, 90, 91, 22, 92, 93, 94, 95, 1, 96, 97, 98, 99};
	int l_8[] = {
		100, 30, 101, 8, 102, 103, 34, 104, 70, 105, 106, 107, 108, 109,
		110, 111, 112, 113, 114
	};
	int l_9[] = { 1, 115, 116, 52, 117, 34, 69, 118, 119, 120, 121, 19 };
	int l_a[] = { 19, 122, 123, 124, 125, 126, 127, 128,129, 130 };
	int l_b[] = {
		131, 132, 133, 134 ,135, 136, 137, 138, 139, 140, 141,
		73, 142, 143, 13, 67, 144, 145, 100, 48, 146
	};

	n = new_net(COUNT(stations), 11);
	net_create_stations(n, stations);
	net_create_line(n, "1", l_1, COUNT(l_1), 18660);
	net_create_line(n, "2", l_2, COUNT(l_2), 23431);
	net_create_line(n, "3", l_3, COUNT(l_3), 23609);
	net_create_line(n, "4", l_4, COUNT(l_4), 10747);
	net_create_line(n, "5", l_5, COUNT(l_5), 15675);
	net_create_line(n, "6", l_6, COUNT(l_6), 13947);
	net_create_line(n, "7", l_7, COUNT(l_7), 18784);
	net_create_line(n, "8", l_8, COUNT(l_8), 20078);
	net_create_line(n, "9", l_9, COUNT(l_9), 15375);
	net_create_line(n, "A", l_a, COUNT(l_a), 17192);
	net_create_line(n, "B", l_b, COUNT(l_b), 23722);

	return n;
}
