#pragma once

#include "../core/cartridge.hh"
#include <cstdint>
#include <map>

enum class NewLicensee : uint8_t
{
    None = 0x00,
    Nintendo1 = 0x01,
    Capcom = 0x08,
    Ea1 = 0x13,
    HudsonSoft = 0x18,
    Bai = 0x19,
    Kss = 0x20,
    Pow = 0x22,
    PcmComplete = 0x24,
    Sanx = 0x25,
    Kemco = 0x28,
    Seta = 0x29,
    Viacom = 0x30,
    Nintendo2 = 0x31,
    Bandai = 0x32,
    OceanAcclaim1 = 0x33,
    Konami1 = 0x34,
    Hector = 0x35,
    Taito = 0x37,
    Hudson = 0x38,
    Banpresto = 0x39,
    Ubisoft = 0x41,
    Atlus = 0x42,
    Malibu = 0x44,
    Angel = 0x46,
    BulletProof = 0x47,
    Irem = 0x49,
    Absolute = 0x50,
    Acclaim = 0x51,
    Activision = 0x52,
    AmericanSammy = 0x53,
    Konami2 = 0x54,
    HiTechExpressions = 0x55,
    Ljn = 0x56,
    Matchbox = 0x57,
    Mattel = 0x58,
    MiltonBradley = 0x59,
    Titus = 0x60,
    Virgin = 0x61,
    LucasArts = 0x64,
    Ocean = 0x67,
    Ea2 = 0x69,
    Infogrames = 0x70,
    Interplay = 0x71,
    Broderbund = 0x72,
    Sculptured = 0x73,
    Sci = 0x75,
    Thq = 0x78,
    Accolade = 0x79,
    Misawa = 0x80,
    Lozc = 0x83,
    TokumaShotenIntermedia = 0x86,
    Tsukuda = 0x87,
    Chunsoft = 0x91,
    VideoSystem = 0x92,
    OceanAcclaim2 = 0x93,
    Varie = 0x95,
    YonezawasPal = 0x96,
    Kaneko = 0x97,
    PackInVideo = 0x99,
    Konami3 = 0xA4
};

