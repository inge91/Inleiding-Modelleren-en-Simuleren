#include <stdio.h>
#include <stdlib.h>

#include "differentials.h"

#define ARRAY_SIZE 5

typedef struct {
    double birthrate,
           deathrate,
           fatality_rate,
           imm_loss_rate,
           recov_imm_rate,
           recov_susc_rate;
} malaria_params;

malaria_params make_params(double birthrate, double deathrate,
                           double fatality_rate, double imm_loss_rate,
                           double recov_imm_rate, double recov_susc_rate)
{
    malaria_params params;

    params.birthrate = birthrate;
    params.deathrate = deathrate;
    params.fatality_rate = fatality_rate;
    params.imm_loss_rate = imm_loss_rate;
    params.recov_imm_rate = recov_imm_rate;
    params.recov_susc_rate = recov_susc_rate;

    return params;
}

int malaria(double t, double *y, double *dy, void *params)
{
    int Hu = 0,
        Hi = 1,
        Hr = 2,
        Mu = 3,
        Mi = 4;

    double birthrate       = ((malaria_params *) params)->birthrate,
           deathrate       = ((malaria_params *) params)->deathrate,
           fatality_rate   = ((malaria_params *) params)->fatality_rate,
           imm_loss_rate   = ((malaria_params *) params)->imm_loss_rate,

           // chance of going from infected to resistant
           recov_imm_rate  = ((malaria_params *) params)->recov_imm_rate,    

           // chance of going from infected to susceptible
           recov_susc_rate = ((malaria_params *) params)->recov_susc_rate;

    // number of bites
    // a mosquito bites once every two days, so every day 50% of the mosquitos
    // could potentially bite (if there are enough humans)

    // if amount of humans >= 0.5 * amount of mosquitos:
    // nb = 0.5 * amount of mosquitos 
    // else:
    // nb = 0.5 * amount of mosquitos * (humans/0.5*mosquitos)
    double nb             = 0,
           human_count    = y[Hu] + y[Hi] + y[Hr],
           mosquito_count = y[Mu] + y[Mi];

    if (human_count >= (0.5 * mosquito_count))
        nb = 0.5 * mosquito_count;
    else
        nb = 0.5 * mosquito_count * (human_count / (0.5 * mosquito_count));

    /* humans */

    // susceptible humans
    // dHu = new humans + recovered infecteds + immunes who lost their immunity -
    // deaths - people that get infected (number of mosquito bites * the ratio
    // of infected mosquitos)
    //
    // dHu = birthrate * Hu + recovery rate * Hi + immunity_loss_rate * Hr
    // - deathrate * Hu - nb * (Mi/Mi+Mu)
    dy[Hu] = birthrate * y[Hu] + recov_susc_rate * y[Hi] +
             imm_loss_rate * y[Hr] - deathrate * y[Hu] -
             nb * (y[Mi] / (y[Mi] + y[Mu]));


    // infected humans
    // dHi = new infecteds - recovered infecteds - dead infecteds
    //
    // dHi = nb * (Mi/Mi+Mu) - recovery_rate_immune * Hi -
    // recovery_rate_susceptible - fatality_rate * Hi
    dy[Hi] = nb * (y[Mi] / y[Mi] + y[Mu]) - recov_imm_rate * y[Hi] -
             recov_susc_rate * y[Hi] - fatality_rate * y[Hi];

    // immune (resistant) humans
    // dHr = infecteds who became resistant - immunes who became susceptible -
    // immunes who died
    //
    // dHr = recov_imm_rate * Hi - imm_loss_rate * Hr - deathrate * Hr
    dy[Hr] = recov_imm_rate * y[Hi] - imm_loss_rate * y[Hr] - deathrate * y[Hr];

    /* mosquitos 
    * 
     * Mosquitos live for 10 days
     * Their population is stable
     * That means that every day, 10% of infected mosquitos die and get "reborn"
     * as uninfected.
     */

    // uninfected mosquitos
    // dMu = 10% of the infected mosquitos - the amount of infected people
    // bitten by uninfected mosquitos
    //
    // dMu = 0.1 * Mi - nb * (Mu / (Mi+Mu)) * (Hi / (Hi+Hu+Hr))
    dy[Mu] = 0.1 * y[Mi] - nb * (y[Mu] / (y[Mi] + y[Mu])) *
        (y[Hi] / (y[Hi] + y[Hu] + y[Hr]));

    // infected mosquitos
    // dMi = the amount of infected people bitten by uninfected mosquitos - 10%
    // of the infected mosquitos
    //
    // dMi = nb * (Mu / (Mi+Mu)) * (Hi / (Hi+Hu+Hr)) - 0.1 * Mi 
    
    dy[Mi] = nb * (y[Mu] / (y[Mi] + y[Mu])) * (y[Hi] / (y[Hi] + y[Hu] + y[Hr]))
        - 0.1 * y[Mi];

    return 0;
}

// parses the command-line input into a a parameter struct
void parse_params(const char *argv[], double param_array[])
{
    param_array[0] = atof(argv[0]);
    param_array[1] = atof(argv[1]);
    param_array[2] = atof(argv[2]);
    param_array[3] = atof(argv[3]);
    param_array[4] = atof(argv[4]);
    param_array[5] = atof(argv[5]);

    // initial values
    param_array[6] = atof(argv[6]);
    param_array[7] = atof(argv[7]);
    param_array[8] = atof(argv[8]);
    param_array[9] = atof(argv[9]);
    param_array[10] = atof(argv[10]);
}

int main(int argc, const char *argv[])
{
    if (argc < 6) {
        printf("Usage: ./malaria birthrate deathrate fatality_rate imm_loss_rate recov_imm_rate recov_susc_rate ...\n\
    initial susceptible_humans infected_humans resistant_humans uninfected_mosquitos infected_mosquitos\n");
        exit(1);
    }

    double param_array[ARRAY_SIZE + 6];
    parse_params(argv, param_array);

    malaria_params params = make_params(param_array[0],
                                        param_array[1],
                                        param_array[2],
                                        param_array[3],
                                        param_array[4],
                                        param_array[5]);

    // Susceptible humans, infected humans, resistant humans, uninfected
    // mosquitos, infected mosquitos
    double y0[ARRAY_SIZE] = {param_array[6], param_array[7], param_array[8], param_array[9]};
    double y1[ARRAY_SIZE];
    char *labels[ARRAY_SIZE] = {"Susceptible humans", "Infected humans",
        "Resistant humans", "Uninfected mosquitos", "Infected mosquitos"};

    RungeKutta4_plot_labels(0, 100, 1, y0, y1, ARRAY_SIZE, &malaria,
                            (void *)(&params), labels);

    return 0;
}
