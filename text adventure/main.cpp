#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <limits>
#include <map>
#include <algorithm>
#include "FanfString.h"

// ======================= Utility =========================
namespace util {
    inline int clamp_int(int v, int lo, int hi) { // no std::clamp per request
        if (v < lo) return lo;
        if (v > hi) return hi;
        return v;
    }
    inline void clear_input() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    inline int rngi(std::mt19937& rng, int lo, int hi) {
        std::uniform_int_distribution<int> d(lo, hi);
        return d(rng);
    }
    inline double rngd(std::mt19937& rng, double lo, double hi) {
        std::uniform_real_distribution<double> d(lo, hi);
        return d(rng);
    }
    inline void pause_ms(int ms) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }
}

// ================== Game Data Structures =================
enum class Room {
    Office = 0,
    ShowStage,
    PrizeCorner, // music box
    GameArea,
    LeftVent,
    RightVent,
    MainHall,
    PartyRoom1,
    PartyRoom2,
    AirDucts,
    MaxRooms
};

static const char* RoomName(Room r) {
    switch (r) {
    case Room::Office: return "Office";
    case Room::ShowStage: return "Show Stage";
    case Room::PrizeCorner: return "Prize Corner";
    case Room::GameArea: return "Game Area";
    case Room::LeftVent: return "Left Vent";
    case Room::RightVent: return "Right Vent";
    case Room::MainHall: return "Main Hall";
    case Room::PartyRoom1: return "Party Room 1";
    case Room::PartyRoom2: return "Party Room 2";
    case Room::AirDucts: return "Air Ducts";
    default: return "?";
    }
}

struct Difficulty {
    int animatronicAggression;   // base % per tick to move
    int foxyAttackChance;        // extra % if in Main Hall
    int musicBoxDrain;           // units per tick
    int cameraNoiseRisk;         // % to lure animatronics when checking cams
    int maskBlockChance;         // chance % that mask saves you
    int shiftLengthTicks;        // ticks from 12 AM to 6 AM
};

struct Animatronic {
    FanfString name;
    Room room;
    int aggBase;         // per-tick movement chance boost
    bool inOfficeKill = false; // if reached lethal state requiring mask/flash
    bool stunned = false;      // for Foxy-like stun after flashlight
    int uniqueCool = 0;        // per-animatronic cooldown (e.g., BB battery)
    bool active = true;

    bool atOffice() const { return room == Room::Office; }
};

struct MusicBox {
    int value = 100; // 0..100
    bool puppetReleased = false;
    void drain(int amt) {
        value -= amt;
        if (value < 0) value = 0;
        if (value == 0) puppetReleased = true;
    }
    void wind(int amt) {
        value += amt;
        if (value > 100) value = 100;
    }
};

struct GameState {
    Difficulty diff{};
    std::vector<Animatronic> bots;
    MusicBox box;
    bool maskOn = false;
    bool flashlight = false;
    bool powerOK = true;  // simple flag for BB trolling
    int tick = 0;         // each loop iteration
    bool camsUp = false;
    Room camRoom = Room::ShowStage;
    bool alive = true;
    bool won = false;
};

// ================== Jump Scare Helpers ===================
static void jumpscare(const FanfString& who) {
    using namespace util;
    std::cout << "\n\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << "!!!!!!!!!  " << who << " JUMP SCARE  !!!!!!!!!!\n";
        pause_ms(180);
    }
    std::cout
        << "\n" << who << ": \"Screeeeeee!!!\"\n"
        << "You are yanked from the chair as metallic claws close in...\n"
        << "—— NIGHT FAILED ——\n\n";
}

// ================== Camera Map Display ===================
static void draw_map(const GameState& g) {
    std::cout << "\n=== CAMERA MAP ===\n";
    std::cout << "[Show Stage]  [Game Area]  [Prize Corner]\n";
    std::cout << "     |              |             |\n";
    std::cout << "[Party1] -- [Main Hall] -- [Party2]\n";
    std::cout << "     |                        |\n";
    std::cout << "[Left Vent]            [Right Vent]\n";
    std::cout << "          \\          /\n";
    std::cout << "              [Air Ducts]\n";
    std::cout << "                    |\n";
    std::cout << "                 [Office]\n";
    std::cout << "Current Cam: " << RoomName(g.camRoom) << (g.camsUp ? "" : " (down)") << "\n";
    std::cout << "Music Box: " << g.box.value << "%\n";
    std::cout << "Mask: " << (g.maskOn ? "ON" : "off")
        << " | Flashlight: " << (g.flashlight ? "ON" : "off")
        << " | Power: " << (g.powerOK ? "OK" : "DISRUPTED by BB") << "\n";
    std::cout << "===================\n";
}

