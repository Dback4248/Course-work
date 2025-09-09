/*
  FNAF-Style Text Adventure (Single File)
  - C++17, portable console (no OS-specific APIs)
  - Includes "jump scares" (ASCII art + beeps + screen flash)
  - No use of std::clamp
  - Intended to compile cleanly with:  
      g++ -std=c++17 -O2 -pipe -pthread fnaf_text_adventure.cpp -o fnaf
      clang++ -std=c++17 -O2 -pthread fnaf_text_adventure.cpp -o fnaf

  Controls (type commands and press Enter):
    help                       Show commands
    status                     Show power, time, doors
    cams <1-6>                 View camera 1..6
    door <left|right> <open|close>
    light <left|right>         Toggle hallway light (small power drain burst)
    wait                       Wait a few seconds (time advances, power drains)
    mutecall                   Silence the phone guy
    quit                       Exit game

  Goal: survive from 12:00 AM to 6:00 AM with power > 0 and no animatronic reaches the office when the matching door is open.
*/

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

using namespace std;
using namespace std::chrono;

static void sleep_ms(int ms) { this_thread::sleep_for(milliseconds(ms)); }

static string lower_copy(string s){
    for(char &c: s) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    return s;
}

static void clear_screen(){
    // ANSI clear; harmless if unsupported
    cout << "\033[2J\033[H";
}

static void flash_screen(int flashes=3, int on_ms=100, int off_ms=80){
    for(int i=0;i<flashes;i++){
        cout << "\033[7m"; // inverse
        cout.flush();
        sleep_ms(on_ms);
        cout << "\033[0m";
        cout.flush();
        sleep_ms(off_ms);
    }
}

static void beep(int times=1){
    for(int i=0;i<times;i++){ cout << '\a'; cout.flush(); sleep_ms(60);} }

struct Animatronic {
    string name;
    // Path nodes: 0=Stage, 1=Dining, 2=Backstage, 3=Left Hall, 4=Right Hall, 5=Left Door, 6=Right Door, 7=Office
    vector<int> pathLeft;   // path toward left door
    vector<int> pathRight;  // path toward right door
    int pos = 0;            // index in whichever path we are currently using
    bool usingLeft = true;  // which path we follow
    bool active = false;    // becomes active after some time
    int aggressiveness = 1; // higher = moves faster/more often

    string cam_label() const {
        // Map node to camera name
        static map<int,string> camNames{
            {0,"Cam1A — Show Stage"}, {1,"Cam1B — Dining Area"}, {2,"Cam5 — Backstage"},
            {3,"Cam2A — West Hall"}, {4,"Cam4A — East Hall"}, {5,"Cam2B — West Hall Corner"},
            {6,"Cam4B — East Hall Corner"}, {7,"Office"}
        };
        int node = current_node();
        auto it = camNames.find(node);
        return (it!=camNames.end()? it->second : string("Unknown"));
    }

    int current_node() const {
        const auto &p = usingLeft ? pathLeft : pathRight;
        int clampedIndex = pos < 0 ? 0 : (pos >= (int)p.size() ? (int)p.size()-1 : pos);
        return p.empty()? 0 : p[clampedIndex];
    }

    bool at_left_door() const { return current_node()==5; }
    bool at_right_door() const { return current_node()==6; }
    bool in_office() const { return current_node()==7; }
};

struct Game {
    // Game state
    int night = 1;
    int hour = 0;         // 0..5 => 12AM..5AM; survive to hour==6
    int minutes = 0;      // 0..59
    bool phoneRinging = true;

    bool leftDoorClosed = false;
    bool rightDoorClosed = false;

    int power = 100;      // %
    int powerDrainBase = 1;  // per tick
    int powerDrainDoor = 1;  // per closed door
    int powerDrainCams = 1;  // while using cameras

    bool camerasUp = false;

    mt19937 rng;

    vector<Animatronic> bots;

    Game(){
        rng.seed(random_device{}());
        setup_animatronics();
    }

