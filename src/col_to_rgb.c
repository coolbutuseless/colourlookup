


#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "hash.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Colour names as returned by "colors()"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static char *col_name[] = {
  "white", "aliceblue", "antiquewhite", "antiquewhite1", "antiquewhite2", 
  "antiquewhite3", "antiquewhite4", "aquamarine", "aquamarine1", 
  "aquamarine2", "aquamarine3", "aquamarine4", "azure", "azure1", 
  "azure2", "azure3", "azure4", "beige", "bisque", "bisque1", "bisque2", 
  "bisque3", "bisque4", "black", "blanchedalmond", "blue", "blue1", 
  "blue2", "blue3", "blue4", "blueviolet", "brown", "brown1", "brown2", 
  "brown3", "brown4", "burlywood", "burlywood1", "burlywood2", 
  "burlywood3", "burlywood4", "cadetblue", "cadetblue1", "cadetblue2", 
  "cadetblue3", "cadetblue4", "chartreuse", "chartreuse1", "chartreuse2", 
  "chartreuse3", "chartreuse4", "chocolate", "chocolate1", "chocolate2", 
  "chocolate3", "chocolate4", "coral", "coral1", "coral2", "coral3", 
  "coral4", "cornflowerblue", "cornsilk", "cornsilk1", "cornsilk2", 
  "cornsilk3", "cornsilk4", "cyan", "cyan1", "cyan2", "cyan3", 
  "cyan4", "darkblue", "darkcyan", "darkgoldenrod", "darkgoldenrod1", 
  "darkgoldenrod2", "darkgoldenrod3", "darkgoldenrod4", "darkgray", 
  "darkgreen", "darkgrey", "darkkhaki", "darkmagenta", "darkolivegreen", 
  "darkolivegreen1", "darkolivegreen2", "darkolivegreen3", "darkolivegreen4", 
  "darkorange", "darkorange1", "darkorange2", "darkorange3", "darkorange4", 
  "darkorchid", "darkorchid1", "darkorchid2", "darkorchid3", "darkorchid4", 
  "darkred", "darksalmon", "darkseagreen", "darkseagreen1", "darkseagreen2", 
  "darkseagreen3", "darkseagreen4", "darkslateblue", "darkslategray", 
  "darkslategray1", "darkslategray2", "darkslategray3", "darkslategray4", 
  "darkslategrey", "darkturquoise", "darkviolet", "deeppink", "deeppink1", 
  "deeppink2", "deeppink3", "deeppink4", "deepskyblue", "deepskyblue1", 
  "deepskyblue2", "deepskyblue3", "deepskyblue4", "dimgray", "dimgrey", 
  "dodgerblue", "dodgerblue1", "dodgerblue2", "dodgerblue3", "dodgerblue4", 
  "firebrick", "firebrick1", "firebrick2", "firebrick3", "firebrick4", 
  "floralwhite", "forestgreen", "gainsboro", "ghostwhite", "gold", 
  "gold1", "gold2", "gold3", "gold4", "goldenrod", "goldenrod1", 
  "goldenrod2", "goldenrod3", "goldenrod4", "gray", "gray0", "gray1", 
  "gray2", "gray3", "gray4", "gray5", "gray6", "gray7", "gray8", 
  "gray9", "gray10", "gray11", "gray12", "gray13", "gray14", "gray15", 
  "gray16", "gray17", "gray18", "gray19", "gray20", "gray21", "gray22", 
  "gray23", "gray24", "gray25", "gray26", "gray27", "gray28", "gray29", 
  "gray30", "gray31", "gray32", "gray33", "gray34", "gray35", "gray36", 
  "gray37", "gray38", "gray39", "gray40", "gray41", "gray42", "gray43", 
  "gray44", "gray45", "gray46", "gray47", "gray48", "gray49", "gray50", 
  "gray51", "gray52", "gray53", "gray54", "gray55", "gray56", "gray57", 
  "gray58", "gray59", "gray60", "gray61", "gray62", "gray63", "gray64", 
  "gray65", "gray66", "gray67", "gray68", "gray69", "gray70", "gray71", 
  "gray72", "gray73", "gray74", "gray75", "gray76", "gray77", "gray78", 
  "gray79", "gray80", "gray81", "gray82", "gray83", "gray84", "gray85", 
  "gray86", "gray87", "gray88", "gray89", "gray90", "gray91", "gray92", 
  "gray93", "gray94", "gray95", "gray96", "gray97", "gray98", "gray99", 
  "gray100", "green", "green1", "green2", "green3", "green4", "greenyellow", 
  "grey", "grey0", "grey1", "grey2", "grey3", "grey4", "grey5", 
  "grey6", "grey7", "grey8", "grey9", "grey10", "grey11", "grey12", 
  "grey13", "grey14", "grey15", "grey16", "grey17", "grey18", "grey19", 
  "grey20", "grey21", "grey22", "grey23", "grey24", "grey25", "grey26", 
  "grey27", "grey28", "grey29", "grey30", "grey31", "grey32", "grey33", 
  "grey34", "grey35", "grey36", "grey37", "grey38", "grey39", "grey40", 
  "grey41", "grey42", "grey43", "grey44", "grey45", "grey46", "grey47", 
  "grey48", "grey49", "grey50", "grey51", "grey52", "grey53", "grey54", 
  "grey55", "grey56", "grey57", "grey58", "grey59", "grey60", "grey61", 
  "grey62", "grey63", "grey64", "grey65", "grey66", "grey67", "grey68", 
  "grey69", "grey70", "grey71", "grey72", "grey73", "grey74", "grey75", 
  "grey76", "grey77", "grey78", "grey79", "grey80", "grey81", "grey82", 
  "grey83", "grey84", "grey85", "grey86", "grey87", "grey88", "grey89", 
  "grey90", "grey91", "grey92", "grey93", "grey94", "grey95", "grey96", 
  "grey97", "grey98", "grey99", "grey100", "honeydew", "honeydew1", 
  "honeydew2", "honeydew3", "honeydew4", "hotpink", "hotpink1", 
  "hotpink2", "hotpink3", "hotpink4", "indianred", "indianred1", 
  "indianred2", "indianred3", "indianred4", "ivory", "ivory1", 
  "ivory2", "ivory3", "ivory4", "khaki", "khaki1", "khaki2", "khaki3", 
  "khaki4", "lavender", "lavenderblush", "lavenderblush1", "lavenderblush2", 
  "lavenderblush3", "lavenderblush4", "lawngreen", "lemonchiffon", 
  "lemonchiffon1", "lemonchiffon2", "lemonchiffon3", "lemonchiffon4", 
  "lightblue", "lightblue1", "lightblue2", "lightblue3", "lightblue4", 
  "lightcoral", "lightcyan", "lightcyan1", "lightcyan2", "lightcyan3", 
  "lightcyan4", "lightgoldenrod", "lightgoldenrod1", "lightgoldenrod2", 
  "lightgoldenrod3", "lightgoldenrod4", "lightgoldenrodyellow", 
  "lightgray", "lightgreen", "lightgrey", "lightpink", "lightpink1", 
  "lightpink2", "lightpink3", "lightpink4", "lightsalmon", "lightsalmon1", 
  "lightsalmon2", "lightsalmon3", "lightsalmon4", "lightseagreen", 
  "lightskyblue", "lightskyblue1", "lightskyblue2", "lightskyblue3", 
  "lightskyblue4", "lightslateblue", "lightslategray", "lightslategrey", 
  "lightsteelblue", "lightsteelblue1", "lightsteelblue2", "lightsteelblue3", 
  "lightsteelblue4", "lightyellow", "lightyellow1", "lightyellow2", 
  "lightyellow3", "lightyellow4", "limegreen", "linen", "magenta", 
  "magenta1", "magenta2", "magenta3", "magenta4", "maroon", "maroon1", 
  "maroon2", "maroon3", "maroon4", "mediumaquamarine", "mediumblue", 
  "mediumorchid", "mediumorchid1", "mediumorchid2", "mediumorchid3", 
  "mediumorchid4", "mediumpurple", "mediumpurple1", "mediumpurple2", 
  "mediumpurple3", "mediumpurple4", "mediumseagreen", "mediumslateblue", 
  "mediumspringgreen", "mediumturquoise", "mediumvioletred", "midnightblue", 
  "mintcream", "mistyrose", "mistyrose1", "mistyrose2", "mistyrose3", 
  "mistyrose4", "moccasin", "navajowhite", "navajowhite1", "navajowhite2", 
  "navajowhite3", "navajowhite4", "navy", "navyblue", "oldlace", 
  "olivedrab", "olivedrab1", "olivedrab2", "olivedrab3", "olivedrab4", 
  "orange", "orange1", "orange2", "orange3", "orange4", "orangered", 
  "orangered1", "orangered2", "orangered3", "orangered4", "orchid", 
  "orchid1", "orchid2", "orchid3", "orchid4", "palegoldenrod", 
  "palegreen", "palegreen1", "palegreen2", "palegreen3", "palegreen4", 
  "paleturquoise", "paleturquoise1", "paleturquoise2", "paleturquoise3", 
  "paleturquoise4", "palevioletred", "palevioletred1", "palevioletred2", 
  "palevioletred3", "palevioletred4", "papayawhip", "peachpuff", 
  "peachpuff1", "peachpuff2", "peachpuff3", "peachpuff4", "peru", 
  "pink", "pink1", "pink2", "pink3", "pink4", "plum", "plum1", 
  "plum2", "plum3", "plum4", "powderblue", "purple", "purple1", 
  "purple2", "purple3", "purple4", "red", "red1", "red2", "red3", 
  "red4", "rosybrown", "rosybrown1", "rosybrown2", "rosybrown3", 
  "rosybrown4", "royalblue", "royalblue1", "royalblue2", "royalblue3", 
  "royalblue4", "saddlebrown", "salmon", "salmon1", "salmon2", 
  "salmon3", "salmon4", "sandybrown", "seagreen", "seagreen1", 
  "seagreen2", "seagreen3", "seagreen4", "seashell", "seashell1", 
  "seashell2", "seashell3", "seashell4", "sienna", "sienna1", "sienna2", 
  "sienna3", "sienna4", "skyblue", "skyblue1", "skyblue2", "skyblue3", 
  "skyblue4", "slateblue", "slateblue1", "slateblue2", "slateblue3", 
  "slateblue4", "slategray", "slategray1", "slategray2", "slategray3", 
  "slategray4", "slategrey", "snow", "snow1", "snow2", "snow3", 
  "snow4", "springgreen", "springgreen1", "springgreen2", "springgreen3", 
  "springgreen4", "steelblue", "steelblue1", "steelblue2", "steelblue3", 
  "steelblue4", "tan", "tan1", "tan2", "tan3", "tan4", "thistle", 
  "thistle1", "thistle2", "thistle3", "thistle4", "tomato", "tomato1", 
  "tomato2", "tomato3", "tomato4", "turquoise", "turquoise1", "turquoise2", 
  "turquoise3", "turquoise4", "violet", "violetred", "violetred1", 
  "violetred2", "violetred3", "violetred4", "wheat", "wheat1", 
  "wheat2", "wheat3", "wheat4", "whitesmoke", "yellow", "yellow1", 
  "yellow2", "yellow3", "yellow4", "yellowgreen"
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Actual colour values
//
// Mostly created with the following code:
//
//  mat <- t(col2rgb(colours(), alpha = TRUE))
//  apply(mat, 1, \(x) paste0("{", paste(x, collapse = ", "), "},")) |>
//  cat(sep = "\n")
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static int col_int[][4] = {
  {255, 255, 255, 255},
  {240, 248, 255, 255},
  {250, 235, 215, 255},
  {255, 239, 219, 255},
  {238, 223, 204, 255},
  {205, 192, 176, 255},
  {139, 131, 120, 255},
  {127, 255, 212, 255},
  {127, 255, 212, 255},
  {118, 238, 198, 255},
  {102, 205, 170, 255},
  {69, 139, 116, 255},
  {240, 255, 255, 255},
  {240, 255, 255, 255},
  {224, 238, 238, 255},
  {193, 205, 205, 255},
  {131, 139, 139, 255},
  {245, 245, 220, 255},
  {255, 228, 196, 255},
  {255, 228, 196, 255},
  {238, 213, 183, 255},
  {205, 183, 158, 255},
  {139, 125, 107, 255},
  {0, 0, 0, 255},
  {255, 235, 205, 255},
  {0, 0, 255, 255},
  {0, 0, 255, 255},
  {0, 0, 238, 255},
  {0, 0, 205, 255},
  {0, 0, 139, 255},
  {138, 43, 226, 255},
  {165, 42, 42, 255},
  {255, 64, 64, 255},
  {238, 59, 59, 255},
  {205, 51, 51, 255},
  {139, 35, 35, 255},
  {222, 184, 135, 255},
  {255, 211, 155, 255},
  {238, 197, 145, 255},
  {205, 170, 125, 255},
  {139, 115, 85, 255},
  {95, 158, 160, 255},
  {152, 245, 255, 255},
  {142, 229, 238, 255},
  {122, 197, 205, 255},
  {83, 134, 139, 255},
  {127, 255, 0, 255},
  {127, 255, 0, 255},
  {118, 238, 0, 255},
  {102, 205, 0, 255},
  {69, 139, 0, 255},
  {210, 105, 30, 255},
  {255, 127, 36, 255},
  {238, 118, 33, 255},
  {205, 102, 29, 255},
  {139, 69, 19, 255},
  {255, 127, 80, 255},
  {255, 114, 86, 255},
  {238, 106, 80, 255},
  {205, 91, 69, 255},
  {139, 62, 47, 255},
  {100, 149, 237, 255},
  {255, 248, 220, 255},
  {255, 248, 220, 255},
  {238, 232, 205, 255},
  {205, 200, 177, 255},
  {139, 136, 120, 255},
  {0, 255, 255, 255},
  {0, 255, 255, 255},
  {0, 238, 238, 255},
  {0, 205, 205, 255},
  {0, 139, 139, 255},
  {0, 0, 139, 255},
  {0, 139, 139, 255},
  {184, 134, 11, 255},
  {255, 185, 15, 255},
  {238, 173, 14, 255},
  {205, 149, 12, 255},
  {139, 101, 8, 255},
  {169, 169, 169, 255},
  {0, 100, 0, 255},
  {169, 169, 169, 255},
  {189, 183, 107, 255},
  {139, 0, 139, 255},
  {85, 107, 47, 255},
  {202, 255, 112, 255},
  {188, 238, 104, 255},
  {162, 205, 90, 255},
  {110, 139, 61, 255},
  {255, 140, 0, 255},
  {255, 127, 0, 255},
  {238, 118, 0, 255},
  {205, 102, 0, 255},
  {139, 69, 0, 255},
  {153, 50, 204, 255},
  {191, 62, 255, 255},
  {178, 58, 238, 255},
  {154, 50, 205, 255},
  {104, 34, 139, 255},
  {139, 0, 0, 255},
  {233, 150, 122, 255},
  {143, 188, 143, 255},
  {193, 255, 193, 255},
  {180, 238, 180, 255},
  {155, 205, 155, 255},
  {105, 139, 105, 255},
  {72, 61, 139, 255},
  {47, 79, 79, 255},
  {151, 255, 255, 255},
  {141, 238, 238, 255},
  {121, 205, 205, 255},
  {82, 139, 139, 255},
  {47, 79, 79, 255},
  {0, 206, 209, 255},
  {148, 0, 211, 255},
  {255, 20, 147, 255},
  {255, 20, 147, 255},
  {238, 18, 137, 255},
  {205, 16, 118, 255},
  {139, 10, 80, 255},
  {0, 191, 255, 255},
  {0, 191, 255, 255},
  {0, 178, 238, 255},
  {0, 154, 205, 255},
  {0, 104, 139, 255},
  {105, 105, 105, 255},
  {105, 105, 105, 255},
  {30, 144, 255, 255},
  {30, 144, 255, 255},
  {28, 134, 238, 255},
  {24, 116, 205, 255},
  {16, 78, 139, 255},
  {178, 34, 34, 255},
  {255, 48, 48, 255},
  {238, 44, 44, 255},
  {205, 38, 38, 255},
  {139, 26, 26, 255},
  {255, 250, 240, 255},
  {34, 139, 34, 255},
  {220, 220, 220, 255},
  {248, 248, 255, 255},
  {255, 215, 0, 255},
  {255, 215, 0, 255},
  {238, 201, 0, 255},
  {205, 173, 0, 255},
  {139, 117, 0, 255},
  {218, 165, 32, 255},
  {255, 193, 37, 255},
  {238, 180, 34, 255},
  {205, 155, 29, 255},
  {139, 105, 20, 255},
  {190, 190, 190, 255},
  {0, 0, 0, 255},
  {3, 3, 3, 255},
  {5, 5, 5, 255},
  {8, 8, 8, 255},
  {10, 10, 10, 255},
  {13, 13, 13, 255},
  {15, 15, 15, 255},
  {18, 18, 18, 255},
  {20, 20, 20, 255},
  {23, 23, 23, 255},
  {26, 26, 26, 255},
  {28, 28, 28, 255},
  {31, 31, 31, 255},
  {33, 33, 33, 255},
  {36, 36, 36, 255},
  {38, 38, 38, 255},
  {41, 41, 41, 255},
  {43, 43, 43, 255},
  {46, 46, 46, 255},
  {48, 48, 48, 255},
  {51, 51, 51, 255},
  {54, 54, 54, 255},
  {56, 56, 56, 255},
  {59, 59, 59, 255},
  {61, 61, 61, 255},
  {64, 64, 64, 255},
  {66, 66, 66, 255},
  {69, 69, 69, 255},
  {71, 71, 71, 255},
  {74, 74, 74, 255},
  {77, 77, 77, 255},
  {79, 79, 79, 255},
  {82, 82, 82, 255},
  {84, 84, 84, 255},
  {87, 87, 87, 255},
  {89, 89, 89, 255},
  {92, 92, 92, 255},
  {94, 94, 94, 255},
  {97, 97, 97, 255},
  {99, 99, 99, 255},
  {102, 102, 102, 255},
  {105, 105, 105, 255},
  {107, 107, 107, 255},
  {110, 110, 110, 255},
  {112, 112, 112, 255},
  {115, 115, 115, 255},
  {117, 117, 117, 255},
  {120, 120, 120, 255},
  {122, 122, 122, 255},
  {125, 125, 125, 255},
  {127, 127, 127, 255},
  {130, 130, 130, 255},
  {133, 133, 133, 255},
  {135, 135, 135, 255},
  {138, 138, 138, 255},
  {140, 140, 140, 255},
  {143, 143, 143, 255},
  {145, 145, 145, 255},
  {148, 148, 148, 255},
  {150, 150, 150, 255},
  {153, 153, 153, 255},
  {156, 156, 156, 255},
  {158, 158, 158, 255},
  {161, 161, 161, 255},
  {163, 163, 163, 255},
  {166, 166, 166, 255},
  {168, 168, 168, 255},
  {171, 171, 171, 255},
  {173, 173, 173, 255},
  {176, 176, 176, 255},
  {179, 179, 179, 255},
  {181, 181, 181, 255},
  {184, 184, 184, 255},
  {186, 186, 186, 255},
  {189, 189, 189, 255},
  {191, 191, 191, 255},
  {194, 194, 194, 255},
  {196, 196, 196, 255},
  {199, 199, 199, 255},
  {201, 201, 201, 255},
  {204, 204, 204, 255},
  {207, 207, 207, 255},
  {209, 209, 209, 255},
  {212, 212, 212, 255},
  {214, 214, 214, 255},
  {217, 217, 217, 255},
  {219, 219, 219, 255},
  {222, 222, 222, 255},
  {224, 224, 224, 255},
  {227, 227, 227, 255},
  {229, 229, 229, 255},
  {232, 232, 232, 255},
  {235, 235, 235, 255},
  {237, 237, 237, 255},
  {240, 240, 240, 255},
  {242, 242, 242, 255},
  {245, 245, 245, 255},
  {247, 247, 247, 255},
  {250, 250, 250, 255},
  {252, 252, 252, 255},
  {255, 255, 255, 255},
  {0, 255, 0, 255},
  {0, 255, 0, 255},
  {0, 238, 0, 255},
  {0, 205, 0, 255},
  {0, 139, 0, 255},
  {173, 255, 47, 255},
  {190, 190, 190, 255},
  {0, 0, 0, 255},
  {3, 3, 3, 255},
  {5, 5, 5, 255},
  {8, 8, 8, 255},
  {10, 10, 10, 255},
  {13, 13, 13, 255},
  {15, 15, 15, 255},
  {18, 18, 18, 255},
  {20, 20, 20, 255},
  {23, 23, 23, 255},
  {26, 26, 26, 255},
  {28, 28, 28, 255},
  {31, 31, 31, 255},
  {33, 33, 33, 255},
  {36, 36, 36, 255},
  {38, 38, 38, 255},
  {41, 41, 41, 255},
  {43, 43, 43, 255},
  {46, 46, 46, 255},
  {48, 48, 48, 255},
  {51, 51, 51, 255},
  {54, 54, 54, 255},
  {56, 56, 56, 255},
  {59, 59, 59, 255},
  {61, 61, 61, 255},
  {64, 64, 64, 255},
  {66, 66, 66, 255},
  {69, 69, 69, 255},
  {71, 71, 71, 255},
  {74, 74, 74, 255},
  {77, 77, 77, 255},
  {79, 79, 79, 255},
  {82, 82, 82, 255},
  {84, 84, 84, 255},
  {87, 87, 87, 255},
  {89, 89, 89, 255},
  {92, 92, 92, 255},
  {94, 94, 94, 255},
  {97, 97, 97, 255},
  {99, 99, 99, 255},
  {102, 102, 102, 255},
  {105, 105, 105, 255},
  {107, 107, 107, 255},
  {110, 110, 110, 255},
  {112, 112, 112, 255},
  {115, 115, 115, 255},
  {117, 117, 117, 255},
  {120, 120, 120, 255},
  {122, 122, 122, 255},
  {125, 125, 125, 255},
  {127, 127, 127, 255},
  {130, 130, 130, 255},
  {133, 133, 133, 255},
  {135, 135, 135, 255},
  {138, 138, 138, 255},
  {140, 140, 140, 255},
  {143, 143, 143, 255},
  {145, 145, 145, 255},
  {148, 148, 148, 255},
  {150, 150, 150, 255},
  {153, 153, 153, 255},
  {156, 156, 156, 255},
  {158, 158, 158, 255},
  {161, 161, 161, 255},
  {163, 163, 163, 255},
  {166, 166, 166, 255},
  {168, 168, 168, 255},
  {171, 171, 171, 255},
  {173, 173, 173, 255},
  {176, 176, 176, 255},
  {179, 179, 179, 255},
  {181, 181, 181, 255},
  {184, 184, 184, 255},
  {186, 186, 186, 255},
  {189, 189, 189, 255},
  {191, 191, 191, 255},
  {194, 194, 194, 255},
  {196, 196, 196, 255},
  {199, 199, 199, 255},
  {201, 201, 201, 255},
  {204, 204, 204, 255},
  {207, 207, 207, 255},
  {209, 209, 209, 255},
  {212, 212, 212, 255},
  {214, 214, 214, 255},
  {217, 217, 217, 255},
  {219, 219, 219, 255},
  {222, 222, 222, 255},
  {224, 224, 224, 255},
  {227, 227, 227, 255},
  {229, 229, 229, 255},
  {232, 232, 232, 255},
  {235, 235, 235, 255},
  {237, 237, 237, 255},
  {240, 240, 240, 255},
  {242, 242, 242, 255},
  {245, 245, 245, 255},
  {247, 247, 247, 255},
  {250, 250, 250, 255},
  {252, 252, 252, 255},
  {255, 255, 255, 255},
  {240, 255, 240, 255},
  {240, 255, 240, 255},
  {224, 238, 224, 255},
  {193, 205, 193, 255},
  {131, 139, 131, 255},
  {255, 105, 180, 255},
  {255, 110, 180, 255},
  {238, 106, 167, 255},
  {205, 96, 144, 255},
  {139, 58, 98, 255},
  {205, 92, 92, 255},
  {255, 106, 106, 255},
  {238, 99, 99, 255},
  {205, 85, 85, 255},
  {139, 58, 58, 255},
  {255, 255, 240, 255},
  {255, 255, 240, 255},
  {238, 238, 224, 255},
  {205, 205, 193, 255},
  {139, 139, 131, 255},
  {240, 230, 140, 255},
  {255, 246, 143, 255},
  {238, 230, 133, 255},
  {205, 198, 115, 255},
  {139, 134, 78, 255},
  {230, 230, 250, 255},
  {255, 240, 245, 255},
  {255, 240, 245, 255},
  {238, 224, 229, 255},
  {205, 193, 197, 255},
  {139, 131, 134, 255},
  {124, 252, 0, 255},
  {255, 250, 205, 255},
  {255, 250, 205, 255},
  {238, 233, 191, 255},
  {205, 201, 165, 255},
  {139, 137, 112, 255},
  {173, 216, 230, 255},
  {191, 239, 255, 255},
  {178, 223, 238, 255},
  {154, 192, 205, 255},
  {104, 131, 139, 255},
  {240, 128, 128, 255},
  {224, 255, 255, 255},
  {224, 255, 255, 255},
  {209, 238, 238, 255},
  {180, 205, 205, 255},
  {122, 139, 139, 255},
  {238, 221, 130, 255},
  {255, 236, 139, 255},
  {238, 220, 130, 255},
  {205, 190, 112, 255},
  {139, 129, 76, 255},
  {250, 250, 210, 255},
  {211, 211, 211, 255},
  {144, 238, 144, 255},
  {211, 211, 211, 255},
  {255, 182, 193, 255},
  {255, 174, 185, 255},
  {238, 162, 173, 255},
  {205, 140, 149, 255},
  {139, 95, 101, 255},
  {255, 160, 122, 255},
  {255, 160, 122, 255},
  {238, 149, 114, 255},
  {205, 129, 98, 255},
  {139, 87, 66, 255},
  {32, 178, 170, 255},
  {135, 206, 250, 255},
  {176, 226, 255, 255},
  {164, 211, 238, 255},
  {141, 182, 205, 255},
  {96, 123, 139, 255},
  {132, 112, 255, 255},
  {119, 136, 153, 255},
  {119, 136, 153, 255},
  {176, 196, 222, 255},
  {202, 225, 255, 255},
  {188, 210, 238, 255},
  {162, 181, 205, 255},
  {110, 123, 139, 255},
  {255, 255, 224, 255},
  {255, 255, 224, 255},
  {238, 238, 209, 255},
  {205, 205, 180, 255},
  {139, 139, 122, 255},
  {50, 205, 50, 255},
  {250, 240, 230, 255},
  {255, 0, 255, 255},
  {255, 0, 255, 255},
  {238, 0, 238, 255},
  {205, 0, 205, 255},
  {139, 0, 139, 255},
  {176, 48, 96, 255},
  {255, 52, 179, 255},
  {238, 48, 167, 255},
  {205, 41, 144, 255},
  {139, 28, 98, 255},
  {102, 205, 170, 255},
  {0, 0, 205, 255},
  {186, 85, 211, 255},
  {224, 102, 255, 255},
  {209, 95, 238, 255},
  {180, 82, 205, 255},
  {122, 55, 139, 255},
  {147, 112, 219, 255},
  {171, 130, 255, 255},
  {159, 121, 238, 255},
  {137, 104, 205, 255},
  {93, 71, 139, 255},
  {60, 179, 113, 255},
  {123, 104, 238, 255},
  {0, 250, 154, 255},
  {72, 209, 204, 255},
  {199, 21, 133, 255},
  {25, 25, 112, 255},
  {245, 255, 250, 255},
  {255, 228, 225, 255},
  {255, 228, 225, 255},
  {238, 213, 210, 255},
  {205, 183, 181, 255},
  {139, 125, 123, 255},
  {255, 228, 181, 255},
  {255, 222, 173, 255},
  {255, 222, 173, 255},
  {238, 207, 161, 255},
  {205, 179, 139, 255},
  {139, 121, 94, 255},
  {0, 0, 128, 255},
  {0, 0, 128, 255},
  {253, 245, 230, 255},
  {107, 142, 35, 255},
  {192, 255, 62, 255},
  {179, 238, 58, 255},
  {154, 205, 50, 255},
  {105, 139, 34, 255},
  {255, 165, 0, 255},
  {255, 165, 0, 255},
  {238, 154, 0, 255},
  {205, 133, 0, 255},
  {139, 90, 0, 255},
  {255, 69, 0, 255},
  {255, 69, 0, 255},
  {238, 64, 0, 255},
  {205, 55, 0, 255},
  {139, 37, 0, 255},
  {218, 112, 214, 255},
  {255, 131, 250, 255},
  {238, 122, 233, 255},
  {205, 105, 201, 255},
  {139, 71, 137, 255},
  {238, 232, 170, 255},
  {152, 251, 152, 255},
  {154, 255, 154, 255},
  {144, 238, 144, 255},
  {124, 205, 124, 255},
  {84, 139, 84, 255},
  {175, 238, 238, 255},
  {187, 255, 255, 255},
  {174, 238, 238, 255},
  {150, 205, 205, 255},
  {102, 139, 139, 255},
  {219, 112, 147, 255},
  {255, 130, 171, 255},
  {238, 121, 159, 255},
  {205, 104, 137, 255},
  {139, 71, 93, 255},
  {255, 239, 213, 255},
  {255, 218, 185, 255},
  {255, 218, 185, 255},
  {238, 203, 173, 255},
  {205, 175, 149, 255},
  {139, 119, 101, 255},
  {205, 133, 63, 255},
  {255, 192, 203, 255},
  {255, 181, 197, 255},
  {238, 169, 184, 255},
  {205, 145, 158, 255},
  {139, 99, 108, 255},
  {221, 160, 221, 255},
  {255, 187, 255, 255},
  {238, 174, 238, 255},
  {205, 150, 205, 255},
  {139, 102, 139, 255},
  {176, 224, 230, 255},
  {160, 32, 240, 255},
  {155, 48, 255, 255},
  {145, 44, 238, 255},
  {125, 38, 205, 255},
  {85, 26, 139, 255},
  {255, 0, 0, 255},
  {255, 0, 0, 255},
  {238, 0, 0, 255},
  {205, 0, 0, 255},
  {139, 0, 0, 255},
  {188, 143, 143, 255},
  {255, 193, 193, 255},
  {238, 180, 180, 255},
  {205, 155, 155, 255},
  {139, 105, 105, 255},
  {65, 105, 225, 255},
  {72, 118, 255, 255},
  {67, 110, 238, 255},
  {58, 95, 205, 255},
  {39, 64, 139, 255},
  {139, 69, 19, 255},
  {250, 128, 114, 255},
  {255, 140, 105, 255},
  {238, 130, 98, 255},
  {205, 112, 84, 255},
  {139, 76, 57, 255},
  {244, 164, 96, 255},
  {46, 139, 87, 255},
  {84, 255, 159, 255},
  {78, 238, 148, 255},
  {67, 205, 128, 255},
  {46, 139, 87, 255},
  {255, 245, 238, 255},
  {255, 245, 238, 255},
  {238, 229, 222, 255},
  {205, 197, 191, 255},
  {139, 134, 130, 255},
  {160, 82, 45, 255},
  {255, 130, 71, 255},
  {238, 121, 66, 255},
  {205, 104, 57, 255},
  {139, 71, 38, 255},
  {135, 206, 235, 255},
  {135, 206, 255, 255},
  {126, 192, 238, 255},
  {108, 166, 205, 255},
  {74, 112, 139, 255},
  {106, 90, 205, 255},
  {131, 111, 255, 255},
  {122, 103, 238, 255},
  {105, 89, 205, 255},
  {71, 60, 139, 255},
  {112, 128, 144, 255},
  {198, 226, 255, 255},
  {185, 211, 238, 255},
  {159, 182, 205, 255},
  {108, 123, 139, 255},
  {112, 128, 144, 255},
  {255, 250, 250, 255},
  {255, 250, 250, 255},
  {238, 233, 233, 255},
  {205, 201, 201, 255},
  {139, 137, 137, 255},
  {0, 255, 127, 255},
  {0, 255, 127, 255},
  {0, 238, 118, 255},
  {0, 205, 102, 255},
  {0, 139, 69, 255},
  {70, 130, 180, 255},
  {99, 184, 255, 255},
  {92, 172, 238, 255},
  {79, 148, 205, 255},
  {54, 100, 139, 255},
  {210, 180, 140, 255},
  {255, 165, 79, 255},
  {238, 154, 73, 255},
  {205, 133, 63, 255},
  {139, 90, 43, 255},
  {216, 191, 216, 255},
  {255, 225, 255, 255},
  {238, 210, 238, 255},
  {205, 181, 205, 255},
  {139, 123, 139, 255},
  {255, 99, 71, 255},
  {255, 99, 71, 255},
  {238, 92, 66, 255},
  {205, 79, 57, 255},
  {139, 54, 38, 255},
  {64, 224, 208, 255},
  {0, 245, 255, 255},
  {0, 229, 238, 255},
  {0, 197, 205, 255},
  {0, 134, 139, 255},
  {238, 130, 238, 255},
  {208, 32, 144, 255},
  {255, 62, 150, 255},
  {238, 58, 140, 255},
  {205, 50, 120, 255},
  {139, 34, 82, 255},
  {245, 222, 179, 255},
  {255, 231, 186, 255},
  {238, 216, 174, 255},
  {205, 186, 150, 255},
  {139, 126, 102, 255},
  {245, 245, 245, 255},
  {255, 255, 0, 255},
  {255, 255, 0, 255},
  {238, 238, 0, 255},
  {205, 205, 0, 255},
  {139, 139, 0, 255},
  {154, 205, 50, 255}
}; 



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This is a bit rough.  Doesn't raise an error if the supposed hexdigit
// is something stupid e.g. "#1122qq"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define hex2int(s) ((s) <= '9') ? (s) - '0' : ((s) & 0x7) + 9;


