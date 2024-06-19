#include <iostream>
#include <string>

// ��������� ��� ������ � �������
class File {
public:
    virtual void open(const std::string& filename) = 0;
    virtual void edit() = 0;
    virtual void print() = 0;
    virtual ~File() {}
};

// ���������� ���������� �������� ���������� �����
class PlainTextFile : public File {
public:
    void open(const std::string& filename) override {
        std::cout << "Opening plain text file: " << filename << std::endl;
    }

    void edit() override {
        std::cout << "Editing plain text file" << std::endl;
    }

    void print() override {
        std::cout << "Printing plain text file" << std::endl;
    }
};

// ��������� ��� ��������� ������
class Highlighter {
public:
    virtual void highlight(const std::string& text) = 0;
    virtual ~Highlighter() {}
};

// ���������� ���������� ��������� ��� �������� ������ (��� ���������)
class PlainTextHighlighter : public Highlighter {
public:
    void highlight(const std::string& text) override {
        std::cout << "Plain text does not support highlighting: " << text << std::endl;
    }
};

// ���������� ���������� XML �����
class XMLFile {
public:
    void openXML(const std::string& filename) {
        std::cout << "Opening XML file: " << filename << std::endl;
    }

    void editXML() {
        std::cout << "Editing XML file" << std::endl;
    }

    void printXML() {
        std::cout << "Printing XML file" << std::endl;
    }
};

// ���������� ���������� ��������� ��� XML ������
class XMLHighlighter {
public:
    void highlightXML(const std::string& text) {
        std::cout << "Highlighting XML text: " << text << std::endl;
    }
};

// ������� ��� XML �����
class XMLFileAdapter : public File {
private:
    XMLFile* xmlFile;
public:
    XMLFileAdapter(XMLFile* file) : xmlFile(file) {}

    void open(const std::string& filename) override {
        xmlFile->openXML(filename);
    }

    void edit() override {
        xmlFile->editXML();
    }

    void print() override {
        xmlFile->printXML();
    }
};

// ������� ��� XML ���������
class XMLHighlighterAdapter : public Highlighter {
private:
    XMLHighlighter* xmlHighlighter;
public:
    XMLHighlighterAdapter(XMLHighlighter* highlighter) : xmlHighlighter(highlighter) {}

    void highlight(const std::string& text) override {
        xmlHighlighter->highlightXML(text);
    }
};

// ����� TextEditor, �������������� ��������� ��������
class TextEditor {
private:
    File* file;
    Highlighter* highlighter;

public:
    TextEditor() : file(nullptr), highlighter(nullptr) {}

    void setFile(File* f) {
        file = f;
    }

    void setHighlighter(Highlighter* h) {
        highlighter = h;
    }

    void openFile(const std::string& filename) {
        if (file) file->open(filename);
    }

    void editFile() {
        if (file) file->edit();
    }

    void printFile() {
        if (file) file->print();
    }

    void highlightText(const std::string& text) {
        if (highlighter) highlighter->highlight(text);
    }

    ~TextEditor() {
        delete file;
        delete highlighter;
    }
};

// ������� �������, ��������������� ������������� �������� "�������"
int main() {
    TextEditor editor;

    // ������ � ������� ��������� ������
    File* plainTextFile = new PlainTextFile();
    Highlighter* plainTextHighlighter = new PlainTextHighlighter();
    editor.setFile(plainTextFile);
    editor.setHighlighter(plainTextHighlighter);
    editor.openFile("example.txt");
    editor.editFile();
    editor.highlightText("This is a plain text file.");
    editor.printFile();

    // ������ � XML ������ ����� ��������
    XMLFile* xmlFile = new XMLFile();
    XMLHighlighter* xmlHighlighter = new XMLHighlighter();
    File* xmlFileAdapter = new XMLFileAdapter(xmlFile);
    Highlighter* xmlHighlighterAdapter = new XMLHighlighterAdapter(xmlHighlighter);
    editor.setFile(xmlFileAdapter);
    editor.setHighlighter(xmlHighlighterAdapter);
    editor.openFile("example.xml");
    editor.editFile();
    editor.highlightText("<tag>This is an XML file.</tag>");
    editor.printFile();

    delete plainTextFile;
    delete plainTextHighlighter;
    delete xmlFileAdapter;
    delete xmlHighlighterAdapter;
    delete xmlFile;
    delete xmlHighlighter;

    return 0;
}