    void setup_animatronics(){
        bots.clear();
        // 3 distinct behaviors
        Animatronic bear{"Ursa", {0,1,3,5,7}, {0,2,4,6,7}, 0, true, false, 1};
        Animatronic hare{"Lapis", {0,2,3,5,7}, {0,1,4,6,7}, 0, true, false, 2};
        Animatronic chick{"Cinder", {0,1,2,3,5,7}, {0,1,2,4,6,7}, 0, false, false, 3};
        bots = {bear, hare, chick};
    }

    void print_header(){
        cout << "\n================= NIGHT " << night << " — 12:00 AM =================\n";
        cout << "Survive until 6:00 AM. Type 'help' for commands.\n";
    }

    void print_help(){
        cout << "\nCommands:\n"
             << "  help                          Show this\n"
             << "  status                        Power/time/doors\n"
             << "  cams <1-6>                    View a camera\n"
             << "  door <left|right> <open|close> Control doors\n"
             << "  light <left|right>            Toggle hallway light\n"
             << "  wait                          Let time pass\n"
             << "  mutecall                      Silence the phone\n"
             << "  quit                          Exit\n";
    }

    string clock_str() const {
        int displayHour = hour==0? 12 : hour;
        ostringstream oss; oss << setw(2) << setfill('0') << minutes; // for curiosity
        (void)oss; // silence unused warning if not used later
        static const char* names[7] = {"12:00 AM","1:00 AM","2:00 AM","3:00 AM","4:00 AM","5:00 AM","6:00 AM"};
        string h = names[min(hour,6)];
        return h;
    }

    void phone_call() const {
        if(!phoneRinging) return;
        cout << "\n☎ The phone crackles: 'Uhh, hello! Welcome to your new summer job... keep an eye on those cameras.'\n";
        cout << "(Type 'mutecall' to hang up.)\n";
    }

    void show_status() const {
        cout << "\nTime: " << clock_str()
             << "  |  Power: " << power << "%"
             << "  |  Doors: L=" << (leftDoorClosed?"Closed":"Open")
             << " R=" << (rightDoorClosed?"Closed":"Open")
             << (camerasUp?"  |  Cams: UP":"  |  Cams: DOWN")
             << "\n";
    }

    void show_camera(int cam){
        camerasUp = true;
        uniform_int_distribution<int> noise(0,3);
        cout << "\n[CAM] Switching to Cam" << cam << "...\n";
        power -= power>0 ? powerDrainCams : 0;
        for(auto &b : bots){
            cout << " - " << b.name << " @ " << b.cam_label();
            if(noise(rng)==0) cout << "  (video static)";
            cout << "\n";
        }
        cout << "(Viewing cams increases power drain while up.)\n";
    }

    void toggle_door(const string& side, const string& state){
        bool close = (lower_copy(state)=="close");
        if(lower_copy(side)=="left"){ leftDoorClosed = close; cout << "Left door " << (close?"closed.":"opened.") << "\n"; }
        else if(lower_copy(side)=="right"){ rightDoorClosed = close; cout << "Right door " << (close?"closed.":"opened.") << "\n"; }
        else { cout << "Use left/right.\n"; return; }
    }

    void hallway_light(const string& side){
        cout << "You flick the " << side << " hallway light." << "\n";
        power -= (power>0 ? 1 : 0);
        // Reveal if someone is at the door corner
        for(auto &b : bots){
            if( (lower_copy(side)=="left" && b.at_left_door()) || (lower_copy(side)=="right" && b.at_right_door()) ){
                cout << "!!! " << b.name << " looms in the " << side << " doorway!\n";
            }
        }
    }

