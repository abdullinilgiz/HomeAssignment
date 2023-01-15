#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <memory>
#include <random>

class Coords {
private:
    std::vector<std::pair<double, double>> coords;
public:
    void Add(std::pair<double, double> coord) {
        coords.push_back(coord);
    }
    void Normalize() {
        double delim;
        for(auto& item : coords) {
            delim = sqrt(pow(item.first, 2) + pow(item.second, 2));;
            item.first /= delim;
            item.second /= delim;
        }
    }
    void PrintCoords(std::ostream& out_stream) const {
        if (coords.size() == 1) {
            out_stream << "LINE     " ;
        } else {
            out_stream << "ELLIPSE  ";
        }
        out_stream << "X: " << std::setw(9) << coords[0].first;
        for (const auto& item : coords) {
            out_stream <<  "  Y: " << std::setw(9) << item.second;
        }
        out_stream <<'\n';
    }
    auto begin() {
        return coords.begin();
    }
    auto end() {
        return coords.end();
    }
};

class Curve {
public:
    virtual Coords getCoords(double x) const = 0;
    virtual Coords getDeriv(double x) const = 0;
};

class Line : public Curve {
private:
    double constant;
    double multiplayer;
public:
    Line(double constant_, double multiplayer_) {
        constant = constant_;
        multiplayer = multiplayer_;
    }

    Coords getCoords(double x) const override {
        Coords result;
        result.Add(std::make_pair(x, constant + multiplayer * x));
        return result;
    }

    Coords getDeriv(double x) const override {
        Coords derivative;
        derivative.Add(std::make_pair(1, multiplayer));
        derivative.Normalize();
        return derivative;
    }

    ~Line() = default;
};

class Ellipse : public Curve {
private:
    double x_radius;
    double y_radius;
public:
    Ellipse(double x, double y) {
        x_radius = x;
        y_radius = y;
    }

    Coords getCoords(double x) const override {
        if (std::abs(x) > x_radius) {
            throw std::invalid_argument("|x| > x_radius");
        }
        Coords result;
        result.Add(std::make_pair(x, y_radius * sqrt(1 - pow(x, 2) / pow(x_radius, 2))));
        if (std::abs(x) != x_radius) {
            result.Add(std::make_pair(x, -y_radius * sqrt(1 - pow(x, 2) / pow(x_radius, 2))));
        }
        return result;
    }

    Coords getDeriv(double x) const override {
        if (std::abs(x) > x_radius) {
            throw std::invalid_argument("|x| > x_radius");
        }
        Coords derivatives;
        if (std::abs(x) < x_radius) {
            derivatives.Add(std::make_pair(1, -y_radius * x
                                              / sqrt(pow(x_radius, 2) - pow(x, 2))));
            derivatives.Add(std::make_pair(1, y_radius * x
                                              / sqrt(pow(x_radius, 2) - pow(x, 2))));
            derivatives.Normalize();
        } else {
            throw  std::invalid_argument("derivative not defined");
        }
        return derivatives;
    }

    ~Ellipse() = default;
};

const double PI = 3.14159265358979323846;

int main() {
    std::mt19937 mersenneRNG(13);
    std::vector<std::shared_ptr<Curve>> curves;
    for (int i = 0; i < 5; ++i){
        curves.push_back(std::make_shared<Ellipse>(mersenneRNG() % 10, mersenneRNG() % 10));
    }
    for (int i = 0; i < 5; ++i) {
        curves.push_back(std::make_shared<Line>(mersenneRNG() % 10, mersenneRNG() % 10));
    }
    std::vector<Coords> coords;
    std::vector<Coords> derivatives;
    for (const auto& item : curves){
        coords.push_back(item->getCoords(PI / 4));
        derivatives.push_back(item->getDeriv(PI / 4));
    }
    std::cout << "COORDS" << std::endl;
    for (const auto& item : coords){
        item.PrintCoords(std::cout);
    }
    std::cout << "DERIVATIVES" << std::endl;
    for (const auto& item : derivatives){
        item.PrintCoords(std::cout);
    }

    return 0;
}
