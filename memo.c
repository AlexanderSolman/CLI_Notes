#include "memo.h"

int main(int argc, char *argv[]){
    // Initiating option variables
    struct options opts;
    opts.hopt = "-h";
    opts.aopt = "-a";
    opts.iopt = "-i";
    opts.sopt = "-s";
    opts.dopt = "-d";

    // Default if no argument was given
    if(argc < 2){
        help();
        return 1;
    }
    // Function calls for all options
    if(strcmp(argv[1], opts.aopt) == 0){
        append(argv[2], argv[3]);
    }else if(strcmp(argv[1], opts.iopt) == 0){
        initiate(argv[2]);
    }else if(strcmp(argv[1], opts.sopt) == 0){
        search(argv[2], argv[3]);
    }else if(strcmp(argv[1], opts.dopt) == 0){
        sscanf(argv[3], "%d", &opts.num);
        if(opts.num > 0){
            delete(argv[2], opts.num);
        }
    }else if(strcmp(argv[1], opts.hopt) == 0){
        help();
    }

    return 0;
}