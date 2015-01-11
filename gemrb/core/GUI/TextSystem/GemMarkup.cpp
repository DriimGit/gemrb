/* GemRB - Infinity Engine Emulator
 * Copyright (C) 2014 The GemRB Project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "GemMarkup.h"

#include "GameData.h"

namespace GemRB {

void GemMarkupParser::SetTextDefaults(const Font* ftext, const Font* finit, Palette* textCol)
{
	this->ftext = ftext;
	this->finit = finit;
	this->palette = textCol;
	textCol->acquire();
}

void GemMarkupParser::ParseMarkupStringIntoContainer(const String& text, TextContainer& container) const
{
	size_t tagPos = text.find_first_of('[');
	if (tagPos != 0) {
		// handle any text before the markup
		container.AppendText(text.substr(0, tagPos));
	}
	// parse the text looking for accepted tags ([cap], [color], [p])
	// [cap] encloses a span of text to be rendered with the finit font
	// [color=%02X%02X%02X] encloses a span of text to be rendered with the given RGB values
	// [p] encloses a span of text to be rendered as an inline block:
	//     it will grow vertically as needed, but be confined to the remaining width of the line

	// span properties
	Color palCol;
	Palette* pal = NULL;
	const Font* fnt = ftext;
	Size frame;
	//ieByte align = 0;

	enum ParseState {
		TEXT = 0,
		OPEN_TAG,
		CLOSE_TAG,
		COLOR
	};

	// TODO: implement escaping [] ('\')
	String token;
	ParseState state = TEXT;
	String::const_iterator it = text.begin() + tagPos;
	for (; it != text.end(); it++) {
		switch (state) {
			case OPEN_TAG:
				switch (*it) {
					case '=':
						if (token == L"color") {
							state = COLOR;
							token.clear();
						}
						// else is a parse error...
						continue;
					case ']':
						if (token == L"cap") {
							fnt = finit;
							//align = IE_FONT_SINGLE_LINE;
						} else if (token == L"p") {
							frame.w = -1;
						}
						state = TEXT;
						token.clear();
						continue;
					case '[': // wasn't actually a tag after all
						state = TEXT;
						token.insert(0, 1, L'[');
						it--; // rewind so the TEXT node is created
						continue;
				}
				break;
			case CLOSE_TAG:
				switch (*it) {
					case ']':
						if (token == L"color") {
							gamedata->FreePalette(pal);
						} else if (token == L"cap") {
							fnt = ftext;
							//align = 0;
						} else if (token == L"p") {
							frame.w = 0;
						}
						state = TEXT;
						token.clear();
						continue;
				}
				break;
			case TEXT:
				switch (*it) {
					case '[':
						if (token.length() && token != L"\n") {
							// FIXME: lazy hack.
							// we ought to ignore all white space between markup unless it contains other text
							Palette* p = pal;
							if (fnt == finit && p == NULL) {
								p = finit->GetPalette();
								p->release();
							}
							container.AppendContent(new TextSpan(token, fnt, p, &frame));
						}
						token.clear();
						if (*++it == '/')
							state = CLOSE_TAG;
						else {
							it--;
							state = OPEN_TAG;
						}
						continue;
				}
				break;
			case COLOR:
				switch (*it) {
					case L']':
						swscanf(token.c_str(), L"%02X%02X%02X", &palCol.r, &palCol.g, &palCol.b);
						// TODO: we shouldnt be making a new palette here. we end up with dozens of identical palettes.
						// something needs to cache these
						pal = new Palette(palCol, palette->back);
						state = TEXT;
						token.clear();
						continue;
				}
				break;
			default: // parse error, not clearing token
				state = TEXT;
				break;
		}
		token += *it;
	}
	// FIXME: should handle errors gracefully
	assert(pal == NULL && state == TEXT);
	if (token.length()) {
		// there was some text at the end without markup
		container.AppendText(token);
	}
}

}
