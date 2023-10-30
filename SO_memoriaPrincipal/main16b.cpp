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

    // Ler o arquivo e armazenar os números em um vetor
    vector<int> numbers;
    int number;
    while (inputFile >> number) {
        numbers.push_back(number);
    }
    inputFile.close();

    if (numbers.empty()) {
        cout << "O arquivo está vazio ou não contém números válidos." << endl;
        return 1;
    }

    // Solicitar ao usuário o índice da linha a ser lida
    int lineIndex;
    cout << "Digite o índice da linha a ser lida (começando em 0): ";
    cin >> lineIndex;

    if (lineIndex < 0 || lineIndex >= numbers.size()) {
        cout << "Índice inválido. Certifique-se de escolher um número entre 0 e " << numbers.size() - 1 << endl;
        return 1;
    }

    // Converter o número escolhido em binário
    int chosenNumber = numbers[lineIndex];
    string binaryRepresentation = bitset<16>(chosenNumber).to_string();

    // Calcular o número da página e o deslocamento
    string pageBinary = binaryRepresentation.substr(0, 4);  // 4 primeiros caracteres para o número da página
    string offsetBinary = binaryRepresentation.substr(4);    // Restante para o deslocamento

    int pageNumber = bitset<4>(pageBinary).to_ulong();      // Converter binário para decimal
    int offset = bitset<12>(offsetBinary).to_ulong();      // Converter binário para decimal

    // Imprimir o resultado
    cout << "O endereço " << chosenNumber << " contém:" << endl;
    cout << "Número da página = " << pageNumber << endl;
    cout << "Deslocamento = " << offset << endl;
    cout << "Representação binária: " << binaryRepresentation << endl;

    // Agora, vamos ler o arquivo "data_memory.txt" para encontrar o valor correspondente
    ifstream dataMemoryFile("data_memory.txt");
    if (!dataMemoryFile.is_open()) {
        cout << "Erro ao abrir o arquivo data_memory.txt." << endl;
        return 1;
    }

    int value;
    int pageSize = 256; // Tamanho da página de 256 bytes para endereços de 16 bits

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