    void time_tick(int seconds=10){
        // Advance time and update world; called by wait and by actions
        // Power drain
        int drain = powerDrainBase + (leftDoorClosed?powerDrainDoor:0) + (rightDoorClosed?powerDrainDoor:0) + (camerasUp?powerDrainCams:0);
        power -= max(0, drain);
        if(power < 0) power = 0;

        // Activate bots as night progresses
        for(size_t i=0;i<bots.size();++i){
            if(!bots[i].active){
                if(hour>=i) bots[i].active = true; // simple ramp
            }
        }

        // Move bots based on aggressiveness and randomness
        uniform_int_distribution<int> chance(0, 9);
        for(auto &b : bots){
            if(!b.active) continue;
            int roll = chance(rng);
            if(roll < b.aggressiveness + hour){
                // 50/50 choose path each move, keeps them unpredictable
                uniform_int_distribution<int> fifty(0,1);
                b.usingLeft = fifty(rng)==0;
                b.pos += 1; // step forward
                // Cap index within path bounds manually (no std::clamp)
                const auto &p = b.usingLeft ? b.pathLeft : b.pathRight;
                if(b.pos >= (int)p.size()) b.pos = (int)p.size()-1;
                if(b.pos < 0) b.pos = 0;
            }
        }

        // Check door collisions -> bounce back if door closed
        for(auto &b : bots){
            if(b.at_left_door() && leftDoorClosed){
                // Bounce back one step
                b.pos = max(0, b.pos-1);
            }
            if(b.at_right_door() && rightDoorClosed){
                b.pos = max(0, b.pos-1);
            }
        }

        // If power runs out: lights out, doors open
        if(power==0){
            leftDoorClosed = rightDoorClosed = false;
            camerasUp = false;
        }

        // Advance clock
        minutes += seconds/10; // coarse: each tick ~1 minute
        if(minutes>=60){ minutes-=60; hour++; }
    }

    bool check_loss(){
        for(auto &b : bots){
            if(b.in_office()){
                jumpscare(b.name);
                cout << "\nYou were caught by " << b.name << "...\n";
                return true;
            }
            if( (b.at_left_door() && !leftDoorClosed) || (b.at_right_door() && !rightDoorClosed) ){
                // They slip in on next tick
                uniform_int_distribution<int> slip(0,2);
                if(slip(rng)==0){
                    b.pos += 1; // into office
                    if(b.pos<0) b.pos=0; // safety
                    jumpscare(b.name);
                    cout << "\n" << b.name << " slipped into the office!\n";
                    return true;
                }
            }
        }
        return false;
    }

    void jumpscare(const string& who){
        clear_screen();
        flash_screen(6, 60, 40);
        beep(3);
        cout << "\n";
        cout << "#############################################\n";
        cout << "#               J U M P S C A R E          #\n";
        cout << "#############################################\n\n";
        cout << "";
        cout << "        " << who << " STARES FROM THE DARK!\n\n";
        cout << R"( 
            .-"""-.
           / .===. \
           \/ 6 6 \/
           (   _\_/ )
        ___ooo__V__ooo___
        )";
        cout << "\n\n";
        beep(2);
        flash_screen(4, 80, 60);
        clear_screen();
    }

    bool check_win() const { return hour >= 6; }

    void game_over(bool win){
        if(win){ cout << "\n6:00 AM! You survived the night.\n"; }
        else { cout << "\nThe night ends... better luck next time.\n"; }
    }

    void run(){
        clear_screen();
        print_header();
        phone_call();
        show_status();

        string line;
        while(true){
            if(check_win()){ game_over(true); break; }
            if(check_loss()){ game_over(false); break; }

            cout << "\n> ";
            if(!std::getline(cin, line)) break;
            string cmd;
            string a,b;
            {
                istringstream iss(line);
                iss >> cmd >> a >> b;
            }
            cmd = lower_copy(cmd);

            if(cmd=="help"){ print_help(); }
            else if(cmd=="status"){ camerasUp=false; show_status(); }
            else if(cmd=="cams"){ 
                int cam = 1;
                try{ cam = stoi(a); } catch(...){ cam = 1; }
                if(cam<1||cam>6) cam=1;
                show_camera(cam);
                time_tick(10);
            }
            else if(cmd=="door"){ toggle_door(a,b); time_tick(10); camerasUp=false; }
            else if(cmd=="light"){ hallway_light(a); time_tick(5); camerasUp=false; }
            else if(cmd=="wait"){ cout << "You wait, listening to the hum of the fans...\n"; time_tick(30); camerasUp=false; }
            else if(cmd=="mutecall"){ if(phoneRinging){ phoneRinging=false; cout << "(Phone silenced.)\n";} else cout << "(It's already quiet.)\n"; }
            else if(cmd=="quit"){ cout << "Quitting...\n"; break; }
            else if(cmd.empty()){ /* ignore */ }
            else { cout << "Unknown command. Type 'help'.\n"; }

            show_status();
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Game g;
    g.run();
    return 0;
}
