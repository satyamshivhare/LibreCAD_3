#include "font_book.h"

using namespace lc::viewer::opengl;

Font_Book::Font_Book()
{
}

Font_Book::~Font_Book()
{
}

bool Font_Book::createDefaultFont(const std::string& name,const std::string& file_path)
{
    _default_font=new GL_Font();

    std::string fontFamily;
    std::string fontStyle;
    if(_default_font->readyFont(file_path, fontFamily, fontStyle))
    {
        _font_map.insert(std::make_pair( name, _default_font ) );
        return true;
    }

    return false;
}

bool Font_Book::createFont(const std::string& name,const std::string& file_path)
{
    GL_Font* font=new GL_Font();

    std::string fontFamily;
    std::string fontStyle;
    if(font->readyFont(file_path, fontFamily, fontStyle))
    {
        if (fontStyle == "Regular") {
            _font_map.insert(std::make_pair(fontFamily, font));
        }
        else if (fontStyle == "Bold") {
            _font_bold_map.insert(std::make_pair(fontFamily, font));
        }
        else if (fontStyle == "Italic") {
            _font_italic_map.insert(std::make_pair(fontFamily, font));
        }
        else if (fontStyle == "Bold Italic") {
            _font_bold_italic_map.insert(std::make_pair(fontFamily, font));
        }
        else {
            _font_map.insert(std::make_pair(name, font));
        }

        return true;
    }

    return false;
}

GL_Font* Font_Book::pickFont(const std::string& font_name, FontType fontType)
{
    std::map<const std::string, GL_Font*>* fontMap;

    if (fontType == FontType::BOLD) {
        fontMap = &_font_bold_map;
    }
    else if (fontType == FontType::ITALIC) {
        fontMap = &_font_italic_map;
    }
    else if (fontType == FontType::BOLD_ITALIC) {
        fontMap = &_font_bold_italic_map;
    }
    else {
        fontMap = &_font_map;
    }

    std::map<const std::string, GL_Font* >::iterator it;

    it = fontMap->find(font_name);

    if (it != fontMap->end()) {
        return (it->second);
    }
    else {
        if (_font_map.find(font_name) != _font_map.end()) {
            return _font_map.find(font_name)->second;
        }
        else {
            return _default_font;
        }
    }
}

std::vector<std::string> Font_Book::getFontList() const {
    std::vector<std::string> result;
    for (const auto& font : _font_map) {
        result.push_back(font.first);
    }
    return result;
}

bool Font_Book::createFontsFromDir(const std::string& directoryPath) {
    if (!boost::filesystem::is_directory(directoryPath)) {
        return false;
    }

    for (boost::filesystem::directory_entry& entry : boost::filesystem::directory_iterator(directoryPath)) {
        createFontFromEntry(entry, directoryPath);
    }

    return true;
}

void Font_Book::createFontFromEntry(boost::filesystem::directory_entry& entry, const std::string& directoryPath) {
    std::string fontFileStem = entry.path().stem().string();
    std::string fontFileName = entry.path().filename().string();

    if (entry.path().extension().string() == ".ttf" || entry.path().extension().string() == ".otf") {
        if (_font_map.find(fontFileStem) == _font_map.end()) {
            createFont(fontFileStem, directoryPath + "/" + fontFileName);
        }
    }
}
