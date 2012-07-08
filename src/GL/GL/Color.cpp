#include <GL/GL/Color.hpp>

namespace GL
{
	Color::Color() : A(1.0f), R(1.0f), G(1.0f), B(1.0f)
	{
	}

	Color::Color( float r, float g, float b ) : A(1.0f), R(r), G(g), B(b)
	{
	}
		
	Color::Color( float a, float r, float g, float b ) : A(a), R(r), G(g), B(B)
	{
	}
		
	Color::Color( const Color& color, float a ) : A(a), R(color.R), G(color.G), B(color.B)
	{
	}
		
	Color Color::FromARGB( uchar a, uchar r, uchar g, uchar b )
	{
		return Color(a / 255.0f, r / 255.0f, g / 255.0f, b / 255.0f);
	}

	Color Color::FromRGB( uchar r, uchar g, uchar b )
	{
		return Color(r / 255.0f, g / 255.0f, b / 255.0f);
	}
	

	/*
		Color constants form the xna framework
	*/	
	const Color Color::TransparentBlack = Color::FromARGB(0, 0, 0, 0);
	const Color Color::TransparentWhite = Color::FromARGB(0, 255, 255, 255);
	const Color Color::AliceBlue = Color::FromARGB(255, 240, 248, 255);
	const Color Color::AntiqueWhite = Color::FromARGB(255, 250, 235, 215);
	const Color Color::Aqua = Color::FromARGB(255, 0, 255, 255);
	const Color Color::Aquamarine = Color::FromARGB(255, 127, 255, 212);
	const Color Color::Azure = Color::FromARGB(255, 240, 255, 255);
	const Color Color::Beige = Color::FromARGB(255, 245, 245, 220);
	const Color Color::Bisque = Color::FromARGB(255, 255, 228, 196);
	const Color Color::Black = Color::FromARGB(255, 0, 0, 0);
	const Color Color::BlanchedAlmond = Color::FromARGB(255, 255, 235, 205);
	const Color Color::Blue = Color::FromARGB(255, 0, 0, 255);
	const Color Color::BlueViolet = Color::FromARGB(255, 138, 43, 226);
	const Color Color::Brown = Color::FromARGB(255, 165, 42, 42);
	const Color Color::BurlyWood = Color::FromARGB(255, 222, 184, 135);
	const Color Color::CadetBlue = Color::FromARGB(255, 95, 158, 160);
	const Color Color::Chartreuse = Color::FromARGB(255, 127, 255, 0);
	const Color Color::Chocolate = Color::FromARGB(255, 210, 105, 30);
	const Color Color::Coral = Color::FromARGB(255, 255, 127, 80);
	const Color Color::CornflowerBlue = Color::FromARGB(255, 100, 149, 237);
	const Color Color::Cornsilk = Color::FromARGB(255, 255, 248, 220);
	const Color Color::Crimson = Color::FromARGB(255, 220, 20, 60);
	const Color Color::Cyan = Color::FromARGB(255, 0, 255, 255);
	const Color Color::DarkBlue = Color::FromARGB(255, 0, 0, 139);
	const Color Color::DarkCyan = Color::FromARGB(255, 0, 139, 139);
	const Color Color::DarkGoldenrod = Color::FromARGB(255, 184, 134, 11);
	const Color Color::DarkGray = Color::FromARGB(255, 169, 169, 169);
	const Color Color::DarkGreen = Color::FromARGB(255, 0, 100, 0);
	const Color Color::DarkKhaki = Color::FromARGB(255, 189, 183, 107);
	const Color Color::DarkMagenta = Color::FromARGB(255, 139, 0, 139);
	const Color Color::DarkOliveGreen = Color::FromARGB(255, 85, 107, 47);
	const Color Color::DarkOrange = Color::FromARGB(255, 255, 140, 0);
	const Color Color::DarkOrchid = Color::FromARGB(255, 153, 50, 204);
	const Color Color::DarkRed = Color::FromARGB(255, 139, 0, 0);
	const Color Color::DarkSalmon = Color::FromARGB(255, 233, 150, 122);
	const Color Color::DarkSeaGreen = Color::FromARGB(255, 143, 188, 139);
	const Color Color::DarkSlateBlue = Color::FromARGB(255, 72, 61, 139);
	const Color Color::DarkSlateGray = Color::FromARGB(255, 47, 79, 79);
	const Color Color::DarkTurquoise = Color::FromARGB(255, 0, 206, 209);
	const Color Color::DarkViolet = Color::FromARGB(255, 148, 0, 211);
	const Color Color::DeepPink = Color::FromARGB(255, 255, 20, 147);
	const Color Color::DeepSkyBlue = Color::FromARGB(255, 0, 191, 255);
	const Color Color::DimGray = Color::FromARGB(255, 105, 105, 105);
	const Color Color::DodgerBlue = Color::FromARGB(255, 30, 144, 255);
	const Color Color::Firebrick = Color::FromARGB(255, 178, 34, 34);
	const Color Color::FloralWhite = Color::FromARGB(255, 255, 250, 240);
	const Color Color::ForestGreen = Color::FromARGB(255, 34, 139, 34);
	const Color Color::Fuchsia = Color::FromARGB(255, 255, 0, 255);
	const Color Color::Gainsboro = Color::FromARGB(255, 220, 220, 220);
	const Color Color::GhostWhite = Color::FromARGB(255, 248, 248, 255);
	const Color Color::Gold = Color::FromARGB(255, 255, 215, 0);
	const Color Color::Goldenrod = Color::FromARGB(255, 218, 165, 32);
	const Color Color::Gray = Color::FromARGB(255, 128, 128, 128);
	const Color Color::Green = Color::FromARGB(255, 0, 128, 0);
	const Color Color::GreenYellow = Color::FromARGB(255, 173, 255, 47);
	const Color Color::Honeydew = Color::FromARGB(255, 240, 255, 240);
	const Color Color::HotPink = Color::FromARGB(255, 255, 105, 180);
	const Color Color::IndianRed = Color::FromARGB(255, 205, 92, 92);
	const Color Color::Indigo = Color::FromARGB(255, 75, 0, 130);
	const Color Color::Ivory = Color::FromARGB(255, 255, 255, 240);
	const Color Color::Khaki = Color::FromARGB(255, 240, 230, 140);
	const Color Color::Lavender = Color::FromARGB(255, 230, 230, 250);
	const Color Color::LavenderBlush = Color::FromARGB(255, 255, 240, 245);
	const Color Color::LawnGreen = Color::FromARGB(255, 124, 252, 0);
	const Color Color::LemonChiffon = Color::FromARGB(255, 255, 250, 205);
	const Color Color::LightBlue = Color::FromARGB(255, 173, 216, 230);
	const Color Color::LightCoral = Color::FromARGB(255, 240, 128, 128);
	const Color Color::LightCyan = Color::FromARGB(255, 224, 255, 255);
	const Color Color::LightGoldenrodYellow = Color::FromARGB(255, 250, 250, 210);
	const Color Color::LightGreen = Color::FromARGB(255, 144, 238, 144);
	const Color Color::LightGray = Color::FromARGB(255, 211, 211, 211);
	const Color Color::LightPink = Color::FromARGB(255, 255, 182, 193);
	const Color Color::LightSalmon = Color::FromARGB(255, 255, 160, 122);
	const Color Color::LightSeaGreen = Color::FromARGB(255, 32, 178, 170);
	const Color Color::LightSkyBlue = Color::FromARGB(255, 135, 206, 250);
	const Color Color::LightSlateGray = Color::FromARGB(255, 119, 136, 153);
	const Color Color::LightSteelBlue = Color::FromARGB(255, 176, 196, 222);
	const Color Color::LightYellow = Color::FromARGB(255, 255, 255, 224);
	const Color Color::Lime = Color::FromARGB(255, 0, 255, 0);
	const Color Color::LimeGreen = Color::FromARGB(255, 50, 205, 50);
	const Color Color::Linen = Color::FromARGB(255, 250, 240, 230);
	const Color Color::Magenta = Color::FromARGB(255, 255, 0, 255);
	const Color Color::Maroon = Color::FromARGB(255, 128, 0, 0);
	const Color Color::MediumAquamarine = Color::FromARGB(255, 102, 205, 170);
	const Color Color::MediumBlue = Color::FromARGB(255, 0, 0, 205);
	const Color Color::MediumOrchid = Color::FromARGB(255, 186, 85, 211);
	const Color Color::MediumPurple = Color::FromARGB(255, 147, 112, 219);
	const Color Color::MediumSeaGreen = Color::FromARGB(255, 60, 179, 113);
	const Color Color::MediumSlateBlue = Color::FromARGB(255, 123, 104, 238);
	const Color Color::MediumSpringGreen = Color::FromARGB(255, 0, 250, 154);
	const Color Color::MediumTurquoise = Color::FromARGB(255, 72, 209, 204);
	const Color Color::MediumVioletRed = Color::FromARGB(255, 199, 21, 133);
	const Color Color::MidnightBlue = Color::FromARGB(255, 25, 25, 112);
	const Color Color::MintCream = Color::FromARGB(255, 245, 255, 250);
	const Color Color::MistyRose = Color::FromARGB(255, 255, 228, 225);
	const Color Color::Moccasin = Color::FromARGB(255, 255, 228, 181);
	const Color Color::NavajoWhite = Color::FromARGB(255, 255, 222, 173);
	const Color Color::Navy = Color::FromARGB(255, 0, 0, 128);
	const Color Color::OldLace = Color::FromARGB(255, 253, 245, 230);
	const Color Color::Olive = Color::FromARGB(255, 128, 128, 0);
	const Color Color::OliveDrab = Color::FromARGB(255, 107, 142, 35);
	const Color Color::Orange = Color::FromARGB(255, 255, 165, 0);
	const Color Color::Orange_red = Color::FromARGB(255, 255, 69, 0);
	const Color Color::Orchid = Color::FromARGB(255, 218, 112, 214);
	const Color Color::PaleGoldenrod = Color::FromARGB(255, 238, 232, 170);
	const Color Color::PaleGreen = Color::FromARGB(255, 152, 251, 152);
	const Color Color::PaleTurquoise = Color::FromARGB(255, 175, 238, 238);
	const Color Color::PaleVioletRed = Color::FromARGB(255, 219, 112, 147);
	const Color Color::PapayaWhip = Color::FromARGB(255, 255, 239, 213);
	const Color Color::PeachPuff = Color::FromARGB(255, 255, 218, 185);
	const Color Color::Peru = Color::FromARGB(255, 205, 133, 63);
	const Color Color::Pink = Color::FromARGB(255, 255, 192, 203);
	const Color Color::Plum = Color::FromARGB(255, 221, 160, 221);
	const Color Color::PowderBlue = Color::FromARGB(255, 176, 224, 230);
	const Color Color::Purple = Color::FromARGB(255, 128, 0, 128);
	const Color Color::Red = Color::FromARGB(255, 255, 0, 0);
	const Color Color::RosyBrown = Color::FromARGB(255, 188, 143, 143);
	const Color Color::RoyalBlue = Color::FromARGB(255, 65, 105, 225);
	const Color Color::SaddleBrown = Color::FromARGB(255, 139, 69, 19);
	const Color Color::Salmon = Color::FromARGB(255, 250, 128, 114);
	const Color Color::SandyBrown = Color::FromARGB(255, 244, 164, 96);
	const Color Color::SeaGreen = Color::FromARGB(255, 46, 139, 87);
	const Color Color::SeaShell = Color::FromARGB(255, 255, 245, 238);
	const Color Color::Sienna = Color::FromARGB(255, 160, 82, 45);
	const Color Color::Silver = Color::FromARGB(255, 192, 192, 192);
	const Color Color::SkyBlue = Color::FromARGB(255, 135, 206, 235);
	const Color Color::SlateBlue = Color::FromARGB(255, 106, 90, 205);
	const Color Color::SlateGray = Color::FromARGB(255, 112, 128, 144);
	const Color Color::Snow = Color::FromARGB(255, 255, 250, 250);
	const Color Color::SpringGreen = Color::FromARGB(255, 0, 255, 127);
	const Color Color::SteelBlue = Color::FromARGB(255, 70, 130, 180);
	const Color Color::Tan = Color::FromARGB(255, 210, 180, 140);
	const Color Color::Teal = Color::FromARGB(255, 0, 128, 128);
	const Color Color::Thistle = Color::FromARGB(255, 216, 191, 216);
	const Color Color::Tomato = Color::FromARGB(255, 255, 99, 71);
	const Color Color::Turquoise = Color::FromARGB(255, 64, 224, 208);
	const Color Color::Violet = Color::FromARGB(255, 238, 130, 238);
	const Color Color::Wheat = Color::FromARGB(255, 245, 222, 179);
	const Color Color::White = Color::FromARGB(255, 255, 255, 255);
	const Color Color::WhiteSmoke = Color::FromARGB(255, 245, 245, 245);
	const Color Color::Yellow = Color::FromARGB(255, 255, 255, 0);
	const Color Color::YellowGreen = Color::FromARGB(255, 154, 205, 50);
}