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

// ����������� ����� Builder
class Builder {
public:
    virtual void createFile() = 0;
    virtual void createHighlighter() = 0;
    virtual TextEditor* getTextEditor() = 0;
    virtual ~Builder() {}
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

// ���������� ��������� ��� ������� ��������� ������
class PlainTextBuilder : public Builder {
private:
    TextEditor* editor;

public:
    PlainTextBuilder() {
        editor = new TextEditor();
    }

    void createFile() override {
        editor->setFile(new PlainTextFile());
    }

    void createHighlighter() override {
        editor->setHighlighter(new PlainTextHighlighter());
    }

    TextEditor* getTextEditor() override {
        return editor;
    }

    ~PlainTextBuilder() {
        delete editor;
    }
};

// ���������� ��������� ��� XML ������
class XMLBuilder : public Builder {
private:
    TextEditor* editor;

public:
    XMLBuilder() {
        editor = new TextEditor();
    }

    void createFile() override {
        editor->setFile(new XMLFile());
    }

    void createHighlighter() override {
        editor->setHighlighter(new XMLHighlighter());
    }

    TextEditor* getTextEditor() override {
        return editor;
    }

    ~XMLBuilder() {
        delete editor;
    }
};

// ��������, ����������� ��������� ����������
class Director {
public:
    void construct(Builder& builder) {
        builder.createFile();
        builder.createHighlighter();
    }
};

// ������� �������, ��������������� ������������� �������� "���������"
int main() {
    Director director;

    PlainTextBuilder plainTextBuilder;
    director.construct(plainTextBuilder);
    TextEditor* plainTextEditor = plainTextBuilder.getTextEditor();
    plainTextEditor->openFile("example.txt");
    plainTextEditor->editFile();
    plainTextEditor->highlightText("This is a plain text file.");
    plainTextEditor->printFile();
    delete plainTextEditor;

    XMLBuilder xmlBuilder;
    director.construct(xmlBuilder);
    TextEditor* xmlEditor = xmlBuilder.getTextEditor();
    xmlEditor->openFile("example.xml");
    xmlEditor->editFile();
    xmlEditor->highlightText("<tag>This is an XML file.</tag>");
    xmlEditor->printFile();
    delete xmlEditor;

    return 0;
}
