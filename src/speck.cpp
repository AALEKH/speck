#include <ctime>
#include <string>
#include <iostream>

struct InputSpeck {
	std::string buffer;
	uint64_t buffer_length;
	// uint64_t input_length;
};

void initiateSpeck() {
	const time_t ctt = time(0);
	std::string curr_time = asctime(localtime(&ctt));
	std::string welcome_message = "Welcome to Speck (v 0.1), your in-house SQL " + curr_time + "Enter .help for hints\nEnter .exit to quit this interface";
	std::cout << welcome_message << std::endl;
}

void prompt() {
	std::cout << "speck >";
}

std::string read_text()
{
    std::string prompt;
    // cout << "Enter your text: ";
    std::getline(std::cin, prompt);
    return prompt;
}

void read_input(InputSpeck* input_speck) {
	input_speck->buffer = read_text();
	input_speck->buffer_length = sizeof(input_speck->buffer)-1;
	if(input_speck->buffer_length <= 0) {
		std::cout << "Error Reading Inputs" << std::endl;
		input_speck->buffer = ".exit";
	}
}

int main() {
	initiateSpeck();
	InputSpeck* input_speck = new InputSpeck();
	while(true) {
		prompt();
		read_input(input_speck);
		if(input_speck->buffer == ".exit"){
			std::cout << "\n Goodbye Skynet !!" << std::endl;
			break;
		} else {
			std::cout << "Something will happen just wait" << std::endl;
		}
	}
	return 0;
}