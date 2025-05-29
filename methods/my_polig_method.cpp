/**
 * @file methods/my_polig_method.cpp
 * @author Nika Adzhindzhal
 */

#include <cmath>
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>
#include "methods.hpp"
#include <point.hpp>
#include <polygon.hpp>     
#include <my_polig.hpp>    // ��� starPolygon

namespace geometry {

    int My_PoligMethod(const nlohmann::json& input, nlohmann::json* output) {
        double precision;
        std::vector<Point<double>> points;

        try {
            // ������ ����� ��������� (�������� � �����)
            precision = input.at("precision").get<double>();
            auto pointsArray = input.at("points");
            for (const auto& point : pointsArray) {
                double x = point.at("x").get<double>();
                double y = point.at("y").get<double>();
                points.push_back(Point<double>(x, y));
            }
        }
        catch (const nlohmann::json::exception& e) {
            std::cerr << "������ JSON: " << e.what() << std::endl;
            return -1;
        }

        // ��������� ������� �����
        if (points.empty()) {
            std::cerr << "����� �� �������������" << std::endl;
            return -1;
        }

        // �������� �������� ���������� ��������������
        std::cout << "START" << std::endl;
        Polygon<double>* poly = starPolygon(points, precision);
        if (poly == nullptr) {
            std::cerr << "������ �������� ��������������" << std::endl;
            return -1;
        }
        std::cout << "FINISH" << std::endl;

        // �������� ������� ��������������
        std::list<Point<double>> vertices = poly->Vertices();

        // ��������� �������� ������
        (*output)["vertices"] = nlohmann::json::array();
        for (const auto& vertex : vertices) {
            nlohmann::json v;
            v["x"] = vertex.X();
            v["y"] = vertex.Y();
            (*output)["vertices"].push_back(v);
        }

        delete poly;  // ����������� ������
        return 0;
    }

}  // namespace geometry
