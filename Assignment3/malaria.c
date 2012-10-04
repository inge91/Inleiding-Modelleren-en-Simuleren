#include <stdio.h>

#include "differentials.h"

typedef struct {
    double birthrate,
           deathrate,
           fatality_rate,
           imm_loss_rate,
           recov_imm_rate,
           recov_susc_rate;
} malaria_params;

int malaria(double t, double *y, double *dy, void *params)
{
    int Hu = 0,
        Hi = 1,
        Hr = 2,
        Mu = 3,
        Mi = 4,
        nb = 5;

    double birthrate       = ((malaria_params *) params)->birthrate,
           deathrate       = ((malaria_params *) params)->deathrate,
           fatality_rate   = ((malaria_params *) params)->fatality_rate,
           imm_loss_rate   = ((malaria_params *) params)->imm_loss_rate,

           // chance of going from infected to resistant
           recov_imm_rate  = ((malaria_params *) params)->recov_imm_rate,    

           // chance of going from infected to susceptible
           recov_susc_rate = ((malaria_params *) params)->recov_susc_rate;

    // susceptible humans
    // dHu = new humans + recovered infecteds + immunes who lost their immunity -
    // deaths - people that get infected (number of mosquito bites * the ratio
    // of infected mosquitos)
    //
    // dHu = birthrate * Hu + recovery rate * Hi + immunity_loss_rate * Hr
    // - deathrate * Hu - nb * (Mi/Mi+Mu)
    dy[Hu] = birthrate * y[Hu] + recovery_rate * y[Hi] +
             imm_loss_rate * y[Hr] - deathrate * y[Hu] -
             y[nb] * (y[Mi] / (y[Mi] + y[Mu]));


    // infected humans
    // dHi = new infecteds - recovered infecteds - dead infecteds
    //
    // dHi = nb * (Mi/Mi+Mu) - recovery_rate_immune * Hi -
    // recovery_rate_susceptible - fatality_rate * Hi
    dy[Hi] = y[nb] * (y[Mi] / y[Mi + y[Mu]]) - recov_imm_rate * y[Hi] -
             recov_susc_rate * y[Hi] - fatality_rate * y[Hi];

    // immune (resistant) humans
    // dHr = infecteds who became resistant - immunes who became susceptible -
    // immunes who died
    //
    // dHr = recov_imm_rate * Hi - imm_loss_rate * Hr - deathrate * Hr
    dy[Hr] = recov_imm_rate * y[Hi] - imm_loss_rate * y[Hr] - deathrate * y[Hr];

    return 0;
}

int main(int argc, const char *argv[])
{
    printf("Hello\n");
    return 0;
}
