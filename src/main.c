/*
 * main.c
 *
 * Programming 2 - Project 3 (PageRank)
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "utils.h"
#include "graphparse.h"
#include "randomsurfer.h"
#include "graph.h"
#include "markov.h"


int main(int argc, char *const *argv) {

    int mm=0;
    int kk=0;
    int opt;
    int no_steps=0;
    double p =0.1;
    char *filename =NULL;
    if (argc<=1) exit (1);
    while ((opt =getopt(argc, argv, "hsr:m:p:"))!=-1){
        switch (opt) {
            case 'h':{
            printf("Usage : ./ pagerank [ OPTIONS ] ... [ FILENAME ]\n");
            printf("Perform pagerank computations for a given file in the DOT format\n\n");
            printf("  -h    Print a brief overview of the available command line parameters\n");
            printf("  -r N  Simulatcleare N steps of the random surfer and output the result\n");
            printf("  -m N  Simulate N steps of the Markov chain and output the result\n");
            printf("  -s    Compute and print the statistics of the graph as defined \n");
            printf("          in section 3.4\n");
            printf("  -p P  Set the parameter p to P%%. (Default : P = 10)\n");}
            break;
            
            case 's':{if (optind<argc){
                filename = argv[optind];
            graph_t *graph= parse_graph (filename);
            print_stats(graph);
            free_graph (graph);
            }
            else{ printf ("No file name provided\n");
                    exit (1);
            }
            }break;

            case 'r':no_steps = atoi (optarg);
            kk= 1;
            break;

            case 'm': no_steps = atoi (optarg);
            mm=1;
            break;

            case 'p':p= atof(optarg);
                break;
           
            default : printf("error\n"); exit (1);
        } 
    }

  if (kk==1){if (optind<argc){
                filename = argv[optind];
                if(filename==NULL){
                    printf("MISSING FILENAME\n");
                    exit(1);
                }
                graph_t *graph= parse_graph (filename);
                if (graph->count==0) {
                    exit (0);
                  free_graph (graph);}
                simulate_rs(graph, no_steps, p);
                free_graph (graph);
                exit (0);
            }else{
                 printf ("No file name provided\n");
                    exit (1);
                 }}

  if (mm==1){if (optind<argc){
                filename = argv[optind];
                if(filename==NULL|| no_steps==0|| p== 0){
                    printf("MISSING FILENAME\n");
                    exit(1);
                }
                graph_t *graph= parse_graph (filename);
                if (graph->count==0) {
                    free_graph (graph);
                    exit (0);
                  }
                simulate_markov(graph, no_steps, p);
                free_graph (graph);
                exit (0);
            }else{
                 printf ("No file name provided\n");
                    exit (1);
                 }}
  // initialize the random number generator
  rand_init();

  // TODO: Implement me
  exit(0);
}
