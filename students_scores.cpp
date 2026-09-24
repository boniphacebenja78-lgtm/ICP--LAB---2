#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const int score_range = 8;

//using two arrays to hold higher and lower scores.

int lowerlimit[score_range] = {0, 25, 50, 75, 100, 125, 150, 175};
int upperlimit[score_range] = {24, 49, 74, 99, 124, 149, 174, 200};

//putting score inot correct group and count frequency.
void countFrequency(int score[], int n, int frequency[]){
    for (int r = 0; r < score_range; r++){
        frequency[r] = 0;
    }
    for (int i = 0; i < n; i++){
        for(int j = 0; j < score_range; j++){
            if(score[i] >= lowerlimit[j] && score[i] <= upperlimit[j]){
                frequency[j]++;
            }
            
        }

    }

}
// functions(midpoint);
double calculateMidpoint(int lowerlimit, int upperlimit){
    return (lowerlimit + upperlimit) / 2.0;
}

//functions (mean) mean is sum of f*x / sum of f
double calculateMean(int frequency[], double Midpoint[]){
    double sumfx = 0;
    double sumf = 0;
    for (int r = 0; r < score_range; r++){
        sumfx += Midpoint[r] * frequency[r];
        sumf += frequency[r];
    }
    return sumfx / sumf;
}

//function (variance)vairance is sum of f*(x - mean)^2 / sum of f;
double calculateVariance(int frequency[], double  Midpoint[],double mean){
    double sumf = 0;
    double sumfx2 = 0;
    for (int r = 0; r < score_range; r++){
        sumf += frequency[r];
        sumfx2 += frequency[r] * pow(calculateMidpoint(lowerlimit[r], upperlimit[r]) - mean, 2);
    }
    return sumfx2 / sumf;
}

//standard deviation is srqt(variance);
double calculateStandardDeviation(double variance){
    double StandardDeviation = sqrt(variance);
    return double(StandardDeviation);

}
int main(){
    int n;
    cout << "Enter number of students:" << endl;
    cin >> n;

    int scores[n];

    //entering scores of students
    cout << "enter the score of the students;" << endl;
    for (int i = 0; i < n; i++){
        int studentScore;
        cin >> studentScore;
        while (studentScore < 0 || studentScore > 200){
            cout << " invalid score, please enter a score between 0 nad 200:"<< endl;
            cin >> studentScore;
        }
        scores[i] = studentScore;

    //midpoint of each group
    double Midpoint[score_range];
    for (int r = 0; r < score_range; r++){
        Midpoint[r] = calculateMidpoint(lowerlimit[r], upperlimit[r]) / 2.0;
    }
    int frequency[score_range];
    countFrequency(scores, n, frequency);

    double mean = calculateMean(frequency, Midpoint);
    double variance = calculateVariance(frequency, Midpoint, mean);
    double standardDeviation = calculateStandardDeviation(variance);

    //table
    cout << left << setw(7) << "group_score" << setw(7) << "midpoint" << setw(7) <<"frequency" << setw(7) << "fx" << setw(7) << "(x - mean)^2" << setw(7) << "f*(x - mean)^2" << endl;

    double sumfx = 0;
    double sumf = 0;
    double sumfx2 = 0;
    for (int r = 0; r < score_range; r++){
        double fx = Midpoint[r] * frequency[r];
        double x_minus_mean_squared = pow(Midpoint[r] - mean, 2);
        double f_times_x_minus_mean_squared = frequency[r] * x_minus_mean_squared;
        sumfx += fx;
        sumf += frequency[r];
        sumfx2 += f_times_x_minus_mean_squared;

        cout << left << setw(7) << lowerlimit[r] << "-" << upperlimit[r] << setw(7) << Midpoint[r] << setw(7) << frequency[r] << setw(7) << fx << setw(7) << x_minus_mean_squared << setw(7) << f_times_x_minus_mean_squared << endl;

        sumf = sumf + frequency[r];
        sumfx = sumfx + fx;
        sumfx2 = sumfx2 + f_times_x_minus_mean_squared;


    }
    cout << "Total" << setw(7) << "" << setw(7) << sumf << setw(7) << sumfx << setw(7) << "" << setw(7) << sumfx2 << endl;

    cout << fixed << setprecision(2);
    cout << "Mean: " << mean << endl;
    cout << "Variance: " << variance << endl;
    cout << "Standard Deviation: " << standardDeviation << endl;

    delete[] scores;
    return 0 ;


        
}