//
// Created by Dell on 01.05.2023.
//
#include <cstdio>
#include <cmath>
#include "boinc_api.h"
#include "boinc_types.h"
#include "boinc_fractional.h"
#include "filesyst.h"
int main(int argc, char** argv) {
    // Initialize BOINC API
    boinc_init_diagnostics(BOINC_DIAG_DEBUG | BOINC_DIAG_PROC_STATUS | BOINC_DIAG_MEMORY_USAGE);
    boinc_parse_init_data_files(argc, argv);
    boinc_init();

    // Get input parameters
    double lower_limit, upper_limit, step_size;
    char input_file[256];
    boinc_resolve_filename("input.txt", input_file, sizeof(input_file));
    FILE* f = boinc_fopen(input_file, "r");
    if (!f) {
        boinc_finish(1);
    }
    if (fscanf(f, "%lf %lf %lf", &lower_limit, &upper_limit, &step_size) != 3) {
        boinc_finish(1);
    }
    boinc_fclose(f);

    // Compute integral using trapezoidal rule
    double result = 0.0;
    double x;
    for (x = lower_limit + step_size; x < upper_limit; x += step_size) {
        result += sin(x);
    }
    result += (sin(lower_limit) + sin(upper_limit)) / 2.0;
    result *= step_size;

    // Write result to output file
    char output_file[256];
    boinc_resolve_filename("output.txt", output_file, sizeof(output_file));
    f = boinc_fopen(output_file, "w");
    if (!f) {
        boinc_finish(1);
    }
    fprintf(f, "%.10g\n", result);
    boinc_fclose(f);

    // Finalize BOINC API
    boinc_finish(0);
}