enum class OldLicensee
{
    None = 0x00,
    Nintendo1 = 0x01,
    Capcom1 = 0x08,
    Hotb = 0x09,
    Jaleco1 = 0x0A,
    Coconuts = 0x0B,
    EliteSystems = 0x0C,
    Ea1 = 0x13,
    HudsonSoft = 0x18,
    ItcEntertainment = 0x19,
    Yanoman = 0x1A,
    Clary = 0x1D,
    Virgin1 = 0x1F,
    Kss = 0x20,
    PcmComplete = 0x24,
    Sanx = 0x25,
    KotobukiSystems = 0x28,
    Seta = 0x29,
    Infogrames = 0x30,
    Nintendo2 = 0x31,
    Bandai1 = 0x32,
    Invalid = 0x33,
    Konami1 = 0x34,
    Hector = 0x35,
    Capcom2 = 0x38,
    Banpresto1 = 0x39,
    EntertainmentI = 0x3C,
    Gremlin = 0x3E,
    Ubisoft = 0x41,
    Atlus1 = 0x42,
    Malibu1 = 0x44,
    Angel1 = 0x46,
    SpectrumHolobyte = 0x47,
    Irem = 0x49,
    Virgin2 = 0x4A,
    Malibu2 = 0x4D,
    UsGold = 0x4F,
    Absolute = 0x50,
    Acclaim1 = 0x51,
    Activision = 0x52,
    AmericanSammy = 0x53,
    Gametek = 0x54,
    ParkPlace = 0x55,
    Ljn1 = 0x56,
    Matchbox = 0x57,
    MiltonBradley = 0x59,
    Mindscape = 0x5A,
    Romstar = 0x5B,
    NaxatSoft1 = 0x5C,
    Tradewest = 0x5D,
    Titus = 0x60,
    Virgin3 = 0x61,
    Ocean = 0x67,
    Ea2 = 0x69,
    EliteSystems2 = 0x6E,
    ElectroBrain = 0x6F,
    Infogrames2 = 0x70,
    Interplay = 0x71,
    Broderbund1 = 0x72,
    SculpturedSoft = 0x73,
    TheSalesCurve = 0x75,
    Thq = 0x78,
    Accolade = 0x79,
    TriffixEntertainment = 0x7A,
    Microprose = 0x7C,
    Kemco1 = 0x7F,
    MisawaEntertainment = 0x80,
    Lozc = 0x83,
    TokumaShotenIntermedia1 = 0x86,
    BulletproofSoftware = 0x8B,
    VicTokai = 0x8C,
    Ape = 0x8E,
    Imax = 0x8F,
    Chunsoft = 0x91,
    VideoSystem = 0x92,
    Tsuburaya = 0x93,
    Varie1 = 0x95,
    YonezawasPal = 0x96,
    Kaneko = 0x97,
    Arc = 0x99,
    NihonBussan = 0x9A,
    Tecmo = 0x9B,
    Imagineering = 0x9C,
    Banpresto2 = 0x90,
    Nova = 0x9F,
    HoriElectric = 0xA1,
    Bandai2 = 0xA2,
    Konami = 0xA4,
    Kawada = 0xA6,
    Takara = 0xA7,
    TechnosJapan = 0xA9,
    Broderbund2 = 0xAA,
    ToeiAnimation = 0xAC,
    Toho = 0xA9,
    Namco = 0xAF,
    Acclaim2 = 0xB0,
    AsciiOrNexoft = 0xB1,
    Bandai3 = 0xB2,
    Enix = 0xB4,
    Hal = 0xB6,
    Snk = 0xB7,
    PonyCanyon1 = 0xB9,
    CultureBrain = 0xBA,
    Sunsoft = 0xBB,
    SonyImagesoft = 0xBD,
    Sammy = 0xBF,
    Taito1 = 0xC0,
    Kemco2 = 0xC2,
    Square = 0xC3,
    TokumaShotenIntermedia2 = 0xC4,
    DataEast = 0xC5,
    TonkinHouse = 0xC6,
    Koei = 0xC8,
    Ufl = 0xC9,
    Ultra = 0xCA,
    Vap = 0xCB,
    Use = 0xCC,
    Meldac = 0xCD,
    PonyCanyon2 = 0xCE,
    Angel2 = 0xCF,
    Taito2 = 0xD0,
    Sofel = 0xD1,
    Quest = 0xD2,
    SigmaEnterprises = 0xD3,
    AskKodansha = 0xD4,
    NaxatSoft2 = 0xD6,
    CopyaSystem = 0xD7,
    Banpresto3 = 0xD9,
    Tomy = 0xDA,
    Ljn2 = 0xD8,
    Ncs = 0xDD,
    Human = 0xDE,
    Altron = 0xDF,
    Jaleco2 = 0xE0,
    TowaChiki = 0xE1,
    Yutaka = 0xE2,
    Varie2 = 0xE3,
    Epoch = 0xE5,
    Athena = 0xE7,
    Asmik = 0xE8,
    Natsume = 0xE9,
    KingRecords = 0xEA,
    Atlus2 = 0xEB,
    EpicSonyRecords = 0xEC,
    Igs = 0xEE,
    AWave = 0xF0,
    ExtremeEntertainment = 0xF3,
    Ljn3 = 0xFF
};

