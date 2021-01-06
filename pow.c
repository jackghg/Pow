// Pow 0.5
// g++ -std=c++0x `fltk-config --cxxflags` pow.cc `fltk-config --ldflags` -o pow
#include <iostream>
#include <ctype.h>
#include <string.h>
#include <vector>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Select_Browser.H>
#include <unistd.h>

using namespace std;

vector<string> ids;
short e, l = 0, i = 0;
// show the window and quit
static void sel(Fl_Widget *r) {
Fl_Select_Browser *b = (Fl_Select_Browser*)r;
l = b->value() - 1;
char cs[25] = "wmctrl -i -a ";
strcat(cs, ids[l].c_str());
system(cs);
exit(0);
}

int main(int argc, char *argv[]) {
// title bar, side margin, top margin, font size
short of = 34, bo = 50, to = 25, fs = 35;
// arguments
if (argc) { short t;
for (int n = 1; n < argc; ++n) {
if (!strcmp(argv[n], "-s")) {
if (n + 1 < argc && isdigit(argv[n+1][0]) && strlen(argv[n+1]) < 5) {
t = atoi(argv[n+1]); if (t) { fs = t; } } }
else if (!strcmp(argv[n], "-m")) {
if (n + 1 < argc && isdigit(argv[n+1][0]) && strlen(argv[n+1]) < 5) {
t = atoi(argv[n+1]); if (t) { bo = t; } } }
else if (!strcmp(argv[n], "-t")) {
if (n + 1 < argc && isdigit(argv[n+1][0]) && strlen(argv[n+1]) < 4) {
t = atoi(argv[n+1]); if (t) { to = t; } } }
else if (!strcmp(argv[n], "-b")) {
if (n + 1 < argc && isdigit(argv[n+1][0]) && strlen(argv[n+1]) < 4) {
t = atoi(argv[n+1]); if (t) { of = t; } } }
else if (!strcmp(argv[n], "-?")) { printf("\nPow 0.5 window switcher.\n\nOPTIONS:\n-s	font size\n-m	side margin from screen\n-t	top margin\n-b	your titlebar height\n\n"); exit(0); } } }
// UI
unsigned short w = Fl::w() - bo - bo;
unsigned short h = Fl::h();
Fl_Window win( bo, to + of, w, 50, "pow" );
Fl_Select_Browser bro(NULL, NULL, w-1, 49);
bro.box(FL_FLAT_BOX);
bro.textsize(fs);
bro.callback(sel);
char buf[99], baf[26];
FILE* pipe = popen("wmctrl -l", "r");
if (!pipe) { printf("error\n"); exit(1); }
while (!feof(pipe)) {
while ( l == 98 ) { fgets(buf, 99, pipe); l = strlen(buf); }
if (fgets(buf, 99, pipe) != NULL) {
l = strlen(buf);
strncpy(baf, strtok(buf, " "), 11);
if (strcmp(strtok(NULL, " "), "-1")) { //exclude panels
ids.push_back(string(baf));
strtok(NULL, " ");
strcpy(baf, "@c");
strncat(baf, strtok(NULL, ""), 23);
e = strlen(baf);
while (isspace(baf[--e])) baf[e] = 0; //r trim
bro.add(baf);
++i; } } }
pclose(pipe);
win.resizable(bro);
float fo =  fs * 18;
fo /= 100; fo += 1.5; fo += fs; fo *= i;
int hh = (int) fo + 5;
if ( hh > 50 ) {
if ( ( hh + of + to ) > h ) hh = h - to - of;
win.resize(bo, to + of, w, hh); } //bro.resize(NULL, NULL, w-1, hh-1);
win.resizable(bro);
win.show(argc, argv);
return(Fl::run());
}
