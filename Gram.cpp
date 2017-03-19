#include <iostream>
#include <string>

using namespace std;




class Rule {
public:
	char from;
	char to0;
	char to1;
	bool mono;
	Rule() {};
	Rule(char start, char non_term1, char non_term2) {
		from = start;
		mono = false;
		to0 = non_term1;
		to1 = non_term2;
	};
	Rule(char start, char term) {
		from = start;
		to0 = term;
		mono = true;
	};
};






bool all(char non_terminal[4], string line, char start, int num_start, int num_finish, int steps, Rule rules[6], bool printing);




bool with_void(char non_terminal[4], string line, char start, char hole, int num_start, int hole_start, int hole_finish, int num_finish, int steps, Rule rules[6], bool printing) {
	if (steps == 0) {
		return false;
	}
	// ƒырка справа
	if (hole_finish == num_finish) {
		for (int i = 0; i < 6; i++) {
			Rule now = rules[i];
			if (now.mono == false) {
				if (now.from == start && now.to1 == hole) {
					if (all(non_terminal, line, now.to0, num_start, hole_start, steps - 1, rules,false)) {

						if (printing) {
						cout << endl;
						cout << "(" << start << ":" << now.to0 << +" " << now.to1 << ")";
						cout << endl;
						all(non_terminal, line, now.to0, num_start, hole_start, steps - 1, rules, true);
						}
						
						return true;

					}
				}
			}
		}
	}
	// ƒырка слева
	if (hole_start == num_start) {
		for (int i = 0; i < 6; i++) {
			Rule now = rules[i];
			if (now.mono == false) {
				if ((now.from == start) && (now.to0 == hole)) {
					if (all(non_terminal, line, now.to1, num_start, hole_start, steps - 1, rules,false)) {
						if (printing) { cout << "(" << start << ":" << now.to0 << +" " << now.to1 << ")";
						all(non_terminal, line, now.to1, num_start, hole_start, steps - 1, rules, true);
						//cout << endl;
						}
						return true;
					}
				}
			}
		}
	}
	// "”меньшение" дырки
	for (int new_hole_start = num_start; new_hole_start < hole_start;new_hole_start++) {
		for (int new_hole_finish = hole_finish; new_hole_finish < num_finish;new_hole_finish++) {
			for (int i = 0; i < 4;i++)
			{
				if (with_void(non_terminal, line, start, non_terminal[i], num_start, new_hole_start, new_hole_finish, num_finish, steps - 1, rules,false)) {
					if (with_void(non_terminal, line, non_terminal[i], hole, new_hole_start, hole_start, hole_finish, new_hole_finish, steps - 1, rules,false)) {
						return true;

					}
				}

			}
		}
	}
	return false;
}

bool all(char non_terminal[4], string line, char start, int num_start, int num_finish, int steps, Rule rules[6],bool printing) {
	if (steps == 0) {
		return false;
	};
	if (num_start + 1 == num_finish) {

		for (int i = 0;i < 6;i++) {
			Rule now = rules[i];
			if (now.mono) {
				if ((now.from == start) && (now.to0 == line[num_start])) {
					if (printing) { cout << "(" << start << " " << line[num_start] << ")"; }
					return true;
				}
			}
		}
	}
	for (int hole_start = num_start; hole_start <= num_finish; hole_start++) {
		for (int hole_finish = hole_start;hole_finish <= num_finish;hole_finish++) {
			for (int i = 0;i < 4;i++) {
				if (with_void(non_terminal, line, start, non_terminal[i], num_start, hole_start, hole_finish, num_finish, steps - 1, rules,false)) {
					if (all(non_terminal, line, non_terminal[i], hole_start, hole_finish, steps - 1, rules,false)) {
						if (printing) {
							with_void(non_terminal, line, start, non_terminal[i], num_start, hole_start, hole_finish, num_finish, steps - 1, rules, true);
							all(non_terminal, line, non_terminal[i], hole_start, hole_finish, steps - 1, rules, true);
						}
						return true;
					}
				}
			}
		}
	}
	return false;
}


int main() {
	Rule rules[6];
	rules[0] = Rule('S', 'S', 'S');
	rules[1] = Rule('S', 'A', 'C');
	rules[2] = Rule('A', 'a');
	rules[3] = Rule('B', 'b');
	rules[4] = Rule('C', 'S', 'B');
	rules[5] = Rule('C', 'b');
	char non_terminal[4];
	non_terminal[0] = 'A';
	non_terminal[1] = 'B';
	non_terminal[2] = 'C';
	non_terminal[3] = 'S';
	string x;
	cin >> x;
	cout << endl << all({"ABCS"}, x , 'S', 0, x.length(), 10, rules,true);
}
