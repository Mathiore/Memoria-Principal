#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
#include <locale.h>
#include <limits>

using namespace std;

int main() {
    setlocale(LC_ALL, "");
    string filename = "addresses_16b.txt"; // Nome do arquivo de texto

    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cout << "Erro ao abrir o arquivo de entrada." << endl;
        return 1;
    }

    // Ler o arquivo e armazenar os n�meros em um vetor
    vector<int> numbers;
    int number;
    while (inputFile >> number) {
        numbers.push_back(number);
    }
    inputFile.close();

    if (numbers.empty()) {
        cout << "O arquivo est� vazio ou n�o cont�m n�meros v�lidos." << endl;
        return 1;
    }

    // Solicitar ao usu�rio o �ndice da linha a ser lida
    int lineIndex;
    cout << "Digite o �ndice da linha a ser lida (come�ando em 0): ";
    cin >> lineIndex;

    if (lineIndex < 0 || lineIndex >= numbers.size()) {
        cout << "�ndice inv�lido. Certifique-se de escolher um n�mero entre 0 e " << numbers.size() - 1 << endl;
        return 1;
    }

    // Converter o n�mero escolhido em bin�rio
    int chosenNumber = numbers[lineIndex];
    string binaryRepresentation = bitset<16>(chosenNumber).to_string();

    // Calcular o n�mero da p�gina e o deslocamento
    string pageBinary = binaryRepresentation.substr(0, 4);  // 4 primeiros caracteres para o n�mero da p�gina
    string offsetBinary = binaryRepresentation.substr(4);    // Restante para o deslocamento

    int pageNumber = bitset<4>(pageBinary).to_ulong();      // Converter bin�rio para decimal
    int offset = bitset<12>(offsetBinary).to_ulong();      // Converter bin�rio para decimal

    // Imprimir o resultado
    cout << "O endere�o " << chosenNumber << " cont�m:" << endl;
    cout << "N�mero da p�gina = " << pageNumber << endl;
    cout << "Deslocamento = " << offset << endl;
    cout << "Representa��o bin�ria: " << binaryRepresentation << endl;

    // Agora, vamos ler o arquivo "data_memory.txt" para encontrar o valor correspondente
    ifstream dataMemoryFile("data_memory.txt");
    if (!dataMemoryFile.is_open()) {
        cout << "Erro ao abrir o arquivo data_memory.txt." << endl;
        return 1;
    }

    int value;
    int pageSize = 256; // Tamanho da p�gina de 256 bytes para endere�os de 16 bits

    int pageStartLine = pageNumber * pageSize;
    int targetLine = pageStartLine + offset; // Calcule a linha alvo

    vector<string> lines;
    string line;

    while (getline(dataMemoryFile, line)) {
        lines.push_back(line);
    }
    cout <<"Valor lido: " << lines[targetLine-1] << endl;

    dataMemoryFile.close();

    return 0;
}
