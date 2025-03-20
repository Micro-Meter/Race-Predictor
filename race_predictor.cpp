#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

class RacePredictor {
private:
    std::vector<double> times;  // Race times in minutes
    std::vector<int> distances; // Race distances in kilometers

    double calculateAverage() {
        if (times.empty()) return 0.0;
        return std::accumulate(times.begin(), times.end(), 0.0) / times.size();
    }

    void calculateLinearRegression(double& slope, double& intercept) {
        if (times.size() < 2) {
            slope = 0;
            intercept = 0;
            return;
        }

        double x_mean = std::accumulate(distances.begin(), distances.end(), 0.0) / distances.size();
        double y_mean = std::accumulate(times.begin(), times.end(), 0.0) / times.size();

        double numerator = 0.0;
        double denominator = 0.0;

        for (size_t i = 0; i < times.size(); ++i) {
            numerator += (distances[i] - x_mean) * (times[i] - y_mean);
            denominator += (distances[i] - x_mean) * (distances[i] - x_mean);
        }

        slope = denominator != 0 ? numerator / denominator : 0;
        intercept = y_mean - slope * x_mean;
    }

public:
    void addRaceData(double time, int distance) {
        times.push_back(time);
        distances.push_back(distance);
    }

    double predictByAverage(int targetDistance) {
        double avgPacePerKm = calculateAverage() / distances[0]; // Assuming consistent distance
        return avgPacePerKm * targetDistance;
    }

    double predictByRegression(int targetDistance) {
        double slope, intercept;
        calculateLinearRegression(slope, intercept);
        return slope * targetDistance + intercept;
    }
};

int main() {
    RacePredictor predictor;
    char choice;
    
    std::cout << "Race Time Predictor\n";
    std::cout << "===================\n";

    do {
        double time;
        int distance;
        
        std::cout << "\nEnter race data:\n";
        std::cout << "Time (in minutes): ";
        std::cin >> time;
        std::cout << "Distance (in kilometers): ";
        std::cin >> distance;

        predictor.addRaceData(time, distance);

        std::cout << "\nPredict for which distance (km)? ";
        int targetDistance;
        std::cin >> targetDistance;

        double avgPrediction = predictor.predictByAverage(targetDistance);
        double regressionPrediction = predictor.predictByRegression(targetDistance);

        std::cout << "\nPredictions for " << targetDistance << "km:\n";
        std::cout << "Based on average pace: " << avgPrediction << " minutes\n";
        std::cout << "Based on linear regression: " << regressionPrediction << " minutes\n";

        std::cout << "\nAdd another race? (y/n): ";
        std::cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    return 0;
}
