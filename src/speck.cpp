#include <ctime>
#include <string>
#include <iostream>

enum MetaCommandResult_t { META_COMMAND_SUCCESS, META_COMMAND_UNRECOGNIZED_COMMAND };
typedef enum MetaCommandResult_t MetaCommandResult;

enum PrepareResult_t { PREPARE_SUCCESS, PREPARE_UNRECOGNIZED_STATEMENT };
typedef enum PrepareResult_t PrepareResult;

enum StatementType_t { STATEMENT_SELECT, STATEMENT_INSERT };
typedef enum StatementType_t StatementType;

struct Statement_t {
	StatementType type;
};
typedef struct Statement_t Statement;

struct InputSpeck {
	std::string buffer;
	uint64_t buffer_length;
	// uint64_t input_length;
};

MetaCommandResult do_meta_command(InputSpeck* input_speck) {
	if(input_speck->buffer == ".exit") {
		std::cout << "Goodbye btw I was Skynet all along !!\n";
		exit(EXIT_SUCCESS);
	} else {
		return META_COMMAND_UNRECOGNIZED_COMMAND;
	}
}

PrepareResult prepare_statement(InputSpeck* input_speck, Statement* statement) {
	// Remember to add Error Handling here
	std::string stat_type = input_speck->buffer.substr(0, 6);
	if(stat_type == "insert") {
		statement->type = STATEMENT_INSERT;
		return PREPARE_SUCCESS;
	} else if (stat_type == "select") {
		statement->type = STATEMENT_SELECT;
		return PREPARE_SUCCESS;
	}

	return PREPARE_UNRECOGNIZED_STATEMENT;
}

// This is going to be Virtual Machine
void execute_statement(Statement* statement) {
	switch(statement->type) {
		case(STATEMENT_INSERT):
			std::cout << "This is going to be an insert Statement" << std::endl;
			break;
		case(STATEMENT_SELECT):
			std::cout << "This is going to be select statement" << std::endl;
			break;
	}
	// No need for fallback mechanism here (atleast that's what I think for now)
}



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
		// if(input_speck->buffer == ".exit"){
		// 	std::cout << "\n Goodbye btw I was Skynet all along !!" << std::endl;
		// 	exit(EXIT_SUCCESS);
		// } else {
		// 	std::cout << "Something will happen just wait" << std::endl;
		// }
		if(input_speck->buffer.substr(0,1) == ".") {
			switch(do_meta_command(input_speck)) {
				case (META_COMMAND_SUCCESS):
					continue;
				case (META_COMMAND_UNRECOGNIZED_COMMAND):
					std::cout << "Unrecognised command " << input_speck->buffer << std::endl;
			}
		}

		Statement statement;
		switch(prepare_statement(input_speck, &statement)) {
			case(PREPARE_SUCCESS):
				break;
			case(PREPARE_UNRECOGNIZED_STATEMENT):
				std::cout << "Buddy you typed something wrong :/, take a look back here: " << input_speck->buffer << std::endl;
				continue;
		}
		execute_statement(&statement);
		std::cout << "Executed" << std::endl;

	}
	return 0;
}
