#include <iostream>
#include <vector>
#include <string>

class Printable {
public:
    virtual void print() const { std::cout << "Printing general content...\n"; } // Tornando print virtual e com uma implementação padrão
    virtual ~Printable() {} // Destrutor virtual para garantir a desalocação correta
};

class File {
public:
    void open(const std::string& filename) { std::cout << "Opening " << filename << "\n"; }
    // Não precisa de destrutor virtual se não for base polimórfica direta em um vetor de ponteiros
};

class TextFile : public Printable, public File { // inherits from Printable and File
public:
    TextFile(const std::string& filename) : filename(filename) {}
    void process() {
        open(filename);
        print(); // calls Printable::print()
        std::cout << "Processing text file.\n";
    }
    void print() const override { // Sobrescrevendo print para TextFile
        std::cout << "Printing TextFile: " << filename << "\n";
    }
private:
    std::string filename;
};

// Nova classe de arquivo: ImageFile
class ImageFile : public Printable, public File { // Herda de Printable e File
public:
    ImageFile(const std::string& filename, std::string resolution) 
        : filename(filename), resolution(resolution) {}

    void view() {
        open(filename);
        std::cout << "Viewing image file with resolution: " << resolution << "\n";
    }

    void print() const override { // Sobrescrevendo print para ImageFile
        std::cout << "Printing ImageFile: " << filename << " at " << resolution << " resolution.\n";
    }
private:
    std::string filename;
    std::string resolution;
};


int main() {
    std::vector<Printable*> printableFiles; // Vetor de ponteiros para Printable

    // Carregando o vetor com instâncias de TextFile e ImageFile
    printableFiles.push_back(new TextFile("documento1.txt"));
    printableFiles.push_back(new TextFile("relatorio.txt"));
    printableFiles.push_back(new ImageFile("foto.jpg", "1920x1080")); // Adicionando ImageFile
    printableFiles.push_back(new TextFile("carta.txt"));
    printableFiles.push_back(new ImageFile("logo.png", "800x600")); // Adicionando outro ImageFile

    // Iterando pelo vetor e chamando o método print()
    std::cout << "--- Chamando print() para todos os arquivos imprimíveis ---\n";
    for (const auto& pFile : printableFiles) {
        pFile->print(); // Chamada polimórfica
    }

    // Importante: desalocar a memória alocada dinamicamente
    std::cout << "\n--- Desalocando memória ---\n";
    for (const auto& pFile : printableFiles) {
        delete pFile;
    }

    return 0;
}