// ================== Core Mechanics =======================
static void move_animatronic(std::mt19937& rng, GameState& g, Animatronic& a) {
    if (!a.active) return;
    if (a.inOfficeKill) return;
    if (a.stunned) { a.stunned = false; return; } // one-tick stun wears off

    // Base move chance
    int chance = g.diff.animatronicAggression + a.aggBase;
    // Camera noise can lure them closer
    if (g.camsUp) chance += g.diff.cameraNoiseRisk / 2;

    chance = util::clamp_int(chance, 0, 100);
    if (util::rngi(rng, 1, 100) > chance) return;

    // Simple directed graph of room progression toward Office
    Room r = a.room;
    switch (r) {
    case Room::ShowStage:    r = Room::MainHall; break;
    case Room::GameArea:     r = Room::MainHall; break;
    case Room::PrizeCorner:  r = Room::MainHall; break;
    case Room::PartyRoom1:   r = Room::LeftVent; break;
    case Room::PartyRoom2:   r = Room::RightVent; break;
    case Room::MainHall:     r = (util::rngi(rng, 0, 1) == 0 ? Room::PartyRoom1 : Room::PartyRoom2); break;
    case Room::LeftVent:     r = Room::AirDucts; break;
    case Room::RightVent:    r = Room::AirDucts; break;
    case Room::AirDucts:     r = Room::Office; break;
    case Room::Office:       r = Room::Office; break;
    default:                 r = Room::Office; break;
    }
    a.room = r;

    // Special checks
    if (a.name == FanfString("Withered Foxy") && a.room == Room::MainHall) {
        // Foxy can lunge from Main Hall randomly, requiring flashlight
        if (util::rngi(rng, 1, 100) <= g.diff.foxyAttackChance) {
            a.inOfficeKill = true; // threat in your face
        }
    }

    if (a.room == Room::Office) {
        a.inOfficeKill = true;
    }
}

static void puppet_logic(std::mt19937& rng, GameState& g) {
    // Puppet is not in bots vector as a mover; it triggers on box = 0
    if (!g.box.puppetReleased) return;
    // Puppet ignores mask; immediate loss chance scales with aggression
    (void)rng; // not used; avoid warnings
    jumpscare(FanfString("PUPPET"));
    g.alive = false;
}

static void resolve_threats(std::mt19937& rng, GameState& g) {
    for (auto& a : g.bots) {
        if (!a.inOfficeKill) continue;

        if (a.name == FanfString("Balloon Boy")) {
            // Disrupt power unless mask prevents him from entering
            if (g.maskOn) {
                a.inOfficeKill = false;
                a.room = Room::MainHall;
                continue;
            }
            g.powerOK = false;
            a.inOfficeKill = false;
            a.room = Room::GameArea;
            a.uniqueCool = 4; // takes a while before he returns
            continue;
        }

        if (a.name == FanfString("Withered Foxy")) {
            // Flashlight stuns Foxy; mask does nothing
            if (g.flashlight && g.powerOK) {
                a.stunned = true;
                a.inOfficeKill = false;
                a.room = Room::MainHall;
                continue;
            }
            jumpscare(a.name);
            g.alive = false;
            return;
        }

        // Others: mask is the counter with a save chance
        if (g.maskOn) {
            const int saveRoll = util::rngi(rng, 1, 100);
            if (saveRoll <= g.diff.maskBlockChance) {
                a.inOfficeKill = false;
                // push them back one step
                a.room = Room::AirDucts;
                continue;
            }
        }
        jumpscare(a.name);
        g.alive = false;
        return;
    }
}

static void decay_cooldowns(GameState& g) {
    for (auto& a : g.bots) {
        if (a.uniqueCool > 0) --a.uniqueCool;
    }
    if (g.powerOK && !g.camsUp && !g.flashlight) {
        // nothing drains here, just flavor hook
    }
}