static const std::map<OldLicensee, std::string> OLD_LICENSEE =
{
    {OldLicensee::None , "-"},
    {OldLicensee::Nintendo1 , "Nintendo"},
    {OldLicensee::Capcom1 , "Capcom"},
    {OldLicensee::Hotb , ""}, //
    {OldLicensee::Jaleco1 , "Jaleco"},
    {OldLicensee::Coconuts , "Coconuts"},
    {OldLicensee::EliteSystems , "Elite Systems"},
    {OldLicensee::Ea1 , "Electronic Arts"},
    {OldLicensee::HudsonSoft , "Hudson Soft"},
    {OldLicensee::ItcEntertainment , "ITC Entertainment"},
    {OldLicensee::Yanoman , "Yanoman"},
    {OldLicensee::Clary , "Clary"},
    {OldLicensee::Virgin1 , "Virgin"},
    {OldLicensee::Kss , "KSS"},
    {OldLicensee::PcmComplete , "PCM"},
    {OldLicensee::Sanx , "San-X"},
    {OldLicensee::KotobukiSystems , "Kotobuki"},
    {OldLicensee::Seta , "SETA"},
    {OldLicensee::Infogrames , "Infogrames"},
    {OldLicensee::Nintendo2 , "Nintendo"},
    {OldLicensee::Bandai1 , "Bandai"},
    {OldLicensee::Invalid , "!!!INVALID!!!"},
    {OldLicensee::Konami1 , "Konami"},
    {OldLicensee::Hector , "Hector"},
    {OldLicensee::Capcom2 , "Capcom"},
    {OldLicensee::Banpresto1 , "Banpresto"},
    {OldLicensee::EntertainmentI , "???"},
    {OldLicensee::Gremlin , "Gremlin"},
    {OldLicensee::Ubisoft , "Ubisoft"},
    {OldLicensee::Atlus1 , "Atlus"},
    {OldLicensee::Malibu1 , "Malibu"},
    {OldLicensee::Angel1 , "Angel"},
    {OldLicensee::SpectrumHolobyte , "Spectrum Holobyte"},
    {OldLicensee::Irem , "Irem"},
    {OldLicensee::Virgin2 , "Virgin"},
    {OldLicensee::Malibu2 , "Malibu"},
    {OldLicensee::UsGold , "U.S. Gold"},
    {OldLicensee::Absolute , "Absolute"},
    {OldLicensee::Acclaim1 , "Acclaim"},
    {OldLicensee::Activision , "Activision"},
    {OldLicensee::AmericanSammy , "American Sammy"},
    {OldLicensee::Gametek , "GameTek"},
    {OldLicensee::ParkPlace , "Park Place"},
    {OldLicensee::Ljn1 , "LJN"},
    {OldLicensee::Matchbox , "Matchbox"},
    {OldLicensee::MiltonBradley , "Milton Bradley"},
    {OldLicensee:: Mindscape , "Mindscape"},
    {OldLicensee::Romstar , "Romstar"},
    {OldLicensee::NaxatSoft1 , "Naxat Soft"},
    {OldLicensee::Tradewest , "Tradewest"},
    {OldLicensee::Titus , "Titus"},
    {OldLicensee::Virgin3 , "Virgin"},
    {OldLicensee::Ocean , "Ocean"},
    {OldLicensee::Ea2 , "Electronic Arts"},
    {OldLicensee::EliteSystems2 , "Elite Systems"},
    {OldLicensee::ElectroBrain , "Electro Brain"},
    {OldLicensee::Infogrames2 , "Infogrames"},
    {OldLicensee::Interplay , "Interplay"},
    {OldLicensee::Broderbund1 , "Broderbund"},
    {OldLicensee::SculpturedSoft , "Sculptured"},
    {OldLicensee::TheSalesCurve , "The Sales Curve"},
    {OldLicensee::Thq , "THQ"},
    {OldLicensee::Accolade , "Accolade"},
    {OldLicensee::TriffixEntertainment , "Triffix"},
    {OldLicensee::Microprose , "MicroProse"},
    {OldLicensee::Kemco1 , "Kemco"},
    {OldLicensee::MisawaEntertainment , "Misawa"},
    {OldLicensee::Lozc , "LOZC"},
    {OldLicensee::TokumaShotenIntermedia1 , "Tokuma Shoten"},
    {OldLicensee::BulletproofSoftware , "Bullet-Proof Software"},
    {OldLicensee::VicTokai , "Vic Tokai"},
    {OldLicensee::Ape , "Ape Inc."},
    {OldLicensee::Imax , "I'Max"},
    {OldLicensee::Chunsoft , "Chunsoft"},
    {OldLicensee::VideoSystem , "Video System"},
    {OldLicensee::Tsuburaya , "Tsuburaya"},
    {OldLicensee::Varie1 , "Varie"},
    {OldLicensee::YonezawasPal , "Yonezawa PR21"},
    {OldLicensee::Kaneko , "Kaneko"},
    {OldLicensee::Arc , "Arc System Works???"},
    {OldLicensee::NihonBussan , "Nihon Bussan"},
    {OldLicensee::Tecmo , "Koei Tecmo"},
    {OldLicensee::Imagineering , "Imagineering"},
    {OldLicensee::Banpresto2 , "Banpresto"},
    {OldLicensee::Nova , "Nova Games"},
    {OldLicensee::HoriElectric , "Hori Electric"},
    {OldLicensee::Bandai2, "Bandai"},
    {OldLicensee::Konami, "Konami"},
    {OldLicensee::Kawada, "Kawada"},
    {OldLicensee::Takara, "Takara"},
    {OldLicensee::TechnosJapan, "Technōs Japan"},
    {OldLicensee::Broderbund2, "Broderbund"},
    {OldLicensee::ToeiAnimation, "Toei Animation"},
    {OldLicensee::Toho, "Toho"},
    {OldLicensee::Namco, "Namco"},
    {OldLicensee::Acclaim2, "Acclaim"},
    {OldLicensee::AsciiOrNexoft, "ASCII Corp./Nexoft"},
    {OldLicensee::Bandai3, "Bandai"},
    {OldLicensee::Enix, "Enix"},
    {OldLicensee::Hal, "HAL Laboratory"},
    {OldLicensee::Snk, "SNK"},
    {OldLicensee::PonyCanyon1, "Pony Canyon"},
    {OldLicensee::CultureBrain, "Culture Brain"},
    {OldLicensee::Sunsoft, "Sunsoft"},
    {OldLicensee::SonyImagesoft, "Sony Imagesoft"},
    {OldLicensee::Sammy, "Sammy Corporation"},
    {OldLicensee::Taito1, "Taito"},
    {OldLicensee::Kemco2, "Kemco"},
    {OldLicensee::Square, "Square"},
    {OldLicensee::TokumaShotenIntermedia2, "Tokuma Shoten"},
    {OldLicensee::DataEast, "Data East"},
    {OldLicensee::TonkinHouse, "Tonkin House"},
    {OldLicensee::Koei, "Koei"},
    {OldLicensee::Ufl, "UFL???"},
    {OldLicensee::Ultra, "Ultra Games"},
    {OldLicensee::Vap, "VAP"},
    {OldLicensee::Use, "Use Corporation"},
    {OldLicensee::Meldac, "Meldac"},
    {OldLicensee::PonyCanyon2, "Pony Canyon"},
    {OldLicensee::Angel2, "Angel"},
    {OldLicensee::Taito2, "Taito"},
    {OldLicensee::Sofel, "SOFEL"},
    {OldLicensee::Quest, "Quest"},
    {OldLicensee::SigmaEnterprises, "Sigma Enterprises"},
    {OldLicensee::AskKodansha, "Ask Kodansha"},
    {OldLicensee::NaxatSoft2, "Naxat Soft"},
    {OldLicensee::CopyaSystem, "Copya System"},
    {OldLicensee::Banpresto3, "Banpresto"},
    {OldLicensee::Tomy, "Tomy"},
    {OldLicensee::Ljn2, "LJN"},
    {OldLicensee::Ncs, "NCS"},
    {OldLicensee::Human, "Human Entertainment"},
    {OldLicensee::Altron, "Altron"},
    {OldLicensee::Jaleco2, "Jaleco"},
    {OldLicensee::TowaChiki, "TowaChiki"},
    {OldLicensee::Yutaka, "Yutaka"},
    {OldLicensee::Varie2, "Varie"},
    {OldLicensee::Epoch, "Epoch"},
    {OldLicensee::Athena, "Athena"},
    {OldLicensee::Asmik, "Asmic Ace Entertainment"},
    {OldLicensee::Natsume, "Natsume"},
    {OldLicensee::KingRecords, "King Records"},
    {OldLicensee::Atlus2, "Atlus"},
    {OldLicensee::EpicSonyRecords, "Epic/Sony Records"},
    {OldLicensee::Igs, "IGS"},
    {OldLicensee::AWave, "A-Wave"},
    {OldLicensee::ExtremeEntertainment, "Extreme Entertainment"},
    {OldLicensee::Ljn3, "LJN"}
};

