#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int FILAS = 7;
const int COLUMNAS = 7;
int camino[FILAS][COLUMNAS] = {
	{1, 1, 0, 0, 0, 0, 1},
    {0, 1, 0, 0, 0, 1, 0},
	{1, 1, 1, 1, 1, 1, 0},
    {1, 0, 1, 0, 1, 0, 0},
	{1, 0, 1, 0, 1, 0, 0},
    {1, 0, 1, 0, 1, 1, 0},
	{1, 0, 1, 0, 0, 0, 1}
};

// función revisa si una posición en el camino  es válida
bool esValida(int x, int y) {
	// Revisar si esta dentro de los límites y si hay un camino 
	if (x >= 0 && x < FILAS && y >= 0 && y < COLUMNAS && camino[x][y] == 1) {
		return true;
	} else {
		return false;
	}
}

// Función iterativa para encontrar si hay un camino usando una pila
bool caminoIterativoExiste(int inicioX, int inicioY, int destinoX, int destinoY) {
	// Verificar que los puntos inicial y el final son válidos
	if (!esValida(inicioX, inicioY) || !esValida(destinoX, destinoY)) {
		return false;
	}
	
	vector<vector<bool>> visitado(FILAS, vector<bool>(COLUMNAS, false));
	stack<pair<int, int>> pila;
	pila.push({inicioX, inicioY});
	visitado[inicioX][inicioY] = true;
	
	// Procesar la pila hasta que esté vacía
	while (!pila.empty()) {
		pair<int, int> nodo = pila.top();
		pila.pop();
		int x = nodo.first;
		int y = nodo.second;
		
		// Si llega al destino, regresa un verdadero
		if (x == destinoX && y == destinoY) {
			return true;
		}
		
		//  movimientos que pueden ser posibles: derecha, izquierda, abajo, arriba
		vector<pair<int, int>> direcciones = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
		for (int i = 0; i < direcciones.size(); i++) {
			int nuevoX = x + direcciones[i].first;
			int nuevoY = y + direcciones[i].second;
			if (esValida(nuevoX, nuevoY) && !visitado[nuevoX][nuevoY]) {
				pila.push({nuevoX, nuevoY});
				visitado[nuevoX][nuevoY] = true;
			}
		}
	}
	
	return false;
}

// Función recursiva para ver si hay un camino
bool caminoRecursivoExiste(int x, int y, int destinoX, int destinoY, vector<vector<bool>>& visitado) {
	// revisa  si la posición es válida o ya paso por ahi
	if (!esValida(x, y) || visitado[x][y]) {
		return false;
	}
	if (x == destinoX && y == destinoY) {
		return true;
	}
	
	visitado[x][y] = true;
	
	// Direcciones posibles
	vector<pair<int, int>> direcciones = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
	for (int i = 0; i < direcciones.size(); i++) {
		int nuevoX = x + direcciones[i].first;
		int nuevoY = y + direcciones[i].second;
		if (caminoRecursivoExiste(nuevoX, nuevoY, destinoX, destinoY, visitado)) {
			return true;
		}
	}
	
	return false;
}

int main() {
	// Punto de inicio y destino
	int inicioX = 0, inicioY = 0;
	int destinoX = 6, destinoY = 6;
	
	//función iterativa
	if (caminoIterativoExiste(inicioX, inicioY, destinoX, destinoY)) {
		cout << "Hay un camino (iterativo)" << endl;
	} else {
		cout << "No hay camino (iterativo)" << endl;
	}
	
	// función recursiva
	vector<vector<bool>> visitado(FILAS, vector<bool>(COLUMNAS, false));
	if (caminoRecursivoExiste(inicioX, inicioY, destinoX, destinoY, visitado)) {
		cout << "Hay un camino (recursivo)" << endl;
	} else {
		cout << "No hay camino (recursivo)" << endl;
	}
	
	return 0;
}

