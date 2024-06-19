#include <iostream>
#include <string>

// ����������� ����� File
class File {
public:
    virtual void open(const std::string& filename) = 0;
    virtual void edit() = 0;
    virtual void print() = 0;
    virtual ~File() {}
};

// ����������� ����� Highlighter
class Highlighter {
public:
    virtual void highlight(const std::string& text) = 0;
    virtual ~Highlighter() {}
};

// ����������� �������
class AbstractFactory {
public:
    virtual File* createFile() = 0;
    virtual Highlighter* createHighlighter() = 0;
    virtual ~AbstractFactory() {}
};

// ���������� ����� ��� �������� ���������� �����
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

// ���������� ����� ��� ��������� �������� ������
class PlainTextHighlighter : public Highlighter {
public:
    void highlight(const std::string& text) override {
        std::cout << "Plain text does not support highlighting: " << text << std::endl;
    }
};

// ���������� ����� ��� XML �����
class XMLFile : public File {
public:
    void open(const std::string& filename) override {
        std::cout << "Opening XML file: " << filename << std::endl;
    }

    void edit() override {
        std::cout << "Editing XML file" << std::endl;
    }

    void print() override {
        std::cout << "Printing XML file" << std::endl;
    }
};

// ���������� ����� ��� ��������� XML ������
class XMLHighlighter : public Highlighter {
public:
    void highlight(const std::string& text) override {
        std::cout << "Highlighting XML text: " << text << std::endl;
    }
};

// ���������� ������� ��� ������� ��������� ������
class PlainTextFactory : public AbstractFactory {
public:
    File* createFile() override {
        return new PlainTextFile();
    }

    Highlighter* createHighlighter() override {
        return new PlainTextHighlighter();
    }
};

// ���������� ������� ��� XML ������
class XMLFactory : public AbstractFactory {
public:
    File* createFile() override {
        return new XMLFile();
    }

    Highlighter* createHighlighter() override {
        return new XMLHighlighter();
    }
};

// ������� ��� ��������� �����
void processFile(AbstractFactory* factory, const std::string& filename, const std::string& text) {
    File* file = factory->createFile();
    Highlighter* highlighter = factory->createHighlighter();

    file->open(filename);
    file->edit();
    highlighter->highlight(text);
    file->print();

    delete file;
    delete highlighter;
}

int main() {
    AbstractFactory* plainTextFactory = new PlainTextFactory();
    processFile(plainTextFactory, "example.txt", "This is a plain text file.");
    delete plainTextFactory;

    AbstractFactory* xmlFactory = new XMLFactory();
    processFile(xmlFactory, "example.xml", "<tag>This is an XML file.</tag>");
    delete xmlFactory;

    return 0;
}