static const std::map<NewLicensee, std::string> NEW_LICENSEE =
{
    {NewLicensee::None , "-"},
    {NewLicensee::Nintendo1 , "Nintendo"},
    {NewLicensee::Capcom , "Capcom"},
    {NewLicensee::Ea1 , "Electronic Arts"},
    {NewLicensee::HudsonSoft , "Hudson Soft"},
    {NewLicensee::Bai , "B-AI"},
    {NewLicensee::Kss , "KSS"},
    {NewLicensee::Pow , "Pow"},
    {NewLicensee::PcmComplete , "PCM"},
    {NewLicensee::Sanx , "San-X"},
    {NewLicensee::Kemco , "Kemco"},
    {NewLicensee::Seta , "SETA"},
    {NewLicensee::Viacom , "Viacom"},
    {NewLicensee::Nintendo2 , "Nintendo"},
    {NewLicensee::Bandai , "Bandai"},
    {NewLicensee::OceanAcclaim1 , "Ocean/Acclaim"},
    {NewLicensee::Konami1 , "Konami"},
    {NewLicensee::Hector , "Hector"},
    {NewLicensee::Taito , "Taito"},
    {NewLicensee::Hudson , "Hudson Soft"},
    {NewLicensee::Banpresto , "Banpresto"},
    {NewLicensee::Ubisoft , "Ubisoft"},
    {NewLicensee::Atlus , "Atlus"},
    {NewLicensee::Malibu , "Malibu"},
    {NewLicensee::Angel , "Angel"},
    {NewLicensee::BulletProof , "Bullet-Proof Software"},
    {NewLicensee::Irem , "Irem"},
    {NewLicensee::Absolute , "Absolute Entertainment"},
    {NewLicensee::Acclaim , "Acclaim"},
    {NewLicensee::Activision , "Activision"},
    {NewLicensee::AmericanSammy , "American Sammy"},
    {NewLicensee::Konami2 , "Konami"},
    {NewLicensee::HiTechExpressions , "Hi Tech Expressions"},
    {NewLicensee::Ljn , "LJN"},
    {NewLicensee::Matchbox , "Matchbox"},
    {NewLicensee::Mattel , "Mattel"},
    {NewLicensee::MiltonBradley , "Milton Bradley"},
    {NewLicensee::Titus , "Titus"},
    {NewLicensee::Virgin , "Virgin"},
    {NewLicensee::LucasArts , "LucasArts"},
    {NewLicensee::Ocean , "Ocean"},
    {NewLicensee::Ea2 , "Electronic Arts"},
    {NewLicensee::Infogrames , "Infogrames"},
    {NewLicensee::Interplay , "Interplay"},
    {NewLicensee::Broderbund , "Broderbund"},
    {NewLicensee::Sculptured , "Sculptured"},
    {NewLicensee::Sci , "SCI"},
    {NewLicensee::Thq , "THQ"},
    {NewLicensee::Accolade , "Accolade"},
    {NewLicensee::Misawa , "Misawa"},
    {NewLicensee::Lozc , "LOZC"},
    {NewLicensee::TokumaShotenIntermedia , "Tokuma Shoten"},
    {NewLicensee::Tsukuda , "Tsukuda"},
    {NewLicensee::Chunsoft , "Chunsoft"},
    {NewLicensee::VideoSystem , "Video System"},
    {NewLicensee::OceanAcclaim2 , "Ocean/Acclaim"},
    {NewLicensee::Varie , "Varie"},
    {NewLicensee::YonezawasPal , "Yonezawa"},
    {NewLicensee::Kaneko , "Kaneko"},
    {NewLicensee::PackInVideo , "Pack-In-Video"},
    {NewLicensee::Konami3, "Konami"}
};