static void camera_ping_effect(std::mt19937& rng, GameState& g) {
    // Small chance to draw attention when flipping cams up
    const int roll = util::rngi(rng, 1, 100);
    if (roll <= g.diff.cameraNoiseRisk) {
        // nearest bot nudges forward
        for (auto& a : g.bots) {
            if (!a.inOfficeKill && a.active && a.room != Room::Office) {
                // 50% chance to hop a step closer
                if (util::rngi(rng, 1, 100) <= 50) {
                    move_animatronic(rng, g, a);
                }
            }
        }
    }
}

// ================== Initialization =======================
static Difficulty choose_difficulty() {
    std::cout << "Choose difficulty:\n";
    std::cout << "1) Easy\n2) Normal\n3) Hard\n4) Custom\n> ";
    int c = 2;
    if (!(std::cin >> c)) { util::clear_input(); c = 2; }
    util::clear_input();

    Difficulty d{};
    if (c == 1) {
        d = { 6,  8,  1,  6, 80, 120 }; // gentle
    }
    else if (c == 3) {
        d = { 18, 20,  3, 20, 55, 110 }; // harsh
    }
    else if (c == 4) {
        std::cout << "Custom setup (enter integers):\n";
        std::cout << "Base aggression per tick (0-30): ";
        int a = 12; if (!(std::cin >> a)) { util::clear_input(); a = 12; }
        std::cout << "Foxy lunge chance in hall (0-40): ";
        int f = 12; if (!(std::cin >> f)) { util::clear_input(); f = 12; }
        std::cout << "Music box drain per tick (1-5): ";
        int m = 2;  if (!(std::cin >> m)) { util::clear_input(); m = 2; }
        std::cout << "Camera noise risk % (0-40): ";
        int n = 10; if (!(std::cin >> n)) { util::clear_input(); n = 10; }
        std::cout << "Mask block chance % (40-95): ";
        int k = 70; if (!(std::cin >> k)) { util::clear_input(); k = 70; }
        std::cout << "Shift length ticks (90-200): ";
        int t = 120;if (!(std::cin >> t)) { util::clear_input(); t = 120; }
        util::clear_input();
        d.animatronicAggression = util::clamp_int(a, 0, 30);
        d.foxyAttackChance = util::clamp_int(f, 0, 40);
        d.musicBoxDrain = util::clamp_int(m, 1, 5);
        d.cameraNoiseRisk = util::clamp_int(n, 0, 40);
        d.maskBlockChance = util::clamp_int(k, 40, 95);
        d.shiftLengthTicks = util::clamp_int(t, 90, 200);
    }
    else { // Normal
        d = { 12, 12,  2, 10, 70, 120 };
    }
    return d;
}

static std::vector<Animatronic> make_bots() {
    std::vector<Animatronic> v;
    v.push_back({ FanfString("Toy Freddy"), Room::ShowStage, 2 });
    v.push_back({ FanfString("Toy Bonnie"), Room::ShowStage, 2 });
    v.push_back({ FanfString("Toy Chica"),  Room::ShowStage, 2 });
    v.push_back({ FanfString("Mangle"),     Room::GameArea,  3 });
    v.push_back({ FanfString("Balloon Boy"),Room::GameArea,  1 });
    v.push_back({ FanfString("Withered Foxy"),Room::MainHall,4 });
    v.push_back({ FanfString("Withered Bonnie"),Room::PartyRoom1,3 });
    // Puppet handled by MusicBox
    return v;
}

// ================== UI Helpers ===========================
static void print_status(const GameState& g) {
    std::cout << "\n—— 12 AM -> 6 AM Night Shift ——\n";
    std::cout << "Tick " << g.tick << "/" << g.diff.shiftLengthTicks << "\n";
    std::cout << "Music Box: " << g.box.value << "%  | "
        << "Mask: " << (g.maskOn ? "ON" : "off")
        << " | Flashlight: " << (g.flashlight ? "ON" : "off")
        << " | Power: " << (g.powerOK ? "OK" : "DISRUPTED") << "\n";
    std::cout << "Animatronics (closest first):\n";
    for (const auto& a : g.bots) {
        std::cout << " - " << a.name << " @ " << RoomName(a.room)
            << (a.inOfficeKill ? " [IN YOUR FACE]" : "")
            << (a.stunned ? " [stunned]" : "")
            << (a.uniqueCool > 0 ? " [cooldown]" : "")
            << "\n";
    }
}