SEXP col_to_rgb_(SEXP cols_) {
  
  int n = LENGTH(cols_);
  
  /* First set up the output matrix */
  SEXP res_        = PROTECT(allocMatrix(INTSXP, 4, n));
  SEXP dim_names_  = PROTECT(allocVector(VECSXP, 2));
  SEXP names_      = PROTECT(allocVector(STRSXP, 4));
  SET_STRING_ELT(names_, 0, mkChar("red"));
  SET_STRING_ELT(names_, 1, mkChar("green"));
  SET_STRING_ELT(names_, 2, mkChar("blue"));
  SET_STRING_ELT(names_, 3, mkChar("alpha"));
  SET_VECTOR_ELT(dim_names_, 0, names_);
  setAttrib(res_, R_DimNamesSymbol, dim_names_);
  
  int *ptr = INTEGER(res_);
  
  for(int i = 0; i < n; i++) {
    const char *str = CHAR(STRING_ELT(cols_, i));
    
    if (str[0] == '#') {
      switch(strlen(str)) {
      case 9: {
      int a, b;
      str++; a = hex2int(*str); 
      str++; b = hex2int(*str);
      *ptr++ = (a << 4) + b;
      
      str++; a = hex2int(*str); 
      str++; b = hex2int(*str);
      *ptr++ = (a << 4) + b;
      
      str++; a = hex2int(*str); 
      str++; b = hex2int(*str);
      *ptr++ = (a << 4) + b;
      
      str++; a = hex2int(*str); 
      str++; b = hex2int(*str);
      *ptr++ = (a << 4) + b;
    }
        break;
      case 7: {
        int a, b;
        str++; a = hex2int(*str); 
        str++; b = hex2int(*str);
        *ptr++ = (a << 4) + b;
        
        str++; a = hex2int(*str); 
        str++; b = hex2int(*str);
        *ptr++ = (a << 4) + b;
        
        str++; a = hex2int(*str); 
        str++; b = hex2int(*str);
        *ptr++ = (a << 4) + b;
        
        *ptr++ = 0;
      }
        break;
      case 5: {
        int a;
        str++; a = hex2int(*str); 
        *ptr++ = (a << 4) + a;
        
        str++; a = hex2int(*str); 
        *ptr++ = (a << 4) + a;
        
        str++; a = hex2int(*str); 
        *ptr++ = (a << 4)  + a;
        
        str++; a = hex2int(*str); 
        *ptr++ = (a << 4)  + a;
      }
        break;
      case 4: {
        int a;
        str++; a = hex2int(*str); 
        *ptr++ = (a << 4) + a;
        
        str++; a = hex2int(*str); 
        *ptr++ = (a << 4) + a;
        
        str++; a = hex2int(*str); 
        *ptr++ = (a << 4)  + a;
        
        *ptr++ = 0;
      }
        break;
      default:
        error("Unhandled hex notation for: %s", str);
      }
    } else {
      
      int idx = hash((const unsigned char *)str);
      // don't need to do a full string comparison, as the probability of
      // an incorrect colour name (e.g. 'bluexx') hashing to a colour
      // that starts with 'blu' seems incredibly remote.  
      // Probably worth testing though to figure out what is needed to 
      // actually cause a collision here. (and how much of the strings should
      // be compared to detect it)
      if (idx < 0 || idx > 656 || memcmp(str, col_name[idx], 3) != 0) {
        error("Not a valid colour name: %s", str);
      }
      int *icol = col_int[idx];
      *ptr++ = *icol++;
      *ptr++ = *icol++;
      *ptr++ = *icol++;
      *ptr++ = *icol;
    }
  }
  UNPROTECT(3);
  
  return res_;
}
