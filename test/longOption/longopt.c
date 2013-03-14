/*
 * a test of longopts
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

struct cmdline_args {
	const char *fwname;
	int flags;
	const char *driver;
	const char *dev;
	int number;
};

static int parse_cmdline_args(int argc, char **argv, struct cmdline_args *args) {
	int opt;
	static const struct option longopts[] = { //

			{ "help", no_argument, 0, 'H' }, // 0: no value
			{ "driver", required_argument, 0, 'D' }, // 1: must have value
			{ "version", no_argument, 0, 'V' }, //
			{ "require-fw-update", optional_argument, 0, 'M' }, //2: may have value
			{ "embedded", no_argument, 0, 'E' }, //
			{ NULL, no_argument, 0, 0 } //
	};

	while ((opt = getopt_long(argc, argv, "d:vsQ", longopts, NULL)) >= 0)
		switch (opt) {
		case 'D': {
			args->driver = optarg;
		}
			break;
		case 'M': {
			args->fwname = optarg;
		}
			break;
		case 'E': {
			printf("embedded args\n");

		}
			break;
		case 'd': {
			args->dev = optarg;
		}
			break;
		case 'q': {
			printf("quit\n");
			exit(0);
		}
			break;

		case 'v':
		case 'V': {
			printf("verison 0.1\n");
			exit(0);
		}
			break;
		case 'H': {
			printf("longopt:\n"
					"\t--help: for help information\n"
					"\t--driver	driver name\n"
					"\t--version\n"
					"example ./longopt --driver fet430uif -d /dev/ttyUSB0 cmd1 cmd2 cmd3 cmd4\n");
			exit(0);
		}
			break;
		case '?':
			fprintf(stderr, "Try --help for usage information.\nexample ./longopt --driver fet430uif -d /dev/ttyUSB0 cmd1 cmd2 cmd3 cmd4\n");
			return -1;
		default:
				//nothing
			break;
		}

	//pass the left args
	while (optind < argc) {
		printf("#%s\n", argv[optind++]);
	}

	return 0;
}


//usage: ./longopt --driver fet430uif -d /dev/ttyUSB0 cmd1 cmd2 cmd3 cmd4
int main(int argc, char **argv) {
	int ret;
	//store your args form CLI
	struct cmdline_args args = { 0 };
	ret = parse_cmdline_args(argc, argv, &args);
	if (ret < 0) {
		fprintf(stderr, "wrong args\n");
		return -1;
	}

	if(args.driver == NULL){
		fprintf(stderr, "Try --help for usage information.\nexample ./longopt --driver fet430uif -d /dev/ttyUSB0 cmd1 cmd2 cmd3 cmd4\n");
		return 0;
	}
	printf("(%s:%s)\n", args.driver, args.dev);
	return ret;
}