static void print_actions() {
    std::cout << "\nActions:\n";
    std::cout << " 1) Toggle Mask\n";
    std::cout << " 2) Flashlight (momentary)\n";
    std::cout << " 3) Flip Cameras Up/Down\n";
    std::cout << " 4) Cycle Camera Left\n";
    std::cout << " 5) Cycle Camera Right\n";
    std::cout << " 6) Wind Music Box (when cams up)\n";
    std::cout << " 7) Wait\n";
    std::cout << "> ";
}

static void cycle_cam(GameState& g, bool right) {
    int r = static_cast<int>(g.camRoom);
    int maxR = static_cast<int>(Room::MaxRooms) - 1;
    if (right) ++r; else --r;
    if (r < 0) r = maxR;
    if (r > maxR) r = 0;
    g.camRoom = static_cast<Room>(r);
}

// ================== Main Loop ============================
int main() {
    std::random_device rd;
    std::mt19937 rng(rd());

    GameState g;
    g.diff = choose_difficulty();
    g.bots = make_bots();
    g.camRoom = Room::ShowStage;

    std::cout << "\nWelcome to FNaF 2 (Text Edition) — survive until 6 AM!\n";
    std::cout << "Tip: Keep the music box wound (Prize Corner). Mask stops most threats.\n";
    std::cout << "Foxy hates light; Balloon Boy disrupts power; Puppet ignores mask.\n";

    // Night loop
    while (g.alive && !g.won) {
        ++g.tick;
        // Drain music box
        g.box.drain(g.diff.musicBoxDrain);
        if (g.camsUp && g.camRoom == Room::PrizeCorner) {
            // passive slow wind when looking at it
            g.box.wind(1);
        }
        if (g.box.puppetReleased == false && g.box.value == 0) {
            g.box.puppetReleased = true;
        }

        // Movement
        for (auto& a : g.bots) {
            if (a.uniqueCool > 0) continue;
            move_animatronic(rng, g, a);
        }

        // Balloon Boy effect duration
        if (!g.powerOK) {
            // After some time power recovers
            if (util::rngi(rng, 1, 100) <= 15) g.powerOK = true;
        }

        // Status & UI
        print_status(g);
        if (g.camsUp) draw_map(g);

        print_actions();
        int choice = 7;
        if (!(std::cin >> choice)) { util::clear_input(); choice = 7; }
        util::clear_input();

        switch (choice) {
        case 1: // mask
            g.maskOn = !g.maskOn;
            if (g.maskOn) g.flashlight = false; // can't both
            std::cout << (g.maskOn ? "You pull the Freddy mask over your face.\n"
                : "You remove the mask.\n");
            break;
        case 2: // flashlight
            if (!g.powerOK) {
                std::cout << "Flashlight sputters... Balloon Boy messed with the batteries!\n";
            }
            else {
                g.flashlight = true;
                std::cout << "You flash the light down the hall!\n";
            }
            break;
        case 3: // cams up/down
            g.camsUp = !g.camsUp;
            if (g.camsUp) {
                g.maskOn = false;
                g.flashlight = false;
                camera_ping_effect(rng, g);
                std::cout << "Cameras up. Use 4/5 to cycle, 6 to wind the box.\n";
            }
            else {
                std::cout << "Cameras down. Back to the office...\n";
            }
            break;
        case 4:
            if (g.camsUp) { cycle_cam(g, false); }
            else std::cout << "Cameras are down.\n";
            break;
        case 5:
            if (g.camsUp) { cycle_cam(g, true); }
            else std::cout << "Cameras are down.\n";
            break;
        case 6:
            if (g.camsUp && g.camRoom == Room::PrizeCorner) {
                std::cout << "You wind the music box...\n";
                g.box.wind(20);
            }
            else {
                std::cout << "You must be viewing Prize Corner to wind it.\n";
            }
            break;
        case 7:
        default:
            std::cout << "You wait, listening to the static and distant clanking...\n";
            break;
        }

        // Resolve threats (jump scares or escapes)
        resolve_threats(rng, g);
        if (!g.alive) break;

        // Puppet check last (overrides everything)
        puppet_logic(rng, g);
        if (!g.alive) break;

        // End-of-tick housekeeping
        decay_cooldowns(g);
        g.flashlight = false; // momentary

        // win condition
        if (g.tick >= g.diff.shiftLengthTicks) {
            g.won = true;
        }

        util::pause_ms(120); // pacing
    }

    if (g.won) {
        std::cout << "\n—— 6:00 AM — You Survived! ——\n";
    }
    else if (!g.alive) {
        std::cout << "Try a new strategy and watch that music box...\n";
    }

    return 0;
}