static const std::map<Cartridge::CartridgeType, std::string> CART_TYPE_NAME =
{
    {Cartridge::RomOnly,
     "ROM ONLY"},
    {Cartridge::Mbc1,
     "MBC1"},
    {Cartridge::Mbc1_Ram,
     "MBC1+RAM"},
    {Cartridge::Mbc1_Ram_Battery,
     "MBC1+RAM+BATTERY"},
    {Cartridge::Mbc2,
     "MBC2"},
    {Cartridge::Mbc2_Battery,
     "MBC2+BATTERY"},
    {Cartridge::Rom_Ram,
     "ROM+RAM"},
    {Cartridge::Rom_Ram_Battery,
     "ROM+RAM+BATTERY"},
    {Cartridge::Mmm01,
     "MMM01"},
    {Cartridge::Mmm01_Ram,
     "MMM01+RAM"},
    {Cartridge::Mmm01_Ram_Battery,
     "MMM01+RAM+BATTERY"},
    {Cartridge::Mbc3_Timer_Battery,
     "MBC3+TIMER+BATTERY"},
    {Cartridge::Mbc3_Timer_Ram_Battery,
     "MBC3+TIMER+RAM+BATTERY"},
    {Cartridge::Mbc3,
     "MBC3"},
    {Cartridge::Mbc3_Ram,
     "MBC3+RAM"},
    {Cartridge::Mbc3_Ram_Battery,
     "MBC3+RAM+BATTERY"},
    {Cartridge::Mbc5,
     "MBC5"},
    {Cartridge::Mbc5_Ram,
     "MBC5+RAM"},
    {Cartridge::Mbc5_Ram_battery,
     "MBC5+RAM+BATTERY"},
    {Cartridge::Mbc5_Rumble,
     "MBC5+RUMBLE"},
    {Cartridge::Mbc5_Rumble_Ram,
     "MBC5+RUMBLE+RAM"},
    {Cartridge::Mbc5_Rumble_Ram_Battery,
     "MBC5+RUMBLE+RAM+BATTERY"},
    {Cartridge::Mbc6,
     "MBC6"},
    {Cartridge::Mbc7_Sensor_Rumble_Ram_Battery,
     "MBC7+SENSOR+RUMBLE+RAM+BATTERY"},
    {Cartridge::PocketCamera,
     "POCKET CAMERA"},
    {Cartridge::BandaiTama5,
     "BANDAI TAMA5"},
    {Cartridge::Huc3,
     "HuC3"},
    {Cartridge::HuC1_Ram_Battery,
     "HuC1+RAM+BATTERY"},
};
