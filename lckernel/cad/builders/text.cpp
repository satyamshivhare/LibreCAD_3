#include "text.h"
#include <cad/primitive/text.h>

using namespace lc::builder;

TextBuilder::TextBuilder()
    :
    _height(100),
    _angle(0),
    _drawingDirection(lc::TextConst::DrawingDirection::None),
    _hAlign(lc::TextConst::HAlign::HACenter),
    _vAlign(lc::TextConst::VAlign::VAMiddle),
    _underlined(false),
    _strikethrough(false),
    _bold(false),
    _italic(false)
{
}

const lc::geo::Coordinate& TextBuilder::insertionPoint() const {
    return _insertionPoint;
}

TextBuilder* TextBuilder::setInsertionPoint(const lc::geo::Coordinate& coord) {
    _insertionPoint = coord;
    return this;
}

const std::string& TextBuilder::textValue() const {
    return _textValue;
}

TextBuilder* TextBuilder::setTextValue(const std::string& text) {
    _textValue = text;
    return this;
}

double TextBuilder::height() const {
    return _height;
}

TextBuilder* TextBuilder::setHeight(double heightIn) {
    _height = heightIn;
    return this;
}

double TextBuilder::angle() const {
    return _angle;
}

TextBuilder* TextBuilder::setAngle(double angleIn) {
    _angle = angleIn;
    return this;
}

TextBuilder* TextBuilder::setDrawingDirection(lc::TextConst::DrawingDirection drawingDirectionIn) {
    _drawingDirection = drawingDirectionIn;
    return this;
}

lc::TextConst::DrawingDirection TextBuilder::drawingDirection() const {
    return _drawingDirection;
}

TextBuilder* TextBuilder::setHorizontalAlign(lc::TextConst::HAlign halignin) {
    _hAlign = halignin;
    return this;
}

lc::TextConst::HAlign TextBuilder::horizontalAlign() const {
    return _hAlign;
}

TextBuilder* TextBuilder::setVerticalAlign(lc::TextConst::VAlign valignin) {
    _vAlign = valignin;
    return this;
}

lc::TextConst::VAlign TextBuilder::verticalAlign() const {
    return _vAlign;
}

TextBuilder* TextBuilder::setTextFont(std::string font) {
    _textStyle = font;
    return this;
}

std::string TextBuilder::textStyle() const {
    return _textStyle;
}

TextBuilder* TextBuilder::setUnderlined(bool underline) {
    _underlined = underline;
    return this;
}

bool TextBuilder::underlined() const {
    return _underlined;
}

TextBuilder* TextBuilder::setStrikethrough(bool strikethrough) {
    _strikethrough = strikethrough;
    return this;
}

bool TextBuilder::strikethrough() const {
    return _strikethrough;
}

TextBuilder* TextBuilder::setBold(bool bold) {
    _bold = bold;
    return this;
}

bool TextBuilder::bold() const {
    return _bold;
}

TextBuilder* TextBuilder::setItalic(bool italic) {
    _italic = italic;
    return this;
}

bool TextBuilder::italic() const {
    return _italic;
}

lc::entity::Text_CSPtr TextBuilder::build() {
    checkValues(true);
    return entity::Text_CSPtr(new entity::Text(*this));
}

void TextBuilder::copy(lc::entity::Text_CSPtr entity) {
    CADEntityBuilder::copy(entity);

    setInsertionPoint(entity->insertion_point());
    setTextValue(entity->text_value());
    setTextFont(entity->style());
    setHeight(entity->height());
    setAngle(entity->angle());
    setDrawingDirection(entity->textgeneration());
    setHorizontalAlign(entity->halign());
    setVerticalAlign(entity->valign());
    setUnderlined(entity->underlined());
    setStrikethrough(entity->strikethrough());
    setBold(entity->bold());
    setItalic(entity->italic());
}
